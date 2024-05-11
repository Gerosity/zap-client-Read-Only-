#pragma once
#include <iostream>
#include <vector>
#include <set>
#include "../Core/Player.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"
#include "../Utils/Memory.hpp"
#include "../Math/Vector2D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Utils/XDisplay.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/Weapons.hpp"
#include "../Core/Level.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

struct Triggerbot
{

    std::chrono::milliseconds LastClickTime;
    std::set<int> WeaponList = {};
    int Range;

    XDisplay* X11Display;
    LocalPlayer* Myself;
    std::vector<Player*>* Players;
    Level* Map;

    Triggerbot(XDisplay* X11Display, Level* Map, LocalPlayer* Myself, std::vector<Player*>* GamePlayers) {
        this->X11Display = X11Display;
        this->Map = Map;
        this->Myself = Myself;
        this->Players = GamePlayers;
    }

    static bool Save() {
        try {

            Config::Triggerbot::Enabled = Features::Triggerbot::Enabled;
            Config::Triggerbot::BindMethod = Features::Triggerbot::BindMethod;
            Config::Triggerbot::AttackMethod = Features::Triggerbot::AttackMethod;
            Config::Triggerbot::Delay = Features::Triggerbot::Delay;
            Config::Triggerbot::TriggerBind = static_cast<int>(Features::Triggerbot::TriggerBind);
            Config::Triggerbot::OnADS = Features::Triggerbot::OnADS;
            Config::Triggerbot::HipfireShotguns = Features::Triggerbot::HipfireShotguns;
            Config::Triggerbot::Range = Features::Triggerbot::Range;
            //Weapon Toggles
            //Light
            Config::Triggerbot::P2020 = Features::Triggerbot::P2020;
            Config::Triggerbot::RE45 = Features::Triggerbot::RE45;
            Config::Triggerbot::Alternator = Features::Triggerbot::Alternator;
            Config::Triggerbot::R99 = Features::Triggerbot::R99;
            Config::Triggerbot::R301 = Features::Triggerbot::R301;
            Config::Triggerbot::Spitfire = Features::Triggerbot::Spitfire;
            Config::Triggerbot::G7 = Features::Triggerbot::G7;
            //Heavy
            Config::Triggerbot::Flatline = Features::Triggerbot::Flatline;
            Config::Triggerbot::Hemlock = Features::Triggerbot::Hemlock;
            Config::Triggerbot::Repeater = Features::Triggerbot::Repeater;
            Config::Triggerbot::Rampage = Features::Triggerbot::Rampage;
            Config::Triggerbot::CARSMG = Features::Triggerbot::CARSMG;
            //Energy
            Config::Triggerbot::Havoc = Features::Triggerbot::Havoc;
            Config::Triggerbot::Devotion = Features::Triggerbot::Devotion;
            Config::Triggerbot::LSTAR = Features::Triggerbot::LSTAR;
            Config::Triggerbot::TripleTake = Features::Triggerbot::TripleTake;
            Config::Triggerbot::Volt = Features::Triggerbot::Volt;
            Config::Triggerbot::Nemesis = Features::Triggerbot::Nemesis;
            //Shotgun
            Config::Triggerbot::Mozambique = Features::Triggerbot::Mozambique;
            Config::Triggerbot::EVA8 = Features::Triggerbot::EVA8;
            Config::Triggerbot::Peacekeeper = Features::Triggerbot::Peacekeeper;
            Config::Triggerbot::Mastiff = Features::Triggerbot::Mastiff;
            //Snipers
            Config::Triggerbot::Longbow = Features::Triggerbot::Longbow;
            Config::Triggerbot::ChargeRifle = Features::Triggerbot::ChargeRifle;
            Config::Triggerbot::Sentinel = Features::Triggerbot::Sentinel;
            //Legendary
            Config::Triggerbot::Wingman = Features::Triggerbot::Wingman;
            Config::Triggerbot::Prowler = Features::Triggerbot::Prowler;
            Config::Triggerbot::Bocek = Features::Triggerbot::Bocek;
            Config::Triggerbot::Kraber = Features::Triggerbot::Kraber;
            Config::Triggerbot::Knife = Features::Triggerbot::Knife;
            //Advanced
            Config::Triggerbot::AdvancedTriggerbot = Features::Triggerbot::AdvancedTriggerbot;
            Config::Triggerbot::P2020Range = Features::Triggerbot::P2020Range;
            Config::Triggerbot::RE45Range = Features::Triggerbot::RE45Range;
            Config::Triggerbot::AlternatorRange = Features::Triggerbot::AlternatorRange;
            Config::Triggerbot::R99Range = Features::Triggerbot::R99Range;
            Config::Triggerbot::R301Range = Features::Triggerbot::R301Range;
            Config::Triggerbot::SpitfireRange = Features::Triggerbot::SpitfireRange;
            Config::Triggerbot::G7Range = Features::Triggerbot::G7Range;
            Config::Triggerbot::FlatlineRange = Features::Triggerbot::FlatlineRange;
            Config::Triggerbot::HemlockRange = Features::Triggerbot::HemlockRange;
            Config::Triggerbot::ProwlerRange = Features::Triggerbot::ProwlerRange;
            Config::Triggerbot::RepeaterRange = Features::Triggerbot::RepeaterRange;
            Config::Triggerbot::RampageRange = Features::Triggerbot::RampageRange;
            Config::Triggerbot::CARSMGRange = Features::Triggerbot::CARSMGRange;
            Config::Triggerbot::HavocRange = Features::Triggerbot::HavocRange;
            Config::Triggerbot::DevotionRange = Features::Triggerbot::DevotionRange;
            Config::Triggerbot::LSTARRange = Features::Triggerbot::LSTARRange;
            Config::Triggerbot::TripleTakeRange = Features::Triggerbot::TripleTakeRange;
            Config::Triggerbot::VoltRange = Features::Triggerbot::VoltRange;
            Config::Triggerbot::NemesisRange = Features::Triggerbot::NemesisRange;
            Config::Triggerbot::LongbowRange = Features::Triggerbot::LongbowRange;
            Config::Triggerbot::ChargeRifleRange = Features::Triggerbot::ChargeRifleRange;
            Config::Triggerbot::SentinelRange = Features::Triggerbot::SentinelRange;
            Config::Triggerbot::MozambiqueRange = Features::Triggerbot::MozambiqueRange;
            Config::Triggerbot::PeacekeeperRange = Features::Triggerbot::PeacekeeperRange;
            Config::Triggerbot::MastiffRange = Features::Triggerbot::MastiffRange;
            Config::Triggerbot::LongbowRange = Features::Triggerbot::LongbowRange;
            Config::Triggerbot::ChargeRifleRange = Features::Triggerbot::ChargeRifleRange;
            Config::Triggerbot::SentinelRange = Features::Triggerbot::SentinelRange;
            Config::Triggerbot::WingmanRange = Features::Triggerbot::WingmanRange;
            Config::Triggerbot::EVA8Range = Features::Triggerbot::EVA8Range;
            Config::Triggerbot::KraberRange = Features::Triggerbot::KraberRange;
            Config::Triggerbot::BocekRange = Features::Triggerbot::BocekRange;
            Config::Triggerbot::ThrowingKnifeRange = Features::Triggerbot::ThrowingKnifeRange;

            return true;
        } catch (...) {
            return false;
        }
    }

