// Externals
#pragma once
#include <chrono>
#include <thread>
#include <string>
#include <stdio.h>
#include <time.h>
#include <random>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#define GLFW_EXPOSE_NATIVE_X11
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

// Internals
#include "Font.hpp"
#include "../Utils/InputManager.hpp"
#include "Utils/Themes.hpp"
#include "Utils/Config.hpp"
#include "../Utils/Features.hpp"

class Overlay
{
private:
    GLFWwindow *OverlayWindow;
    int ScreenWidth;
    int ScreenHeight;
    int ScreenPosX;
    int ScreenPosY;

    void GrabScreenSize()
    {
        GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *vidMode = glfwGetVideoMode(primaryMonitor);
        glfwGetMonitorPos(primaryMonitor, &ScreenPosX, &ScreenPosY);
        ScreenWidth = vidMode->width;
        ScreenHeight = vidMode->height;
    }

    /*std::string RandomString(int ch) // Returned the same string everytime
    {
        char alpha[35] = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        std::string result = "";
        for (int i = 0; i < ch; i++)
            result = result + alpha[rand() % 35];
        return result;
    }*/

    std::string RandomString(std::string::size_type length)
	{
	    static auto& chrs = "0123456789"
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	    thread_local static std::mt19937 rg{std::random_device{}()};
	    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

	    std::string s;

	    s.reserve(length);

	    while(length--)
		s += chrs[pick(rg)];

	    return s;
	}

    int RandomInt(int min, int max)
    {
        srand( time(NULL) ); //seeding for the first time only!
        return min + rand() % (( max + 1 ) - min);
    }

    static void GLFWErrorCallback(int error, const char *description)
    {
        fprintf(stderr, "GLFW Error %d: %s\n", error, description);
    }

    long long CurrentEpochMilliseconds()
    {
        auto currentTime = std::chrono::system_clock::now();
        auto duration = currentTime.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

    ImWchar *GetFontGlyphRanges() noexcept
    {
        static ImVector<ImWchar> ranges;
        if (ranges.empty())
        {
            ImFontGlyphRangesBuilder builder;
            constexpr ImWchar baseRanges[] = {
                0x0100, 0x024F, // Latin Extended-A + Latin Extended-B
                0x0300, 0x03FF, // Combining Diacritical Marks + Greek/Coptic
                0x0600, 0x06FF, // Arabic
                0x0E00, 0x0E7F, // Thai
                0};
            builder.AddRanges(baseRanges);
            builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
            builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesDefault());
            builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
            builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesChineseSimplifiedCommon());
            // ★龍王™
            builder.AddChar(u'\u2605'); // ★
            builder.AddChar(u'\u9F8D'); // 龍
            builder.AddChar(u'\u738B'); // 王
            builder.AddChar(u'\u2122'); // ™
            builder.BuildRanges(&ranges);
        }
        return ranges.Data;
    }

