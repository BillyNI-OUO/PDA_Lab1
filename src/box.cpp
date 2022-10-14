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
	while(currentBlock != nullptr){
		if(currentBlock->lowerLeftCornerCoordinate.second + currentBlock->height > yCoordinate){
			return false;
		}
		if(currentBlock->isSolid){
			return true;
		}else if(currentBlock->topRight != nullptr){
				if(currentBlock->topRight->lowerLeftCornerCoordinate.first < xCoordinate+width){
					return true;
				}else if(currentBlock->leftBot != nullptr){
						currentBlock = currentBlock->leftBot;
				}else{
					return false;
				}
		}else{
			return false;
		}
	}
	return false;
}


std::vector<Block*> Box::searchBlocks(int xCoordinate, int yCoordinate, int width, int height){
	std::vector<Block*> res;
	int curYCoordinate = yCoordinate+height-1;
	while(curYCoordinate > yCoordinate){
		Block *currentBlock = this->searchPointInBlock(xCoordinate, curYCoordinate);
		if (currentBlock == nullptr)return res;
		this->recursiveEnumerate(currentBlock, &res,  xCoordinate, yCoordinate, width, height);
		curYCoordinate -= currentBlock->height;
	}
	return res;
}

void Box::recursiveEnumerate(Block *curBlock, std::vector<Block*>*res, int xCoordinate, int yCoordinate, int width, int height){
	if(curBlock == nullptr)return;
	res->push_back(curBlock);
	if(curBlock->lowerLeftCornerCoordinate.first+curBlock->width > xCoordinate+width)return;
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
		return nullptr;
	}
	Block *currentBlock = this->headBlock;
	while(currentBlock != nullptr){
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
	if(targetBlock == nullptr)return res;
	Block *currentBlock = targetBlock->topRight;
	while(currentBlock!=nullptr){
		res.push_back(currentBlock);
		currentBlock = currentBlock->leftBot;
		if(currentBlock==nullptr)break;
		if(currentBlock->lowerLeftCornerCoordinate.second+currentBlock->height <= targetBlock->lowerLeftCornerCoordinate.second){
			break;
		}
	}
	return res;
}

std::vector<Block*> Box::searchLeftNeighbors(Block *targetBlock){
	std::vector<Block*> res;
	if(targetBlock == nullptr)return res;
	Block *currentBlock = targetBlock->botLeft;
	while(currentBlock!=nullptr){

		res.push_back(currentBlock);
		currentBlock = currentBlock->rightTop;
		if(currentBlock==nullptr)break;
		if(currentBlock->lowerLeftCornerCoordinate.second 
			>= targetBlock->lowerLeftCornerCoordinate.second+targetBlock->height){
			break;
		}
	}

	return res;
}

std::vector<Block*> Box::searchTopNeighbors(Block *targetBlock){
	std::vector<Block*> res;
	if(targetBlock == nullptr)return res;
	Block *currentBlock = targetBlock->rightTop;
	
	while(currentBlock != nullptr){
		res.push_back(currentBlock);
		currentBlock = currentBlock->botLeft;
		if(currentBlock==nullptr)break;
		if(currentBlock->lowerLeftCornerCoordinate.first+currentBlock->width <= targetBlock->lowerLeftCornerCoordinate.first){
			break;
		}
	}
	return res;
}

