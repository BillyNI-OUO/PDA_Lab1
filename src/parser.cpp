#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Parser{
	public:
		int height;
		int lengh;
	void set(char* filename);
};

void Parser::set(char* filename){
	ifstream data(filename);
	string line;
    stringstream ss;
  	if (data.is_open()){
    while ( getline (data,line) ){
    	ss.str(line);
    	string tok;
    	getline(ss, tok, ' ');
    	std::istringstream(tok) >> height;
    	getline(ss, tok, ' ');
    	std::istringstream(tok) >> lengh;
    	break;
    }
    data.close();
  }
} 
