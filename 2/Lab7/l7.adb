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
                    item := the_fifo.last_element;
                    the_fifo.delete_last;
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
            
            function inv(d : in boolean; id : in integer) return integer is
            begin if not d then return p - id + 1; else return id; end if; end inv;
            function inc(d : in boolean) return integer is
            begin if d then return +1; else return -1; end if; end inc;
            procedure determine_action(id, s_id, e_id, size : in integer; q : in out fifo_type; d : in boolean; c : in boolean) is
                t_id : integer;
                temp : sync;
            begin
                if (inv(d, id) >= s_id) and (inv(d, id) <= e_id) then
                    temp.this_id := id;
                    if (e_id - s_id < 4) and (e_id - s_id > 2) then
                        if (inv(d, id) = s_id) then
                            temp.with_id := id + inc(d);
                            temp.size := size * (e_id - inv(d, id) - 0) / (e_id - s_id + 1);
                            temp.dir := true;
                            q.push(temp);
                        elsif (inv(d, id) = e_id) then
                            temp.with_id := id - inc(d);
                            temp.size := size * (e_id - inv(d, id) + 1) / (e_id - s_id + 1);
                            temp.dir := false;
                            q.push(temp);
                        else
                            temp.with_id := id + inc(d);
                            temp.size := size * (e_id - inv(d, id) - 0) / (e_id - s_id + 1);
                            temp.dir := true;
                            q.push(temp);
                            temp.with_id := id - inc(d);
                            temp.size := size * (e_id - inv(d, id) + 1) / (e_id - s_id + 1);
                            temp.dir := false;
                            q.push(temp);
                        end if;
                    else
                        t_id := (e_id + s_id) / 2;
                        if (inv(d, id) = s_id) then
                            temp.with_id := t_id + inc(d);
                            temp.size := size / 2;
                            temp.dir := true;
                            q.push(temp);
                        elsif inv(d, id) = t_id + inc(d) then
                            temp.with_id := s_id;
                            temp.size := size / 2;
                            temp.dir := false;
                            q.push(temp);
                        end if;
                        determine_action(id, s_id, t_id, size / 2, q, d, c);
                        determine_action(id, t_id + 1, e_id, size / 2, q, d, c);
                    end if;
                end if;
            end determine_action;
			
			procedure task_start is 
                task type task_type (id : integer) is
                    entry number_sync(v : in float);
                    entry vector_sync(v : in vector);
                    entry data_r_to_l_sync(v0 : in float; v1, v2 : in vector; v3 : in matrix);
                    entry data_l_to_r_sync(v0 : in float; v1 : in matrix);
                end task_type;
                type task_pointer is access task_type;
				task_array : array (1..p) of task_pointer;
                task body task_type is
			        a : vector;
                    b, c, d, t : vector;
                    mo, ms : matrix;
                    e : float;
                    f : float;

                    fin : positive;
                    q : fifo_type;
                    tmp : sync;
                    temp : float;
                begin
                    if id = p then fin := n; else fin := size * id; end if;
					ada.text_io.put("Task #");
                    integer_io.put(id, width => 0);
                    ada.text_io.put_line(" was initialized.");

                    clear_vector(a);
                    if id = 1 then
                        b := fill_vector(1.0);
                        e := 1.0;
                        ms := fill_matrix(1.0);
                        for i in 1..n loop 
                            set(i, float(i), a);
                        end loop;
                    elsif id = p then
                        c := fill_vector(1.0);
                        d := fill_vector(1.0);
                        t := fill_vector(1.0);
                        mo := fill_matrix(1.0);
                        null;
                    end if;

                    determine_action(id, 1, p, n, q, true, false);
                    while q.not_empty loop
                        q.pop(tmp);
                        if (tmp.dir) then
                            stdout.print(tmp);
                            task_array(tmp.with_id).vector_sync(b);
                        else
                            stdout.print(tmp);
                            accept vector_sync(v : in vector) do
                                b := v;
                            end vector_sync;
                        end if;
                    end loop;
                    determine_action(id, 1, p, n, q, false, false);
                    while q.not_empty loop
                        q.pop(tmp);
                        if (tmp.dir) then
                            stdout.print(tmp);
                            task_array(tmp.with_id).vector_sync(c);
                        else
                            stdout.print(tmp);
                            accept vector_sync(v : in vector) do
                                c := v;
                            end vector_sync;
                        end if;
                    end loop;
                    f := 0.0;
                    if fin /= 0 then
                        for i in size * (id - 1) + 1 .. fin loop
                            f := f + get(i, b) * get(i, c);
                        end loop;
                    end if;
                    
                    determine_action(id, 1, p, n, q, true, true);
                    while q.not_empty loop
                        q.pop(tmp);
                        if (tmp.dir) then
                            stdout.print(tmp);
                            task_array(tmp.with_id).number_sync(f);
                        else
                            stdout.print(tmp);
                            accept number_sync(v : in float) do
                                f := f + v;
                            end number_sync;
                        end if;
                    end loop;
                    
                    determine_action(id, 1, p, n, q, true, false);
                    while q.not_empty loop
                        q.pop(tmp);
                        if (tmp.dir) then
                            stdout.print(tmp);
                            task_array(tmp.with_id).data_l_to_r_sync(e, ms);
                        else
                            stdout.print(tmp);
                            accept data_l_to_r_sync(v0 : in float; v1 : in matrix) do
                                e := v0;
                                ms := v1;
                            end data_l_to_r_sync;
                        end if;
                    end loop;
                    determine_action(id, 1, p, n, q, false, false);
                    while q.not_empty loop
                        q.pop(tmp);
                        if (tmp.dir) then
                            stdout.print(tmp);
                            task_array(tmp.with_id).data_r_to_l_sync(f, d, t, mo);
                        else
                            stdout.print(tmp);
                            accept data_r_to_l_sync(v0 : in float; v1, v2 : in vector; v3 : in matrix) do
                                f := v0;
                                d := v1;
                                t := v2;
                                mo := v3;
                            end data_r_to_l_sync;
                        end if;
                    end loop;
                    
                    if fin /= 0 then
                        for i in size * (id - 1) + 1 .. fin loop
                            for j in 1..n loop
                                temp := 0.0;
                                for k in 1..n loop
                                    temp := temp + get(i, k, mo) * get(k, j, ms);
                                end loop;
                                set(i, get(i, a) + temp * get(i, t), a);
                            end loop;
                            set(i, get(i, d) * f + get(i, a) * e, a);
                        end loop;
                    end if;
                    determine_action(id, 1, p, n, q, false, true);
                    while q.not_empty loop
                        q.pop(tmp);
                        if (tmp.dir) then
                            stdout.print(tmp);
                            task_array(tmp.with_id).vector_sync(a);
                        else
                            stdout.print(tmp);
                            accept vector_sync(v : in vector) do
                                a := v;
                            end vector_sync;
                        end if;
                    end loop;

                    if id = 16 then
                        if n < 10 then
                            ada.text_io.put_line("Result of the calculations:");
                            put_vector(a);
                        end if;
                        null;
                    end if;

					ada.text_io.put("Task #");
                    integer_io.put(id, width => 0);
                    ada.text_io.put_line(" was finished.");
                end task_type;
			begin
                begin
                    for i in 1..p loop
                        task_array(i) := new task_type(id => i);
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
