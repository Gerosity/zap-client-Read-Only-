#pragma once
#include <string>
#include "Offsets.hpp"
#include "LocalPlayer.hpp"
#include "Level.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/Memory.hpp"
#include "../Utils/HitboxType.hpp"
#include "../Utils/Weapons.hpp"
#include "../Math/Vector2D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Math/FloatVector2D.hpp"
#include "../Math/FloatVector3D.hpp"
#include "../Math/Matrix.hpp"
#include "../Overlay/Overlay.hpp"
#include "GlowMode.hpp"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

struct Player {
    LocalPlayer* Myself;

    int Index;
    long BasePointer;

    std::string Name;
    int Team;

    int GlowEnable;
    int GlowThroughWall;
    int HighlightID;

    bool IsDead;
    bool IsKnocked;

    Vector2D ViewAngles;
    Vector3D LocalOrigin;
    Vector3D AbsoluteVelocity;

    int Health;
    int MaxHealth;
    int Shield;
    int MaxShield;

    int LastTimeAimedAt;
    int LastTimeAimedAtPrevious;
    bool IsAimedAt;

    int LastVisibleTime;
    int LastTimeVisiblePrevious;
    bool IsVisible;

    bool IsLocal;
    bool IsAlly;
    bool IsHostile;
    bool nonBR;
    bool friendly;

    int WeaponIndex;
    bool IsHoldingGrenade;
    long WeaponEntity;

    float DistanceToLocalPlayer;
    float Distance2DToLocalPlayer;

    float ViewYaw;

    bool IsLockedOn = false;

    // For AimbotMode Grinder
    int ducking;
    // bool aimbotLocked;
    FloatVector3D localOrigin_prev;
    FloatVector3D localOrigin;
    FloatVector3D absoluteVelocity;
    FloatVector3D localOrigin_predicted;
    FloatVector2D aimbotDesiredAngles;
    FloatVector2D aimbotDesiredAnglesIncrement;
    FloatVector2D aimbotDesiredAnglesSmoothed;
    float aimbotScore;
    FloatVector2D aimbotDesiredAnglesSmoothedNoRecoil;

    Player(int PlayerIndex, LocalPlayer* Me) {
        this->Index = PlayerIndex;
        this->Myself = Me;
    }

    void Read() {
        BasePointer = Memory::Read<long>(OFF_REGION + OFF_ENTITY_LIST + ((Index + 1) << 5));
        if (BasePointer == 0)
            return;

        Name = Memory::ReadString(BasePointer + OFF_NAME);
        Team = Memory::Read<int>(BasePointer + OFF_TEAM_NUMBER);

        if (!IsPlayer() && !IsDummy()) {
            BasePointer = 0;
            return;
        }
        IsDead = (IsDummy()) ? false : Memory::Read<short>(BasePointer + OFF_LIFE_STATE) > 0;
        IsKnocked = (IsDummy()) ? false : Memory::Read<short>(BasePointer + OFF_BLEEDOUT_STATE) > 0;

        LocalOrigin = Memory::Read<Vector3D>(BasePointer + OFF_LOCAL_ORIGIN);
        AbsoluteVelocity = Memory::Read<Vector3D>(BasePointer + OFF_ABSVELOCITY);
        ViewAngles = Memory::Read<Vector2D>(BasePointer + OFF_VIEW_ANGLES);
        ViewYaw = Memory::Read<float>(BasePointer + OFF_YAW);

        GlowEnable = Memory::Read<int>(BasePointer + OFF_GLOW_ENABLE);
        GlowThroughWall = Memory::Read<int>(BasePointer + OFF_GLOW_THROUGH_WALL);
        HighlightID = Memory::Read<int>(BasePointer + OFF_GLOW_HIGHLIGHT_ID + 1);

        LastTimeAimedAt = Memory::Read<int>(BasePointer + OFF_LAST_AIMEDAT_TIME);
        IsAimedAt = LastTimeAimedAtPrevious < LastTimeAimedAt;
        LastTimeAimedAtPrevious = LastTimeAimedAt;

        float WorldTime = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE);
        float Time1;
        Time1 = Memory::Read<float>(BasePointer + OFF_LAST_VISIBLE_TIME);
        IsVisible = (Time1 + 0.2) >= WorldTime || IsAimedAt;

