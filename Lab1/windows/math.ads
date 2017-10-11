with ada.containers.generic_array_sort;
generic
	size : positive;
package math is
	type vector is private;
	type matrix is private;
	function get_matrix return matrix;
	function get_vector return vector;
	function sort(v : in vector) return vector;
	function "*"(m1, m2 : in matrix) return matrix;
	function "*"(v : in vector; m : in matrix) return vector;
	function "+"(v1, v2 : in vector) return vector;
	procedure put_vector(v : in vector);
	function transpose(m : in matrix) return matrix;
	procedure put_matrix(m : in matrix);
private
	type vector is array(1..size) of float;
	type matrix is array(1..size, 1..size) of float;
end math;