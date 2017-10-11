with ada.text_io;
with ada.containers.vectors;

procedure l1 is
	task f1;
	task f2;
	task f3;
	
	n : constant natural := 3;
	
	package vector is new ada.containers.vectors(natural, float);
	use vector;	
	package integer_io is new ada.text_io.integer_io(natural);
	
	type name is new vector.vector;
		
	task body f1 is 
		a : vector.vector;
		b : name;
		i : natural;
		entry insert(m : in natural);
		entry remove(m : out natural);
	begin 
		ada.text_io.put_line("Task #1 was initialized.");
		
		ada.text_io.put("Input ");
		integer_io.put(n);
		ada.text_io.put_line(" floats for a vector:");
		i := 1;
		while i <= n loop
			append(a, float'value(ada.text_io.get_line));
			i := i + 1;
		end loop;
		
		ada.text_io.put_line("Task #1 was finished.");
	end f1;
	
	task body f2 is 
	begin 
		ada.text_io.put_line("Task #2 was initialized.");
		ada.text_io.put_line("Task #2 was finished.");
	end f2;
	
	task body f3 is 
	begin 
		ada.text_io.put_line("Task #3 was initialized.");
		ada.text_io.put_line("Task #3 was finished.");
	end f3;

begin
	null;
end l1;