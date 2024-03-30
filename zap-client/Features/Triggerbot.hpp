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

    XDisplay *X11Display;
    LocalPlayer *Myself;
    std::vector<Player *> *Players;
    Level *Map;

    Triggerbot(XDisplay *X11Display, Level *Map, LocalPlayer *Myself, std::vector<Player *> *GamePlayers)
    {
        this->X11Display = X11Display;
        this->Map = Map;
        this->Myself = Myself;
        this->Players = GamePlayers;
    }

    bool Save()
    {
        try
        {
            
            Config::Triggerbot::Enabled = Features::Triggerbot::Enabled;
            Config::Triggerbot::BindMethod = Features::Triggerbot::BindMethod;
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
        }
        catch (...)
        {
            return false;
        }
    }

    void UpdateWeaponList()
    {
        WeaponList.clear();
        // Light
        if (Features::Triggerbot::P2020)
            WeaponList.insert(WeaponIDs::WEAPON_P2020);
        if (Features::Triggerbot::RE45)
            WeaponList.insert(WeaponIDs::WEAPON_RE45);
        if (Features::Triggerbot::Alternator)
            WeaponList.insert(WeaponIDs::WEAPON_ALTERNATOR);
        if (Features::Triggerbot::R99)
            WeaponList.insert(WeaponIDs::WEAPON_R99);
        if (Features::Triggerbot::R301)
            WeaponList.insert(WeaponIDs::WEAPON_R301);
        if (Features::Triggerbot::Spitfire)
            WeaponList.insert(WeaponIDs::WEAPON_SPITFIRE);
        if (Features::Triggerbot::G7)
            WeaponList.insert(WeaponIDs::WEAPON_G7);
        // Heavy
        if (Features::Triggerbot::Flatline)
            WeaponList.insert(WeaponIDs::WEAPON_FLATLINE);
        if (Features::Triggerbot::Hemlock)
            WeaponList.insert(WeaponIDs::WEAPON_HEMLOCK);
        if (Features::Triggerbot::Repeater)
            WeaponList.insert(WeaponIDs::WEAPON_REPEATER);
        if (Features::Triggerbot::Rampage)
            WeaponList.insert(WeaponIDs::WEAPON_RAMPAGE);
        if (Features::Triggerbot::CARSMG)
            WeaponList.insert(WeaponIDs::WEAPON_CAR);
        // Energy
        if (Features::Triggerbot::Havoc)
            WeaponList.insert(WeaponIDs::WEAPON_HAVOC);
        if (Features::Triggerbot::Devotion)
            WeaponList.insert(WeaponIDs::WEAPON_DEVOTION);
        if (Features::Triggerbot::LSTAR)
            WeaponList.insert(WeaponIDs::WEAPON_LSTAR);
        if (Features::Triggerbot::TripleTake)
            WeaponList.insert(WeaponIDs::WEAPON_TRIPLETAKE);
        if (Features::Triggerbot::Volt)
            WeaponList.insert(WeaponIDs::WEAPON_VOLT);
        if (Features::Triggerbot::Nemesis)
            WeaponList.insert(WeaponIDs::WEAPON_NEMESIS);
        // Shotguns
        if (Features::Triggerbot::Mozambique)
            WeaponList.insert(WeaponIDs::WEAPON_MOZAMBIQUE);
        if (Features::Triggerbot::EVA8)
            WeaponList.insert(WeaponIDs::WEAPON_EVA8);
        if (Features::Triggerbot::Peacekeeper)
            WeaponList.insert(WeaponIDs::WEAPON_PEACEKEEPER);
        if (Features::Triggerbot::Mastiff)
            WeaponList.insert(WeaponIDs::WEAPON_MASTIFF);
        // Snipers
        if (Features::Triggerbot::Longbow)
            WeaponList.insert(WeaponIDs::WEAPON_LONGBOW);
        if (Features::Triggerbot::ChargeRifle)
            WeaponList.insert(WeaponIDs::WEAPON_CHARGE_RIFLE);
        if (Features::Triggerbot::Sentinel)
            WeaponList.insert(WeaponIDs::WEAPON_SENTINEL);
        // Legendary
        if (Features::Triggerbot::Wingman)
            WeaponList.insert(WeaponIDs::WEAPON_WINGMAN);
        if (Features::Triggerbot::Prowler)
            WeaponList.insert(WeaponIDs::WEAPON_PROWLER);
        if (Features::Triggerbot::Bocek)
            WeaponList.insert(WeaponIDs::WEAPON_BOCEK);
        if (Features::Triggerbot::Kraber)
            WeaponList.insert(WeaponIDs::WEAPON_KRABER);
        if (Features::Triggerbot::Knife)
            WeaponList.insert(WeaponIDs::WEAPON_KNIFE);
    }

    void Update()
    {
        if (!Map->IsPlayable)
            return;
        if (Features::Home::IsMenuOpened)
            return;

        if (!Features::Triggerbot::Enabled)
            return;

        UpdateTriggerbotSettings(); // Updates Triggerbot Settings - For Advanced And Non-Advanced Triggerbot

        // Triggerbot Start - Not a great way to do this but oh well
        if (Features::Triggerbot::BindMethod == 0)
        {
            // Memory Bind Method
            //  Always on - Will always shoot, ignores keybind
            if (!Features::Triggerbot::OnADS)
            {
                if (!Myself->IsCombatReady())
                    return;

                if (WeaponList.find(Myself->WeaponIndex) == WeaponList.end())
                    return;

                for (int i = 0; i < Players->size(); i++)
                {
                    Player *player = Players->at(i);
                    if (!player->IsCombatReady())
                        continue;
                    if (!player->IsHostile)
                        continue;
                    if (!player->IsAimedAt)
                        continue;
                    if (player->DistanceToLocalPlayer < Conversion::ToGameUnits(Range))
                    {
                        X11Display->MouseClickLeft();
                        break;
                    }
                }
            }

            // Requires ADS
            if (Features::Triggerbot::OnADS && !Features::Triggerbot::HipfireShotguns)
            {
                if (WeaponList.find(Myself->WeaponIndex) == WeaponList.end())
                    return;
                if (!Myself->IsCombatReady())
                    return;
                if (!Myself->IsZooming)
                    return;
                for (int i = 0; i < Players->size(); i++)
                {
                    Player *player = Players->at(i);
                    if (!player->IsCombatReady())
                        continue;
                    if (!player->IsHostile)
                        continue;
                    if (!player->IsAimedAt)
                        continue;

                    if (player->DistanceToLocalPlayer < Conversion::ToGameUnits(Range))
                    {
                        X11Display->MouseClickLeft();
                        break;
                    }
                }
            }

            if (Features::Triggerbot::OnADS && Features::Triggerbot::HipfireShotguns)
            {
                if (Myself->IsZooming)
                {
                    if (WeaponList.find(Myself->WeaponIndex) == WeaponList.end())
                        return;
                    for (int i = 0; i < Players->size(); i++)
                    {
                        Player *player = Players->at(i);
                        if (!player->IsCombatReady())
                            continue;
                        if (!player->IsHostile)
                            continue;
                        if (!player->IsAimedAt)
                            continue;
                        if (player->DistanceToLocalPlayer < Conversion::ToGameUnits(Range))
                        {
                            X11Display->MouseClickLeft();
                            break;
                        }
                    }
                }

                if (!Myself->IsZooming)
                {
                    if (Myself->WeaponIndex == WeaponIDs::WEAPON_MOZAMBIQUE or Myself->WeaponIndex == WeaponIDs::WEAPON_EVA8 or Myself->WeaponIndex == WeaponIDs::WEAPON_PEACEKEEPER or Myself->WeaponIndex == WeaponIDs::WEAPON_MASTIFF)
                    { // Shotgun IDs

                        for (int i = 0; i < Players->size(); i++)
                        {
                            Player *player = Players->at(i);
                            if (!player->IsCombatReady())
                                continue;
                            if (!player->IsHostile)
                                continue;
                            if (!player->IsAimedAt)
                                continue;
                            if (player->DistanceToLocalPlayer < Conversion::ToGameUnits(Range))
                            {
                                X11Display->MouseClickLeft();
                                break;
                            }
                        }
                    }
                }
            }
        }

        if (Features::Triggerbot::BindMethod == 1)
        {
            // Keybind Method

            if (!IsKeybindDown())
                return;

            if (!Myself->IsCombatReady())
                return;

            if (WeaponList.find(Myself->WeaponIndex) == WeaponList.end())
                return;

            for (int i = 0; i < Players->size(); i++)
            {
                Player *player = Players->at(i);
                if (!player->IsCombatReady())
                    continue;
                if (!player->IsHostile)
                    continue;
                if (!player->IsAimedAt)
                    continue;
                if (player->DistanceToLocalPlayer < Conversion::ToGameUnits(Range))
                {
                    X11Display->MouseClickLeft();
                    break;
                }
            }
        }
    }
    
    bool IsKeybindDown()
    {
        bool ActivatedByBind = InputManager::isKeyDownOrPress(Features::Triggerbot::TriggerBind);
        bool Active = ActivatedByBind;
        return Active;
    }

    void UpdateTriggerbotSettings()
    {
        if (!Features::Triggerbot::AdvancedTriggerbot)
        {
            Range = Features::Triggerbot::Range;
        }

        if (Features::Triggerbot::AdvancedTriggerbot)
        {
            if (Features::Triggerbot::P2020 && Myself->WeaponIndex == WeaponIDs::WEAPON_P2020)
            {
                Range = Features::Triggerbot::P2020Range;
            }

            if (Features::Triggerbot::RE45 && Myself->WeaponIndex == WeaponIDs::WEAPON_RE45)
            {
                Range = Features::Triggerbot::RE45Range;
            }

            if (Features::Triggerbot::Alternator && Myself->WeaponIndex == WeaponIDs::WEAPON_ALTERNATOR)
            {
                Range = Features::Triggerbot::AlternatorRange;
            }

            if (Features::Triggerbot::R99 && Myself->WeaponIndex == WeaponIDs::WEAPON_R99)
            {
                Range = Features::Triggerbot::R99Range;
            }

            if (Features::Triggerbot::R301 && Myself->WeaponIndex == WeaponIDs::WEAPON_R301)
            {
                Range = Features::Triggerbot::R301Range;
            }

            if (Features::Triggerbot::Spitfire && Myself->WeaponIndex == WeaponIDs::WEAPON_SPITFIRE)
            {
                Range = Features::Triggerbot::SpitfireRange;
            }

            if (Features::Triggerbot::G7 && Myself->WeaponIndex == WeaponIDs::WEAPON_G7)
            {
                Range = Features::Triggerbot::G7Range;
            }

            if (Features::Triggerbot::Flatline && Myself->WeaponIndex == WeaponIDs::WEAPON_FLATLINE)
            {
                Range = Features::Triggerbot::FlatlineRange;
            }

            if (Features::Triggerbot::Prowler && Myself->WeaponIndex == WeaponIDs::WEAPON_PROWLER)
            {
                Range = Features::Triggerbot::ProwlerRange;
            }

            if (Features::Triggerbot::Hemlock && Myself->WeaponIndex == WeaponIDs::WEAPON_HEMLOCK)
            {
                Range = Features::Triggerbot::HemlockRange;
            }

            if (Features::Triggerbot::Repeater && Myself->WeaponIndex == WeaponIDs::WEAPON_REPEATER)
            {
                Range = Features::Triggerbot::RepeaterRange;
            }

            if (Features::Triggerbot::Rampage && Myself->WeaponIndex == WeaponIDs::WEAPON_RAMPAGE)
            {
                Range = Features::Triggerbot::RampageRange;
            }

            if (Features::Triggerbot::CARSMG && Myself->WeaponIndex == WeaponIDs::WEAPON_CAR)
            {
                Range = Features::Triggerbot::CARSMGRange;
            }

            if (Features::Triggerbot::Havoc && Myself->WeaponIndex == WeaponIDs::WEAPON_HAVOC)
            {
                Range = Features::Triggerbot::HavocRange;
            }

            if (Features::Triggerbot::Devotion && Myself->WeaponIndex == WeaponIDs::WEAPON_DEVOTION)
            {
                Range = Features::Triggerbot::DevotionRange;
            }

            if (Features::Triggerbot::LSTAR && Myself->WeaponIndex == WeaponIDs::WEAPON_LSTAR)
            {
                Range = Features::Triggerbot::LSTARRange;
            }

            if (Features::Triggerbot::TripleTake && Myself->WeaponIndex == WeaponIDs::WEAPON_TRIPLETAKE)
            {
                Range = Features::Triggerbot::TripleTakeRange;
            }

            if (Features::Triggerbot::Volt && Myself->WeaponIndex == WeaponIDs::WEAPON_VOLT)
            {
                Range = Features::Triggerbot::VoltRange;
            }

            if (Features::Triggerbot::Nemesis && Myself->WeaponIndex == WeaponIDs::WEAPON_NEMESIS)
            {
                Range = Features::Triggerbot::NemesisRange;
            }

            if (Features::Triggerbot::Mozambique && Myself->WeaponIndex == WeaponIDs::WEAPON_MOZAMBIQUE)
            {
                Range = Features::Triggerbot::MozambiqueRange;
            }

            if (Features::Triggerbot::Peacekeeper && Myself->WeaponIndex == WeaponIDs::WEAPON_PEACEKEEPER)
            {
                Range = Features::Triggerbot::PeacekeeperRange;
            }

            if (Features::Triggerbot::Mastiff && Myself->WeaponIndex == WeaponIDs::WEAPON_MASTIFF)
            {
                Range = Features::Triggerbot::MastiffRange;
            }

            if (Features::Triggerbot::Longbow && Myself->WeaponIndex == WeaponIDs::WEAPON_LONGBOW)
            {
                Range = Features::Triggerbot::LongbowRange;
            }

            if (Features::Triggerbot::ChargeRifle && Myself->WeaponIndex == WeaponIDs::WEAPON_CHARGE_RIFLE)
            {
                Range = Features::Triggerbot::ChargeRifleRange;
            }

            if (Features::Triggerbot::Sentinel && Myself->WeaponIndex == WeaponIDs::WEAPON_SENTINEL)
            {
                Range = Features::Triggerbot::SentinelRange;
            }

            if (Features::Triggerbot::Wingman && Myself->WeaponIndex == WeaponIDs::WEAPON_WINGMAN)
            {
                Range = Features::Triggerbot::WingmanRange;
            }

            if (Features::Triggerbot::EVA8 && Myself->WeaponIndex == WeaponIDs::WEAPON_EVA8)
            {
                Range = Features::Triggerbot::EVA8Range;
            }

            if (Features::Triggerbot::Bocek && Myself->WeaponIndex == WeaponIDs::WEAPON_BOCEK)
            {
                Range = Features::Triggerbot::BocekRange;
            }

            if (Features::Triggerbot::Kraber && Myself->WeaponIndex == WeaponIDs::WEAPON_KRABER)
            {
                Range = Features::Triggerbot::KraberRange;
            }

            if (Features::Triggerbot::Knife && Myself->WeaponIndex == WeaponIDs::WEAPON_KNIFE)
            {
                Range = Features::Triggerbot::ThrowingKnifeRange;
            }
        }
    }
};
