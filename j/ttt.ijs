NB. Resets the grid
r=: '000000000' 1!:2 (1!:21 <'grid')

NB. Reads grid, returns 3by3 matrix, 1 = X, 2 = O, 0 = unoccupied
read=: 3 : 0
3 3 $ "."0 (1!:1) <'grid'
)
