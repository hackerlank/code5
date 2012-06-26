SRC = NetService.h NetService.cpp World.cpp World.h main.cpp

objs = NetService.o World.o main.o MessageDescriptor.o

Wing : $(objs)
	g++ -g -o $@ $(objs) $(incs) -I.. -L../lib -lnet -lprotobuf -lschedule -lnetmsg -lutil; cp $@ ../bin/

NetService.o : NetService.cpp NetService.h
	g++ -c -g $< -I.. -o $@

World.o : World.cpp World.h
	g++ -c -g $< -I../ -o $@

main.o : main.cpp
	g++ -c -g $< -I../ -o $@

MessageDescriptor.o : MessageDescriptor.cpp MessageDescriptor.h
	g++ -c -g $< -I../ -o $@


clean:
	-rm Wing *.o
