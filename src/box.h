#ifndef BOX_H
#define BOX_H 

#include "block.h"
class Box{
	public:
		int width;
		int height;
		Block *headBlock;
		void setWidthAndHeight(int, int);
};

#endif