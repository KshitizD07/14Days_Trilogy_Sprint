# Extra Questions (DAA)

*This file will contain answers to the extra questions asked during the study sprint.*

---

## Q1: Explain in detail the following algorithmic paradigms: Dynamic Programming, Greedy Technique, Branch and Bound, Divide and Conquer, and Backtracking. (10 Marks)

**Answer:**

These five algorithmic paradigms are fundamental strategies used to design algorithms for solving complex computational problems, particularly optimization problems.

### 1. Divide and Conquer
**Concept:**
Divide and Conquer is a top-down approach that solves a problem by breaking it down into smaller, strictly independent subproblems of the same type. It solves these subproblems recursively and then combines their solutions to form the solution to the original problem.

**Core Mechanisms (The 3 Steps):**
*   **Divide:** Partition the problem into `k` smaller subproblems (often `k=2`).
*   **Conquer:** Solve the subproblems recursively. If the subproblem size is small enough (base case), solve it directly.
*   **Combine:** Merge the solutions of the subproblems to produce the final answer.

**Characteristics:**
*   Subproblems must be non-overlapping (independent). If they overlap, this approach does redundant work.
*   Usually implemented using recursion.
*   Time complexity is often analyzed using Recurrence Relations and the Master Theorem.

**Examples:**
*   **Merge Sort:** Divides array in half, sorts halves, merges them. (Time: $O(n \log n)$)
*   **Quick Sort:** Partitions array around a pivot, sorts partitions.
*   **Binary Search:** Discards half the search space at each step.

---

### 2. Greedy Technique
**Concept:**
The Greedy approach builds a solution piece by piece, always choosing the next piece that offers the most immediate and obvious benefit. It makes the "locally optimal choice" at each stage with the hope that these local optimums will lead to a "globally optimal solution."

**Core Mechanisms:**
*   It never reconsiders its choices; once a decision is made, it is final.
*   It operates top-down, making a sequence of greedy choices to reduce the problem size.
*   For a greedy algorithm to yield an optimal solution, the problem must exhibit two properties:
    1.  **Greedy Choice Property:** A global optimum can be arrived at by selecting a local optimum.
    2.  **Optimal Substructure:** An optimal solution to the problem contains optimal solutions to subproblems.

**Characteristics:**
*   Usually very fast, simple to design, and easy to implement.
*   Highly space-efficient (rarely requires auxiliary memory tables).
*   **Drawback:** It does not guarantee a globally optimal solution for all problems (e.g., it fails on the 0/1 Knapsack problem).

**Examples:**
*   **Fractional Knapsack:** Sort items by value/weight ratio and greedily take the highest ratio.
*   **Prim's and Kruskal's Algorithms:** For Minimum Spanning Trees.
*   **Dijkstra's Algorithm:** For Single-Source Shortest Paths.
*   **Huffman Coding:** For data compression.

---

### 3. Dynamic Programming (DP)
**Concept:**
Dynamic Programming is a bottom-up (tabulation) or top-down (memoization) technique used for optimization problems where subproblems overlap. Instead of solving the same subproblem multiple times (like naive Divide and Conquer would), DP solves each subproblem only once and stores the result in a table (usually an array or matrix).

**Core Mechanisms:**
*   Like Greedy, it requires the problem to have **Optimal Substructure**.
*   Crucially, it requires **Overlapping Subproblems** (the space of subproblems must be small, and a recursive algorithm revisits the same problems repeatedly).
*   It examines all possible sequences of decisions before making a final choice, guaranteeing a globally optimal solution.

**Characteristics:**
*   Slower than Greedy algorithms because it exhaustively searches the state space (though much faster than naive recursion).
*   Requires extra memory (Space Complexity is often $O(n)$ or $O(n^2)$) to maintain the lookup table.
*   Guarantees the optimal solution if the principle of optimality holds.

**Examples:**
*   **0/1 Knapsack Problem:** Build a table considering weights and item limits.
*   **Floyd-Warshall Algorithm:** All-pairs shortest path.
*   **Longest Common Subsequence (LCS).**
*   **Matrix Chain Multiplication.**

---

### 4. Backtracking
**Concept:**
Backtracking is a systematic way to iterate through all the possible configurations of a search space. It builds candidates for the solutions incrementally. If it determines that a partial candidate `c` cannot possibly be completed to a valid solution, it abandons `c` ("backtracks" to the previous step) and tries the next available option.

**Core Mechanisms:**
*   Conceptually, it explores a "State Space Tree" using a Depth-First Search (DFS) approach.
*   It uses bounding/pruning conditions to kill branches of the tree that violate problem constraints.

**Characteristics:**
*   Used primarily for finding *all* solutions or checking if *any* solution exists (Decision/Constraint Satisfaction Problems), rather than strict optimization.
*   Time complexity is typically exponential ($O(2^n)$ or $O(n!)$) in the worst case, but pruning makes it feasible for small inputs.

**Examples:**
*   **N-Queens Problem:** Placing queens safely on a board.
*   **Graph Coloring Problem:** Assigning colors without adjacent conflicts.
*   **Sum of Subsets:** Finding subsets that sum to a specific target.
*   **Hamiltonian Circuit:** Finding a path that visits every vertex exactly once.

---

### 5. Branch and Bound
**Concept:**
Branch and Bound is an algorithm design paradigm for discrete and combinatorial optimization problems. Like backtracking, it explores a state space tree, but it is specifically designed to find the *optimal* solution (minimum or maximum) rather than just any valid solution.

**Core Mechanisms:**
*   **Branching:** Dividing the problem into subproblems (child nodes).
*   **Bounding:** Calculating a lower bound (for minimization) or upper bound (for maximization) on the best possible solution that can be found in a given subtree.
*   **Pruning:** If the bound of a node is worse than the best solution found so far (the "incumbent"), that entire subtree is discarded.
*   It usually employs a Breadth-First Search (FIFO queue) or a Least-Cost Search (Priority Queue/Min-Heap) to decide which live node to expand next.

**Characteristics:**
*   "Intelligent" exhaustive search.
*   Primarily used for NP-Hard optimization problems where DP or Greedy fail.
*   Requires a heuristic to calculate the bounds efficiently.

**Examples:**
*   **Travelling Salesman Problem (TSP):** Finding the absolute shortest route.
*   **0/1 Knapsack (Optimization version):** Using fractional knapsack as a bounding function to prune paths.
*   **Assignment Problem.**
