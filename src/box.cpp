#include "box.h"
#include <iostream>
#include <vector>
void Box::setWidthAndHeight(int width, int height){
	this->width = width;
	this->height = height;
}

bool Box::searchIsSolidBlock(int xCoordinate, int yCoordinate, int width, int height){
	Block *currentBlock = this->searchPointInBlock(xCoordinate, yCoordinate+height);
	while(currentBlock != NULL){
		if(currentBlock->isSolid){
			return true;
		}else if(currentBlock->topRight != NULL){
				if(currentBlock->topRight->lowerLeftCornerCoordinate.first <= xCoordinate+width){
					return true;
				}
		}else{
			if(currentBlock->leftBot != NULL){
				if(currentBlock->leftBot->lowerLeftCornerCoordinate.second+yCoordinate < yCoordinate){
					currentBlock = currentBlock->leftBot;
				}else{
					return false;
				}
			}else{
				return false;
			}
		}
	}

	return false;

}


std::vector<Block*> Box::searchBlocks(int xCoordinate, int yCoordinate, int width, int height){
	std::vector<Block*> v;

	return v;

}

Block* Box::searchPointInBlock(int xCoordinate, int yCoordinate){
	if(xCoordinate < 0 || yCoordinate < 0 || xCoordinate > width || yCoordinate > height){
		return NULL;
	}
	Block *currentBlock = this->headBlock;
	while(currentBlock != NULL){
		if(yCoordinate >= currentBlock->lowerLeftCornerCoordinate.second+height){
			currentBlock = currentBlock->rightTop;
		}else if (yCoordinate < currentBlock->lowerLeftCornerCoordinate.second){
			currentBlock = currentBlock->leftBot;
		}else{
			if(xCoordinate >= currentBlock->lowerLeftCornerCoordinate.first+width){
				currentBlock = currentBlock->topRight;
			}else if(xCoordinate < currentBlock->lowerLeftCornerCoordinate.first){
				currentBlock = currentBlock->botLeft;
			}else{
				return currentBlock;
			}
		}
	}
	return currentBlock;
}

std::vector<Block*> Box::searchNeighbors(Block *targetBlock){
	std::vector<Block*> res, subNeighbors;
	subNeighbors = this->searchRightNeighbors(targetBlock);
	res.insert(std::end(res), std::begin(subNeighbors), std::end(subNeighbors));
	subNeighbors = this->searchBotNeighbors(targetBlock);
	res.insert(std::end(res), std::begin(subNeighbors), std::end(subNeighbors));
	subNeighbors = this->searchLeftNeighbors(targetBlock);
	res.insert(std::end(res), std::begin(subNeighbors), std::end(subNeighbors));
	subNeighbors = this->searchTopNeighbors(targetBlock);
	res.insert(std::end(res), std::begin(subNeighbors), std::end(subNeighbors));
	return res;
}
std::vector<Block*> Box::searchRightNeighbors(Block *targetBlock){
	std::vector<Block*> res;
	Block *currentBlock = targetBlock->topRight;
	while(currentBlock!=NULL){

		res.push_back(currentBlock);
		if(currentBlock->lowerLeftCornerCoordinate.second <= targetBlock->lowerLeftCornerCoordinate.second){
			break;
		}
		currentBlock = currentBlock->leftBot;
	}

	return res;
}

std::vector<Block*> Box::searchLeftNeighbors(Block *targetBlock){
	std::vector<Block*> res;
	Block *currentBlock = targetBlock->botLeft;
	while(currentBlock!=NULL){

		res.push_back(currentBlock);
		if(currentBlock->lowerLeftCornerCoordinate.second+currentBlock->height 
			>= targetBlock->lowerLeftCornerCoordinate.second+targetBlock->height){
			break;
		}
		currentBlock = currentBlock->rightTop;
	}

	return res;
}

std::vector<Block*> Box::searchTopNeighbors(Block *targetBlock){
	std::vector<Block*> res;
	Block *currentBlock = targetBlock->rightTop;
	
	while(currentBlock != NULL){
		res.push_back(currentBlock);
		if(currentBlock->lowerLeftCornerCoordinate.first <= targetBlock->lowerLeftCornerCoordinate.first){
			break;
		}
		currentBlock = currentBlock->botLeft;
	}
	return res;
}

