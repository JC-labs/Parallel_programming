with ada.text_io;
package body math is 
	package integer_io is new ada.text_io.integer_io(positive);
	package float_io is new ada.text_io.float_io(float);
	function get_vector return vector is
		ret : vector;
	begin
		ada.text_io.put("Input ");
		integer_io.put(size);
		ada.text_io.put_line(" floats for the a vector:");
		for i in 1..size loop
			ret(i) := float'value(ada.text_io.get_line);
		end loop;
		return ret;
	end;	
	function get_matrix return matrix is
		ret : matrix;
	begin
		ada.text_io.put("Input ");
		integer_io.put(size);
		ada.text_io.put("x");
		integer_io.put(size);
		ada.text_io.put_line(" floats for the a matrix:");
		for i in 1..size loop
			for j in 1..size loop
				ret(i, j) := float'value(ada.text_io.get_line);
			end loop;
		end loop;
		return ret;
	end;
	
	function sort(v : in vector) return vector is
		t : float;
		r : vector;
	begin
		r := v;
		for i in 1..size loop
			for j in i..size loop
				if r(i) > r(j) then
					t := r(j);
					r(j) := r(i);
					r(i) := t;
				end if;
			end loop;
		end loop;
		return r;
	end sort;
	
	function "*"(m1, m2 : in matrix) return matrix is
		ret : matrix;
	begin
		for i in 1..size loop
			for j in 1..size loop
				ret(i, j) := 0.0;
				for k in 1..size loop
					ret(i, j) := ret(i, j) + m1(i, k) * m2(k, j);
				end loop;
			end loop;
		end loop;
		return ret;
	end "*";
	function "*"(v : in vector; m : in matrix) return vector is
	ret : vector;
	begin
		for i in 1..size loop
			ret(i) := 0.0;
			for j in 1..size loop
				ret(i) := ret(i) + m(i, j) * v(i);
			end loop;
		end loop;
		return ret;
	end "*";
	function "+"(v1, v2 : in vector) return vector is
		ret : vector;
	begin
		for i in 1..size loop
			ret(i) := v1(i) + v2(i);
		end loop;
		return ret;
	end "+";
		
	procedure put_vector(v : in vector) is
	begin
		ada.text_io.put_line("Resulting vector is ");
		for i in 1..size loop
			float_io.put(v(i));
		end loop;
		ada.text_io.put_line("");
	end put_vector;
	
	function transpose(m : in matrix) return matrix is
		ret : matrix;
	begin
		for i in 1..size loop
			for j in i..size loop
				ret(i, j) := m(j, i);
				ret(j, i) := m(i, j);
			end loop;
		end loop;
		return ret;
	end transpose;
	
	procedure put_matrix(m : in matrix) is
	begin
		ada.text_io.put_line("Resulting matrix is ");
		for i in 1..size loop
			for j in 1..size loop
				float_io.put(m(i, j));
			end loop;
			ada.text_io.put_line("");
		end loop;
	end put_matrix;
	
end math;