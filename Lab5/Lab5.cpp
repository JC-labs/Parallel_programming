/*
    Parallel and Allotted Calculations.
    Lab #5: Threads in OpenMP.

    The code was written by
        Krisak Ivan,
        student of IO-53, KPI.
    October 25, 2017.

    Functions:
    c = a.sort() * (ma * me) + b.sort();
    mg = mk.transpose() * (mh * mf);
    o = (r + s).sort() * (mt * mp);
*/
#include "Math.hpp"
int main() {
	[](void* m) -> void* {
		pp::additional::write("Thread #1 has been initialized\n");
		auto math = (pp::Math<double>*)m;
		pp::Vector<double> a = math->fill_vector(1.0);//math.read_vector();
		pp::Vector<double> b = math->fill_vector(1.0);//math.read_vector();
		pp::Matrix<double> ma = math->fill_matrix(1.0);//math.read_matrix();
		pp::Matrix<double> me = math->fill_matrix(1.0);//math.read_matrix();		
		//sleep(15000);
		pp::Vector<double> c = math->function_1(a, b, ma, me);
		//sleep(15000);
		math->print(c);
		pp::additional::write("Thread #1 has finished its execution\n");
	};
	[](void* m) -> void* {
		pp::additional::write("Thread #2 has been initialized\n");
		auto math = (pp::Math<double>*)m;
		pp::Matrix<double> mk = math->fill_matrix(1.0);//math->read_matrix();
		pp::Matrix<double> mh = math->fill_matrix(1.0);//math->read_matrix();
		pp::Matrix<double> mf = math->fill_matrix(1.0);//math->read_matrix();
		//sleep(15000);
		pp::Matrix<double> mg = math->function_2(mk, mh, mf);
		//sleep(15000);
		math->print(mg);
		pp::additional::write("Thread #2 has finished its execution\n");
	};
	[](void* m) -> void* {
		pp::additional::write("Thread #3 has been initialized\n");
		auto math = (pp::Math<double>*)m;
		pp::Vector<double> r = math->fill_vector(1.0);//math->read_vector();
		pp::Vector<double> s = math->fill_vector(1.0);//math->read_vector();
		pp::Matrix<double> mt = math->fill_matrix(1.0);//math->read_matrix();
		pp::Matrix<double> mp = math->fill_matrix(1.0);//math->read_matrix();
		//sleep(15000);
		pp::Vector<double> o = math->function_3(r, s, mt, mp);
		//sleep(15000);
		math->print(o);
		pp::additional::write("Thread #3 has finished its execution\n");
	};
	return 0;
}