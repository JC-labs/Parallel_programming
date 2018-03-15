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
            sem1, sem2, sem3, sem4, sem5 : ada.synchronous_task_control.suspension_object;
            sem6, sem7 : ada.synchronous_task_control.suspension_object;

	        package mathematics is new math(n); use mathematics;
            b, c : vector;
            mo, mt, mr : matrix;
            d : float;

            e : float;
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
                e_i, temp : float;
                d_1, e_1 : float;
                mr_1 : matrix;
            begin
                ada.text_io.put_line("First Processor was initialized.");
                b := fill_vector;
                c := fill_vector;
                mo := fill_matrix;
                mt := fill_matrix;
                mr := fill_matrix;
                d := get_scalar;
                e := 0.0;
                clear_matrix(ma);
                ada.synchronous_task_control.set_true(sem6);
                ada.synchronous_task_control.set_true(sem7);
                ada.text_io.put_line("Data input was successful.");
                ada.synchronous_task_control.set_true(sem1);

                e_i := 0.0;
                for i in 1..n/2 loop
                    e_i := e_i + get(i, b) * get(i, c);
                end loop;
                ada.synchronous_task_control.suspend_until_true(sem6);
                e := e + e_i;
                ada.synchronous_task_control.set_true(sem6);

                ada.synchronous_task_control.set_true(sem2);
                ada.synchronous_task_control.suspend_until_true(sem3);

                ada.synchronous_task_control.suspend_until_true(sem7);
                mr_1 := mr;
                d_1 := d;
                e_1 := e;
                ada.synchronous_task_control.set_true(sem7);

                for i in 1..n/2 loop
                    for j in 1..n loop 
                        temp := 0.0;
			    	    for k in 1..n loop
                            temp := temp + get(i, k, mt) * get(k, j, mr_1);
                        end loop;
                        set(i, j, temp * d_1 + get(i, j, mo) * e_1, ma);
                    end loop;
                end loop;

                ada.synchronous_task_control.set_true(sem5);
                ada.synchronous_task_control.suspend_until_true(sem4);

                if n < 10 then
                    ada.text_io.put_line("Result of the calculations:");
                    put_matrix(ma);
                end if;
                ada.text_io.put_line("First Processor has finished processing.");
            end p0;

            task body p1 is
                e_i, temp : float;
                d_1, e_1 : float;
                mr_1 : matrix;
            begin
                ada.synchronous_task_control.suspend_until_true(sem1);
                ada.text_io.put_line("Second Processor is ready.");

                e_i := 0.0;
                for i in n/2+1..n loop
                    e_i := e_i + get(i, b) * get(i, c);
                end loop;
                ada.synchronous_task_control.suspend_until_true(sem6);
                e := e + e_i;
                ada.synchronous_task_control.set_true(sem6);

                ada.synchronous_task_control.set_true(sem3);
                ada.synchronous_task_control.suspend_until_true(sem2);

                ada.synchronous_task_control.suspend_until_true(sem7);
                mr_1 := mr;
                d_1 := d;
                e_1 := e;
                ada.synchronous_task_control.set_true(sem7);

                for i in n/2+1..n loop
                    for j in 1..n loop
                        temp := 0.0;
				        for k in 1..n loop
                            temp := temp + get(i, k, mt) * get(k, j, mr_1);
                        end loop;
                        set(i, j, temp * d_1 + get(i, j, mo) * e_1, ma);
                    end loop;
                end loop;

                ada.synchronous_task_control.set_true(sem4);
                ada.synchronous_task_control.suspend_until_true(sem5);

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