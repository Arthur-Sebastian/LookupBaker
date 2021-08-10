#include "animtools.h"

/*

[COLOR24 CLASS IMPLEMENTATION]

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

[ANIMATION CLASS IMPLEMENTATION]

*/

animationDescriptor::animationDescriptor()
{
	//assign name, and indicator pointer
	animationName = "New Animation";
	//signifies empty animation
	animationHead = nullptr;
	bakedCache_size = 0;
	bakedCache_r = nullptr;
	bakedCache_g = nullptr;
	bakedCache_b = nullptr;
}

animationDescriptor::~animationDescriptor()
{
	//scroller for the list
	animationNode* current = animationHead;
	//remove the linked list from memory
	while(current != nullptr)
	{
		//preserve the next pointer
		animationNode* savenext = current -> next;
		//delete the current
		delete current;
		//move on to the next in line
		current = savenext;
	}
	//remove prebake buffers
	clearBakedCache();
}

void animationDescriptor::setName(std::string setname)
{
	//assign the name to the provided string
	animationName = setname;
}

std::string animationDescriptor::getName()
{
	return animationName;
}

void animationDescriptor::printName()
{
	//put the animation name into the standard output
	std::cout << "Animation title: '" << animationName << "'\n";
}

void animationDescriptor::addNode(animationNode prototype)
{
	//scroller for the list
	animationNode* current = animationHead;
	//first element of the list
	if(current == nullptr)
	{
		//create the first node and exit method
		animationHead = createNode(prototype);
		return;
	}
	//move through to the end
	while(current -> next != nullptr)
	{
		current = current -> next;
	}
	//append to the end
	current -> next = createNode(prototype);
}

animationNode* animationDescriptor::createNode(animationNode prototype)
{
	//create a temporary pointer to store return
	animationNode* retptr = new animationNode;
	//assign member variables
	*retptr = prototype;
	retptr -> next = nullptr;
	//return the newly created node
	return retptr;
}

bool animationDescriptor::editNode(int nodeindex, animationNode prototype)
{
	//scroller for the list
	animationNode* current = animationHead;
	//index tracker
	int counter = 1;
	//go through every node until we reach the right one
	while(counter < nodeindex)
	{
		//move on to the next one
		if(current -> next != nullptr)
		{
			current = current -> next;
			counter++;
		}
		//cannot move to the next one, exit loop
		else break;
	}
	//if reached node has correct index, edit
	if(counter == nodeindex)
	*current = prototype;
	//otherwise correct node was not reached
	else return false;
	//everything ok
	return true;
}

void animationDescriptor::printNodes()
{
	//scroller for the list
	animationNode* current = animationHead;
	//node number tracker
	int counter = 1;
	//print out the color nodes in order
	while(current != nullptr)
	{
		std::cout << counter << ". ";
		//print out the data
		std::cout << current -> color;
		if(current -> transition == NONE) 
		std::cout << " -> NONE,   ";
		else if(current -> transition == LINEAR)
		std::cout << " -> LINEAR, ";
		else if(current -> transition == SINE)
		std::cout << " -> SINE,   ";
		std::cout << "LENGTH: " << current -> length << std::endl;
		//move on to next
		current = current -> next;
		counter++;
	}
}

int animationDescriptor::getAnimationLength()
{
	int totalsize = 0;
	animationNode* current = animationHead;
	while(current != nullptr)
	{
		//skip the last point length
		if(current -> next != nullptr)
		totalsize += current -> length;
		current = current -> next;
	}
	return totalsize;
}

void animationDescriptor::clearBakedCache()
{
	delete[] bakedCache_r;
	bakedCache_r = nullptr;
	delete[] bakedCache_g;
	bakedCache_g = nullptr;
	delete[] bakedCache_b;
	bakedCache_b = nullptr;
	bakedCache_size = 0;
}

void animationDescriptor::buildAnimation()
{
	animationNode* current = animationHead;
	animationNode* upcoming;
	//exit if no nodes are present
	if(current == nullptr || current -> next == nullptr) 
	{
		std::cout << "There is not enough nodes to bake!\n";
		return;
	}
	//clean out the bake cache
	if(bakedCache_r != nullptr)
	{
		clearBakedCache();
	}
	//create new buffers
	bakedCache_size = getAnimationLength();
	uint8_t* r_buffer = new uint8_t[bakedCache_size];
	uint8_t* g_buffer = new uint8_t[bakedCache_size];
	uint8_t* b_buffer = new uint8_t[bakedCache_size];
	//variable to keep track of current buffer index
	int bufferFillIndex = 0;
	//begin scrolling through transitions
	upcoming = current -> next;
	while(upcoming != nullptr)
	{
		//calculate all values
		for(int i = 0; i < current -> length; i++)
		{
			//interpolation values
			color24 temp;
			float frac;
			frac = (float)i/(current -> length);
			//apply correct transition
			if(current -> transition == LINEAR)
				temp = lerpColorLinear(frac, (current -> color), (upcoming -> color));
			else if(current -> transition == NONE)
				temp = upcoming -> color;
			else if(current -> transition == SINE)
				temp = lerpColorSine(frac, (current -> color), (upcoming -> color));
			//output section
			*(r_buffer+bufferFillIndex) = temp.r;
			*(g_buffer+bufferFillIndex) = temp.g;
			*(b_buffer+bufferFillIndex) = temp.b;
			//move the indexer
			bufferFillIndex++;
		}
		//move on to another
		current = upcoming;
		if(current != nullptr)
		upcoming = current -> next;
	}
	//assign new buffers into the object
	bakedCache_r = r_buffer;
	bakedCache_g = g_buffer;
	bakedCache_b = b_buffer;
}

void animationDescriptor::outputBaked(std::ostream& str, colorChannel channel)
{
	//save output formatting
	std::ios init(NULL);
	init.copyfmt(str);
	if(bakedCache_r == nullptr)
	{
		std::cout << "Baked cache is empty. Bake your animation first!\n";
		return;
	}
	for(int i = 0; i < bakedCache_size; i++)
	{
		//divide into neat column
		if(i) 
		str << ", ";
		else 
		str << "	";
		if(i && !(i%10))
		str << "\n	";
		//display prefix
		str << "0x";
		//setup output stream
		str << std::hex << std::setw(2) << std::setfill('0');
		str << std::uppercase;
		switch(channel)
		{
			case RED:
			str << (int)*(bakedCache_r+i);
			break;
			case GREEN:
			str << (int)*(bakedCache_g+i);
			break;
			case BLUE:
			str << (int)*(bakedCache_b+i);
			break;
		}
	}
	//restore formatting
	str.copyfmt(init);
}

/*

[COLOR TRANSITIONS IMPLEMENTATION]

*/

color24 lerpColorLinear(float f, color24 color1, color24 color2)
{
	color24 output;
	//caluclate color differences between 2 colors
	//even if they are negative
	int rdiff = color2.r - color1.r;
	int gdiff = color2.g - color1.g;
	int bdiff = color2.b - color1.b;
	//transform between color values on percentage 
	output.r = (uint8_t)(color1.r + (rdiff * f));
	output.g = (uint8_t)(color1.g + (gdiff * f));
	output.b = (uint8_t)(color1.b + (bdiff * f));
	return output;
}

color24 lerpColorSine(float f, color24 color1, color24 color2)
{
	color24 output;
	//convert linear transition to sine progression
	float sinetemp = sin(f*1.57);
	float fsine = sinetemp*sinetemp;
	//use new value to transition
	output = lerpColorLinear(fsine, color1, color2);
	return output;
}
