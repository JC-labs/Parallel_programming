/*
    Parallel and Allotted Calculations.
    Lab #8: MPI: distributed graph.

    The code was written by
        Krisak Ivan,
        student of IO-53, KPI.
    May 4th, 2018.

    Function:
	MA = max(Z) * MO + e * (MT * MR);
*/
#include "../../Course_Project/SharedMemorySystem/FileReader.hpp"
#include "../../Course_Project/SharedMemorySystem/Types.cpp"
#include <mpi.h>
#include <iostream>
#include <vector>
#include <algorithm>
int main() {
	int id, n, p, size;
	vector z;
	matrix mo, mt, mr;
	number e;
	number b;
	matrix ma;

	int is_provided, is_successful = MPI_Init_thread(nullptr, nullptr, MPI_THREAD_MULTIPLE, &is_provided);
	if (is_successful != MPI_SUCCESS || is_provided != MPI_THREAD_MULTIPLE)
		std::cout << ("MPI 3.0 isn't supported.");
	MPI_Comm_rank(MPI_COMM_WORLD, &id); MPI_Comm_size(MPI_COMM_WORLD, &p);
	if (id == 0) {
		std::ifstream fn;
		fn.open("data/n.txt");
		fn >> n;
	}
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	z.resize(n); mo.resize(n); mt.resize(n); mr.resize(n); ma.resize(n);
	if (id == 0) read_file("data/input.txt", z, mo, mt, mr, e);
	size = n / p;

	MPI_Group group;
	MPI_Comm graph_comm;
	int const topology_size = 11;
	int const indices[topology_size] = {4, 6, 8, 10, 13, 14, 15, 17, 18, 19, 20},
		edges[topology_size * 2] = { 1, 2, 3, 4,
					0, 5,
					0, 6,
					0, 7,
					0, 8, 9,
					1,
					2,
					3, 10,
					4,
					4,
					7
	};
	if (p != topology_size) {
		std::cout << "Unsupported number of processors... Aborting.\n";
		std::cin.get();
		return 0;
	}
	MPI_Graph_create(MPI_COMM_WORLD, topology_size, indices, edges, false, &graph_comm);
	MPI_Comm_group(graph_comm, &group);

	std::cout << "Process #" << id << " has been initialized.\n";
	if (n >= p) {
		number *z_l = new number[size];
		MPI_Scatter(z.data(), size, MPI_FLOAT, z_l, size, MPI_FLOAT, 0, graph_comm);

		number b_l = std::numeric_limits<number>::min();
		for (int i = 0; i < size; i++)
			if (b_l < z_l[i]) b_l = z_l[i];
		MPI_Reduce(&b_l, &b, 1, MPI_FLOAT, MPI_MAX, 0, graph_comm);

		mr.resize(n);
		MPI_Bcast(&b, 1, MPI_FLOAT, 0, graph_comm);
		MPI_Bcast(&e, 1, MPI_FLOAT, 0, graph_comm);
		MPI_Bcast(mr.data(), n * n, MPI_FLOAT, 0, graph_comm);
		
		matrix mo_l, mt_l; mo_l.resize(n, size); mt_l.resize(n, size);
		MPI_Scatter(mo.data(), size * n, MPI_FLOAT, mo_l.data(), size * n, MPI_FLOAT, 0, graph_comm);
		MPI_Scatter(mt.data(), size * n, MPI_FLOAT, mt_l.data(), size * n, MPI_FLOAT, 0, graph_comm);

		matrix ma_l; ma_l.resize(n, size);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < n; j++) {
				number temp = 0;
				for (int k = 0; k < n; k++)
					temp += mt_l[i][k] * mr[k][j];
				ma_l[i][j] += temp;
			}
			for (int j = 0; j < n; j++)
				ma_l[i][j] = ma_l[i][j] * e + mo_l[i][j] * b;
		}

		MPI_Gather(ma_l.data(), size * n, MPI_FLOAT, ma.data(), size * n, MPI_FLOAT, 0, graph_comm);
		if (id == 0) write_file(ma, std::cout);
	}

	std::cout << "Process #" << id << " has been finished.\n";
	MPI_Comm_free(&graph_comm);
	MPI_Finalize();
	return 0;
}