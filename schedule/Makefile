OBJS += schedule/PQScheduler.o

INC += schedule/IScheduler.h schedule/FuncSchedFeture.h schedule/PQScheduler.h

schedule/%.o : schedule/%.cpp
	g++ -c -o "$@" "$<" -I/opt/local/include -I.
