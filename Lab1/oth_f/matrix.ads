with vector;
generic
	size : positive;
package matrix is
	type matrix is private;
	function get_matrix return matrix;
	function "*"(m1, m2: in matrix) return matrix;
	function "*"(v: in vector; m: in matrix) return vector;
private
	type matrix is array(1..size, 1..size) of float;
end matrix;