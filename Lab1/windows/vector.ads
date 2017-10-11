with ada.containers.generic_array_sort;
generic
	size : positive;
package vector is
	type vector is private;
	function get_vector return vector;
	function sort(v: in vector) return vector;
	--procedure sort is new ada.containers.generic_array_sort(positive, element, vector);	
private
	type vector is array(1..size) of float;
end vector;