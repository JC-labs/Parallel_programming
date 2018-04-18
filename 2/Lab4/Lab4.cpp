/*
    Parallel and Allotted Calculations.
    Lab #4: OpenMP: mutexes, bariers, critical sections and parallel loops.

    The code was written by
        Krisak Ivan,
        student of IO-53, KPI.
    April 18, 2018.

    Function:
	A = max(Z) * E + (T * MO) * (MK * MR);
*/
#include "../../Course_Project/SharedMemorySystem/FileReader.hpp"
#include "../../Course_Project/SharedMemorySystem/Types.cpp"
#include <omp.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
struct Memory {
	int n, p, size;

	vector a, z, e, t;
	matrix mo, mk, mr;

	number b;
	vector c;

	omp_lock_t mutex;

	void clear(int n) {
		b = std::numeric_limits<number>::min();
		::resize(a, n);
		::resize(z, n);
		::resize(e, n);
		::resize(t, n);
		::resize(mo, n);
		::resize(mk, n);
		::resize(mr, n);

		::resize(c, n);
	}
	Memory(int _n, int _p) {
		n = _n; p = _p; size = _n / _p;
		clear(_n);
		omp_init_lock(&mutex);
	}
	~Memory() {
		omp_destroy_lock(&mutex);
	}
};

int main() {
	int n;
	std::ifstream fn;
	fn.open("data/n.txt");
	fn >> n;
	Memory m(n, 4);

	omp_set_dynamic(0);
	#pragma omp parallel num_threads(m.p)
	{
		int id = omp_get_thread_num();
		std::cout << "Thread #" << id << " has been initialized.\n";
		if (id == 0) read_file("data/input_0.txt", m.e, m.mk);
		if (id == 3) read_file("data/input_1.txt", m.z, m.mo);
		if (id == 6) read_file("data/input_2.txt", m.t, m.mr);

		#pragma omp barrier

		number b = std::numeric_limits<number>::min();
		#pragma omp for nowait
		for (int i = m.size * id; i < m.size * (id + 1); i++)
			if (b < m.z[i]) b = m.z[i];
		#pragma omp critical(min)
		{
			if (b < m.b) m.b = b;
		}

		vector t(n);
		omp_set_lock(&m.mutex);
		std::copy(m.t.begin(), m.t.end(), t.begin());
		omp_unset_lock(&m.mutex);

		#pragma omp for collapse(2)
		for (int i = m.size * id; i < m.size * (id + 1); i++)
			for (int j = 0; j < m.size; j++)
				m.c[i] += m.t[j] * m.mo[i][j];

		#pragma omp atomic read
			b = m.b;
		number temp;
		#pragma omp for collapse(3)
		for (int i = m.size * id; i < m.size * (id + 1); i++) {
			for (int j = 0; j < m.n; j++) {
				temp = 0;
				for (int k = 0; k < m.n; k++)
					temp += m.mk[i][k] * m.mr[k][j];
				m.a[i] += temp * m.c[j];
			}
			m.a[i] = m.a[i] + m.e[i] * b;
		}

		if (id == 3) write_file("data/output.txt", m.a);

		std::cout << "Thread #" << id << " has been resolved.\n";
	}
	return 0;
}
