// Externals
#include <iostream>
#include <string>
#include <unistd.h>
#include <atomic>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <GLFW/glfw3.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XInput2.h>

// Internals
#include "Core/Level.hpp"
#include "Core/Player.hpp"
#include "Core/LocalPlayer.hpp"
#include "Core/Camera.hpp"

#include "Features/Legitbot.hpp"
#include "Features/Ragebot.hpp"
#include "Features/Sense.hpp"
#include "Features/Radar.hpp"
#include "Features/Triggerbot.hpp"
#include "Features/Misc.hpp"
// #include "Features/Test.hpp"

#include "Overlay/Overlay.hpp"
#include "Overlay/GUI.hpp"

#include "Utils/Config.hpp"
#include "Utils/ConfigManager.hpp"
#include "Utils/Features.hpp"
#include "Utils/Memory.hpp"
#include "Utils/XDisplay.hpp"

// Objects
XDisplay *X11Display = new XDisplay();
Overlay OverlayWindow = Overlay();
ImDrawList *Canvas;

// Game Objects
Level *Map = new Level();
LocalPlayer *Myself = new LocalPlayer();
Camera *GameCamera = new Camera();

// Players
std::vector<Player *> *HumanPlayers = new std::vector<Player *>;
std::vector<Player *> *Dummies = new std::vector<Player *>;
std::vector<Player *> *Players = new std::vector<Player *>;

// Features
Sense *ESP = new Sense(Map, Players, GameCamera, Myself, X11Display);
Radar *MapRadar = new Radar(X11Display, Players, GameCamera, Map, Myself);
Legitbot *Legit = new Legitbot(X11Display, Map, Myself, Players);
Ragebot *Rage = new Ragebot(X11Display, Map, Myself, Players);
Triggerbot *Trigger = new Triggerbot(X11Display, Map, Myself, Players);
Misc *MiscTab = new Misc(X11Display, Map, Myself, Players);
// Test* Testing = new Test(X11Display, Map, Myself);
Overlay *Home = new Overlay;
AdvancedGUI *Advanced = new AdvancedGUI;
Menu *GUI = new Menu(Myself, Advanced);
ConfigManager *Configs = new ConfigManager(Legit, Rage, Trigger, ESP, MapRadar, MiscTab);

// Booleans and Variables
bool IsMenuOpened = true;

// Thread
std::atomic_bool StopThread(false);

// Inputs
void HandleKeyEvent(Display *display, XEvent *Event)
{
    if (Event->type == KeyPress)
    {
        if (IsMenuOpened)
        {
            IsMenuOpened = false;
            Features::Home::IsMenuOpened = false;
            OverlayWindow.CaptureInput(false);
        }
        else
        {
            IsMenuOpened = true;
            Features::Home::IsMenuOpened = true;
            OverlayWindow.CaptureInput(true);
        }
    }
}

void X11EventListener()
{
    Display *display = XOpenDisplay(nullptr);
    Window root = DefaultRootWindow(display);
    XGrabKey(display, XKeysymToKeycode(display, XK_Insert), AnyModifier, root, False, GrabModeAsync, GrabModeAsync);
    XEvent event;
    while (!StopThread)
    {
        XNextEvent(display, &event);
        HandleKeyEvent(display, &event);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    XCloseDisplay(display);
}

// Overlay
bool InitializeOverlayWindow()
{
    if (!OverlayWindow.InitializeOverlay())
    {
        OverlayWindow.DestroyOverlay();
        return false;
    }
    int ScreenWidth;
    int ScreenHeight;
    OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);
    GameCamera->Initialize(ScreenWidth, ScreenHeight);
    std::cout << "overlay initialized" << std::endl;
    return true;
}

// Interface
ImVec4 ProcessingTimeColor;

