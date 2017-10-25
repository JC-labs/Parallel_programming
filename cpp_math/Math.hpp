#pragma once
#include "Matrix.hpp"
#include <string>
namespace pp {
	namespace additional {
		void write(std::string const& text);
		void write(double n);
	}
	int read_integer();
	double read_double();

	template <typename T> class Math {
		size_t m_size;
	public:
		Math() {
			additional::write("Enter N for all the Vectors and Matrices: ");
			m_size = read_integer();
		}
		Vector<T> read_vector() {
			Vector<T> ret(m_size);
			for (size_t i = 0; i < m_size; i++)
				ret[i] = read_double();
			return ret;
		}
		Matrix<T> read_matrix() {
			Matrix<T> ret(m_size);
			for (size_t i = 0; i < m_size; i++)
				for (size_t j = 0; j < m_size; j++)
					ret[i][j] = read_double();
			return ret;
		}
		Vector<T> fill_vector(T value) {
			Vector<T> ret(m_size);
			for (size_t i = 0; i < m_size; i++)
				ret[i] = value;
			return ret;
		}
		Matrix<T> fill_matrix(T value) {
			Matrix<T> ret(m_size);
			for (size_t i = 0; i < m_size; i++)
				for (size_t j = 0; j < m_size; j++)
					ret[i][j] = value;
			return ret;
		}
		void print(Vector<T>& v) {
			if (m_size <= 10) {
				for (size_t i = 0; i < m_size; i++)
					additional::write(v[i]);
				additional::write("\n");
			}
		}
		void print(Matrix<T>& m) {
			if (m_size <= 10) {
				for (size_t i = 0; i < m_size; i++) {
					for (size_t j = 0; j < m_size; j++)
						additional::write(m[i][j]);
					additional::write("\n");
				}
			}
		}

		Vector<T> function_1(Vector<T> &a, Vector<T> &b, Matrix<T> &ma, Matrix<T> &me) {
			return a.sort() * (ma * me) + b.sort();
		}
		Matrix<T> function_2(Matrix<T> &mk, Matrix<T> &mh, Matrix<T> &mf) {
			return mk.transpose() * (mh * mf);
		}
		Vector<T> function_3(Vector<T> &r, Vector<T> &s, Matrix<T> &mt, Matrix<T> &mp) {
			return (r + s).sort() * (mt * mp);
		}
	};
}
