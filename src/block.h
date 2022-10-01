#ifndef BLOCK_H
#define BLOCK_H 

#include <utility>
#include <iostream>
class Block{
	public:
		Block *leftBot;
		Block *botLeft;
		Block *rightTop;
		Block *topRight;
		std::pair<int, int> lowerLeftCornerCoordinate;
		int height;
		int width;
		Block (std::pair<int, int> coordinate, Block *lb, Block *bl, Block *rt, Block *tr, int height, int width);
		void PrintContent(){
			std::cout << width << " " << height << std::endl;
		}
};

#endif