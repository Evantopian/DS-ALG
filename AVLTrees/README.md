# Assignment 2: Lists and Trees

**Objective**: Learn and manipulate how AVL trees function.

## Part 1:
**Objective**: Create a class object named `SequenceMap` that will store enzyme sequences and acronyms.
#### Implementing The Class: 
* &check;  Private Members.
* &check;  The Big Five (defaults).
* &check;  Overloading Operators (>), (<).
* &check;  Merge member function.

### Experience:
**Bugs:** Implementing `SequenceMap.h` was quite straightforward however a bug I encountered, or really a mistake on my part, was the `Merge` function. While I uploaded `SequenceMap.h` for the first time to gradescope I had named it `Merge`, which is correct, but for my own styling I made the name lowercased and then ran into errors after constructing part 2A of the assignment. Reading the discussion board from Professor Raja about `Merge` annd `merge` clarified the issue and in the end I fixed it.

**Feedback:** Ifelt that the instructions for the `Merge` function was a little bit unclear at first, I thought of sorting, but as I progressed into insertions of the AVL Tree, I realized that it was simply appending one vector to another while disregarding duplicates.
<br>


## Part Two:
**Manipulating the AVL Tree:**

#### Part 2 (A):
* &check; Parser for "Database." (query_tree)
* &check; Insertion with `Merge` implementation.
* &check; Overloading << (ostream) operator for printing.

### Experience:
**Bugs:** Again, this part of the assignment was quite straightforward as well. No bugs of significant other than printing was found.

**Feedback:** As mentioned above, no significant errors occured. The process for this implementation went quite smooth for me.
<br>

#### Part 2 (B):
* &check; Parser for "Database." (test_tree)
* &check; Printing number of nodes.
* &check; Printing average depth & ratio of the average depth to # of nodes.
* &check; Counting  `find()` for total # of successful queries & printing average number of recursive calls.
* &check; Using `remove()` to remove **every other** sequence in `sequence.txt`, printing # of recursive calls, & printing the average number of recursive calls.
* &check; Re-printing # of nodes, the average depth, and the ratio of the average depth to `n` of the tree.

### Experience:
**Bugs:** Bugs that I encourtered throughout this part of the assignment regarded honing in on the accepted margins of the prompted values. For example, and the most bothersome of all, when trying to achieve around `~ 9.1` for the average number of recursive calls for `remove()`, I achieve `~ 8.4`, `9.4`, and even `10.6`. After debugging for around an hour, I resolve this issue by noticing that `findMin()` was another recursive function that was being called. However, resolving that resulted in `~ 10.6`. Re-reading the pdf, I leared that we had to account for only every other sequence found in `sequence.txt`. Solving that issuse resulted in `~ 9.4`. Then after tweaking and re-examing `remove()`, I managed to achieve `9.1` a chose enough number to pass gradescope. 


**Feedback:** The majority of my errors were not so much the software engineering, but rather reading and comprehending the instructions and code of the assignment. Other errors regarded simple recursive thinking like finding the `sum_depth`. But, in essence, the problems were straightforward and required trial and error.
<br>

#### Part 2 (C):
* &check; Parser for "Database." (test_tree_mod)
* &check; Implement Double Rotation w/o using given singlular rotation functions.

**Feedback:** This part of the assignment was very guided. Since we've been given the textbook implementation of singular rotations of an AVL tree, all I had to do was understand the singular implementations, then both imagine and sketch out how the operations would look like and schematically build the function. In essence, I took a lot of influence from the singular rotation functions and built double rotations of the function. Hence, there were no signficant bugs that were notable.


### Running The Program:
To compile on terminal, type:
```bash
make
```

You can compile one program individually by just typing `make <Program Name>`, for example:

```bash
make query_tree
```

To delete executables and object files, type:

```bash
make clean
```
