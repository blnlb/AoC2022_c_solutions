## Comments
I saw the number change (from 4 to 14) coming. Of course I could have extended the if-else conditions to cover all 13+12+11+...+1 cases. But damn would that be silly looking. Easy copy-paste job, but still.

You can actually achieve part 1's goal with part 2's code. Change the macro 
`#define DISTINCT_CHAR 14`
to
`#define DISTINCT_CHAR 4`

## Example Output and Time with `input.txt`
### Part 1
1766
### Part 2
2383

## Time Complexity
### Part 1
`O(n)`. Worst case scenario is we read `n-4` different windows of our string.
### Part 2 
`O(n^2)`. This is textbook double for-loop complexity. Probably a more elegant solution exists.
