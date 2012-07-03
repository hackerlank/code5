#ifndef _PLAYER_H
#define _PLAYER_H

#include "Entity.h"

class Player: public Entity {
public:
	Player(player_id id);

	template<class T>
	void send(T* msg) {

	}
private:
	player_id _playerId;
};

#endif
