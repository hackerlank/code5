OBJS += world/NetService.o world/World.o world/main.o world/MessageDescriptor.o \
	world/AOIService.o world/Zone.o world/ScriptSys.o world/MapMgr.o \
	world/Player.o

INC += world/NetService.h world/World.h world/MessageDescriptor.h world/AOIService.h \
	world/Zone.h world/scriptSys.h world/MapMgr.h 

world/%.o : world/%.cpp
	g++ -I. -c -o "$@" "$<" -I/opt/local/include -I/usr/local/include
