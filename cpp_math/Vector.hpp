#pragma once
#include <algorithm>
namespace pp {
	template <typename T> class Matrix;
	template <typename T> class Vector {
		size_t m_size;
		T *m_data;
	public:
		Vector(size_t size) : m_size(size) { m_data = new T[size]{ (T)0.0 }; }
		~Vector() { delete[] m_data; }
		T const& operator[](size_t index) const { return m_data[index]; }
		T& operator[](size_t index) { return m_data[index]; }
		Vector<T> operator*(Matrix<T> const& m) const {
			Vector<T> ret(m_size);
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < n; j++)
					ret[i] += m_data[j] * m[j][i];
			return ret;
		}
		Vector<T> operator+(Vector<T> const& v) const {
			Vector ret = new Vector();
			for (size_t i = 0; i < n; i++)
				ret[i] = m_data[i] + v[i];
			return ret;
		}
		Vector<T> sort() { return std::sort(m_data, m_data + m_size); }
	};
}