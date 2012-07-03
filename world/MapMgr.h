#ifndef _MAPMGR_H
#define _MAPMGR_H

#include "MapMask.h"
#include "Zone.h"
#include "pattern/Singleton.h" 

#include <map>
#include "_types.h"

using std::map;

class MapMgr :public Singleton<MapMgr>{
public:
	typedef map<int, SPMapMask> MapMaskMap;
	typedef map<long, SPZone> ZoneMap;

	bool load(const char* fn);

	SPMapMask getMap(int id);

	void removeZone(long zoneId);

	SPZone createZone(int mapId, bool dynamic);
	SPZone getZone(long zoneId);

private:
	MapMaskMap _maps;
	ZoneMap	 _zones;
};

#endif
