-- Parallel and alloted calculations. Part 2
-- Lab #7 Local Memory System in Ada
-- with A = (B * C) * D + e * T * (MO * MS);

-- was implemented by
-- Krisak Ivan Mykolayovich,
-- a student of IO-53

with ada.text_io, ada.containers.doubly_linked_lists, math;
procedure l7 is
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

            type sync is record
                this_id, with_id, size : integer;
                dir : boolean;
            end record;
            
            generic
                type element_Type is private;
            package fifo is
                type fifo_type is tagged private;
                procedure push(the_fifo : in out fifo_type; item : in element_type);
                procedure pop(the_fifo : in out fifo_type; item : out element_type);
                function not_empty(the_fifo : in out fifo_type) return boolean;
                empty_Error : exception;
            private
                package list_pkg is new ada.containers.doubly_linked_lists(element_type); use list_pkg;
                type fifo_type is new list with null record;
            end fifo;
            package body fifo is
                procedure push(the_fifo : in out fifo_type; item : in element_type) is
                begin the_fifo.prepend(item); end Push;
                procedure pop(the_fifo : in out fifo_type; item : out element_type) is
                begin 
                    if is_empty(the_fifo) then raise empty_error; end if;
                    item := the_fifo.first_element;
                    the_fifo.delete_first;
                end pop;
                function not_empty(the_fifo : in out fifo_type) return boolean is
                begin 
                    return not is_empty(the_fifo);
                end not_empty;
            end fifo;
            package queue is new fifo(sync); use queue;

            protected stdout is procedure print(t : in sync); end stdout;
            protected body stdout is procedure print(t : in sync) is begin
                ada.text_io.put("Task #"); 
                integer_io.put(t.this_id, width => 0);
                ada.text_io.put(" is to ");
                if (t.dir) then ada.text_io.put("send "); else ada.text_io.put("receive "); end if;
                integer_io.put(t.size, width => 0);
                ada.text_io.put(" elements ");
                if (t.dir) then ada.text_io.put("to "); else ada.text_io.put("from "); end if;
                ada.text_io.put("task #"); 
                integer_io.put(t.with_id, width => 0);
                ada.text_io.put_line("");
            end print; end stdout;
            
            procedure determine_action(id, s_id, e_id, size : in integer; q : in out fifo_type, inv : in boolean) is
                t_id : integer;
                temp : sync;
            begin
                if (id >= s_id) and (id <= e_id) then
                    temp.this_id := id;
                    temp.with_id := id - 1;
                    temp.size := size / 2;
                    temp.dir := false;
                    if (e_id - s_id < 4) and (e_id - s_id > 2) then
                        if (id = s_id) then
                            temp.with_id := id + 1;
                            temp.size := size * (e_id - id - 0) / (e_id - s_id + 1);
                            temp.dir := true;
                            q.push(temp);
                        elsif (id = e_id) then
                            temp.size := size * (e_id - id + 1) / (e_id - s_id + 1);
                            q.push(temp);
                        else
                            temp.size := size * (e_id - id + 1) / (e_id - s_id + 1);
                            q.push(temp);
                            temp.with_id := id + 1;
                            temp.size := size * (e_id - id - 0) / (e_id - s_id + 1);
                            temp.dir := true;
                            q.push(temp);
                        end if;
                    else
                        t_id := (e_id + s_id) / 2;
                        if (id = s_id) then
                            temp.with_id := t_id + 1;
                            temp.dir := true;
                            q.push(temp);
                        elsif id = t_id + 1 then
                            temp.with_id := s_id;
                            q.push(temp);
                        end if;
                        determine_action(id, s_id, t_id, size / 2, q);
                        determine_action(id, t_id + 1, e_id, size / 2, q);
                    end if;
                end if;
            end determine_action;
			
			procedure task_start is 
                task type task_type (id, ids : integer) is 
                    entry vector_sync(v : in vector);
                end task_type;
                type task_pointer is access task_type;
				task_array : array (1..p) of task_pointer;
                task body task_type is
                    q : fifo_type;
                    t : sync;
                begin
					--ada.text_io.put("Task #");
                    --integer_io.put(id, width => 0);
                    --ada.text_io.put_line(" was initialized.");

                    if id = 1 then
                        --b := fill_vector;
                        --e := get_scalar;
                        --ms := fill_matrix;
                        clear_vector(a);
                        for i in 1..n loop 
                            set(i, float(i), a);
                        end loop;
                    elsif id = ids then
                        --c := fill_vector;
                        --d := fill_vector;
                        --t := fill_vector;
                        --mo := fill_matrix;
                        null;
                    end if;

                    determine_action(id, 1, p, n, q);
                    while q.not_empty loop
                        q.pop(t);
                        if (t.dir) then
                            stdout.print(t);
                            task_array(t.with_id).vector_sync(a);
                        else
                            stdout.print(t);
                            accept vector_sync(v : in vector) do
                                a := v;
                            end vector_sync;
                        end if;
                    end loop;

                    if id = 16 then
                        --if n < 10 then
                            --ada.text_io.put_line("Result of the calculations:");
                            put_vector(a);
                        --end if;
                    end if;

					--ada.text_io.put("Task #");
                    --integer_io.put(id, width => 0);
                    --ada.text_io.put_line(" was finished.");
                end task_type;
			begin
                begin
                    for i in 1..p loop
                        task_array(i) := new task_type(id => i, ids => p);
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
    --p := 128;
    size := n / p;
    main;
end l7;
