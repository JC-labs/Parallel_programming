#pragma once
#include <algorithm>
namespace pp {
	template <typename T> class Matrix;
	template <typename T> class Vector {
		size_t m_size;
		T *m_data;
	protected:
		Vector(size_t size, T *data) : m_size(size), m_data(data) {}
	public:
		explicit Vector() {}
		Vector(size_t size) : m_size(size) { m_data = new T[size]{ (T)0.0 }; }
		~Vector() { delete[] m_data; }
		T const& operator[](size_t index) const { return m_data[index]; }
		T& operator[](size_t index) { return m_data[index]; }
		Vector<T> operator*(Matrix<T> const& m) const {
			Vector<T> ret(m_size);
			for (size_t i = 0; i < m_size; i++)
				for (size_t j = 0; j < m_size; j++)
					ret[i] += m_data[j] * m[j][i];
			return ret;
		}
		Vector<T> operator+(Vector<T> const& v) const {
			Vector ret(m_size);
			for (size_t i = 0; i < m_size; i++)
				ret[i] = m_data[i] + v[i];
			return ret;
		}
		Vector<T>& sort() { std::sort(m_data, m_data + m_size); return *this; }
	};
}
