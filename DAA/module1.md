# Module 1: Introduction and Advanced Data Structure

## Q1: What is recurrence relation? How is a recurrence solved using master’s theorem? (2 Marks / 10 Marks context)

**Answer:**

**Recurrence Relation:**
A recurrence relation is an equation or inequality that describes a function in terms of its value on smaller inputs. In the context of Algorithm Analysis, it is often used to describe the time complexity of a divide-and-conquer algorithm.
For example, in Merge Sort, the time taken to sort an array of size `n` is the time taken to sort two arrays of size `n/2` plus the time taken to merge them:
`T(n) = 2T(n/2) + O(n)`
Here, `T(n)` is defined in terms of `T(n/2)`.

**Master's Theorem:**
The Master Theorem provides a cookbook method for solving recurrence relations of the form:
`T(n) = aT(n/b) + f(n)`
Where:
- `n` is the size of the problem.
- `a >= 1` is the number of subproblems in the recursion.
- `b > 1` is the factor by which the subproblem size is reduced.
- `f(n)` is the cost of the work done outside the recursive calls, which includes the cost of dividing the problem and the cost of merging the solutions (often an asymptotically positive function).

The theorem compares the function `f(n)` with the function `n^(log_b a)`. There are three main cases:

**Case 1: If f(n) = O(n^c) where c < log_b a**
In this case, the work done in the recursive calls (the leaves of the recursion tree) dominates.
The time complexity is:
`T(n) = Theta(n^(log_b a))`

**Case 2: If f(n) = Theta(n^(log_b a) * log^k n) for some k >= 0**
In this case, the work done at each level of the recursion tree is roughly equal.
The time complexity is:
`T(n) = Theta(n^(log_b a) * log^(k+1) n)`
(Usually, `k=0`, so `T(n) = Theta(n^(log_b a) * log n)`)

**Case 3: If f(n) = Omega(n^c) where c > log_b a**
AND if the regularity condition holds: `a * f(n/b) <= k * f(n)` for some constant `k < 1` and sufficiently large `n`.
In this case, the work done at the root of the recursion tree dominates.
The time complexity is:
`T(n) = Theta(f(n))`

---

## Q2: Solve the recurrence T (n) = 4T(n/2) + n^2 (2 Marks)

**Answer:**

Given Recurrence: `T(n) = 4T(n/2) + n^2`
We can solve this using the Master Theorem. The recurrence is of the form `T(n) = aT(n/b) + f(n)`.
Comparing the two, we get:
- `a = 4`
- `b = 2`
- `f(n) = n^2`

Step 1: Calculate `n^(log_b a)`
`log_b a = log_2 4 = 2`
So, `n^(log_b a) = n^2`

Step 2: Compare `f(n)` with `n^(log_b a)`
`f(n) = n^2`
`n^(log_b a) = n^2`

Therefore, `f(n) = Theta(n^(log_b a))` or `f(n) = Theta(n^2)`.
This matches **Case 2** of the Master Theorem (with `k=0`).

Step 3: Apply the Case 2 formula
The time complexity is `T(n) = Theta(n^(log_b a) * log n)`
Therefore, **`T(n) = Theta(n^2 log n)`**

---

## Q3: Solve the following recurrence relation: (i) T (n) = T (n-1) + n^4 (ii) T (n) = T (n/4) + T (n/2) + n^2 (10 Marks)

**Answer:**

### (i) `T(n) = T(n-1) + n^4`
This recurrence cannot be solved directly using the standard Master Theorem because it reduces the problem size by a constant (subtraction) rather than a fraction (division). We use the Iterative (Substitution) Method or Recursion Tree method.

Let's expand the recurrence:
`T(n) = T(n-1) + n^4`
`T(n) = [T(n-2) + (n-1)^4] + n^4`
`T(n) = [T(n-3) + (n-2)^4] + (n-1)^4 + n^4`
...
Continuing this process down to `T(1)`:
`T(n) = T(1) + 2^4 + 3^4 + ... + (n-1)^4 + n^4`

Assuming `T(1)` is a constant (base case), the sum is the sum of the 4th powers of the first `n` natural numbers.
The sum `sum(i^k)` from `i=1` to `n` is bounded by `Theta(n^(k+1))`.
Therefore, the sum `1^4 + 2^4 + ... + n^4 = Theta(n^5)`.

Result: **`T(n) = Theta(n^5)`**

### (ii) `T(n) = T(n/4) + T(n/2) + n^2`
This is an example of an Akra-Bazzi type recurrence or can be solved using the Recursion Tree method.

