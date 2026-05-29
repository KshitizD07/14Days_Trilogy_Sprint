# Module 4: Error Handling and Optimization - Compiler Design Solutions

This document contains detailed solutions to previous year questions (PYQs) for Module 4 of the Compiler Design syllabus.

---

## 1. List the methods of error recovery.

When a compiler encounters an error during parsing, it doesn't just stop. It attempts to "recover" so it can continue checking the rest of the code for further errors. The main methods are:

1.  **Panic-Mode Recovery:** The simplest and most common method. When an error is detected, the parser discards input symbols one by one until it finds a "synchronizing token" (like a semicolon `;` or a closing brace `}`). This allows the parser to resume at a clear boundary.
2.  **Phrase-Level Recovery:** The parser performs a local correction on the remaining input. For example, it might replace a comma with a semicolon or insert a missing symbol. This allows the parser to continue without discarding large chunks of code, but it's risky as a wrong correction can lead to "cascading errors."
3.  **Error Productions:** If the compiler designer knows common mistakes (like using `=` instead of `==` in an `if` statement), they can add specific "error rules" to the grammar that match these mistakes. When an error production is triggered, the parser generates a specific diagnostic message.
4.  **Global Least-Cost Recovery:** This is a theoretical approach where the compiler finds the minimum number of changes (insertions, deletions, or substitutions) needed to transform the erroneous string into a valid one. It is computationally expensive and rarely used in practice.

---

## 2. Give various methods of loop optimization.

Loops are often the most executed parts of a program, making them prime targets for optimization.

1.  **Code Motion (Loop Invariant Computation):** If a calculation inside a loop produces the same result on every iteration, it is "moved" outside the loop (to the loop header).
    *Example:* `while(i < n) { x = y + z; a[i] = x * i; }` $\to$ `x = y + z; while(i < n) { a[i] = x * i; }`
2.  **Induction Variable Elimination:** If several variables change in a locked-step fashion within a loop (induction variables), the compiler can often eliminate some of them to reduce overhead.
3.  **Strength Reduction:** Replacing expensive operations (like multiplication) with cheaper ones (like addition).
    *Example:* If `j = i * 4` inside a loop where `i` increases by 1, replace it with `j = j + 4`.
4.  **Loop Unrolling:** Replicating the loop body multiple times to reduce the overhead of the loop control logic (testing the condition and jumping).
5.  **Loop Jamming (Fusion):** Combining two loops that iterate over the same range into a single loop.

---

## 3. What is DAG in code optimization? Construct DAG for `P = Q * -C + (a + b) + (a + b) * D`.

### DAG (Directed Acyclic Graph)
A DAG is a data structure used to represent the flow of data within a **Basic Block**. Unlike a syntax tree, a DAG eliminates common sub-expressions by allowing a node to have multiple parents if its value is reused.

### Construction for `P = Q * -C + (a + b) + (a + b) * D`
1.  **Intermediate Code (TAC):**
    - `t1 = -C`
    - `t2 = Q * t1`
    - `t3 = a + b`
    - `t4 = t2 + t3`
    - `t5 = t3 * D` (Reuse `t3`)
    - `P = t4 + t5`

2.  **DAG Structure:**
    - Leaf nodes: `Q`, `C`, `a`, `b`, `D`.
    - Node `n1`: `uminus` on `C` (gives `-C`).
    - Node `n2`: `*` on `Q` and `n1` (gives `Q * -C`).
    - Node `n3`: `+` on `a` and `b` (gives `a + b`).
    - Node `n4`: `+` on `n2` and `n3` (gives `Q * -C + (a + b)`).
    - Node `n5`: `*` on `n3` and `D` (gives `(a + b) * D`).
    - Node `n6`: `+` on `n4` and `n5` (gives the final result).
    - Label `P` on node `n6`.

*Note: The key optimization here is that `a + b` is only computed once and its node `n3` is reused by both `n4` and `n5`.*

---

## 4. Explain Peephole optimization and its characteristics.

**Peephole Optimization** is a local optimization technique that examines a short sequence of target instructions (a "peephole") and replaces them with a more efficient sequence.

### Characteristics
-   **Local Scope:** Only looks at a few instructions at a time (usually 2 to 5).
-   **Redundant-Instruction Elimination:** Removes instructions like `STORE x; LOAD x;`.
-   **Flow-of-Control Optimization:** Replaces a jump to another jump with a direct jump.
-   **Algebraic Simplification:** Replaces instructions like `ADD R1, R1, #0` or `MUL R1, R1, #1` with nothing.
-   **Strength Reduction:** Replaces `MUL R1, R1, #2` with `SHL R1, R1, #1` (shift left).
-   **Use of Machine Idioms:** Uses specialized hardware instructions that perform multiple operations at once (e.g., auto-increment addressing).

---

## 5. Why is loop optimization more important than other code optimizations?

Loop optimization is prioritized because of the **90/10 rule** in software engineering: typically, 90% of a program's execution time is spent in just 10% of the code, and that 10% is almost always inside loops.

-   **Multiplicative Effect:** An optimization that saves 1 microsecond in a basic block might be negligible. But if that block is inside a loop that runs 1 million times, the optimization saves 1 entire second.
-   **Data Locality:** Loops often process large arrays. Optimizations like "Loop Interchange" can improve cache performance, which is often a bigger bottleneck than CPU speed.
-   **Frequency of Occurrence:** In scientific computing and data processing, nested loops are the core of the application. Optimizing them is the difference between a program that takes minutes to run and one that takes hours.

---

## 8. Write the algorithm for partitioning a sequence of three-address instructions into basic blocks.

A **Basic Block** is a sequence of instructions with exactly one entry point (the first instruction) and one exit point (the last instruction), with no internal branches.

### Algorithm
1.  **Identify Leaders:** Find the set of "leader" instructions. An instruction is a leader if:
    -   It is the very first instruction in the code.
    -   It is the target of a conditional or unconditional `goto`.
    -   It immediately follows a conditional or unconditional `goto`.
2.  **Form Blocks:** For each leader, its basic block consists of the leader itself and all subsequent instructions until (but not including) the next leader or the end of the program.

---

## 9. Explain (i) Lexical phase errors, (ii) Syntactic phase errors.

### (i) Lexical Phase Errors
These occur during scanning when the input characters do not match the patterns for any valid token.
-   **Examples:**
    -   Appearance of an illegal character (e.g., `@` in a language that doesn't use it).
    -   Malformed identifiers or numeric literals (e.g., `123variable`).
    -   Unterminated string literals.
-   **Recovery:** Usually involves skipping the current character and trying to find the next valid token.

### (ii) Syntactic Phase Errors
These occur during parsing when the sequence of tokens does not follow the grammar rules of the language.
-   **Examples:**
    -   Missing semicolon or closing brace.
    -   Invalid expression structure (e.g., `if (a < b) + 5`).
    -   Wrong number of arguments in a function call.
-   **Recovery:** Uses methods like panic-mode recovery or phrase-level correction to reach a stable state and continue parsing.
