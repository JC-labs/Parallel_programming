#pragma once
#include <vector>
#include <istream>
using number = float;
using vector = std::vector<number>;
class matrix : std::vector<number> {
	size_t x_size, y_size;
public:
	inline vector operator[](size_t const i) { return std::vector<number>(begin() + i * x_size, end() + (i + 1) * x_size); }
	inline vector const operator[](size_t const i) const { return std::vector<number>(begin() + i * x_size, end() + (i + 1) * x_size); }
	inline vector at(size_t const i) { return operator[](i); }
	inline vector const at(size_t const i) const { operator[](i); }
	inline void resize(size_t i, size_t j) { std::vector<number>::resize(i * j); x_size = i; y_size = j; }
	inline void resize(size_t i) { return resize(i, i); }
	inline size_t const size_x() const { return x_size; }
	inline size_t const size_y() const { return y_size; }
	/*back compatibility*/inline size_t const size() const { return x_size; }
	inline number* data() { return &std::vector<number>::at(0); }
	inline number const* data() const { return &std::vector<number>::at(0); }
	using std::vector<number>::begin;
	using std::vector<number>::end;
};

void fill(vector &v, number value);
void fill(matrix &m, number value);
void get(vector &v, std::istream &s);
void get(matrix &m, std::istream &s);
/*back compatibility*/void resize(vector &v, size_t n);
/*back compatibility*/void resize(matrix &m, size_t n);
void write_file(matrix const& m, std::ostream &s);
void write_file(vector const& v, std::ostream &s);
number dot_product(vector const& v1, int i1, vector const& v2, int i2, int size);
number maximum(vector const& v, int i, int size);