libschedule.a : PQScheduler.o IScheduler.h FuncSchedFeture.h 
	ar rcs -o $@ PQScheduler.o; cp $@ ../lib

PQScheduler.o : PQScheduler.cpp PQScheduler.h IScheduler.h
	g++ -c -o $@ PQScheduler.cpp -I..

clean:
	-rm *.o libschedule.a