    void UpdateWeaponList() {
        WeaponList.clear();
        // Define a lambda function to reduce repetition
        auto InsertIfEnabled = [&](const bool feature, const int weaponID) {
            if (feature)
                WeaponList.insert(weaponID);
        };
        // Light
        InsertIfEnabled(Features::Triggerbot::P2020, WeaponIDs::WEAPON_P2020);
        InsertIfEnabled(Features::Triggerbot::RE45, WeaponIDs::WEAPON_RE45);
        InsertIfEnabled(Features::Triggerbot::Alternator, WeaponIDs::WEAPON_ALTERNATOR);
        InsertIfEnabled(Features::Triggerbot::R99, WeaponIDs::WEAPON_R99);
        InsertIfEnabled(Features::Triggerbot::R301, WeaponIDs::WEAPON_R301);
        InsertIfEnabled(Features::Triggerbot::Spitfire, WeaponIDs::WEAPON_SPITFIRE);
        InsertIfEnabled(Features::Triggerbot::G7, WeaponIDs::WEAPON_G7);

        // Heavy
        InsertIfEnabled(Features::Triggerbot::Flatline, WeaponIDs::WEAPON_FLATLINE);
        InsertIfEnabled(Features::Triggerbot::Prowler, WeaponIDs::WEAPON_PROWLER);
        InsertIfEnabled(Features::Triggerbot::Hemlock, WeaponIDs::WEAPON_HEMLOCK);
        InsertIfEnabled(Features::Triggerbot::Repeater, WeaponIDs::WEAPON_REPEATER);
        InsertIfEnabled(Features::Triggerbot::Rampage, WeaponIDs::WEAPON_RAMPAGE);
        InsertIfEnabled(Features::Triggerbot::CARSMG, WeaponIDs::WEAPON_CAR);

        // Energy
        InsertIfEnabled(Features::Triggerbot::Havoc, WeaponIDs::WEAPON_HAVOC);
        InsertIfEnabled(Features::Triggerbot::Devotion, WeaponIDs::WEAPON_DEVOTION);
        InsertIfEnabled(Features::Triggerbot::LSTAR, WeaponIDs::WEAPON_LSTAR);
        InsertIfEnabled(Features::Triggerbot::TripleTake, WeaponIDs::WEAPON_TRIPLETAKE);
        InsertIfEnabled(Features::Triggerbot::Volt, WeaponIDs::WEAPON_VOLT);
        InsertIfEnabled(Features::Triggerbot::Nemesis, WeaponIDs::WEAPON_NEMESIS);

        // Shotguns
        InsertIfEnabled(Features::Triggerbot::Mozambique, WeaponIDs::WEAPON_MOZAMBIQUE);
        InsertIfEnabled(Features::Triggerbot::Peacekeeper, WeaponIDs::WEAPON_PEACEKEEPER);
        InsertIfEnabled(Features::Triggerbot::Mastiff, WeaponIDs::WEAPON_MASTIFF);

        // Snipers
        InsertIfEnabled(Features::Triggerbot::Longbow, WeaponIDs::WEAPON_LONGBOW);
        InsertIfEnabled(Features::Triggerbot::ChargeRifle, WeaponIDs::WEAPON_CHARGE_RIFLE);
        InsertIfEnabled(Features::Triggerbot::Sentinel, WeaponIDs::WEAPON_SENTINEL);

        // Legendary
        InsertIfEnabled(Features::Triggerbot::Wingman, WeaponIDs::WEAPON_WINGMAN);
        InsertIfEnabled(Features::Triggerbot::EVA8, WeaponIDs::WEAPON_EVA8);
        InsertIfEnabled(Features::Triggerbot::Bocek, WeaponIDs::WEAPON_BOCEK);
        InsertIfEnabled(Features::Triggerbot::Kraber, WeaponIDs::WEAPON_KRABER);
        InsertIfEnabled(Features::Triggerbot::Knife, WeaponIDs::WEAPON_KNIFE);
    }

