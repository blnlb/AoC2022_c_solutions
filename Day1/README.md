### Output and Time
The biggest number of calories is... 195292.
This program took **0.000225** seconds to run.
### Time Complexitiy
Where _n_ is the number of lines, I suspect we only scale up with the number of calorie observations we parse.
We only sort in place when we need to move out an element of the _top3_ array. Which could feasibly happen _n-2_ times worst case.
Summation and data creation is all **O(1)**.
So I guess this is **O(2n-2)=O(n)**. Right?

(Provide feedback if you got it!)
