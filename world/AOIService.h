#ifndef _AOISERVICE_H
#define _AOISERVICE_H

#include <boost/function.hpp>
#include <list>
#include <map>
#include <vector>

#include "Entity.h"
#include "math/math.h"

using std::list;
using std::map;
using std::vector;

class AOIArea {
public:
	typedef list<WEntity> EntityList;

	void add(WEntity& entity) {

	}

	void remove(entity_id id) {

	}

	EntityList _entities;
};

typedef vector<AOIArea*> AreaList;

typedef void (*AOIHandler)(AOIArea*, WEntity&);
//typedef boost::function<bool, WEntity&> EntityMatchFunc;

class AOIService {
public:
	enum {
		AreaW = 8, 
		AreaH = 8 
	};

	typedef map<entity_id, WEntity> EntityMap;

	AOIService(int w, int h);

	void moveTo(WEntity& entity, int x, int y);
	//void add(WEntity& entity);
	void appear(WEntity& entity, bool addNew = false);
	void remove(entity_id id);
	
	inline AOIArea* getArea(int x, int y){
		if ( x < 0 || x >= _widthArea || y < 0 || y >= _heightArea)
			return NULL;

		return &_areas[x][y];
	}

	inline AOIArea* getAreaByPos(int x, int y) {
		return getArea(UpperDiv(x, AreaW), UpperDiv(y, AreaH));
	}

	AreaList& getArea9(int x, int y);
	inline	AreaList& getArea9ByPos(int x, int y){ 
		return getArea9(UpperDiv(x, AreaW), UpperDiv(y, AreaH));
	}
	
	inline WEntity getEntity(entity_id id);

//	WEntity searchNear(int x, int y, EntityMatchFunc& matchFunc, int areaDis = 2);
public:
	inline void setHandlers(AOIHandler& appear, AOIHandler& disappear, AOIHandler move) {

		_onApear = appear;
		_onDisapear = disappear;
		_onMove = move;
}
	AOIHandler _onApear;
	AOIHandler _onDisapear;
	AOIHandler _onMove;

	AOIArea** _areas;
	const int	_width;
	const int	_height;
	
	const int 	_widthArea;
	const int	_heightArea;
	EntityMap	_entities;
};

typedef boost::shared_ptr<AOIService> SPAOIService;
#endif
