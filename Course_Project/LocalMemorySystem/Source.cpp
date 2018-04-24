#include "Solution.hpp"
int main() {
	if (int provided, temp = MPI_Init_thread(nullptr, nullptr, MPI_THREAD_MULTIPLE, &provided);
			(temp != MPI_SUCCESS || provided != MPI_THREAD_MULTIPLE))
		std::cout << ("MPI 3.0 isn't supported.");
	int id, p; MPI_Comm_rank(MPI_COMM_WORLD, &id); MPI_Comm_size(MPI_COMM_WORLD, &p);
	std::chrono::time_point<std::chrono::steady_clock> start_time;
	if (id == p - 1)
		start_time = std::chrono::high_resolution_clock::now();
	int data[3];
	if (id == 0) {
		std::ifstream fn;
		fn.open("data/n.txt");
		fn >> data[0] >> data[1] >> data[2];
		if (p != data[0] * data[1])
			std::cout << "It's impossible to create specified number(" << data[0] * data[1] << ") of processes.";
	}
	MPI_Bcast(data, 3, MPI_INT, 0, MPI_COMM_WORLD);

	solve<false, true, false, true>(data[0], data[1], data[2]);
	if (id == p - 1) {
		std::ofstream ft;
		ft.open("data/testing.txt", std::fstream::app);
		ft << "Test with p = " << data[0] << "x" << data[1] << " and n = " << data[2] << " took " << 
			std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start_time).count() << " microseconds.\n";
	}

	MPI_Finalize();
	return 0;
}