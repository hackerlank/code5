#ifndef _GATE_MSG_CODER_
#define _GATE_MSG_CODER_

#include "net/PackData.h"
#include "net/Coder.h"

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

#endif