    void Trigger() {
        if (Features::Triggerbot::AttackMethod == 0) { // Mouse
            X11Display->MouseClickLeft();
        }
    }

    void Update() {
        if (!Map->IsPlayable)
            return;
        if (Features::Home::IsMenuOpened)
            return;
        
        Features::Triggerbot::AttackMethod = 0; // Read Only!

        if (!Features::Triggerbot::Enabled)
            return;

        // Delay
        if (Features::Triggerbot::AttackMethod == 0) { // Mouse
            static std::chrono::time_point LastTimePoint = std::chrono::steady_clock::now();
            auto CurTimePoint = std::chrono::steady_clock::now();
            if (CurTimePoint - LastTimePoint <= std::chrono::milliseconds(Features::Triggerbot::Delay)) {
                return;
            } else {
                LastTimePoint = CurTimePoint;
                // Continue With Triggerbot
            }
        }

        UpdateTriggerbotSettings(); // Updates Triggerbot Settings - For Advanced And Non-Advanced Triggerbot

        // Triggerbot Start - Not a great way to do this...
        if (Features::Triggerbot::BindMethod == 0) { // Memory Bind Method
            // Always on - Will always shoot, ignores keybind
            if (!Features::Triggerbot::OnADS) {
                if (!Myself->IsCombatReady())
                    return;
                if (WeaponList.find(Myself->WeaponIndex) == WeaponList.end())
                    return;
                for (int i = 0; i < Players->size(); i++) {
                    Player* player = Players->at(i);
                    if (!player->IsCombatReady())
                        continue;
                    if (!player->IsHostile)
                        continue;
                    if (!player->IsAimedAt)
                        continue;
                    if (player->DistanceToLocalPlayer < Conversion::ToGameUnits(Range)) {
                        Trigger();
                        break;
                    }
                }
            }

            // Requires ADS
            if (Features::Triggerbot::OnADS && !Features::Triggerbot::HipfireShotguns) {
                if (WeaponList.find(Myself->WeaponIndex) == WeaponList.end())
                    return;
                if (!Myself->IsCombatReady())
                    return;
                if (!Myself->IsZooming)
                    return;
                for (int i = 0; i < Players->size(); i++) {
                    Player* player = Players->at(i);
                    if (!player->IsCombatReady())
                        continue;
                    if (!player->IsHostile)
                        continue;
                    if (!player->IsAimedAt)
                        continue;
                    if (player->DistanceToLocalPlayer < Conversion::ToGameUnits(Range)) {
                        Trigger();
                        break;
                    }
                }
            }

            if (Features::Triggerbot::OnADS && Features::Triggerbot::HipfireShotguns) {
                if (Myself->IsZooming) {
                    if (WeaponList.find(Myself->WeaponIndex) == WeaponList.end())
                        return;
                    for (int i = 0; i < Players->size(); i++) {
                        Player* player = Players->at(i);
                        if (!player->IsCombatReady())
                            continue;
                        if (!player->IsHostile)
                            continue;
                        if (!player->IsAimedAt)
                            continue;
                        if (player->DistanceToLocalPlayer < Conversion::ToGameUnits(Range)) {
                            Trigger();
                            break;
                        }
                    }
                }

                if (!Myself->IsZooming) {
                    if (Myself->WeaponIndex == WeaponIDs::WEAPON_MOZAMBIQUE or Myself->WeaponIndex == WeaponIDs::WEAPON_EVA8 or Myself->WeaponIndex == WeaponIDs::WEAPON_PEACEKEEPER or Myself->WeaponIndex == WeaponIDs::WEAPON_MASTIFF) { // Shotgun IDs
                        for (int i = 0; i < Players->size(); i++) {
                            Player* player = Players->at(i);
                            if (!player->IsCombatReady())
                                continue;
                            if (!player->IsHostile)
                                continue;
                            if (!player->IsAimedAt)
                                continue;
                            if (player->DistanceToLocalPlayer < Conversion::ToGameUnits(Range)) {
                                Trigger();
                                break;
                            }
                        }
                    }
                }
            }
        }

        if (Features::Triggerbot::BindMethod == 1) {
            // Keybind Method

            if (!IsKeybindDown())
                return;

            if (!Myself->IsCombatReady())
                return;

            if (WeaponList.find(Myself->WeaponIndex) == WeaponList.end())
                return;

            for (int i = 0; i < Players->size(); i++) {
                Player* player = Players->at(i);
                if (!player->IsCombatReady())
                    continue;
                if (!player->IsHostile)
                    continue;
                if (!player->IsAimedAt)
                    continue;
                if (player->DistanceToLocalPlayer < Conversion::ToGameUnits(Range)) {
                    Trigger();
                    break;
                }
            }
        }
    }

