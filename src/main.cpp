#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "datapoint.hpp"
#include "color.hpp"

void command(std::string, bool*);
void clear();

int main() {
	bool loopctl = true;
	clear();
	while(loopctl) {
		std::string cmd;
		cmd.clear();
		std::cout << "> ";
		std::getline(std::cin, cmd);
		command(cmd, &loopctl);
	}
}

void clear() {
	system("clear");
	std::cout 
	<< "[*] LookupBaker V1.1 [*]\n"
	<< "  (C) A.S. Miller 2022\n";
	std::cout << "Type 'help' or '?' for a list of commands.\n";
}

void command(std::string cmd, bool* ctl) {
	char* com, par;
	if(cmd == "help" || cmd == "?") {
		std::cout << "Command reference: \n"
		<< "1. help - displays this list\n"
		<< "2. exit - ends the program\n"
		<< "3. clear - clears the command line\n"
		<< "4. setup - starts settings wizard\n";
		return;
	}
	else if(cmd == "exit") {
		*ctl = false;
	}
	else if(cmd == "clear") {
		clear();
	}
	else {
		std::cout << "Invalid command. "
		<< "Type 'help' or '?' for a list of commands.\n";
	}
}

//void fileWriter(animationDescriptor& animref) {
//	system("clear");
//	std::cout << "Precalculating output...\n\n";
//	//output file stream
//	std::ofstream output;
//	output.open(animref.getName() + ".cpp.txt");
//	//gather animation length data
//	int length = animref.getAnimationLength();
//	//red channel values
//	output << "const uint8_t " << animref.getName()+"_r" << "[" << length << "] PROGMEM = {\n";
//	animref.outputBaked(output, RED);
//	output << "\n};\n\n";
//	//green channel values
//	output << "const uint8_t " << animref.getName()+"_g" << "[" << length << "] PROGMEM = {\n";
//	animref.outputBaked(output, GREEN);
//	output << "\n};\n\n";
//	//blue channel values
//	output << "const uint8_t " << animref.getName()+"_b" << "[" << length << "] PROGMEM = {\n";
//	animref.outputBaked(output, BLUE);
//	output << "\n};\n\n";
//	output.close();
//	std::cout << "Lookup tables saved into " << animref.getName() + ".cpp.txt" << "!\n";
//}
