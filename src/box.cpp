#include "box.h"
#include<stdio.h>
#include <iostream>
#include <vector>
void Box::setWidthAndHeight(int width, int height){
	this->width = width;
	this->height = height;
}

bool Box::searchIsSolidBlock(int xCoordinate, int yCoordinate, int width, int height){
	if(yCoordinate <= 0)return false;
	Block *currentBlock = this->searchPointInBlock(xCoordinate, yCoordinate+height-1);
	while(currentBlock != NULL){
		if(currentBlock->lowerLeftCornerCoordinate.second+currentBlock->height>=yCoordinate){
			return false;
		}
		if(currentBlock->isSolid){
			return true;
		}else if(currentBlock->topRight != NULL){
				if(currentBlock->topRight->lowerLeftCornerCoordinate.first < xCoordinate+width){
					return true;
				}else if(currentBlock->leftBot != NULL){
						currentBlock = currentBlock->leftBot;
				}else{
					return false;
				}
		}
	}
	return false;
}


std::vector<Block*> Box::searchBlocks(int xCoordinate, int yCoordinate, int width, int height){
	std::vector<Block*> res;
	int curYCoordinate = yCoordinate+height-1;
	while(curYCoordinate > yCoordinate){
		
		Block *currentBlock = this->searchPointInBlock(xCoordinate, curYCoordinate);
		if (currentBlock == NULL)return res;
		this->recursiveEnumerate(currentBlock, &res,  xCoordinate, yCoordinate, width, height);
		curYCoordinate -= currentBlock->height;
	}
	return res;
}

void Box::recursiveEnumerate(Block *curBlock, std::vector<Block*>*res, int xCoordinate, int yCoordinate, int width, int height){
	if(curBlock == NULL)return;
	res->push_back(curBlock);
	if(curBlock->lowerLeftCornerCoordinate.first > xCoordinate+width)return;
	std::vector<Block*>neighbors = this->searchRightNeighbors(curBlock);
	std::vector<Block*>insetNeighbor;
	for(auto i: neighbors){
		if(i->lowerLeftCornerCoordinate.second <= yCoordinate+height && i->lowerLeftCornerCoordinate.second+i->height > yCoordinate
		&&i->lowerLeftCornerCoordinate.first <=xCoordinate+width){
			insetNeighbor.push_back(i);
		}
	}
	for(auto i: insetNeighbor){
		if(i->botLeft == curBlock){
			recursiveEnumerate(i, res, xCoordinate, yCoordinate, width, height);
		}else if(i->lowerLeftCornerCoordinate.second<yCoordinate && curBlock->lowerLeftCornerCoordinate.second<yCoordinate){
			recursiveEnumerate(i, res, xCoordinate, yCoordinate, width, height);
		}
	}

	return;
}


