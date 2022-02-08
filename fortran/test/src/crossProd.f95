program crossProd
implicit none
	integer, dimension(3) :: a, b, res
	print *, "Please enter three integers:"
	read (*, *) a
	print *, "Please enter another three integers:"
	read (*, *) b
	res = (/ a(2) * b(3) - a(3) * b(2), a(3) * b(1) - a(1) * b(3), a(1) * b(2) - a(2) * b(1) /)
	print *, "The cross product is ", res
end program crossProd