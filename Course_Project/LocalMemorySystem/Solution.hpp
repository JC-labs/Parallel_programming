#pragma once
#include <mpi.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "..\SharedMemorySystem\Types.hpp"
#include "..\SharedMemorySystem\FileReader.hpp"
class Sync {
	inline static int px;
public:
	static void init(int _px) { px = _px; }
	static void send(int x, int y, int count, void *ptr) {
		MPI_Send(ptr, count, MPI_FLOAT, y * px + x, 0, MPI_COMM_WORLD);
	}
	static void receive(int x, int y, int count, void *ptr) {
		MPI_Recv(ptr, count, MPI_FLOAT, y * px + x, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
};
template <bool output = true, bool status_print = true, bool print_detailed_status_info = true, bool print_error_info = true>
void solve(int px, int py, int n) {
	int size = n / (px * py);
	int x = px / 2, y = py / 2;
	Sync::init(px);

	int provided;
	if (auto temp = MPI_Init_thread(nullptr, nullptr, MPI_THREAD_MULTIPLE, &provided);
			(temp != MPI_SUCCESS || provided != MPI_THREAD_MULTIPLE) && print_error_info)
		std::cout << ("MPI 3.0 isn't supported.");
	{
		int id, p; 
		MPI_Comm_rank(MPI_COMM_WORLD, &id);
		MPI_Comm_size(MPI_COMM_WORLD, &p);
		if (print_error_info && p != px * py) std::cout << ("It's impossible to create specified number of threads.");

		int y = id / px;
		int x = id - y * px;
		if constexpr (status_print) {
			std::stringstream str;
			str << "Thread #" << id << " has started.\n";
			std::cout << str.str();
		}

		int start = size * id;
		int finish = start + size;

		if (id == 0) {
			vector c; resize(c, n);
			matrix mo; resize(mo, n);
			matrix ms; resize(ms, n);
			read_file("data\\input_0.txt", c, mo, ms);
			write_file("data\\output.txt", mo);

			if (print_detailed_status_info) 
				std::cout << '\t' << x << ' ' << y << " starts sending c : " << c.size() << "\n";
			if (y != py - 1) Sync::send(x, y + 1, n - (px * size), &c[px * size]);
			if (x != px - 1) Sync::send(x + 1, y, (px - 1) * size, &c[size]);
		}
		if (id == p - 1) {
			vector b; resize(b, n);
			vector z; resize(z, n);
			matrix mr; resize(mr, n);
			read_file("data\\input_1.txt", b, z, mr);

			vector c; resize(c, (px - x) * size);
			Sync::receive(x - 1, y, (px - x) * size, &c[0]);
			if (print_detailed_status_info) 
				std::cout << '\t' << x << ' ' << y << " has received part of c : " << c.size() << "\n";
		} 
		if (id != 0 && id != p - 1) {
			vector c;
			if (x == 0) {
				resize(c, (py - y) * px * size);
				Sync::receive(x, y - 1, (py - y) * px * size, &c[0]);
				if (y != py - 1) Sync::send(x, y + 1, (px - x - 1) * size, &c[px * size]);
				if (x != px - 1) Sync::send(x + 1, y, (px - 1) * size, &c[size]);
				if (print_detailed_status_info)
					std::cout << '\t' << x << ' ' << y << " has received part of c : " << c.size() << "\n";
			} else {
				resize(c, (px - x) * size);
				Sync::receive(x - 1, y, (px - x) * size, &c[0]);
				if (x != px - 1) Sync::send(x + 1, y, (px - x - 1) * size, &c[size]);
				if (print_detailed_status_info)
					std::cout << '\t' << x << ' ' << y << " has received part of c : " << c.size() << "\n";
			}
		}

		if (status_print) {
			std::stringstream str;
			str << "Thread #" << id << " has finished.\n";
			std::cout << str.str();
		}
	} MPI_Finalize();

		/*
		#pragma omp barrier

		if (no_temp) {
			if (for_blocks) {
				#pragma omp for reduction(+:d) nowait
				for (int i = 0; i < n; i++)
					d += m.b[i] * m.c[i];
				#pragma omp for nowait
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
				#pragma omp for nowait
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
				#pragma omp for nowait
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
			write_file("data\\output.txt", m.ma);
	}
	if constexpr (copy) omp_destroy_lock(&ms_copy);*/
}