    bool IsKeybindDown() {
        bool ActivatedByBind = InputManager::isKeyDownOrPress(Features::Triggerbot::TriggerBind);
        bool Active = ActivatedByBind;
        return Active;
    }

    void UpdateTriggerbotSettings() {
        if (!Features::Triggerbot::AdvancedTriggerbot) {
            Range = Features::Triggerbot::Range;
        }

        if (Features::Triggerbot::AdvancedTriggerbot) {
            if (Features::Triggerbot::P2020 && Myself->WeaponIndex == WeaponIDs::WEAPON_P2020) {
                Range = Features::Triggerbot::P2020Range;
            }

            if (Features::Triggerbot::RE45 && Myself->WeaponIndex == WeaponIDs::WEAPON_RE45) {
                Range = Features::Triggerbot::RE45Range;
            }

            if (Features::Triggerbot::Alternator && Myself->WeaponIndex == WeaponIDs::WEAPON_ALTERNATOR) {
                Range = Features::Triggerbot::AlternatorRange;
            }

            if (Features::Triggerbot::R99 && Myself->WeaponIndex == WeaponIDs::WEAPON_R99) {
                Range = Features::Triggerbot::R99Range;
            }

            if (Features::Triggerbot::R301 && Myself->WeaponIndex == WeaponIDs::WEAPON_R301) {
                Range = Features::Triggerbot::R301Range;
            }

            if (Features::Triggerbot::Spitfire && Myself->WeaponIndex == WeaponIDs::WEAPON_SPITFIRE) {
                Range = Features::Triggerbot::SpitfireRange;
            }

            if (Features::Triggerbot::G7 && Myself->WeaponIndex == WeaponIDs::WEAPON_G7) {
                Range = Features::Triggerbot::G7Range;
            }

            if (Features::Triggerbot::Flatline && Myself->WeaponIndex == WeaponIDs::WEAPON_FLATLINE) {
                Range = Features::Triggerbot::FlatlineRange;
            }

            if (Features::Triggerbot::Prowler && Myself->WeaponIndex == WeaponIDs::WEAPON_PROWLER) {
                Range = Features::Triggerbot::ProwlerRange;
            }

            if (Features::Triggerbot::Hemlock && Myself->WeaponIndex == WeaponIDs::WEAPON_HEMLOCK) {
                Range = Features::Triggerbot::HemlockRange;
            }

            if (Features::Triggerbot::Repeater && Myself->WeaponIndex == WeaponIDs::WEAPON_REPEATER) {
                Range = Features::Triggerbot::RepeaterRange;
            }

            if (Features::Triggerbot::Rampage && Myself->WeaponIndex == WeaponIDs::WEAPON_RAMPAGE) {
                Range = Features::Triggerbot::RampageRange;
            }

            if (Features::Triggerbot::CARSMG && Myself->WeaponIndex == WeaponIDs::WEAPON_CAR) {
                Range = Features::Triggerbot::CARSMGRange;
            }

            if (Features::Triggerbot::Havoc && Myself->WeaponIndex == WeaponIDs::WEAPON_HAVOC) {
                Range = Features::Triggerbot::HavocRange;
            }

            if (Features::Triggerbot::Devotion && Myself->WeaponIndex == WeaponIDs::WEAPON_DEVOTION) {
                Range = Features::Triggerbot::DevotionRange;
            }

            if (Features::Triggerbot::LSTAR && Myself->WeaponIndex == WeaponIDs::WEAPON_LSTAR) {
                Range = Features::Triggerbot::LSTARRange;
            }

            if (Features::Triggerbot::TripleTake && Myself->WeaponIndex == WeaponIDs::WEAPON_TRIPLETAKE) {
                Range = Features::Triggerbot::TripleTakeRange;
            }

            if (Features::Triggerbot::Volt && Myself->WeaponIndex == WeaponIDs::WEAPON_VOLT) {
                Range = Features::Triggerbot::VoltRange;
            }

            if (Features::Triggerbot::Nemesis && Myself->WeaponIndex == WeaponIDs::WEAPON_NEMESIS) {
                Range = Features::Triggerbot::NemesisRange;
            }

            if (Features::Triggerbot::Mozambique && Myself->WeaponIndex == WeaponIDs::WEAPON_MOZAMBIQUE) {
                Range = Features::Triggerbot::MozambiqueRange;
            }

            if (Features::Triggerbot::Peacekeeper && Myself->WeaponIndex == WeaponIDs::WEAPON_PEACEKEEPER) {
                Range = Features::Triggerbot::PeacekeeperRange;
            }

            if (Features::Triggerbot::Mastiff && Myself->WeaponIndex == WeaponIDs::WEAPON_MASTIFF) {
                Range = Features::Triggerbot::MastiffRange;
            }

            if (Features::Triggerbot::Longbow && Myself->WeaponIndex == WeaponIDs::WEAPON_LONGBOW) {
                Range = Features::Triggerbot::LongbowRange;
            }

            if (Features::Triggerbot::ChargeRifle && Myself->WeaponIndex == WeaponIDs::WEAPON_CHARGE_RIFLE) {
                Range = Features::Triggerbot::ChargeRifleRange;
            }

            if (Features::Triggerbot::Sentinel && Myself->WeaponIndex == WeaponIDs::WEAPON_SENTINEL) {
                Range = Features::Triggerbot::SentinelRange;
            }

            if (Features::Triggerbot::Wingman && Myself->WeaponIndex == WeaponIDs::WEAPON_WINGMAN) {
                Range = Features::Triggerbot::WingmanRange;
            }

            if (Features::Triggerbot::EVA8 && Myself->WeaponIndex == WeaponIDs::WEAPON_EVA8) {
                Range = Features::Triggerbot::EVA8Range;
            }

            if (Features::Triggerbot::Bocek && Myself->WeaponIndex == WeaponIDs::WEAPON_BOCEK) {
                Range = Features::Triggerbot::BocekRange;
            }

            if (Features::Triggerbot::Kraber && Myself->WeaponIndex == WeaponIDs::WEAPON_KRABER) {
                Range = Features::Triggerbot::KraberRange;
            }

            if (Features::Triggerbot::Knife && Myself->WeaponIndex == WeaponIDs::WEAPON_KNIFE) {
                Range = Features::Triggerbot::ThrowingKnifeRange;
            }
        }
    }
};