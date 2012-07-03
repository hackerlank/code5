#ifndef _ENTITY_H
#define _ENTITY_H

#include "_types.h"
enum EntityType{
	ETPlayer
};

class Entity {
public:
	Point _position;
	entity_id _id;
	EntityType _entityType;
};

typedef boost::shared_ptr<Entity> SPEntity;
typedef boost::weak_ptr<Entity> WEntity;

#endif
