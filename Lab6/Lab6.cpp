/*
    Parallel and Allotted Calculations.
    Lab #6: Threads in MPI.

    The code was written by
        Krisak Ivan,
        student of IO-53, KPI.
    November 1, 2017.

    Functions:
    c = a.sort() * (ma * me) + b.sort();
    mg = mk.transpose() * (mh * mf);
    o = (r + s).sort() * (mt * mp);
*/
#include "Math.hpp"
#include <mpi.h>
void function1(pp::Math<double>* math) {
	pp::additional::write("Thread #1 has been initialized\n");
	pp::Vector<double> a = math->fill_vector(1.0);//math.read_vector();
	pp::Vector<double> b = math->fill_vector(1.0);//math.read_vector();
	pp::Matrix<double> ma = math->fill_matrix(1.0);//math.read_matrix();
	pp::Matrix<double> me = math->fill_matrix(1.0);//math.read_matrix();
	pp::Vector<double> c = math->function_1(a, b, ma, me);
	math->print(c);
	pp::additional::write("Thread #1 has finished its execution\n");
}
void function2(pp::Math<double>* math) {
	pp::additional::write("Thread #2 has been initialized\n");
	pp::Matrix<double> mk = math->fill_matrix(1.0);//math->read_matrix();
	pp::Matrix<double> mh = math->fill_matrix(1.0);//math->read_matrix();
	pp::Matrix<double> mf = math->fill_matrix(1.0);//math->read_matrix();
	pp::Matrix<double> mg = math->function_2(mk, mh, mf);
	math->print(mg);
	pp::additional::write("Thread #2 has finished its execution\n");
}
void function3(pp::Math<double>* math) {
	pp::additional::write("Thread #3 has been initialized\n");
	pp::Vector<double> r = math->fill_vector(1.0);//math->read_vector();
	pp::Vector<double> s = math->fill_vector(1.0);//math->read_vector();
	pp::Matrix<double> mt = math->fill_matrix(1.0);//math->read_matrix();
	pp::Matrix<double> mp = math->fill_matrix(1.0);//math->read_matrix();
	pp::Vector<double> o = math->function_3(r, s, mt, mp);
	math->print(o);
	pp::additional::write("Thread #3 has finished its execution\n");
}
static int numprocs;
int main(int argN, char** args) {
	pp::Math<double> math;
	MPI_Status status; 
	MPI_Init(&argN, &args);
	MPI_Comm_size (MPI_COMM_WORLD, &numprocs); 
	MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);  
	double time_start = MPI_Wtime();
	std::cout << "Hello World, my rank is " << my_rank <<" "<< MPI_Wtime() - time_start << std::endl; 
	MPI_Finalize (); 
	return 0;
}