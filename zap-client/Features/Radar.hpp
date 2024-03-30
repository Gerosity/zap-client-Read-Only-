#pragma once
#include <iostream>
#include <vector>
#include <iostream>
#include <vector>

#include "../Core/Player.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"

#include "../Math/Vector2D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Math/QAngle.hpp"
#include "../Math/Resolver.hpp"

#include "../Utils/Memory.hpp"
#include "../Utils/XDisplay.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/HitboxType.hpp"
#include "../Utils/InputManager.hpp"
#include "../Utils/InputTypes.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "../Overlay/Overlay.hpp"
#include "../Overlay/Renderer.hpp"

// Geometry
#define DEG2RAD(x) ((float)(x) * (float)(M_PI / 180.f))

struct Radar
{

	XDisplay *X11Display;
	Camera *GameCamera;
	Level *m_level;
	LocalPlayer *Myself;
	std::vector<Player *> *Players;
	std::chrono::milliseconds LastUpdateTime;

	Radar(XDisplay *X11Display, std::vector<Player *> *Players, Camera *GameCamera, Level *level, LocalPlayer *localplayer)
	{
		this->X11Display = X11Display;
		this->Players = Players;
		this->GameCamera = GameCamera;
		this->m_level = level;
		this->Myself = localplayer;
	}

	bool Save()
	{
		try
		{
			Config::Radar::MiniMap = Features::Radar::MiniMap;
			Config::Radar::MiniMapRange = Features::Radar::MiniMapRange;
			Config::Radar::MiniMapScaleX = Features::Radar::MiniMapScaleX;
			Config::Radar::MiniMapScaleY = Features::Radar::MiniMapScaleY;
			Config::Radar::MiniMapDotSize = Features::Radar::MiniMapDotSize;
			Config::Radar::MiniMapBlackBGSize = Features::Radar::MiniMapBlackBGSize;
			Config::Radar::MiniMapGuides = Features::Radar::MiniMapGuides;
			Config::Radar::BigMap = Features::Radar::BigMap;
			Config::Radar::BigMapBind = static_cast<int>(Features::Radar::BigMapBind);
			Config::Radar::CircleColorR = Features::Radar::CircleColor[0];
			Config::Radar::CircleColorG = Features::Radar::CircleColor[0];
			Config::Radar::CircleColorB = Features::Radar::CircleColor[0];
			Config::Radar::CircleColorA = Features::Radar::CircleColor[0];

			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	void RenderDrawings(ImDrawList *Canvas, LocalPlayer *Myself, Overlay OverlayWindow)
	{
		int ScreenWidth;
		int ScreenHeight;
		OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);
		if (!m_level->IsPlayable)
			return;

		if (Features::Radar::MiniMap)
		{
			ImVec2 Center = ImGui::GetMainViewport()->GetCenter();
			ImGui::SetNextWindowPos(ImVec2(0.0f, Center.y), ImGuiCond_Once, ImVec2(0.02f, 0.5f));

			ImGui::Begin(("Radar"), (bool *)true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);

			for (auto i = 0; i < Players->size(); i++)
			{
				Player *p = Players->at(i);
				if (!p->IsHostile || !p->IsValid() || Myself->BasePointer == p->BasePointer)
					continue;

				float radardistance = (int)((Myself->LocalOrigin, p->Distance2DToLocalPlayer) / 39.62);

				MiniMapRadar(p->LocalOrigin, Myself->LocalOrigin, p->ViewAngles.y, radardistance, p->Team, p->ViewYaw);
			}
			ImGui::End();
		}
	}

	// DRAW RADAR POINT mini Map
	void DrawRadarPointMiniMap(Vector3D EnemyPos, Vector3D LocalPos, float targetY, float enemyDist, int TeamID, int xAxis, int yAxis, int width, int height, ImColor color, float targetyaw)
	{
		bool out = false;
		Vector3D siz;
		siz.x = width;
		siz.y = height;
		Vector3D pos;
		pos.x = xAxis;
		pos.y = yAxis;
		bool ck = false;

		Vector3D single = Renderer::RotatePoint(EnemyPos, LocalPos, pos.x, pos.y, siz.x, siz.y, targetY, 0.3f, &ck);
		if (enemyDist >= 0.f && enemyDist < Features::Radar::MiniMapRange)
		{
			for (int i = 1; i <= 30; i++)
			{
				Renderer::TeamMiniMap(single.x, single.y, Features::Radar::MiniMapDotSize, TeamID, targetyaw, Features::Radar::MiniMapDotSize, Features::Radar::MiniMapBlackBGSize, ImColor(Features::Radar::CircleColor[0], Features::Radar::CircleColor[1], Features::Radar::CircleColor[2], Features::Radar::CircleColor[3]));
			}
		}
	}

	// MINI MAP RADAR IMPLEMENTATION
	void MiniMapRadar(Vector3D EnemyPos, Vector3D LocalPos, float targetY, float eneamyDist, int TeamId, float targetyaw)
	{
		/*ImGuiStyle* style = &ImGui::GetStyle();
		style->WindowRounding = 0.2f;
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.13529413f, 0.14705884f, 0.15490198f, 0.82f));*/
		ImGuiWindowFlags TargetFlags;
		TargetFlags = ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar;
		if (Features::Radar::MiniMap)
		{
			// 1920*1080: 215 x 215
			// 2560*1440: 335 x 335
			ImGui::SetNextWindowSize({Features::Radar::MiniMapScaleX, Features::Radar::MiniMapScaleY});
			ImGui::Begin(("##Radar"), 0, TargetFlags);
			{
				ImDrawList *Draw = ImGui::GetWindowDrawList();
				ImVec2 DrawPos = ImGui::GetCursorScreenPos();
				ImVec2 DrawSize = ImGui::GetContentRegionAvail();
				ImVec2 midRadar = ImVec2(DrawPos.x + (DrawSize.x / 2), DrawPos.y + (DrawSize.y / 2));
				if (Features::Radar::MiniMapGuides)
				{
					ImVec2 startHorizontal(midRadar.x - DrawSize.x / 2.f, midRadar.y);
					ImVec2 endHorizontal(midRadar.x + DrawSize.x / 2.f, midRadar.y);
					ImVec2 startVertical(midRadar.x, midRadar.y - DrawSize.y / 2.f);
					ImVec2 endVertical(midRadar.x, midRadar.y + DrawSize.y / 2.f);
					float extension = -500000.f;

					ImGui::GetWindowDrawList()->AddLine(startHorizontal, ImVec2(startHorizontal.x - extension, endHorizontal.y), IM_COL32(255, 255, 255, 255));
					ImGui::GetWindowDrawList()->AddLine(endHorizontal, ImVec2(endHorizontal.x + extension, endHorizontal.y), IM_COL32(255, 255, 255, 255));

					ImGui::GetWindowDrawList()->AddLine(startVertical, ImVec2(startVertical.x, startVertical.y - extension), IM_COL32(255, 255, 255, 255));
					ImGui::GetWindowDrawList()->AddLine(endVertical, ImVec2(endVertical.x, endVertical.y + extension), IM_COL32(255, 255, 255, 255));
				}

				DrawRadarPointMiniMap(EnemyPos, LocalPos, targetY, eneamyDist, TeamId, DrawPos.x, DrawPos.y, DrawSize.x, DrawSize.y, {255, 255, 255, 255}, targetyaw);
			}
			ImGui::End();
		}
	}
};
