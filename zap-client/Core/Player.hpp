#pragma once
#include <string>
#include "Offsets.hpp"
#include "LocalPlayer.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/Memory.hpp"
#include "../Utils/HitboxType.hpp"
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

struct Player
{
    LocalPlayer *Myself;

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

    Player(int PlayerIndex, LocalPlayer *Me)
    {
        this->Index = PlayerIndex;
        this->Myself = Me;
    }

    void Read()
    {
        BasePointer = Memory::Read<long>(OFF_REGION + OFF_ENTITY_LIST + ((Index + 1) << 5));
        if (BasePointer == 0)
            return;

        Name = Memory::ReadString1(BasePointer + OFF_NAME);
        Team = Memory::Read<int>(BasePointer + OFF_TEAM_NUMBER);

        if (!IsPlayer() && !IsDummy())
        {
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

        /*LastVisibleTime = Memory::Read<int>(BasePointer + OFF_LAST_VISIBLE_TIME);
        IsVisible = IsAimedAt || LastTimeVisiblePrevious < LastVisibleTime;
        LastTimeVisiblePrevious = LastVisibleTime;*/

        float WorldTime = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE);
        float Time1;
        Time1 = Memory::Read<float>(BasePointer + OFF_LAST_VISIBLE_TIME);
        IsVisible = (Time1 + 0.2) >= WorldTime || IsAimedAt;

        Health = Memory::Read<int>(BasePointer + OFF_HEALTH);
        MaxHealth = Memory::Read<int>(BasePointer + OFF_MAXHEALTH);
        Shield = Memory::Read<int>(BasePointer + OFF_SHIELD);
        MaxShield = Memory::Read<int>(BasePointer + OFF_MAXSHIELD);

        if (!IsDead && !IsKnocked && IsHostile)
        {
            long WeaponHandle = Memory::Read<long>(BasePointer + OFF_WEAPON_HANDLE);
            long WeaponHandleMasked = WeaponHandle & 0xffff;
            WeaponEntity = Memory::Read<long>(OFF_REGION + OFF_ENTITY_LIST + (WeaponHandleMasked << 5));

            int OffHandWeaponID = Memory::Read<int>(BasePointer + OFF_OFFHAND_WEAPON);
            IsHoldingGrenade = OffHandWeaponID == -251 ? true : false;

            WeaponIndex = Memory::Read<int>(WeaponEntity + OFF_WEAPON_INDEX);
        }

        if (Myself->IsValid()) {
        	IsLocal = Myself->BasePointer == BasePointer;
                IsAlly = IsTeammate();
                IsHostile = !IsAlly;
                DistanceToLocalPlayer = Myself->LocalOrigin.Distance(LocalOrigin);
                Distance2DToLocalPlayer = Myself->LocalOrigin.To2D().Distance(LocalOrigin.To2D());
		    if (IsVisible) {
		        aimbotDesiredAngles = calcDesiredAngles();
		        aimbotDesiredAnglesIncrement = calcDesiredAnglesIncrement();
		        aimbotScore = calcAimbotScore();
		    }
        }

        // For AimbotMode Grinder
        localOrigin = Memory::Read<FloatVector3D>(BasePointer + OFF_LOCAL_ORIGIN);
        absoluteVelocity = Memory::Read<FloatVector3D>(BasePointer + OFF_ABSVELOCITY);
        FloatVector3D localOrigin_diff = localOrigin.subtract(localOrigin_prev).normalize().multiply(20);
        localOrigin_predicted = localOrigin.add(localOrigin_diff);
        localOrigin_prev = FloatVector3D(localOrigin.x, localOrigin.y, localOrigin.z);

        DistanceToLocalPlayer = Myself->LocalOrigin.Distance(LocalOrigin);
        Distance2DToLocalPlayer = Myself->LocalOrigin.To2D().Distance(LocalOrigin.To2D());
    }

    std::string GetPlayerName()
    {
        uintptr_t NameIndex = Memory::Read<uintptr_t>(BasePointer + OFF_NAME_INDEX);
        uintptr_t NameOffset = Memory::Read<uintptr_t>(OFF_REGION + OFF_NAME_LIST + ((NameIndex - 1) * 24));
        std::string PlayerName = Memory::ReadPlayerName(NameOffset, 64);
        return PlayerName;
    }