std::vector<Block*> Box::searchBotNeighbors(Block *targetBlock){
	std::vector<Block*> res;
	Block *currentBlock = targetBlock->leftBot;
	
	while(currentBlock != NULL){
		res.push_back(currentBlock);
		if(currentBlock->lowerLeftCornerCoordinate.first+currentBlock->width 
			>= targetBlock->lowerLeftCornerCoordinate.first+targetBlock->width){
			break;
		}
		currentBlock = currentBlock->topRight;
	}
	return res;
}




Block *Box::findDownBlock(Block *targetBlock, int xCoordinate){
	std::vector<Block*> topBlockBotNeighbors = this->searchBotNeighbors(targetBlock);
		for(Block * i: topBlockBotNeighbors){
			if(i->lowerLeftCornerCoordinate.first <= xCoordinate && 
				i->lowerLeftCornerCoordinate.first+i->width > xCoordinate){
				return i;
			}
		}
		return NULL;
	}


Block* Box::createBlock(int xCoordinate, int yCoordinate, int width, int height){
	if(this->searchIsSolidBlock(xCoordinate, yCoordinate, width, height)){
		return NULL;
	}
	Block *topBlock = this->searchPointInBlock(xCoordinate, yCoordinate+height);
	Block *startBlock = this->splitBlock(yCoordinate+height, topBlock);
	Block *botBlock = this->searchPointInBlock(xCoordinate, yCoordinate);
	Block *endBlock = this->splitBlock(yCoordinate, botBlock);

	Block *newBlock = new Block(std::pair<int,int>(xCoordinate, yCoordinate), NULL, NULL,
	 NULL, NULL, height, width, true);
	Block *leftLastBlock = NULL;
	Block *rightLastBlock = NULL;
	Block *currentBlock = startBlock;


	if (currentBlock == NULL){
		std::vector<Block*> topBlockBotNeighbors = this->searchBotNeighbors(topBlock);
		for(Block * i: topBlockBotNeighbors){
			if(i->lowerLeftCornerCoordinate.first <= xCoordinate && 
				i->lowerLeftCornerCoordinate.first+i->width > xCoordinate){
				currentBlock = i;
				break;
			}
		}
	}
	if(currentBlock == NULL){
		return NULL;
	}
	std::vector<Block*> currentBlockTopNeighbors = this->searchTopNeighbors(currentBlock);
	for(Block* i: currentBlockTopNeighbors){
		if(i->lowerLeftCornerCoordinate.first < xCoordinate+width && newBlock->rightTop == NULL){
			newBlock->rightTop = i;
		}
		if(i->lowerLeftCornerCoordinate.first < 
			currentBlock->lowerLeftCornerCoordinate.first){
			leftLastBlock = i;
			break;
		}
	}
	rightLastBlock = currentBlock->rightTop;



	while(currentBlock != NULL){
		if(currentBlock == endBlock){
			break;
		}
		std::vector<Block*> topNeighbors = this->searchTopNeighbors(currentBlock);
		std::vector<Block*> botNeighbors = this->searchBotNeighbors(currentBlock);
		
		if(xCoordinate > currentBlock->lowerLeftCornerCoordinate.first){
			Block *newLeftBlock = new Block(currentBlock->lowerLeftCornerCoordinate, currentBlock->leftBot, 
			currentBlock->leftBot, leftLastBlock, newBlock, currentBlock->height,
			xCoordinate-currentBlock->lowerLeftCornerCoordinate.first, false);
			if (leftLastBlock == NULL){
				leftLastBlock = newLeftBlock;
			}else if(newLeftBlock->width == leftLastBlock->width){
				leftLastBlock->height += newLeftBlock->height;
				leftLastBlock->leftBot = newLeftBlock->leftBot;
				leftLastBlock->botLeft = newLeftBlock->botLeft;
				leftLastBlock->lowerLeftCornerCoordinate = newLeftBlock->lowerLeftCornerCoordinate;
				delete newLeftBlock;
			}else{
				leftLastBlock = newLeftBlock;
			}
			//add leftNeighbors point to leftlast
			std::vector<Block*> leftNeighbors = this->searchLeftNeighbors(currentBlock);
			for(Block *i : leftNeighbors){
				i->topRight = leftLastBlock;
			}
			
			//add topNeighbors to leftlast
			for(Block *i : topNeighbors){
				if(i->lowerLeftCornerCoordinate.first >= leftLastBlock->lowerLeftCornerCoordinate.first 
					&& i->lowerLeftCornerCoordinate.first < xCoordinate){
					i->leftBot = leftLastBlock;	
				}
			}

			//add botNeighbors to leftlast
			for(Block *i : botNeighbors){
				if(i->lowerLeftCornerCoordinate.first+i->width > leftLastBlock->lowerLeftCornerCoordinate.first 
					&& i->lowerLeftCornerCoordinate.first+i->width < xCoordinate){
					i->rightTop = leftLastBlock;	
				}
			}
		}
		
		if(xCoordinate+width < currentBlock->lowerLeftCornerCoordinate.first+currentBlock->width){
			Block *newRightBlock = new Block(std::pair<int, int>(xCoordinate+width, 
				currentBlock->lowerLeftCornerCoordinate.second), NULL, newBlock, rightLastBlock, 
				currentBlock->topRight, currentBlock->height,
				currentBlock->lowerLeftCornerCoordinate.first+currentBlock->width-(xCoordinate+width), false);
			if(rightLastBlock == NULL){
				rightLastBlock = newRightBlock;
			}else if(newRightBlock->width == rightLastBlock->width){
				rightLastBlock->height += newRightBlock->height;
				rightLastBlock->leftBot = newRightBlock->leftBot;
				rightLastBlock->lowerLeftCornerCoordinate = newRightBlock->lowerLeftCornerCoordinate;
				delete newRightBlock;
			}else{
				rightLastBlock->leftBot = newRightBlock;
				rightLastBlock = newRightBlock;
			}

			if(newBlock->topRight == NULL){
				newBlock->topRight = rightLastBlock;
			}
			//add rightNeighbors to rightLast
			std::vector<Block*> rightNeighbors = this->searchRightNeighbors(currentBlock);
			for(Block *i : rightNeighbors){
				i->botLeft = rightLastBlock;
			}

			//add topNeighbors to leftlast
			for(Block *i : topNeighbors){
				if(i->lowerLeftCornerCoordinate.first >= rightLastBlock->lowerLeftCornerCoordinate.first 
					&& i->lowerLeftCornerCoordinate.first < rightLastBlock->lowerLeftCornerCoordinate.first){
					i->leftBot = rightLastBlock;	
				}
			}

			//add botNeighbors to leftlast
			for(Block *i : botNeighbors){
				if(i->lowerLeftCornerCoordinate.first+i->width > rightLastBlock->lowerLeftCornerCoordinate.first 
					&& i->lowerLeftCornerCoordinate.first+i->width < rightLastBlock->lowerLeftCornerCoordinate.first+rightLastBlock->width){
					i->rightTop = leftLastBlock;	
				}
			}

		}
		Block *tempBlock = currentBlock;
		currentBlock = this->findDownBlock(currentBlock, xCoordinate);
		if(tempBlock == this->headBlock){
			this->headBlock = newBlock;
		}
		if(currentBlock == endBlock){
			newBlock->leftBot = currentBlock;
			newBlock->botLeft = leftLastBlock;
			break;
		}
		delete tempBlock;

	}



	return newBlock;
}

