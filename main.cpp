#include <iostream>
#include "./src/parser.cpp"
using namespace std;

int main(){
	cout << "Hello World" << endl;
	Parser parser;
	parser.set("./testcase/case0.txt");
	cout << parser.height << endl;
}