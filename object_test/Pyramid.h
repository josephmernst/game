#ifndef _PYRAMID_H_
#define _PYRAMID_H_

#include "Object.h"


class Pyramid : public virtual Object{
 public:
	Pyramid();
	~Pyramid();
	Pyramid(const Pyramid & orig);
	virtual void draw();
};


#endif
