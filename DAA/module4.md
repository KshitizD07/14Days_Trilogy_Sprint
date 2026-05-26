# Module 4: String Matching & Complexity Theory

## Q1: Explain Rabin Karp string matching Algorithm. Simulate Rabin-Karp string matching for pattern “abc” in text “abcabcabc” with q=101. (7.5 Marks / 10 Marks Context)

**Answer:**

**Rabin-Karp Algorithm:**
Rabin-Karp is a string-matching algorithm that uses hashing to find any one of a set of pattern strings in a text. For text of length `n` and pattern of length `m`, its average and best-case running time is `O(n+m)`, but its worst-case time is `O(nm)`.
The core idea is to calculate a hash value for the pattern `p`, and then calculate hash values for every sliding window of length `m` in the text `t`. If the hash values match, it performs a character-by-character check to rule out spurious hits (hash collisions).

To calculate hashes efficiently for sliding windows, it uses a "rolling hash" technique.
Given an alphabet size `d` (e.g., 256 for ASCII) and a prime number `q` (to avoid overflow):
Hash `h(t[i+1...i+m]) = (d * (h(t[i...i+m-1]) - t[i]*h) + t[i+m]) mod q`
Where `h` is `d^(m-1) mod q`.

**Simulation:**
Text `T` = "abcabcabc", Length `n` = 9
Pattern `P` = "abc", Length `m` = 3
Prime `q` = 101. Alphabet size `d` = 10 (let's map a=1, b=2, c=3 for simplicity to simulate the math).

*Hash of Pattern P("abc"):*
`p = (1*10^2 + 2*10^1 + 3*10^0) mod 101 = 123 mod 101 = 22`

*Initial Hash of Text Window T[0..2] ("abc"):*
`t0 = (1*10^2 + 2*10^1 + 3*10^0) mod 101 = 123 mod 101 = 22`

**Matching Process:**
1.  **Shift 0 ("abc"):**
    `t0 == p (22 == 22)`. Hash matches.
    Check characters: "abc" == "abc". Match found at index 0.
2.  **Shift 1 ("bca"):**
    Calculate `t1` from `t0` using rolling hash.
    Old char out='a'(1), New char in='a'(1).
    `t1 = (10 * (22 - 1 * (10^2 mod 101)) + 1) mod 101`
    *(Simplified without mod arithmetic for mental trace: "bca" -> 231 mod 101 = 29)*
    `t1 (29) != p (22)`. No match.
3.  **Shift 2 ("cab"):**
    `t2` hash for "cab" (312 mod 101 = 9).
    `t2 (9) != p (22)`. No match.
4.  **Shift 3 ("abc"):**
    `t3` hash for "abc" (123 mod 101 = 22).
    `t3 == p (22 == 22)`. Hash matches.
    Check characters: "abc" == "abc". Match found at index 3.
... This continues.
It will find exact matches at shifts 0, 3, and 6.

---

## Q2: Explain Naive string matching algorithm with example. (6 Marks Context)
*(Also addresses "Write an algorithm for naive string matcher?")*

**Answer:**

**Naive String Matching Algorithm:**
The naive string matching algorithm is the simplest method. It slides the pattern over text one character at a time and checks for a match. If a mismatch is found, it simply shifts the pattern by exactly one position to the right and starts checking again from the beginning of the pattern.

**Algorithm:**
```text
NAIVE-STRING-MATCHER(T, P)
1. n = T.length
2. m = P.length
3. for s = 0 to n - m // s is the valid shift
4.     j = 1
5.     while j <= m and T[s + j] == P[j]
6.         j = j + 1
7.     if j > m
8.         print "Pattern occurs with shift " s
```

**Time Complexity:**
*   **Best Case:** `O(n)`. When the first character of the pattern doesn't appear in the text at all (e.g., T="AAAA", P="B"). Only one comparison per shift.
*   **Worst Case:** `O((n-m+1) * m)` which is `O(n*m)`. Occurs when all characters of text and pattern are identical, or when all but the last character match (e.g., T="AAAAAAAA", P="AAAAB").

**Example:**
Text `T` = "AACAADAAB"
Pattern `P` = "AADA"

*   **Shift 0:** `AACA...` vs `AADA`. Matches at A, A. Mismatch at C vs D.
*   **Shift 1:** `_ACA...` vs `AADA`. Mismatch immediately (C vs A).
*   **Shift 2:** `__CAA...` vs `AADA`. Mismatch immediately (C vs A).
*   **Shift 3:** `___AADA...` vs `AADA`. Matches A, A, D, A. **Full Match!**
*   **Shift 4:** `____ADA...` vs `AADA`. Matches A. Mismatch D vs A.
...and so on.

---

## Q3: Write KMP algorithm for string matching? Perform the KMP algorithm to search the occurrences of the pattern abaab in the text string abbabaabaabab. (10 Marks)

**Answer:**

**Knuth-Morris-Pratt (KMP) Algorithm:**
The naive algorithm wastes information by throwing away knowledge about previously matched characters. KMP avoids this by pre-computing a prefix array `pi` (often called the Longest Proper Prefix which is also Suffix array, or LPS).
When a mismatch occurs, the LPS array tells the algorithm exactly how far to shift the pattern to the right to avoid redundant comparisons, guaranteeing a linear `O(n+m)` worst-case time complexity.

**KMP Matcher Algorithm:**
```text
KMP-MATCHER(T, P)
1. n = T.length; m = P.length
2. pi = COMPUTE-PREFIX-FUNCTION(P)
3. q = 0 // number of characters matched
4. for i = 1 to n // scan the text from left to right
5.     while q > 0 and P[q + 1] != T[i]
6.         q = pi[q] // next character does not match, fallback
7.     if P[q + 1] == T[i]
8.         q = q + 1 // character matched
9.     if q == m     // is all of P matched?
10.        print "Pattern occurs with shift " (i - m)
11.        q = pi[q] // look for the next match
```

**Performing the Search:**
Pattern `P` = "abaab"
Text `T` = "abbabaabaabab"

**Step 1: Compute LPS (pi) Array for P="abaab"**
*   LPS[0] ('a') = 0
*   LPS[1] ('b') = 0 (no prefix="b" matches suffix)
*   LPS[2] ('a') = 1 (prefix "a" matches suffix "a")
*   LPS[3] ('a') = 1 (prefix "a" matches suffix "a")
*   LPS[4] ('b') = 2 (prefix "ab" matches suffix "ab")
`pi` array = `[0, 0, 1, 1, 2]`

**Step 2: Match using KMP**
`T` = a b b a b a a b a a b a b
`P` = a b a a b

*   **i=1 ('a'):** Matches P[1]. `q=1`.
*   **i=2 ('b'):** Matches P[2]. `q=2`.
*   **i=3 ('b'):** Mismatch with P[3] ('a'). `q = pi[2] = 0`. Mismatch with P[1] ('a').
*   **i=4 ('a'):** Matches P[1]. `q=1`.
*   **i=5 ('b'):** Matches P[2]. `q=2`.
*   **i=6 ('a'):** Matches P[3]. `q=3`.
*   **i=7 ('a'):** Matches P[4]. `q=4`.
*   **i=8 ('b'):** Matches P[5]. `q=5`. **Pattern fully matched! Shift = 8-5 = 3.**
    *   Set `q = pi[5] = 2` to continue searching. Current matched part of pattern is "ab".
*   **i=9 ('a'):** Matches P[3]. `q=3`.
*   **i=10 ('a'):** Matches P[4]. `q=4`.
*   **i=11 ('b'):** Matches P[5]. `q=5`. **Pattern fully matched! Shift = 11-5 = 6.**
    *   Set `q = pi[5] = 2`.
*   **i=12 ('a'):** Matches P[3]. `q=3`.
*   **i=13 ('b'):** Mismatch with P[4] ('a'). `q = pi[3] = 1`. `T[13]` ('b') matches `P[2]` ('b'). `q=2`.

Output: Matches found at shifts 3 and 6.

---

## Q4: Define P, NP and NP-complete in decision problems. Explain the following: (i) P problem (ii) NP problem (iii) NP hard problem (10 Marks)

**Answer:**

Complexity theory classifies computational problems based on how difficult they are to solve. These classifications apply to **decision problems**—problems with a simple "yes" or "no" answer (e.g., "Is there a path from A to B shorter than length k?").

**1. P (Polynomial Time) Problems:**
*   **Definition:** The class `P` consists of all decision problems that can be *solved* by a deterministic algorithm (like a standard computer) in polynomial time.
*   **Meaning:** An algorithm runs in polynomial time if its running time is `O(n^k)` for some constant `k`, where `n` is the size of the input.
*   **Implication:** Problems in `P` are considered "tractable" or efficiently solvable.
*   **Examples:** Sorting an array, finding the shortest path in a graph (Dijkstra's), searching an element.

**2. NP (Non-deterministic Polynomial Time) Problems:**
*   **Definition:** The class `NP` consists of all decision problems for which a given "yes" answer (a proposed solution or certificate) can be *verified* by a deterministic algorithm in polynomial time.
*   **Meaning:** If someone hands you a potential solution, you can check if it's correct very quickly (in polynomial time). It does *not* necessarily mean you can find the solution quickly. It also stands for problems solvable by a non-deterministic Turing machine in polynomial time.
*   **Relationship:** Every problem in `P` is also in `NP` (if you can solve it quickly, you can verify it quickly). Therefore, `P` is a subset of `NP`.
*   **Examples:** Sudoku (hard to solve, easy to check if a filled grid is valid), Travelling Salesman Problem (decision version).

**3. NP-Hard Problems:**
*   **Definition:** A problem is NP-Hard if it is *at least as hard* as the hardest problems in `NP`. Formally, a problem `H` is NP-Hard if every problem `L` in `NP` can be reduced in polynomial time to `H`.
*   **Meaning:** If you can find a polynomial-time algorithm for any NP-Hard problem, you can solve *all* problems in NP in polynomial time (which would prove P = NP, the biggest unsolved problem in computer science).
*   **Note:** NP-Hard problems do not have to be in NP themselves (they don't even have to be decision problems).
*   **Examples:** The optimization version of the Travelling Salesman Problem, the Halting Problem.

**4. NP-Complete Problems:**
*   **Definition:** A problem is NP-Complete if it satisfies two conditions:
    1.  It is in `NP` (its solutions can be verified quickly).
    2.  It is `NP-Hard` (every problem in NP can be reduced to it).
*   **Meaning:** These are the "hardest" problems within the `NP` class. They are the most likely candidates to be intractable. If a polynomial-time algorithm is ever found for even one NP-Complete problem, then P = NP.
*   **Examples:** The Boolean Satisfiability Problem (SAT), Graph Coloring, 0/1 Knapsack (decision version).

---

## Q5: What is approximation algorithm? Explain set cover problem using approximation algorithm. (10 Marks)

**Answer:**

**Approximation Algorithm:**
An approximation algorithm is a way to approach NP-Hard optimization problems. Since finding the absolute exact optimal solution would take an unreasonable amount of time (likely exponential), an approximation algorithm finds a "good enough" solution in polynomial time.
It doesn't guarantee the best answer, but it guarantees that the solution it finds is within a known, mathematically proven factor of the true optimal solution. This factor is called the approximation ratio.

**The Set Cover Problem:**
**Problem Statement:** You are given a "universe" of elements `U` = {1, 2, ..., n} and a collection of subsets `S` = {S1, S2, ..., Sm} whose union equals `U`. The goal is to identify the smallest number of subsets from `S` whose union covers all elements in `U`.
*Example scenario:* `U` is a set of skills needed for a project. `S` is a pool of contractors, where each contractor possesses a subset of those skills. You want to hire the minimum number of contractors to get all the required skills.

This is a classic NP-Complete problem.

**Greedy Approximation Algorithm for Set Cover:**
The greedy approach provides a well-known approximation algorithm for this problem.
**Strategy:** At every step, choose the subset that covers the maximum number of currently uncovered elements.

**Algorithm:**
```text
GREEDY-SET-COVER(U, S)
1. C = empty set // C will hold the selected subsets
2. Uncovered = U // elements not yet covered
3. while Uncovered is not empty
4.     Find a subset Si in S that maximizes the intersection size |Si INTERSECT Uncovered|
5.     C = C U {Si}
6.     Uncovered = Uncovered - Si
7. return C
```

**Approximation Ratio:**
This greedy algorithm does not guarantee the absolute minimum number of subsets. However, it is mathematically proven to have an approximation ratio of `H(d)`, where `d` is the size of the largest subset, and `H(n)` is the n-th harmonic number (roughly `ln(n)`).
This means if the true optimal solution requires `OPT` subsets, the greedy algorithm will pick at most `OPT * ln(|U|)` subsets. While not perfect, it runs very fast (in polynomial time) and gives a bound on how "bad" the answer can be.

---

## Q6: Working modulo q = 11, how many spurious hits does the Rabin-Karp matcher encounter in the text T = 31415926 when looking for the pattern P = 26. (10 Marks Context)

**Answer:**

**Rabin-Karp Matcher Spurious Hits:**
In the Rabin-Karp algorithm, a "hit" occurs when the hash value of a substring in the text matches the hash value of the pattern.
A **"spurious hit"** is a false positive: the hash values match, but the actual string characters do not match.

**Given:**
Text `T = 31415926`
Pattern `P = 26`
Modulo `q = 11`
Since the text and pattern are digits, our alphabet size `d = 10`.

**Step 1: Calculate the hash of Pattern P:**
Hash(P) = P mod q = 26 mod 11 = **4**

**Step 2: Calculate the hash of every window of length 2 in Text T:**
We will slide a window of size 2 across `T` and calculate its value modulo 11.
*   **Window 1 ("31"):** 31 mod 11 = **9** (Mismatch: 9 != 4)
*   **Window 2 ("14"):** 14 mod 11 = **3** (Mismatch: 3 != 4)
*   **Window 3 ("41"):** 41 mod 11 = **8** (Mismatch: 8 != 4)
*   **Window 4 ("15"):** 15 mod 11 = **4** (Hash Match: 4 == 4!)
    *   *Check characters:* "15" != "26". This is a **Spurious Hit**.
*   **Window 5 ("59"):** 59 mod 11 = **4** (Hash Match: 4 == 4!)
    *   *Check characters:* "59" != "26". This is a **Spurious Hit**.
*   **Window 6 ("92"):** 92 mod 11 = **4** (Hash Match: 4 == 4!)
    *   *Check characters:* "92" != "26". This is a **Spurious Hit**.
*   **Window 7 ("26"):** 26 mod 11 = **4** (Hash Match: 4 == 4!)
    *   *Check characters:* "26" == "26". This is an **Exact Match** (Valid hit).

**Result:**
The Rabin-Karp matcher encounters exactly **3 spurious hits** (at substrings "15", "59", and "92") before finding the exact match at "26".

---

## Q7: Suggest an approximation algorithm for TSP. Assume that the cost function satisfies the triangle inequality. (10 Marks)

**Answer:**

**TSP with Triangle Inequality:**
The general Travelling Salesman Problem cannot be approximated within any constant factor unless P = NP. However, if the cost function (distances) satisfies the **triangle inequality** (i.e., for any three cities A, B, C, the distance `dist(A,C) <= dist(A,B) + dist(B,C)`), there is a simple 2-approximation algorithm.
This means the path found will be at most twice the length of the absolute shortest optimal path.

**Approximation Algorithm (Based on Minimum Spanning Tree):**

```text
APPROX-TSP-TOUR(G, c) // Graph G, cost function c
1. Select an arbitrary vertex r as a "root" vertex.
2. Compute a Minimum Spanning Tree (MST) T for G from root r using Prim's algorithm.
3. Let L be the list of vertices visited in a preorder tree walk of T.
4. Return the Hamiltonian cycle H that visits the vertices in the order L.
```

**Step-by-step Explanation & Example:**
1.  **Find MST:** We first find a Minimum Spanning Tree of the graph. We know the cost of the MST is less than or equal to the cost of the optimal TSP tour (because removing any edge from the optimal tour leaves a spanning tree).
2.  **Preorder Walk:** We traverse the MST using a Depth-First Search (preorder walk). This creates a path that visits every node, but it will traverse some edges twice (going down the tree and backing up).
    *   Cost of this full walk = `2 * Cost(MST)`.
3.  **Shortcut (Bypass):** The walk from step 2 is not a valid TSP tour because it visits cities multiple times. We create the final tour by traversing the list and skipping (shortcutting) any city we have already visited, going directly to the next unvisited city in the preorder traversal.
4.  **Triangle Inequality Guarantee:** Because of the triangle inequality, taking a direct shortcut between two cities is never longer than going through an intermediate city. Therefore, shortcutting the duplicate visits only *decreases* (or maintains) the total cost.
5.  **Conclusion:** The final tour cost is less than or equal to `2 * Cost(MST)`, which is `<= 2 * Cost(Optimal Tour)`.

**Example:**
*   **Graph:** Cities A, B, C, D on a 2D plane (Euclidean distance satisfies triangle inequality).
*   **MST:** Suppose MST edges are (A,B), (B,C), (B,D). Root is A.
*   **Preorder Walk of MST:** A -> B -> C -> (back to B) -> D -> (back to B) -> (back to A).
*   **Shortcut to Form Cycle:**
    *   Start A.
    *   Next is B. Path: A->B
    *   Next is C. Path: A->B->C
    *   Next in walk is B (already visited, skip!).
    *   Next is D. Path: A->B->C->D
    *   End: return to start A. Final Cycle: **A->B->C->D->A**.
This cycle is guaranteed to be within a factor of 2 of the optimal.