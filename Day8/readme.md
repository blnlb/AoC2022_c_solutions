## Comments
Glad I broke up each direction into different functions. The change from part 1 to 2 amounted to changing return types and the following:
# Part 1
```
return checkUp(grid, row, col) || checkDown(grid, row, col) ||
            checkLeft(grid, row, col) || checkRight(grid, row, col);
```
# Part 2
```
return checkUp(grid, row, col) * checkDown(grid, row, col) *
            checkLeft(grid, row, col) * checkRight(grid, row, col);
```

## Example Output and Time with `input.txt`

### Part 1
```
1533
Program took 0.914000 ms
```
### Part 2
```
345744
Program took 1.700000 ms
```
