#pragma once
#include "Distribution.hpp"
#include "..\SharedMemorySystem\FileReader.hpp"
template <bool output = true, bool status_print = true, bool print_detailed_status_info = false, bool print_error_info = true>
void solve(int px, int py, int n) {
	int size = n / (px * py);
	Sync::init(px);
	
	int provided;
	if (auto temp = MPI_Init_thread(nullptr, nullptr, MPI_THREAD_MULTIPLE, &provided);
			(temp != MPI_SUCCESS || provided != MPI_THREAD_MULTIPLE) && print_error_info)
		std::cout << ("MPI 3.0 isn't supported.");
	{
		int id, p; MPI_Comm_rank(MPI_COMM_WORLD, &id); MPI_Comm_size(MPI_COMM_WORLD, &p);
		if (print_error_info && p != px * py) 
			std::cout << "It's impossible to create specified number(" << px * py << ") of processes.";

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

		distribute<minimum, left_to_right, print_detailed_status_info>(x, y, px, py, size, c);
		distribute<minimum, right_to_left, print_detailed_status_info>(x, y, px, py, size, b);
		number d = dot_product(b, id == 0 ? 0 : b.size() - size, c, 0, size);
		if constexpr (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " has calculated b * c. Result is equal to " << d << '\n';
		collect<left_to_right, print_detailed_status_info>(x, y, px, py, size, d, [](number a, number b) -> number {
			return a + b; 
		});
		if constexpr (print_detailed_status_info) std::cout << '\n';

		distribute<minimum, right_to_left, print_detailed_status_info>(x, y, px, py, size, z);
		number e = maximum(z, id == 0 ? 0 : z.size() - size, size);
		if constexpr (print_detailed_status_info)
			std::cout << '\t' << x << ' ' << y << " has calculated max(z). Result is equal to " << e << '\n';
		collect<left_to_right, print_detailed_status_info>(x, y, px, py, size, e, [](number a, number b) -> number {
			return a > b ? a : b;
		});
		if constexpr (print_detailed_status_info) std::cout << '\n';

		distribute<minimum, left_to_right, print_detailed_status_info>(x, y, px, py, size, mo);
		distribute<minimum, right_to_left, print_detailed_status_info>(x, y, px, py, size, mr);
		distribute<full, left_to_right, print_detailed_status_info>(x, y, px, py, size, ms);
		broadcast<print_detailed_status_info>(px - 1, py - 1, d);
		broadcast<print_detailed_status_info>(px - 1, py - 1, e);
		matrix ma = calculate(mo, 0, mr, mr.size_y() - size, ms, d, e, n, size);
		if constexpr (print_detailed_status_info) {
			std::cout << '\t' << x << ' ' << y << " has calculated ma.\n";
			std::cout << "\tResult is a matrix (" << ma.size_x() << 'x' << ma.size_y() << ") :";
			int i = 0;
			for (auto it : ma) {
				if (i++ % ma.size_x() == 0) std::cout << "\n\t\t\t"; 
				std::cout << it << ' ';
			}
			std::cout << '\n';
		}
		collect<left_to_right, print_detailed_status_info>(x, y, px, py, size, ma);

		if (x == px - 1 && y == py - 1) {
			write_file("data/output.txt", ma);
			if constexpr (print_detailed_status_info) {
				std::cout << '\t' << x << ' ' << y << " has received resulting matrix.\n";
				std::cout << "\tResult is a matrix (" << ma.size_x() << 'x' << ma.size_y() << ") :";
				int i = 0;
				for (auto it : ma) {
					if (i++ % ma.size_x() == 0) std::cout << "\n\t\t\t";
					std::cout << it << ' ';
				}
				std::cout << '\n';
			}
		}
		if (status_print) std::cout << "Thread #" << id << " has finished.\n";
	} MPI_Finalize();
}