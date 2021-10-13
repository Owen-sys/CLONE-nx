# Clone-Nx-Remastered
> A fork of [Hamhub7's Clone-nx](https://github.com/hamhub7/CLONE-nx) With the purpose of updating its state to make it compatible with newer firmwares.

Clone-nx copys the inputs of your (P1 or Handheld) controller.

## Support the Creators
Join our [Discord server](http://discord.gg/qeamCcV)  
Support hamhub7 on [Patreon](https://www.patreon.com/aaronhh) or [PayPal](https://www.paypal.me/aaronhamhub)  
Make a pull request!  

## Features
New features are already planned, such as:
1. A Smash Bros Ultimate Version Of Clone-nx for the in-game mods if you dont have memory for the sysmoodule.
2. Custom Mapping Support For Controller Combo's.
3. Custom Colors
4. GUI for previously mentioned mapping support.
5. Tas-Support (To record Multiple Inputs into a automatically generated format that will be used for [tas-script] (https://github.com/hamhub7/tas-script) more on that eventually)
6. Support for Libnx-Auto-Updater.

## Usage
First of all, you need to have an [Atmosphere-injected Switch](https://switch.homebrew.guide/).

### Installation
1. Acquire `Clone-NX.nsp` either from the latest release, or more preferrably build yourself via the instructions below
2. Create the relevant title directory on your Switch's SD card at `sdmc:/atmosphere/titles/0100000000000cab/` (`sdmc:/atmosphere/contents/0100000000000cab` on Atmosphere versions 0.10.0 or newer if using tas-script use 0100000000000dab for clone-nx instead.)
3. Place the NSP as `sdmc:/atmosphere/titles/0100000000000cab/exefs.nsp` (`sdmc:/atmosphere/contents/0100000000000cab/exefs.nsp` on Atmosphere versions 0.10.0 or newer)
4. Create an empty file at `sdmc:/atmosphere/titles/0100000000000cab/flags/boot2.flag` (`sdmc:/atmosphere/contents/0100000000000cab//flags/boot2.flag` on Atmosphere versions 0.10.0 or newer)
5. Reboot into CFW

### Keybinds (Currently Removed Will be added back very soon)
You need to have a USB keyboard attached to your Switch, either via the dock or a USB-A to USB-C adapter in the charging port.

#### Controllers
- `1` = Pro Controller  
- `2` = Pair of Joycons (this adds two controllers; exists for ease-of-use)  
- `3` = Left Joycon  
- `4` = Right Joycon  
- `5` = Famicom Controller  
- `6` = Famicom Controller with mic  
- `7` = NES Controller  
- `8` = Unused SNES-style Controller/Pad
- `-` = Remove the most recently added controller

#### Scripts
- `f1` = `sdmc:/scripts/script1.txt`
- `f2` = `sdmc:/scripts/script2.txt`
- ...
- `f12` = `sdmc:/scripts/script12.txt`

#### Utilities
- `Q` = Press L+R on the most recently added controller
- `W` = Press A on the most recently added controller
- `PAUSE` = Pauses and resumes execution of current script
- `SCROLLLOCK` = Stops execution of current script

## Building from Source
1. [Set up the required libraries](https://switchbrew.org/wiki/Setting_up_Development_Environment)
2. In the newly installed MSYS2, navigate to the folder you'd like to build this project in, either by opening MSYS in that directory or using the `cd` command to navigate
3. `git clone https://github.com/Owen-sys/CLONE-nx.git`
4. `cd CLONE-NX`
5. `make`
6. You should see a file called `Clone-nx.nsp`

The `make` process will fail for one of three reasons:
- You cloned a commit that doesn't compile (unlikely)
- Your folder is named something other than `Clone-nx`; solution is to `ln -s Clone-Nx.json config.json`
- Your directory's full path has spaces in it (usually your account name)