        Health = Memory::Read<int>(BasePointer + OFF_HEALTH);
        MaxHealth = Memory::Read<int>(BasePointer + OFF_MAXHEALTH);
        Shield = Memory::Read<int>(BasePointer + OFF_SHIELD);
        MaxShield = Memory::Read<int>(BasePointer + OFF_MAXSHIELD);

        if (Myself->IsValid()) {
            IsLocal = Myself->BasePointer == BasePointer;
            IsAlly = IsTeammate();
            IsHostile = !IsAlly;
            DistanceToLocalPlayer = Myself->LocalOrigin.Distance(LocalOrigin);
            Distance2DToLocalPlayer = Myself->LocalOrigin.To2D().Distance(LocalOrigin.To2D());
            if (IsVisible) { // For AimbotMode Grinder
                aimbotDesiredAngles = calcDesiredAngles();
                aimbotDesiredAnglesIncrement = calcDesiredAnglesIncrement();
                aimbotScore = calcAimbotScore();
            }
        }

        if (!IsDead && !IsKnocked && IsHostile) {
            long WeaponHandle = Memory::Read<long>(BasePointer + OFF_WEAPON_HANDLE);
            long WeaponHandleMasked = WeaponHandle & 0xffff;
            WeaponEntity = Memory::Read<long>(OFF_REGION + OFF_ENTITY_LIST + (WeaponHandleMasked << 5));

            int OffHandWeaponID = Memory::Read<int>(BasePointer + OFF_OFFHAND_WEAPON);
            IsHoldingGrenade = OffHandWeaponID == -251 ? true : false;

            WeaponIndex = Memory::Read<int>(WeaponEntity + OFF_WEAPON_INDEX);
        }