Let's draw the recursion tree:
The cost at the root is `n^2`.
The root splits into two children of sizes `n/4` and `n/2`.
The cost at level 1 (children of root) is:
`(n/4)^2 + (n/2)^2 = n^2/16 + n^2/4 = (5/16) * n^2`

The cost at level 2 (grandchildren) is:
For the `n/4` node: `(n/16)^2 + (n/8)^2 = n^2/256 + n^2/64 = (5/256)n^2`
For the `n/2` node: `(n/8)^2 + (n/4)^2 = n^2/64 + n^2/16 = (5/64)n^2`
Total cost at level 2 = `(5/256)n^2 + (20/256)n^2 = (25/256)n^2 = (5/16)^2 * n^2`

We can observe a pattern. The cost at level `i` is `((5/16)^i) * n^2`.
The total cost `T(n)` is the sum of costs at all levels:
`T(n) = n^2 + (5/16)n^2 + (5/16)^2 * n^2 + ...`
`T(n) = n^2 * [1 + (5/16) + (5/16)^2 + ...]`

The expression in the brackets is an infinite geometric series with a common ratio `r = 5/16 < 1`.
The sum of an infinite geometric series `1 + r + r^2 + ...` is `1 / (1 - r)`.
Sum = `1 / (1 - 5/16) = 1 / (11/16) = 16/11`.

Therefore, `T(n) <= (16/11) * n^2`.
Since the first term is `n^2`, `T(n) >= n^2`.
Thus, `T(n)` is bounded above and below by a constant multiple of `n^2`.

Result: **`T(n) = Theta(n^2)`**

---

## Q4: What is asymptotic notation? Explain Omega (Ω) notation? (2 Marks / 10 Marks Context)
*(Combines "What is asymptotic notation?" and "Explain different asymptotic notations")*

**Answer:**

**Asymptotic Notation:**
Asymptotic notations are mathematical tools used to describe the limiting behavior of a function when the argument tends towards a particular value or infinity. In algorithm analysis, they are used to estimate the running time (or space) complexity of algorithms. They allow us to compare the efficiency of different algorithms independently of hardware or programming language specifics by focusing on how the execution time grows as the input size (`n`) grows indefinitely. They capture the "order of growth."

The three primary asymptotic notations are Big-O (`O`), Omega (`Ω`), and Theta (`Θ`).

**Omega (Ω) Notation (Lower Bound):**
Omega notation provides an asymptotic lower bound. It gives the best-case scenario or the minimum amount of time an algorithm will take for a given input size.

Definition: Let `f(n)` and `g(n)` be two functions defined on the set of positive integers. We say `f(n) = Ω(g(n))` if there exist positive constants `c` and `n0` such that:
`0 <= c * g(n) <= f(n)` for all `n >= n0`.

In simpler terms, it means `f(n)` grows at least as fast as `g(n)`. For example, if an algorithm's time complexity is `Ω(n)`, it means it will take at least linear time, but it could take more (like `n^2`).

**Explanation of other notations (for completeness):**

**Big-O (O) Notation (Upper Bound):**
Big-O notation provides an asymptotic upper bound. It describes the worst-case scenario or the maximum time required.
Definition: `f(n) = O(g(n))` if there exist positive constants `c` and `n0` such that:
`0 <= f(n) <= c * g(n)` for all `n >= n0`.
Meaning `f(n)` grows no faster than `g(n)`.

**Theta (Θ) Notation (Tight Bound):**
Theta notation provides an asymptotic tight bound. It means the function grows exactly at the same rate as the reference function. It is used when an algorithm has the same worst-case and best-case time complexity, or to describe the exact growth rate.
Definition: `f(n) = Θ(g(n))` if there exist positive constants `c1`, `c2`, and `n0` such that:
`0 <= c1 * g(n) <= f(n) <= c2 * g(n)` for all `n >= n0`.
Meaning `f(n)` is bounded both above and below by `g(n)`.

---

## Q5: Explain different characteristics of an algorithm. (8 Marks)

**Answer:**

An algorithm is a well-defined, step-by-step computational procedure that takes some value, or a set of values, as input and produces some value, or a set of values, as output. For a sequence of instructions to be considered a valid algorithm, it must possess the following fundamental characteristics:

1.  **Input:**
    An algorithm must have zero or more well-defined inputs. These are the quantities that are given to it initially before the algorithm begins its execution.

2.  **Output:**
    An algorithm must produce at least one output. The output is the result or the solution to the problem the algorithm is designed to solve, generated after processing the inputs.

