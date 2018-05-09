with ada.text_io;
package body math is 
	package integer_io is new ada.text_io.integer_io(positive);
	package float_io is new ada.text_io.float_io(float);
	function get_scalar return float is
	begin
		ada.text_io.put("Input a scalar: ");
		return float'value(ada.text_io.get_line);
	end;
	function get_vector return vector is
		ret : vector;
	begin
		ada.text_io.put("Input ");
		integer_io.put(size);
		ada.text_io.put(" floats for the a vector:");
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
		ada.text_io.put_line(" floats for the matrix:");
		for i in 1..size loop
			for j in 1..size loop
				ret(i, j) := float'value(ada.text_io.get_line);
			end loop;
		end loop;
		return ret;
	end;	
	function fill_matrix(v : in float) return matrix is
		ret : matrix;
	begin
		for i in 1..size loop
			for j in 1..size loop
				ret(i, j) := v;
			end loop;
		end loop;
		return ret;
	end;
	function fill_vector(v : in float) return vector is
		ret : vector;
	begin
		for i in 1..size loop
			ret(i) := v;
		end loop;
		return ret;
	end;

	procedure put_vector(v : in vector) is
	begin
		ada.text_io.put_line("Resulting vector is ");
		for i in 1..size loop
			float_io.put(v(i));
		end loop;
		ada.text_io.put_line("");
	end put_vector;
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
	procedure put_scalar(f : in float) is
	begin
		float_io.put(f);
	end put_scalar;

	procedure clear_matrix(m : out matrix) is
	begin
		for i in 1..size loop
			for j in 1..size loop
				m(i, j) := 0.0;
			end loop;
		end loop;
	end clear_matrix;
	procedure clear_vector(v : out vector) is
	begin
		for i in 1..size loop
			v(i) := 0.0;
		end loop;
	end clear_vector;

	function get(i : in positive; v : in vector) return float is
	begin
		return v(i);
	end get;
	function get(i, j : in positive; m : in matrix) return float is 
	begin
		return m(i,j);
	end get;
	procedure set(i : in positive; f : float; v : out vector) is
	begin
		v(i) := f;
	end set;
	procedure set(i, j : in positive; f : float; m : out matrix) is
	begin
		m(i, j) := f;
	end set;
	procedure append(i, j : in positive; f : float; m : out matrix) is
	begin
		m(i, j) := m(i, j) + f;
	end append;
end math;