public:
    int ProcessingTime;
    long long StartTime;
    int SleepTime;
    int TimeLeftToSleep;

    int AsciiArt = 5;
    int AsciiArtSpeed = 100;
    int ThemeStyle;
    int ThemeColor;
    bool TeamGamemode = true;
    bool ErrorLogging = false;

    bool InitializeOverlay()
    {
        glfwSetErrorCallback(GLFWErrorCallback);
        if (!glfwInit())
        {
            return false;
        }

        GrabScreenSize();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        glfwDefaultWindowHints();

        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
        glfwWindowHint(GLFW_REFRESH_RATE, 75);

        OverlayWindow = glfwCreateWindow(ScreenWidth, ScreenHeight, RandomString(RandomInt(10, 20)).c_str(), NULL, NULL);

        glfwSetWindowPos(OverlayWindow, ScreenPosX, ScreenPosY);
        CaptureInput(true);
        glfwMakeContextCurrent(OverlayWindow);

        // Centering //
        GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *vidMode = glfwGetVideoMode(primaryMonitor);
        glfwSetWindowPos(OverlayWindow, (vidMode->width - ScreenWidth) / 2, (vidMode->height - ScreenHeight) / 2);
        // End of Centering //

        InitializeUI();

        glfwShowWindow(OverlayWindow);
        glfwSwapInterval(0);

        return true;
    }

    void InitializeUI()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImFontConfig cfg;
        /*cfg.OversampleH = cfg.OversampleV = 1;
        cfg.PixelSnapH = true;
        cfg.SizePixels = 13.0f;
        cfg.GlyphOffset = {1.0f, -1.0f};*/
        cfg.OversampleH = cfg.OversampleV = 1;
        cfg.PixelSnapH = false;
        cfg.SizePixels = 13.0f; // 13.0f
        cfg.GlyphOffset = {0.0f, 0.0f};
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.Fonts->AddFontFromMemoryCompressedTTF(_compressedFontData, _compressedFontSize, cfg.SizePixels, &cfg, GetFontGlyphRanges());
        // io.Fonts->AddFontFromFileTTF("../Assets/Fonts/NanumGothic-Bold.ttf", cfg.SizePixels, &cfg, GetFontGlyphRanges());

        ImGui::StyleColorsDark();
        ImGuiStyle &style = ImGui::GetStyle();
        /*style.WindowPadding                     = ImVec2(8.00f, 8.00f);
        style.FramePadding                      = ImVec2(5.00f, 2.00f);
        style.CellPadding                       = ImVec2(6.00f, 6.00f);
        style.ItemSpacing                       = ImVec2(6.00f, 6.00f);
        style.ItemInnerSpacing                  = ImVec2(6.00f, 6.00f);
        style.TouchExtraPadding                 = ImVec2(0.00f, 0.00f);
        style.IndentSpacing                     = 25;
        style.ScrollbarSize                     = 12;
        style.GrabMinSize                       = 10;
        style.WindowBorderSize                  = 1;
        style.ChildBorderSize                   = 1;
        style.PopupBorderSize                   = 1;
        style.FrameBorderSize                   = 1;
        style.TabBorderSize                     = 1;
        style.WindowRounding                    = 7;
        style.ChildRounding                     = 4;
        style.FrameRounding                     = 3;
        style.PopupRounding                     = 4;
        style.ScrollbarRounding                 = 9;
        style.GrabRounding                      = 3;
        style.LogSliderDeadzone                 = 4;
        style.TabRounding                       = 4;

        style.Colors[ImGuiCol_Text]                   = Text;
        style.Colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        style.Colors[ImGuiCol_WindowBg]               = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        style.Colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_PopupBg]                = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
        style.Colors[ImGuiCol_Border]                 = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
        style.Colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
        style.Colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        style.Colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        style.Colors[ImGuiCol_FrameBgActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        style.Colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TitleBgActive]          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
        style.Colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.00f);
        style.Colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
        style.Colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        style.Colors[ImGuiCol_CheckMark]              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        style.Colors[ImGuiCol_SliderGrab]             = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        style.Colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        style.Colors[ImGuiCol_Button]                 = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        style.Colors[ImGuiCol_ButtonHovered]          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        style.Colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        style.Colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        style.Colors[ImGuiCol_HeaderHovered]          = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
        style.Colors[ImGuiCol_HeaderActive]           = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
        style.Colors[ImGuiCol_Separator]              = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        style.Colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        style.Colors[ImGuiCol_SeparatorActive]        = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        style.Colors[ImGuiCol_ResizeGrip]             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        style.Colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        style.Colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        style.Colors[ImGuiCol_Tab]                    = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        style.Colors[ImGuiCol_TabHovered]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        style.Colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
        style.Colors[ImGuiCol_TabUnfocused]           = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        style.Colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        style.Colors[ImGuiCol_PlotLines]              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        style.Colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        style.Colors[ImGuiCol_TableBorderLight]       = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        style.Colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        style.Colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        style.Colors[ImGuiCol_DragDropTarget]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        style.Colors[ImGuiCol_NavHighlight]           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
        style.Colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
        style.Colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);*/

        ImGuiStyle &Style = ImGui::GetStyle();
        style.SliderThickness = 0.2f;
        style.SliderContrast = 0.5f;
        style.SliderValuePos = ImVec2(1.0f, 2.2f);
        style.WindowPadding = ImVec2(8.00f, 8.00f);
        style.FramePadding = ImVec2(5.00f, 2.00f);
        style.CellPadding = ImVec2(6.00f, 6.00f);
        style.ItemSpacing = ImVec2(6.00f, 6.00f);
        style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
        style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
        style.IndentSpacing = 25;
        style.ScrollbarSize = 12;
        style.GrabMinSize = 10;
        style.WindowBorderSize = 1;
        style.ChildBorderSize = 1;
        style.PopupBorderSize = 1;
        style.FrameBorderSize = 1;
        style.TabBorderSize = 1;
        style.WindowRounding = 7;
        style.ChildRounding = 4;
        style.FrameRounding = 3;
        style.PopupRounding = 4;
        style.ScrollbarRounding = 9;
        style.GrabRounding = 3;
        style.LogSliderDeadzone = 4;
        style.TabRounding = 4;

        style.Colors[ImGuiCol_Text] = ImVec4(0.900000f, 0.900000f, 0.900000f, 1.000000f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.600000f, 0.600000f, 0.600000f, 1.000000f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.058824f, 0.058824f, 0.058824f, 1.000000f);
        style.Colors[ImGuiCol_ChildBg] = ImVec4(0.000000f, 0.000000f, 0.000000f, 0.000000f);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(57 / 255.f, 57 / 255.f, 57 / 255.f, 1);
        style.Colors[ImGuiCol_Border] = ImVec4(0.500000f, 0.500000f, 0.500000f, 0.500000f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.000000f, 0.000000f, 0.000000f, 0.000000f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.430000f, 0.430000f, 0.430000f, 0.390000f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.470000f, 0.470000f, 0.690000f, 0.400000f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.420000f, 0.410000f, 0.640000f, 0.690000f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.270000f, 0.270000f, 0.540000f, 0.830000f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.320000f, 0.320000f, 0.630000f, 0.870000f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.400000f, 0.400000f, 0.800000f, 0.200000f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.400000f, 0.400000f, 0.550000f, 0.800000f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.200000f, 0.250000f, 0.300000f, 0.000000f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.400000f, 0.400000f, 0.400000f, 0.300000f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.400000f, 0.400000f, 0.400000f, 0.400000f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.400000f, 0.400000f, 0.400000f, 0.600000f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.900000f, 0.900000f, 0.900000f, 0.500000f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.000000f, 1.000000f, 1.000000f, 0.300000f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.410000f, 0.390000f, 0.800000f, 0.600000f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.350000f, 0.400000f, 0.610000f, 0.620000f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.400000f, 0.480000f, 0.710000f, 0.790000f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.460000f, 0.540000f, 0.800000f, 1.000000f);
        style.Colors[ImGuiCol_Header] = ImVec4(45 / 255.f, 45 / 255.f, 45 / 255.f, 1);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(50 / 255.f, 50 / 255.f, 50 / 255.f, 1);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(45 / 255.f, 45 / 255.f, 45 / 255.f, 1);
        style.Colors[ImGuiCol_Separator] = ImVec4(0.500000f, 0.500000f, 0.500000f, 0.600000f);
        style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.600000f, 0.600000f, 0.700000f, 1.000000f);
        style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.700000f, 0.700000f, 0.900000f, 1.000000f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.000000f, 1.000000f, 1.000000f, 0.160000f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.780000f, 0.820000f, 1.000000f, 0.600000f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.780000f, 0.820000f, 1.000000f, 0.900000f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.000000f, 0.000000f, 1.000000f, 0.350000f);
        style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.000000f, 1.000000f, 0.000000f, 0.900000f);

        ImGui_ImplGlfw_InitForOpenGL(OverlayWindow, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
    }

    bool AlignedButton(const char *label, float alignment = 0.5f)
    {
        ImGuiStyle &style = ImGui::GetStyle();

        float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
        float avail = ImGui::GetContentRegionAvail().x;

        float off = (avail - size) * alignment;
        if (off > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

        return ImGui::Button(label);
    }

    bool Save()
    {
        try
        {
            /*Config::Home::AsciiArt = AsciiArt;
            Config::Home::AsciiArtSpeed = AsciiArtSpeed;
            Config::Home::TeamGamemode = TeamGamemode;
            Config::Home::Style = ThemeStyle;
            Config::Home::Color = ThemeColor;
            //Config::Home::MenuX = MenuX;
            //Config::Home::MenuY = MenuY;
            Config::Home::ErrorLogging = ErrorLogging;*/
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    void DestroyOverlay()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        if (OverlayWindow != nullptr)
        {
            glfwDestroyWindow(OverlayWindow);
        }

        glfwTerminate();
    }

    void CaptureInput(bool capture)
    {
        glfwSetWindowAttrib(OverlayWindow, GLFW_MOUSE_PASSTHROUGH, capture ? GLFW_FALSE : GLFW_TRUE);
    }

    void FocusOverlay()
    {
        glfwFocusWindow(OverlayWindow);
    }

    void Start(bool (*Update)(), void (*RenderUI)())
    {
        while (!glfwWindowShouldClose(OverlayWindow))
        {
            StartTime = CurrentEpochMilliseconds();
            glfwPollEvents();
            glViewport(0, 0, ScreenWidth, ScreenHeight);
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, ScreenWidth, ScreenHeight, 0, -1, 1);

            // Update
            if (Update != nullptr)
            {
                Update();
            }

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Render
            if (RenderUI != nullptr)
            {
                RenderUI();
            }

            // Render ImGui and swap buffers
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(OverlayWindow);

            ProcessingTime = static_cast<int>(CurrentEpochMilliseconds() - StartTime);
            SleepTime = 6; // 16.67 > 60hz | 6.97 > 144hz
            if (!Features::Settings::FPSCap)
            {
                TimeLeftToSleep = std::max(0, SleepTime - ProcessingTime);
            }

            if (Features::Settings::FPSCap)
            {
                TimeLeftToSleep = 1000 / Features::Settings::CappedFPS;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(TimeLeftToSleep));
        }

        DestroyOverlay();
    }

    void GetScreenResolution(int &Width, int &Height) const
    {
        Width = ScreenWidth;
        Height = ScreenHeight;
    }

    const std::string currentDateTime(int Option) // 1 for Date And Time, 2 For Date Only, 3 for Time Only
    {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);

        if (Option == 1) // Date and Time
        {
            strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
        }
        else if (Option == 2) // Date Only
        {
            strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
        }
        else if (Option == 3) // Time Only
        {
            strftime(buf, sizeof(buf), "%X", &tstruct);
        }

        return buf;
    }
};
