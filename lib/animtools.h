#ifndef ANIMTOOLS_H
#define ANIMTOOLS_H

#include <ostream>
#include <iostream>
#include <iomanip>
#include <math.h>

#define animparm int value
#define block(num) if(value <= 255+(num*255))
#define frac(blocknum) (((float)value-((blocknum)*255))/255)

class color24
{

friend std::ostream& operator<<(std::ostream& str, const color24& col);

public:
	color24()
	{
		r = 0;
		g = 0;
		b = 0;
	}
	/*
	Hexval in format 0x00RRGGBB.
	Highest byte is always ignored.
	*/
	color24(uint32_t hexval);
	void set(uint32_t* hexval);
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

color24 lerpColorLinear(float f, color24 color1, color24 color2);
color24 lerpColorSine(float f, color24 color1, color24 color2);

//transition type descriptor
typedef enum transitionType
{

	NONE = 1,
	LINEAR,
	SINE

} transitionType;

//color channel descriptor
typedef enum colorChannel
{

	RED,
	GREEN,
	BLUE
	
} colorChannel;

//24 bit color value node
typedef struct animationNode
{

	//hex value of color interpretation
	color24 color;
	//transition length
	int length;
	//transition type to the next
	transitionType transition;
	//a pointer to a next color point
	animationNode* next;
	
} animationNode;

class animationDescriptor
{

public:
	animationDescriptor();
	~animationDescriptor();
	void addNode(animationNode);
	bool editNode(int, animationNode);
	void printNodes();
	void setName(std::string);
	std::string getName();
	void printName();
	int getAnimationLength();
	void buildAnimation();
	void outputBaked(std::ostream&, colorChannel);
	
private:
	std::string animationName;
	animationNode* animationHead;
	animationNode* createNode(animationNode);
	void clearBakedCache();
	uint8_t* bakedCache_r;
	uint8_t* bakedCache_g;
	uint8_t* bakedCache_b;
	int bakedCache_size;
	
};

#endif
