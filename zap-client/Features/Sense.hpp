#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include "../Core/Player.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"
#include "../Core/GlowMode.hpp"
#include "../Core/Camera.hpp"
#include "../Core/Level.hpp"

#include "../Features/Legitbot.hpp"

#include "../Overlay/Overlay.hpp"
#include "../Overlay/Renderer.hpp"

#include "../Utils/Memory.hpp"
#include "../Utils/Color.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/HitboxType.hpp"
#include "../Utils/XDisplay.hpp"
#include "../Utils/InputManager.hpp"
#include "../Utils/InputTypes.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

// Geometry
#define DEG2RAD(x) ((float)(x) * (float)(M_PI / 180.f))
#define ABS(x) ((x < 0) ? (-x) : (x))

struct Sense
{
	// Variables
	XDisplay *X11Display;
	Camera *GameCamera;
	LocalPlayer *Myself;
	std::vector<Player *> *Players;
	std::chrono::milliseconds LastUpdateTime;
	int TotalSpectators = 0;
	int PlayersNear = 0;
	std::vector<std::string> Spectators;
	Level *Map;

	Sense(Level *Map, std::vector<Player *> *Players, Camera *GameCamera, LocalPlayer *Myself, XDisplay *X11Display)
	{
		this->Players = Players;
		this->GameCamera = GameCamera;
		this->Map = Map;
		this->Myself = Myself;
		this->X11Display = X11Display;
	}

