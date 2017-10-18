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
			additional::write("Enter N for all the Vectors and Matrices: ");
			m_size = read_integer();
		}
		Vector<double> read_vector() {
			Vector<T> ret;
			for (size_t i = 0; i < m_size; i++)
				ret[i] = read_double();
			return ret;
		}
		Matrix<double> read_matrix() {
			Matrix<T> ret;
			for (size_t i = 0; i < m_size; i++)
				for (size_t j = 0; j < m_size; j++)
					ret[i][j] = read_double();
			return ret;
		}
		Vector<double> fill_vector(double value) {
			Vector<T> ret;
			for (size_t i = 0; i < m_size; i++)
				ret[i] = value;
			return ret;
		}
		Matrix<double> fill_matrix(double value) {
			Matrix<T> ret;
			for (size_t i = 0; i < m_size; i++)
				for (size_t j = 0; j < m_size; j++)
					ret[i][j] = value;
			return ret;
		}
		void print(Vector<double>& v) {
			if (m_size <= 10) {
				for (size_t i = 0; i < m_size; i++)
					additional::write(v[i]);
				additional::write("\n");
			}
		}
		void print(Matrix<double>& m) {
			if (m_size <= 10) {
				for (size_t i = 0; i < m_size; i++) {
					for (size_t j = 0; j < m_size; j++)
						additional::write(m[i][j]);
					additional::write("\n");
				}
				additional::write("\n");
			}
		}

		Vector<double> function_1(Vector<double> &a, Vector<double> &b, Matrix<double> &ma, Matrix<double> &me) {
			return a.sort() * (ma * me) + b.sort();
		}
		Matrix<double> function_2(Matrix<double> &mk, Matrix<double> &mh, Matrix<double> &mf) {
			return mk.transpose() * (mh * mf);
		}
		Vector<double> function_3(Vector<double> &r, Vector<double> &s, Matrix<double> &mt, Matrix<double> &mp) {
			return (r + s).sort() * (mt * mp);
		}
	};
}