Block* Box::searchPointInBlock(int xCoordinate, int yCoordinate){
	if(xCoordinate < 0 || yCoordinate < 0 || xCoordinate > width || yCoordinate > height){
		return NULL;
	}
	Block *currentBlock = this->headBlock;
	while(currentBlock != NULL){
		if(yCoordinate >= currentBlock->lowerLeftCornerCoordinate.second+currentBlock->height){
			currentBlock = currentBlock->rightTop;
		}else if (yCoordinate < currentBlock->lowerLeftCornerCoordinate.second){
			currentBlock = currentBlock->leftBot;
		}else{
			if(xCoordinate >= currentBlock->lowerLeftCornerCoordinate.first+currentBlock->width){
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
	if(targetBlock == NULL)return res;
	Block *currentBlock = targetBlock->topRight;
	while(currentBlock!=NULL){
		res.push_back(currentBlock);
		currentBlock = currentBlock->leftBot;
		if(currentBlock==NULL)break;
		if(currentBlock->lowerLeftCornerCoordinate.second+currentBlock->height <= targetBlock->lowerLeftCornerCoordinate.second){
			break;
		}
	}
	return res;
}

std::vector<Block*> Box::searchLeftNeighbors(Block *targetBlock){
	std::vector<Block*> res;
	if(targetBlock == NULL)return res;
	Block *currentBlock = targetBlock->botLeft;
	while(currentBlock!=NULL){

		res.push_back(currentBlock);
		currentBlock = currentBlock->rightTop;
		if(currentBlock==NULL)break;
		if(currentBlock->lowerLeftCornerCoordinate.second 
			>= targetBlock->lowerLeftCornerCoordinate.second+targetBlock->height){
			break;
		}
	}

	return res;
}

std::vector<Block*> Box::searchTopNeighbors(Block *targetBlock){
	std::vector<Block*> res;
	if(targetBlock == NULL)return res;
	Block *currentBlock = targetBlock->rightTop;
	
	while(currentBlock != NULL){
		res.push_back(currentBlock);
		currentBlock = currentBlock->botLeft;
		if(currentBlock==NULL)break;
		if(currentBlock->lowerLeftCornerCoordinate.first+currentBlock->width <= targetBlock->lowerLeftCornerCoordinate.first){
			break;
		}
	}
	return res;
}

std::vector<Block*> Box::searchBotNeighbors(Block *targetBlock){
	std::vector<Block*> res;
	if(targetBlock == NULL)return res;
	Block *currentBlock = targetBlock->leftBot;
	
	while(currentBlock != NULL){
		res.push_back(currentBlock);
		currentBlock = currentBlock->topRight;
		if(currentBlock==NULL)break;
		if(currentBlock->lowerLeftCornerCoordinate.first
			>= targetBlock->lowerLeftCornerCoordinate.first+targetBlock->width){
			break;
		}
	}
	return res;
}




Block *Box::findDownBlock(Block *targetBlock, int xCoordinate){
	//return this->searchPointInBlock(xCoordinate, targetBlock->lowerLeftCornerCoordinate.second-1);
	
	std::vector<Block*> topBlockBotNeighbors = this->searchBotNeighbors(targetBlock);
	for(Block * i: topBlockBotNeighbors){
		if(i->lowerLeftCornerCoordinate.first <= xCoordinate && 
			i->lowerLeftCornerCoordinate.first+i->width > xCoordinate){
			return i;
		}
	}
	return NULL;
}

Block* Box::createBlock(int xCoordinate, int yCoordinate, int width, int height, int index){
	if(this->searchIsSolidBlock(xCoordinate, yCoordinate, width, height)){
		return NULL;
	}
	Block *topBlock = this->searchPointInBlock(xCoordinate, yCoordinate+height);
	Block *startBlock = this->splitBlock(yCoordinate+height, topBlock);
	Block *botBlock = this->searchPointInBlock(xCoordinate, yCoordinate);
	Block *endBlock = this->splitBlock(yCoordinate, botBlock);

	Block *newBlock = new Block(std::pair<int,int>(xCoordinate, yCoordinate), NULL, NULL,
	 NULL, NULL, height, width, true, index);
	Block *leftLastBlock = NULL;
	Block *rightLastBlock = NULL;
	Block *currentBlock = startBlock;


	if (currentBlock == NULL){
		currentBlock = this->searchPointInBlock(xCoordinate, yCoordinate+height-1);
		//currentBlock->PrintContent();
		// std::vector<Block*> topBlockBotNeighbors = this->searchBotNeighbors(topBlock);
		// for(Block * i: topBlockBotNeighbors){
		// 	if(i->lowerLeftCornerCoordinate.first <= xCoordinate && 
		// 		i->lowerLeftCornerCoordinate.first+i->width > xCoordinate){
		// 		currentBlock = i;
		// 		break;
		// 	}
		// }
	}
	if(currentBlock == NULL){
		return NULL;
	}
	std::vector<Block*> currentBlockTopNeighbors = this->searchTopNeighbors(currentBlock);
	for(Block* i: currentBlockTopNeighbors){
		if(i->lowerLeftCornerCoordinate.first < xCoordinate+width && newBlock->rightTop == NULL){
			newBlock->rightTop = i;
			break;
		}
	}



	while(currentBlock != NULL){
		if(currentBlock == endBlock){
			break;
		}
		std::vector<Block*> topNeighbors = this->searchTopNeighbors(currentBlock);
		std::vector<Block*> botNeighbors = this->searchBotNeighbors(currentBlock);
		std::vector<Block*> leftNeighbors = this->searchLeftNeighbors(currentBlock);
		std::vector<Block*> rightNeighbors = this->searchRightNeighbors(currentBlock);
		if(xCoordinate > currentBlock->lowerLeftCornerCoordinate.first){
			Block *newLeftBlock = new Block(currentBlock->lowerLeftCornerCoordinate, currentBlock->leftBot, 
			currentBlock->botLeft, leftLastBlock, newBlock, currentBlock->height,
			xCoordinate-currentBlock->lowerLeftCornerCoordinate.first, false, -1);
			if(newLeftBlock->rightTop == NULL){
				for(auto i: topNeighbors){
					if(newLeftBlock->lowerLeftCornerCoordinate.first+ newLeftBlock->width >
						i->lowerLeftCornerCoordinate.first){
						newLeftBlock->rightTop = i;
						break;

					}
				}
			}
			if (leftLastBlock == NULL){
				leftLastBlock = newLeftBlock;
			}else if(newLeftBlock->width == leftLastBlock->width && !leftLastBlock->isSolid){
				leftLastBlock->height += newLeftBlock->height;
				leftLastBlock->leftBot = newLeftBlock->leftBot;
				leftLastBlock->botLeft = newLeftBlock->botLeft;
				leftLastBlock->lowerLeftCornerCoordinate = newLeftBlock->lowerLeftCornerCoordinate;
				delete newLeftBlock;
			}else{
				if(leftLastBlock->width<newLeftBlock->width){
					leftLastBlock->leftBot = newLeftBlock;
				}
				leftLastBlock = newLeftBlock;

			}
			//add leftNeighbors point to leftlast
			
			for(Block *i : leftNeighbors){
				i->topRight = leftLastBlock;
			}
			
			//add topNeighbors to leftlast
			for(Block *i : topNeighbors){
				if(i->lowerLeftCornerCoordinate.first < xCoordinate 
					&& i->lowerLeftCornerCoordinate.first >= leftLastBlock->lowerLeftCornerCoordinate.first){
					i->leftBot = leftLastBlock;	
				}
			}

			//add botNeighbors to leftlast
			for(Block *i : botNeighbors){
				if(i->lowerLeftCornerCoordinate.first+i->width > leftLastBlock->lowerLeftCornerCoordinate.first 
					&& i->lowerLeftCornerCoordinate.first+i->width <= xCoordinate){
					i->rightTop = leftLastBlock;	
				}
			}
		}else{
			leftLastBlock = currentBlock->botLeft;
		}
		// currentBlock->PrintContent();
		// leftLastBlock->PrintContent();
		
		if(xCoordinate+width < currentBlock->lowerLeftCornerCoordinate.first+currentBlock->width){
			Block *newRightBlock = new Block(std::pair<int, int>(xCoordinate+width, 
				currentBlock->lowerLeftCornerCoordinate.second), NULL, newBlock, rightLastBlock, 
				currentBlock->topRight, currentBlock->height,
				currentBlock->lowerLeftCornerCoordinate.first+currentBlock->width-(xCoordinate+width), false, -1);
				newRightBlock->leftBot = this->findDownBlock(currentBlock, newRightBlock->lowerLeftCornerCoordinate.first);
			if(rightLastBlock == NULL){
				rightLastBlock = newRightBlock;
			}else if(newRightBlock->width == rightLastBlock->width && !rightLastBlock->isSolid){
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
			
			for(Block *i : rightNeighbors){
				i->botLeft = rightLastBlock;
			}

			//add topNeighbors to rightlast
			for(Block *i : topNeighbors){
				if(i->lowerLeftCornerCoordinate.first < rightLastBlock->lowerLeftCornerCoordinate.first+rightLastBlock->width
					&& i->lowerLeftCornerCoordinate.first >= rightLastBlock->lowerLeftCornerCoordinate.first){
					i->leftBot = rightLastBlock;	
				}
			}

			//add botNeighbors to rightlast
			for(Block *i : botNeighbors){
				if(i->lowerLeftCornerCoordinate.first+i->width > rightLastBlock->lowerLeftCornerCoordinate.first 
					&& i->lowerLeftCornerCoordinate.first+i->width <= rightLastBlock->lowerLeftCornerCoordinate.first+rightLastBlock->width){
					i->rightTop = rightLastBlock;	
				}
			}

		}else{

			if(!rightNeighbors.empty()){
				if(rightLastBlock != NULL){
					rightLastBlock->leftBot = rightNeighbors.front();
				}
				rightLastBlock = rightNeighbors.back();
			}
		}

		
		Block *tempBlock = currentBlock;
		currentBlock = this->findDownBlock(currentBlock, xCoordinate);
		if(tempBlock == this->headBlock){
			this->headBlock = newBlock;
		}
		if(tempBlock->lowerLeftCornerCoordinate.second == yCoordinate){
			newBlock->leftBot = currentBlock;
			newBlock->botLeft = leftLastBlock;
			if(rightLastBlock->lowerLeftCornerCoordinate.second < newBlock->lowerLeftCornerCoordinate.second+newBlock->height){
				rightLastBlock->botLeft = newBlock;
			}
			std::vector<Block *> endBlockLeftNeighbors = this->searchLeftNeighbors(currentBlock);
			std::vector<Block*> endBlockRightNeighbors = this->searchRightNeighbors(currentBlock);
			
			if(!endBlockLeftNeighbors.empty()){	
				Block* curLeftNeightbor = endBlockLeftNeighbors.back();
				if(curLeftNeightbor->width == leftLastBlock->width && !leftLastBlock->isSolid && !curLeftNeightbor->isSolid &&
					 leftLastBlock->lowerLeftCornerCoordinate.first == curLeftNeightbor->lowerLeftCornerCoordinate.first){
					leftLastBlock->height += curLeftNeightbor->height;
					leftLastBlock->leftBot = curLeftNeightbor->leftBot;
					leftLastBlock->botLeft = curLeftNeightbor->botLeft;
					leftLastBlock->lowerLeftCornerCoordinate = curLeftNeightbor->lowerLeftCornerCoordinate;
					std::vector<Block*> curLeftNeightborLeftNeightbors = this->searchLeftNeighbors(curLeftNeightbor);
					std::vector<Block*> curLeftNeightborBotNeightbors = this->searchBotNeighbors(curLeftNeightbor);
					std::vector<Block*> curLeftNeightborRightNeightbors = this->searchRightNeighbors(curLeftNeightbor);
					for(auto i: curLeftNeightborLeftNeightbors){
						if(i->topRight == curLeftNeightbor){
							i->topRight = leftLastBlock;
						}
					}
					for(auto i: curLeftNeightborBotNeightbors){
						if(i->rightTop == curLeftNeightbor){
							i->rightTop = leftLastBlock;
						}
					}
					for(auto i:curLeftNeightborRightNeightbors){
						if(i->botLeft == curLeftNeightbor){
							i->botLeft = leftLastBlock;
						}
					}

					delete curLeftNeightbor;
				}else{
					if(leftLastBlock->lowerLeftCornerCoordinate.first >= curLeftNeightbor->lowerLeftCornerCoordinate.first&&
						leftLastBlock->lowerLeftCornerCoordinate.first < curLeftNeightbor->width+curLeftNeightbor->lowerLeftCornerCoordinate.first)
							leftLastBlock->leftBot = curLeftNeightbor;
				}		
			}
			

			
			if(!endBlockRightNeighbors.empty()){
				Block *right = endBlockRightNeighbors.front();
				if(right->width == rightLastBlock->width && !right->isSolid && !rightLastBlock->isSolid && 
					right->lowerLeftCornerCoordinate.first == rightLastBlock->lowerLeftCornerCoordinate.first){
					rightLastBlock->height += right->height;
					rightLastBlock->leftBot = right->leftBot;
					rightLastBlock->botLeft = right->botLeft;
					rightLastBlock->lowerLeftCornerCoordinate = right->lowerLeftCornerCoordinate;
					std::vector<Block*> curLeftNeightborRightNeightbors = this->searchRightNeighbors(right);
					std::vector<Block*> curLeftNeightborBotNeightbors = this->searchBotNeighbors(right);
					std::vector<Block*> curLeftNeightborLeftNeightbors = this->searchLeftNeighbors(right);
					for(auto i: curLeftNeightborRightNeightbors){
						if(i->botLeft == i){
							i->botLeft = rightLastBlock;
						}
					}
					for(auto i: curLeftNeightborBotNeightbors){
						if(i->rightTop == i){
							i->rightTop = rightLastBlock;
						}
					}
					for(auto i: curLeftNeightborLeftNeightbors){
						if(i->topRight == i){
							i->topRight = rightLastBlock;
						}
					}
					delete right;
				}else{	
					if(right->lowerLeftCornerCoordinate.first >= rightLastBlock->lowerLeftCornerCoordinate.first&&
						right->lowerLeftCornerCoordinate.first+right->width < rightLastBlock->lowerLeftCornerCoordinate.first){
						rightLastBlock->leftBot = right;	
					}
				}
				
			}
			delete tempBlock;
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
		yCoordinate-targetBlock->lowerLeftCornerCoordinate.second, targetBlock->width, targetBlock->isSolid, -1);

	std::vector<Block *> targetBlockRightNeighbors = this->searchRightNeighbors(targetBlock);
	std::vector<Block *> targetBlockBotNeighbors = this->searchBotNeighbors(targetBlock);
	std::vector<Block *> targetBlockLeftNeighbors = this->searchLeftNeighbors(targetBlock);

	for(Block *i : targetBlockRightNeighbors){
		if(i->lowerLeftCornerCoordinate.second < newBlock->lowerLeftCornerCoordinate.second + newBlock->height){
			if(newBlock->topRight == NULL){
				newBlock->topRight = i;
			}
			i->botLeft = newBlock;
		}else{
			i->botLeft = targetBlock;
		}
	}
	
	
	for(Block *i: targetBlockBotNeighbors){
		if(i->lowerLeftCornerCoordinate.first+width < newBlock->lowerLeftCornerCoordinate.second+newBlock->width){
			i->rightTop = newBlock;
		}
	}

	
	targetBlock->botLeft = NULL;
	for(Block *i : targetBlockLeftNeighbors){
		if(i->lowerLeftCornerCoordinate.second+i->height > targetBlock->lowerLeftCornerCoordinate.second){
			if(targetBlock->botLeft == NULL){
				targetBlock->botLeft = i;
			}
			i->topRight = targetBlock;
		}else if(i->lowerLeftCornerCoordinate.second > newBlock->lowerLeftCornerCoordinate.second) {
			i->topRight = newBlock;
		}
	}

	

	targetBlock->height -= (yCoordinate - targetBlock->lowerLeftCornerCoordinate.second);
	targetBlock->lowerLeftCornerCoordinate.second = yCoordinate;
	targetBlock->leftBot = newBlock;
	return newBlock;
	
}

