#pragma once
#include <mpi.h>
#include <iostream>
#include <functional>
#include "..\SharedMemorySystem\Types.hpp"
class Sync {
	inline static int px;
	Sync() {};
public:
	static void init(int _px) { px = _px; }
	static void send(int x, int y, void *ptr) { return send(x, y, 1, ptr); }
	static void send(int x, int y, int count, void *ptr) { MPI_Send(ptr, count, MPI_FLOAT, y * px + x, 0, MPI_COMM_WORLD); }
	static void send(int x, int y, int row_count, int col_count, void *ptr) { MPI_Send(ptr, row_count * col_count, MPI_FLOAT, y * px + x, 0, MPI_COMM_WORLD); }
	static void receive(int x, int y, void *ptr) { return receive(x, y, 1, ptr); }
	static void receive(int x, int y, int count, void *ptr) { MPI_Recv(ptr, count, MPI_FLOAT, y * px + x, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); }
	static void receive(int x, int y, int row_count, int col_count, void *ptr) { MPI_Recv(ptr, row_count * col_count, MPI_FLOAT, y * px + x, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); }
	static void broadcast(int x, int y, void *ptr) { return broadcast(x, y, 1, ptr); }
	static void broadcast(int x, int y, int count, void *ptr) { MPI_Bcast(ptr, count, MPI_FLOAT, y * px + x, MPI_COMM_WORLD); }
	static void broadcast(int x, int y, int row_count, int col_count, void *ptr) { MPI_Bcast(ptr, row_count * col_count, MPI_FLOAT, y * px + x, MPI_COMM_WORLD); }
};
template<bool left_to_right> constexpr int inv(int c, int pc) { if constexpr(left_to_right) return c; else return pc - c - 1; }
template<bool minimum, bool dir, bool print_detailed_status_info = true>
void distribute(int x, int y, int px, int py, int size, matrix &m) {
	int n = px * py * size;
	if (inv<dir>(x, px) == 0 && inv<dir>(y, py) == 0) {
		if constexpr (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " starts sending a matrix : " << m.size_x() << 'x' << m.size_y() << "\n";
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
			std::cout << '\t' << x << ' ' << y << " has received a matrix : " << m.size_x() << 'x' << m.size_y() << "\n";
	}
}
template<bool dir, bool print_detailed_status_info = true>
void collect(int x, int y, int px, int py, int size, matrix &m) {
	int n = px * py * size;
	if (inv<dir>(x, px) == 0 && inv<dir>(y, py) == 0) {
		if constexpr (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " starts sending a matrix : " << m.size_x() << 'x' << m.size_y() << '\n';
		if (inv<dir>(x, px) != px - 1) Sync::send(x + (dir ? 1 : -1), y, size, n, m.data());
	} else {
		if (inv<dir>(x, px) == px - 1 && inv<dir>(y, py) == py - 1) {
			m.resize(n, n);
			std::move(m.begin(), m.begin() + size * n, m.end() - size * n);
			if (inv<dir>(y, py) != 0) Sync::receive(x, y - (dir ? 1 : -1), y * px * size, n, m.data());
			if (inv<dir>(x, px) != 0) Sync::receive(x - (dir ? 1 : -1), y, x * size, n, m.data() + y * px * size * n);
		} else {
			if (inv<dir>(x, px) == px - 1) {
				m.resize(n, (y + 1) * px * size);
				std::move(m.begin(), m.begin() + size * n, m.end() - size * n);
				if (inv<dir>(y, py) != 0) Sync::receive(x, y - (dir ? 1 : -1), y * px * size, n, m.data());
				if (inv<dir>(x, px) != 0) Sync::receive(x - (dir ? 1 : -1), y, x * size, n, m.data() + y * px * size * n);
			} else {
				m.resize(n, (x + 1) * size);
				std::move(m.begin(), m.begin() + size * n, m.end() - size * n);
				if (inv<dir>(x, px) != 0) Sync::receive(x - (dir ? 1 : -1), y, x * size, n, m.data());
			}
			if (inv<dir>(x, px) == px - 1 && inv<dir>(y, py) != py - 1)
				Sync::send(x, y + (dir ? 1 : -1), (y + 1) * px * size, n, m.data());
			else if (inv<dir>(x, px) != px - 1)
				Sync::send(x + (dir ? 1 : -1), y, (x + 1) * size, n, m.data());
		}
		if constexpr (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " has received a matrix : " << m.size_x() << 'x' << m.size_y() << "\n";
	}
}
template<bool minimum, bool dir, bool print_detailed_status_info = true>
void distribute(int x, int y, int px, int py, int size, vector &v) {
	int n = px * py * size;
	if (inv<dir>(x, px) == 0 && inv<dir>(y, py) == 0) {
		if constexpr (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " starts sending a vector : " << v.size() << "\n";
		if (inv<dir>(y, py) != py - 1) Sync::send(x, y + (dir ? 1 : -1), minimum ? (py - 1) * px * size : n, v.data() + (minimum ? (dir ? px * size : 0) : 0));
		if (inv<dir>(x, px) != px - 1) Sync::send(x + (dir ? 1 : -1), y, minimum ? (px - 1) * size : n, v.data() + (minimum ? (dir ? size : (py - 1) * px * size) : 0));
	} else {
		if (inv<dir>(x, px) == px - 1 && inv<dir>(y, py) == py - 1) {
			v.resize(minimum ? (px - inv<dir>(x, px)) * size : n);
			if (inv<dir>(x, px) != 0) Sync::receive(x - (dir ? 1 : -1), y, minimum ? (px - inv<dir>(x, px)) * size : n, v.data());
		} else {
			if (inv<dir>(x, px) == 0) {
				v.resize(minimum ? (py - inv<dir>(y, py)) * px * size : n);
				Sync::receive(x, y - (dir ? 1 : -1), minimum ? (py - inv<dir>(y, py)) * px * size : n, v.data());
				if (inv<dir>(y, py) != py - 1) Sync::send(x, y + (dir ? 1 : -1), minimum ? (py - inv<dir>(y, py) - 1) * px * size : n, v.data() + (minimum ? (dir ? px * size : 0) : 0));
			} else {
				v.resize(minimum ? (px - inv<dir>(x, px)) * size : n);
				Sync::receive(x - (dir ? 1 : -1), y, minimum ? (px - inv<dir>(x, px)) * size : n, v.data());
			}
			if (inv<dir>(x, px) != px - 1) Sync::send(x + (dir ? 1 : -1), y, minimum ? (px - inv<dir>(x, px) - 1) * size : n, v.data() + (minimum ? (dir ? size : (x == px - 1 ? y * px * size : 0)) : 0));
		}
		if constexpr (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " has received a vector : " << v.size() << "\n";
	}
}
template<bool dir, bool print_detailed_status_info = true>
void collect(int x, int y, int px, int py, int size, number &value,
			 std::function<number(number, number)> lambda
			 = [](number a, number b) -> number { return a; }) {
	if (inv<dir>(x, px) == 0 && inv<dir>(y, py) == 0) {
		if constexpr (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " starts sending a number : " << value << "\n";
		if (inv<dir>(x, px) != px - 1) Sync::send(x + (dir ? 1 : -1), y, &value);
	} else {
		if (inv<dir>(x, px) == px - 1 && inv<dir>(y, py) == py - 1) {
			number temp;
			if (inv<dir>(x, px) != 0) Sync::receive(x - (dir ? 1 : -1), y, &temp);
			value = lambda(value, temp);
			if (inv<dir>(y, py) != 0) Sync::receive(x, y - (dir ? 1 : -1), &temp);
			value = lambda(value, temp);
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
		}
		if constexpr (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " has calculated a number : " << value << "\n";
	}
}
template<bool print_detailed_status_info = true>
void broadcast(int x, int y, number &value) { Sync::broadcast(x, y, &value); }
bool const left_to_right = true;
bool const right_to_left = false;
bool const minimum = true;
bool const full = false;