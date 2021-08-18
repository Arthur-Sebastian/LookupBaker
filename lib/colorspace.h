#include <ostream>
#include <iomanip>

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

//color channel descriptor
typedef enum colorChannel
{

	RED,
	GREEN,
	BLUE
	
} colorChannel;
