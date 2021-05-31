# lua-gpio-win
Lua 5.4 dll library module to control and access Gpio on devices with win OS. (e.g. Rasperry Pi on Win ARM).

Due to the lack of any options to access the gpio's on rasperry pi's on a windows OS I made this lua libarary
to quickly access the Pinouts and read their state. Interfacing via I2C is ont he todo list as well so stay tuned.

Load this module via require("LuaGpioWin")

Currently this libary provides the following functions:

info()
PinOn(pinNumber)
PinOff(pinNumber)
PinToggle(pinNumber)
PinRead(pinNumber)

A test kit (test folder) is also available (use via start.bat). Edit the script.lua to fit your needs.
