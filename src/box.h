#ifndef BOX_H
#define BOX_H 

#include "block.h"
#include <vector>
class Box{
	public:
		int width;
		int height;
		Block *headBlock;
		void setWidthAndHeight(int, int);
		Block* createBlock(int xCoordinate, int yCoordinate, int width, int height);
		bool searchIsSolidBlock(int xCoordinate, int yCoordinate, int width, int height);
		std::vector<Block*> searchBlocks(int xCoordinate, int yCoordinate, int width, int height);
		Block* searchPointInBlock(int xCoordinate, int yCoordinate);
		std::vector<Block*> searchNeighbors(Block *);
		std::vector<Block*> searchRightNeighbors(Block *targetBlock);
		std::vector<Block*> searchLeftNeighbors(Block *targetBlock);
		std::vector<Block*> searchTopNeighbors(Block *targetBlock);
		std::vector<Block*> searchBotNeighbors(Block *targetBlock);
		Block* splitBlock(int yCoordinate, Block *targetBlock);
		Block* findDownBlock(Block *targetBlock, int xCoordinate);
};

#endif