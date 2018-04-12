using System;
using System.Threading;

namespace parallel_programming_3 {
    
    class Lab3 {
        static private Int32 p = 8;
        static private Int32 n, size;
        static private Double[] a, z, s, t;
        static private Double[,] mo, mk;
        static private Double b, d;

        static private Mutex mtx;
        static private SemaphoreSlim sem1;
        static private ManualResetEvent[] ev;
        static private CountdownEvent sem2;

        class Thread_Class {
            Int32 id;
            Double temp_value;
            public Thread_Class(Int32 i, Double t) { id = i; temp_value = t; }
            public void run() {
                Console.WriteLine("Task #" + (id + 1) + " has started.");
                if (id + 1 == 1) {
                    fill(n, temp_value, ref z);
                    fill(n, temp_value, ref mk);
                    ev[0].Set();
                } else if (id + 1 == p - 1) {
                    d = temp_value;
                    fill(n, temp_value, ref s);
                    ev[1].Set();
                } else if (id + 1 == p) {
                    fill(n, temp_value, ref t);
                    fill(n, temp_value, ref mo);
                    ev[2].Set();
                }
                WaitHandle.WaitAll(ev);
                Double b_i = Double.MaxValue;
                for (Int32 i = size * id; i < (id == p - 1 ? n : size * (id + 1)); i++)
                    if (b_i > s[i]) b_i = s[i];

                Thread.BeginCriticalRegion();
                if (b > b_i) b = b_i;
                Thread.EndCriticalRegion();

                sem2.Signal();
                sem2.Wait();

                mtx.WaitOne();
                Double d_i = d;
                mtx.ReleaseMutex();
                sem1.Wait();
                b_i = b;
                sem1.Release();

                Double temp;
                for (int i = size * id; i < (id == p - 1 ? n : size * (id + 1)); i++) {
                    for (int j = 0; j < n; j++) {
                        temp = 0;
                        for (int k = 0; k < n; k++)
                            temp += mo[i,k] * mk[k,j];
                        a[i] += temp * t[j];
                    }
                    a[i] = a[i] * b + d * z[i];
                }
                sort(ref a, size * id, (id == p - 1 ? n : size * (id + 1)) - 1);

                if (id % 2 == 0) {
                   tasks[id + 1].Join();
                    merge(ref a, size * id, size * (id + 1) - 1, size * (id + 1), (id + 1 == p - 1 ? n : size * (id + 2)) - 1);
                }
                if (id % 4 == 0) {
                    tasks[id + 2].Join();
                    merge(ref a, size * id, size * (id + 2) - 1, size * (id + 2), (id + 3 == p - 1 ? n : size * (id + 4)) - 1);
                }
                if (id % 8 == 0) {
                    tasks[id + 4].Join();
                    merge(ref a, size * id, size * (id + 4) - 1, size * (id + 4), (id + 7 == p - 1 ? n : size * (id + 8)) - 1);
                }
                if (id + 1 == 1)
                    if (n <= 10) {
                        for (Int32 i = 0; i < n; i++)
                            Console.Write(a[i] + " ");
                        Console.WriteLine();
                    }

                Console.WriteLine("Task #" + (id + 1) + " was finished.");
            }
        }
        static private Thread[] tasks;
        static void Main(String[] args) {
            Console.Write("Enter N for all the vectors an matrices: ");
            n = Int32.Parse(Console.ReadLine());
            Console.Write("Enter a value to fill all the matrices and vectors: ");
            Double tmp = Double.Parse(Console.ReadLine());
            a = new Double[n];
            size = n / p;
            tasks = new Thread[p];
            mtx = new Mutex(false);
            sem1 = new SemaphoreSlim(1, 1);
            ev = new ManualResetEvent[3];
            for (Int16 i = 0; i < 3; i++) ev[i] = new ManualResetEvent(false);
            sem2 = new CountdownEvent(8);
            for (Int16 i = 0; i < p; i++) tasks[i] = new Thread((new Thread_Class(i, tmp)).run);
            for (Int32 i = 0; i < p; i++) tasks[i].Start();
            tasks[0].Join();
            return;
        }
        static void fill(Int32 n, Double v, ref Double[] c) {
            c = new Double[n];
            for (Int32 i = 0; i < n; i++)
                c[i] = v;
        }
        static void fill(Int32 n, Double v, ref Double[,] c) {
            c = new Double[n, n];
            for (Int32 i = 0; i < n; i++)
                for (Int32 j = 0; j < n; j++)
                    c[i, j] = v;
        }
        static void sort(ref Double[] v, int s, int e) {
            bool swapped;
            do {
                swapped = false;
                for (int i = s; i < e; i++)
                    if (v[i] > v[i + 1]) {
                        var temp = v[i + 1];
                        v[i + 1] = v[i];
                        v[i] = temp;
                        swapped = true;
                    }
            } while (swapped);
        }
        static void merge(ref Double[] v, int i, int ie, int j, int je) {
            if (size == 0) return;
            Double[] res = new Double[je - i];
            int ri = 0;
            while (i < ie && j < je)
                if (v[i] < v[j])
                    res[ri++] = v[i++];
                else
                    res[ri++] = v[j++];
            while (i < ie)
                res[ri++] = v[i++];
            while (j < je)
                res[ri++] = v[j++];
            for (int c = i; c < je; c++)
                v[c] = res[c];
        }
    }
}