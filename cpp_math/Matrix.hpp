#pragma once
#include "Vector.hpp"
namespace pp {
	template <typename T> class Matrix {
		size_t m_size;
		Vector<T>* m_data;
	protected:
		void swap(size_t i, size_t j) {
			T temp = m_data[i][j];
			m_data[i][j] = m_data[j][i];
			m_data[j][i] = temp;
		}
	public:
		Matrix(size_t size) : m_size(size) {
			m_data = new Vector<T>[size] {size};
			for (size_t i = 0; i < size; i++)
				m_data[i] = Vector<T>(size);
		}
		~Matrix() { delete[] m_data; }
		Vector<T> const& operator[](size_t index) const { return m_data[index]; }
		Vector<T>& operator[](size_t index) { return m_data[index]; }
		Matrix operator*(Matrix const& m) {
			Matrix ret(m_size);
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < n; j++)
					for (size_t k = 0; k < n; k++)
						ret[i][j] += m_data[i][k] * m[k][j];
			return ret;
		}
		Matrix& transpose() {
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < i; j++)
					swap(i, j);
			return this;
		}
	};
}