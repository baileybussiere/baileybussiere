program firstTenFib
implicit none
	integer :: a, b, c, temp
	a = 0
	b = 1
	do c = 0, 9
		temp = a + b
		print *, temp
		a = b
		b = temp
	end do
end program firstTenFib