3.  **Definiteness (Unambiguity):**
    Every step or instruction in the algorithm must be clear, precise, and unambiguous. There should be no room for subjective interpretation. Each action to be performed must be rigorously specified. For example, "add 5 or 6 to x" is not definite, but "add 5 to x" is.

4.  **Finiteness (Termination):**
    If we trace out the instructions of an algorithm, then for all cases, the algorithm must terminate after a finite number of steps. It cannot enter an infinite loop. A procedure that has all characteristics of an algorithm except finiteness is often called a "computational method" (like an operating system).

5.  **Effectiveness (Feasibility):**
    Every instruction in the algorithm must be sufficiently basic such that it can, in principle, be carried out exactly and in a finite length of time by a person using only paper and pencil. The operations must be achievable.

6.  **Language Independent:**
    The algorithm must be independent of any specific programming language. It should be written in a generic way (like pseudocode or flowcharts) so that it can be implemented in any language like C, C++, Java, or Python without changing the core logic.

7.  **Efficiency:**
    While not strictly a requirement for being an algorithm, a good algorithm is efficient. Efficiency is measured in terms of the resources it consumes, primarily:
    *   **Time Complexity:** The amount of time the algorithm takes to complete.
    *   **Space Complexity:** The amount of memory space the algorithm requires during execution.

---

## Q6: Explain how algorithms performance is analyzed? (2 Marks)

**Answer:**

Algorithm performance is analyzed primarily using two metrics, which evaluate resource consumption:

1.  **Time Complexity:** This is the most crucial metric. It evaluates how the execution time of an algorithm increases as the input size (`n`) grows. We use Asymptotic Notations (Big O for worst-case, Omega for best-case, Theta for average/tight bound) to represent this growth rate. It is not measured in seconds (which depends on hardware) but in the number of basic operations performed.
2.  **Space Complexity:** This measures the total amount of memory space required by the algorithm during its execution as a function of input size. It includes both the space needed for variables/inputs and the auxiliary (extra) space needed for temporary operations or recursion stacks.

---

## Q7: Write three steps involved in divide and conquer approach for problem solving. (8 Marks / 10 Marks Context)
*(Also covers: "Explain searching technique using divide and conquer approach." and elements of specific sort questions)*

**Answer:**

The Divide and Conquer paradigm is a powerful problem-solving strategy that breaks down a complex problem into smaller, more manageable sub-problems, solves them recursively, and then combines their solutions to get the final answer. The three fundamental steps are:

1.  **Divide:**
    The original problem is partitioned into several smaller sub-problems. These sub-problems must be of the same type as the original problem, just with a smaller input size. For example, in Merge Sort, an array of size `n` is divided into two halves of size `n/2`.

2.  **Conquer:**
    The sub-problems are solved recursively. The recursion continues until the sub-problem size is small enough to be solved directly and simply without further division. This simple case is known as the "base case".

3.  **Combine:**
    The solutions of the sub-problems are merged or combined together to create the solution to the original problem. The efficiency of the divide-and-conquer algorithm often depends heavily on how efficiently the combine step can be performed.

**Application in Searching (Binary Search):**
Binary Search is a classic example of Divide and Conquer used for searching a sorted array.
*   **Divide:** The middle element of the sorted array is checked. The problem is divided by discarding half of the search space based on whether the target value is less than or greater than the middle element.
*   **Conquer:** The algorithm recursively searches the remaining half. The base case is when the element is found, or the search space is empty (element not found).
*   **Combine:** In binary search, the combine step is trivial or non-existent, as the solution of the sub-problem (finding the index) is directly the solution to the original problem.

---

## Q8: Write down the best-case, worst case and average case-complexity of quicksort. (8 Marks Context)
*(Also addresses "Explain quicksort algorithm and also write its time and space complexity" and "Write down the best-case, worst case and average case-complexity of quicksort")*

**Answer:**

**Quicksort Algorithm Overview:**
Quicksort is a highly efficient, comparison-based, divide-and-conquer sorting algorithm. It works by selecting a 'pivot' element from the array and partitioning the other elements into two sub-arrays, according to whether they are less than or greater than the pivot. The sub-arrays are then sorted recursively.

**Algorithm Steps:**
1.  Choose a pivot element (often the last, first, or middle element).
2.  Partitioning: Rearrange the array so that all elements smaller than the pivot come before it, and all elements greater come after it. The pivot is now in its final sorted position.
3.  Recursively apply the above steps to the sub-array of elements with smaller values and the sub-array of elements with greater values.

**Time Complexity:**

*   **Best-Case Complexity: O(n log n)**
    The best case occurs when the partition process always picks the middle element as the pivot. The problem is divided into two equal halves at every step. The recurrence is `T(n) = 2T(n/2) + O(n)`, which solves to `O(n log n)`.

