#include "block.h"
#include <iostream>
Block::Block (std::pair<int, int> coordinate, Block *lb, Block *bl, Block *rt, Block *tr, int height, int width){
	leftBot = lb;
	botLeft = bl;
	rightTop = rt;
	topRight = tr;
	lowerLeftCornerCoordinate = coordinate;
	this->width = width;
	this->height = height;
}