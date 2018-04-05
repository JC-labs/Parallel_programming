#pragma once
#include <fstream>
#include "Types.hpp"
#include <string>

template <typename T, typename = std::enable_if<std::is_same<T, vector>::value || std::is_same<T, matrix>::value
	|| std::is_same<T, int>::value || std::is_same<T, number>::value>>
void read(std::istream &s, T &t) {
	if constexpr (std::is_same<T, int>::value || std::is_same<T, number>::value)
		s >> t;
	else {
		std::string temp;
		number value;
		s >> temp >> value;
		if (temp == "fill") fill(t, value);
		else if (temp == "get") get(t, s);
	}
}
template <typename T, typename...Ts>
void read(std::istream &s, T &t, Ts&...ts) {
	read(s, t);
	if constexpr(sizeof...(ts)) read(s, ts...);
}
template <typename T, typename...Ts>
void read(std::string &&filename, T &t, Ts&...ts) {
	std::ifstream f;
	f.open(filename);
	return read(f, t, ts...);
}
void write(std::string &&filename, matrix const& m) {
	std::ofstream f;
	f.open(filename);
	return write(m, f);
}
void write(std::string &&filename, vector const& v) {
	std::ofstream f;
	f.open(filename);
	return write(v, f);
}