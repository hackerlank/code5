#include "MapMgr.h"

bool MapMgr::load(const char* fn) {
	return true;
}

SPMapMask MapMgr::getMap(int id) {
	MapMaskMap::iterator itr = _maps.find(id);
	return itr != _maps.end() ? itr->second : SPMapMask();
}

void MapMgr::removeZone(long zoneId) {
	_zones.erase(zoneId);
}


SPZone MapMgr::createZone(int mapId, bool dynamic) {
	SPMapMask mask = getMap(mapId);
	if (!mask)
		return SPZone();
	
	static long s_idAcc = 1;
	long zoneId = mapId | ((s_idAcc++) << 16);

	SPZone zone(new Zone(zoneId, mask));
	_zones[zoneId] = zone;
	return zone;
}

SPZone MapMgr::getZone(long zoneId) {
	ZoneMap::iterator itr = _zones.find(zoneId);
	return itr != _zones.end() ? itr->second : SPZone();
}