void RenderUI()
{
    auto io = ImGui::GetIO();
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("##Overlay", nullptr,
                 ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoScrollbar |
                     ImGuiWindowFlags_NoSavedSettings |
                     ImGuiWindowFlags_NoInputs |
                     ImGuiWindowFlags_NoBackground |
                     ImGuiSliderFlags_AlwaysClamp);
    Canvas = ImGui::GetWindowDrawList();
    // if (Map->IsPlayable)
    MapRadar->RenderDrawings(Canvas, Myself, OverlayWindow);
    ESP->RenderWatermark(Canvas, Myself, OverlayWindow);
    ESP->RenderDrawings(Canvas, Legit, Myself, OverlayWindow);
    ImGui::End();

    if (!Features::Home::IsMenuOpened)
        return;

    ImDrawList *DrawList = ImGui::GetBackgroundDrawList();
    ImColor OverlayRender = ImColor(1.0f, 1.0f, 1.0f, 0.6f);
    ImColor SolidRender = ImColor(1.0f, 1.0f, 1.0f, 1.0f);
    GUI->SetStyle();
    // GUI->RenderBaseMenu();
    /*if (ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
        ImGui::GetStyle().Alpha = 0.75f;
    }
    else if (!ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
        ImGui::GetStyle().Alpha = 1.00f;
    }*/

    // Window Size
    ImGui::SetNextWindowSizeConstraints(ImVec2(GUI->WindowWidth, GUI->WindowHeight), ImVec2(GUI->WindowWidth, GUI->WindowHeight));
    ImGui::SetNextWindowSize(ImVec2(GUI->WindowWidth, GUI->WindowHeight), ImGuiCond_FirstUseEver);

    // Setup flags and begin window
    if (ImGui::Begin("##CheatGUI", &Features::Home::IsMenuOpened, GUI->WindowFlags))
    {
        // Setup "MenuSize" so that we can calculate control positions
        ImVec2 MenuSize = ImGui::GetWindowSize();
        // Render Left Panel
        ImGui::SetCursorPos(ImVec2(10, 32));

        ImVec4 *colors = ImGui::GetStyle().Colors;

        colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        if (ImGui::BeginChild("##LeftPanel", ImVec2(GUI->WindowWidth / 6 - 5, GUI->WindowHeight - 43), true, ImGuiWindowFlags_NoScrollbar))
        {
            colors[ImGuiCol_Border] = colors[ImGuiCol_Border];
            // Color the background of the tab button brighter if it is the active tab
            ImVec4 *colors = ImGui::GetStyle().Colors;
            ImVec4 TabButton1 = GUI->DetailColor;
            ImVec4 TabButton2 = GUI->DetailColor;
            ImVec4 TabButton3 = GUI->DetailColor;
            ImVec4 TabButton4 = GUI->DetailColor;
            ImVec4 TabButton5 = GUI->DetailColor;
            ImVec4 TabButton6 = GUI->DetailColor;
            ImVec4 TabButton7 = GUI->DetailColor;
            ImVec4 TabButton8 = GUI->DetailColor;
            ImVec4 TabButton9 = GUI->DetailColor;
            TabButton1.w = 0.00f;
            TabButton2.w = 0.00f;
            TabButton3.w = 0.00f;
            TabButton4.w = 0.00f;
            TabButton5.w = 0.00f;
            TabButton6.w = 0.00f;
            TabButton7.w = 0.00f;
            TabButton8.w = 0.00f;
            TabButton9.w = 0.00f;
            ImVec4 TabButton1Hovered = ImVec4(GUI->DetailColor.x, GUI->DetailColor.y, GUI->DetailColor.z, GUI->DetailColor.w - 0.50f);
            ImVec4 TabButton2Hovered = ImVec4(GUI->DetailColor.x, GUI->DetailColor.y, GUI->DetailColor.z, GUI->DetailColor.w - 0.50f);
            ;
            ImVec4 TabButton3Hovered = ImVec4(GUI->DetailColor.x, GUI->DetailColor.y, GUI->DetailColor.z, GUI->DetailColor.w - 0.50f);
            ;
            ImVec4 TabButton4Hovered = ImVec4(GUI->DetailColor.x, GUI->DetailColor.y, GUI->DetailColor.z, GUI->DetailColor.w - 0.50f);
            ;
            ImVec4 TabButton5Hovered = ImVec4(GUI->DetailColor.x, GUI->DetailColor.y, GUI->DetailColor.z, GUI->DetailColor.w - 0.50f);
            ;
            ImVec4 TabButton6Hovered = ImVec4(GUI->DetailColor.x, GUI->DetailColor.y, GUI->DetailColor.z, GUI->DetailColor.w - 0.50f);
            ;
            ImVec4 TabButton7Hovered = ImVec4(GUI->DetailColor.x, GUI->DetailColor.y, GUI->DetailColor.z, GUI->DetailColor.w - 0.50f);
            ;
            ImVec4 TabButton8Hovered = ImVec4(GUI->DetailColor.x, GUI->DetailColor.y, GUI->DetailColor.z, GUI->DetailColor.w - 0.50f);
            ;
            ImVec4 TabButton9Hovered = ImVec4(GUI->DetailColor.x, GUI->DetailColor.y, GUI->DetailColor.z, GUI->DetailColor.w - 0.50f);
            ;
            TabButton1Hovered.w = 0.250f;
            TabButton2Hovered.w = 0.250f;
            TabButton3Hovered.w = 0.250f;
            TabButton4Hovered.w = 0.250f;
            TabButton5Hovered.w = 0.250f;
            TabButton6Hovered.w = 0.250f;
            TabButton7Hovered.w = 0.250f;
            TabButton8Hovered.w = 0.250f;
            TabButton9Hovered.w = 0.250f;
            ImVec4 TabButton1Text = GUI->SelectedColor;
            ImVec4 TabButton2Text = GUI->SelectedColor;
            ImVec4 TabButton3Text = GUI->SelectedColor;
            ImVec4 TabButton4Text = GUI->SelectedColor;
            ImVec4 TabButton5Text = GUI->SelectedColor;
            ImVec4 TabButton6Text = GUI->SelectedColor;
            ImVec4 TabButton7Text = GUI->SelectedColor;
            ImVec4 TabButton8Text = GUI->SelectedColor;
            ImVec4 TabButton9Text = GUI->SelectedColor;
            switch (GUI->CurrentTab)
            {
            case GUI->MenuTabs::Legitbot:
                TabButton1.w = 0.25f;
                TabButton1Hovered.w = GUI->DetailColor.w - 0.50f;
                TabButton1Text = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                break;
            case GUI->MenuTabs::Ragebot:
                TabButton2.w = 0.25f;
                TabButton2Hovered.w = GUI->DetailColor.w - 0.50f;
                TabButton2Text = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                break;
            case GUI->MenuTabs::Triggerbot:
                TabButton4.w = 0.25f;
                TabButton4Hovered.w = GUI->DetailColor.w - 0.50f;
                TabButton4Text = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                break;
            case GUI->MenuTabs::ESP:
                TabButton6.w = 0.25f;
                TabButton6Hovered.w = GUI->DetailColor.w - 0.50f;
                TabButton6Text = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                break;
            case GUI->MenuTabs::Misc:
                TabButton7.w = 0.25f;
                TabButton7Hovered.w = GUI->DetailColor.w - 0.50f;
                TabButton7Text = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                break;
            case GUI->MenuTabs::Settings:
                TabButton8.w = 0.25f;
                TabButton8Hovered.w = GUI->DetailColor.w - 0.50f;
                TabButton8Text = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                break;
            case GUI->MenuTabs::Config:
                TabButton9.w = 0.25f;
                TabButton9Hovered.w = GUI->DetailColor.w - 0.50f;
                TabButton9Text = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                break;
            }
            ImGuiStyle &Style = ImGui::GetStyle();
            constexpr int ButtonHeight = 43;
            Style.FrameBorderSize = 1;

            colors[ImGuiCol_ButtonHovered] = TabButton1Hovered;
            colors[ImGuiCol_ButtonActive] = TabButton1Hovered;
            colors[ImGuiCol_Button] = TabButton1;
            colors[ImGuiCol_Text] = GUI->TextColor;
            if (ImGui::Button("LEGITBOT", ImVec2(MenuSize.x / 6 - 35, ButtonHeight)))
            {
                GUI->CurrentTab = GUI->MenuTabs::Legitbot;
            }

            colors[ImGuiCol_ButtonHovered] = TabButton2Hovered;
            colors[ImGuiCol_ButtonActive] = TabButton2Hovered;
            colors[ImGuiCol_Button] = TabButton2;
            colors[ImGuiCol_Text] = GUI->TextColor;
            if (ImGui::Button("RAGEBOT", ImVec2(MenuSize.x / 6 - 35, ButtonHeight)))
            {
                GUI->CurrentTab = GUI->MenuTabs::Ragebot;
            }

            colors[ImGuiCol_ButtonHovered] = TabButton4Hovered;
            colors[ImGuiCol_ButtonActive] = TabButton4Hovered;
            colors[ImGuiCol_Button] = TabButton4;
            colors[ImGuiCol_Text] = GUI->TextColor;
            if (ImGui::Button("TRIGGERBOT", ImVec2(MenuSize.x / 6 - 35, ButtonHeight)))
            {
                GUI->CurrentTab = GUI->MenuTabs::Triggerbot;
            }

            colors[ImGuiCol_ButtonHovered] = TabButton6Hovered;
            colors[ImGuiCol_ButtonActive] = TabButton6Hovered;
            colors[ImGuiCol_Button] = TabButton6;
            colors[ImGuiCol_Text] = GUI->TextColor;
            if (ImGui::Button("ESP", ImVec2(MenuSize.x / 6 - 35, ButtonHeight)))
            {
                GUI->CurrentTab = GUI->MenuTabs::ESP;
            }

            colors[ImGuiCol_ButtonHovered] = TabButton7Hovered;
            colors[ImGuiCol_ButtonActive] = TabButton7Hovered;
            colors[ImGuiCol_Button] = TabButton7;
            colors[ImGuiCol_Text] = GUI->TextColor;
            if (ImGui::Button("MISC", ImVec2(MenuSize.x / 6 - 35, ButtonHeight)))
            {
                GUI->CurrentTab = GUI->MenuTabs::Misc;
            }

            colors[ImGuiCol_ButtonHovered] = TabButton8Hovered;
            colors[ImGuiCol_ButtonActive] = TabButton8Hovered;
            colors[ImGuiCol_Button] = TabButton8;
            colors[ImGuiCol_Text] = GUI->TextColor;
            if (ImGui::Button("SETTINGS", ImVec2(MenuSize.x / 6 - 35, ButtonHeight)))
            {
                GUI->CurrentTab = GUI->MenuTabs::Settings;
            }

            colors[ImGuiCol_ButtonHovered] = TabButton9Hovered;
            colors[ImGuiCol_ButtonActive] = TabButton9Hovered;
            colors[ImGuiCol_Button] = TabButton9;
            colors[ImGuiCol_Text] = GUI->TextColor;
            if (ImGui::Button("CONFIGS", ImVec2(MenuSize.x / 6 - 35, ButtonHeight)))
            {
                GUI->CurrentTab = GUI->MenuTabs::Config;
            }

            /*else
            {
                GUI->TripleSpacing();
                GUI->TripleSpacing();
                ImGui::Checkbox("Team Check", &GUI->TeamGamemode);
                if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                    ImGui::SetTooltip("Enable if playing BR, Gun Run or Training\nDisable if playing Control or TDM");
                Features::Home::TeamGamemode = GUI->TeamGamemode;
            }*/

            /*Space(true);
            Space(true);
            Space(true);

            colors[ImGuiCol_Border] = GUI->DetailColor;
            colors[ImGuiCol_ButtonHovered] = TabButton7Hovered;
            colors[ImGuiCol_ButtonActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
            colors[ImGuiCol_Button] = TabButton7;
            colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            if (ImGui::Button("Hide Menu", ImVec2(MenuSize.x / 4 - 35, ButtonHeight))) {
                Features::Home::IsMenuOpened = false;
            }
            Style.FrameBorderSize = 0;
            colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);*/

            ImGui::EndChild();
        }

        std::stringstream TitleText, Date, Time, Version, UnknownCheats, Spacings;
        TitleText << "zap-client";
        Date << OverlayWindow.currentDateTime(2);
        Time << OverlayWindow.currentDateTime(3);
        Version << "Version 1.0.6";
        UnknownCheats << "unknowncheats.me";
        Spacings << "  |  ";
        std::string combined = TitleText.str() + Spacings.str() + Date.str() + Spacings.str() + Time.str() + Spacings.str() + Version.str() + Spacings.str() + UnknownCheats.str();
        const char *combinedText = combined.c_str();

        ImVec2 WindowPosition = ImGui::GetWindowPos();
        int TextPosition = WindowPosition.x + (GUI->WindowWidth / 3);
        ImGui::GetForegroundDrawList()->AddText(ImVec2(TextPosition, WindowPosition.y + 10), ImColor(1.0, 1.0f, 1.0f, 1.0f), combinedText);
        ImGui::GetForegroundDrawList()->AddLine(ImVec2(TextPosition - 5, WindowPosition.y + 23), ImVec2(TextPosition + 346, WindowPosition.y + 23), ImColor(255, 255, 255), 1);

        // Render Right (Main) Panel
        ImGui::SetCursorPos(ImVec2(175, 32));
        colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        if (ImGui::BeginChild("##RightPanel", ImVec2(GUI->WindowWidth - 186, GUI->WindowHeight - 43), true, ImGuiWindowFlags_NoScrollbar))
        {
            colors[ImGuiCol_Border] = GUI->DetailColor;
            // Render Tabs
            switch (GUI->CurrentTab)
            {
            case GUI->MenuTabs::Legitbot:
                GUI->RenderLegitbot();
                break;
            case GUI->MenuTabs::Ragebot:
                GUI->RenderRagebot();
                break;
            case GUI->MenuTabs::Triggerbot:
                GUI->RenderTriggerbot();
                break;
            case GUI->MenuTabs::ESP:
                GUI->RenderESP(OverlayWindow);
                break;
            case GUI->MenuTabs::Misc:
                GUI->RenderMisc();
                break;
            case GUI->MenuTabs::Settings:
                GUI->RenderSettings();
                break;
            case GUI->MenuTabs::Config:
                ImVec2 TabSize;
                TabSize = ImGui::GetWindowSize();
                ImGui::SetCursorPos(ImVec2(0, 0));
                ImGui::BeginChild("workzone", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
                /*ImGui::BeginGroup();
                ImGui::Spacing();
                ImGui::SameLine();
                if (ImGui::SubTab("CONFIGS", 0 == GUI->SelectedConfigSubTab, ImVec2(205, 25)))
                    GUI->SelectedConfigSubTab = 0;
                ImGui::EndGroup();*/
                //SubTab Caused Crashing For Some Reason - Not like its needed anyway

                ImGui::SetCursorPos({15, 15});

                ImGui::BeginChild("workzone", ImVec2(GUI->WindowWidth - 186, GUI->WindowHeight - 60), false, ImGuiWindowFlags_NoScrollbar);

                ImGui::BeginChildFrame(1, ImVec2(GUI->WindowWidth - 220, GUI->WindowHeight - 73), true);
                {
                    GUI->DoubleSpacing();
                    Configs->LoadConfigs();
                    Configs->RenderConfigs();

                    ImGui::EndChildFrame();
                }

                ImGui::EndChild();
                ImGui::EndChild();
                break;
            }
            ImGui::EndChild();
            Legit->UpdateAimList();
            Legit->UpdateRCSList();
            Rage->UpdateRageList();
            Trigger->UpdateWeaponList();
            MiscTab->UpdateRapidFireList();
        }

        // Add Vertical Separator Line
        ImVec2 C = ImGui::GetWindowPos();
        const ImVec2 Point1 = ImVec2(MenuSize.x / 6 + 6.5f + C.x, 32 + C.y);
        const ImVec2 Point2 = ImVec2(MenuSize.x / 6 + 6.5f + C.x, 32 + (MenuSize.y - 43) + C.y);
        ImGui::GetWindowDrawList()->AddLine(Point1, Point2, ImGui::ColorConvertFloat4ToU32(GUI->DetailColor), 1.0f);

        // End Drawlist Calls
        ImGui::End();
    }
}

// Core
bool UpdateCore()
{
    try
    {
        // Map Checking //
        Map->Read();
        if (!Map->IsPlayable)
        {
            return true;
        }

        // Read Local Player //
        Myself->Read();
        if (!Myself->IsValid())
        {
            return true;
        }

        // Populate Players //
        Players->clear();
        if (Map->IsFiringRange)
        {
            for (int i = 0; i < Dummies->size(); i++)
            {
                Player *p = Dummies->at(i);
                p->Read();
                if (p->BasePointer != 0 && (p->IsPlayer() || p->IsDummy()))
                    Players->push_back(p);
            }
        }
        else
        {
            for (int i = 0; i < HumanPlayers->size(); i++)
            {
                Player *p = HumanPlayers->at(i);
                p->Read();
                if (p->BasePointer != 0 && (p->IsPlayer() || p->IsDummy()))
                    Players->push_back(p);
            }
        }

        // Updates //
        GameCamera->Update();
        Legit->UpdateAimbot();
        Legit->UpdateRCS();
        Rage->Update();
        Trigger->Update();
        MiscTab->Update();

        return true;
    }
    catch (const std::exception &ex)
    {
        std::system("clear");
        std::cout << "Error: " << ex.what() << std::endl;
        return true;
    }

    return false;
}

void MiscThreadRun()
{
    while (!StopThread)
    {
        if (!Map->IsPlayable)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        if (!Myself->IsValid())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        //----------------------------- RapidFire -----------------------------
        if (Features::Misc::RapidFire)
        {
            MiscTab->RapidFire(); // Run RapidFire
        }

        //----------------------------- Other -----------------------------
        
    }
}

// Main
int main(int argc, char *argv[])
{
    if (getuid())
    {
        std::cout << "Please run as sudo!" << std::endl;
        return -1;
    }

    // Waiting for Apex Legends to be found //
    while (Memory::GetPID() == 0)
    {
        std::system("clear");
        std::cout << "waiting for apex..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    std::system("clear");
    std::cout << " " << std::endl; // Spacing

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    std::cout << "                                                   ████   ███                       █████   " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "                                                  ░░███  ░░░                       ░░███    " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << " █████████  ██████   ████████              ██████  ░███  ████   ██████  ████████   ███████  " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "░█░░░░███  ░░░░░███ ░░███░░███ ██████████ ███░░███ ░███ ░░███  ███░░███░░███░░███ ░░░███░   " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "░   ███░    ███████  ░███ ░███░░░░░░░░░░ ░███ ░░░  ░███  ░███ ░███████  ░███ ░███   ░███    " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "  ███░   █ ███░░███  ░███ ░███           ░███  ███ ░███  ░███ ░███░░░   ░███ ░███   ░███ ███" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << " █████████░░████████ ░███████            ░░██████  █████ █████░░██████  ████ █████  ░░█████ " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "░░░░░░░░░  ░░░░░░░░  ░███░░░              ░░░░░░  ░░░░░ ░░░░░  ░░░░░░  ░░░░ ░░░░░    ░░░░░  " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "                     ░███                                                                   " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "                     █████                                                                  " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "                    ░░░░░                                                                   " << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "zap client - ver 1.0.6 [Read Only]" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "By Gerosity" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "For Game Version v3.0.63.32" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Initialize Overlay Window //
    if (!InitializeOverlayWindow())
        return -1;

    // Theading //
    std::thread X11Thread(X11EventListener);
    X11Thread.detach();
    std::thread InputManagerThread(InputManager::run);
    InputManagerThread.detach();
    std::thread MiscThread(MiscThreadRun);
    MiscThread.detach();

    // Initialize the whole process //
    try
    {
        for (int i = 0; i < 70; i++)
            HumanPlayers->push_back(new Player(i, Myself));

        for (int i = 0; i < 15000; i++) // 15000
            Dummies->push_back(new Player(i, Myself));

        std::cout << "core initialized" << std::endl;
        std::cout << "-----------------------------" << std::endl;

        // LoadConfig();
        // This is where the fun starts //
        OverlayWindow.Start(&UpdateCore, &RenderUI);
        srand (static_cast <unsigned> (time(0)));
    }
    catch (...)
    {
    }

    StopThread = true;
    InputManager::StopThread = true;
    X11Thread.join();
    InputManagerThread.join();
    MiscThread.join();
    return 0;
};
