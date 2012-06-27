INCS += net/CoderMgr.h net/INetwork.h net/Socket.h net/ net/PackData.h \
	net/Coder.h net/EpollServer.h

OBJS += net/Coder.o net/Socket.o net/EpollServer.o net/CoderMgr.o

net/%.o	: net/%.cpp
	g++ -I. -c -o "$@" "$<"