        // For AimbotMode Grinder
        localOrigin = Memory::Read<FloatVector3D>(BasePointer + OFF_LOCAL_ORIGIN);
        absoluteVelocity = Memory::Read<FloatVector3D>(BasePointer + OFF_ABSVELOCITY);
        FloatVector3D localOrigin_diff = localOrigin.subtract(localOrigin_prev).normalize().multiply(20);
        localOrigin_predicted = localOrigin.add(localOrigin_diff);
        localOrigin_prev = FloatVector3D(localOrigin.x, localOrigin.y, localOrigin.z);
    }

    bool IsSpectating() {
        if (!IsDead)
            return false;
        uint64_t SpectatorList = Memory::Read<uint64_t>(OFF_REGION + 0x1EACCE8);
        int PlayerData = Memory::Read<int>(BasePointer + 0x38);
        int SpecIndex = Memory::Read<int>(SpectatorList + PlayerData*8 + 0x964);
        uint64_t SpectatorAddr =  Memory::Read<uint64_t>(OFF_REGION + OFF_ENTITY_LIST + ((SpecIndex & 0xFFFF) << 5));
        if(SpectatorAddr == Myself->BasePointer)
            return true;
        return false;
    }

    float GetViewYaw() {
        if (!IsDummy() || IsPlayer()) {
            return Memory::Read<float>(BasePointer + OFF_YAW);
        }
        return 0.0f;
    }

    bool IsValid() {
        return BasePointer != 0 && Health > 0 && !IsDead && (IsPlayer() || IsDummy());
    }

    bool IsCombatReady() {
        if (!IsValid())
            return false;
        if (IsDummy())
            return true;
        if (IsDead)
            return false;
        if (IsKnocked)
            return false;
        return true;
    }

    bool IsPlayer() {
        return Name == "player";
    }

    bool IsDummy() {
        return Team == 97;
    }

    bool IsTeammate() {
        if (LvMap::m_mixtape && Myself->Squad == -1) {
            return (Team & 1) == (Myself->Team & 1);
        } else {
            return Team == Myself->Team;
        }
    }

    // Bones //
    int GetBoneFromHitbox(HitboxType HitBox) const {
        long ModelPointer = Memory::Read<long>(BasePointer + OFF_STUDIOHDR);
        if (!Memory::IsValidPointer(ModelPointer))
            return -1;

        long StudioHDR = Memory::Read<long>(ModelPointer + 0x8);
        if (!Memory::IsValidPointer(StudioHDR + 0x34))
            return -1;

        auto HitboxCache = Memory::Read<uint16_t>(StudioHDR + 0x34);
        auto HitboxArray = StudioHDR + ((uint16_t)(HitboxCache & 0xFFFE) << (4 * (HitboxCache & 1)));
        if (!Memory::IsValidPointer(HitboxArray + 0x4))
            return -1;

        auto IndexCache = Memory::Read<uint16_t>(HitboxArray + 0x4);
        auto HitboxIndex = ((uint16_t)(IndexCache & 0xFFFE) << (4 * (IndexCache & 1)));
        auto BonePointer = HitboxIndex + HitboxArray + (static_cast<int>(HitBox) * 0x20);
        if (!Memory::IsValidPointer(BonePointer))
            return -1;

        return Memory::Read<uint16_t>(BonePointer);
    }

    Vector3D GetBonePosition(HitboxType HitBox) const {
        Vector3D Offset = Vector3D(0.0f, 0.0f, 0.0f);

        int Bone = GetBoneFromHitbox(HitBox);
        if (Bone < 0 || Bone > 255)
            return LocalOrigin.Add(Offset);

        long BonePtr = Memory::Read<long>(BasePointer + OFF_BONES);
        BonePtr += (Bone * sizeof(Matrix3x4));
        if (!Memory::IsValidPointer(BonePtr))
            return LocalOrigin.Add(Offset);

        Matrix3x4 BoneMatrix = Memory::Read<Matrix3x4>(BonePtr);
        Vector3D BonePosition = BoneMatrix.GetPosition();

        if (!BonePosition.IsValid())
            return LocalOrigin.Add(Vector3D(0, 0, 0));

        BonePosition += LocalOrigin;
        return BonePosition;
    }

    // For AimbotMode Grinder
    float calcDesiredPitch() {
        if (IsLocal)
            return 0;
        const FloatVector3D shift = FloatVector3D(100000, 100000, 100000);
        const FloatVector3D originA = Myself->localOrigin.add(shift);
        const float extraZ = (ducking != -1) ? 10 : 0;
        const FloatVector3D originB = localOrigin_predicted.add(shift).subtract(FloatVector3D(0, 0, extraZ));
        const float deltaZ = originB.z - originA.z;
        const float pitchInRadians = std::atan2(-deltaZ, Distance2DToLocalPlayer);
        const float degrees = pitchInRadians * (180.0f / M_PI);
        return degrees;
    }

    float calcDesiredYaw() {
        if (IsLocal)
            return 0;
        const FloatVector2D shift = FloatVector2D(100000, 100000);
        const FloatVector2D originA = Myself->localOrigin.to2D().add(shift);
        const FloatVector2D originB = localOrigin_predicted.to2D().add(shift);
        const FloatVector2D diff = originB.subtract(originA);
        const double yawInRadians = std::atan2(diff.y, diff.x);
        const float degrees = yawInRadians * (180.0f / M_PI);
        return degrees;
    }

    FloatVector2D calcDesiredAngles() {
        return FloatVector2D(calcDesiredPitch(), calcDesiredYaw());
    }

    FloatVector2D calcDesiredAnglesIncrement() {
        return FloatVector2D(calcPitchIncrement(), calcYawIncrement());
    }

    float calcPitchIncrement() {
        float wayA = aimbotDesiredAngles.x - Myself->viewAngles.x;
        float wayB = 180 - abs(wayA);
        if (wayA > 0 && wayB > 0)
            wayB *= -1;
        if (fabs(wayA) < fabs(wayB))
            return wayA;
        return wayB;
    }

    float calcYawIncrement() {
        float wayA = aimbotDesiredAngles.y - Myself->viewAngles.y;
        float wayB = 360 - abs(wayA);
        if (wayA > 0 && wayB > 0)
            wayB *= -1;
        if (fabs(wayA) < fabs(wayB))
            return wayA;
        return wayB;
    }

    float calcAimbotScore() {
        return (1000 - (fabs(aimbotDesiredAnglesIncrement.x) + fabs(aimbotDesiredAnglesIncrement.y)));
    }

    std::string GetPlayerName() {
        if (IsDummy()) {
            return "Dummie";
        } else {
            uintptr_t NameIndex = Memory::Read<uintptr_t>(BasePointer + OFF_NAME_INDEX);
            uintptr_t NameOffset = Memory::Read<uintptr_t>(OFF_REGION + OFF_NAME_LIST + ((NameIndex - 1) * 24));
            std::string PlayerName = Memory::ReadStringSize(NameOffset, 64);
            return PlayerName;
        }
    }

    std::string getPlayerModelName() {
        uintptr_t ModelOffset = Memory::Read<uintptr_t>(BasePointer + OFF_MODELNAME);
        std::string ModelName = Memory::ReadStringSize(ModelOffset, 1024);

        static std::unordered_map<std::string, std::string> ModelNameMap = { {"dummie", "Dummie"}, {"ash", "Ash"}, {"ballistic", "Ballistic"}, {"bangalore", "Bangalore"}, {"bloodhound", "Bloodhound"}, {"catalyst", "Catalyst"}, {"caustic", "Caustic"}, {"conduit", "Conduit"}, {"crypto", "Crypto"}, {"fuse", "Fuse"}, {"gibraltar", "Gibraltar"}, {"horizon", "Horizon"}, {"nova", "Horizon"}, {"holo", "Mirage"}, {"mirage", "Mirage"}, {"lifeline", "Lifeline"}, {"loba", "Loba"}, {"madmaggie", "Mad Maggie"}, {"newcastle", "Newcastle"}, {"octane", "Octane"}, {"pathfinder", "Pathfinder"}, {"rampart", "Rampart"}, {"revenant", "Revenant"}, {"seer", "Seer"}, {"stim", "Octane"}, {"valkyrie", "Valkyrie"}, {"vantage", "Vantage"}, {"wattson", "Wattson"}, {"wraith", "Wraith"}, {"alter", "Alter"}, };

        std::string replacedName = ModelName;
        for (auto& entry : ModelNameMap) {
            if (ModelName.find(entry.first) != std::string::npos) {
                replacedName = entry.second;
                break;
            }
        }

        return replacedName;
    }

    std::string GetWeaponHeldName() {
        // Variables
        int WeaponID = WeaponIndex;
        // Check if Holding Grenade
        if (IsHoldingGrenade) {
            std::string WeaponName = "Throwable";
            return WeaponName;
        } else {
            static std::unordered_map<int, std::string> WeaponMap = { {WeaponIDs::WEAPON_P2020, "P2020"}, {WeaponIDs::WEAPON_RE45, "RE-45"}, {WeaponIDs::WEAPON_ALTERNATOR, "Alternator"}, {WeaponIDs::WEAPON_R301, "R-301"}, {WeaponIDs::WEAPON_R99, "R-99"}, {WeaponIDs::WEAPON_SPITFIRE, "Spitfire"}, {WeaponIDs::WEAPON_G7, "G7 Scout"}, {WeaponIDs::WEAPON_FLATLINE, "Flatline"}, {WeaponIDs::WEAPON_PROWLER, "Prowler"}, {WeaponIDs::WEAPON_HEMLOCK, "Hemlock"}, {WeaponIDs::WEAPON_REPEATER, "30-30 Repeater"}, {WeaponIDs::WEAPON_RAMPAGE, "Rampage"}, {WeaponIDs::WEAPON_CAR, "CAR-SMG"}, {WeaponIDs::WEAPON_HAVOC, "Havoc"}, {WeaponIDs::WEAPON_DEVOTION, "Devotion"}, {WeaponIDs::WEAPON_LSTAR, "L-STAR"}, {WeaponIDs::WEAPON_TRIPLETAKE, "Triple Take"}, {WeaponIDs::WEAPON_VOLT, "Volt"}, {WeaponIDs::WEAPON_NEMESIS, "Nemesis"}, {WeaponIDs::WEAPON_MOZAMBIQUE, "Mozambique"}, {WeaponIDs::WEAPON_PEACEKEEPER, "Peacekeeper"}, {WeaponIDs::WEAPON_MASTIFF, "Mastiff"}, {WeaponIDs::WEAPON_SENTINEL, "Sentinel"}, {WeaponIDs::WEAPON_CHARGE_RIFLE, "Charge Rifle"}, {WeaponIDs::WEAPON_LONGBOW, "Longbow"}, {WeaponIDs::WEAPON_WINGMAN, "Wingman"}, {WeaponIDs::WEAPON_EVA8, "EVA-8 Auto"}, {WeaponIDs::WEAPON_BOCEK, "Bocek"}, {WeaponIDs::WEAPON_KRABER, "Kraber"}, {WeaponIDs::WEAPON_KNIFE, "Throwing Knife"}, {WeaponIDs::WEAPON_HANDS, "Melee"}, };

            auto it = WeaponMap.find(WeaponID);
            if (it != WeaponMap.end()) {
                return it->second;
            } else {
                return "Unknown";
            }
        }
    }

    ImColor GetWeaponHeldColor() {
        // Variables
        int WeaponID = WeaponIndex;
        ImColor LightCol, HeavyCol, EnergyCol, ShotgunCol, SniperCol, LegendaryCol, MeleeCol, ThrowableCol;
        if (IsHoldingGrenade) {
            if (IsHostile) {
                ThrowableCol = ImColor(Features::Colors::Enemy::ThrowableWeaponColor[0], Features::Colors::Enemy::ThrowableWeaponColor[1], Features::Colors::Enemy::ThrowableWeaponColor[2], Features::Colors::Enemy::ThrowableWeaponColor[3]);
                return ThrowableCol;
            } else if (!IsHostile) {
                ThrowableCol = ImColor(Features::Colors::Teammate::ThrowableWeaponColor[0], Features::Colors::Teammate::ThrowableWeaponColor[1], Features::Colors::Teammate::ThrowableWeaponColor[2], Features::Colors::Teammate::ThrowableWeaponColor[3]);
                return ThrowableCol;
            }
        } else {
            if (IsHostile) {
                LightCol = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
                HeavyCol = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
                EnergyCol = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
                ShotgunCol = ImColor(Features::Colors::Enemy::ShotgunWeaponColor[0], Features::Colors::Enemy::ShotgunWeaponColor[1], Features::Colors::Enemy::ShotgunWeaponColor[2], Features::Colors::Enemy::ShotgunWeaponColor[3]);
                SniperCol = ImColor(Features::Colors::Enemy::SniperWeaponColor[0], Features::Colors::Enemy::SniperWeaponColor[1], Features::Colors::Enemy::SniperWeaponColor[2], Features::Colors::Enemy::SniperWeaponColor[3]);
                LegendaryCol = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
                MeleeCol = ImColor(Features::Colors::Enemy::MeleeWeaponColor[0], Features::Colors::Enemy::MeleeWeaponColor[1], Features::Colors::Enemy::MeleeWeaponColor[2], Features::Colors::Enemy::MeleeWeaponColor[3]);
                ThrowableCol = ImColor(Features::Colors::Enemy::ThrowableWeaponColor[0], Features::Colors::Enemy::ThrowableWeaponColor[1], Features::Colors::Enemy::ThrowableWeaponColor[2], Features::Colors::Enemy::ThrowableWeaponColor[3]);
            } else if (!IsHostile) {
                LightCol = ImColor(Features::Colors::Teammate::LightWeaponColor[0], Features::Colors::Teammate::LightWeaponColor[1], Features::Colors::Teammate::LightWeaponColor[2], Features::Colors::Teammate::LightWeaponColor[3]);
                HeavyCol = ImColor(Features::Colors::Teammate::HeavyWeaponColor[0], Features::Colors::Teammate::HeavyWeaponColor[1], Features::Colors::Teammate::HeavyWeaponColor[2], Features::Colors::Teammate::HeavyWeaponColor[3]);
                EnergyCol = ImColor(Features::Colors::Teammate::EnergyWeaponColor[0], Features::Colors::Teammate::EnergyWeaponColor[1], Features::Colors::Teammate::EnergyWeaponColor[2], Features::Colors::Teammate::EnergyWeaponColor[3]);
                ShotgunCol = ImColor(Features::Colors::Teammate::ShotgunWeaponColor[0], Features::Colors::Teammate::ShotgunWeaponColor[1], Features::Colors::Teammate::ShotgunWeaponColor[2], Features::Colors::Teammate::ShotgunWeaponColor[3]);
                SniperCol = ImColor(Features::Colors::Teammate::SniperWeaponColor[0], Features::Colors::Teammate::SniperWeaponColor[1], Features::Colors::Teammate::SniperWeaponColor[2], Features::Colors::Teammate::SniperWeaponColor[3]);
                LegendaryCol = ImColor(Features::Colors::Teammate::LegendaryWeaponColor[0], Features::Colors::Teammate::LegendaryWeaponColor[1], Features::Colors::Teammate::LegendaryWeaponColor[2], Features::Colors::Teammate::LegendaryWeaponColor[3]);
                MeleeCol = ImColor(Features::Colors::Teammate::MeleeWeaponColor[0], Features::Colors::Teammate::MeleeWeaponColor[1], Features::Colors::Teammate::MeleeWeaponColor[2], Features::Colors::Teammate::MeleeWeaponColor[3]);
                ThrowableCol = ImColor(Features::Colors::Teammate::ThrowableWeaponColor[0], Features::Colors::Teammate::ThrowableWeaponColor[1], Features::Colors::Teammate::ThrowableWeaponColor[2], Features::Colors::Teammate::ThrowableWeaponColor[3]);
            }

            static std::unordered_map<int, ImColor> WeaponMap = { {WeaponIDs::WEAPON_P2020, LightCol}, {WeaponIDs::WEAPON_RE45, LightCol}, {WeaponIDs::WEAPON_ALTERNATOR, LightCol}, {WeaponIDs::WEAPON_R301, LightCol}, {WeaponIDs::WEAPON_R99, LightCol}, {WeaponIDs::WEAPON_SPITFIRE, LightCol}, {WeaponIDs::WEAPON_G7, LightCol}, {WeaponIDs::WEAPON_FLATLINE, HeavyCol}, {WeaponIDs::WEAPON_PROWLER, HeavyCol}, {WeaponIDs::WEAPON_HEMLOCK, HeavyCol}, {WeaponIDs::WEAPON_REPEATER, HeavyCol}, {WeaponIDs::WEAPON_RAMPAGE, HeavyCol}, {WeaponIDs::WEAPON_CAR, HeavyCol}, {WeaponIDs::WEAPON_HAVOC, EnergyCol}, {WeaponIDs::WEAPON_DEVOTION, EnergyCol}, {WeaponIDs::WEAPON_LSTAR, EnergyCol}, {WeaponIDs::WEAPON_TRIPLETAKE, EnergyCol}, {WeaponIDs::WEAPON_VOLT, EnergyCol}, {WeaponIDs::WEAPON_NEMESIS, EnergyCol}, {WeaponIDs::WEAPON_MOZAMBIQUE, ShotgunCol}, {WeaponIDs::WEAPON_PEACEKEEPER, ShotgunCol}, {WeaponIDs::WEAPON_MASTIFF, ShotgunCol}, {WeaponIDs::WEAPON_SENTINEL, SniperCol}, {WeaponIDs::WEAPON_CHARGE_RIFLE, SniperCol}, {WeaponIDs::WEAPON_LONGBOW, SniperCol}, {WeaponIDs::WEAPON_WINGMAN, LegendaryCol}, {WeaponIDs::WEAPON_EVA8, LegendaryCol}, {WeaponIDs::WEAPON_BOCEK, LegendaryCol}, {WeaponIDs::WEAPON_KRABER, LegendaryCol}, {WeaponIDs::WEAPON_KNIFE, LegendaryCol}, {WeaponIDs::WEAPON_HANDS, MeleeCol}, };
            
            auto it = WeaponMap.find(WeaponID);
            if (it != WeaponMap.end()) {
                return it->second;
            } else {
                return ImColor(255, 255, 255);
            }
        
        }
    }

    ImColor GetShieldColor() {
        // Variables
        ImColor ShieldColor;
        if (MaxShield == 50) { // white
            ShieldColor = ImColor(247, 247, 247);
        } else if (MaxShield == 75) { // blue
            ShieldColor = ImColor(39, 178, 255);
        } else if (MaxShield == 100) { // purple
            ShieldColor = ImColor(206, 59, 255);
        } else if (MaxShield == 125) { // red
            ShieldColor = ImColor(219, 2, 2);
        } else {
            ShieldColor = ImColor(247, 247, 247);
        }
        return ShieldColor;
    }
};
