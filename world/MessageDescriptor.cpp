#include "MessageDescriptor.h"

#include "net/Coder.h"
#include "net/PackData.h"

#include "proto/login.pb.h"
#include "proto/move.pb.h"

Coder* g_msg_coders[] = {
	//request
	new PBDecoder<netmsg::LoginRequest>(),
	new PBDecoder<netmsg::MovePathRequest>(),
	new PBDecoder<netmsg::MoveRequest>(),
	
	//Sys
	new PBDecoder<netmsg::ServerLoginRequest>(),
	NULL
};