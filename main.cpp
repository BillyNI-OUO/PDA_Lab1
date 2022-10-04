#include <iostream>
#include <fstream>
#include <stdio.h>
#include "./src/parser.cpp"
#include "./src/box.cpp"
#include "./src/block.cpp"
using namespace std;

int main(int argc, char **argv){
	char *filename = (char*)"./testcase/case0.txt"; //default testcase
	if (argc == 2){
		filename = argv[1];
	}
	std::vector<vector<int>> answers;
	Box box;
	Parser parser(filename);
	parser.Set(&box);
	parser.PrintContent();

	vector<std::pair<int, int>> ansStack;
	// for(int i = 0; i < parser.operation.size(); i ++){
	// 	if(parser.operation[i].first == 'P'){
	// 		std::pair<int, int> tempAns;
	// 		Block *searchResult = box.searchPointInBlock(parser.operation[i].second[0], parser.operation[i].second[1]);
	// 		if(searchResult == NULL){
	// 			continue;
	// 		}
	// 		tempAns.first = searchResult->lowerLeftCornerCoordinate.first;
	// 		tempAns.second = searchResult->lowerLeftCornerCoordinate.second;
	// 		ansStack.push_back(tempAns);
	// 	}else if(parser.operation[i].first == 'N'){
	// 		std::vector<int> v = parser.operation[i].second;
	// 		box.createBlock(v[1], v[2], v[3], v[4], v[0]);
	// 	}
	// }
	Block* temp = box.createBlock(35, 35, 30, 30, 1);
	
	temp = box.createBlock(35, 65, 60, 20, 2);
	//temp->leftBot->botLeft->PrintContent();



	temp = box.createBlock(65, 5, 20, 60, 3);
	//temp = box.createBlock(5, 15, 60, 20, 4);
	//temp = box.createBlock(15, 35, 20, 60, 5);
	//temp->topRight->leftBot->botLeft->PrintContent();
	int cnt = 0;
	//temp->PrintContent();
	//temp->botLeft->rightTop->botLeft->leftBot->PrintContent();
	vector<Block*> res;
	res = box.searchBlocks(0, 0, 100, 100);
	//res.push_back(temp);
	//temp->botLeft->PrintContent();
	//res = box.searchLeftNeighbors(temp);
	// for(Block *i : res){
	// 	i->PrintContent();
	// }
	//cout << box.searchIsSolidBlock(0,0,100,100) << endl;

	FILE *fptr;
	fptr = fopen("out.txt","w");
	if(fptr == NULL)
	{
		printf("Error!");   
		exit(1);             
	}
	fprintf(fptr, "%d\n", res.size());
	fprintf(fptr, "%d %d\n", box.width, box.height);
	for(Block *i:res){
		fprintf(fptr, "%d %d %d %d %d\n", i->index, i->lowerLeftCornerCoordinate.first,
		 i->lowerLeftCornerCoordinate.second, i->width, i->height);
	}

	fclose(fptr);
}
