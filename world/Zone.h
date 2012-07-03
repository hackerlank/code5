#ifndef _ZONE_H
#define _ZONE_H

#include "AOIService.h"
#include "MapMask.h"

class Zone {
public:
	Zone(long id, SPMapMask& mm);

	void addEntity(SPEntity& entity);
	void removeEntityById(entity_id);
	
	void _onAreaAppear(AOIArea* area, WEntity& entity);
	void _onAreaDisappear(AOIArea* area, WEntity& entity);
	void _onAreaMove(AOIArea* area, WEntity& entity);
public:
	long _id;
	const SPAOIService _aoi;
	const SPMapMask _mapMask;
};

typedef boost::shared_ptr<Zone> SPZone;

#endif
