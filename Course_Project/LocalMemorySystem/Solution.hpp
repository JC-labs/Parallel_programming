#pragma once
#include <mpi.h>
#include <iostream>
#include <functional>
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
	static void send(int x, int y, void *ptr) {
		MPI_Send(ptr, 1, MPI_FLOAT, y * px + x, 0, MPI_COMM_WORLD);
	}
	static void receive(int x, int y, void *ptr) {
		MPI_Recv(ptr, 1, MPI_FLOAT, y * px + x, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	static void send(int x, int y, int row_count, int col_count, void *ptr) {
		MPI_Send(ptr, row_count * col_count, MPI_FLOAT, y * px + x, 0, MPI_COMM_WORLD);
	}
	static void receive(int x, int y, int row_count, int col_count, void *ptr) {
		MPI_Recv(ptr, row_count * col_count, MPI_FLOAT, y * px + x, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
};
template<bool left_to_right> constexpr int inv(int c, int pc) { if constexpr(left_to_right) return c; else return pc - c - 1; }
template<bool minimum, bool dir, bool print_detailed_status_info = true>
void distribute(int x, int y, int px, int py, int size, matrix &m) {
	int n = px * py * size;
	if (inv<dir>(x, px) == 0 && inv<dir>(y, py) == 0) {
		if constexpr (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " starts sending the matrix : " << m.size_x() << 'x' << m.size_y() << "\n";
		if (inv<dir>(y, py) != py - 1) Sync::send(x, y + (dir ? 1 : -1), minimum ? (py - 1) * px * size : n, n, m.data() + (minimum ? n * (dir ? px * size : 0) : 0));
		if (inv<dir>(x, px) != px - 1) Sync::send(x + (dir ? 1 : -1), y, minimum ? (px - 1) * size : n, n, m.data() + (minimum ? n * (dir ? size : (py - 1) * px * size) : 0));
	} else {
		if (inv<dir>(x, px) == px - 1 && inv<dir>(y, py) == py - 1) {
			m.resize(n, minimum ? (px - inv<dir>(x, px)) * size : n);
			if (inv<dir>(x, px) != 0) Sync::receive(x - (dir ? 1 : -1), y, minimum ? (px - inv<dir>(x, px)) * size : n, n, m.data());
		} else {
			if (inv<dir>(x, px) == 0) {
				m.resize(n, minimum ? (py - inv<dir>(y, py)) * px * size : n);
				Sync::receive(x, y - (dir ? 1 : -1), minimum ? (py - inv<dir>(y, py)) * px * size : n, n, m.data());
				if (inv<dir>(y, py) != py - 1) Sync::send(x, y + (dir ? 1 : -1), minimum ? (py - inv<dir>(y, py) - 1) * px * size : n, n, m.data() + (minimum ? n * (dir ? px * size : 0) : 0));
			} else {
				m.resize(n, minimum ? (px - inv<dir>(x, px)) * size : n);
				Sync::receive(x - (dir ? 1 : -1), y, minimum ? (px - inv<dir>(x, px)) * size : n, n, m.data());
			}
			if (inv<dir>(x, px) != px - 1) Sync::send(x + (dir ? 1 : -1), y, minimum ? (px - inv<dir>(x, px) - 1) * size : n, n, m.data() + (minimum ? n * (dir ? size : (x == px - 1 ? y * px * size : 0)) : 0));
		}
		if constexpr (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " has received part of the vector : " << m.size_x() << 'x' << m.size_y() << "\n";
	}
}
template<bool dir, bool print_detailed_status_info = true>
void distribute(int x, int y, int px, int py, int size, vector &v) {
	if (inv<dir>(x, px) == 0 && inv<dir>(y, py) == 0) {
		if constexpr (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " starts sending the vector : " << v.size() << "\n";
		if (inv<dir>(y, py) != py - 1) Sync::send(x, y + (dir ? 1 : -1), (py - 1) * px * size, &v[dir ? px * size : 0]);
		if (inv<dir>(x, px) != px - 1) Sync::send(x + (dir ? 1 : -1), y, (px - 1) * size, &v[dir ? size : (py - 1) * px * size]);
	} else {
		if (inv<dir>(x, px) == px - 1 && inv<dir>(y, py) == py - 1) {
			v.resize((px - inv<dir>(x, px)) * size);
			if (inv<dir>(x, px) != 0) Sync::receive(x - (dir ? 1 : -1), y, (px - inv<dir>(x, px)) * size, &v[0]);
		} else {
			if (inv<dir>(x, px) == 0) {
				v.resize((py - inv<dir>(y, py)) * px * size);
				Sync::receive(x, y - (dir ? 1 : -1), (py - inv<dir>(y, py)) * px * size, &v[0]);
				if (inv<dir>(y, py) != py - 1) Sync::send(x, y + (dir ? 1 : -1), (py - inv<dir>(y, py) - 1) * px * size, &v[dir ? px * size : 0]);
			} else {
				v.resize((px - inv<dir>(x, px)) * size);
				Sync::receive(x - (dir ? 1 : -1), y, (px - inv<dir>(x, px)) * size, &v[0]);
			}
			if (inv<dir>(x, px) != px - 1) Sync::send(x + (dir ? 1 : -1), y, (px - inv<dir>(x, px) - 1) * size, &v[dir ? size : (x == px - 1 ? y * px * size : 0)]);
		}
		if constexpr (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " has received part of the vector : " << v.size() << "\n";
	}
}
template<bool dir, bool print_detailed_status_info = true>
void distribute(int x, int y, int px, int py, int size, number &value, 
				std::function<number(number, number)> lambda 
				= [](number a, number b) -> number { return a; }) {
	if (inv<dir>(x, px) == 0 && inv<dir>(y, py) == 0) {
		if constexpr (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " starts sending its value : " << value << "\n";
		if (inv<dir>(x, px) != px - 1) Sync::send(x + (dir ? 1 : -1), y, &value);
	} else if (inv<dir>(x, px) == px - 1 && inv<dir>(y, py) == py - 1) {
		number temp;
		if (inv<dir>(x, px) != 0) Sync::receive(x - (dir ? 1 : -1), y, &temp);
		value = lambda(value, temp);
		if (inv<dir>(y, py) != 0) Sync::receive(x, y - (dir ? 1 : -1), &temp);
		value = lambda(value, temp);
		if constexpr (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " has calculated its value : " << value << "\n";
	} else {
		number temp;
		if (inv<dir>(x, px) == px - 1 && inv<dir>(y, py) != 0) {
			Sync::receive(x, y - (dir ? 1 : -1), &temp);
			value = lambda(value, temp);
		}
		if (inv<dir>(x, px) != 0) {
			Sync::receive(x - (dir ? 1 : -1), y, &temp);
			value = lambda(value, temp);
		}
		if (inv<dir>(x, px) == px - 1 && inv<dir>(y, py) != py - 1)
			Sync::send(x, y + (dir ? 1 : -1), &value);
		else if (inv<dir>(x, px) != px - 1)
			Sync::send(x + (dir ? 1 : -1), y, &value);
		if constexpr (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " has calculated its value : " << value << "\n";
	}
}
bool const left_to_right = true;
bool const right_to_left = false;
bool const minimum_distribution = true;
bool const full_distribution = false;
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
		if (print_error_info && p != px * py) 
			std::cout << "It's impossible to create specified number(" << px * py << ") of threads.";

		int y = id / px;
		int x = id - y * px;
		if constexpr (status_print) std::cout << "Thread #" << id << " has started.\n";
		
		vector c, b, z;
		matrix mo, ms, mr;
		if (id == 0) {
			c.resize(n); mo.resize(n); ms.resize(n);
			read_file("data\\input_0.txt", c, mo, ms);
		}
		if (id == p - 1) {
			b.resize(n); z.resize(n); mr.resize(n);
			read_file("data\\input_1.txt", b, z, mr);
		}

		distribute<left_to_right, print_detailed_status_info>(x, y, px, py, size, c);
		distribute<right_to_left, print_detailed_status_info>(x, y, px, py, size, b);
		number d = dot_product(b, id == 0 ? 0 : b.size() - size, c, 0, size);
		if constexpr (status_print) 
			std::cout << '\t' << x << ' ' << y << " has calculated b * c. Result is equal to " << d << '\n';
		distribute<left_to_right, print_detailed_status_info>(x, y, px, py, size, d, [](number a, number b) -> number {
			return a + b; 
		});
		std::cout << '\n';

		distribute<right_to_left, print_detailed_status_info>(x, y, px, py, size, z);
		number e = maximum(z, id == 0 ? 0 : z.size() - size, size);
		if constexpr (status_print)
			std::cout << '\t' << x << ' ' << y << " has calculated max(z). Result is equal to " << e << '\n';
		distribute<left_to_right, print_detailed_status_info>(x, y, px, py, size, e, [](number a, number b) -> number {
			return a > b ? a : b;
		});
		std::cout << '\n';

		distribute<full_distribution, left_to_right, print_detailed_status_info>(x, y, px, py, size, mo);
		std::cout << "\t\t\t";
		for (auto it : mo) std::cout << it << ' ';
		std::cout << '\n';

		if (status_print) std::cout << "Thread #" << id << " has finished.\n";
	} MPI_Finalize();
}