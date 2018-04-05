#pragma once
#include <vector>
#include <istream>
using number = float;
using vector = std::vector<number>;
using matrix = std::vector<vector>;

void fill(vector &v, number value);
void fill(matrix &m, number value);
void get(vector &v, std::istream &s);
void get(matrix &m, std::istream &s);
void resize(vector &v, size_t n);
void resize(matrix &m, size_t n);
void write_file(matrix const& m, std::ostream &s);
void write_file(vector const& v, std::ostream &s);