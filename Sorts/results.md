# Merge Sort (Poorly Written):
* Time complexity: O(n*log(n)).
* As tested in both class and at home with my desktop, the merge sort runs slower than both ```qsort``` and ```qsort2``` for smaller datasets but runs faster as the dataset increases, surpassing the inplace quicksort at around ```s = 55000``` (on my machine).

# Quick Sort (Poorly Written):
* Time complexity: O(n^2)
* The reason why this quick sort, ```qsort```, is slower than its inplace counterpart is the fact that qsort allocates more memory when creating vectors when sorting. 
* Even if we changed the pivot of the quick sort to its most centered value, there is no significant change in runtime.

# Quick Sort (In place from Geeks):
* Time complexity: O(n*log(n))
* This better variation of the quick sort performs much faster than the poorly written one, obviously, due to its “in place” operations on the vector. Less allocation = faster performance.
* When changing the pivot to the most median value, since we’re comparing low and high bounds, the median value is the most efficient selection, the quicksort performs faster but not to an extreme, but faster nonetheless. At a larger scale with a more powerful machine, these pivotal changes are definitely a factor to consider when striving for the most efficient runtime.

