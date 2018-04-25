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
	function get_scalar return float;
	function get_matrix return matrix;
	function get_vector return vector;
	function fill_matrix return matrix;
	function fill_vector return vector;
	procedure put_vector(v : in vector);
	procedure put_matrix(m : in matrix);
	procedure put_scalar(f : in float);
	procedure clear_matrix(m : out matrix);

	function get(i : in positive; v : in vector) return float;
	function get(i, j : in positive; m : in matrix) return float;
	procedure set(i : in positive; f : float; v : out vector);
	procedure set(i, j : in positive; f : float; m : out matrix);
	procedure append(i, j : in positive; f : float; m : out matrix);
private
	type vector is array(1..size) of float;
	type matrix is array(1..size, 1..size) of float;
end math;
