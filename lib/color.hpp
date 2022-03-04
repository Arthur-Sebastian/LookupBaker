#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <ostream>
#include <iostream>

template <typename Type>
class ColorRGB {

public:
	ColorRGB();
	ColorRGB(Type, Type, Type);

	ColorRGB operator-(const ColorRGB&) const;
	ColorRGB operator+(const ColorRGB&) const;
	ColorRGB operator*(float) const;
	
	void print();
	
	Type r;
	Type g;
	Type b;

};

template <typename Type>
ColorRGB<Type>::ColorRGB() {	
}

template <typename Type>
ColorRGB<Type>::ColorRGB(Type ir, Type ig, Type ib) {
	r = ir;
	g = ig;
	b = ib;
}

template <typename Type>
void ColorRGB<Type>::print() {
	std::cout << "\nR: " << (int) r;
	std::cout << "\nG: " << (int) g;
	std::cout << "\nB: " << (int) b;
}

template <typename Type>
ColorRGB<Type> ColorRGB<Type>::operator-(const ColorRGB& sub) const {
	return ColorRGB<Type>(r-sub.r, g-sub.g, b-sub.b);
}

template <typename Type>
ColorRGB<Type> ColorRGB<Type>::operator+(const ColorRGB& sub) const {
	return ColorRGB<Type>(r+sub.r, g+sub.g, b+sub.b);
}

template <typename Type>
ColorRGB<Type> ColorRGB<Type>::operator*(float mul) const {
	return ColorRGB<Type>(r*mul, g*mul, b*mul);
}

#endif
