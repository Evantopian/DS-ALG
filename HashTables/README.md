# Assignment 3: Hashing and Heaps

**Objective**: Operations on HashTables: Create linear probing, quadratic probing, and double hashing tables. Create a spell checker on the `HashTable(s)` developed.

#### Project Implementations: 
* &check;  Data Parsing & Display.
* &check;  Linear Probing.
* &check;  Quadratic Probing.
* &check;  Double Hashing.
* &check;  Spell Check (Three Cases)

### Part 1:
**Linear and Quadratic Probing:**
#### Implementing The Class(s): 
* &check;  Data Parsing & Display.
* &check;  Linear Probing.
* &check;  Quadratic Probing.
* &check;  Probe Count Display.

### Experience:
**Bugs** There were no bugs in this section of the project considering that the code was derived from the textbook. Moreover, after understanding the code, the conversion from linear to quadratic was easily implemented, the `offset` value.

**Feedback:** Displaying the data was quite interesting. Seeing the number of collisions and load-factor of the data helped me understand the `HashTable` slightly more. 

<br>

### Part Two:
**Double Hashing:**

#### Part 2:
* &check;  Data Parsing & Display.
* &check;  Probe Count Display.
* &check;  Second Hash Function.
* &check;  Pass in default & custom `R` value.

### Experience:
**Bugs:** Little to no bugs were found here considering that double hashing only required me to modify the `FindPos(HashedObj x)` function slightly more, mainly `offset`. Implementing the custom `R` value was probably the only issue I faced here. I forgot that when passing `R` into the constructor, you must shift the non-argument parameters to the end of the parameters itself. In essence, `(size_t size = 101, int r)` to `(int r, size_t size = 101)`.

**Feedback:** As mentioned above, no significant errors occured. The process for this implementation went quite smooth for me.

**Extras:** Checked if user inputed `R` value is prime or not. If not prime, find next prime. If the value of `R` orginally or after conversion exceeds the size of the the table, then print `"ERROR"` and then `abort()`.

<br>


### Part 3:
**Spell Check:**

* &check;  Dictionary Data Parsing.
* &check;  Case A: Adding one character in any possible position.
* &check;  Case B: Removing one character from the word.
* &check;  Case C: Swapping adjacent characters in the word.
* &check;  Spell Check Display.

### Experience:
**Bugs:** At first I attempted to implement cases A, B, & C with a normal recursive permutation function; however, I realized that I was making the problem a lot more complicated than it should be. Though I do think that a recursive function can complete both B and C together. But nonetheless, I decided with an iterative approach to the problem. As for bugs in general, there were no real notical bugs other than simple syntactic errors.

**Feedback:** The spell check problem, Part 3, was a lot more enjoyable to code since it's more hands on coding rather than implementing a already given class. 



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

To run, type (1 : HashTable Data | 2 : Spell Check):

```bash
./create_and_test_hash words <words file name> <query words file name> <flag>

./spell_check <document file> <dictionary file>
```