extern "C" {
#include "dependencies\includes\lualib.h"
#include "dependencies\includes\lauxlib.h"
#include "dependencies\includes\lua.h"
}
#include <iostream>

#include <winrt/windows.devices.gpio.h>
using namespace winrt::Windows::Devices::Gpio;

void Write_GPIO(unsigned int pinNumber, bool state) {
    GpioController gpio = GpioController::GetDefault();
    if (gpio == nullptr) {
        std::cout << "Error: GPIO access.";
        return;
    }
    GpioPin pin = gpio.OpenPin(pinNumber);
    pin.SetDriveMode(GpioPinDriveMode::Output);
    if (state) {        
        pin.Write(GpioPinValue::High);   
    }
    else {
        pin.Write(GpioPinValue::Low);
    }
}

GpioPinValue Read_GPIO(unsigned int pinNumber) {
    GpioController gpio = GpioController::GetDefault();
    if (gpio == nullptr) {
        std::cout << "Error: GPIO access.";
        return GpioPinValue::Low;
    }
    GpioPin pin = gpio.OpenPin(pinNumber);
    pin.SetDriveMode(GpioPinDriveMode::Input);
    return pin.Read();    
}

extern "C" static int PinOn(lua_State* L) {
    unsigned int pinNumber = luaL_checkinteger(L, 1);
    Write_GPIO(pinNumber, true);
    return 0;
}

extern "C" static int PinOff(lua_State * L) {
    unsigned int pinNumber = luaL_checkinteger(L, 1);
    Write_GPIO(pinNumber, false);
    return 0;
}

extern "C" static int PinToggle(lua_State * L) {
    unsigned int pinNumber = luaL_checkinteger(L, 1);
    if (Read_GPIO(pinNumber) == GpioPinValue::Low) {
        Write_GPIO(pinNumber, true);
    }
    else {
        Write_GPIO(pinNumber, false);
    }
    return 0;
}

extern "C" static int PinRead(lua_State * L) {
    unsigned int pinNumber = luaL_checkinteger(L, 1);
    if (Read_GPIO(pinNumber) == GpioPinValue::High) {
        lua_pushboolean(L, 1);
    }
    else {
        lua_pushboolean(L, 0);
    }
    return 1;
}

extern "C" static int info(lua_State * L) {
    std::cout << "Lua GPIO win 0.1";
    lua_pushstring(L, "Lua GPIO win 0.1");
    return 0;
}

extern "C" __declspec(dllexport) int __cdecl luaopen_LuaGpioWin(lua_State* L) {
    lua_register(L, "info", info);
    lua_register(L, "PinOn", PinOn);
    lua_register(L, "PinOff", PinOff);
    lua_register(L, "PinToggle", PinToggle);
    lua_register(L, "PinRead", PinRead);
    return 0;
}