	bool Save()
	{
		try
		{

			Config::Sense::Enabled = Features::Sense::Enabled;
			Config::Sense::DrawFOVCircle = Features::Sense::DrawFOVCircle;
			Config::Sense::DrawFilledFOVCircle = Features::Sense::DrawFilledFOVCircle;
			Config::Sense::FOVThickness = Features::Sense::FOVThickness;
			Config::Sense::GameFOV = Features::Sense::GameFOV;
			Config::Sense::DrawCrosshair = Features::Sense::DrawCrosshair;
			Config::Sense::CrosshairSize = Features::Sense::CrosshairSize;
			Config::Sense::CrosshairThickness = Features::Sense::CrosshairThickness;
			Config::Sense::ShowSpectators = Features::Sense::ShowSpectators;
			Config::Sense::DrawSpectatorWarning = Features::Sense::DrawSpectatorWarning;
			Config::Sense::DrawVisibleWarning = Features::Sense::DrawVisibleWarning;
			Config::Sense::WarningTextOutline = Features::Sense::WarningTextOutline;
			Config::Sense::WarningTextX = Features::Sense::WarningTextX;
			Config::Sense::WarningTextY = Features::Sense::WarningTextY;
			Config::Sense::TextOutline = Features::Sense::TextOutline;
			Config::Sense::VisibilityCheck = Features::Sense::VisibilityCheck;
			Config::Sense::ESPMaxDistance = Features::Sense::ESPMaxDistance;

			Config::SenseEnemy::DrawEnemy = Features::Sense::Enemy::DrawEnemy;
			Config::SenseEnemy::DrawBoxes = Features::Sense::Enemy::DrawBoxes;
			Config::SenseEnemy::BoxType = Features::Sense::Enemy::BoxType;
			Config::SenseEnemy::BoxStyle = Features::Sense::Enemy::BoxStyle;
			Config::SenseEnemy::BoxThickness = Features::Sense::Enemy::BoxThickness;
			Config::SenseEnemy::DrawSkeleton = Features::Sense::Enemy::DrawSkeleton;
			Config::SenseEnemy::SkeletonThickness = Features::Sense::Enemy::SkeletonThickness;
			Config::SenseEnemy::DrawHeadCircle = Features::Sense::Enemy::DrawHeadCircle;
			Config::SenseEnemy::HeadCircleThickness = Features::Sense::Enemy::HeadCircleThickness;
			Config::SenseEnemy::DrawBars = Features::Sense::Enemy::DrawBars;
			Config::SenseEnemy::HealthBar = Features::Sense::Enemy::HealthBar;
			Config::SenseEnemy::ShieldBar = Features::Sense::Enemy::ShieldBar;
			Config::SenseEnemy::BarMode = Features::Sense::Enemy::BarMode;
			Config::SenseEnemy::BarStyle = Features::Sense::Enemy::BarStyle;
			Config::SenseEnemy::BarThickness = Features::Sense::Enemy::BarThickness;
			Config::SenseEnemy::BarThickness2 = Features::Sense::Enemy::BarThickness2;
			Config::SenseEnemy::BarHeight = Features::Sense::Enemy::BarHeight;
			Config::SenseEnemy::BarWidth = Features::Sense::Enemy::BarWidth;
			Config::SenseEnemy::BarColorMode = Features::Sense::Enemy::BarColorMode;
			Config::SenseEnemy::WeaponColorType = Features::Sense::Enemy::WeaponColorType;
			Config::SenseEnemy::DrawDistance = Features::Sense::Enemy::DrawDistance;
			Config::SenseEnemy::TracerPosition = Features::Sense::Enemy::TracerPosition;
			Config::SenseEnemy::TracerBone = Features::Sense::Enemy::TracerBone;
			Config::SenseEnemy::DrawTracers = Features::Sense::Enemy::DrawTracers;
			Config::SenseEnemy::TracerThickness = Features::Sense::Enemy::TracerThickness;
			Config::SenseEnemy::DrawNames = Features::Sense::Enemy::DrawNames;
			Config::SenseEnemy::DrawSeer = Features::Sense::Enemy::DrawSeer;
			Config::SenseEnemy::DrawStatus = Features::Sense::Enemy::DrawStatus;
			Config::SenseEnemy::ShowMaxStatusValues = Features::Sense::Enemy::ShowMaxStatusValues;
			Config::SenseEnemy::DrawWeapon = Features::Sense::Enemy::DrawWeapon;
			Config::SenseEnemy::DrawLegend = Features::Sense::Enemy::DrawLegend;

			Config::SenseTeammate::DrawTeam = Features::Sense::Teammate::DrawTeam;
			Config::SenseTeammate::DrawBoxes = Features::Sense::Teammate::DrawBoxes;
			Config::SenseTeammate::BoxType = Features::Sense::Teammate::BoxType;
			Config::SenseTeammate::BoxStyle = Features::Sense::Teammate::BoxStyle;
			Config::SenseTeammate::BoxThickness = Features::Sense::Teammate::BoxThickness;
			Config::SenseTeammate::DrawSkeleton = Features::Sense::Teammate::DrawSkeleton;
			Config::SenseTeammate::SkeletonThickness = Features::Sense::Teammate::SkeletonThickness;
			Config::SenseTeammate::DrawHeadCircle = Features::Sense::Teammate::DrawHeadCircle;
			Config::SenseTeammate::HeadCircleThickness = Features::Sense::Teammate::HeadCircleThickness;
			Config::SenseTeammate::DrawBars = Features::Sense::Teammate::DrawBars;
			Config::SenseTeammate::HealthBar = Features::Sense::Teammate::HealthBar;
			Config::SenseTeammate::ShieldBar = Features::Sense::Teammate::ShieldBar;
			Config::SenseTeammate::BarMode = Features::Sense::Teammate::BarMode;
			Config::SenseTeammate::BarStyle = Features::Sense::Teammate::BarStyle;
			Config::SenseTeammate::BarThickness = Features::Sense::Teammate::BarThickness;
			Config::SenseTeammate::BarThickness2 = Features::Sense::Teammate::BarThickness2;
			Config::SenseTeammate::BarHeight = Features::Sense::Teammate::BarHeight;
			Config::SenseTeammate::BarWidth = Features::Sense::Teammate::BarWidth;
			Config::SenseTeammate::BarColorMode = Features::Sense::Teammate::BarColorMode;
			Config::SenseTeammate::WeaponColorType = Features::Sense::Teammate::WeaponColorType;
			Config::SenseTeammate::DrawDistance = Features::Sense::Teammate::DrawDistance;
			Config::SenseTeammate::TracerPosition = Features::Sense::Teammate::TracerPosition;
			Config::SenseTeammate::TracerBone = Features::Sense::Teammate::TracerBone;
			Config::SenseTeammate::DrawTracers = Features::Sense::Teammate::DrawTracers;
			Config::SenseTeammate::TracerThickness = Features::Sense::Teammate::TracerThickness;
			Config::SenseTeammate::DrawNames = Features::Sense::Teammate::DrawNames;
			Config::SenseTeammate::DrawSeer = Features::Sense::Teammate::DrawSeer;
			Config::SenseTeammate::DrawStatus = Features::Sense::Teammate::DrawStatus;
			Config::SenseTeammate::ShowMaxStatusValues = Features::Sense::Teammate::ShowMaxStatusValues;
			Config::SenseTeammate::DrawWeapon = Features::Sense::Teammate::DrawWeapon;
			Config::SenseTeammate::DrawLegend = Features::Sense::Teammate::DrawLegend;


			Config::SensePositions::NamePosition = Features::Sense::Positions::NamePosition;
			Config::SensePositions::DistancePosition = Features::Sense::Positions::DistancePosition;
			Config::SensePositions::LegendPosition = Features::Sense::Positions::LegendPosition;
			Config::SensePositions::WeaponPosition = Features::Sense::Positions::WeaponPosition;
			Config::SensePositions::StatusPosition = Features::Sense::Positions::StatusPosition;

			// Colors
			Config::SenseEnemy::WeaponColorType = Features::Sense::Enemy::WeaponColorType;
			Config::EnemyColors::InvisibleBoxColorR = Features::Colors::Enemy::InvisibleBoxColor[0];
			Config::EnemyColors::InvisibleBoxColorG = Features::Colors::Enemy::InvisibleBoxColor[1];
			Config::EnemyColors::InvisibleBoxColorB = Features::Colors::Enemy::InvisibleBoxColor[2];
			Config::EnemyColors::InvisibleBoxColorA = Features::Colors::Enemy::InvisibleBoxColor[3];
			Config::EnemyColors::VisibleBoxColorR = Features::Colors::Enemy::VisibleBoxColor[0];
			Config::EnemyColors::VisibleBoxColorG = Features::Colors::Enemy::VisibleBoxColor[1];
			Config::EnemyColors::VisibleBoxColorB = Features::Colors::Enemy::VisibleBoxColor[2];
			Config::EnemyColors::VisibleBoxColorA = Features::Colors::Enemy::VisibleBoxColor[3];
			Config::EnemyColors::InvisibleFilledBoxColorR = Features::Colors::Enemy::InvisibleFilledBoxColor[0];
			Config::EnemyColors::InvisibleFilledBoxColorG = Features::Colors::Enemy::InvisibleFilledBoxColor[1];
			Config::EnemyColors::InvisibleFilledBoxColorB = Features::Colors::Enemy::InvisibleFilledBoxColor[2];
			Config::EnemyColors::InvisibleFilledBoxColorA = Features::Colors::Enemy::InvisibleFilledBoxColor[3];
			Config::EnemyColors::VisibleFilledBoxColorR = Features::Colors::Enemy::VisibleFilledBoxColor[0];
			Config::EnemyColors::VisibleFilledBoxColorG = Features::Colors::Enemy::VisibleFilledBoxColor[1];
			Config::EnemyColors::VisibleFilledBoxColorB = Features::Colors::Enemy::VisibleFilledBoxColor[2];
			Config::EnemyColors::VisibleFilledBoxColorA = Features::Colors::Enemy::VisibleFilledBoxColor[3];
			Config::EnemyColors::InvisibleTracerColorR = Features::Colors::Enemy::InvisibleTracerColor[0];
			Config::EnemyColors::InvisibleTracerColorG = Features::Colors::Enemy::InvisibleTracerColor[1];
			Config::EnemyColors::InvisibleTracerColorB = Features::Colors::Enemy::InvisibleTracerColor[2];
			Config::EnemyColors::InvisibleTracerColorA = Features::Colors::Enemy::InvisibleTracerColor[3];
			Config::EnemyColors::VisibleTracerColorR = Features::Colors::Enemy::VisibleTracerColor[0];
			Config::EnemyColors::VisibleTracerColorG = Features::Colors::Enemy::VisibleTracerColor[1];
			Config::EnemyColors::VisibleTracerColorB = Features::Colors::Enemy::VisibleTracerColor[2];
			Config::EnemyColors::VisibleTracerColorA = Features::Colors::Enemy::VisibleTracerColor[3];
			Config::EnemyColors::InvisibleSkeletonColorR = Features::Colors::Enemy::InvisibleSkeletonColor[0];
			Config::EnemyColors::InvisibleSkeletonColorG = Features::Colors::Enemy::InvisibleSkeletonColor[1];
			Config::EnemyColors::InvisibleSkeletonColorB = Features::Colors::Enemy::InvisibleSkeletonColor[2];
			Config::EnemyColors::InvisibleSkeletonColorA = Features::Colors::Enemy::InvisibleSkeletonColor[3];
			Config::EnemyColors::VisibleSkeletonColorR = Features::Colors::Enemy::VisibleSkeletonColor[0];
			Config::EnemyColors::VisibleSkeletonColorG = Features::Colors::Enemy::VisibleSkeletonColor[1];
			Config::EnemyColors::VisibleSkeletonColorB = Features::Colors::Enemy::VisibleSkeletonColor[2];
			Config::EnemyColors::VisibleSkeletonColorA = Features::Colors::Enemy::VisibleSkeletonColor[3];
			Config::EnemyColors::InvisibleNameColorR = Features::Colors::Enemy::InvisibleNameColor[0];
			Config::EnemyColors::InvisibleNameColorG = Features::Colors::Enemy::InvisibleNameColor[1];
			Config::EnemyColors::InvisibleNameColorB = Features::Colors::Enemy::InvisibleNameColor[2];
			Config::EnemyColors::InvisibleNameColorA = Features::Colors::Enemy::InvisibleNameColor[3];
			Config::EnemyColors::VisibleNameColorR = Features::Colors::Enemy::VisibleNameColor[0];
			Config::EnemyColors::VisibleNameColorG = Features::Colors::Enemy::VisibleNameColor[1];
			Config::EnemyColors::VisibleNameColorB = Features::Colors::Enemy::VisibleNameColor[2];
			Config::EnemyColors::VisibleNameColorA = Features::Colors::Enemy::VisibleNameColor[3];
			Config::EnemyColors::InvisibleDistanceColorR = Features::Colors::Enemy::InvisibleDistanceColor[0];
			Config::EnemyColors::InvisibleDistanceColorG = Features::Colors::Enemy::InvisibleDistanceColor[1];
			Config::EnemyColors::InvisibleDistanceColorB = Features::Colors::Enemy::InvisibleDistanceColor[2];
			Config::EnemyColors::InvisibleDistanceColorA = Features::Colors::Enemy::InvisibleDistanceColor[3];
			Config::EnemyColors::VisibleDistanceColorR = Features::Colors::Enemy::VisibleDistanceColor[0];
			Config::EnemyColors::VisibleDistanceColorG = Features::Colors::Enemy::VisibleDistanceColor[1];
			Config::EnemyColors::VisibleDistanceColorB = Features::Colors::Enemy::VisibleDistanceColor[2];
			Config::EnemyColors::VisibleDistanceColorA = Features::Colors::Enemy::VisibleDistanceColor[3];
			Config::EnemyColors::InvisibleLegendColorR = Features::Colors::Enemy::InvisibleLegendColor[0];
			Config::EnemyColors::InvisibleLegendColorG = Features::Colors::Enemy::InvisibleLegendColor[1];
			Config::EnemyColors::InvisibleLegendColorB = Features::Colors::Enemy::InvisibleLegendColor[2];
			Config::EnemyColors::InvisibleLegendColorA = Features::Colors::Enemy::InvisibleLegendColor[3];
			Config::EnemyColors::VisibleLegendColorR = Features::Colors::Enemy::VisibleLegendColor[0];
			Config::EnemyColors::VisibleLegendColorG = Features::Colors::Enemy::VisibleLegendColor[1];
			Config::EnemyColors::VisibleLegendColorB = Features::Colors::Enemy::VisibleLegendColor[2];
			Config::EnemyColors::VisibleLegendColorA = Features::Colors::Enemy::VisibleLegendColor[3];
			Config::EnemyColors::InvisibleWeaponColorR = Features::Colors::Enemy::InvisibleWeaponColor[0];
			Config::EnemyColors::InvisibleWeaponColorG = Features::Colors::Enemy::InvisibleWeaponColor[1];
			Config::EnemyColors::InvisibleWeaponColorB = Features::Colors::Enemy::InvisibleWeaponColor[2];
			Config::EnemyColors::InvisibleWeaponColorA = Features::Colors::Enemy::InvisibleWeaponColor[3];
			Config::EnemyColors::VisibleWeaponColorR = Features::Colors::Enemy::VisibleWeaponColor[0];
			Config::EnemyColors::VisibleWeaponColorG = Features::Colors::Enemy::VisibleWeaponColor[1];
			Config::EnemyColors::VisibleWeaponColorB = Features::Colors::Enemy::VisibleWeaponColor[2];
			Config::EnemyColors::VisibleWeaponColorA = Features::Colors::Enemy::VisibleWeaponColor[3];
			Config::Colors::FOVColorR = Features::Colors::FOVColor[0];
			Config::Colors::FOVColorG = Features::Colors::FOVColor[1];
			Config::Colors::FOVColorB = Features::Colors::FOVColor[2];
			Config::Colors::FOVColorA = Features::Colors::FOVColor[3];
			Config::Colors::FilledFOVColorR = Features::Colors::FilledFOVColor[0];
			Config::Colors::FilledFOVColorG = Features::Colors::FilledFOVColor[1];
			Config::Colors::FilledFOVColorB = Features::Colors::FilledFOVColor[2];
			Config::Colors::FilledFOVColorA = Features::Colors::FilledFOVColor[3];
			Config::Colors::CrosshairColorR = Features::Colors::CrosshairColor[0];
			Config::Colors::CrosshairColorG = Features::Colors::CrosshairColor[1];
			Config::Colors::CrosshairColorB = Features::Colors::CrosshairColor[2];
			Config::Colors::CrosshairColorA = Features::Colors::CrosshairColor[3];
			// Weapon Colors
			Config::EnemyColors::LightWeaponColorR = Features::Colors::Enemy::LightWeaponColor[0];
			Config::EnemyColors::LightWeaponColorG = Features::Colors::Enemy::LightWeaponColor[1];
			Config::EnemyColors::LightWeaponColorB = Features::Colors::Enemy::LightWeaponColor[2];
			Config::EnemyColors::LightWeaponColorA = Features::Colors::Enemy::LightWeaponColor[3];
			Config::EnemyColors::HeavyWeaponColorR = Features::Colors::Enemy::HeavyWeaponColor[0];
			Config::EnemyColors::HeavyWeaponColorG = Features::Colors::Enemy::HeavyWeaponColor[1];
			Config::EnemyColors::HeavyWeaponColorB = Features::Colors::Enemy::HeavyWeaponColor[2];
			Config::EnemyColors::HeavyWeaponColorA = Features::Colors::Enemy::HeavyWeaponColor[3];
			Config::EnemyColors::EnergyWeaponColorR = Features::Colors::Enemy::EnergyWeaponColor[0];
			Config::EnemyColors::EnergyWeaponColorG = Features::Colors::Enemy::EnergyWeaponColor[1];
			Config::EnemyColors::EnergyWeaponColorB = Features::Colors::Enemy::EnergyWeaponColor[2];
			Config::EnemyColors::EnergyWeaponColorA = Features::Colors::Enemy::EnergyWeaponColor[3];
			Config::EnemyColors::ShotgunWeaponColorR = Features::Colors::Enemy::ShotgunWeaponColor[0];
			Config::EnemyColors::ShotgunWeaponColorG = Features::Colors::Enemy::ShotgunWeaponColor[1];
			Config::EnemyColors::ShotgunWeaponColorB = Features::Colors::Enemy::ShotgunWeaponColor[2];
			Config::EnemyColors::ShotgunWeaponColorA = Features::Colors::Enemy::ShotgunWeaponColor[3];
			Config::EnemyColors::SniperWeaponColorR = Features::Colors::Enemy::SniperWeaponColor[0];
			Config::EnemyColors::SniperWeaponColorG = Features::Colors::Enemy::SniperWeaponColor[1];
			Config::EnemyColors::SniperWeaponColorB = Features::Colors::Enemy::SniperWeaponColor[2];
			Config::EnemyColors::SniperWeaponColorA = Features::Colors::Enemy::SniperWeaponColor[3];
			Config::EnemyColors::LegendaryWeaponColorR = Features::Colors::Enemy::LegendaryWeaponColor[0];
			Config::EnemyColors::LegendaryWeaponColorG = Features::Colors::Enemy::LegendaryWeaponColor[1];
			Config::EnemyColors::LegendaryWeaponColorB = Features::Colors::Enemy::LegendaryWeaponColor[2];
			Config::EnemyColors::LegendaryWeaponColorA = Features::Colors::Enemy::LegendaryWeaponColor[3];
			Config::EnemyColors::MeleeWeaponColorR = Features::Colors::Enemy::MeleeWeaponColor[0];
			Config::EnemyColors::MeleeWeaponColorG = Features::Colors::Enemy::MeleeWeaponColor[1];
			Config::EnemyColors::MeleeWeaponColorB = Features::Colors::Enemy::MeleeWeaponColor[2];
			Config::EnemyColors::MeleeWeaponColorA = Features::Colors::Enemy::MeleeWeaponColor[3];
			Config::EnemyColors::ThrowableWeaponColorR = Features::Colors::Enemy::ThrowableWeaponColor[0];
			Config::EnemyColors::ThrowableWeaponColorG = Features::Colors::Enemy::ThrowableWeaponColor[1];
			Config::EnemyColors::ThrowableWeaponColorB = Features::Colors::Enemy::ThrowableWeaponColor[2];
			Config::EnemyColors::ThrowableWeaponColorA = Features::Colors::Enemy::ThrowableWeaponColor[3];

			// Colors
			Config::SenseTeammate::WeaponColorType = Features::Sense::Teammate::WeaponColorType;
			Config::TeammateColors::InvisibleBoxColorR = Features::Colors::Teammate::InvisibleBoxColor[0];
			Config::TeammateColors::InvisibleBoxColorG = Features::Colors::Teammate::InvisibleBoxColor[1];
			Config::TeammateColors::InvisibleBoxColorB = Features::Colors::Teammate::InvisibleBoxColor[2];
			Config::TeammateColors::InvisibleBoxColorA = Features::Colors::Teammate::InvisibleBoxColor[3];
			Config::TeammateColors::VisibleBoxColorR = Features::Colors::Teammate::VisibleBoxColor[0];
			Config::TeammateColors::VisibleBoxColorG = Features::Colors::Teammate::VisibleBoxColor[1];
			Config::TeammateColors::VisibleBoxColorB = Features::Colors::Teammate::VisibleBoxColor[2];
			Config::TeammateColors::VisibleBoxColorA = Features::Colors::Teammate::VisibleBoxColor[3];
			Config::TeammateColors::InvisibleFilledBoxColorR = Features::Colors::Teammate::InvisibleFilledBoxColor[0];
			Config::TeammateColors::InvisibleFilledBoxColorG = Features::Colors::Teammate::InvisibleFilledBoxColor[1];
			Config::TeammateColors::InvisibleFilledBoxColorB = Features::Colors::Teammate::InvisibleFilledBoxColor[2];
			Config::TeammateColors::InvisibleFilledBoxColorA = Features::Colors::Teammate::InvisibleFilledBoxColor[3];
			Config::TeammateColors::VisibleFilledBoxColorR = Features::Colors::Teammate::VisibleFilledBoxColor[0];
			Config::TeammateColors::VisibleFilledBoxColorG = Features::Colors::Teammate::VisibleFilledBoxColor[1];
			Config::TeammateColors::VisibleFilledBoxColorB = Features::Colors::Teammate::VisibleFilledBoxColor[2];
			Config::TeammateColors::VisibleFilledBoxColorA = Features::Colors::Teammate::VisibleFilledBoxColor[3];
			Config::TeammateColors::InvisibleTracerColorR = Features::Colors::Teammate::InvisibleTracerColor[0];
			Config::TeammateColors::InvisibleTracerColorG = Features::Colors::Teammate::InvisibleTracerColor[1];
			Config::TeammateColors::InvisibleTracerColorB = Features::Colors::Teammate::InvisibleTracerColor[2];
			Config::TeammateColors::InvisibleTracerColorA = Features::Colors::Teammate::InvisibleTracerColor[3];
			Config::TeammateColors::VisibleTracerColorR = Features::Colors::Teammate::VisibleTracerColor[0];
			Config::TeammateColors::VisibleTracerColorG = Features::Colors::Teammate::VisibleTracerColor[1];
			Config::TeammateColors::VisibleTracerColorB = Features::Colors::Teammate::VisibleTracerColor[2];
			Config::TeammateColors::VisibleTracerColorA = Features::Colors::Teammate::VisibleTracerColor[3];
			Config::TeammateColors::InvisibleSkeletonColorR = Features::Colors::Teammate::InvisibleSkeletonColor[0];
			Config::TeammateColors::InvisibleSkeletonColorG = Features::Colors::Teammate::InvisibleSkeletonColor[1];
			Config::TeammateColors::InvisibleSkeletonColorB = Features::Colors::Teammate::InvisibleSkeletonColor[2];
			Config::TeammateColors::InvisibleSkeletonColorA = Features::Colors::Teammate::InvisibleSkeletonColor[3];
			Config::TeammateColors::VisibleSkeletonColorR = Features::Colors::Teammate::VisibleSkeletonColor[0];
			Config::TeammateColors::VisibleSkeletonColorG = Features::Colors::Teammate::VisibleSkeletonColor[1];
			Config::TeammateColors::VisibleSkeletonColorB = Features::Colors::Teammate::VisibleSkeletonColor[2];
			Config::TeammateColors::VisibleSkeletonColorA = Features::Colors::Teammate::VisibleSkeletonColor[3];
			Config::TeammateColors::InvisibleNameColorR = Features::Colors::Teammate::InvisibleNameColor[0];
			Config::TeammateColors::InvisibleNameColorG = Features::Colors::Teammate::InvisibleNameColor[1];
			Config::TeammateColors::InvisibleNameColorB = Features::Colors::Teammate::InvisibleNameColor[2];
			Config::TeammateColors::InvisibleNameColorA = Features::Colors::Teammate::InvisibleNameColor[3];
			Config::TeammateColors::VisibleNameColorR = Features::Colors::Teammate::VisibleNameColor[0];
			Config::TeammateColors::VisibleNameColorG = Features::Colors::Teammate::VisibleNameColor[1];
			Config::TeammateColors::VisibleNameColorB = Features::Colors::Teammate::VisibleNameColor[2];
			Config::TeammateColors::VisibleNameColorA = Features::Colors::Teammate::VisibleNameColor[3];
			Config::TeammateColors::InvisibleDistanceColorR = Features::Colors::Teammate::InvisibleDistanceColor[0];
			Config::TeammateColors::InvisibleDistanceColorG = Features::Colors::Teammate::InvisibleDistanceColor[1];
			Config::TeammateColors::InvisibleDistanceColorB = Features::Colors::Teammate::InvisibleDistanceColor[2];
			Config::TeammateColors::InvisibleDistanceColorA = Features::Colors::Teammate::InvisibleDistanceColor[3];
			Config::TeammateColors::VisibleDistanceColorR = Features::Colors::Teammate::VisibleDistanceColor[0];
			Config::TeammateColors::VisibleDistanceColorG = Features::Colors::Teammate::VisibleDistanceColor[1];
			Config::TeammateColors::VisibleDistanceColorB = Features::Colors::Teammate::VisibleDistanceColor[2];
			Config::TeammateColors::VisibleDistanceColorA = Features::Colors::Teammate::VisibleDistanceColor[3];
			Config::TeammateColors::InvisibleLegendColorR = Features::Colors::Teammate::InvisibleLegendColor[0];
			Config::TeammateColors::InvisibleLegendColorG = Features::Colors::Teammate::InvisibleLegendColor[1];
			Config::TeammateColors::InvisibleLegendColorB = Features::Colors::Teammate::InvisibleLegendColor[2];
			Config::TeammateColors::InvisibleLegendColorA = Features::Colors::Teammate::InvisibleLegendColor[3];
			Config::TeammateColors::VisibleLegendColorR = Features::Colors::Teammate::VisibleLegendColor[0];
			Config::TeammateColors::VisibleLegendColorG = Features::Colors::Teammate::VisibleLegendColor[1];
			Config::TeammateColors::VisibleLegendColorB = Features::Colors::Teammate::VisibleLegendColor[2];
			Config::TeammateColors::VisibleLegendColorA = Features::Colors::Teammate::VisibleLegendColor[3];
			Config::TeammateColors::InvisibleWeaponColorR = Features::Colors::Teammate::InvisibleWeaponColor[0];
			Config::TeammateColors::InvisibleWeaponColorG = Features::Colors::Teammate::InvisibleWeaponColor[1];
			Config::TeammateColors::InvisibleWeaponColorB = Features::Colors::Teammate::InvisibleWeaponColor[2];
			Config::TeammateColors::InvisibleWeaponColorA = Features::Colors::Teammate::InvisibleWeaponColor[3];
			Config::TeammateColors::VisibleWeaponColorR = Features::Colors::Teammate::VisibleWeaponColor[0];
			Config::TeammateColors::VisibleWeaponColorG = Features::Colors::Teammate::VisibleWeaponColor[1];
			Config::TeammateColors::VisibleWeaponColorB = Features::Colors::Teammate::VisibleWeaponColor[2];
			Config::TeammateColors::VisibleWeaponColorA = Features::Colors::Teammate::VisibleWeaponColor[3];
			Config::Colors::FOVColorR = Features::Colors::FOVColor[0];
			Config::Colors::FOVColorG = Features::Colors::FOVColor[1];
			Config::Colors::FOVColorB = Features::Colors::FOVColor[2];
			Config::Colors::FOVColorA = Features::Colors::FOVColor[3];
			Config::Colors::FilledFOVColorR = Features::Colors::FilledFOVColor[0];
			Config::Colors::FilledFOVColorG = Features::Colors::FilledFOVColor[1];
			Config::Colors::FilledFOVColorB = Features::Colors::FilledFOVColor[2];
			Config::Colors::FilledFOVColorA = Features::Colors::FilledFOVColor[3];
			Config::Colors::CrosshairColorR = Features::Colors::CrosshairColor[0];
			Config::Colors::CrosshairColorG = Features::Colors::CrosshairColor[1];
			Config::Colors::CrosshairColorB = Features::Colors::CrosshairColor[2];
			Config::Colors::CrosshairColorA = Features::Colors::CrosshairColor[3];
			// Weapon Colors
			Config::TeammateColors::LightWeaponColorR = Features::Colors::Teammate::LightWeaponColor[0];
			Config::TeammateColors::LightWeaponColorG = Features::Colors::Teammate::LightWeaponColor[1];
			Config::TeammateColors::LightWeaponColorB = Features::Colors::Teammate::LightWeaponColor[2];
			Config::TeammateColors::LightWeaponColorA = Features::Colors::Teammate::LightWeaponColor[3];
			Config::TeammateColors::HeavyWeaponColorR = Features::Colors::Teammate::HeavyWeaponColor[0];
			Config::TeammateColors::HeavyWeaponColorG = Features::Colors::Teammate::HeavyWeaponColor[1];
			Config::TeammateColors::HeavyWeaponColorB = Features::Colors::Teammate::HeavyWeaponColor[2];
			Config::TeammateColors::HeavyWeaponColorA = Features::Colors::Teammate::HeavyWeaponColor[3];
			Config::TeammateColors::EnergyWeaponColorR = Features::Colors::Teammate::EnergyWeaponColor[0];
			Config::TeammateColors::EnergyWeaponColorG = Features::Colors::Teammate::EnergyWeaponColor[1];
			Config::TeammateColors::EnergyWeaponColorB = Features::Colors::Teammate::EnergyWeaponColor[2];
			Config::TeammateColors::EnergyWeaponColorA = Features::Colors::Teammate::EnergyWeaponColor[3];
			Config::TeammateColors::ShotgunWeaponColorR = Features::Colors::Teammate::ShotgunWeaponColor[0];
			Config::TeammateColors::ShotgunWeaponColorG = Features::Colors::Teammate::ShotgunWeaponColor[1];
			Config::TeammateColors::ShotgunWeaponColorB = Features::Colors::Teammate::ShotgunWeaponColor[2];
			Config::TeammateColors::ShotgunWeaponColorA = Features::Colors::Teammate::ShotgunWeaponColor[3];
			Config::TeammateColors::SniperWeaponColorR = Features::Colors::Teammate::SniperWeaponColor[0];
			Config::TeammateColors::SniperWeaponColorG = Features::Colors::Teammate::SniperWeaponColor[1];
			Config::TeammateColors::SniperWeaponColorB = Features::Colors::Teammate::SniperWeaponColor[2];
			Config::TeammateColors::SniperWeaponColorA = Features::Colors::Teammate::SniperWeaponColor[3];
			Config::TeammateColors::LegendaryWeaponColorR = Features::Colors::Teammate::LegendaryWeaponColor[0];
			Config::TeammateColors::LegendaryWeaponColorG = Features::Colors::Teammate::LegendaryWeaponColor[1];
			Config::TeammateColors::LegendaryWeaponColorB = Features::Colors::Teammate::LegendaryWeaponColor[2];
			Config::TeammateColors::LegendaryWeaponColorA = Features::Colors::Teammate::LegendaryWeaponColor[3];
			Config::TeammateColors::MeleeWeaponColorR = Features::Colors::Teammate::MeleeWeaponColor[0];
			Config::TeammateColors::MeleeWeaponColorG = Features::Colors::Teammate::MeleeWeaponColor[1];
			Config::TeammateColors::MeleeWeaponColorB = Features::Colors::Teammate::MeleeWeaponColor[2];
			Config::TeammateColors::MeleeWeaponColorA = Features::Colors::Teammate::MeleeWeaponColor[3];
			Config::TeammateColors::ThrowableWeaponColorR = Features::Colors::Teammate::ThrowableWeaponColor[0];
			Config::TeammateColors::ThrowableWeaponColorG = Features::Colors::Teammate::ThrowableWeaponColor[1];
			Config::TeammateColors::ThrowableWeaponColorB = Features::Colors::Teammate::ThrowableWeaponColor[2];
			Config::TeammateColors::ThrowableWeaponColorA = Features::Colors::Teammate::ThrowableWeaponColor[3];

			Config::Colors::SpectatorWarningColorR = Features::Colors::SpectatorWarningColor[0];
			Config::Colors::SpectatorWarningColorG = Features::Colors::SpectatorWarningColor[1];
			Config::Colors::SpectatorWarningColorB = Features::Colors::SpectatorWarningColor[2];
			Config::Colors::SpectatorWarningColorA = Features::Colors::SpectatorWarningColor[3];
			Config::Colors::VisibleWarningColorR = Features::Colors::VisibleWarningColor[0];;
			Config::Colors::VisibleWarningColorG = Features::Colors::VisibleWarningColor[1];
			Config::Colors::VisibleWarningColorB = Features::Colors::VisibleWarningColor[2];
			Config::Colors::VisibleWarningColorA = Features::Colors::VisibleWarningColor[3];

			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	void RenderWatermark(ImDrawList *Canvas, LocalPlayer *Myself, Overlay OverlayWindow)
	{
		int ScreenWidth;
		int ScreenHeight;
		OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);

		if (Features::Watermark::Watermark)
		{
			if (Features::Watermark::WatermarkPosition == 0)
			{ // Top Right
				ImGui::SetNextWindowPos(ImVec2(10.0f, 22.0f), ImGuiCond_Once, ImVec2(0.02f, 0.5f));
			}
			ImGui::SetNextWindowBgAlpha(0.3f);
			ImGui::Begin("Watermark", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

			ImGuiStyle &style = ImGui::GetStyle();
			if (Features::Watermark::Name)
			{
				ImGui::TextColored(style.Colors[ImGuiCol_Text], "zap-client");
			}

			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 1, 1), " | ");
			ImGui::SameLine();

			if (Features::Watermark::Spectators)
			{
				std::chrono::milliseconds Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
				if (Now >= LastUpdateTime + std::chrono::milliseconds(1500))
				{
					int TempTotalSpectators = 0;
					std::vector<std::string> TempSpectators;

					for (int i = 0; i < Players->size(); i++)
					{
						Player *p = Players->at(i);
						if (p->BasePointer == Myself->BasePointer)
							continue;
						if (p->GetViewYaw() == Myself->ViewYaw && p->IsDead)
						{
							TempTotalSpectators++;
							TempSpectators.push_back(p->GetPlayerName());
						}
					}

					TotalSpectators = TempTotalSpectators;
					Spectators = TempSpectators;
					LastUpdateTime = Now;
				}
				ImGui::Text("Spectators: ");
				ImGui::SameLine();
				ImGui::TextColored(TotalSpectators > 0 ? ImVec4(1, 0.343, 0.475, 1) : ImVec4(0.4, 1, 0.343, 1), "%d", TotalSpectators);
			}

			ImGui::SameLine();

			ImGui::TextColored(ImVec4(1, 1, 1, 1), " | ");

			ImGui::SameLine();

			if (Features::Watermark::ProcessingSpeed)
			{
				ImVec4 ProcessingTimeColor;
				ProcessingTimeColor = OverlayWindow.ProcessingTime > 20 ? ProcessingTimeColor = ImVec4(1, 0.343, 0.475, 1) : ProcessingTimeColor = ImVec4(0.4, 1, 0.343, 1);
				ImGui::TextColored(ProcessingTimeColor, "Processing Time: %02dms ", OverlayWindow.ProcessingTime);
			}

			ImGui::End();
		}
	}

