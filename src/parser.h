#ifndef PARSER_H
#define PARSER_H 

#include "box.h"
#include <vector>
class Parser{
	public:
		int height;
		int lengh;
		char *filename;
		std::vector<std::pair<char, std::vector<int>>> operation;
	Parser(char *filename);
	void Set(Box *box);
	void PrintContent(){
		for (int i = 0; i < operation.size(); i++) {
        std::cout << operation[i].first << " ";
        for (int j = 0; j < operation[i].second.size(); j ++){
        	std::cout << operation[i].second[j] << " ";
        }
        std::cout << std::endl;
    }
	}
};

#endif