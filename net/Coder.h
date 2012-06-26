#ifndef _CODER_H
#define _CODER_H

#include <string>
#include <stdlib.h>
#include <string.h>
#include "PackData.h"

using std::string;

struct DataBuffer{
	DataBuffer()
		:size(0), data(0)
	{}
	
	DataBuffer(const DataBuffer& buffer)
		:size(buffer.size),data(buffer.data)
	{}
	
	DataBuffer(const char* d, int sz, bool copy)
	{
		size = sz;
		if (copy) {	
			data = (char*)malloc(sz);
			memcpy(data, d, size);
		} else
			data = const_cast<char*>(d);
	}

	void release()
	{
		delete[] data;
	}

	char* detach()
	{
		char* ptr = data;
		data = 0;
		size = 0;
		return ptr;
	}

	int size;
	char* data;
};

class Coder {
public:
	static DataBuffer encode(Message* msg); 
	
	virtual int category() = 0;
	virtual int msgId() = 0;
public:
	Coder(){}
	Coder(const Coder&) {}

	virtual ~Coder(){}

	virtual Message* decode(const void* data, int size) = 0;	
};

template<class T>
class PBDecoder : public Coder{
public:
	~PBDecoder() {}
	int category() { return T::_category;}
	int msgId() { return T::_msgId; }

	Message* decode(const void* data, int size) {
		T* msg = new T();
		if (!msg->ParseFromArray(data, size)) {
			delete msg;
			return NULL;
		} else
			return msg;
	}	
};

template<class T>
class  MessageHandler{
public:
	virtual ~MessageHandler(){}
	virtual T operator()(player_id, Message*) = 0;
};

template<class T, class U>
class AnyMsgHandler : public MessageHandler<T>{
public:
	typedef T (*FuncType)(player_id, U*);

	AnyMsgHandler(FuncType f)
		:_funcHandler(f)
	{}
	
	virtual ~AnyMsgHandler() {};

	virtual T operator()(player_id playerId, Message* msg) { 
		return _funcHandler(playerId, (U*)msg);
	}

	FuncType _funcHandler;
};

#endif
