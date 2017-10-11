--Math library containing some vector and matrxi operations.
--for L #1: Threads in Ada.

--was implemented by
--Krisak Ivan Mylikayovich,
--a student of IO-53.

with ada.containers.generic_array_sort;
generic
	size : positive;
package math is
	type vector is private;
	type matrix is private;
	function get_matrix return matrix;
	function get_vector return vector;
	function fill_matrix return matrix;
	function fill_vector return vector;
	procedure put_vector(v : in vector);
	procedure put_matrix(m : in matrix);

	function f1(a, b : in vector; ma, me : in matrix) return vector;
	function f2(mk, mh, mf : in matrix) return matrix;
	function f3(r, s : in vector; mt, mp : in matrix) return vector;

	--function sort(v : in vector) return vector;
	--function transpose(m : in matrix) return matrix;
	--function "*"(m1, m2 : in matrix) return matrix;
	--function "*"(v : in vector; m : in matrix) return vector;
	--function "+"(v1, v2 : in vector) return vector;
private
	type vector is array(1..size) of float;
	type matrix is array(1..size, 1..size) of float;
end math;
