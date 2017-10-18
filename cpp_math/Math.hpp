#pragma once
#include "Matrix.hpp"
namespace pp {
	namespace additional {
		void write(char* text);
		void write(double n);
	}
	int read_integer();
	double read_double();

	template <typename T> class Math {
		size_t m_size;
	public:
		Math() {
			write("Enter N for all the Vectors and Matrices: ");
			m_size = read_integer();
		}
		Vector<T> read_vector() {
			Vector<T> ret;
			for (size_t i = 0; i < n; i++)
				ret[i] = read_double();
			return ret;
		}
		Matrix<double> read_matrix() {
			Matrix<T> ret;
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < n; j++)
					ret[i][j] = read_double();
			return ret;
		}
		Vector<double> fill_vector(double value) {
			Vector<T> ret;
			for (size_t i = 0; i < n; i++)
				ret[i] = value;
			return ret;
		}
		Matrix<double> fill_matrix(double value) {
			Matrix<T> ret;
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < n; j++)
					ret[i][j] = value;
			return ret;
		}
		void print(Vector<double>& v) {
			if (m_size <= 10) {
				for (size_t i = 0; i < m_size; i++)	write(v[i]);
				write("\n");
			}
		}
		void print(Matrix<double>& m) {
			if (m_size <= 10) {
				for (size_t i = 0; i < m_size; i++) {
					for (size_t j = 0; j < m_size; j++)
						write(m[i][j]);
					write("\n");
				}
				write("\n");
			}
		}

		Vector<double> function_1(Vector a, Vector b, Matrix ma, Matrix me) {
			return a.sort() * (ma * me) + b.sort();
		}
		Matrix function_2(Matrix mk, Matrix mh, Matrix mf) {
			return mk.transpose() * (mh * mf);
		}
		Vector function_3(Vector r, Vector s, Matrix mt, Matrix mp) {
			return (r + s).sort() * (mt * mp);
		}
	};
}