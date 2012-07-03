#include "AOIService.h"
#include <assert.h>

AOIService::AOIService(int w, int h) 
	:_width(w), _height(h), 
	_widthArea(UpperDiv(w, AreaW)), 
	_heightArea(UpperDiv(h, AreaH)) 
{
	_areas = (AOIArea**)(new AOIArea[ _widthArea * _heightArea]);
}

AreaList& AOIService::getArea9(int x, int y) {
	static AreaList s_area9;
	s_area9.clear();
	for ( int i = x - 1; i < x + 1; ++i) {
		for (int j = y - 1; j < y + 1; ++j)	{
			if ( x < 0 || x >= _widthArea || y < 0 || y >= _heightArea)
				s_area9.push_back(&_areas[i][j]);
		}
	}

	return s_area9;
}

void AOIService::moveTo(WEntity& entity, int x, int y) {
	SPEntity sentity = entity.lock();
	
	Point pos = entity.lock()->_position;
	AOIArea* areaFrom = getAreaByPos(pos.x, pos.y);
	AOIArea* areaTo = getAreaByPos(pos.x, pos.y);
	
	if (areaTo == areaFrom) {
		if (areaTo)
			_onMove(areaTo, entity);
	} else {
		//TODO dispear from back side
		//appear to the front side
		// move in the new 9 area
	}
}

/*
void AOIService::add(SPEntity& entity) {
	AOIArea* area = getAreaByPos(entity->position.x, entity->position.y);
	if (!area)
		return;

	area->add(entity);
	_entities[entity->_id] = entity;
}
*/

void AOIService::appear(WEntity& entity, bool addNew) {
	assert(!entity.expired());
	SPEntity sentity = entity.lock();

	EntityMap::iterator itr = _entities.find(sentity->_id);
	if (itr != _entities.end())
		return;
	
	AOIArea* areaTo = getAreaByPos(sentity->_position.x, sentity->_position.y);
	if (!areaTo)
		return;
	
	AreaList& areas = getArea9(sentity->_position.x, sentity->_position.y);
	for (AreaList::iterator itr = areas.begin(); itr != areas.end(); ++itr) 
		_onApear(*itr, entity);

	if (addNew) {
		areaTo->add(entity);
		_entities[sentity->_id] = entity;
	}
}

void AOIService::remove(entity_id id) {
	EntityMap::iterator itr = _entities.find(id);
	if (itr == _entities.end())
		return;

	
	WEntity entity(itr->second);
	AreaList& areas = getArea9(entity.lock()->_position.x, entity.lock()->_position.y);
	for (AreaList::iterator itr = areas.begin(); itr != areas.end(); ++itr) {
		_onDisapear(*itr, entity);
		(*itr)->remove(id);
	}
	
	_entities.erase(itr);
}

WEntity AOIService::getEntity(entity_id id) {
	EntityMap::iterator itr = _entities.find(id);
	return itr == _entities.end() ? WEntity() : itr->second;
}

/*
static WEntity nearEntityInArea(AOIArea* area, int x, int y, EntityMatchFunc& matchFunc, int &dis){
	#define _DIS(e) max(abs(x - e->position.x), abs(y - e->position.y))
	if (area) {
		for (AOIArea::EntityList::iterator itr = area->_entities.begin();
			itr != area->_entities.end(); ++itr) 
		{
			if (matchFunc(*itr)) {
				const int disNow =  _DIS(*itr);
				if ( disNow < dis) {
					dis = disNow;
					nearEntity = *itr;
				}
			}
		}
	}
}

//cycle out stratage
WEntity AOIService::searchNear(int x, int y, EntityMatchFunc& matchFunc, int areaDis ) {
	const int areaX = UpperDiv(x, AreaW);
	const int areaY = UpperDiv(y, AreaH);
	int disMin = INT_MAX;
	//for the center

	// TODO
	if (areaDis > 0) {
		WEntity entity =  nearEntityInArea(getArea(areaX, areaY), x, y, matchFunc, disMin);
		if (entity != NULL)
			return entity;
	}	

	// how to make a cube cycle
	for (int cycle = 1; cycle < areaDis; ++cycle) {
		WEntity nearEntity = NULL;
		for (int i = areaX - cycle ; i < areaX + cycle; ++i) {
			WEntity entity = nearEntityInArea(getArea(i, areaY + cycle), x, y, matchFunc, disMin);	
			if (entity

		}
	}
	return WEntity();
}

*/
