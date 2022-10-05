#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "./src/parser.cpp"
#include "./src/box.cpp"
#include "./src/block.cpp"
using namespace std;

typedef struct ANS
{
	int index;
	int solid;
	int space;
};

bool ansCompare(ANS a, ANS b){
	return a.index < b.index;
}

int main(int argc, char **argv){
	char *filename = (char*)"./testcase/case1.txt"; //default testcase
	char *ouputFilename = (char*)"output.txt";
	if (argc >= 2){
		filename = argv[1];
	}
	if(argc >= 3){
		ouputFilename = argv[2];
	}
	std::vector<vector<int>> answers;
	Box box;
	Parser parser(filename);
	parser.Set(&box);
	box.headBlock->PrintContent();
	parser.PrintContent();

	vector<std::pair<int, int>> ansStack;
	vector<Block*> Blockstack;
	vector<ANS> ansVector;

	for(int i = 0; i < parser.operation.size(); i ++){
		if(parser.operation[i].first == 'P'){
			std::pair<int, int> tempAns;
			Block *searchResult = box.searchPointInBlock(parser.operation[i].second[0], parser.operation[i].second[1]);
			if(searchResult == nullptr){
				continue;
			}
			tempAns.first = searchResult->lowerLeftCornerCoordinate.first;
			tempAns.second = searchResult->lowerLeftCornerCoordinate.second;
			ansStack.push_back(tempAns);
		}else if(parser.operation[i].first == 'N'){
			if(i > 7)break;
			std::vector<int> v = parser.operation[i].second;
			Block *tempBlock = box.createBlock(v[1], v[2], v[3], v[4], v[0]);
			printf("%d\n", tempBlock->index);
			Blockstack.push_back(tempBlock);
		}
	}

	for(auto i: Blockstack){
		int solidcnt = 0;
		int spacecnt = 0;
		vector<Block*> tempStack = box.searchNeighbors(i);
		for(auto j: tempStack){
			if(j->isSolid){
				solidcnt++;
			}else{
				spacecnt++;
			}
		}
		ANS ans;
		ans.index = i->index;
		ans.solid = solidcnt;
		ans.space = spacecnt;
		ansVector.push_back(ans);
	}
	std::sort(ansVector.begin(), ansVector.end(), ansCompare);

	vector<Block*> res;
	res = box.searchBlocks(0, 0, 100, 150);

	FILE *foptr;
	foptr = fopen(ouputFilename,"w");

	fprintf(foptr,"%d\n", res.size());

	for(auto i: ansVector){
		fprintf(foptr,"%d %d %d\n", i.index, i.solid, i.space);
	}
	for(auto i:ansStack){
		fprintf(foptr,"%d %d\n", i.first, i.second);
	}
	fclose(foptr);
	// Block* temp = box.createBlock(35, 35, 30, 30, 1);
	
	// temp = box.createBlock(35, 65, 60, 20, 2);
	


	res = box.searchBlocks(0, 0, 100, 150);
	// temp = box.createBlock(65, 5, 20, 60, 3);
	// box.createBlock(5, 15, 60, 20, 4);
	// box.createBlock(15, 35, 20, 60, 5);
	//temp->topRight->leftBot->botLeft->PrintContent();
	//temp->PrintContent();
	//temp->botLeft->leftBot->PrintContent();
	
	//res = box.searchBlocks(0, 0, 100, 100);
	Block *temp = box.searchPointInBlock(0, 64);
	//res.push_back(temp->topRight->leftBot);
	//temp->botLeft->PrintContent();
	//Block* temp = box.searchPointInBlock(0, 121);
	res = box.searchNeighbors(temp->topRight);
	//Blockstack[4]->topRight->PrintContent();
	//temp->botLeft->PrintContent();
	// for(Block *i : res){
	// 	i->PrintContent();
	// }
	//cout << box.searchIsSolidBlock(0,0,100,100) << endl;

	FILE *fptr;
	fptr = fopen("out.txt","w");
	if(fptr == nullptr)
	{
		printf("Error!");   
		exit(1);             
	}
	fprintf(fptr, "%d\n", res.size());
	fprintf(fptr, "%d %d\n", box.width, box.height);
	for(auto *i:res){
		fprintf(fptr, "%d %d %d %d %d\n", i->index, i->lowerLeftCornerCoordinate.first,
		 i->lowerLeftCornerCoordinate.second, i->width, i->height);
	}
	fclose(fptr);
	exit(0);  
}
