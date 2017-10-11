with ada.text_io;
package body matrix is 
	package integer_io is new ada.text_io.integer_io(positive);
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
	function "*"(m1, m2: in matrix) return matrix is
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
	function "*"(v: in vector; m: in matrix) return vector is
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
end matrix;