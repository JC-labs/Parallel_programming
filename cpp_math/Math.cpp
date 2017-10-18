#include "Math.hpp"
#include "Matrix.hpp"
#include <string>
#include <iostream>

void pp::additional::write(char* text) {
	std::cout << text;
}
void pp::additional::write(double n) {
	std::cout << n << ' ';
}
int pp::read_integer() {
	int ret;
	std::cin >> ret;
	return ret;
}
double pp::read_double() {
	double ret;
	std::cin >> ret;
	return ret;
}