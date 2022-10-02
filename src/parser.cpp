#include <iostream>
#include <fstream>
#include <sstream>
#include "parser.h"
using namespace std;

typedef pair<int,int> Coordinate;
typedef pair<char, std::vector<int>> Instruction;

Parser::Parser(char *filename){
	ifstream inputFile(filename);
	if (inputFile.is_open()){
		this->filename = filename;
		inputFile.close();
	}else{
		throw std::invalid_argument( "invalid testcase filenmae" );
	}

}

void Parser::Set(Box *box){
	ifstream inputFile(this->filename);
	string line;
    stringstream ss;
    string tok;
  	if (inputFile.is_open()){
  		int width, height;
  		getline (inputFile,line);
  		ss.str(line);
  		getline(ss, tok, ' ');
  		std::istringstream(tok) >> width;
  		std::istringstream(tok) >> height;
  		box->setWidthAndHeight(width, height);
  		box->headBlock = new Block(Coordinate(0, 0), NULL, NULL, NULL, NULL, width, height, false);

	    while ( getline (inputFile,line) ){
	    	ss.str("");
            ss.clear();
	    	ss.str(line);
	    	getline(ss, tok, ' ');
	    	string operators;
	    	istringstream(tok) >> operators;
	    	if (operators == "P"){
	    		int pX, pY;
	    		getline(ss, tok, ' ');
	    		std::istringstream(tok) >> pX;
	    		getline(ss, tok, ' ');
  				std::istringstream(tok) >> pY;
  				vector<int> *operands = new vector<int>;
  				operands->push_back(pX);
  				operands->push_back(pY);
  				operation.push_back(Instruction('P', *operands));
	    	}else{
	    		vector<int> *operands = new vector<int>;
	    		for(int i = 0; i < 4; i ++){
	    			int temp;
	    			getline(ss, tok, ' ');
	    			std::istringstream(tok) >> temp;
	    			operands->push_back(temp);
	    		}
  				operation.push_back(Instruction('N', *operands));
	    	}
	    }
    inputFile.close();
  }
} 
