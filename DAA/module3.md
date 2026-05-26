# Module 3: Dynamic Programming, Backtracking & Branch and Bound

## Q1: Describe the Dynamic 0/1 Knapsack Problem. Find an optimal solution for the dynamic programming 0/1 knapsack instance for n=3, m=6, profits are (p1, p2, p3) = (1, 2, 5), weights are (w1, w2, w3) = (2, 3, 4). (7.5 Marks / 10 Marks Context)

**Answer:**

**Dynamic 0/1 Knapsack Problem Description:**
You are given `n` items, each with a weight `w_i` and a profit (or value) `p_i`. You have a knapsack with a maximum weight capacity `W` (or `m`). The objective is to select a subset of items to put into the knapsack such that the total weight does not exceed `W`, and the total profit is maximized.
It's called "0/1" because you must either entirely accept (1) or entirely reject (0) an item; you cannot take fractions of an item (unlike the Fractional Knapsack solved via Greedy).
Dynamic Programming solves this by building a 2D table `V[i][w]`, representing the maximum value that can be attained with weight less than or equal to `w` using items up to `i`.

**The DP Recurrence Relation:**
*   `V[i][w] = 0` if `i=0` or `w=0` (Base case)
*   `V[i][w] = V[i-1][w]` if `w_i > w` (Item `i` is too heavy, skip it)
*   `V[i][w] = max(V[i-1][w], V[i-1][w - w_i] + p_i)` if `w_i <= w` (Max of excluding vs. including item `i`)

**Solving the given instance:**
`n` = 3 (number of items)
`W` (capacity `m`) = 6
Profits `p` = (1, 2, 5)
Weights `w` = (2, 3, 4)

We construct a table `V[0..3][0..6]`. Rows are items (0 to 3), columns are weights (0 to 6).

| i (Item) \ w (Cap) | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **0 (None)** | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| **1 (w=2, p=1)** | 0 | 0 | **1** | 1 | 1 | 1 | 1 |
| **2 (w=3, p=2)** | 0 | 0 | 1 | **2** | 2 | **3** | 3 |
| **3 (w=4, p=5)** | 0 | 0 | 1 | 2 | **5** | 5 | **6** |

**Step-by-step Calculation (Highlights):**
*   **Row 1 (Item 1, w=2, p=1):** For capacities `w < 2`, value is 0. For `w >= 2`, we can include it. `V[1][2] = max(V[0][2], V[0][0]+1) = max(0, 1) = 1`.
*   **Row 2 (Item 2, w=3, p=2):**
    *   `w=2`: Can't include item 2. Take `V[1][2] = 1`.
    *   `w=3`: `max(V[1][3], V[1][0]+2) = max(1, 2) = 2`.
    *   `w=5`: `max(V[1][5], V[1][2]+2) = max(1, 1+2) = 3`.
*   **Row 3 (Item 3, w=4, p=5):**
    *   `w=3`: Can't include item 3. Take `V[2][3] = 2`.
    *   `w=4`: `max(V[2][4], V[2][0]+5) = max(2, 5) = 5`.
    *   `w=6`: `max(V[2][6], V[2][2]+5) = max(3, 1+5) = 6`.

**Result:** The optimal (maximum) profit is **6**, found at `V[3][6]`.
To find the items, trace back from `V[3][6]`:
- Is `V[3][6] != V[2][6]`? (6 != 3). Yes, so **Item 3 is included**. Remaining capacity = 6 - 4 = 2.
- Move to `V[2][2]`. Is `V[2][2] != V[1][2]`? (1 != 1). No, Item 2 is excluded.
- Move to `V[1][2]`. Is `V[1][2] != V[0][2]`? (1 != 0). Yes, so **Item 1 is included**.
**Items selected:** Item 1 and Item 3.

---

## Q2: Explain Floyd warshell with an algorithm. Find out all pair shortest path using Floyd warshell for given graph. (10 Marks)
*(Assuming a generic 4-node graph based on the syllabus context, as drawing specific matrices is difficult. I will focus on the algorithm and matrix operation).*

**Answer:**

**Floyd-Warshall Algorithm:**
The Floyd-Warshall algorithm is a Dynamic Programming approach used to find the shortest paths between ALL pairs of vertices in a weighted graph. It works for both directed and undirected graphs, and it can handle negative edge weights (provided there are no negative-weight cycles).

**Concept:**
It considers vertices sequentially as intermediate points. Let `D_ij^(k)` be the shortest path from vertex `i` to vertex `j` using only vertices from `{1, 2, ..., k}` as intermediate nodes.
The recurrence relation is:
`D_ij^(k) = min( D_ij^(k-1) , D_ik^(k-1) + D_kj^(k-1) )`
This means the shortest path either does not go through vertex `k`, or it goes from `i` to `k` and then from `k` to `j`.

