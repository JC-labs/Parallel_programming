with ada.text_io, vector, matrix;

procedure l1 is	
	package integer_io is new ada.text_io.integer_io(natural);

	task t1 is
		entry input_mutex;
	end t1;
	task t2 is
		entry input_mutex;
	end t2;
	task t3 is 
		entry input_mutex;
	end t3;
	
	--procedure f1(n : in natural) is
	--	--package vecN is new vector(float, n);
	--	--use vecN;
	--	--package matN is new matrix(float, n);
	--	--use matN;
	--	
	--	--a : vector;
	--	--b : vector;
	--	--c : vector;
	--	--ma : matrix;
	--	--me : matrix;
	--begin
	--	ada.text_io.put("F1 was called with n = ");
	--	integer_io.put(n);
	--	ada.text_io.put_line("");
	--end f1;
	--procedure f2(n : in natural) is
	--	package vecN is new vector(n);
	--	use vecN;
	--	package matN is new matrix(float, n);
	--	use matN;
	--begin
	--	ada.text_io.put("F2 was called with n = ");
	--	integer_io.put(n);
	--	ada.text_io.put_line("");
	--end f2;
	--procedure f3(n : in natural) is
	--	package vecN is new vector(n);
	--	use vecN;
	--	package matN is new matrix(float, n);
	--	use matN;
	--begin
	--	ada.text_io.put("F3 was called with n = ");
	--	integer_io.put(n);
	--	ada.text_io.put_line("");
	end f3;
		
	task body t1 is 
		n : natural;
		package vecN is new vector(n);
		a : vecN.vector;
	begin 
		ada.text_io.put_line("First Task was initialized.");
		ada.text_io.put("Input N for the first function: ");
		n := natural'value(ada.text_io.get_line);
		a := vecN.get_vector(n);
		accept input_mutex do null; end input_mutex;
		t3.input_mutex;
		--f1(n);
		ada.text_io.put_line("First Task was processed.");
	end t1;
	
	task body t2 is 
		n : natural;
	begin 
		t1.input_mutex;
		ada.text_io.put_line("Second Task was initialized.");		
		ada.text_io.put("Input N for the second function: ");
		n := natural'value(ada.text_io.get_line);
		accept input_mutex do null; end input_mutex;
		t3.input_mutex;
		--f2(n);
		ada.text_io.put_line("Second Task was processed.");
	end t2;
	
	task body t3 is 
		n : natural;
	begin
		t2.input_mutex;
		ada.text_io.put_line("Third Task was initialized.");
		ada.text_io.put("Input N for the third function: ");
		n := natural'value(ada.text_io.get_line);
		accept input_mutex do null; end input_mutex;
		accept input_mutex do null; end input_mutex;
		--f3(n);
		ada.text_io.put_line("Third Task was processed.");
	end t3;

begin
	null;
end l1;