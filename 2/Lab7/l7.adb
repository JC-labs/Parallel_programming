-- Parallel and alloted calculations. Part 2
-- Lab #7 Local Memory System in Ada
-- with A = (B * C) * D + e * T * (MO * MS);

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
			b, c, d, t : vector;
			mo, ms : matrix;
            e : float;

			a : vector;
			
			procedure task_start is 
                task type task_type (id : Integer, ids : Integer);
                type task_pointer is access task_type;
				type task_array is array (Integer range <>) of task_pointer;
                task body task_type is
                begin
					ada.text_io.put("Task #");
                    integer_io.put(id, width => 0);
                    ada.text_io.put_line(" was initialized.");

                    if id = 1 then
                        b := fill_vector;
                        e := get_scalar;
                        ms := fill_matrix;
                        clear_vector(a);
                    elsif id = ids then
                        c := fill_vector;
                        d := fill_vector;
                        t := fill_vector;
                        mo := fill_matrix;
                    end if;


                    


                    if id = 1 then
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
                        tasks(i) := new task_type(id => i, p);
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
    p := 16;
    size := n / p;
    main;
end l5;