    std::string getPlayerModelName()
    {
        uintptr_t modelOffset = Memory::Read<uintptr_t>(BasePointer + OFF_MODELNAME);
        std::string modelName = Memory::ReadLegend(modelOffset, 1024);
        // Check for different player names
        if (modelName.find("dummie") != std::string::npos)
            modelName = "Dummy";
        else if (modelName.find("ash") != std::string::npos)
            modelName = "Ash";
        else if (modelName.find("ballistic") != std::string::npos)
            modelName = "Ballistic";
        else if (modelName.find("bangalore") != std::string::npos)
            modelName = "Bangalore";
        else if (modelName.find("bloodhound") != std::string::npos)
            modelName = "Bloodhound";
        else if (modelName.find("catalyst") != std::string::npos)
            modelName = "Catalyst";
        else if (modelName.find("caustic") != std::string::npos)
            modelName = "Caustic";
        else if (modelName.find("conduit") != std::string::npos)
            modelName = "Conduit";
        else if (modelName.find("crypto") != std::string::npos)
            modelName = "Crypto";
        else if (modelName.find("fuse") != std::string::npos)
            modelName = "Fuse";
        else if (modelName.find("gibraltar") != std::string::npos)
            modelName = "Gibraltar";
        else if (modelName.find("horizon") != std::string::npos)
            modelName = "Horizon";
        else if (modelName.find("nova") != std::string::npos)
            modelName = "Horizon";
        else if (modelName.find("holo") != std::string::npos)
            modelName = "Mirage";
        else if (modelName.find("mirage") != std::string::npos)
            modelName = "Mirage";
        else if (modelName.find("lifeline") != std::string::npos)
            modelName = "Lifeline";
        else if (modelName.find("loba") != std::string::npos)
            modelName = "Loba";
        else if (modelName.find("madmaggie") != std::string::npos)
            modelName = "Mad Maggie";
        else if (modelName.find("newcastle") != std::string::npos)
            modelName = "Newcastle";
        else if (modelName.find("octane") != std::string::npos)
            modelName = "Octane";
        else if (modelName.find("pathfinder") != std::string::npos)
            modelName = "Pathfinder";
        else if (modelName.find("rampart") != std::string::npos)
            modelName = "Rampart";
        else if (modelName.find("revenant") != std::string::npos)
            modelName = "Revenant";
        else if (modelName.find("seer") != std::string::npos)
            modelName = "Seer";
        else if (modelName.find("stim") != std::string::npos)
            modelName = "Octane";
        else if (modelName.find("valkyrie") != std::string::npos)
            modelName = "Valkyrie";
        else if (modelName.find("vantage") != std::string::npos)
            modelName = "Vantage";
        else if (modelName.find("wattson") != std::string::npos)
            modelName = "Wattson";
        else if (modelName.find("wraith") != std::string::npos)
            modelName = "Wraith";

        return modelName;
    }

    bool IsItem()
    {
        return Name == "prop_survival";
    }

    float GetViewYaw()
    {
        if (!IsDummy() || IsPlayer())
        {
            return Memory::Read<float>(BasePointer + OFF_YAW);
        }
        return 0.0f;
    }

    bool IsValid()
    {
        return BasePointer != 0 && Health > 0 && (IsPlayer() || IsDummy());
    }

    bool IsCombatReady()
    {
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

    bool IsPlayer()
    {
        return Name == "player";
    }

    bool IsDummy()
    {
        return Team == 97;
    }

    bool IsTeammate()
    {
        if (LvMap::m_mixtape && Myself->Squad == -1)
        {
            return (Team & 1) == (Myself->Team & 1);
        }
        else
        {
            return Team == Myself->Team;
        }
    }

    // Bones //
    int GetBoneFromHitbox(HitboxType HitBox) const
    {
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

    Vector3D GetBonePosition(HitboxType HitBox) const
    {
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
    float calcDesiredPitch()
    {
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

    float calcDesiredYaw()
    {
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

    FloatVector2D calcDesiredAngles()
    {
        return FloatVector2D(calcDesiredPitch(), calcDesiredYaw());
    }

    FloatVector2D calcDesiredAnglesIncrement()
    {
        return FloatVector2D(calcPitchIncrement(), calcYawIncrement());
    }

    float calcPitchIncrement()
    {
        float wayA = aimbotDesiredAngles.x - Myself->viewAngles.x;
        float wayB = 180 - abs(wayA);
        if (wayA > 0 && wayB > 0)
            wayB *= -1;
        if (fabs(wayA) < fabs(wayB))
            return wayA;
        return wayB;
    }

    float calcYawIncrement()
    {
        float wayA = aimbotDesiredAngles.y - Myself->viewAngles.y;
        float wayB = 360 - abs(wayA);
        if (wayA > 0 && wayB > 0)
            wayB *= -1;
        if (fabs(wayA) < fabs(wayB))
            return wayA;
        return wayB;
    }

    float calcAimbotScore()
    {
        return (1000 - (fabs(aimbotDesiredAnglesIncrement.x) + fabs(aimbotDesiredAnglesIncrement.y)));
    }
};
