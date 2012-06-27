OBJS += gate/Gate.o gate/main.o gate/PlayerMgr.o gate/NetService.o \
	gate/Player.o gate/WorldMgr.o #ScriptSys.o

INCS += gate/GateMsgCoder.h gate/ScriptSys.h gate/Gate.h gate/PlayerMgr.h \
	gate/WorldMgr.h gate/Player.h

gate/%.o : gate/%.cpp
	g++ -c -o "$@" "$<" -I. -I/usr/include/lua5.1

#gate/ScriptSys.o : gate/ScriptSys.cpp gate/ScriptSys.h
#	g++ -c -o "$@" "$<" -I. 
