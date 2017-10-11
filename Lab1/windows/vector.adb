with ada.text_io;
package body vector is 
	package integer_io is new ada.text_io.integer_io(positive);
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
	
	function sort(v: in vector) return vector is
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
	
end vector;