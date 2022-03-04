#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "datapoint.hpp"
#include "color.hpp"


int main() {
	ColorRGB<uint8_t> red(0xFF, 0, 0);
	ColorRGB<uint8_t> blue(0, 0, 0xFF);
	DataPoint<ColorRGB<uint8_t>> point(red);
	DataPoint<ColorRGB<uint8_t>> point2(blue);
	point.interpolate(point2, 0.5f).print();
	point.interpolate(point2, 0.0f).print();
	point.interpolate(point2, 1.0f).print();
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
