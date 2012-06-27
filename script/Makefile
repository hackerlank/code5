OBJS += script/LuaMgr.o
INCS += script/LuaMgr.h script/Script.h

script/%.o : script/%.cpp
	g++ -c -o $@ $< -I3rd/lua-5.1.4/src