	void RenderDrawings(ImDrawList *Canvas, Legitbot *AimAssistState, LocalPlayer *Myself, Overlay OverlayWindow)
	{
		int ScreenWidth;
		int ScreenHeight;
		OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);

		bool GetWeaponID = false; //For finding weapon IDs (Local Player)
		if (GetWeaponID) {
			if (!Myself->IsDead) {

			ImVec2 Center = ImGui::GetMainViewport()->GetCenter();
					ImGui::SetNextWindowPos(ImVec2(0.0f, Center.y), ImGuiCond_Once, ImVec2(0.02f, 0.5f));
					ImGui::SetNextWindowBgAlpha(0.3f);
			ImGui::Begin("Current Weapon ID", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

			std::stringstream LocalwepID;
			LocalwepID << Myself->WeaponIndex;
			std::string LocalwepInt = LocalwepID.str() + " ";
			const char* LocalwepText = (char*)LocalwepInt.c_str();

					ImGui::Text("Current ID: ");
					ImGui::SameLine();
					ImGui::Text(LocalwepText);
					ImGui::End();
			}
		}

		if (!Map->IsPlayable)
			return;
		if (Myself->IsDead)
			return;
		if (!Features::Settings::OverlayEnabled)
			return;

		if (Features::Sense::ShowSpectators)
		{
			ImVec2 Center = ImGui::GetMainViewport()->GetCenter();
			ImGui::SetNextWindowPos(ImVec2(0.0f, Center.y), ImGuiCond_Once, ImVec2(0.02f, 0.5f));
			ImGui::SetNextWindowBgAlpha(0.3f);
			ImGui::Begin("Spectators", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

			std::chrono::milliseconds Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			if (Now >= LastUpdateTime + std::chrono::milliseconds(1500))
			{
				int TempTotalSpectators = 0;
				std::vector<std::string> TempSpectators;

				for (int i = 0; i < Players->size(); i++)
				{
					Player *p = Players->at(i);
					if (p->BasePointer == Myself->BasePointer)
						continue;
					if (p->GetViewYaw() == Myself->ViewYaw && p->IsDead)
					{
						TempTotalSpectators++;
						TempSpectators.push_back(p->GetPlayerName());
					}
				}

				TotalSpectators = TempTotalSpectators;
				Spectators = TempSpectators;
				LastUpdateTime = Now;
			}
			ImGui::Text("Spectators: ");
			ImGui::SameLine();
			ImGui::TextColored(TotalSpectators > 0 ? ImVec4(1, 0.343, 0.475, 1) : ImVec4(0.4, 1, 0.343, 1), "%d", TotalSpectators);
			if (static_cast<int>(Spectators.size()) > 0)
			{
				ImGui::Separator();
				for (int i = 0; i < static_cast<int>(Spectators.size()); i++)
				{
					ImGui::TextColored(ImVec4(1, 0.343, 0.475, 1), "> %s", Spectators.at(i).c_str());
				}
			}
			ImGui::End();
		}

		// Draw Crosshair
		if (Features::Sense::DrawCrosshair)
		{
			int x = (int)(ScreenWidth * 0.5f);
			int y = (int)(ScreenHeight * 0.5f);
			Renderer::DrawLine(Canvas, Vector2D(x - Features::Sense::CrosshairSize, y), Vector2D(x + Features::Sense::CrosshairSize, y), Features::Sense::CrosshairThickness, ImColor(Features::Colors::CrosshairColor[0], Features::Colors::CrosshairColor[1], Features::Colors::CrosshairColor[2], Features::Colors::CrosshairColor[3])); // Left - right
			Renderer::DrawLine(Canvas, Vector2D(x, y - Features::Sense::CrosshairSize), Vector2D(x, y + Features::Sense::CrosshairSize), Features::Sense::CrosshairThickness, ImColor(Features::Colors::CrosshairColor[0], Features::Colors::CrosshairColor[1], Features::Colors::CrosshairColor[2], Features::Colors::CrosshairColor[3])); // Top - bottom
		}

		// Draw FOV Circle (Legitbot)
		if (Features::Sense::DrawFOVCircle && Features::Aimbot::AimbotEnabled && !Features::Aimbot::AimbotMode == 1 && Myself->IsCombatReady())
		{
			float FOV = std::min(Features::Aimbot::FOV, Features::Aimbot::FOV * (AimAssistState->GetFOVScale() * Features::Aimbot::ZoomScale));
			float Radius = tanf(DEG2RAD(FOV) / 2) / tanf(DEG2RAD(Features::Sense::GameFOV) / 2) * ScreenWidth;
			Renderer::DrawCircle(Canvas, Vector2D(ScreenWidth / 2, ScreenHeight / 2), Radius, 40, ImColor(Features::Colors::FOVColor[0], Features::Colors::FOVColor[1], Features::Colors::FOVColor[2], Features::Colors::FOVColor[3]), Features::Sense::FOVThickness);
		}

		// Draw Filled FOV Circle (Legitbot)
		if (Features::Sense::DrawFilledFOVCircle && Features::Aimbot::AimbotEnabled && !Features::Aimbot::AimbotMode == 1 && Myself->IsCombatReady())
		{
			float FOV = std::min(Features::Aimbot::FOV, Features::Aimbot::FOV * (AimAssistState->GetFOVScale() * Features::Aimbot::ZoomScale));
			float Radius = tanf(DEG2RAD(FOV) / 2) / tanf(DEG2RAD(Features::Sense::GameFOV) / 2) * ScreenWidth;
			Renderer::DrawCircleFilled(Canvas, Vector2D(ScreenWidth / 2, ScreenHeight / 2), Radius, 40, ImColor(Features::Colors::FilledFOVColor[0], Features::Colors::FilledFOVColor[1], Features::Colors::FilledFOVColor[2], Features::Colors::FilledFOVColor[3]));
		}

		// Draw FOV Circle (Ragebot)
		if (Features::Sense::DrawFOVCircle && Features::Ragebot::RageAimbot && Myself->IsCombatReady())
		{
			float FOV = std::min(Features::Ragebot::FOV, Features::Ragebot::FOV * (AimAssistState->GetFOVScale() * Features::Ragebot::ZoomScale));
			float Radius = tanf(DEG2RAD(FOV) / 2) / tanf(DEG2RAD(Features::Sense::GameFOV) / 2) * ScreenWidth;
			Renderer::DrawCircle(Canvas, Vector2D(ScreenWidth / 2, ScreenHeight / 2), Radius, 40, ImColor(Features::Colors::FOVColor[0], Features::Colors::FOVColor[1], Features::Colors::FOVColor[2], Features::Colors::FOVColor[3]), Features::Sense::FOVThickness);
		}

		// Draw Filled FOV Circle (Legitbot)
		if (Features::Sense::DrawFilledFOVCircle && Features::Ragebot::RageAimbot && Myself->IsCombatReady())
		{
			float FOV = std::min(Features::Ragebot::FOV, Features::Ragebot::FOV * (AimAssistState->GetFOVScale() * Features::Ragebot::ZoomScale));
			float Radius = tanf(DEG2RAD(FOV) / 2) / tanf(DEG2RAD(Features::Sense::GameFOV) / 2) * ScreenWidth;
			Renderer::DrawCircleFilled(Canvas, Vector2D(ScreenWidth / 2, ScreenHeight / 2), Radius, 40, ImColor(Features::Colors::FilledFOVColor[0], Features::Colors::FilledFOVColor[1], Features::Colors::FilledFOVColor[2], Features::Colors::FilledFOVColor[3]));
		}

		// Draw lot of things
		if (Features::Settings::ESPEnabled)
		{
			for (int i = 0; i < Players->size(); i++)
			{
				Player *p = Players->at(i);

				Vector2D LocalOriginW2S, HeadPositionW2S, AboveHeadW2S;

				Vector3D LocalOrigin3D = p->LocalOrigin;
				Vector3D Head3D = p->GetBonePosition(HitboxType::Head);
				Vector3D AboveHead3D = p->GetBonePosition(HitboxType::Head);

				AboveHead3D.z += 10.f; // Y Offset

				bool bLocalOriginW2SValid = GameCamera->WorldToScreen(LocalOrigin3D, LocalOriginW2S);
				bool bHeadPositionW2SValid = GameCamera->WorldToScreen(Head3D, HeadPositionW2S);
				GameCamera->WorldToScreen(AboveHead3D, AboveHeadW2S);

				// Colors - Players (Enemy)
				ImVec4 EnemyBoxColor, EnemyFilledBoxColor, EnemyTracerColor, EnemySkeletonColor, EnemyHeadCircleColor, EnemyNameColor, EnemyDistanceColor, EnemyLegendColor, EnemyWeaponColor;
				if (p->IsVisible)
				{
					EnemyBoxColor = ImVec4(Features::Colors::Enemy::VisibleBoxColor[0], Features::Colors::Enemy::VisibleBoxColor[1], Features::Colors::Enemy::VisibleBoxColor[2], Features::Colors::Enemy::VisibleBoxColor[3]);
					EnemyFilledBoxColor = ImVec4(Features::Colors::Enemy::VisibleFilledBoxColor[0], Features::Colors::Enemy::VisibleFilledBoxColor[1], Features::Colors::Enemy::VisibleFilledBoxColor[2], Features::Colors::Enemy::VisibleFilledBoxColor[3]);
					EnemyTracerColor = ImVec4(Features::Colors::Enemy::VisibleTracerColor[0], Features::Colors::Enemy::VisibleTracerColor[1], Features::Colors::Enemy::VisibleTracerColor[2], Features::Colors::Enemy::VisibleTracerColor[3]);
					EnemySkeletonColor = ImVec4(Features::Colors::Enemy::VisibleSkeletonColor[0], Features::Colors::Enemy::VisibleSkeletonColor[1], Features::Colors::Enemy::VisibleSkeletonColor[2], Features::Colors::Enemy::VisibleSkeletonColor[3]);
					EnemyHeadCircleColor = ImVec4(Features::Colors::Enemy::VisibleHeadCircleColor[0], Features::Colors::Enemy::VisibleHeadCircleColor[1], Features::Colors::Enemy::VisibleHeadCircleColor[2], Features::Colors::Enemy::VisibleHeadCircleColor[3]);
					EnemyNameColor = ImVec4(Features::Colors::Enemy::VisibleNameColor[0], Features::Colors::Enemy::VisibleNameColor[1], Features::Colors::Enemy::VisibleNameColor[2], Features::Colors::Enemy::VisibleNameColor[3]);
					EnemyDistanceColor = ImVec4(Features::Colors::Enemy::VisibleDistanceColor[0], Features::Colors::Enemy::VisibleDistanceColor[1], Features::Colors::Enemy::VisibleDistanceColor[2], Features::Colors::Enemy::VisibleDistanceColor[3]);
					EnemyLegendColor = ImVec4(Features::Colors::Enemy::VisibleLegendColor[0], Features::Colors::Enemy::VisibleLegendColor[1], Features::Colors::Enemy::VisibleLegendColor[2], Features::Colors::Enemy::VisibleLegendColor[3]);
					EnemyWeaponColor = ImVec4(Features::Colors::Enemy::VisibleWeaponColor[0], Features::Colors::Enemy::VisibleWeaponColor[1], Features::Colors::Enemy::VisibleWeaponColor[2], Features::Colors::Enemy::VisibleWeaponColor[3]);
				}
				if (!p->IsVisible)
				{
					EnemyBoxColor = ImVec4(Features::Colors::Enemy::InvisibleBoxColor[0], Features::Colors::Enemy::InvisibleBoxColor[1], Features::Colors::Enemy::InvisibleBoxColor[2], Features::Colors::Enemy::InvisibleBoxColor[3]);
					EnemyFilledBoxColor = ImVec4(Features::Colors::Enemy::InvisibleFilledBoxColor[0], Features::Colors::Enemy::InvisibleFilledBoxColor[1], Features::Colors::Enemy::InvisibleFilledBoxColor[2], Features::Colors::Enemy::InvisibleFilledBoxColor[3]);
					EnemyTracerColor = ImVec4(Features::Colors::Enemy::InvisibleTracerColor[0], Features::Colors::Enemy::InvisibleTracerColor[1], Features::Colors::Enemy::InvisibleTracerColor[2], Features::Colors::Enemy::InvisibleTracerColor[3]);
					EnemySkeletonColor = ImVec4(Features::Colors::Enemy::InvisibleSkeletonColor[0], Features::Colors::Enemy::InvisibleSkeletonColor[1], Features::Colors::Enemy::InvisibleSkeletonColor[2], Features::Colors::Enemy::InvisibleSkeletonColor[3]);
					EnemyHeadCircleColor = ImVec4(Features::Colors::Enemy::InvisibleHeadCircleColor[0], Features::Colors::Enemy::InvisibleHeadCircleColor[1], Features::Colors::Enemy::InvisibleHeadCircleColor[2], Features::Colors::Enemy::InvisibleHeadCircleColor[3]);
					EnemyNameColor = ImVec4(Features::Colors::Enemy::InvisibleNameColor[0], Features::Colors::Enemy::InvisibleNameColor[1], Features::Colors::Enemy::InvisibleNameColor[2], Features::Colors::Enemy::InvisibleNameColor[3]);
					EnemyDistanceColor = ImVec4(Features::Colors::Enemy::InvisibleDistanceColor[0], Features::Colors::Enemy::InvisibleDistanceColor[1], Features::Colors::Enemy::InvisibleDistanceColor[2], Features::Colors::Enemy::InvisibleDistanceColor[3]);
					EnemyLegendColor = ImVec4(Features::Colors::Enemy::InvisibleLegendColor[0], Features::Colors::Enemy::InvisibleLegendColor[1], Features::Colors::Enemy::InvisibleLegendColor[2], Features::Colors::Enemy::InvisibleLegendColor[3]);
					EnemyWeaponColor = ImVec4(Features::Colors::Enemy::InvisibleWeaponColor[0], Features::Colors::Enemy::InvisibleWeaponColor[1], Features::Colors::Enemy::InvisibleWeaponColor[2], Features::Colors::Enemy::InvisibleWeaponColor[3]);
				}

				// Colors - Players (Teammate)
				ImVec4 TeammateBoxColor, TeammateFilledBoxColor, TeammateTracerColor, TeammateSkeletonColor, TeammateHeadCircleColor, TeammateNameColor, TeammateDistanceColor, TeammateLegendColor, TeammateWeaponColor;
				if (p->IsVisible)
				{
					TeammateBoxColor = ImVec4(Features::Colors::Teammate::VisibleBoxColor[0], Features::Colors::Teammate::VisibleBoxColor[1], Features::Colors::Teammate::VisibleBoxColor[2], Features::Colors::Teammate::VisibleBoxColor[3]);
					TeammateFilledBoxColor = ImVec4(Features::Colors::Teammate::VisibleFilledBoxColor[0], Features::Colors::Teammate::VisibleFilledBoxColor[1], Features::Colors::Teammate::VisibleFilledBoxColor[2], Features::Colors::Teammate::VisibleFilledBoxColor[3]);
					TeammateTracerColor = ImVec4(Features::Colors::Teammate::VisibleTracerColor[0], Features::Colors::Teammate::VisibleTracerColor[1], Features::Colors::Teammate::VisibleTracerColor[2], Features::Colors::Teammate::VisibleTracerColor[3]);
					TeammateSkeletonColor = ImVec4(Features::Colors::Teammate::VisibleSkeletonColor[0], Features::Colors::Teammate::VisibleSkeletonColor[1], Features::Colors::Teammate::VisibleSkeletonColor[2], Features::Colors::Teammate::VisibleSkeletonColor[3]);
					TeammateHeadCircleColor = ImVec4(Features::Colors::Teammate::VisibleHeadCircleColor[0], Features::Colors::Teammate::VisibleHeadCircleColor[1], Features::Colors::Teammate::VisibleHeadCircleColor[2], Features::Colors::Teammate::VisibleHeadCircleColor[3]);
					TeammateNameColor = ImVec4(Features::Colors::Teammate::VisibleNameColor[0], Features::Colors::Teammate::VisibleNameColor[1], Features::Colors::Teammate::VisibleNameColor[2], Features::Colors::Teammate::VisibleNameColor[3]);
					TeammateDistanceColor = ImVec4(Features::Colors::Teammate::VisibleDistanceColor[0], Features::Colors::Teammate::VisibleDistanceColor[1], Features::Colors::Teammate::VisibleDistanceColor[2], Features::Colors::Teammate::VisibleDistanceColor[3]);
					TeammateLegendColor = ImVec4(Features::Colors::Teammate::VisibleLegendColor[0], Features::Colors::Teammate::VisibleLegendColor[1], Features::Colors::Teammate::VisibleLegendColor[2], Features::Colors::Teammate::VisibleLegendColor[3]);
					TeammateWeaponColor = ImVec4(Features::Colors::Teammate::VisibleWeaponColor[0], Features::Colors::Teammate::VisibleWeaponColor[1], Features::Colors::Teammate::VisibleWeaponColor[2], Features::Colors::Teammate::VisibleWeaponColor[3]);
				}
				if (!p->IsVisible)
				{
					TeammateBoxColor = ImVec4(Features::Colors::Teammate::InvisibleBoxColor[0], Features::Colors::Teammate::InvisibleBoxColor[1], Features::Colors::Teammate::InvisibleBoxColor[2], Features::Colors::Teammate::InvisibleBoxColor[3]);
					TeammateFilledBoxColor = ImVec4(Features::Colors::Teammate::InvisibleFilledBoxColor[0], Features::Colors::Teammate::InvisibleFilledBoxColor[1], Features::Colors::Teammate::InvisibleFilledBoxColor[2], Features::Colors::Teammate::InvisibleFilledBoxColor[3]);
					TeammateTracerColor = ImVec4(Features::Colors::Teammate::InvisibleTracerColor[0], Features::Colors::Teammate::InvisibleTracerColor[1], Features::Colors::Teammate::InvisibleTracerColor[2], Features::Colors::Teammate::InvisibleTracerColor[3]);
					TeammateSkeletonColor = ImVec4(Features::Colors::Teammate::InvisibleSkeletonColor[0], Features::Colors::Teammate::InvisibleSkeletonColor[1], Features::Colors::Teammate::InvisibleSkeletonColor[2], Features::Colors::Teammate::InvisibleSkeletonColor[3]);
					TeammateHeadCircleColor = ImVec4(Features::Colors::Teammate::InvisibleHeadCircleColor[0], Features::Colors::Teammate::InvisibleHeadCircleColor[1], Features::Colors::Teammate::InvisibleHeadCircleColor[2], Features::Colors::Teammate::InvisibleHeadCircleColor[3]);
					TeammateNameColor = ImVec4(Features::Colors::Teammate::InvisibleNameColor[0], Features::Colors::Teammate::InvisibleNameColor[1], Features::Colors::Teammate::InvisibleNameColor[2], Features::Colors::Teammate::InvisibleNameColor[3]);
					TeammateDistanceColor = ImVec4(Features::Colors::Teammate::InvisibleDistanceColor[0], Features::Colors::Teammate::InvisibleDistanceColor[1], Features::Colors::Teammate::InvisibleDistanceColor[2], Features::Colors::Teammate::InvisibleDistanceColor[3]);
					TeammateLegendColor = ImVec4(Features::Colors::Teammate::InvisibleLegendColor[0], Features::Colors::Teammate::InvisibleLegendColor[1], Features::Colors::Teammate::InvisibleLegendColor[2], Features::Colors::Teammate::InvisibleLegendColor[3]);
					TeammateWeaponColor = ImVec4(Features::Colors::Teammate::InvisibleWeaponColor[0], Features::Colors::Teammate::InvisibleWeaponColor[1], Features::Colors::Teammate::InvisibleWeaponColor[2], Features::Colors::Teammate::InvisibleWeaponColor[3]);
				}

				// Positions - god this is some shitass code... but it works
				Vector2D NamePosition;
				if (Features::Sense::Positions::NamePosition == 0) // Top 1
				{
					NamePosition = AboveHeadW2S.Subtract(Vector2D(0, 15));
				}
				if (Features::Sense::Positions::NamePosition == 1) // Top 2
				{
					NamePosition = AboveHeadW2S.Subtract(Vector2D(0, 30));
				}
				if (Features::Sense::Positions::NamePosition == 2) // Bottom 1
				{
					NamePosition = LocalOriginW2S;
				}
				if (Features::Sense::Positions::NamePosition == 3) // Bottom 2
				{
					NamePosition = LocalOriginW2S.Add(Vector2D(0, 10));
				}
				if (Features::Sense::Positions::NamePosition == 4) // Bottom 1
				{
					NamePosition = LocalOriginW2S.Add(Vector2D(0, 20));
				}
				Vector2D DistancePosition;
				if (Features::Sense::Positions::DistancePosition == 0) // Top 1
				{
					DistancePosition = AboveHeadW2S.Subtract(Vector2D(0, 15));
				}
				if (Features::Sense::Positions::DistancePosition == 1) // Top 2
				{
					DistancePosition = AboveHeadW2S.Subtract(Vector2D(0, 30));
				}
				if (Features::Sense::Positions::DistancePosition == 2) // Bottom 1
				{
					DistancePosition = LocalOriginW2S;
				}
				if (Features::Sense::Positions::DistancePosition == 3) // Bottom 2
				{
					DistancePosition = LocalOriginW2S.Add(Vector2D(0, 10));
				}
				if (Features::Sense::Positions::DistancePosition == 4) // Bottom 1
				{
					DistancePosition = LocalOriginW2S.Add(Vector2D(0, 20));
				}
				Vector2D LegendPosition;
				if (Features::Sense::Positions::LegendPosition == 0) // Top 1
				{
					LegendPosition = AboveHeadW2S.Subtract(Vector2D(0, 15));
				}
				if (Features::Sense::Positions::LegendPosition == 1) // Top 2
				{
					LegendPosition = AboveHeadW2S.Subtract(Vector2D(0, 30));
				}
				if (Features::Sense::Positions::LegendPosition == 2) // Bottom 1
				{
					LegendPosition = LocalOriginW2S;
				}
				if (Features::Sense::Positions::LegendPosition == 3) // Bottom 2
				{
					LegendPosition = LocalOriginW2S.Add(Vector2D(0, 10));
				}
				if (Features::Sense::Positions::LegendPosition == 4) // Bottom 1
				{
					LegendPosition = LocalOriginW2S.Add(Vector2D(0, 20));
				}
				Vector2D WeaponPosition;
				if (Features::Sense::Positions::WeaponPosition == 0) // Top 1
				{
					WeaponPosition = AboveHeadW2S.Subtract(Vector2D(0, 15));
				}
				if (Features::Sense::Positions::WeaponPosition == 1) // Top 2
				{
					WeaponPosition = AboveHeadW2S.Subtract(Vector2D(0, 30));
				}
				if (Features::Sense::Positions::WeaponPosition == 2) // Bottom 1
				{
					WeaponPosition = LocalOriginW2S;
				}
				if (Features::Sense::Positions::WeaponPosition == 3) // Bottom 2
				{
					WeaponPosition = LocalOriginW2S.Add(Vector2D(0, 10));
				}
				if (Features::Sense::Positions::WeaponPosition == 4) // Bottom 1
				{
					WeaponPosition = LocalOriginW2S.Add(Vector2D(0, 20));
				}
				Vector2D StatusPosition;
				if (Features::Sense::Positions::StatusPosition == 0) // Top 1
				{
					StatusPosition = AboveHeadW2S.Subtract(Vector2D(0, 15));
				}
				if (Features::Sense::Positions::StatusPosition == 1) // Top 2
				{
					StatusPosition = AboveHeadW2S.Subtract(Vector2D(0, 30));
				}
				if (Features::Sense::Positions::StatusPosition == 2) // Bottom 1
				{
					StatusPosition = LocalOriginW2S;
				}
				if (Features::Sense::Positions::StatusPosition == 3) // Bottom 2
				{
					StatusPosition = LocalOriginW2S.Add(Vector2D(0, 10));
				}
				if (Features::Sense::Positions::StatusPosition == 4) // Bottom 1
				{
					StatusPosition = LocalOriginW2S.Add(Vector2D(0, 20));
				}

				// EnemyESP
				// VisibilityCheck = false
				if (!Features::Sense::VisibilityCheck && !p->IsLocal && p->IsHostile && p->IsCombatReady() && p->DistanceToLocalPlayer < (Conversion::ToGameUnits(Features::Sense::ESPMaxDistance)))
				{
					// Draw Warning Text - Spectators
					if (Features::Sense::DrawSpectatorWarning && TotalSpectators >= 1)
					{
						std::stringstream WarningTextStart, Space1, Amount, Space2;
						WarningTextStart << "SPECTATOR WARNING";
						Space1 << " [";
						Amount << TotalSpectators;
						Space2 << "]";
						std::string combined = WarningTextStart.str() + Space1.str() + Amount.str() + Space2.str();
						const char *CombinedText = combined.c_str();

						int TextPosX = Features::Sense::WarningTextX;
						int TextPosY = Features::Sense::WarningTextY - 12;
						Renderer::DrawText(Canvas, Vector2D(TextPosX, TextPosY), CombinedText, ImColor(Features::Colors::SpectatorWarningColor[0], Features::Colors::SpectatorWarningColor[1], Features::Colors::SpectatorWarningColor[2], Features::Colors::SpectatorWarningColor[3]), Features::Sense::WarningTextOutline ? true : false, true, false);
					}

					// Draw Warning Text - Visible
					if (Features::Sense::DrawVisibleWarning && p->IsVisible)
					{
						const char *Text = "VISIBLE WARNING!";
						int TextPosX = Features::Sense::WarningTextX;
						int TextPosY = Features::Sense::WarningTextY;
						Renderer::DrawText(Canvas, Vector2D(TextPosX, TextPosY), Text, ImColor(Features::Colors::VisibleWarningColor[0], Features::Colors::VisibleWarningColor[1], Features::Colors::VisibleWarningColor[2], Features::Colors::VisibleWarningColor[3]), Features::Sense::WarningTextOutline ? true : false, true, false);
					}

					// Draw Info Bars
					if (Features::Sense::Enemy::DrawBars && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						int health = p->Health;
						int maxHealth = p->MaxHealth;
						int shield = p->Shield;
						int maxShield = p->MaxShield;

						Renderer::Draw2DBar(Canvas, Features::Sense::Enemy::BarMode, Features::Sense::Enemy::BarStyle, Features::Sense::Enemy::BarColorMode, LocalOriginW2S, HeadPositionW2S, AboveHeadW2S, health, maxHealth, shield, maxShield, Features::Sense::Enemy::BarThickness, Features::Sense::Enemy::BarThickness2, Features::Sense::Enemy::BarWidth, Features::Sense::Enemy::BarHeight);
					}

					if (Features::Sense::Enemy::DrawTracers)
					{
						// Tracers
						Vector2D chestScreenPosition;
						if (Features::Sense::Enemy::TracerBone == 0)
						{
							GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 66)), chestScreenPosition);
						}
						else if (Features::Sense::Enemy::TracerBone == 1)
						{
							GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), chestScreenPosition);
						}

						if (Features::Sense::Enemy::TracerPosition == 0) // top to head
						{
							if (!chestScreenPosition.IsZeroVector())
							{
								int x = (int)(ScreenWidth * 0.5f);

								Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, Features::Sense::Enemy::TracerThickness, ImColor(EnemyTracerColor));
							}
						}

