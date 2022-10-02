#include <iostream>
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
	cout << box.height << " " << box.width << endl;
	parser.PrintContent();
	Block *ans;
	box.splitBlock(50, box.headBlock);
	vector<Block*> res = box.searchBotNeighbors(box.headBlock);
	ans = box.createBlock(35,35, 60, 20);
	res = box.searchNeighbors(ans);
	box.headBlock->PrintContent();
	for(Block *i: res){
		i->PrintContent();
	}
	
	//cout << box.searchIsSolidBlock(0,0,100,100) << endl;

}