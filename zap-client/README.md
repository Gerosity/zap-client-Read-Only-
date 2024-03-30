# zap-client [Apex External Cheat For Linux] [Read-Only Version]
**Updated to Game Version v3.0.62.29 (Season 20) (26.03.24)**

By **Gerosity**

All credits to original owners

Instructions are down below

zap-client configs **are compatible** with this!

**There was a recent banwave and a lot of accounts were hit. Be careful & never cheat on a main account, its not worth it**

# Other Repositories:
https://github.com/Gerosity/zap-client              - The main version

https://github.com/Gerosity/Apex-Protection         - A protection guide, not fully tested but its not like its going to hurt using it

# Features:
    Legitbot - Aimbot, RCS
    Ragebot - Aimbot, RCS
    Flickbot
    Triggerbot
    Glow - Player, Viewmodel & Item
    ESP - Enemy & Teammate, Spectator List, Crosshair, Radar
    Misc - Movement, Camera (Quick Turn), Rapid Fire (For Semi-Auto & Burst Weapons), Skin Changer (Basic, not to be confused with a model changer)
    Settings - Gamemode Switcher, Disable Overlay, Disable ESP, FPS Cap
    Configs - Custom Configs

# Changelog:
    30.03.24 - Version 1.0.5
    Legitbot:
        New Aimbot Mode (An old xap-client smoothing method), testing for now
        Smoothing Modes (Static and randomised) (For randomised I recommend setting the values close together!)
    Ragebot:
        Fixes
    Flickbot:
        Fixes
    Misc:
        SuperGlide FPS (Set it to your in-game FPS, 75 is probably the best)
    Settings:
        Removed Gamemode Toggle - It now automatically switches based on what 
        gamemode your playing
    Other:
        Randomised Overlay Name now actually works
        Added a run.sh script which randomises the zapclient binary and hides PID once executed - use this 
        instead of ./zapclient

    26.03.24 - Version 1.0.3
    Updated to latest game version (Game Version v3.0.62.29)

    24.03.24 - Version 1.0.2
    
    Complete GUI Overhaul
    Fixed issues with aimbot & triggerbot
    Added Ragebot, Flickbot, Viewmodel Glow, Glow Customizations, ESP Features, BHop, QuickTurn, RapidFire, Overlay Settings
    Bunch a stuff that I cant remember all at once

# Before Installation
**Install Linux**

    Not hard at all, use Google & YouTube. Search "How to dual boot Linux and windows"

**Install Steam & Apex**
  
    Use YouTube & Google for this.
    if upon opening apex you get a black screen and it does not open, follow this: https://www.unknowncheats.me/forum/4012140-post13.html

# Installation
**1.Install dependencies**

    sudo apt-get install -y libudev-dev
    sudo apt install cmake xorg-dev libglu1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
    sudo apt install -y libudev-dev libglu1-mesa-dev libxkbcommon-dev libwayland-dev git cmake g++ gcc libinput-dev libsoil-dev
    sudo apt-get install build-essential
    sudo apt-get install libx11-dev
    sudo apt-get install libxtst-dev

**2.Build glfw**

    git clone https://github.com/glfw/glfw.git
    cd glfw
    mkdir build
    cd build
    cmake ..
    make
    sudo make install

**3. Exit the terminal and re-open it (So that you dont build the cheat directly into the GLFW build folder, wont work otherwise)**

**4. Clone repo**

    git clone https://github.com/Gerosity/zap-client.git
    cd zap-client

**5. Build & Run**

    mkdir build
    cd build
    cmake ..
    make
    chmod +x run.sh
    ./run.sh

**6. Press Insert to toggle the Menu (You can only interact with the Menu and the game when the menu is active).**
**Note: You will need to alt+tab between the cheat overlay and apex.**

# Previews:
https://www.youtube.com/watch?v=VBnAyOhTSIs
https://www.youtube.com/watch?v=vCsmewJlgk0

# Credits:
    https://github.com/Nexilist/xap-client - for the base, massive credits to them
    https://github.com/arturzxc/grinder - alternate aimbot mode, most of the misc features
    https://github.com/Braziliana/T_TApe - custom config system
    https://www.unknowncheats.me/forum/apex-legends/ - A TON of help, offsets, many additional features & more
    wafflesgaming - aimbot help, Extra ESP Features such as 2D Corners
    0xAgartha & ghostrazzor - run.sh script (Randomises zapclient binary & Hides PID before execution)

