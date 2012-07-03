SRC = NetService.h NetService.cpp World.cpp World.h main.cpp

objs = NetService.o World.o main.o MessageDescriptor.o AOIService.o \
		Zone.o ScriptSys.o MapMgr.o

Wing : $(objs)
	g++ -g -o $@ $(objs) $(incs) -I.. -L../lib -lnet -lprotobuf -lschedule -lnetmsg -lutil; cp $@ ../bin/

NetService.o : NetService.cpp NetService.h
	g++ -c -g $< -I.. -o $@

World.o : World.cpp World.h
	g++ -c -g $< -I../ -o $@ -I/usr/include/lua5.1

main.o : main.cpp
	g++ -c -g $< -I../ -o $@

MessageDescriptor.o : MessageDescriptor.cpp MessageDescriptor.h
	g++ -c -g $< -I../ -o $@

Zone.o : Zone.cpp Zone.h
	g++ -c -g $< -I../ -o $@

AOIService.o : AOIService.cpp AOIService.h
	g++ -c -g $< -I../ -o $@

Player.o : Player.cpp Player.h
	g++ -c -g $< -I../ -o $@

MapMgr.o : MapMgr.cpp MapMgr.h MapMgr.h
	g++ -c -g $< -I../ -o "$@" -I.

ScriptSys.o : ScriptSys.cpp ScriptSys.h
	g++ -c -g $< -I../ -o $@ -I/usr/include/lua5.1

clean:
	-rm -f Wing *.o
