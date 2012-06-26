#include "World.h"

#include <boost/bind.hpp>
#include "NetService.h"
#include "proto/login.pb.h"

#include <stdio.h>

using namespace std;

PQScheduler Scheduler(World::FrameTime);

int World::init(const char* userName, const char* pwd, const char* serverName) {
	NetService::instance().init("127.0.0.1", 9913);
	NetService::instance().connect();

	netmsg::ServerLoginRequest msg;
	msg.set_username(userName);
	msg.set_passwd(pwd);
	msg.set_servername(serverName);
	NetService::instance().send(-1, &msg);

	return 0;
}

void World::update(long elapsed) {
	static long s_timeAcc = 0;

	s_timeAcc += elapsed;

	while (s_timeAcc >= FrameTime) {
		s_timeAcc -= FrameTime;

		//handle net request first
		NetService::instance().update();

		size_t msgHanlded = 0;
		while (msgHanlded++ < MsgHandlePerFrame) {
			MsgPair pair = NetService::instance().pop();
			player_id player = pair.get<0>();
			Message* msg = pair.get<1>();
			
			if (!msg)
				break;

			printf("*******************");
			printf("%s", msg->DebugString().c_str());
			delete msg;
		}
	}

}