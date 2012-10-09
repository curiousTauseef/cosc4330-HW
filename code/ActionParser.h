/*
 * ActionParser.h
 *
 *  Created on: Oct 5, 2012
 *      Author: xmuweili
 */

#ifndef ACTIONPARSER_H_
#define ACTIONPARSER_H_
#include<iostream>
#include<fstream>
#include<assert.h>
using namespace std;

bool actionParser(char * filename){
	std::ifstream file(filename);
	std::string line;

	int room_num = 0;
	int custom_num = 0;

	//start parsing the file
	std::getline(file, line);
	assert(line.size()>0);

	//get the room number
	if (sscanf(line.c_str(), "%d", &room_num) == 1)
		std::cout<<"Total room number is "<<room_num<<"\n";
	else{
		std::cout<<"error in reading room number";
		exit(0);
	}

	//get the custom number
	std::getline(file, line);
	assert(line.size()>0);
	if(sscanf(line.c_str(), "%d", &custom_num) ==1)
		std::cout<<"Total custom number is "<<custom_num<<"\n";
	else
	{
		std::cout<<"error in reading custom number";
		exit(0);
	}

	//parse all actions
	while(1){



	};
	return false;
}

#endif /* ACTIONPARSER_H_ */
