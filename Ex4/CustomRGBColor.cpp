#include "CustomRGBColor.h"

CustomRGBColor::CustomRGBColor()
{
}

CustomRGBColor::CustomRGBColor(double r, double g, double b)
{
	red = r;
	green = g;
	blue = b;
}

CustomRGBColor::~CustomRGBColor()
{
}

bool CustomRGBColor::operator==(CustomRGBColor const & other) const
{
	//two pixels are equal is based on their color
	if (red == other.getRed() && green == other.getGreen() && blue == other.getBlue())
	{
		return true;
	}
	return false;
}

std::ostream & operator<<(std::ostream & out, const CustomRGBColor & pixel)
{
	out << pixel.getRed() << "/" << pixel.getGreen() << "/" << pixel.getBlue();
	return out;
}