**Algorithm:**
```text
FLOYD-WARSHALL(W) // W is the n x n weight matrix
1. n = W.rows
2. D^(0) = W
3. for k = 1 to n          // k is the intermediate vertex
4.     let D^(k) be a new n x n matrix
5.     for i = 1 to n      // i is the source vertex
6.         for j = 1 to n  // j is the destination vertex
7.             D^(k)[i][j] = min(D^(k-1)[i][j], D^(k-1)[i][k] + D^(k-1)[k][j])
8.     D^(k-1) = D^(k)     // Can be done in-place to save memory
9. return D^(n)
```

**Solving Matrix Operations (Conceptual Example for a 4-node graph):**
Given an initial adjacency weight matrix `D0` where `D0[i][j]` is the weight of edge `i->j` (or infinity if no edge).

*   **Step k=1:** We check if going through node 1 makes paths shorter. We compare `D[i][j]` with `D[i][1] + D[1][j]`. Row 1 and Column 1 remain unchanged.
*   **Step k=2:** We check if going through node 2 makes paths shorter. Compare `D[i][j]` with `D[i][2] + D[2][j]`. Row 2 and Column 2 remain unchanged.
*   ... repeat up to `k=n`.
The final matrix `D(n)` will contain the shortest distances between all pairs of nodes.

---

## Q3: Define backtracking? Solve N-Queens problem for n=4 showing backtracking steps. (7.5 Marks / 10 Marks Context)

**Answer:**

**Backtracking Definition:**
Backtracking is an algorithmic technique for solving problems recursively by trying to build a solution incrementally, one piece at a time. If it determines that the current partial solution cannot possibly be completed to form a valid solution, it abandons it ("backtracks" to the previous step) and tries the next available option. It systematically explores the "state space tree" of the problem.

**N-Queens Problem (n=4):**
The goal is to place 4 queens on a 4x4 chessboard such that no two queens attack each other (meaning no two queens are in the same row, same column, or same diagonal).
We place queens column by column.

**Backtracking Steps (State Space Tree trace for n=4):**
Let `(row, column)` denote the position.
*   **Col 1:**
    *   Place Q1 at (1, 1). Valid.
*   **Col 2:**
    *   Try (1, 2). Attacks Q1 (row).
    *   Try (2, 2). Attacks Q1 (diagonal).
    *   Try (3, 2). Valid. Place Q2 at (3, 2).
*   **Col 3:**
    *   Try (1, 3). Attacks Q1 (row).
    *   Try (2, 3). Attacks Q1 (diagonal) & Q2 (diagonal).
    *   Try (3, 3). Attacks Q2 (row).
    *   Try (4, 3). Attacks Q2 (diagonal).
    *   *Dead end! No safe spot in Col 3.* **BACKTRACK!**
*   **Col 2 (Backtracked):**
    *   Remove Q2 from (3, 2).
    *   Try next option: Place Q2 at (4, 2). Valid.
*   **Col 3 (Attempt 2):**
    *   Try (1, 3). Attacks Q1 (row).
    *   Try (2, 3). Valid. Place Q3 at (2, 3).
*   **Col 4:**
    *   Try (1, 4). Attacks Q1.
    *   Try (2, 4). Attacks Q3.
    *   Try (3, 4). Attacks Q2 & Q3 (diagonals).
    *   Try (4, 4). Attacks Q2.
    *   *Dead end!* **BACKTRACK!**
*   **Col 3 (Backtracked):**
    *   Remove Q3 from (2, 3). No more options in Col 3. **BACKTRACK!**
*   **Col 2 (Backtracked):**
    *   Remove Q2 from (4, 2). No more options in Col 2. **BACKTRACK!**
*   **Col 1 (Backtracked):**
    *   Remove Q1 from (1, 1).
    *   Try next option: Place Q1 at (2, 1).
*   **Fast Forward Path to Solution:**
    *   Q1 at (2, 1).
    *   Col 2: Try options. (4, 2) is valid. Q2 at (4, 2).
    *   Col 3: Try options. (1, 3) is valid. Q3 at (1, 3).
    *   Col 4: Try options. (3, 4) is valid. Q4 at (3, 4).
    *   **Solution Found!** Positions: (2,1), (4,2), (1,3), (3,4).

---

## Q4: What is sum of subset problem? Draw a state space tree for Sum of subset problem using backtracking? Let n=6, m=30 and w [1:6] = {5, 10, 12, 13, 15, 18} (10 Marks)

**Answer:**

**Sum of Subset Problem:**
Given a set of non-negative integers `S = {w1, w2, ..., wn}` and a target sum `m`, the problem is to find all possible subsets of `S` whose elements sum exactly to `m`. It is a classic NP-Complete problem solved using Backtracking.

