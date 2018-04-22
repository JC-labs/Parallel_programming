#pragma once
#include <mpi.h>
#include <iostream>
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
template<bool left_to_right> int inv(int c, int pc) { if constexpr(left_to_right) return c; else return pc - c - 1; }
template<bool dir, bool print_detailed_status_info = true>
void distribute(int x, int y, int px, int py, int size, vector &v) {
	if (inv<dir>(x, px) == 0 && inv<dir>(y, py) == 0) {
		if (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " starts sending the vector : " << v.size() << "\n";
		if (inv<dir>(y, py) != py - 1) Sync::send(x, y + (dir ? 1 : -1), (py - 1) * px * size, &v[dir ? px * size : 0]);
		if (inv<dir>(x, px) != px - 1) Sync::send(x + (dir ? 1 : -1), y, (px - 1) * size, &v[dir ? size : (py - 1) * px * size]);
	} else if (inv<dir>(x, px) == px - 1 && inv<dir>(y, py) == py - 1) {
		resize(v, (px - inv<dir>(x, px)) * size);
		Sync::receive(x - (dir ? 1 : -1), y, (px - inv<dir>(x, px)) * size, &v[0]);
		if (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " has received part of the vector : " << v.size() << "\n";
	} else {
		if (inv<dir>(x, px) == 0) {
			resize(v, (py - inv<dir>(y, py)) * px * size);
			Sync::receive(x, y - (dir ? 1 : -1), (py - inv<dir>(y, py)) * px * size, &v[0]);
			if (inv<dir>(y, py) != py - 1) Sync::send(x, y + (dir ? 1 : -1), (py - inv<dir>(y, py) - 1) * px * size, &v[dir ? px * size : 0]);
		} else {
			resize(v, (px - inv<dir>(x, px)) * size);
			Sync::receive(x - (dir ? 1 : -1), y, (px - inv<dir>(x, px)) * size, &v[0]);
		}
		if (inv<dir>(x, px) != px - 1) Sync::send(x + (dir ? 1 : -1), y, (px - inv<dir>(x, px) - 1) * size, &v[dir ? size : (x == px - 1 ? y * px * size : 0)]);
		if (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " has received part of the vector : " << v.size() << "\n";
	}
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
		int id, p; MPI_Comm_rank(MPI_COMM_WORLD, &id); MPI_Comm_size(MPI_COMM_WORLD, &p);
		if (print_error_info && p != px * py) std::cout << "It's impossible to create specified number(" << px * py << ") of threads.";

		int y = id / px;
		int x = id - y * px;
		if constexpr (status_print) std::cout << "Thread #" << id << " has started.\n";
		
		vector c, b, z;
		matrix mo, ms, mr;
		if (id == 0) {
			resize(c, n); resize(mo, n); resize(ms, n);
			read_file("data\\input_0.txt", c, mo, ms);
		}
		if (id == p - 1) {
			resize(b, n); resize(z, n); resize(mr, n);
			read_file("data\\input_1.txt", b, z, mr);
		}

		distribute<true, print_detailed_status_info>(x, y, px, py, size, c);
		distribute<false, print_detailed_status_info>(x, y, px, py, size, b);

		number d = dot_product(b, id == 0 ? 0 : b.size() - size, c, 0, size);
		std::cout << '\t' << x << ' ' << y << " has calculated b * c. Result is equal to " << d << '\n';

		if (status_print) std::cout << "Thread #" << id << " has finished.\n";
	} MPI_Finalize();
}