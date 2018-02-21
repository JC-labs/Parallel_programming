/*
    Parallel and Allotted Calculations.
    Lab #2: Threads in C#.

    The code was written by
        Krisak Ivan,
        student of IO-53, KPI.
    October 5, 2017.

    Functions:
    c = a.sort() * (ma * me) + b.sort();
    mg = mk.transpose() * (mh * mf);
    o = (r + s).sort() * (mt * mp);
*/
using System;
using System.Threading;

namespace parallel_programming_3
{
    class Lab3
    {
        static void Main(String[] args)
        {
            Math m = new Math();
            Thread t1 = new Thread(() =>
            {
                Console.WriteLine("Thread #1 has been initialized");

                Math.Vector a = m.fill_vector(1.0);//m.read_vector();
                Math.Vector b = m.fill_vector(1.0);//m.read_vector();
                Math.Matrix ma = m.fill_matrix(1.0);//m.read_matrix();
                Math.Matrix me = m.fill_matrix(1.0);//m.read_matrix();

                Thread.Sleep(15);
                Math.Vector c = m.function_1(a, b, ma, me);
                Thread.Sleep(15);
                m.print(c);

                Console.WriteLine("Thread #1 has finished the execution");
            });
            t1.Priority = ThreadPriority.Normal;
            t1.Start();
            Thread t2 = new Thread(() =>
            {
                Console.WriteLine("Thread #2 has been initialized");

                Math.Matrix mk = m.fill_matrix(1.0);//m.read_matrix();
                Math.Matrix mh = m.fill_matrix(1.0);//m.read_matrix();
                Math.Matrix mf = m.fill_matrix(1.0);//m.read_matrix();

                Thread.Sleep(15);
                Math.Matrix mg = m.function_2(mk, mh, mf);
                Thread.Sleep(15);
                m.print(mg);

                Console.WriteLine("Thread #2 has finished the execution");
            });
            t2.Priority = ThreadPriority.BelowNormal;
            t2.Start();
            Thread t3 = new Thread(() =>
            {
                Console.WriteLine("Thread #3 has been initialized");

                Math.Vector r = m.fill_vector(1.0);//m.read_vector();
                Math.Vector s = m.fill_vector(1.0);//m.read_vector();
                Math.Matrix mt = m.fill_matrix(1.0);//m.read_matrix();
                Math.Matrix mp = m.fill_matrix(1.0);//m.read_matrix();

                Thread.Sleep(15);
                Math.Vector o = m.function_3(r, s, mt, mp);
                Thread.Sleep(15);
                m.print(o);

                Console.WriteLine("Thread #3 has finished the execution");
            });
            t3.Priority = ThreadPriority.AboveNormal;
            t3.Start();

            t1.Join();
            t2.Join();
            t3.Join();
        }
    }
}