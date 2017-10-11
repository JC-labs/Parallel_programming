/*
    Parallel and Allotted Calculations.
    Lab #2: Threads in Java.

    The code was written by
        Krisak Ivan,
        student of IO-53, KPI.
    September 27, 2017.

    Functions:
    c = a.sort() * (ma * me) + b.sort();
    mg = mk.transpose() * (mh * mf);
    o = (r + s).sort() * (mt * mp);
 */
package j;
public class L1 {

    static class Thread_1 extends Thread {
        private Math m;
        public Thread_1(Math m_){
            m = m_;
        }
        @Override
        public void run() {
            System.out.println("Thread #1 has been initialized");

            Math.Vector a  = m.fill_vector(1.0);//m.read_vector();
            Math.Vector b  = m.fill_vector(1.0);//m.read_vector();
            Math.Matrix ma = m.fill_matrix(1.0);//m.read_matrix();
            Math.Matrix me = m.fill_matrix(1.0);//m.read_matrix();

            try {
                Thread.sleep(15);
                Math.Vector c = m.function_1(a, b, ma, me);
                Thread.sleep(15);
                m.print(c);
            } catch (InterruptedException e) {
                System.out.println("Thread #1 was suddenly interrupted");
            }

            System.out.println("Thread #1 has finished the execution");
        }
    }

    static class Thread_2_Runnable implements Runnable {
        private Math m;
        public Thread_2_Runnable(Math m_){
            m = m_;
        }
        @Override
        public void run() {
            System.out.println("Thread #2 has been initialized");

            Math.Matrix mk = m.fill_matrix(1.0);//m.read_matrix();
            Math.Matrix mh = m.fill_matrix(1.0);//m.read_matrix();
            Math.Matrix mf = m.fill_matrix(1.0);//m.read_matrix();

            try {
                Thread.sleep(15);
                Math.Matrix mg = m.function_2(mk, mh, mf);
                Thread.sleep(15);
                m.print(mg);
            } catch (InterruptedException e) {
                System.out.println("Thread #2 was suddenly interrupted");
            }

            System.out.println("Thread #2 has finished the execution");
        }
    }

    public static void main(String[] args) {
        Math m = new Math();

        Thread t1 = new Thread_1(m);
        t1.setPriority(Thread.NORM_PRIORITY);
        t1.start();
        Thread t2 = new Thread(new Thread_2_Runnable(m));
        t2.setPriority(Thread.MIN_PRIORITY);
        t2.start();
        Thread t3 = new Thread(() -> {
            System.out.println("Thread #3 has been initialized");

            Math.Vector r  = m.fill_vector(1.0);//m.read_vector();
            Math.Vector s  = m.fill_vector(1.0);//m.read_vector();
            Math.Matrix mt = m.fill_matrix(1.0);//m.read_matrix();
            Math.Matrix mp = m.fill_matrix(1.0);//m.read_matrix();

            try {
                Thread.sleep(15);
                Math.Vector o = m.function_3(r, s, mt, mp);
                Thread.sleep(15);
                m.print(o);
            } catch (InterruptedException e) {
                System.out.println("Thread #3 was suddenly interrupted");
            }

            System.out.println("Thread #3 has finished the execution");
        });
        t3.setPriority(Thread.MAX_PRIORITY);
        t3.start();
    }
}