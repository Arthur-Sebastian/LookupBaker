#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "lib/animtools.h"

void programHeader();
void fileWriter(animationDescriptor&);
void getSettings(animationDescriptor&);
void buildNode(animationDescriptor&);

int main()
{
	//instantiate an animation object
	animationDescriptor mainanim;
	//displays a program title
	programHeader();
	//grabs basic information
	getSettings(mainanim);
	//run the program in loop until exit
	while(1)
	{
		std::cout << "Do you wish to add a color node? (y/n)\n";
		uint8_t input;
		std::cin >> input;
		if(input == 'y')
		buildNode(mainanim);
		else if(input == 'n')
		break;
		else
		std::cout << "Answer with 'y' or 'n'.\n";
	}
	//bake
	mainanim.buildAnimation();
	//write the file
	fileWriter(mainanim);
	return 0;
}

void programHeader()
{
	//displays a big table with title and copyright
	std::cout << "|----------------[ LookupBaker ]----------------|\n";
	std::cout << "|--- RGB animation lookup table creator tool ---|\n";
	std::cout << "|------ for 8bit machine target platforms ------|\n";
	std::cout << "|------[ (C) Artur Sebastian Miller 2021 ]------|\n\n";
}

void getSettings(animationDescriptor& animref)
{
	std::string tempname;
	std::cout << "Input a name for the animation:\n";
	std::cin >> tempname;
	animref.setName(tempname);
}

void buildNode(animationDescriptor& animref)
{
	uint32_t color;
	uint16_t transition;
	uint16_t length;
	animationNode prototype;
	//gather input
	std::cout << "Input a hex color (FFFFFF):\n";
	std::cin >> std::hex >> color;
	std::cout << "Input transition length in steps:\n";
	std::cin >> std::dec >> length;
	std::cout << "Select transition type (1 - NONE, 2 - LINEAR, 3 - SINE):\n";
	std::cin >> transition;
	//assign values
	prototype.color = color24(color);
	prototype.transition = (transitionType) transition;
	prototype.length = length;
	animref.addNode(prototype);
	system("clear");
	std::cout << "Current file:\n";
	animref.printNodes();
}

void fileWriter(animationDescriptor& animref)
{
	system("clear");
	std::cout << "Baking animation...\n\n";
	//output file stream
	std::ofstream output;
	output.open(animref.getName()+".cpp.txt");
	//gather animation length data
	int length = animref.getAnimationLength();
	//red channel values
	output << "const uint8_t " << animref.getName()+"_r" << "[" << length << "] PROGMEM =\n{\n";
	animref.outputBaked(output, RED);
	output << "\n};\n\n";
	//green channel values
	output << "const uint8_t " << animref.getName()+"_g" << "[" << length << "] PROGMEM =\n{\n";
	animref.outputBaked(output, GREEN);
	output << "\n};\n\n";
	//blue channel values
	output << "const uint8_t " << animref.getName()+"_b" << "[" << length << "] PROGMEM =\n{\n";
	animref.outputBaked(output, BLUE);
	output << "\n};\n\n";
	output.close();
	std::cout << "Lookup tables and definitions saved into " << animref.getName()+".cpp.txt" << "!\n";
}
