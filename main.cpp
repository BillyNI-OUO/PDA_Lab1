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
	cout << "Hello World" << endl;
	Box box;
	Parser parser(filename);
	parser.Set(&box);
	cout << box.height << " " << box.width << endl;
	parser.PrintContent();
}