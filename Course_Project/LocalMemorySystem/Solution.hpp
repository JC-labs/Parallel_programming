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
number dot_product(vector const& v1, int i1, vector const& v2, int i2, int size) {
	number res = 0;
	size += i1;
	while (i1 < size) {
		res += v1[i1++] * v2[i2++];
	} return res;
}
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
		if (print_error_info && p != px * py) std::cout << "It's impossible to create specified number(" << px * py << ") of threads.";

		int y = id / px;
		int x = id - y * px;
		if constexpr (status_print) {
			std::stringstream str;
			str << "Thread #" << id << " has started.\n";
			std::cout << str.str();
		}
		
		vector c, b, z;
		matrix mo, ms, mr;
		if (id == 0) {
			resize(c, n); resize(mo, n); resize(ms, n);
			read_file("data\\input_0.txt", c, mo, ms);

			if (print_detailed_status_info) 
				std::cout << '\t' << x << ' ' << y << " starts sending c : " << c.size() << "\n";
			if (y != py - 1) Sync::send(x, y + 1, n - (px * size), &c[px * size]);
			if (x != px - 1) Sync::send(x + 1, y, (px - 1) * size, &c[size]);
			
			if (id != p - 1) {
				resize(b, (x + 1) * size);
				Sync::receive(x + 1, y, (x + 1) * size, &b[0]);
				if (print_detailed_status_info)
					std::cout << '\t' << x << ' ' << y << " has received part of b : " << b.size() << "\n";
			}

			auto d = dot_product(b, 0, c, 0, size);
			std::cout << '\t' << x << ' ' << y << " has calculated b * c. Result is equal to " << d << '\n';			
		}
		if (id == p - 1) {
			resize(b, n); resize(z, n); resize(mr, n);
			read_file("data\\input_1.txt", b, z, mr);

			if (id != 0) {
				resize(c, (px - x) * size);
				Sync::receive(x - 1, y, (px - x) * size, &c[0]);
				if (print_detailed_status_info)
					std::cout << '\t' << x << ' ' << y << " has received part of c : " << c.size() << "\n";
			}
			
			if (print_detailed_status_info)
				std::cout << '\t' << x << ' ' << y << " starts sending b : " << b.size() << "\n";
			if (y != 0) Sync::send(x, y - 1, n - (px * size), &b[0]);
			if (x != 0) Sync::send(x - 1, y, (px - 1) * size, &b[n - (px * size)]);

			auto d = dot_product(b, n - size - 1, c, 0, size);
			std::cout << '\t' << x << ' ' << y << " has calculated b * c. Result is equal to " << d << '\n';			
		} 
		if (id != 0 && id != p - 1) {
			if (x == 0) {
				resize(c, (py - y) * px * size);
				Sync::receive(x, y - 1, (py - y) * px * size, &c[0]);
				if (y != py - 1) Sync::send(x, y + 1, (py - y - 1) * px * size, &c[px * size]);
			} else {
				resize(c, (px - x) * size);
				Sync::receive(x - 1, y, (px - x) * size, &c[0]);
			}
			if (x != px - 1) Sync::send(x + 1, y, (px - x - 1) * size, &c[size]);
			if (print_detailed_status_info)
				std::cout << '\t' << x << ' ' << y << " has received part of c : " << c.size() << "\n";
			
			if (x == px - 1) {
				resize(b, (y + 1) * px * size);
				Sync::receive(x, y + 1, (y + 1) * px * size, &b[0]);
				if (y != 0) Sync::send(x, y - 1, y * px * size, &b[0]);
				if (x != 0) Sync::send(x - 1, y, x * size, &b[y * px * size]);
			} else {
				resize(b, (x + 1) * size);
				Sync::receive(x + 1, y, (x + 1) * size, &b[0]);
				if (x != 0) Sync::send(x - 1, y, x * size, &b[0]);
			}
			if (print_detailed_status_info)
				std::cout << '\t' << x << ' ' << y << " has received part of b : " << b.size() << "\n";

			auto d = dot_product(b, b.size() - size, c, 0, size);
			std::cout << '\t' << x << ' ' << y << " has calculated b * c. Result is equal to " << d << '\n';
		}

		if (status_print) {
			std::stringstream str;
			str << "Thread #" << id << " has finished.\n";
			std::cout << str.str();
		}
	} MPI_Finalize();
}