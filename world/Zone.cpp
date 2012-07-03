#include "Zone.h"

Zone::Zone(long id, SPMapMask& mm)
	:_id(id), _mapMask(mm),	
	_aoi(new AOIService(_aoi->_width, _aoi->_height))
{
	//TODO init aoi service
	//_aoi->setHandlers(_onAreaAppear, _onAreaDisappear, _onAreaMove);
}

void Zone::addEntity(SPEntity& entity) {
	WEntity wentity(entity);
	_aoi->appear(wentity, true);
}

void Zone::removeEntityById(entity_id id) {
	_aoi->remove(id);
}

void Zone::_onAreaAppear(AOIArea* area, WEntity& entity) {

}

void Zone::_onAreaDisappear(AOIArea* area, WEntity& entity) {
}

void Zone::_onAreaMove(AOIArea* area, WEntity& entity) { 

}

