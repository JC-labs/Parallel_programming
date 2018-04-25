-- Parallel and alloted calculations. Part 2
-- #1 Semaphores in Ada
-- with MA = (B * C) * MO + d * MT * MR;

-- was implemented by
-- Krisak Ivan Mykolayovich,
-- a student of IO-53

with ada.text_io, ada.synchronous_task_control, math;
procedure l5 is
	package integer_io is new ada.text_io.integer_io(positive);
	n : positive;
    p : positive;
	procedure main is
		default_storage_size : positive := 1000 * 1024 * 1024;
		task crutch is
			pragma storage_size(default_storage_size);
		end crutch;
		task body crutch is			
			package mathematics is new math(n); use mathematics;
			b, c, t : vector;
			mo, mk, mr : matrix;
			ma : matrix;
			
			d, e : float;
			
			procedure task_start is 
                task type task_type (id : Integer);
                type task_pointer is access task_type;
				type task_array is array (Integer range <>) of task_pointer;
                task body task_type is
                begin
					ada.text_io.put("Task #");
                    integer_io.put(id, width => 0);
                    ada.text_io.put_line(" was initialized.");

                    
                    
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
    main;
end l5;
