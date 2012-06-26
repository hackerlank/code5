all: login.pb.cc move.pb.cc

login.pb.cc : defines/login.proto
	protoc -I=defines --cpp_out=. defines/login.proto

move.pb.cc	:	defines/move.proto
	protoc -I=defines --cpp_out=. defines/move.proto

python: login_pb2.py move_pb2.py

login_pb2.py : defines/login.proto
	protoc -I=defines --python_out=. $<

move_pb2.py	:	defines/move.proto
	protoc -I=defines --python_out=. $<