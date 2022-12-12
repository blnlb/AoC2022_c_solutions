## Comments
A bit ashamed in retrospect how much I preprocessed this. But I just wanted to get to the good stuff. Of course, `c` ended up not being a great candidate for this. Sure, the operations were fast, but the function pointers in structs ended up being not ideal. I had to create each operation for all 8 monkeys, meaning 12 functions overall. Instead of running a loop, and being able to pass in a lambda function of any sort, I created a pretty messy and over-explicit piece of code in setting up everything. 

I also copy-pasted all of the original worry values. This isn't good programming probably. But it's good math. And the function pointer in struct thing was relatively coy, if inelegant.

## Time Complexity
I guess this would run a lot. To be specific we drill down into three different for-loops. One goes over all each monkey's item. The one above this goes through each monkey. Since there are ~36 items, we'd feasibly go through 36 passes, but monkey's pass to monkey's further up in the loop. So we could have 36*36 items worst case, assuming each monkey is immediately able to pass to the next monkey in line. But they aren't. They have two branches only, among 7 choices. I'm sure there's a combinatoric solution here. I'm going with the `36^2 = 1296` option. After this, we run `20` times or `10000` times. Big difference.

There are multiple factors to choose from. Do we let `n` be the number of items in the queue, the number of times we iterate through a round, the number of monkeys? Is there a clear function relating each of these? Do we carry two variables and calculate this to run at, say, `O(n^2)*O(m)`? 

Since I have never studied complexities, and you are reading this, perhaps you can help? Provide me a comment if you desire. I will happily read them and learn :)