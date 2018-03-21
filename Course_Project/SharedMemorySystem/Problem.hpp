#pragma once
#include <iostream>
#include "Types.hpp"
#include "FileReader.hpp"

struct Memory {
	vector b, c, z;
	matrix ma, mo, mr, ms;

	void resize(size_t n) {
		::resize(b, n);
		::resize(c, n);
		::resize(z, n);
		::resize(ma, n);
		::resize(mo, n);
		::resize(mr, n);
		::resize(ms, n);
	}
	Memory(size_t n) { resize(n); }
};

void solve() {
	size_t p, n;
	read("data\\n.txt", p, n);

	Memory m(n);
	omp_set_dynamic(0);
	#pragma omp parallel num_threads(p)
	{
		auto t_id = omp_get_thread_num();
		if (t_id == 0)
			read("data\\input_0.txt", m.c, m.mo, m.ms);
		else if (t_id == p - 1)
			read("data\\input_0.txt", m.b, m.z, m.mr);
		#pragma omp barrier

		//Calculations

		#pragma omp barrier
		if (t_id == p - 1)
			write("data\\output.txt", m.ma);
	}
}