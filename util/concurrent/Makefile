INCS +=  util/concurrent/Lock.h util/concurrent/Mutex.h \
	util/concurrent/RWLock.h util/concurrent/Thread.h

OBJS += util/concurrent/Thread.o

util/concurrent/%.o : util/concurrent/%.cpp 
	g++ -c -o "$@" "$<"
	
