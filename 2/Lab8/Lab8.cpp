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
		z.resize(n); mo.resize(n); mt.resize(n); mr.resize(n);
		read_file("data/input.txt", z, mo, mt, mr, e);
	}
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
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

	//MPI_Intercomm_create(graph_comm, 0, )

	std::cout << "Process #" << id << " has been initialized.\n";
	if (n >= p) {
		number *z_l = new number[size];
		//z.resize(size);
		//MPI_Scatter((void*) z.data(), n, MPI_FLOAT, MPI_IN_PLACE, size, MPI_FLOAT, 0, MPI_COMM_WORLD);
		if (id == 0)
			MPI_Scatter((void*) z.data(), n, MPI_FLOAT, z_l, size, MPI_FLOAT, 0, MPI_COMM_WORLD);
		else {
			//z.resize(size);
			MPI_Scatter(MPI_IN_PLACE, n, MPI_FLOAT, z_l, size, MPI_FLOAT, 0, MPI_COMM_WORLD);
		}
		//MPI_Bcast(z.data(), n, MPI_FLOAT, 0, graph_comm);
		std::cout << "My local Z is ";
		for (int i = 0; i < size; i++)/*/(auto it : z)*/
			std::cout << z_l[i]/*/it*/ << '\t';
		std::cout << std::endl;
	}

	std::cout << "Process #" << id << " has been finished.\n";
	MPI_Comm_free(&graph_comm);
	MPI_Finalize();
	/*
	int n;
	std::ifstream fn;
	fn.open("data/n.txt");
	fn >> n;
	Memory m(n, 6);

	omp_set_dynamic(0);
	#pragma omp parallel num_threads(m.p)
	{
		int id = omp_get_thread_num();
		std::cout << "Thread #" << id + 1 << " has been initialized.\n";
		if (id == 0) read_file("data/input_0.txt", m.e, m.mk);
		if (id == 2) read_file("data/input_1.txt", m.z, m.mo);
		if (id == 5) read_file("data/input_2.txt", m.t, m.mr);

		#pragma omp barrier

		number b = std::numeric_limits<number>::min();
		#pragma omp for nowait
		for (int i = m.size * id; i < m.size * (id + 1); i++)
			if (b < m.z[i]) b = m.z[i];
		#pragma omp critical(min)
		{
			if (b < m.b) m.b = b;
		}

		vector t(n);
		omp_set_lock(&m.mutex);
		std::copy(m.t.begin(), m.t.end(), t.begin());
		omp_unset_lock(&m.mutex);

		#pragma omp for collapse(2)
		for (int i = m.size * id; i < m.size * (id + 1); i++)
			for (int j = 0; j < m.size; j++)
				m.c[i] += m.t[j] * m.mo[i][j];

		#pragma omp atomic read
			b = m.b;
		number temp;
		#pragma omp for
		for (int i = m.size * id; i < m.size * (id + 1); i++) {
			for (int j = 0; j < m.n; j++) {
				temp = 0;
				for (int k = 0; k < m.n; k++)
					temp += m.mk[i][k] * m.mr[k][j];
				m.a[i] += temp * m.c[j];
			}
			m.a[i] = m.a[i] + m.e[i] * b;
		}

		if (id == 2) write_file("data/output.txt", m.a);

		std::cout << "Thread #" << id + 1 << " has been resolved.\n";
	}
	return 0;
	*/
}