std::vector<Block*> Box::searchBotNeighbors(Block *targetBlock){
	std::vector<Block*> res;
	if(targetBlock == nullptr)return res;
	Block *currentBlock = targetBlock->leftBot;
	
	while(currentBlock != nullptr){
		res.push_back(currentBlock);
		currentBlock = currentBlock->topRight;
		if(currentBlock==nullptr)break;
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
	return nullptr;
}

Block* Box::createBlock(int xCoordinate, int yCoordinate, int width, int height, int index){
	if(this->searchIsSolidBlock(xCoordinate, yCoordinate, width, height)){
		return nullptr;
	}
	Block *topBlock = this->searchPointInBlock(xCoordinate, yCoordinate+height);
	Block *startBlock = this->splitBlock(yCoordinate+height, topBlock);
	Block *botBlock = this->searchPointInBlock(xCoordinate, yCoordinate);
	Block *endBlock = this->splitBlock(yCoordinate, botBlock);

	
	Block *currentBlock = this->searchPointInBlock(xCoordinate, yCoordinate+height-1);
	if(currentBlock->lowerLeftCornerCoordinate.first == xCoordinate && currentBlock->lowerLeftCornerCoordinate.second == yCoordinate && currentBlock->width == width && currentBlock->height == height){
		currentBlock->index = index;
		currentBlock->isSolid = true;
		return currentBlock;
	}
	Block *newBlock = new Block(std::pair<int,int>(0, 0), nullptr, nullptr,
	 nullptr, nullptr, 0, 0, true, index);
	if(currentBlock == nullptr){
		return nullptr;
	}
	
	newBlock->topRight = this->searchPointInBlock(xCoordinate+width, yCoordinate+height-1);
	if(newBlock->topRight == currentBlock){
		newBlock->topRight = nullptr;
	}
	newBlock->rightTop = this->searchPointInBlock(xCoordinate+width-1, yCoordinate+height);
	

	while(currentBlock != nullptr){
		if(currentBlock == endBlock){
			break;
		}
		bool createLeft = false;
		bool createRight = false;
		std::vector<Block*> topNeighbors = this->searchTopNeighbors(currentBlock);
		std::vector<Block*> botNeighbors = this->searchBotNeighbors(currentBlock);
		std::vector<Block*> leftNeighbors = this->searchLeftNeighbors(currentBlock);
		std::vector<Block*> rightNeighbors = this->searchRightNeighbors(currentBlock);
		Block *nextBlock = this->searchPointInBlock(xCoordinate, currentBlock->lowerLeftCornerCoordinate.second-1);
		Block *leftLastBlock = this->searchPointInBlock(xCoordinate-1,currentBlock->lowerLeftCornerCoordinate.second+currentBlock->height);
		Block *rightLastBlock = this->searchPointInBlock(xCoordinate+width, currentBlock->lowerLeftCornerCoordinate.second+currentBlock->height);
		Block *rightNewBlockLeftBot = this->searchPointInBlock(xCoordinate+width, currentBlock->lowerLeftCornerCoordinate.second-1);
		if(xCoordinate > currentBlock->lowerLeftCornerCoordinate.first){
			createLeft = true;
			Block *newLeftBlock = new Block(currentBlock->lowerLeftCornerCoordinate, currentBlock->leftBot, 
			currentBlock->botLeft, leftLastBlock, newBlock, currentBlock->height,
			xCoordinate-currentBlock->lowerLeftCornerCoordinate.first, false, -1);
			if (leftLastBlock == nullptr){
				leftLastBlock = newLeftBlock;
			}else if(newLeftBlock->width == leftLastBlock->width && !leftLastBlock->isSolid &&
				 newLeftBlock->lowerLeftCornerCoordinate.first == leftLastBlock->lowerLeftCornerCoordinate.first){
				leftLastBlock->height += newLeftBlock->height;
				leftLastBlock->leftBot = newLeftBlock->leftBot;
				leftLastBlock->botLeft = newLeftBlock->botLeft;
				leftLastBlock->lowerLeftCornerCoordinate = newLeftBlock->lowerLeftCornerCoordinate;
				delete newLeftBlock;
			}else{
				if(leftLastBlock->lowerLeftCornerCoordinate.first >= newLeftBlock->lowerLeftCornerCoordinate.first){
					leftLastBlock->leftBot = newLeftBlock;
				}
				leftLastBlock = newLeftBlock;
			}
			
			//add leftNeighbors point to leftlast
			for(Block *i : leftNeighbors){
				if(i->topRight == currentBlock && i != leftLastBlock){
					i->topRight = leftLastBlock;
				}
				
			}
			//add topNeighbors to leftlast
			for(Block *i : topNeighbors){	
				if(i->lowerLeftCornerCoordinate.first < xCoordinate 
					&& i->lowerLeftCornerCoordinate.first >= leftLastBlock->lowerLeftCornerCoordinate.first && i != leftLastBlock){
					i->leftBot = leftLastBlock;
					//					
				}
			}

			//add botNeighbors to leftlast
			for(Block *i : botNeighbors){
				if(i->lowerLeftCornerCoordinate.first+i->width > leftLastBlock->lowerLeftCornerCoordinate.first 
					&& i->lowerLeftCornerCoordinate.first+i->width <= xCoordinate){
					i->rightTop = leftLastBlock;	
				}
			}
		}
		
		//newBlock->botLeft = leftLastBlock;
		//leftLastBlock->PrintContent();
		// currentBlock->PrintContent();
		// leftLastBlock->PrintContent();
		
		if(xCoordinate+width < currentBlock->lowerLeftCornerCoordinate.first+currentBlock->width){
			createRight = true;
			Block *newRightBlock = new Block(std::pair<int, int>(xCoordinate+width, 
				currentBlock->lowerLeftCornerCoordinate.second), nullptr, newBlock, currentBlock->rightTop, 
				currentBlock->topRight, currentBlock->height,
				currentBlock->lowerLeftCornerCoordinate.first+currentBlock->width-(xCoordinate+width), false, -1);
				newRightBlock->leftBot=rightNewBlockLeftBot;
			if(rightLastBlock == nullptr){
				rightLastBlock = newRightBlock;
			}else if(newRightBlock->width == rightLastBlock->width && !rightLastBlock->isSolid && 
				newRightBlock->lowerLeftCornerCoordinate.first == rightLastBlock->lowerLeftCornerCoordinate.first){
				rightLastBlock->height += newRightBlock->height;
				rightLastBlock->leftBot = newRightBlock->leftBot;
				rightLastBlock->botLeft = newRightBlock->botLeft;
				rightLastBlock->lowerLeftCornerCoordinate = newRightBlock->lowerLeftCornerCoordinate;
				delete newRightBlock;
			}else{
				if(rightLastBlock->lowerLeftCornerCoordinate.first== newRightBlock->lowerLeftCornerCoordinate.first){
				 	rightLastBlock->leftBot = newRightBlock;
				}
				rightLastBlock = newRightBlock;
			}

			if(newBlock->topRight == nullptr){
				newBlock->topRight = rightLastBlock;
			}

			//add rightNeighbors to rightLast
			for(Block *i : rightNeighbors){
				if(i->botLeft == currentBlock){
					i->botLeft = rightLastBlock;
				}
			}

			//add topNeighbors to rightlast
			for(Block *i : topNeighbors){
				if(i->lowerLeftCornerCoordinate.first < rightLastBlock->lowerLeftCornerCoordinate.first+rightLastBlock->width
					&& i->lowerLeftCornerCoordinate.first >= rightLastBlock->lowerLeftCornerCoordinate.first && i != rightLastBlock){
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

		}
		
		
		for(Block *i:topNeighbors){
			if(i->lowerLeftCornerCoordinate.first>=xCoordinate && i->lowerLeftCornerCoordinate.first < xCoordinate+width && i!=newBlock){
				i->leftBot = newBlock;
			}
		}
		for(Block *i:botNeighbors){
			if(i->lowerLeftCornerCoordinate.first+i->width >xCoordinate && 
				i->lowerLeftCornerCoordinate.first+i->width<=xCoordinate+width){
					i->rightTop=newBlock;
				}
		}
		for(Block *i:leftNeighbors){
			if(i->lowerLeftCornerCoordinate.first+i->width == xCoordinate && i->topRight == currentBlock){
				i->topRight = newBlock;
			}
		}
		for(Block*i:rightNeighbors){
			if(i->lowerLeftCornerCoordinate.first == xCoordinate+width && i->botLeft == currentBlock){
				i->botLeft = newBlock;
			}
		}
		
		newBlock->lowerLeftCornerCoordinate.first = xCoordinate;
		newBlock->lowerLeftCornerCoordinate.second = currentBlock->lowerLeftCornerCoordinate.second;
		newBlock->width = width;
		newBlock->height += currentBlock->height;
		if(createLeft){
			newBlock->botLeft = leftLastBlock;
		}else{
			newBlock->botLeft = currentBlock->botLeft;
		}
		newBlock->leftBot = nextBlock;
		Block *tempBlock = currentBlock;
		
		currentBlock = nextBlock;
		if(tempBlock == this->headBlock){
			this->headBlock = newBlock;
		}
		if(tempBlock->lowerLeftCornerCoordinate.second == yCoordinate){
			
			Block* curLeftNeightbor = this->searchPointInBlock(xCoordinate-1, tempBlock->lowerLeftCornerCoordinate.second-1);
			if(curLeftNeightbor!=nullptr && leftLastBlock !=nullptr && createLeft){	
				if(curLeftNeightbor->width == leftLastBlock->width && !leftLastBlock->isSolid && !curLeftNeightbor->isSolid &&
					leftLastBlock->lowerLeftCornerCoordinate.first == curLeftNeightbor->lowerLeftCornerCoordinate.first && curLeftNeightbor != leftLastBlock){
					std::vector<Block*> curLeftNeightborLeftNeightbors = this->searchLeftNeighbors(curLeftNeightbor);
					std::vector<Block*> curLeftNeightborBotNeightbors = this->searchBotNeighbors(curLeftNeightbor);
					std::vector<Block*> curLeftNeightborRightNeightbors = this->searchRightNeighbors(curLeftNeightbor);
					leftLastBlock->height += curLeftNeightbor->height;
					leftLastBlock->leftBot = curLeftNeightbor->leftBot;
					leftLastBlock->botLeft = curLeftNeightbor->botLeft;
					leftLastBlock->lowerLeftCornerCoordinate = curLeftNeightbor->lowerLeftCornerCoordinate;
					
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
				}else if(createLeft){
					leftLastBlock->leftBot = this->searchPointInBlock(leftLastBlock->lowerLeftCornerCoordinate.first, leftLastBlock->lowerLeftCornerCoordinate.second-1);
				}
			}
			

			Block *right = this->searchPointInBlock(xCoordinate+width, tempBlock->lowerLeftCornerCoordinate.second-1);
			if(right != nullptr && rightLastBlock != nullptr){	
				if(right->width == rightLastBlock->width && !right->isSolid && !rightLastBlock->isSolid && 
					right->lowerLeftCornerCoordinate.first == rightLastBlock->lowerLeftCornerCoordinate.first && right != rightLastBlock && createRight){

					std::vector<Block*> curLeftNeightborRightNeightbors = this->searchRightNeighbors(right);
					std::vector<Block*> curLeftNeightborBotNeightbors = this->searchBotNeighbors(right);
					std::vector<Block*> curLeftNeightborLeftNeightbors = this->searchLeftNeighbors(right);
					rightLastBlock->height += right->height;
					rightLastBlock->leftBot = right->leftBot;
					rightLastBlock->botLeft = right->botLeft;
					rightLastBlock->lowerLeftCornerCoordinate = right->lowerLeftCornerCoordinate;
					
					for(auto i: curLeftNeightborRightNeightbors){
						if(i->botLeft == right){
							i->botLeft = rightLastBlock;
						}
					}
					for(auto i: curLeftNeightborBotNeightbors){
						if(i->rightTop == right){
							i->rightTop = rightLastBlock;
						}
					}
					for(auto i: curLeftNeightborLeftNeightbors){
						if(i->topRight == right){
							i->topRight = rightLastBlock;
						}
					}
					
					delete right;
				
				}else if(rightLastBlock != right && createRight){
					rightLastBlock->leftBot = right;
				}
				
			}
			break;
		}
		delete tempBlock;
	}


	return newBlock;
}

Block* Box::splitBlock(int yCoordinate, Block *targetBlock){
	if(targetBlock == nullptr){
		return nullptr;
	}
	if(yCoordinate == targetBlock->lowerLeftCornerCoordinate.second){
		return nullptr;
	}
	Block *newBlock = new Block(targetBlock->lowerLeftCornerCoordinate, targetBlock->leftBot, 
		targetBlock->botLeft, targetBlock, nullptr,
		yCoordinate-targetBlock->lowerLeftCornerCoordinate.second, targetBlock->width, targetBlock->isSolid, -1);

	std::vector<Block *> targetBlockRightNeighbors = this->searchRightNeighbors(targetBlock);
	std::vector<Block *> targetBlockBotNeighbors = this->searchBotNeighbors(targetBlock);
	std::vector<Block *> targetBlockLeftNeighbors = this->searchLeftNeighbors(targetBlock);

	


	for(Block *i : targetBlockRightNeighbors){
		if(i->botLeft == targetBlock && i->lowerLeftCornerCoordinate.second >= yCoordinate){
			i->botLeft = targetBlock;
		}else if(i->botLeft == targetBlock && i->lowerLeftCornerCoordinate.second >= targetBlock->lowerLeftCornerCoordinate.second){
			i->botLeft = newBlock;
		}
		if(newBlock->topRight == nullptr && i->lowerLeftCornerCoordinate.second+i->height >= yCoordinate){
			newBlock->topRight = i;
		}
	}
	
	
	for(Block *i: targetBlockBotNeighbors){
		if(i->rightTop == targetBlock){
			i->rightTop = newBlock;
		}
	}

	
	targetBlock->botLeft = nullptr;
	for(Block *i : targetBlockLeftNeighbors){
		if(i->topRight == targetBlock && i->lowerLeftCornerCoordinate.second+i->height > yCoordinate){
			i->topRight = targetBlock;
		}else if(i->topRight == targetBlock && i->lowerLeftCornerCoordinate.second+i->height <= yCoordinate) {
			i->topRight = newBlock;
		}
		if(targetBlock->botLeft == nullptr && i->lowerLeftCornerCoordinate.second+i->height > yCoordinate){
			targetBlock->botLeft = i;
		}
	}

	

	targetBlock->height -= (yCoordinate - targetBlock->lowerLeftCornerCoordinate.second);
	targetBlock->lowerLeftCornerCoordinate.second = yCoordinate;
	targetBlock->leftBot = newBlock;
	return newBlock;
	
}

