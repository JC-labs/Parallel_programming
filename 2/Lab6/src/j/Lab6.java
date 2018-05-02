/*
	Parallel and alloted calculations. Part 2
	Lab #6 Monitores
	with A = (B * C) * (T * MO) + min(Z) * S * (MT * MR);
	
	was implemented by
	Krisak Ivan Mykolayovich,
	a student of IO-53
*/
package j;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;
public class Lab6 {
	private static Math m;
	private static int p = 6;
	private static int size;
	
	private static Math.Vector a, b, c, s, t, z;
	private static Math.Matrix mo, mk, mr;

	private static class dot_product extends RecursiveTask<Double> {
		private Math.Vector b, c;
		private int from, to;
		public dot_product(Math.Vector _b, Math.Vector _c, int _from, int _to) { b = _b; c = _c; from = _from; to = _to; }
		@Override
		protected Double compute() {
			if (to - from == 1)
				return b.get(from) * c.get(from);
			else if (to - from == 2) {
				return b.get(from) * c.get(from) + b.get(to - 1) * c.get(to - 1);
			} else {
				int offset = (to - from) / 2;
				dot_product left_fork = new dot_product(b, c, from, from + offset);
				left_fork.fork();
				dot_product right_fork = new dot_product(b, c, from + offset, to);
				return right_fork.compute() + left_fork.join();
			}
		}
	};
	private static class Minimum extends RecursiveTask<Double> {
		private Math.Vector z;
		private int from, to;
		public Minimum(Math.Vector _z, int _from, int _to) { z = _z; from = _from; to = _to; }
		@Override
		protected Double compute() {
			if (to - from == 1)
				return z.get(from);
			else if (to - from == 2) {
				return z.get(from) < z.get(to - 1) ? z.get(from) : z.get(to - 1);
			} else {
				int offset = (to - from) / 2;
				Minimum left_fork = new Minimum(z, from, from + offset);
				left_fork.fork();
				Minimum right_fork = new Minimum(z, from + offset, to);
				Double right = right_fork.compute(),
						left = left_fork.join();
				return left < right ? left : right;
			}
		}
	};

	private static class synchronization_monitor {
		private int fi = 0, fa = 0;
		public synchronization_monitor() {}
		public synchronized void signal_input() { if (++fi >= 4) { notifyAll(); } }
		public synchronized void wait_input() {
			try { if (fi < 4) wait(); } catch(Exception e) { e.printStackTrace(); }
		}
		public synchronized void signal_a() { if (++fa >= p - 1) { notifyAll(); } }
		public synchronized void wait_a() {
			try { if (fi < p - 1) wait(); } catch(Exception e) { e.printStackTrace(); }
		}
	}
	private static class resource_monitor {
		private Double d = 0.0, e = 0.0;
		public synchronized void set_d(Double _d) { d = _d; }
		public synchronized void set_e(Double _e) { e = _e; }
		public synchronized Double get_d() { return d; };
		public synchronized Double get_e() { return e; };
	}
	
	private static synchronization_monitor sync;
	private static resource_monitor res;
	private static class Threads extends Thread {
		private Math m;
		private int id;
		public Threads(Math _m, int _id) { m = _m; id = _id; }
		@Override
		public void run() {
			System.out.println("Thread #" + String.valueOf(id + 1) + " has been initialized");
			int fin;
			if (id == p - 1) fin = m.getN();
			else fin = size * (id + 1);

			if (id == 0) {
				b = m.fill_vector(1.0);
				c = m.fill_vector(1.0);
				mr = m.fill_matrix(1.0);
				a = m.fill_vector(0.0);

				res.set_d(new ForkJoinPool().invoke(new dot_product(b, c, 0, m.getN())));

				sync.signal_input();
			} else if (id == 1) {
				t = m.fill_vector(1.0);
				mk = m.fill_matrix(1.0);
				sync.signal_input();
			} else if (id == p - 2) {
				mo = m.fill_matrix(1.0);
				sync.signal_input();
			} else if (id == p - 1) {
				s = m.fill_vector(1.0);
				z = m.fill_vector(1.0);

				res.set_e(new ForkJoinPool().invoke(new Minimum(z, 0, m.getN())));

				sync.signal_input();
			}
			sync.wait_input();

			double d = res.get_d();
			double e = res.get_e();
			Math.Vector v = m.fill_vector(0.0);
			if (fin != 0) {
				for (int i = size * id; i < fin; i++) {
					for (int j = 0; j < m.getN(); j++) {
						double tmp = 0.0;
						for (int k = 0; k < m.getN(); k++)
							tmp += mk.get(i, k) * mr.get(k, j);
						a.append(i, s.get(i) * tmp);
						v.append(i, t.get(i) * mo.get(i, j));
					}
					a.set(i, a.get(i) * e + v.get(i) * d);
				}
			}

			if (id != 0)
				sync.signal_a();
			else {
				sync.wait_a();
				m.print(a);
			}

			System.out.println("Thread #" + String.valueOf(id + 1) + " has finished its execution");
		}
	}
	
	public static void main(String[] args) {
		m = new Math();
		size = m.getN() / p;
		sync = new synchronization_monitor();
		res = new resource_monitor();
		Threads ts[] = new Threads[p];
		for (int i = 0; i < p; i++)
			(ts[i] = new Threads(m, i)).start();
		for (int i = 0; i < p; i++)
			try { ts[i].join(); } catch (Exception e) { e.printStackTrace(); }
	}
}