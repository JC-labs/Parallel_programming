/*
    Parallel and Allotted Calculations.
    Lab #4: Threads in POSIX.

    The code was written by
        Krisak Ivan,
        student of IO-53, KPI.
    October 18, 2017.

    Functions:
    c = a.sort() * (ma * me) + b.sort();
    mg = mk.transpose() * (mh * mf);
    o = (r + s).sort() * (mt * mp);
*/
#include "Math.hpp"
#include <pthread.h>
#include <unistd.h>
int main() {
	pthread_t task1, task2, task3;

	auto math = new pp::Math<double>;

	if (pthread_create(&task1, NULL, [](void* m) -> void* {
		pp::additional::write("Thread #1 has been initialized\n");
		auto math = (pp::Math<double>*)m;

		pp::Vector<double> a = math->fill_vector(1.0);//math.read_vector();
		pp::Vector<double> b = math->fill_vector(1.0);//math.read_vector();
		pp::Matrix<double> ma = math->fill_matrix(1.0);//math.read_matrix();
		pp::Matrix<double> me = math->fill_matrix(1.0);//math.read_matrix();
		
		usleep(15000);
		pp::Vector<double> c = math->function_1(a, b, ma, me);
		usleep(15000);

		math->print(c);
		pp::additional::write("Thread #1 has finished its execution\n");
	}, math))
		return -1;	

	pthread_join(task1, NULL);
	pthread_join(task2, NULL);
	pthread_join(task3, NULL);
	return 0;
}
