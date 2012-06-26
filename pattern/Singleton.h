#ifndef _PATTERN_H
#define _PATTERN_H

template<class T>
class Singleton {
public:
	static T& instance() {
		static T* _instance = 0;
		if (!_instance)
			_instance = new T();
		return *_instance;
	}
};

#endif