**Backtracking Strategy:**
We sort the set `S` in increasing order (though not strictly necessary, it helps pruning). We construct a state space tree where each level `i` represents the decision to either include or exclude element `wi`.
We prune a node (backtrack) if:
1.  Current sum + next element > `m` (we overshot the target).
2.  Current sum + sum of all remaining elements < `m` (even if we take everything left, we can't reach the target).

**Given:** `n = 6`, `m = 30`, `w = {5, 10, 12, 13, 15, 18}`

**State Space Tree Generation:**
Let a node be represented as `(Sum_so_far, index_considered)`. Root is `(0, 0)`.
Left child means "Include w[i]", Right child means "Exclude w[i]".

*   **Root:** (0, 0).
*   **Level 1 (Consider 5):**
    *   Inc 5: `(5, 1)`
    *   Exc 5: `(0, 1)`
*   **Level 2 (Consider 10):**
    *   From `(5, 1)` -> Inc 10: `(15, 2)`. Exc 10: `(5, 2)`
    *   From `(0, 1)` -> Inc 10: `(10, 2)`. Exc 10: `(0, 2)`
*   **Tracing a successful path:**
    *   Start: 0. Add 5 -> 5. Add 10 -> 15. Add 15 -> 30.
    *   Path: Include 5, Include 10, Exclude 12, Exclude 13, Include 15. Solution: `{5, 10, 15}`.
*   **Tracing a pruned path:**
    *   Start: 0. Add 5 -> 5. Add 10 -> 15. Add 12 -> 27. Add 13 -> 40.
    *   At sum 40, `40 > 30 (m)`, so this branch is **pruned** (killed). Backtrack to 27, try excluding 13.

*(In an exam, drawing the top 3-4 levels of the binary tree clearly showing the left edge as 'Take' and right edge as 'Don't Take', and explicitly marking a node with an 'X' where pruning occurs based on the conditions, fulfills the drawing requirement).*

---

## Q5: What is travelling salesman problem (TSP)? Find the solution of following TSP using dynamic programming. (10 Marks)
*Matrix given:*
```
0 1 15 6
2 0 7 3
9 6 0 12
10 4 8 0
```

**Answer:**

**Travelling Salesman Problem (TSP):**
Given a set of cities and the distances between every pair of cities, the TSP asks for the shortest possible route that visits every city exactly once and returns to the starting city. It is a well-known NP-Hard problem.

**Dynamic Programming Solution to TSP:**
Let the cities be `{1, 2, 3, 4}`. Let vertex 1 be the start/end point.
We use a table `g(i, S)` which represents the shortest path starting at city `i`, visiting all cities in set `S` exactly once, and returning to city 1.
The recurrence is:
`g(i, S) = min over j in S { Cost(i, j) + g(j, S - {j}) }`
Base case: `g(i, empty set) = Cost(i, 1)` (distance from last city back to start).

**Solving the Matrix:**
Nodes = `{1, 2, 3, 4}`. Start = 1. Remaining set = `{2, 3, 4}`.
We want to find `g(1, {2, 3, 4})`.

*   **Base cases (|S| = 0):**
    `g(2, ø) = c21 = 2`
    `g(3, ø) = c31 = 9`
    `g(4, ø) = c41 = 10`

*   **Subproblems of size 1 (|S| = 1):**
    `g(2, {3}) = c23 + g(3, ø) = 7 + 9 = 16`
    `g(2, {4}) = c24 + g(4, ø) = 3 + 10 = 13`
    `g(3, {2}) = c32 + g(2, ø) = 6 + 2 = 8`
    `g(3, {4}) = c34 + g(4, ø) = 12 + 10 = 22`
    `g(4, {2}) = c42 + g(2, ø) = 4 + 2 = 6`
    `g(4, {3}) = c43 + g(3, ø) = 8 + 9 = 17`

*   **Subproblems of size 2 (|S| = 2):**
    `g(2, {3,4}) = min( c23 + g(3,{4}), c24 + g(4,{3}) ) = min(7+22, 3+17) = min(29, 20) = 20` (Path: 2->4->3->1)
    `g(3, {2,4}) = min( c32 + g(2,{4}), c34 + g(4,{2}) ) = min(6+13, 12+6) = min(19, 18) = 18` (Path: 3->4->2->1)
    `g(4, {2,3}) = min( c42 + g(2,{3}), c43 + g(3,{2}) ) = min(4+16, 8+8) = min(20, 16) = 16` (Path: 4->3->2->1)

*   **Final Problem (|S| = 3):**
    `g(1, {2,3,4}) = min(`
       `c12 + g(2, {3,4})  =>  1 + 20 = 21`
       `c13 + g(3, {2,4})  => 15 + 18 = 33`
       `c14 + g(4, {2,3})  =>  6 + 16 = 22`
    `)`
    Minimum is 21.

**Optimal Route & Cost:**
Minimum cost is **21**.
Tracing back the path that gave 21:
From 1 we went to 2 (cost 1).
For `g(2, {3,4})`, the minimum was via node 4. So, 2->4.
For `g(4, {3})`, the minimum was via node 3. So, 4->3.
From 3 back to start 1. So, 3->1.
Optimal Path: **1 -> 2 -> 4 -> 3 -> 1**
Verification: `1 + 3 + 8 + 9 = 21`.