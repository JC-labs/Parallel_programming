with ada.text_io, math;

procedure l1 is	
	package integer_io is new ada.text_io.integer_io(positive);
	
	n1, n2, n3 : positive;
	procedure tasks is
		task t1 is
			entry input_mutex;
			entry output_mutex;
		end t1;
		task t2 is
			entry input_mutex;
			entry output_mutex;
		end t2;
		task t3 is
			entry input_mutex;
			entry output_mutex;
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
			a := get_vector;
			b := get_vector;
			ma := get_matrix;
			me := get_matrix;
			accept input_mutex do null; end input_mutex;
			c := sort(a) * (ma * me) + sort(b);
			t3.input_mutex;
			ada.text_io.put("F1's ");
			put_vector(c);
			accept output_mutex do null; end output_mutex;
			t3.output_mutex;
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
			t1.input_mutex;
			mk := get_matrix;
			mh := get_matrix;
			mf := get_matrix;
			accept input_mutex do null; end input_mutex;
			mg := transpose(mk) * (mh * mf);
			t3.input_mutex;
			t1.output_mutex;
			ada.text_io.put("F2's ");
			put_matrix(mg);
			accept output_mutex do null; end output_mutex;
			t3.output_mutex;
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
			t2.input_mutex;
			r := get_vector;
			s := get_vector;
			mt := get_matrix;
			mp := get_matrix;
			accept input_mutex do null; end input_mutex;
			accept input_mutex do null; end input_mutex;
			o := sort(r + s) * (mt * mp);
			t2.output_mutex;
			ada.text_io.put("F3's ");
			put_vector(o);
			accept output_mutex do null; end output_mutex;
			accept output_mutex do null; end output_mutex;
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