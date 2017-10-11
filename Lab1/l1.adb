--Parallel and alloted calculations.
--#1: Threads in Ada.
--with
--f1: c := sort(a) * (ma * me) + sort(b);
--f2: mg := transpose(mk) * (mh * mf);
--f3: o := sort(r + s) * (mt * mp);

--was implemented by
--Krisak Ivan Mylikayovich,
--a student of IO-53.

with ada.text_io, system.multiprocessors, math;
procedure l1 is	
	package integer_io is new ada.text_io.integer_io(positive);
	
	n1, n2, n3 : positive;
	procedure tasks is
		defalut_storage_size : positive := 50 * 1024 * 1024;
	
		task t1 is
			pragma task_name("task_1");
			--pragma cpu(1);
			pragma storage_size(defalut_storage_size);
			pragma priority(1);
		end t1;
		task t2 is			
			pragma task_name("task_2");
			--pragma cpu(2);
			pragma storage_size(defalut_storage_size);
			pragma priority(1);
		end t2;
		task t3 is			
			pragma task_name("task_3");
			--pragma cpu(3);
			pragma storage_size(defalut_storage_size);
			pragma priority(1);
		end t3;
		
		task body t1 is
			package mathematics is new math(n1); use mathematics;
			a : vector; 
			b : vector;
			c : vector;
			ma : matrix;
			me : matrix;
		begin 
			ada.text_io.put_line("First Task was initialized.");
			a := fill_vector;
			b := fill_vector;
			ma := fill_matrix;
			me := fill_matrix;

			delay 0.25;
			--c := sort(a) * (ma * me) + sort(b);
			c := f1(a, b, ma, me);
			delay 0.25;

			if n1 <= 10 then 
				ada.text_io.put("F1's ");
				put_vector(c);
			end if;
			ada.text_io.put_line("First Task was processed.");
		end t1;
		task body t2 is 
			package mathematics is new math(n2); use mathematics;
			mk : matrix;
			mh : matrix;
			mf : matrix;
			mg : matrix;
		begin 
			ada.text_io.put_line("Second Task was initialized.");
			mk := fill_matrix;
			mh := fill_matrix;
			mf := fill_matrix;

			delay 0.25;
			--mg := transpose(mk) * (mh * mf);
			mg := f2(mk, mh, mf);
			delay 0.25;

			if n1 <= 10 then 
				ada.text_io.put("F2's ");
				put_matrix(mg);
			end if;
			ada.text_io.put_line("Second Task was processed.");
		end t2;
		task body t3 is 
			package mathematics is new math(n3); use mathematics;
			r : vector; 
			s : vector;
			o : vector;
			mt : matrix;
			mp : matrix;
		begin
			ada.text_io.put_line("Third Task was initialized.");
			r := fill_vector;
			s := fill_vector;
			mt := fill_matrix;
			mp := fill_matrix;

			delay 0.25;
			--o := sort(r + s) * (mt * mp);
			o := f3(r, s, mt, mp);
			delay 0.25;

			if n1 <= 10 then 
				ada.text_io.put("F3's ");
				put_vector(o);
			end if;
			ada.text_io.put_line("Third Task was processed.");
		end t3;	
	begin
		null;
	end tasks;

begin
	ada.text_io.put("Input N for the first function: ");
	n1 := positive'value(ada.text_io.get_line);
	ada.text_io.put("Input N for the second function: ");
	n2 := positive'value(ada.text_io.get_line);
	ada.text_io.put("Input N for the third function: ");
	n3 := positive'value(ada.text_io.get_line);
	tasks;
end l1;