						else if (Features::Sense::Enemy::TracerPosition == 1) // middle to bottom
						{
							if (!chestScreenPosition.IsZeroVector())
							{
								int x = (int)(ScreenWidth * 0.5f);

								Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, Features::Sense::Enemy::TracerThickness, ImColor(EnemyTracerColor));
							}
						}

						else if (Features::Sense::Enemy::TracerPosition == 2) // bottom to bottom
						{
							if (!chestScreenPosition.IsZeroVector())
							{
								int x = (int)(ScreenWidth * 0.5f);

								Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, Features::Sense::Enemy::TracerThickness, ImColor(EnemyTracerColor));
							}
						}
					}

					// Distance
					if (Features::Sense::Enemy::DrawDistance && !Features::Sense::Enemy::DrawNames && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						char buffer[256];
						const char *dist = std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str();
						const char *txt = "[";
						const char *txt2 = " M]";
						strncpy(buffer, txt, sizeof(buffer));
						strncat(buffer, dist, sizeof(buffer));
						strncat(buffer, txt2, sizeof(buffer));

						if (!LocalOriginW2S.IsZeroVector())
						{
							Renderer::DrawText(Canvas, DistancePosition, buffer, ImColor(EnemyDistanceColor), Features::Sense::TextOutline ? true : false, true, false);
						}
					}

					// Names Only
					if (!Features::Sense::Enemy::DrawDistance && Features::Sense::Enemy::DrawNames && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						Renderer::DrawText(Canvas, AboveHeadW2S.Subtract(Vector2D(0, 16)), p->GetPlayerName().c_str(), ImColor(EnemyNameColor), Features::Sense::TextOutline ? true : false, true, false);
					}

					// Name & Distance
					if (Features::Sense::Enemy::DrawDistance && Features::Sense::Enemy::DrawNames && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						std::stringstream name, space, dist, txt, txt2;
						name << p->GetPlayerName().c_str();
						space << " ";
						dist << std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str();
						txt << "[";
						txt2 << " M]";
						std::string combined = name.str() + space.str() + txt.str() + dist.str() + txt2.str();
						const char *combinedText = combined.c_str();

						Renderer::DrawText(Canvas, NamePosition, combinedText, ImColor(EnemyNameColor), Features::Sense::TextOutline ? true : false, true, false);
					}

					// Legend
					if (Features::Sense::Enemy::DrawLegend && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						Renderer::DrawText(Canvas, LocalOriginW2S, p->getPlayerModelName().c_str(), ImColor(EnemyLegendColor), Features::Sense::TextOutline ? true : false, true, false);
					}

					// Draw Health + Shield Text
					if (Features::Sense::Enemy::DrawStatus && bLocalOriginW2SValid)
					{
						std::stringstream healthValue, shieldValue, maxHealthValue, maxShieldValue;
						healthValue << p->Health;
						shieldValue << p->Shield;
						maxHealthValue << p->MaxHealth;
						maxShieldValue << p->MaxShield;
						std::string healthInt = healthValue.str() + " HP";
						std::string shieldInt = shieldValue.str() + " AP";
						const char *healthText = (char *)healthInt.c_str();
						const char *shieldText = (char *)shieldInt.c_str();
						std::string combinedHealth = healthValue.str() + " / " + maxHealthValue.str() + " HP";
						const char *combinedHealthText = combinedHealth.c_str();
						std::string combinedShield = shieldValue.str() + " / " + maxShieldValue.str() + " AP";
						const char *combinedShieldText = combinedShield.c_str();

						ImColor ShieldColor;
						if (p->MaxShield == 50)
						{ // white
							ShieldColor = ImColor(247, 247, 247);
						}
						else if (p->MaxShield == 75)
						{ // blue
							ShieldColor = ImColor(39, 178, 255);
						}
						else if (p->MaxShield == 100)
						{ // purple
							ShieldColor = ImColor(206, 59, 255);
						}
						else if (p->MaxShield == 125)
						{ // red
							ShieldColor = ImColor(219, 2, 2);
						}
						else
						{
							ShieldColor = ImColor(247, 247, 247);
						}

						// Render Text
						if (!Features::Sense::Enemy::ShowMaxStatusValues)
						{
							Renderer::DrawText(Canvas, StatusPosition, healthText, ImColor(0, 255, 0), Features::Sense::TextOutline ? true : false, true, false);
							Renderer::DrawText(Canvas, StatusPosition.Add(Vector2D(0, 0 + 10)), shieldText, ShieldColor, Features::Sense::TextOutline ? true : false, true, false);
						}
						if (Features::Sense::Enemy::ShowMaxStatusValues)
						{
							Renderer::DrawText(Canvas, StatusPosition, combinedHealthText, ImColor(0, 255, 0), Features::Sense::TextOutline ? true : false, true, false);
							Renderer::DrawText(Canvas, StatusPosition.Add(Vector2D(0, 0 + 10)), combinedShieldText, ShieldColor, Features::Sense::TextOutline ? true : false, true, false);
						}
					}

					// Weapon ESP
					int weaponHeldID;
					weaponHeldID = p->WeaponIndex;
					const char *weaponHeldText = "Unknown";

					ImColor weaponHeldColor;
					weaponHeldColor = ImColor(255, 255, 255);

					// Draw Weapon
					if (Features::Sense::Enemy::DrawWeapon && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{

						// Light Weapons
						if (weaponHeldID == 107)
						{ // P2020
							weaponHeldText = "P2020";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 82)
						{ // RE-45
							weaponHeldText = "RE-45";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 81)
						{ // Alternator
							weaponHeldText = "Alternator";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 106)
						{ // R-99
							weaponHeldText = "R-99";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 0)
						{ // R-301
							weaponHeldText = "R-301";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 108)
						{ // Spitfire
							weaponHeldText = "Spitfire";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 91)
						{ // G7
							weaponHeldText = "G7 Scout";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						// Heavy Weapons
						if (weaponHeldID == 114)
						{ // CARSMG
							weaponHeldText = "CAR SMG";
							weaponHeldColor = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
						}
						if (weaponHeldID == 6)
						{ // Rampage
							weaponHeldText = "Rampage";
							weaponHeldColor = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
						}
						if (weaponHeldID == 113)
						{ // Repeater
							weaponHeldText = "Repeater";
							weaponHeldColor = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
						}
						if (weaponHeldID == 92)
						{ // Hemlock
							weaponHeldText = "Hemlock";
							weaponHeldColor = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
						}
						if (weaponHeldID == 90)
						{ // Flatline
							weaponHeldText = "Flatline";
							weaponHeldColor = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
						}
						// Energy Weapons
						if (weaponHeldID == 115)
						{ // Nemesis
							weaponHeldText = "Nemesis";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						if (weaponHeldID == 112)
						{ // Volt
							weaponHeldText = "Volt";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						if (weaponHeldID == 109)
						{ // TripleTake
							weaponHeldText = "Triple Take";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						if (weaponHeldID == 95)
						{ // LSTAR
							weaponHeldText = "L-STAR";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						if (weaponHeldID == 85)
						{ // Devotion
							weaponHeldText = "Devotion";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						if (weaponHeldID == 87)
						{ // Havoc
							weaponHeldText = "Havoc";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						// Shotguns
						if (weaponHeldID == 98)
						{ // Mozambique
							weaponHeldText = "Mozambique";
							weaponHeldColor = ImColor(Features::Colors::Enemy::ShotgunWeaponColor[0], Features::Colors::Enemy::ShotgunWeaponColor[1], Features::Colors::Enemy::ShotgunWeaponColor[2], Features::Colors::Enemy::ShotgunWeaponColor[3]);
						}
						if (weaponHeldID == 89)
						{ // EVA8
							weaponHeldText = "EVA-8 Auto";
							weaponHeldColor = ImColor(Features::Colors::Enemy::ShotgunWeaponColor[0], Features::Colors::Enemy::ShotgunWeaponColor[1], Features::Colors::Enemy::ShotgunWeaponColor[2], Features::Colors::Enemy::ShotgunWeaponColor[3]);
						}
						if (weaponHeldID == 105)
						{ // Peacekeeper
							weaponHeldText = "Peacekeeper";
							weaponHeldColor = ImColor(Features::Colors::Enemy::ShotgunWeaponColor[0], Features::Colors::Enemy::ShotgunWeaponColor[1], Features::Colors::Enemy::ShotgunWeaponColor[2], Features::Colors::Enemy::ShotgunWeaponColor[3]);
						}
						if (weaponHeldID == 97)
						{ // Mastiff
							weaponHeldText = "Mastiff";
							weaponHeldColor = ImColor(Features::Colors::Enemy::ShotgunWeaponColor[0], Features::Colors::Enemy::ShotgunWeaponColor[1], Features::Colors::Enemy::ShotgunWeaponColor[2], Features::Colors::Enemy::ShotgunWeaponColor[3]);
						}
						// Snipers
						if (weaponHeldID == 1)
						{ // Sentinel
							weaponHeldText = "Sentinel";
							weaponHeldColor = ImColor(Features::Colors::Enemy::SniperWeaponColor[0], Features::Colors::Enemy::SniperWeaponColor[1], Features::Colors::Enemy::SniperWeaponColor[2], Features::Colors::Enemy::SniperWeaponColor[3]);
						}
						if (weaponHeldID == 84)
						{ // ChargeRifle
							weaponHeldText = "Charge Rifle";
							weaponHeldColor = ImColor(Features::Colors::Enemy::SniperWeaponColor[0], Features::Colors::Enemy::SniperWeaponColor[1], Features::Colors::Enemy::SniperWeaponColor[2], Features::Colors::Enemy::SniperWeaponColor[3]);
						}
						if (weaponHeldID == 86)
						{ // Longbow
							weaponHeldText = "Longbow";
							weaponHeldColor = ImColor(Features::Colors::Enemy::SniperWeaponColor[0], Features::Colors::Enemy::SniperWeaponColor[1], Features::Colors::Enemy::SniperWeaponColor[2], Features::Colors::Enemy::SniperWeaponColor[3]);
						}
						// Legendary Weapons
						if (weaponHeldID == 111)
						{ // Wingman
							weaponHeldText = "Wingman";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}
						if (weaponHeldID == 103)
						{ // Prowler
							weaponHeldText = "Prowler";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}
						if (weaponHeldID == 2)
						{ // Bocek
							weaponHeldText = "Bocek";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}
						if (weaponHeldID == 94)
						{ // Kraber
							weaponHeldText = "Kraber";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}
						if (weaponHeldID == 169)
						{ // Knife
							weaponHeldText = "Throwing Knife";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}
						/*if (weaponHeldID == 3) { //BusterSword
							weaponHeldText = "Buster Sword";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}*/
						// Melee & Grenade
						/*if (weaponHeldID == 213) { //Thermite Grenade
							weaponHeldText = "Thermite Grenade";
							weaponHeldColor = ThrowableWeaponColor;
						}*/
						if (p->IsHoldingGrenade)
						{
							weaponHeldText = "Throwable";
							weaponHeldColor = ImColor(Features::Colors::Enemy::ThrowableWeaponColor[0], Features::Colors::Enemy::ThrowableWeaponColor[1], Features::Colors::Enemy::ThrowableWeaponColor[2], Features::Colors::Enemy::ThrowableWeaponColor[3]);
						}
						if (weaponHeldID == 116)
						{ // Melee
							weaponHeldText = "Melee";
							weaponHeldColor = ImColor(Features::Colors::Enemy::MeleeWeaponColor[0], Features::Colors::Enemy::MeleeWeaponColor[1], Features::Colors::Enemy::MeleeWeaponColor[2], Features::Colors::Enemy::MeleeWeaponColor[3]);
						}

						if (Features::Colors::WeaponColorMode == 1)
						{ // Changes color to ammo type
							Renderer::DrawText(Canvas, WeaponPosition, weaponHeldText, ImColor(weaponHeldColor), Features::Sense::TextOutline ? true : false, true, false);
						}

						if (Features::Colors::WeaponColorMode == 0)
						{ // Single Color
							Renderer::DrawText(Canvas, WeaponPosition, weaponHeldText, ImColor(EnemyWeaponColor), Features::Sense::TextOutline ? true : false, true, false);
						}
					}

					/*bool TestWeaponID = false; //For finding weapon IDs (Used for finding melee ID)
					if (TestWeaponID && bLocalOriginW2SValid && bHeadPositionW2SValid) {
						if (p->IsHostile) {
							std::stringstream wepID;
							wepID << p->WeaponIndex;
							std::string wepInt = wepID.str() + " ";
							const char* wepText = (char*)wepInt.c_str();

							ImColor weaponWHeldColor;
							weaponWHeldColor = ImColor(255, 255, 255);

							Renderer::DrawText(Canvas, LocalOriginW2S.Add(Vector2D(0, 0)), wepText, ImColor(weaponWHeldColor), true, true, false);
						}
					}*/

					// Draw Boxes
					if (Features::Sense::Enemy::DrawBoxes && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						Renderer::Draw2DBox(Canvas, Features::Sense::Enemy::BoxType, Features::Sense::Enemy::BoxStyle, LocalOriginW2S, HeadPositionW2S, ImColor(EnemyBoxColor), ImColor(EnemyFilledBoxColor), Features::Sense::Enemy::BoxThickness);
					}

					// Draw Skeleton
					if (Features::Sense::Enemy::DrawSkeleton && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{

						Vector2D Neck, UpperChest, LowerChest, Stomach, Leftshoulder, Leftelbow, LeftHand, Rightshoulder, RightelbowBone, RightHand, LeftThighs, Leftknees, Leftleg, RightThighs, Rightknees, Rightleg;
						// Head bone is HeadPositionW2S
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Neck), Neck);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::UpperChest), UpperChest);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LowerChest), LowerChest);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Stomach), Stomach);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftshoulder), Leftshoulder);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftelbow), Leftelbow);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LeftHand), LeftHand);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightshoulder), Rightshoulder);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightelbowBone), RightelbowBone);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightHand), RightHand);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LeftThighs), LeftThighs);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftknees), Leftknees);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftleg), Leftleg);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightThighs), RightThighs);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightknees), Rightknees);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightleg), Rightleg);

						Renderer::DrawLine(Canvas, HeadPositionW2S, Neck, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Neck, UpperChest, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, LowerChest, Stomach, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Stomach, RightThighs, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
					}

					// Draw Head Circle
					if (Features::Sense::Enemy::DrawHeadCircle && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{

						Vector2D HeadPos2D;
						Vector3D HeadPos3D = p->GetBonePosition(HitboxType::Head);
						HeadPos3D.z += 3.f;

						GameCamera->WorldToScreen(HeadPos3D, HeadPos2D);

						Renderer::DrawCircle(Canvas, HeadPos2D, 3650 / p->DistanceToLocalPlayer, 255, ImColor(EnemyHeadCircleColor), Features::Sense::Enemy::HeadCircleThickness);
					}

					// Seer
					if (Features::Sense::Enemy::DrawSeer && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						if (!HeadPositionW2S.IsZeroVector())
							Renderer::DrawSeer(Canvas, HeadPositionW2S.x, HeadPositionW2S.y - 20, p->Shield, p->MaxShield, p->Health);
					}
				}

				// VisibilityCheck = true
				if (Features::Sense::VisibilityCheck && !p->IsLocal && p->IsHostile && p->IsCombatReady() && p->IsVisible && p->DistanceToLocalPlayer < (Conversion::ToGameUnits(Features::Sense::ESPMaxDistance)))
				{
					// Draw Warning Text - Spectators
					if (Features::Sense::DrawSpectatorWarning && TotalSpectators >= 1)
					{
						std::stringstream WarningTextStart, Space1, Amount, Space2;
						WarningTextStart << "SPECTATOR WARNING";
						Space1 << " [";
						Amount << TotalSpectators;
						Space2 << "]";
						std::string combined = WarningTextStart.str() + Space1.str() + Amount.str() + Space2.str();
						const char *CombinedText = combined.c_str();

						int TextPosX = Features::Sense::WarningTextX;
						int TextPosY = Features::Sense::WarningTextY - 12;
						Renderer::DrawText(Canvas, Vector2D(TextPosX, TextPosY), CombinedText, ImColor(Features::Colors::SpectatorWarningColor[0], Features::Colors::SpectatorWarningColor[1], Features::Colors::SpectatorWarningColor[2], Features::Colors::SpectatorWarningColor[3]), Features::Sense::WarningTextOutline ? true : false, true, false);
					}

					// Draw Warning Text - Visible
					if (Features::Sense::DrawVisibleWarning && p->IsVisible)
					{
						const char *Text = "VISIBLE WARNING!";
						int TextPosX = Features::Sense::WarningTextX;
						int TextPosY = Features::Sense::WarningTextY;
						Renderer::DrawText(Canvas, Vector2D(TextPosX, TextPosY), Text, ImColor(Features::Colors::VisibleWarningColor[0], Features::Colors::VisibleWarningColor[1], Features::Colors::VisibleWarningColor[2], Features::Colors::VisibleWarningColor[3]), Features::Sense::WarningTextOutline ? true : false, true, false);
					}

					// Draw Info Bars
					if (Features::Sense::Enemy::DrawBars && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						int health = p->Health;
						int maxHealth = p->MaxHealth;
						int shield = p->Shield;
						int maxShield = p->MaxShield;

						Renderer::Draw2DBar(Canvas, Features::Sense::Enemy::BarMode, Features::Sense::Enemy::BarStyle, Features::Sense::Enemy::BarColorMode, LocalOriginW2S, HeadPositionW2S, AboveHeadW2S, health, maxHealth, shield, maxShield, Features::Sense::Enemy::BarThickness, Features::Sense::Enemy::BarThickness2, Features::Sense::Enemy::BarWidth, Features::Sense::Enemy::BarHeight);
					}

					if (Features::Sense::Enemy::DrawTracers)
					{
						// Tracers
						Vector2D chestScreenPosition;
						if (Features::Sense::Enemy::TracerBone == 0)
						{
							GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 66)), chestScreenPosition);
						}
						else if (Features::Sense::Enemy::TracerBone == 1)
						{
							GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), chestScreenPosition);
						}

						if (Features::Sense::Enemy::TracerPosition == 0) // top to head
						{
							if (!chestScreenPosition.IsZeroVector())
							{
								int x = (int)(ScreenWidth * 0.5f);

								Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, Features::Sense::Enemy::TracerThickness, ImColor(EnemyTracerColor));
							}
						}

						else if (Features::Sense::Enemy::TracerPosition == 1) // middle to bottom
						{
							if (!chestScreenPosition.IsZeroVector())
							{
								int x = (int)(ScreenWidth * 0.5f);

								Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, Features::Sense::Enemy::TracerThickness, ImColor(EnemyTracerColor));
							}
						}

						else if (Features::Sense::Enemy::TracerPosition == 2) // bottom to bottom
						{
							if (!chestScreenPosition.IsZeroVector())
							{
								int x = (int)(ScreenWidth * 0.5f);

								Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, Features::Sense::Enemy::TracerThickness, ImColor(EnemyTracerColor));
							}
						}
					}

					// Distance
					if (Features::Sense::Enemy::DrawDistance && !Features::Sense::Enemy::DrawNames && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						char buffer[256];
						const char *dist = std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str();
						const char *txt = "[";
						const char *txt2 = " M]";
						strncpy(buffer, txt, sizeof(buffer));
						strncat(buffer, dist, sizeof(buffer));
						strncat(buffer, txt2, sizeof(buffer));

						if (!LocalOriginW2S.IsZeroVector())
						{
							Renderer::DrawText(Canvas, DistancePosition, buffer, ImColor(EnemyDistanceColor), Features::Sense::TextOutline ? true : false, true, false);
						}
					}

					// Names Only
					if (!Features::Sense::Enemy::DrawDistance && Features::Sense::Enemy::DrawNames && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						Renderer::DrawText(Canvas, AboveHeadW2S.Subtract(Vector2D(0, 16)), p->GetPlayerName().c_str(), ImColor(EnemyNameColor), Features::Sense::TextOutline ? true : false, true, false);
					}

					// Name & Distance
					if (Features::Sense::Enemy::DrawDistance && Features::Sense::Enemy::DrawNames && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						std::stringstream name, space, dist, txt, txt2;
						name << p->GetPlayerName().c_str();
						space << " ";
						dist << std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str();
						txt << "[";
						txt2 << " M]";
						std::string combined = name.str() + space.str() + txt.str() + dist.str() + txt2.str();
						const char *combinedText = combined.c_str();

						Renderer::DrawText(Canvas, NamePosition, combinedText, ImColor(EnemyNameColor), Features::Sense::TextOutline ? true : false, true, false);
					}

					// Legend
					if (Features::Sense::Enemy::DrawLegend && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						Renderer::DrawText(Canvas, LocalOriginW2S, p->getPlayerModelName().c_str(), ImColor(EnemyLegendColor), Features::Sense::TextOutline ? true : false, true, false);
					}

					// Draw Health + Shield Text
					if (Features::Sense::Enemy::DrawStatus && bLocalOriginW2SValid)
					{
						std::stringstream healthValue, shieldValue, maxHealthValue, maxShieldValue;
						healthValue << p->Health;
						shieldValue << p->Shield;
						maxHealthValue << p->MaxHealth;
						maxShieldValue << p->MaxShield;
						std::string healthInt = healthValue.str() + " HP";
						std::string shieldInt = shieldValue.str() + " AP";
						const char *healthText = (char *)healthInt.c_str();
						const char *shieldText = (char *)shieldInt.c_str();
						std::string combinedHealth = healthValue.str() + " / " + maxHealthValue.str() + " HP";
						const char *combinedHealthText = combinedHealth.c_str();
						std::string combinedShield = shieldValue.str() + " / " + maxShieldValue.str() + " AP";
						const char *combinedShieldText = combinedShield.c_str();

						ImColor ShieldColor;
						if (p->MaxShield == 50)
						{ // white
							ShieldColor = ImColor(247, 247, 247);
						}
						else if (p->MaxShield == 75)
						{ // blue
							ShieldColor = ImColor(39, 178, 255);
						}
						else if (p->MaxShield == 100)
						{ // purple
							ShieldColor = ImColor(206, 59, 255);
						}
						else if (p->MaxShield == 125)
						{ // red
							ShieldColor = ImColor(219, 2, 2);
						}
						else
						{
							ShieldColor = ImColor(247, 247, 247);
						}

						// Render Text
						if (!Features::Sense::Enemy::ShowMaxStatusValues)
						{
							Renderer::DrawText(Canvas, StatusPosition, healthText, ImColor(0, 255, 0), Features::Sense::TextOutline ? true : false, true, false);
							Renderer::DrawText(Canvas, StatusPosition.Add(Vector2D(0, 0 + 10)), shieldText, ShieldColor, Features::Sense::TextOutline ? true : false, true, false);
						}
						if (Features::Sense::Enemy::ShowMaxStatusValues)
						{
							Renderer::DrawText(Canvas, StatusPosition, combinedHealthText, ImColor(0, 255, 0), Features::Sense::TextOutline ? true : false, true, false);
							Renderer::DrawText(Canvas, StatusPosition.Add(Vector2D(0, 0 + 10)), combinedShieldText, ShieldColor, Features::Sense::TextOutline ? true : false, true, false);
						}
					}

					// Weapon ESP
					int weaponHeldID;
					weaponHeldID = p->WeaponIndex;
					const char *weaponHeldText = "Unknown";

					ImColor weaponHeldColor;
					weaponHeldColor = ImColor(255, 255, 255);

					// Draw Weapon
					if (Features::Sense::Enemy::DrawWeapon && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{

						// Light Weapons
						if (weaponHeldID == 107)
						{ // P2020
							weaponHeldText = "P2020";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 82)
						{ // RE-45
							weaponHeldText = "RE-45";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 81)
						{ // Alternator
							weaponHeldText = "Alternator";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 106)
						{ // R-99
							weaponHeldText = "R-99";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 0)
						{ // R-301
							weaponHeldText = "R-301";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 108)
						{ // Spitfire
							weaponHeldText = "Spitfire";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 91)
						{ // G7
							weaponHeldText = "G7 Scout";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						// Heavy Weapons
						if (weaponHeldID == 114)
						{ // CARSMG
							weaponHeldText = "CAR SMG";
							weaponHeldColor = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
						}
						if (weaponHeldID == 6)
						{ // Rampage
							weaponHeldText = "Rampage";
							weaponHeldColor = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
						}
						if (weaponHeldID == 113)
						{ // Repeater
							weaponHeldText = "Repeater";
							weaponHeldColor = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
						}
						if (weaponHeldID == 92)
						{ // Hemlock
							weaponHeldText = "Hemlock";
							weaponHeldColor = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
						}
						if (weaponHeldID == 90)
						{ // Flatline
							weaponHeldText = "Flatline";
							weaponHeldColor = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
						}
						// Energy Weapons
						if (weaponHeldID == 115)
						{ // Nemesis
							weaponHeldText = "Nemesis";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						if (weaponHeldID == 112)
						{ // Volt
							weaponHeldText = "Volt";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						if (weaponHeldID == 109)
						{ // TripleTake
							weaponHeldText = "Triple Take";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						if (weaponHeldID == 95)
						{ // LSTAR
							weaponHeldText = "L-STAR";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						if (weaponHeldID == 85)
						{ // Devotion
							weaponHeldText = "Devotion";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						if (weaponHeldID == 87)
						{ // Havoc
							weaponHeldText = "Havoc";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						// Shotguns
						if (weaponHeldID == 98)
						{ // Mozambique
							weaponHeldText = "Mozambique";
							weaponHeldColor = ImColor(Features::Colors::Enemy::ShotgunWeaponColor[0], Features::Colors::Enemy::ShotgunWeaponColor[1], Features::Colors::Enemy::ShotgunWeaponColor[2], Features::Colors::Enemy::ShotgunWeaponColor[3]);
						}
						if (weaponHeldID == 89)
						{ // EVA8
							weaponHeldText = "EVA-8 Auto";
							weaponHeldColor = ImColor(Features::Colors::Enemy::ShotgunWeaponColor[0], Features::Colors::Enemy::ShotgunWeaponColor[1], Features::Colors::Enemy::ShotgunWeaponColor[2], Features::Colors::Enemy::ShotgunWeaponColor[3]);
						}
						if (weaponHeldID == 105)
						{ // Peacekeeper
							weaponHeldText = "Peacekeeper";
							weaponHeldColor = ImColor(Features::Colors::Enemy::ShotgunWeaponColor[0], Features::Colors::Enemy::ShotgunWeaponColor[1], Features::Colors::Enemy::ShotgunWeaponColor[2], Features::Colors::Enemy::ShotgunWeaponColor[3]);
						}
						if (weaponHeldID == 97)
						{ // Mastiff
							weaponHeldText = "Mastiff";
							weaponHeldColor = ImColor(Features::Colors::Enemy::ShotgunWeaponColor[0], Features::Colors::Enemy::ShotgunWeaponColor[1], Features::Colors::Enemy::ShotgunWeaponColor[2], Features::Colors::Enemy::ShotgunWeaponColor[3]);
						}
						// Snipers
						if (weaponHeldID == 1)
						{ // Sentinel
							weaponHeldText = "Sentinel";
							weaponHeldColor = ImColor(Features::Colors::Enemy::SniperWeaponColor[0], Features::Colors::Enemy::SniperWeaponColor[1], Features::Colors::Enemy::SniperWeaponColor[2], Features::Colors::Enemy::SniperWeaponColor[3]);
						}
						if (weaponHeldID == 84)
						{ // ChargeRifle
							weaponHeldText = "Charge Rifle";
							weaponHeldColor = ImColor(Features::Colors::Enemy::SniperWeaponColor[0], Features::Colors::Enemy::SniperWeaponColor[1], Features::Colors::Enemy::SniperWeaponColor[2], Features::Colors::Enemy::SniperWeaponColor[3]);
						}
						if (weaponHeldID == 86)
						{ // Longbow
							weaponHeldText = "Longbow";
							weaponHeldColor = ImColor(Features::Colors::Enemy::SniperWeaponColor[0], Features::Colors::Enemy::SniperWeaponColor[1], Features::Colors::Enemy::SniperWeaponColor[2], Features::Colors::Enemy::SniperWeaponColor[3]);
						}
						// Legendary Weapons
						if (weaponHeldID == 111)
						{ // Wingman
							weaponHeldText = "Wingman";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}
						if (weaponHeldID == 103)
						{ // Prowler
							weaponHeldText = "Prowler";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}
						if (weaponHeldID == 2)
						{ // Bocek
							weaponHeldText = "Bocek";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}
						if (weaponHeldID == 94)
						{ // Kraber
							weaponHeldText = "Kraber";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}
						if (weaponHeldID == 169)
						{ // Knife
							weaponHeldText = "Throwing Knife";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}
						/*if (weaponHeldID == 3) { //BusterSword
							weaponHeldText = "Buster Sword";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}*/
						// Melee & Grenade
						/*if (weaponHeldID == 213) { //Thermite Grenade
							weaponHeldText = "Thermite Grenade";
							weaponHeldColor = ThrowableWeaponColor;
						}*/
						if (p->IsHoldingGrenade)
						{
							weaponHeldText = "Throwable";
							weaponHeldColor = ImColor(Features::Colors::Enemy::ThrowableWeaponColor[0], Features::Colors::Enemy::ThrowableWeaponColor[1], Features::Colors::Enemy::ThrowableWeaponColor[2], Features::Colors::Enemy::ThrowableWeaponColor[3]);
						}
						if (weaponHeldID == 116)
						{ // Melee
							weaponHeldText = "Melee";
							weaponHeldColor = ImColor(Features::Colors::Enemy::MeleeWeaponColor[0], Features::Colors::Enemy::MeleeWeaponColor[1], Features::Colors::Enemy::MeleeWeaponColor[2], Features::Colors::Enemy::MeleeWeaponColor[3]);
						}

						if (Features::Colors::WeaponColorMode == 1)
						{ // Changes color to ammo type
							Renderer::DrawText(Canvas, WeaponPosition, weaponHeldText, ImColor(weaponHeldColor), Features::Sense::TextOutline ? true : false, true, false);
						}

						if (Features::Colors::WeaponColorMode == 0)
						{ // Single Color
							Renderer::DrawText(Canvas, WeaponPosition, weaponHeldText, ImColor(EnemyWeaponColor), Features::Sense::TextOutline ? true : false, true, false);
						}
					}

					/*bool TestWeaponID = false; //For finding weapon IDs (Used for finding melee ID)
					if (TestWeaponID && bLocalOriginW2SValid && bHeadPositionW2SValid) {
						if (p->IsHostile) {
							std::stringstream wepID;
							wepID << p->WeaponIndex;
							std::string wepInt = wepID.str() + " ";
							const char* wepText = (char*)wepInt.c_str();

							ImColor weaponWHeldColor;
							weaponWHeldColor = ImColor(255, 255, 255);

							Renderer::DrawText(Canvas, LocalOriginW2S.Add(Vector2D(0, 0)), wepText, ImColor(weaponWHeldColor), true, true, false);
						}
					}*/

					// Draw Boxes
					if (Features::Sense::Enemy::DrawBoxes && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						Renderer::Draw2DBox(Canvas, Features::Sense::Enemy::BoxType, Features::Sense::Enemy::BoxStyle, LocalOriginW2S, HeadPositionW2S, ImColor(EnemyBoxColor), ImColor(EnemyFilledBoxColor), Features::Sense::Enemy::BoxThickness);
					}

					// Draw Skeleton
					if (Features::Sense::Enemy::DrawSkeleton && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{

						Vector2D Neck, UpperChest, LowerChest, Stomach, Leftshoulder, Leftelbow, LeftHand, Rightshoulder, RightelbowBone, RightHand, LeftThighs, Leftknees, Leftleg, RightThighs, Rightknees, Rightleg;
						// Head bone is HeadPositionW2S
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Neck), Neck);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::UpperChest), UpperChest);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LowerChest), LowerChest);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Stomach), Stomach);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftshoulder), Leftshoulder);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftelbow), Leftelbow);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LeftHand), LeftHand);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightshoulder), Rightshoulder);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightelbowBone), RightelbowBone);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightHand), RightHand);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LeftThighs), LeftThighs);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftknees), Leftknees);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftleg), Leftleg);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightThighs), RightThighs);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightknees), Rightknees);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightleg), Rightleg);

						Renderer::DrawLine(Canvas, HeadPositionW2S, Neck, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Neck, UpperChest, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, LowerChest, Stomach, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Stomach, RightThighs, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, Features::Sense::Enemy::SkeletonThickness, ImColor(EnemySkeletonColor));
					}

					// Draw Head Circle
					if (Features::Sense::Enemy::DrawHeadCircle && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{

						Vector2D HeadPos2D;
						Vector3D HeadPos3D = p->GetBonePosition(HitboxType::Head);
						HeadPos3D.z += 3.f;

						GameCamera->WorldToScreen(HeadPos3D, HeadPos2D);

						Renderer::DrawCircle(Canvas, HeadPos2D, 3650 / p->DistanceToLocalPlayer, 255, ImColor(EnemyHeadCircleColor), Features::Sense::Enemy::HeadCircleThickness);
					}

					// Seer
					if (Features::Sense::Enemy::DrawSeer && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						if (!HeadPositionW2S.IsZeroVector())
							Renderer::DrawSeer(Canvas, HeadPositionW2S.x, HeadPositionW2S.y - 20, p->Shield, p->MaxShield, p->Health);
					}
				}

				// Team ESP
				if (Features::Sense::Teammate::DrawTeam && !p->IsLocal && p->IsAlly && p->IsCombatReady() && p->DistanceToLocalPlayer < (Conversion::ToGameUnits(Features::Sense::ESPMaxDistance)))
				{
					// Draw Warning Text - Spectators
					if (Features::Sense::DrawSpectatorWarning && TotalSpectators >= 1)
					{
						std::stringstream WarningTextStart, Space1, Amount, Space2;
						WarningTextStart << "SPECTATOR WARNING";
						Space1 << " [";
						Amount << TotalSpectators;
						Space2 << "]";
						std::string combined = WarningTextStart.str() + Space1.str() + Amount.str() + Space2.str();
						const char *CombinedText = combined.c_str();

						int TextPosX = Features::Sense::WarningTextX;
						int TextPosY = Features::Sense::WarningTextY - 12;
						Renderer::DrawText(Canvas, Vector2D(TextPosX, TextPosY), CombinedText, ImColor(Features::Colors::SpectatorWarningColor[0], Features::Colors::SpectatorWarningColor[1], Features::Colors::SpectatorWarningColor[2], Features::Colors::SpectatorWarningColor[3]), Features::Sense::WarningTextOutline ? true : false, true, false);
					}

					// Draw Info Bars
					if (Features::Sense::Teammate::DrawBars && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						int health = p->Health;
						int maxHealth = p->MaxHealth;
						int shield = p->Shield;
						int maxShield = p->MaxShield;

						Renderer::Draw2DBar(Canvas, Features::Sense::Enemy::BarMode, Features::Sense::Enemy::BarStyle, Features::Sense::Enemy::BarColorMode, LocalOriginW2S, HeadPositionW2S, AboveHeadW2S, health, maxHealth, shield, maxShield, Features::Sense::Enemy::BarThickness, Features::Sense::Enemy::BarThickness2, Features::Sense::Enemy::BarWidth, Features::Sense::Enemy::BarHeight);
					}

					if (Features::Sense::Teammate::DrawTracers)
					{
						// Tracers
						Vector2D chestScreenPosition;
						if (Features::Sense::Teammate::TracerBone == 0)
						{
							GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 66)), chestScreenPosition);
						}
						else if (Features::Sense::Teammate::TracerBone == 1)
						{
							GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), chestScreenPosition);
						}

						if (Features::Sense::Teammate::TracerPosition == 0) // top to head
						{
							if (!chestScreenPosition.IsZeroVector())
							{
								int x = (int)(ScreenWidth * 0.5f);

								Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, Features::Sense::Teammate::TracerThickness, ImColor(TeammateTracerColor));
							}
						}

						else if (Features::Sense::Teammate::TracerPosition == 1) // middle to bottom
						{
							if (!chestScreenPosition.IsZeroVector())
							{
								int x = (int)(ScreenWidth * 0.5f);

								Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, Features::Sense::Teammate::TracerThickness, ImColor(TeammateTracerColor));
							}
						}

						else if (Features::Sense::Teammate::TracerPosition == 2) // bottom to bottom
						{
							if (!chestScreenPosition.IsZeroVector())
							{
								int x = (int)(ScreenWidth * 0.5f);

								Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, Features::Sense::Teammate::TracerThickness, ImColor(TeammateTracerColor));
							}
						}
					}

					// Distance
					if (Features::Sense::Teammate::DrawDistance && !Features::Sense::Teammate::DrawNames && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						char buffer[256];
						const char *dist = std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str();
						const char *txt = "[";
						const char *txt2 = " M]";
						strncpy(buffer, txt, sizeof(buffer));
						strncat(buffer, dist, sizeof(buffer));
						strncat(buffer, txt2, sizeof(buffer));

						if (!LocalOriginW2S.IsZeroVector())
						{
							Renderer::DrawText(Canvas, DistancePosition, buffer, ImColor(EnemyDistanceColor), Features::Sense::TextOutline ? true : false, true, false);
						}
					}

					// Names Only
					if (!Features::Sense::Teammate::DrawDistance && Features::Sense::Teammate::DrawNames && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						Renderer::DrawText(Canvas, AboveHeadW2S.Subtract(Vector2D(0, 16)), p->GetPlayerName().c_str(), ImColor(TeammateNameColor), Features::Sense::TextOutline ? true : false, true, false);
					}

					// Name & Distance
					if (Features::Sense::Teammate::DrawDistance && Features::Sense::Teammate::DrawNames && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						std::stringstream name, space, dist, txt, txt2;
						name << p->GetPlayerName().c_str();
						space << " ";
						dist << std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str();
						txt << "[";
						txt2 << " M]";
						std::string combined = name.str() + space.str() + txt.str() + dist.str() + txt2.str();
						const char *combinedText = combined.c_str();

						Renderer::DrawText(Canvas, NamePosition, combinedText, ImColor(TeammateNameColor), Features::Sense::TextOutline ? true : false, true, false);
					}

					// Legend
					if (Features::Sense::Teammate::DrawLegend && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						Renderer::DrawText(Canvas, LocalOriginW2S, p->getPlayerModelName().c_str(), ImColor(TeammateLegendColor), Features::Sense::TextOutline ? true : false, true, false);
					}

					// Draw Health + Shield Text
					if (Features::Sense::Teammate::DrawStatus && bLocalOriginW2SValid)
					{
						std::stringstream healthValue, shieldValue, maxHealthValue, maxShieldValue;
						healthValue << p->Health;
						shieldValue << p->Shield;
						maxHealthValue << p->MaxHealth;
						maxShieldValue << p->MaxShield;
						std::string healthInt = healthValue.str() + " HP";
						std::string shieldInt = shieldValue.str() + " AP";
						const char *healthText = (char *)healthInt.c_str();
						const char *shieldText = (char *)shieldInt.c_str();
						std::string combinedHealth = healthValue.str() + " / " + maxHealthValue.str() + " HP";
						const char *combinedHealthText = combinedHealth.c_str();
						std::string combinedShield = shieldValue.str() + " / " + maxShieldValue.str() + " AP";
						const char *combinedShieldText = combinedShield.c_str();

						ImColor ShieldColor;
						if (p->MaxShield == 50)
						{ // white
							ShieldColor = ImColor(247, 247, 247);
						}
						else if (p->MaxShield == 75)
						{ // blue
							ShieldColor = ImColor(39, 178, 255);
						}
						else if (p->MaxShield == 100)
						{ // purple
							ShieldColor = ImColor(206, 59, 255);
						}
						else if (p->MaxShield == 125)
						{ // red
							ShieldColor = ImColor(219, 2, 2);
						}
						else
						{
							ShieldColor = ImColor(247, 247, 247);
						}

						// Render Text
						if (!Features::Sense::Teammate::ShowMaxStatusValues)
						{
							Renderer::DrawText(Canvas, StatusPosition, healthText, ImColor(0, 255, 0), Features::Sense::TextOutline ? true : false, true, false);
							Renderer::DrawText(Canvas, StatusPosition.Add(Vector2D(0, 0 + 10)), shieldText, ShieldColor, Features::Sense::TextOutline ? true : false, true, false);
						}
						if (Features::Sense::Teammate::ShowMaxStatusValues)
						{
							Renderer::DrawText(Canvas, StatusPosition, combinedHealthText, ImColor(0, 255, 0), Features::Sense::TextOutline ? true : false, true, false);
							Renderer::DrawText(Canvas, StatusPosition.Add(Vector2D(0, 0 + 10)), combinedShieldText, ShieldColor, Features::Sense::TextOutline ? true : false, true, false);
						}
					}

					// Weapon ESP
					int weaponHeldID;
					weaponHeldID = p->WeaponIndex;
					const char *weaponHeldText = "Unknown";

					ImColor weaponHeldColor;
					weaponHeldColor = ImColor(255, 255, 255);

					// Draw Weapon
					if (Features::Sense::Teammate::DrawWeapon && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{

						// Light Weapons
						if (weaponHeldID == 107)
						{ // P2020
							weaponHeldText = "P2020";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 82)
						{ // RE-45
							weaponHeldText = "RE-45";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 81)
						{ // Alternator
							weaponHeldText = "Alternator";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 106)
						{ // R-99
							weaponHeldText = "R-99";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 0)
						{ // R-301
							weaponHeldText = "R-301";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 108)
						{ // Spitfire
							weaponHeldText = "Spitfire";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						if (weaponHeldID == 91)
						{ // G7
							weaponHeldText = "G7 Scout";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
						}
						// Heavy Weapons
						if (weaponHeldID == 114)
						{ // CARSMG
							weaponHeldText = "CAR SMG";
							weaponHeldColor = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
						}
						if (weaponHeldID == 6)
						{ // Rampage
							weaponHeldText = "Rampage";
							weaponHeldColor = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
						}
						if (weaponHeldID == 113)
						{ // Repeater
							weaponHeldText = "Repeater";
							weaponHeldColor = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
						}
						if (weaponHeldID == 92)
						{ // Hemlock
							weaponHeldText = "Hemlock";
							weaponHeldColor = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
						}
						if (weaponHeldID == 90)
						{ // Flatline
							weaponHeldText = "Flatline";
							weaponHeldColor = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
						}
						// Energy Weapons
						if (weaponHeldID == 115)
						{ // Nemesis
							weaponHeldText = "Nemesis";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						if (weaponHeldID == 112)
						{ // Volt
							weaponHeldText = "Volt";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						if (weaponHeldID == 109)
						{ // TripleTake
							weaponHeldText = "Triple Take";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						if (weaponHeldID == 95)
						{ // LSTAR
							weaponHeldText = "L-STAR";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						if (weaponHeldID == 85)
						{ // Devotion
							weaponHeldText = "Devotion";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						if (weaponHeldID == 87)
						{ // Havoc
							weaponHeldText = "Havoc";
							weaponHeldColor = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
						}
						// Shotguns
						if (weaponHeldID == 98)
						{ // Mozambique
							weaponHeldText = "Mozambique";
							weaponHeldColor = ImColor(Features::Colors::Enemy::ShotgunWeaponColor[0], Features::Colors::Enemy::ShotgunWeaponColor[1], Features::Colors::Enemy::ShotgunWeaponColor[2], Features::Colors::Enemy::ShotgunWeaponColor[3]);
						}
						if (weaponHeldID == 89)
						{ // EVA8
							weaponHeldText = "EVA-8 Auto";
							weaponHeldColor = ImColor(Features::Colors::Enemy::ShotgunWeaponColor[0], Features::Colors::Enemy::ShotgunWeaponColor[1], Features::Colors::Enemy::ShotgunWeaponColor[2], Features::Colors::Enemy::ShotgunWeaponColor[3]);
						}
						if (weaponHeldID == 105)
						{ // Peacekeeper
							weaponHeldText = "Peacekeeper";
							weaponHeldColor = ImColor(Features::Colors::Enemy::ShotgunWeaponColor[0], Features::Colors::Enemy::ShotgunWeaponColor[1], Features::Colors::Enemy::ShotgunWeaponColor[2], Features::Colors::Enemy::ShotgunWeaponColor[3]);
						}
						if (weaponHeldID == 97)
						{ // Mastiff
							weaponHeldText = "Mastiff";
							weaponHeldColor = ImColor(Features::Colors::Enemy::ShotgunWeaponColor[0], Features::Colors::Enemy::ShotgunWeaponColor[1], Features::Colors::Enemy::ShotgunWeaponColor[2], Features::Colors::Enemy::ShotgunWeaponColor[3]);
						}
						// Snipers
						if (weaponHeldID == 1)
						{ // Sentinel
							weaponHeldText = "Sentinel";
							weaponHeldColor = ImColor(Features::Colors::Enemy::SniperWeaponColor[0], Features::Colors::Enemy::SniperWeaponColor[1], Features::Colors::Enemy::SniperWeaponColor[2], Features::Colors::Enemy::SniperWeaponColor[3]);
						}
						if (weaponHeldID == 84)
						{ // ChargeRifle
							weaponHeldText = "Charge Rifle";
							weaponHeldColor = ImColor(Features::Colors::Enemy::SniperWeaponColor[0], Features::Colors::Enemy::SniperWeaponColor[1], Features::Colors::Enemy::SniperWeaponColor[2], Features::Colors::Enemy::SniperWeaponColor[3]);
						}
						if (weaponHeldID == 86)
						{ // Longbow
							weaponHeldText = "Longbow";
							weaponHeldColor = ImColor(Features::Colors::Enemy::SniperWeaponColor[0], Features::Colors::Enemy::SniperWeaponColor[1], Features::Colors::Enemy::SniperWeaponColor[2], Features::Colors::Enemy::SniperWeaponColor[3]);
						}
						// Legendary Weapons
						if (weaponHeldID == 111)
						{ // Wingman
							weaponHeldText = "Wingman";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}
						if (weaponHeldID == 103)
						{ // Prowler
							weaponHeldText = "Prowler";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}
						if (weaponHeldID == 2)
						{ // Bocek
							weaponHeldText = "Bocek";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}
						if (weaponHeldID == 94)
						{ // Kraber
							weaponHeldText = "Kraber";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}
						if (weaponHeldID == 169)
						{ // Knife
							weaponHeldText = "Throwing Knife";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}
						/*if (weaponHeldID == 3) { //BusterSword
							weaponHeldText = "Buster Sword";
							weaponHeldColor = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
						}*/
						// Melee & Grenade
						/*if (weaponHeldID == 213) { //Thermite Grenade
							weaponHeldText = "Thermite Grenade";
							weaponHeldColor = ThrowableWeaponColor;
						}*/
						if (p->IsHoldingGrenade)
						{
							weaponHeldText = "Throwable";
							weaponHeldColor = ImColor(Features::Colors::Enemy::ThrowableWeaponColor[0], Features::Colors::Enemy::ThrowableWeaponColor[1], Features::Colors::Enemy::ThrowableWeaponColor[2], Features::Colors::Enemy::ThrowableWeaponColor[3]);
						}
						if (weaponHeldID == 116)
						{ // Melee
							weaponHeldText = "Melee";
							weaponHeldColor = ImColor(Features::Colors::Enemy::MeleeWeaponColor[0], Features::Colors::Enemy::MeleeWeaponColor[1], Features::Colors::Enemy::MeleeWeaponColor[2], Features::Colors::Enemy::MeleeWeaponColor[3]);
						}

						if (Features::Colors::WeaponColorMode == 1)
						{ // Changes color to ammo type
							Renderer::DrawText(Canvas, WeaponPosition, weaponHeldText, ImColor(weaponHeldColor), Features::Sense::TextOutline ? true : false, true, false);
						}

						if (Features::Colors::WeaponColorMode == 0)
						{ // Single Color
							Renderer::DrawText(Canvas, WeaponPosition, weaponHeldText, ImColor(TeammateWeaponColor), Features::Sense::TextOutline ? true : false, true, false);
						}
					}

					/*bool TestWeaponID = false; //For finding weapon IDs (Used for finding melee ID)
					if (TestWeaponID && bLocalOriginW2SValid && bHeadPositionW2SValid) {
						if (p->IsHostile) {
							std::stringstream wepID;
							wepID << p->WeaponIndex;
							std::string wepInt = wepID.str() + " ";
							const char* wepText = (char*)wepInt.c_str();

							ImColor weaponWHeldColor;
							weaponWHeldColor = ImColor(255, 255, 255);

							Renderer::DrawText(Canvas, LocalOriginW2S.Add(Vector2D(0, 0)), wepText, ImColor(weaponWHeldColor), true, true, false);
						}
					}*/

					// Draw Boxes
					if (Features::Sense::Teammate::DrawBoxes && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						Renderer::Draw2DBox(Canvas, Features::Sense::Teammate::BoxType, Features::Sense::Teammate::BoxStyle, LocalOriginW2S, HeadPositionW2S, ImColor(TeammateBoxColor), ImColor(TeammateFilledBoxColor), Features::Sense::Teammate::BoxThickness);
					}

					// Draw Skeleton
					if (Features::Sense::Teammate::DrawSkeleton && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{

						Vector2D Neck, UpperChest, LowerChest, Stomach, Leftshoulder, Leftelbow, LeftHand, Rightshoulder, RightelbowBone, RightHand, LeftThighs, Leftknees, Leftleg, RightThighs, Rightknees, Rightleg;
						// Head bone is HeadPositionW2S
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Neck), Neck);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::UpperChest), UpperChest);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LowerChest), LowerChest);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Stomach), Stomach);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftshoulder), Leftshoulder);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftelbow), Leftelbow);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LeftHand), LeftHand);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightshoulder), Rightshoulder);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightelbowBone), RightelbowBone);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightHand), RightHand);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LeftThighs), LeftThighs);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftknees), Leftknees);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftleg), Leftleg);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightThighs), RightThighs);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightknees), Rightknees);
						GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightleg), Rightleg);

						Renderer::DrawLine(Canvas, HeadPositionW2S, Neck, Features::Sense::Teammate::SkeletonThickness, ImColor(TeammateSkeletonColor));
						Renderer::DrawLine(Canvas, Neck, UpperChest, Features::Sense::Teammate::SkeletonThickness, ImColor(TeammateSkeletonColor));
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, Features::Sense::Teammate::SkeletonThickness, ImColor(TeammateSkeletonColor));
						Renderer::DrawLine(Canvas, LowerChest, Stomach, Features::Sense::Teammate::SkeletonThickness, ImColor(TeammateSkeletonColor));
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, Features::Sense::Teammate::SkeletonThickness, ImColor(TeammateSkeletonColor));
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, Features::Sense::Teammate::SkeletonThickness, ImColor(TeammateSkeletonColor));
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, Features::Sense::Teammate::SkeletonThickness, ImColor(TeammateSkeletonColor));
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, Features::Sense::Teammate::SkeletonThickness, ImColor(TeammateSkeletonColor));
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, Features::Sense::Teammate::SkeletonThickness, ImColor(TeammateSkeletonColor));
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, Features::Sense::Teammate::SkeletonThickness, ImColor(TeammateSkeletonColor));
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, Features::Sense::Teammate::SkeletonThickness, ImColor(TeammateSkeletonColor));
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, Features::Sense::Teammate::SkeletonThickness, ImColor(TeammateSkeletonColor));
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, Features::Sense::Teammate::SkeletonThickness, ImColor(TeammateSkeletonColor));
						Renderer::DrawLine(Canvas, Stomach, RightThighs, Features::Sense::Teammate::SkeletonThickness, ImColor(TeammateSkeletonColor));
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, Features::Sense::Teammate::SkeletonThickness, ImColor(TeammateSkeletonColor));
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, Features::Sense::Teammate::SkeletonThickness, ImColor(TeammateSkeletonColor));
					}

					// Draw Head Circle
					if (Features::Sense::Teammate::DrawHeadCircle && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{

						Vector2D HeadPos2D;
						Vector3D HeadPos3D = p->GetBonePosition(HitboxType::Head);
						HeadPos3D.z += 3.f;

						GameCamera->WorldToScreen(HeadPos3D, HeadPos2D);

						Renderer::DrawCircle(Canvas, HeadPos2D, 3650 / p->DistanceToLocalPlayer, 255, ImColor(TeammateHeadCircleColor), Features::Sense::Teammate::HeadCircleThickness);
					}

					// Seer
					if (Features::Sense::Teammate::DrawSeer && bLocalOriginW2SValid && bHeadPositionW2SValid)
					{
						if (!HeadPositionW2S.IsZeroVector())
							Renderer::DrawSeer(Canvas, HeadPositionW2S.x, HeadPositionW2S.y - 20, p->Shield, p->MaxShield, p->Health);
					}
				}
			}
		}
	}
};