#all: login_pb2.py move_pb2.py

OBJS += proto/move.pb.o proto/login.pb.o
INCS += proto/login.pb.h proto/move.pb.h

proto/%.o : proto/%.cc
	g++ -c -o $@ $<

