#ifndef BLOCK_H
#define BLOCK_H 

#include <utility>
#include <iostream>
class Block{
	public:
		Block *leftBot, *botLeft, *rightTop, *topRight;
		int height, width;
		bool isSolid;
		std::pair<int, int> lowerLeftCornerCoordinate;

		Block (std::pair<int, int> coordinate, Block *lb, Block *bl, Block *rt, Block *tr, int height, int width, bool isSolid);
		void PrintContent(){
			std::cout << "(x, y): " << lowerLeftCornerCoordinate.first << ", " << lowerLeftCornerCoordinate.second << std::endl;
			std::cout << "width: " << width << std::endl;
			std::cout << "height: " << height << std::endl;
			std::cout << "isSolid: " << isSolid << std::endl;
		}
};

#endif