-- Parallel and alloted calculations. Part 2
-- #1 Semaphores in Ada
-- with MA = (B * C) * MO + d * MT * MR;

-- was implemented by
-- Krisak Ivan Mykolayovich,
-- a student of IO-53

with ada.text_io, ada.synchronous_task_control, math;
procedure l1 is
    package integer_io is new ada.text_io.integer_io(positive);
    n : positive;
    procedure main is
        default_storage_size : positive := 1000 * 1024 * 1024;
        task crutch is
            pragma task_name("processor_0");
            pragma storage_size(default_storage_size);
        end crutch;

        task body crutch is
            input, dot_t1, dot_t2, res_t1, res_t2 : ada.synchronous_task_control.suspension_object;

	        package mathematics is new math(n); use mathematics;
            b, c : vector;
            mo, mt, mr : matrix;
            d : float;

            bc : float;
            ma : matrix;

        procedure processors is

            task p0 is
                pragma task_name("processor_0");
                --pragma cpu(1);
                pragma storage_size(default_storage_size);
            end p0;
            task p1 is
                pragma task_name("processor_1");
                --pragma cpu(4);
                pragma storage_size(default_storage_size);
            end p1;

            task body p0 is
                --bc_temp : float;
                temp : float;
            begin
                ada.text_io.put_line("First Processor was initialized.");
                b := fill_vector;
                c := fill_vector;
                mo := fill_matrix;
                mt := fill_matrix;
                mr := fill_matrix;
                d := get_scalar;
                bc := 0.0;
                clear_matrix(ma);
                ada.text_io.put_line("Data input was successful.");
                ada.synchronous_task_control.set_true(input);

                --bc_temp := 0.0;
                for i in 1..n/2 loop
                    --bc_temp := bc_temp + get(i, b) * get(i, c);
                    bc := bc + get(i, b) * get(i, c);
                end loop;
                --bc := bc + bc_temp;

                ada.synchronous_task_control.set_true(dot_t1);
                ada.synchronous_task_control.suspend_until_true(dot_t2);

                for i in 1..n/2 loop
                    for j in 1..n loop 
                        temp := 0.0;
			    	    for k in 1..n loop
                            temp := temp + get(i, k, mt) * get(k, j, mr);
                        end loop;
                        set(i, j, temp * d + get(i, j, mo) * bc, ma);
                    end loop;
                end loop;

                ada.synchronous_task_control.set_true(res_t1);
                ada.synchronous_task_control.suspend_until_true(res_t2);

                if n < 10 then
                    ada.text_io.put_line("Result of the calculations:");
                    put_matrix(ma);
                end if;
                ada.text_io.put_line("First Processor has finished processing.");
            end p0;

            task body p1 is
                --bc_temp : float;
                temp : float;
            begin
                ada.synchronous_task_control.suspend_until_true(input);
                ada.text_io.put_line("Second Processor is ready.");

                --bc_temp := 0.0;
                for i in n/2+1..n loop
                    --bc_temp := bc_temp + get(i, b) * get(i, c);
                    bc := bc + get(i, b) * get(i, c);
                end loop;
                --bc := bc + bc_temp;

                ada.synchronous_task_control.set_true(dot_t2);
                ada.synchronous_task_control.suspend_until_true(dot_t1);

                for i in n/2+1..n loop
                    for j in 1..n loop
                        temp := 0.0;
				        for k in 1..n loop
                            temp := temp + get(i, k, mt) * get(k, j, mr);
                        end loop;
                        set(i, j, temp * d + get(i, j, mo) * bc, ma);
                    end loop;
                end loop;                

                ada.synchronous_task_control.set_true(res_t2);
                ada.synchronous_task_control.suspend_until_true(res_t1);

                ada.text_io.put_line("Second Processor has finished processing.");
            end p1;
        begin
            null;
        end processors;
        begin
            processors;
        end crutch;
    begin
        null;
    end main;
begin
    ada.text_io.put("Input N:");
	n := positive'value(ada.text_io.get_line);
    main;
end l1;