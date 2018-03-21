#include "Types.hpp"
void fill(vector &v, number value) {
	for (auto &it : v)
		it = value;
}
void fill(matrix &m, number value) {
	for (auto &v : m)
		for (auto &it : v)
			it = value;
}
void get(vector &v, std::istream &s) {
	for (auto &it : v)
		s >> it;
}
void get(matrix &m, std::istream &s) {
	for (auto &v : m)
		for (auto &it : v)
			s >> it;
}
void resize(vector &v, size_t n) { v.resize(n); }
void resize(matrix &m, size_t n) {
	m.resize(n);
	for (auto &it : m)
		it.resize(n);
}
void write(matrix const& m, std::ostream &s) {
	s << "Output of a matrix (" << m.size() << "x" << m.size() << "):\n";
	for (auto v : m) {
		for (auto it : v)
			s << it << ' ';
		s << '\n';
	}
}