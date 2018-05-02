/*
	Parallel and alloted calculations. Part 2
	Lab #6 Monitores
	with A = (B * C) * (T * MO) + min(Z) * S * (MT * MR);
	
	was implemented by
	Krisak Ivan Mykolayovich,
	a student of IO-53
*/
package j;
public class Lab6 {
	private static Math m;
	private static int p = 6;
	private static int size;
	
	private static Math.Vector a, b, c, s, t, z;
	private static Math.Matrix mo, mk, mr;
	
	private static class synchronization_monitor {
		private int fi = 0, fde = 0, fa = 0;
		public synchronization_monitor() {}
		
		public synchronized void signal_input() { if (++fi >= 4) { notifyAll(); }
		public synchronized void wait_input() { 
			try { if (fi < 4) wait(); } catch(Exception e) { e.printStackTrace(); }
		}
		
		public synchronized void signal_d_and_e() { if (++fde >= p) { notifyAll(); }
		public synchronized void wait_d_and_e() { 
			try { if (fi < P) wait(); } catch(Exception e) { e.printStackTrace(); }
		}
		
		public synchronized void signal_a() { if (++fa >= p - 1) { notifyAll(); }
		public synchronized void wait_() { 
			try { if (fi < P - 1) wait(); } catch(Exception e) { e.printStackTrace(); }
		}		
	}
	
	private static class resource_monitor {
		private float d = 0.0, e = Float.MAX_VALUE;
		
		public synchronized void set_min_e(float _e) { if (_e < e) e = _e; }
		public synchronized void faa_d(float _d) { d += _d; }
		
		public synchronized float get_d() { return d; };
		public synchronized float get_e() { return e; };
	}
	
	private static class Minimum extends RecursiveTask<float> {
		private Math.Vector z;
		private int from;
		private int to;
		public Minimum(Math.Vector _z, int _from, int _to) { z = _z; from = _from; to = _to; }
		@Override
		protected float compute() {
			int offset = (to - from) / 2;
			if (offset == 0)
				return z.get(from);
			else if (offset == 1) {
				return z.get(from) < z.get(to) ? z.get(from) : z.get(to);
			} else {
				Minimum left_fork = new Minimum(from, from + offset);
				left.fork();
				Minimum right_fork = new Minimum(from + offset, to);
				float right = right_fork.compute(),
					left = left_fork.join();
				return left < right ? left : right;
			}
	}
	
	private static synchronization_monitor sync;
	private static resource_monitor res;	
	private static class Threads extends Thread {
		private Math m;
		private int id;
		public Threads(Math _m, int _id) { m = _m; id = _id; }
		@Override
		public void run() {
			System.out.println("Thread #" + String.valueOf(id) + " has been initialized"); 
			
			if (id == 0) { 
				b = Math.fill_vector(1);
				c = Math.fill_vector(1);
				mr = Math.fill_matrix(1);
				a = Math.fill_vector(0);
				synchronization_monitor.signal_input();
			} else if (id == 1) {
				t = Math.fill_vector(1);
				mk = Math.fill_matrix(1);
				synchronization_monitor.signal_input();
			} else if (id == p - 1) {
				mo = Math.fill_matrix(1);
				synchronization_monitor.signal_input();
			} else if (id == p) {
				s = Math.fill_vector(1);
				z = Math.fill_vector(1);
				synchronization_monitor.signal_input();
			}
			synchronization_monitor.wait_input();
			
			
			
			synchronization_monitor.signal_d_and_e();
			synchronization_monitor.wait_d_and_e();
			
			
			
			if (id != 0) 
				synchronization_monitor.signal_a();
			else {
				synchronization_monitor.wait_a();
				if (n < 10) Math.print_vector(a);
			}
			
			System.out.println("Thread #" + String.valueOf(id) + " has finished its execution"); 
		}
	}
	
	public static void main() {
		m = new Math();
		size = m.getN() / p;
		sync = new synchronization_monitor();
		res = new resource_monitor();
		Thread ts[p];
		for (int i = 0; i < p; i++)
			(ts[i] = new Threads(m, i)).start();
		for (int i = 0; i < p; i++)
			try { ts[i].join(); } catch (Exception e) { e.printStackTrace(); }
	}
	
}