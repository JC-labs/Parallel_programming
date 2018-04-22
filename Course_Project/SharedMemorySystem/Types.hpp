#pragma once
#include <vector>
#include <istream>
using number = float;
using vector = std::vector<number>;
class matrix : std::vector<number> {
	size_t m_size;
public:
	inline vector operator[](size_t const i) { return std::vector<number>(begin() + i * m_size, end() + (i + 1) * m_size); }
	inline vector const operator[](size_t const i) const { return std::vector<number>(begin() + i * m_size, end() + (i + 1) * m_size); }
	inline vector at(size_t const i) { return std::vector<number>(begin() + i * m_size, end() + (i + 1) * m_size); }
	inline vector const at(size_t const i) const { return std::vector<number>(begin() + i * m_size, end() + (i + 1) * m_size); }
	inline void resize(size_t i) { std::vector<number>::resize(i * i); m_size = i; }
	inline size_t const size() const { return m_size; }
	inline number* data() { return &std::vector<number>::at(0); }
	inline number const* data() const { return &std::vector<number>::at(0); }
	using std::vector<number>::begin;
	using std::vector<number>::end;
};

void fill(vector &v, number value);
void fill(matrix &m, number value);
void get(vector &v, std::istream &s);
void get(matrix &m, std::istream &s);
void resize(vector &v, size_t n);
void resize(matrix &m, size_t n);
void write_file(matrix const& m, std::ostream &s);
void write_file(vector const& v, std::ostream &s);
number dot_product(vector const& v1, int i1, vector const& v2, int i2, int size);
number maximum(vector const& v, int i, int size);