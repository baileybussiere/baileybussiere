fib_l=: 3 : 0
if. y<2
do. y
else. (fib_l <:y)+fib_l y-2 end.
)
