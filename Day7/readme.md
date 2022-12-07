## Comments
Interesting little conditional recursion. Changed the buffer to a pointer, so I could do some address jumping. Ended up passing the file pointer into functions so that the buffer could stay open and not lose its place. Some of this is general and useful in other settings. In particular 
```
struct node {
    int sum;
    int numChildren;
    struct node **children;
} node;
typedef struct node nod;
```
and the accompanying `nod *createNode(int)` and `void deleteNode(nod*)` functions are general enough to be used again. Even binary trees can be encoded this way, though giving `node->children[0]` the name `node->left` will probably end up being clearer, more intuitive, and less of a memory hog. In any case, the create function needs just a minor retweak.

`createNode(int)` can also be tweaked by removing the call with an `int` and setting the `sum` to 0, but this way allows for more flexibility in future code. So look forward to me refactoring this into `utility.h`.

## Example Output and Time with `input.txt`
I tracked how long the total program takes before and after freeing the memory associated with the tree. One caveat here is of course that part of the second invocation calculates how long the program, the cleanup, and _the first invocation_ take together. Oh well. It's consistent across both programs.
### Part 1
```
919137
Duration of program, pre-cleanup: 0.191000 ms
Duration of program, post-cleanup: 0.198000 ms
```
### Part 2
```
@ Best candidate is of size: 2877389 <--------
Duration of program, pre-cleanup: 0.196000 ms
Duration of program, pre-cleanup: 0.204000 ms
```

## Time Complexity
### Part 1
We go through the file once, line by line to read everything, and we build a tree in place.
```O(2n) = O(n)```
### Part 2 
`O(2n)` for the same reason.
