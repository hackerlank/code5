#ifndef _MAPMASK_H
#define _MAPMASK_H

#include "_types.h"

class MapMask {
public:
	MapMask(int w, int h, byte** m)
		:width(w), height(h), masks(m)
	{}

	~MapMask() {
		if (masks)
			delete[] masks;
	}

	int width;
	int height;
	byte** masks;
};

typedef boost::shared_ptr<MapMask> SPMapMask;

#endif
