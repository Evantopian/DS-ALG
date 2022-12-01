# Assignment 1: The Big Five

**Prompt**: Create a class called `Points2D` which represents a sequence of 2D points. 

**Objective**: Learn how to apply the Big Five/Rule of Five.

<br>

## Part One:

#### Implementing The Big Five: 
* &check;  Zero parameter constructors.
* &check;  Copy constructor and assignment.
* &check;  Move constructor and assignment.
* &check;  Destructor.


### Experience:
**Bugs:** There were no noticible bug that could not have been fixed while programming this class. Bugs included regarded segfaults, malloc errors, & double frees. These issues were resolved by iterating through VsCode's built in debugger, finding the problem, and realizing a solution.

**Feedback:** I found that majority of the difficulty in implementing The Big Five regarded `*sequence_`. Having to copy and move a pointer was a first, but nothing out of worldly.
<br>

## Part Two:
**Overloading Operators:**
* &check; Overload << 
* &check;  Overload >>
* &check;  Overload +
* &check;  Overload []

### Experience:
**Bugs (1):** Majority of the bugs resided here. The most severe error regarded overloading the insertion operator, >>. Prior to testing the addition operator, I thought program was supposed to truncate the excessive values found after a single input. 

E.g 
`2 1 2 3 4 5` → `(1, 2) (3, 4) 5` 
Prior to testing on GradeScope, I truncated the 5, however, "Test 2: Overloading Operators" required `stdin` such that a input of:
```
4  1.5 2.5 6.6 9.2 4.5 3.2 5.4
3  200.0 6.0 450.2 8.8 9.6 3.4
```
Becomes `(1.5, 2.5) (6.6, 9.2) (4.5, 3.2) (5.4, 3)` instead of throwing an error and aborting early since there were only 3 proper pairs in the first line. This required me to remake my overloading >> function from using `std::stringstream` and `std::getline` to  `std::cin`.


**Bugs (2):** Handling invalid inputs like `string` and `char` was straightforward. Setting my input variable as a `double val;` and then putting the condition `if (in.fail() || val < 0)` would handle both non-numerical values and sizes of less than 0.

<br>


## Other Checks:
* Numerical Input (non-numerical, abort)
* Input size (input < indicated size, abort)
* "+" operator (c1 or c2 = 0, return non-zero instance)
* "+" operator (c1 && c2 = 0, return c1, zero)

### Running The Program:
To compile on terminal, type:

```bash
make clean
make all
```

To delete executables and object files, type:

```bash
make clean
```

To run, type:

```bash
./test_points2d
```

## Providing Input from Standard Input

To run with a given file that is redirected to standard input:

```bash
./test_points2d < test_input_file.txt
```
