/*
    Parallel and Allotted Calculations.
    Lab #7: Threads in C++1x.

    The code was written by
        Krisak Ivan,
        student of IO-53, KPI.
    November 8, 2017.

    Functions:
    c = a.sort() * (ma * me) + b.sort();
    mg = mk.transpose() * (mh * mf);
    o = (r + s).sort() * (mt * mp);
*/
#include "Math.hpp"
#include <thread>
#include <chrono>
using namespace std::literals;
class f1_thread : public std::thread {
public:
	explicit f1_thread(pp::Math<double>* math = new pp::Math<double>()) : std::thread([math]() {
		pp::additional::write("Thread #1 has been initialized\n");
		pp::Vector<double> a = math->fill_vector(1.0);//math.read_vector();
		pp::Vector<double> b = math->fill_vector(1.0);//math.read_vector();
		pp::Matrix<double> ma = math->fill_matrix(1.0);//math.read_matrix();
		pp::Matrix<double> me = math->fill_matrix(1.0);//math.read_matrix();
		std::this_thread::sleep_for(1ms);
		pp::Vector<double> c = math->function_1(a, b, ma, me);
		std::this_thread::sleep_for(1ms);
		math->print(c);
		pp::additional::write("Thread #1 has finished its execution\n");
	}) {}
};
class f2 {
public:
	void operator()(pp::Math<double>* math = new pp::Math<double>()) {
		pp::additional::write("Thread #2 has been initialized\n");
		pp::Matrix<double> mk = math->fill_matrix(1.0);//math->read_matrix();
		pp::Matrix<double> mh = math->fill_matrix(1.0);//math->read_matrix();
		pp::Matrix<double> mf = math->fill_matrix(1.0);//math->read_matrix();
		std::this_thread::sleep_for(1ms);
		pp::Matrix<double> mg = math->function_2(mk, mh, mf);
		std::this_thread::sleep_for(1ms);
		math->print(mg);
		pp::additional::write("Thread #2 has finished its execution\n");
	}
};
void f3(pp::Math<double>* math = new pp::Math<double>()) {
	pp::additional::write("Thread #3 has been initialized\n");
	pp::Vector<double> r = math->fill_vector(1.0);//math->read_vector();
	pp::Vector<double> s = math->fill_vector(1.0);//math->read_vector();
	pp::Matrix<double> mt = math->fill_matrix(1.0);//math->read_matrix();
	pp::Matrix<double> mp = math->fill_matrix(1.0);//math->read_matrix();
	std::this_thread::sleep_for(1ms);
	pp::Vector<double> o = math->function_3(r, s, mt, mp);
	std::this_thread::sleep_for(1ms);
	math->print(o);
	pp::additional::write("Thread #3 has finished its execution\n");
}
int main(int argN, char** args) {
	auto math = new pp::Math<double>();
	f1_thread t1(math);
	std::thread t2(f2(), math);
	std::thread t3(f3, math);

	t1.join();
	t2.join();
	t3.join();
	delete math;
	return 0;
}
