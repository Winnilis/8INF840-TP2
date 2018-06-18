#pragma once
#include <iostream>

//Classe to store the RGB color of a pixel
class CustomRGBColor
{
public:
	CustomRGBColor();
	CustomRGBColor(double red, double green, double blue);
	~CustomRGBColor();
	double getRed() const{ return red; };
	double getGreen() const{ return green; };
	double getBlue() const{ return blue; };
	bool operator==(CustomRGBColor const&) const;
	friend std::ostream & operator<<(std::ostream & out, const CustomRGBColor & pixel);

private:
	double red;
	double green;
	double blue;
};