Block* Box::splitBlock(int yCoordinate, Block *targetBlock){
	if(targetBlock == NULL){
		return NULL;
	}
	if(yCoordinate == targetBlock->lowerLeftCornerCoordinate.second){
		return NULL;
	}
	Block *newBlock = new Block(targetBlock->lowerLeftCornerCoordinate, targetBlock->leftBot, 
		targetBlock->botLeft, targetBlock, NULL,
		yCoordinate-targetBlock->lowerLeftCornerCoordinate.second, targetBlock->width, targetBlock->isSolid);

	std::vector<Block *> targetBlockRightNeighbors = this->searchRightNeighbors(targetBlock);
	for(Block *i : targetBlockRightNeighbors){
		if(i->lowerLeftCornerCoordinate.second < newBlock->lowerLeftCornerCoordinate.second + newBlock->height){
			newBlock->topRight = i;
			i->botLeft = newBlock;
			break;
		}
	}
	std::vector<Block *> targetBlockLeftNeighbors = this->searchLeftNeighbors(targetBlock);
	for(Block *i : targetBlockLeftNeighbors){
		if(i->lowerLeftCornerCoordinate.second+i->height > targetBlock->lowerLeftCornerCoordinate.second + targetBlock->height){
			targetBlock->botLeft = i;
			i->topRight = targetBlock;
			break;
		}
	}
	targetBlock->height -= (yCoordinate - targetBlock->lowerLeftCornerCoordinate.second);
	targetBlock->lowerLeftCornerCoordinate.second = yCoordinate;
	targetBlock->leftBot = newBlock;
	return newBlock;
	
}