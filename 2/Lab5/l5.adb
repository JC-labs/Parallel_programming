-- Parallel and alloted calculations. Part 2
-- Lab #5 Protected modules in Ada
-- with A = (B * C) * (T * MO) + min(Z) * S * (MT * MR);

-- was implemented by
-- Krisak Ivan Mykolayovich,
-- a student of IO-53

with ada.text_io, ada.synchronous_task_control, math;
procedure l5 is
	package integer_io is new ada.text_io.integer_io(positive);
	n : positive;
    p : positive;
    size : integer;
	procedure main is
		default_storage_size : positive := 1000 * 1024 * 1024;
		task crutch is
			pragma storage_size(default_storage_size);
		end crutch;
		task body crutch is
			package mathematics is new math(n); use mathematics;
			b, c, t, s, z : vector;
			mo, mk, mr : matrix;
			a : vector;

            protected synchronization_monitor is
                entry wait_input;
                entry wait_d_and_e;
                entry wait_a;
                procedure signal_input;
                procedure signal_d_and_e;
                procedure signal_a;
            private
                fi : integer := 0;
                fde : integer := 0;
                fa : integer := 0;
            end synchronization_monitor;
            protected body synchronization_monitor is
                entry wait_input when fi = 4 is begin null; end;
                entry wait_d_and_e when fde = p is begin null; end;
                entry wait_a when fa = p - 1 is begin null; end;
                procedure signal_input is begin fi := fi + 1; end;
                procedure signal_d_and_e is begin fde := fde + 1; end;
                procedure signal_a is begin fa := fa + 1; end;
            end synchronization_monitor;

            protected resource_monitor is
                procedure set_min_e(e_i : float);
                procedure faa_d(d_i : float);
                function get_d return float;
                function get_e return float;
            private
                d : float := 0.0;
                e : float := float'large;
            end;
            protected body resource_monitor is
                procedure set_min_e(e_i : float) is begin if e_i < e then e := e_i; end if; end;
                procedure faa_d(d_i : float) is begin d := d + d_i; end;
                function get_d return float is begin return d; end;
                function get_e return float is begin return e; end;
            end resource_monitor;
			
			procedure task_start is 
                task type task_type (id : Integer);
                type task_pointer is access task_type;
				type task_array is array (Integer range <>) of task_pointer;
                task body task_type is
                    d, e, temp : float;
                    fin : positive;
                    v : vector;
                begin
                    if id = p then fin := n; else fin := size * id; end if;

					ada.text_io.put("Task #");
                    integer_io.put(id, width => 0);
                    ada.text_io.put_line(" was initialized.");

                    if id = 1 then
                        b := fill_vector;
                        c := fill_vector;
                        mr := fill_matrix;
                        clear_vector(a);
                        synchronization_monitor.signal_input;
                    elsif id = 2 then
                        t := fill_vector;
                        mk := fill_matrix;
                        synchronization_monitor.signal_input;
                    elsif id = 3 then
                        mo := fill_matrix;
                        synchronization_monitor.signal_input;
                    elsif id = 4 then
                        z := fill_vector;
                        s := fill_vector;
                        synchronization_monitor.signal_input;
                    end if;
                    synchronization_monitor.wait_input;

                    temp := 0.0;
                    if fin /= 0 then
                        for i in size * (id - 1) + 1 .. fin loop
                            temp := temp + get(i, b) * get(i, c);
                        end loop;
                    end if;
                    resource_monitor.faa_d(temp);

                    temp := float'large;
                    if fin /= 0 then
                        for i in size * (id - 1) + 1.. fin loop
                            if get(i, z) < temp then temp := get(i, z); end if;
                        end loop;
                    end if;
                    resource_monitor.set_min_e(temp);

                    synchronization_monitor.signal_d_and_e;
                    synchronization_monitor.wait_d_and_e;

                    d := resource_monitor.get_d;
                    e := resource_monitor.get_e;
                    clear_vector(v);
                    if fin /= 0 then
                        for i in size * (id - 1) + 1 .. fin loop
                            for j in 1..n loop
                                temp := 0.0;
                                for k in 1..n loop
                                    temp := temp + get(i, k, mk) * get(k, j, mr);
                                end loop;
                                set(i, get(i, a) + temp * get(i, s), a);
                                set(i, get(i, v) + get(i, j, mo) * get(i, t), v);
                            end loop;
                            set(i, get(i, a) * e + get(i, v) * d, a);
                        end loop;
                    end if;

                    if id /= 1 then
                        synchronization_monitor.signal_a;
                    else
                        synchronization_monitor.wait_a;
                        if n < 10 then
                            ada.text_io.put_line("Result of the calculations:");
                            put_vector(a);
                        end if;
                    end if;

					ada.text_io.put("Task #");
                    integer_io.put(id, width => 0);
                    ada.text_io.put_line(" was finished.");
                end task_type;
			begin
				declare
					tasks : task_array(1..p);
                begin
                    for i in tasks'Range loop
                        tasks(i) := new task_type(id => i);
                    end loop;
                end;
			end task_start;
        begin
            task_start;
        end crutch;
    begin
        null;
    end main;
begin
    ada.text_io.put("Input N:");
	n := positive'value(ada.text_io.get_line);
    p := 4;
    size := n / p;
    main;
end l5;
