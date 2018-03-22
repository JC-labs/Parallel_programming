#pragma once
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Types.hpp"
#include "FileReader.hpp"

struct Memory {
	vector b, c, z;
	matrix ma, mo, mr, ms;

	void resize(int n) {
		::resize(b, n);
		::resize(c, n);
		::resize(z, n);
		::resize(ma, n);
		::resize(mo, n);
		::resize(mr, n);
		::resize(ms, n);
	}
	Memory(int n) { resize(n); }
};

template <bool output = true, bool status_print = true, bool copy = false, bool no_temp = false, bool for_blocks = false>
void solve() {
	int p, n;
	read("data\\n.txt", p, n);

	int size = n / p;
	Memory m(n);
	number d = 0, e = std::numeric_limits<number>::min();

	omp_lock_t ms_copy;
	if constexpr (copy) omp_init_lock(&ms_copy);

	omp_set_dynamic(0);
	#pragma omp parallel num_threads(p)
	{
		int t_id = omp_get_thread_num();
		if (status_print) {
			std::stringstream str;
			str << "Thread #" << t_id << " has started.\n";
			std::cout << str.str();
		}

		int start = size * t_id;
		int finish = start + size;

		if (t_id == 0)
			read("data\\input_0.txt", m.c, m.mo, m.ms);
		else if (t_id == p - 1)
			read("data\\input_0.txt", m.b, m.z, m.mr);
		#pragma omp barrier

		if (no_temp) {
			if (for_blocks) {
				#pragma omp for reduction(+:d)
				for (int i = 0; i < n; i++)
					d += m.b[i] * m.c[i];
				#pragma omp for
				for (int i = 0; i < n; i++) {
					#pragma omp critical(cs_max)
					{
						if (m.z[i] > e)
							e = m.z[i];
					}
				}
			} else {
				for (int i = start; i < finish; i++) {
					#pragma omp atomic
						d += m.b[i] * m.c[i];
				}
				for (int i = start; i < finish; i++) {
					#pragma omp critical(cs_max)
					{
						if (m.z[i] > e)
							e = m.z[i];
					}
				}
			}
		} else {
			number d_i = 0, e_i = std::numeric_limits<number>::min();
			if (for_blocks) {
				#pragma omp for
				for (int i = 0; i < n; i++)
					d_i += m.b[i] * m.c[i];
				#pragma omp atomic
				d += d_i;
				#pragma omp for
				for (int i = 0; i < n; i++)
					if (m.z[i] > e_i)
						e_i = m.z[i];
				#pragma omp critical(cs_max)
				{
					if (e_i > e) e = e_i;
				}
			} else {
				for (int i = start; i < finish; i++)
					d_i += m.b[i] * m.c[i];
				#pragma omp atomic
					d += d_i;
				for (int i = 0; i < n; i++)
					if (m.z[i] > e_i)
						e_i = m.z[i];
				#pragma omp critical(cs_max)
				{
					if (e_i > e) e = e_i;
				}
			}
		}

		#pragma omp barrier

		if (copy) {
			matrix ms_i; 
			number d_i, e_i;
			resize(ms_i, n);
			#pragma omp critical(cs_copy)
			{
				d_i = d;
				e_i = e;
			}
			omp_set_lock(&ms_copy);
			std::copy(m.ms.begin(), m.ms.end(), ms_i.begin());
			omp_unset_lock(&ms_copy);

			if (for_blocks) {
				#pragma omp for
				for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++) {
						number t = 0;
						for (int k = 0; k < n; k++)
							t += m.mr[i][k] * ms_i[k][j];
						m.ma[i][j] = m.mo[i][j] * d_i + t * e_i;
					}
			} else {
				for (int i = start; i < finish; i++)
					for (int j = 0; j < n; j++) {
						number t = 0;
						for (int k = 0; k < n; k++)
							t += m.mr[i][k] * ms_i[k][j];
						m.ma[i][j] = m.mo[i][j] * d_i + t * e_i;
					}
			}
		} else {
			if (for_blocks) {
				#pragma omp for
				for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++) {
						number t = 0;
						for (int k = 0; k < n; k++)
							t += m.mr[i][j] * m.ms[i][j];
						m.ma[i][j] = m.mo[i][j] * d + t * e;
					}
			} else {
				for (int i = start; i < finish; i++)
					for (int j = 0; j < n; j++) {
						number t = 0;
						for (int k = 0; k < n; k++)
							t += m.mr[i][j] * m.ms[i][j];
						m.ma[i][j] = m.mo[i][j] * d + t * e;
					}
			}
		}

		#pragma omp barrier
		if (output && t_id == p - 1)
			write("data\\output.txt", m.ma);
		if (status_print) {
			std::stringstream str;
			str << "Thread #" << t_id << " has finished.\n";
			std::cout << str.str();
		}
	}
	if constexpr (copy) omp_destroy_lock(&ms_copy);
}