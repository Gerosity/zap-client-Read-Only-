# zap-client Read Only Version [Apex External Cheat For Linux]
**Updated to Game Version v3.0.68.50 (Season 21) (10.05.24)**

By **Gerosity**

All credits to original owners

Instructions are down below

**Never cheat on a main account, its not worth it**

<details>
<summary><b>Features</b></summary>
    
    Legitbot - Aimbot, RCS, Visuals
    Triggerbot
    ESP - Enemy & Teammate, Spectator List, Crosshair, Radar
    Misc - Rapid Fire (For Semi-Auto & Burst Weapons)
    Settings - Disable Overlay, Disable ESP, FPS Cap
    Configs - Custom Configs, Premade Configs

</details>

<details>
<summary><b>Changelog</b></summary>
    
    10.05.24 - Version 1.1.1
    - Updated offsets to latest version (Game Version v3.0.68.50)
    - Fixed Spectator List (Might get patched sooner or later)

    07.05.24 - Version 1.1.0 - Season 21 Update
    Updated offsets to latest version (Game Version v3.0.67.34)
    
    Legitbot:
        - Added Target Visuals (Draw Line, Dot & Box On/To Aimbot Current or Best Target)
        - Added Target Information (Draw Information About Aimbot Current or Best Target)
        - Fixed Standalone RCS
    Triggerbot:
        - Added Attack Methods (Mouse or Memory, Both Support Controller, Memory has not been thoroughly tested)
        - Added Triggerbot Delay (Note: Processing Speed Affects This, Its Not Perfect & Depending On Attack Method, It Will Be Different)
    Glow:
        - Fixed Glow Max Distance (Now ACTUALLY works)
        - Added Knocked Check & Knocked Color
        - Fixed Glow Sheild Based Color Mode
        - Fixed Custom Item Glow (?)
    Sense:
        - Added Knocked Check & Knocked Color
        - Added Box, Skeleton & Head Circle Outlines
        - Re-designed Watermark And Spectator List (Still Patched) (Credits: hir0xy)
        - Fixed Position Changer
    Misc:
        - Added Superglide Modes (Manual Or Automatic, Automatic Supports Controller)
        - Re-designed Misc Tab (Credits: hir0xy)
    Settings:
        - Overlay Now Runs At An Uncapped Refresh Rate
        - If FPS Cap Is Disabled, Cheat Will Run At Refresh Rate (Recommened)
        - Added Toggle For Anti Aliased Lines - For ESP
        - Added Dead Check - Displays ESP & Glow If You Are Dead/Spectating
    Configs:
        - Added Premade Configs (Note: Not Perfect & Should Be Used As A Base For Creating Your Own
        Legit Config, Fine Tune To Your Liking!)
    Other:
        - Added Version Check (Can Be Skipped) (Credits: hir0xy)
        - Fixed A Couple Error Messages (Credits: hir0xy)
        - Optimizations (Untested) & Cleaner Code  (Credits: hir0xy)
        - Fixed Overlay Errors (Credits: hir0xy)
    
    22.04.24 - Version 1.0.6.1
    Updated offsets to latest version (Game Version v3.0.65.42)
    Busy atm but will eventually start working on a better and more optimised version of this

    8.04.24 - Version 1.0.6
    Updated offsets to latest version (Game Version v3.0.63.32)

    1.04.24
    Updated offsets to latest version (Game version v3.0.62.30)

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
        Added a run.sh script which randomises the zapclient binary and hides PID once 
        executed - use this instead of ./zapclient

    26.03.24 - Version 1.0.3
    Updated to latest game version (Game Version v3.0.62.29)

    24.03.24 - Version 1.0.2
    
    Complete GUI Overhaul
    Fixed issues with aimbot & triggerbot
    Added Ragebot, Flickbot, Viewmodel Glow, Glow Customizations, ESP Features, BHop, QuickTurn, RapidFire, Overlay Settings
    Bunch a stuff that I cant remember all at once
</details>

<details>
<summary><b>Video Previews</b></summary>
    
**Menu Preview - Version 1.0.0:**

[![Menu](https://img.youtube.com/vi/VBnAyOhTSIs/0.jpg)](https://www.youtube.com/watch?v=VBnAyOhTSIs)

**Release - Version 1.0.0:**

[![Release - Version 1.0.0](https://img.youtube.com/vi/vCsmewJlgk0/0.jpg)](https://www.youtube.com/watch?v=vCsmewJlgk0)

**Update - Version 1.1.0:**

[![Update - Version 1.1.0](https://img.youtube.com/vi/YyiQNBgrV1Q/0.jpg)](https://www.youtube.com/watch?v=YyiQNBgrV1Q)
</details>

# Other Repositories:
https://github.com/Gerosity/zap-client-Read-Only-   - A read memory only version

https://github.com/Gerosity/Apex-Protection         - A protection guide, not fully tested but its not like its going to hurt using it

# Before Installation
**Install Linux**

    Not hard at all, use Google & YouTube. Search "How to dual boot Linux and windows"
    NOTE: It is recommened to use GNOME or Cinnamon as your desktop environment. KDE Plasma is known not to allow the overlay to be drawn above the game.
    Other desktop environments may work

**Install Steam & Apex**
  
    Use YouTube & Google for this.
    if upon opening apex you get a black screen and it does not open, follow this: https://www.unknowncheats.me/forum/4012140-post13.html

# Installation
**1 Install dependencies**
<details>
<summary><b>Debian dependencies</b></summary>
    
    sudo apt-get install -y libudev-dev
    sudo apt install cmake xorg-dev libglu1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
    sudo apt install -y libudev-dev libglu1-mesa-dev libxkbcommon-dev libwayland-dev git cmake g++ gcc libinput-dev libsoil-dev
    sudo apt-get install build-essential
    sudo apt-get install libx11-dev
    sudo apt-get install libxtst-dev

</details>
<details>
<summary><b>Arch dependencies - Look through the UC thread for any more information</b></summary>
    
    sudo pacman -Sy libudev0 cmake xorg-server git base-devel libx11 libxtst

</details>

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

    Then Either:
    sudo ./zapclient
    or
    ./run.sh

**6. Press Insert to toggle the Menu (You can only interact with the Menu and the game when the menu is active).**
**Note: You will need to alt+tab between the cheat overlay and apex.**

# Credits:
    https://github.com/Nexilist/xap-client - for the base, massive credits to them
    https://github.com/arturzxc/grinder - alternate aimbot mode, most of the misc features
    https://github.com/Braziliana/T_TApe - custom config system
    https://www.unknowncheats.me/forum/apex-legends/ - A TON of help, offsets, many additional features & more
    wafflesgaming - aimbot help, Extra ESP Features such as 2D Corners
    0xAgartha & ghostrazzor - run.sh script (Randomises zapclient binary & Hides PID before execution)
    hir0xy - Version Checker, Overlay Fixes, Cleaner GUI & optimizations here and there

