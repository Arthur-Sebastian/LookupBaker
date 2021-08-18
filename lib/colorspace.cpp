#include "colorspace.h"

/*

[COLOR CLASS IMPLEMENTATION]

*/

std::ostream& operator<<(std::ostream& str, const color24& col)
{
	//copy formatting
	std::ios init(NULL);
	init.copyfmt(str);
	//output
	str << "#"; 
	str << std::uppercase << std::hex << std::setfill('0') << std::setw(6);
	uint32_t tmp = (col.r << 16) | (col.g << 8) | col.b;
	str << tmp;
	//restore formatting
	str.copyfmt(init);
	return str;
}

color24::color24(uint32_t hexval)
{
	set(&hexval);
}

void color24::set(uint32_t* hexval)
{
	r = (uint8_t)((*hexval & 0x00FF0000) >> 16);
	g = (uint8_t)((*hexval & 0x0000FF00) >> 8);
	b = (uint8_t)(*hexval & 0x000000FF);
}

/*

[COLORSPACE TRANSITION IMPLEMENTATIONS]

*/

int max(int a, int b, int c)
{
	int temp;
	a > b ? temp = a : temp = b;
	if(temp < c) return c;
	else return temp;
}

int min(int a, int b, int c)
{
	int temp;
	a > b ? temp = b : temp = a;
	if(temp < c) return temp;
	else return c;
}

color24 RGBtoHSV(color24 input)
{
	int v = max(input.r, input.g, input.b);
	int mmdiff = v - min(input.r, input.g, input.b);
	int s = mmdiff/v;
	int htemp;
	if(v == input.r)
		htemp = (input.g - input.b)/mmdiff;
	else if(v == input.g)
		htemp = (input.b - input.r)/mmdiff + 2;
	else if(v == input.b)
		htemp = (input.r - input.g)/mmdiff + 4;
	htemp *= 60;
}