*   **Average-Case Complexity: O(n log n)**
    On average, even if the splits aren't perfectly equal (e.g., 9-to-1 split), the depth of the recursion tree remains `O(log n)`. The work done at each level is `O(n)`. Therefore, the average time complexity is mathematically proven to be `O(n log n)`. This is the typical performance in practice, making it generally faster than Merge Sort.

*   **Worst-Case Complexity: O(n^2)**
    The worst case occurs when the partition process always picks the greatest or smallest element as the pivot. This happens if the array is already sorted (or reverse sorted) and the first or last element is chosen as the pivot. In this case, one sub-problem is of size `n-1` and the other is size `0`. The recurrence is `T(n) = T(n-1) + O(n)`, which results in an arithmetic series summing to `O(n^2)`.

**Space Complexity:**
*   Quicksort is an **in-place** sort (it doesn't require a large auxiliary array like Merge Sort).
*   However, it uses space on the call stack due to recursion.
*   **Best/Average Case Space:** `O(log n)` stack frames.
*   **Worst Case Space:** `O(n)` stack frames (if the recursion tree is completely unbalanced).

---

## Q9: Sort the given array by using merge sort algorithm: <5, 2, 4, 7, 1, 3, 2, 6> (12 Marks)

**Answer:**

Merge Sort is a Divide and Conquer algorithm. It divides the input array into two halves, calls itself for the two halves, and then merges the two sorted halves.

**Given Array:** [5, 2, 4, 7, 1, 3, 2, 6]

**Step 1: Divide phase**
We recursively divide the array into halves until we reach sub-arrays of size 1.

Level 0: [5, 2, 4, 7, 1, 3, 2, 6]
Level 1: [5, 2, 4, 7] and [1, 3, 2, 6]
Level 2: [5, 2], [4, 7] and [1, 3], [2, 6]
Level 3: [5], [2], [4], [7] and [1], [3], [2], [6] (Base case reached: arrays of size 1 are sorted)

**Step 2: Merge (Conquer and Combine) phase**
We merge the sorted sub-arrays back together in sorted order.

Level 2 (Merging Level 3):
Merge [5] and [2] -> [2, 5]
Merge [4] and [7] -> [4, 7]
Merge [1] and [3] -> [1, 3]
Merge [2] and [6] -> [2, 6]

Current State: [2, 5], [4, 7] and [1, 3], [2, 6]

Level 1 (Merging Level 2):
Merge [2, 5] and [4, 7] -> Compare elements: 2<4(take 2), 5>4(take 4), 5<7(take 5), take remaining 7. Result: [2, 4, 5, 7]
Merge [1, 3] and [2, 6] -> Compare: 1<2(take 1), 3>2(take 2), 3<6(take 3), take 6. Result: [1, 2, 3, 6]

Current State: [2, 4, 5, 7] and [1, 2, 3, 6]

Level 0 (Merging Level 1):
Merge [2, 4, 5, 7] and [1, 2, 3, 6]
- 1 < 2 -> [1]
- 2 == 2 -> [1, 2, 2]
- 3 < 4 -> [1, 2, 2, 3]
- 4 < 6 -> [1, 2, 2, 3, 4]
- 5 < 6 -> [1, 2, 2, 3, 4, 5]
- 6 < 7 -> [1, 2, 2, 3, 4, 5, 6]
- Add remaining 7 -> [1, 2, 2, 3, 4, 5, 6, 7]

**Final Sorted Array:** <1, 2, 2, 3, 4, 5, 6, 7>

---

## Q10: Write an algorithm for counting sort? Illustrate the operation of counting sort on the following array: A={4, 0, 2, 0, 1, 3, 5, 4, 1, 3, 2, 3} (10 Marks)

**Answer:**

**Counting Sort Algorithm:**
Counting sort is a non-comparison-based sorting algorithm. It works by counting the number of objects having distinct key values (like a hash). Then doing some arithmetic to calculate the position of each object in the output sequence. It is efficient when the range of input data (`k`) is not significantly greater than the number of objects to be sorted (`n`).

**Algorithm:**
```text
COUNTING-SORT(A, B, k)
// A: Input array [1..n]
// B: Output sorted array [1..n]
// k: Maximum value in array A
1. let C[0..k] be a new array
2. for i = 0 to k
3.     C[i] = 0
4. for j = 1 to A.length
5.     C[A[j]] = C[A[j]] + 1
6. // C[i] now contains the number of elements equal to i.
7. for i = 1 to k
8.     C[i] = C[i] + C[i-1]
9. // C[i] now contains the number of elements less than or equal to i.
10. for j = A.length down to 1
11.    B[C[A[j]]] = A[j]
12.    C[A[j]] = C[A[j]] - 1
```

**Illustration:**
Given Array `A` = {4, 0, 2, 0, 1, 3, 5, 4, 1, 3, 2, 3}
Size `n = 12`. Maximum element `k = 5`.

**Step 1 & 2: Initialize count array C and count occurrences.**
Create array `C` of size `k+1 = 6`, initialized to 0.
Count frequencies of each element in `A`:
`A`: [4, 0, 2, 0, 1, 3, 5, 4, 1, 3, 2, 3]
`C`:
Index: 0  1  2  3  4  5
Count: 2  2  2  3  2  1
(e.g., '0' appears 2 times, '3' appears 3 times)

**Step 3: Cumulative Count.**
Modify `C` such that each element at index `i` stores the sum of previous counts. This gives the actual position in the sorted array.
`C[i] = C[i] + C[i-1]`
Index: 0  1  2  3  4  5
C:     2  4  6  9  11 12
(e.g., there are 9 elements less than or equal to 3)

**Step 4: Build Output Array B.**
Traverse input array `A` from end to start (to maintain stability).
`B` is an empty array of size 12.

1.  `j=12, A[12]=3`. Look up `C[3]=9`. Place '3' at `B[9]`. Decrement `C[3]` to 8.
2.  `j=11, A[11]=2`. Look up `C[2]=6`. Place '2' at `B[6]`. Decrement `C[2]` to 5.
3.  `j=10, A[10]=3`. Look up `C[3]=8`. Place '3' at `B[8]`. Decrement `C[3]` to 7.
4.  `j=9,  A[9]=1`.  Look up `C[1]=4`. Place '1' at `B[4]`. Decrement `C[1]` to 3.
5.  `j=8,  A[8]=4`.  Look up `C[4]=11`. Place '4' at `B[11]`. Decrement `C[4]` to 10.
6.  `j=7,  A[7]=5`.  Look up `C[5]=12`. Place '5' at `B[12]`. Decrement `C[5]` to 11.
... continuing this process ...

**Final Output Array B:**
{0, 0, 1, 1, 2, 2, 3, 3, 3, 4, 4, 5}

---

## Q11: Write an algorithm for insertion sort. Find the time complexity of Insertion sort in all cases. (10 Marks)

**Answer:**

**Insertion Sort Algorithm:**
Insertion sort is a simple sorting algorithm that builds the final sorted array one item at a time. It is much like sorting playing cards in your hands. You pick one card and place it in its correct position relative to the already sorted cards.

**Algorithm:**
```text
INSERTION-SORT(A)
// A is the input array of size n
1. for i = 2 to A.length
2.     key = A[i]
3.     // Insert A[i] into the sorted sequence A[1 .. i-1].
4.     j = i - 1
5.     while j > 0 and A[j] > key
6.         A[j + 1] = A[j]  // Shift element to the right
7.         j = j - 1
8.     A[j + 1] = key      // Place key in its correct position
```

**Time Complexity Analysis:**
The time complexity depends heavily on the initial order of the elements.

*   **Best-Case Complexity: O(n)**
    The best case occurs when the array is already sorted. In the inner `while` loop, the condition `A[j] > key` will always evaluate to false immediately for every element. Thus, the inner loop never executes its body, and the algorithm only makes one comparison per outer loop iteration. Total comparisons = `n-1`. Therefore, time complexity is linear, `O(n)`.

*   **Worst-Case Complexity: O(n^2)**
    The worst case occurs when the array is sorted in reverse order. For every element `A[i]`, the inner `while` loop must shift all previously sorted elements `A[1..i-1]` to the right to make space at the very beginning of the array.
    For `i=2`, 1 shift.
    For `i=3`, 2 shifts.
    ...
    For `i=n`, `n-1` shifts.
    Total operations roughly equal to `1 + 2 + ... + (n-1) = n(n-1)/2`. This is a quadratic function, so the time complexity is `O(n^2)`.

*   **Average-Case Complexity: O(n^2)**
    On average, for a randomly ordered array, an element `A[i]` will be smaller than half of the elements in the sorted sub-array `A[1..i-1]`. Thus, the inner loop will execute about `i/2` times. The total number of operations will be approximately half of the worst-case, which is `(n(n-1)/2) / 2 = n^2/4`. Asymptotically, constants are ignored, resulting in a time complexity of `O(n^2)`.
