require("Lua_GPIO_RPI_Win")

gpio5 = 5

info()

print("Activating Pin " .. gpio5)
PinOn(gpio5)

if PinRead(gpio5) then
	print("Pin " .. gpio5 .. " activated")
end