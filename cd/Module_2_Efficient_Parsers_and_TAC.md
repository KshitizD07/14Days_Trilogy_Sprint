# Module 2: Efficient Parsers and Intermediate Code - Compiler Design Solutions

This document contains detailed solutions to previous year questions (PYQs) for Module 2 of the Compiler Design syllabus.

---

## 1. Construct the LR(0) canonical collection of items and the parsing table for the grammar: [S'->S, S->cB|ccA, A->cA|a, B->ccB|b].

### Augmented Grammar
0. `S' -> S`
1. `S -> c B`
2. `S -> c c A`
3. `A -> c A`
4. `A -> a`
5. `B -> c c B`
6. `B -> b`

### Canonical Collection of LR(0) Items

- **I0:** 
  `S' -> .S`
  `S -> .cB`
  `S -> .ccA`
- **I1:** (GOTO I0, S)
  `S' -> S.`
- **I2:** (GOTO I0, c)
  `S -> c.B`
  `S -> c.cA`
  `B -> .ccB`
  `B -> .b`
- **I3:** (GOTO I2, B)
  `S -> cB.`
- **I4:** (GOTO I2, c)
  `S -> cc.A`
  `B -> c.cB`
  `A -> .cA`
  `A -> .a`
- **I5:** (GOTO I2, b)
  `B -> b.`
- **I6:** (GOTO I4, A)
  `S -> ccA.`
- **I7:** (GOTO I4, c)
  `B -> cc.B`
  `A -> c.A`
  `B -> .ccB`
  `B -> .b`
  `A -> .cA`
  `A -> .a`
- **I8:** (GOTO I4, a)
  `A -> a.`
- **I9:** (GOTO I7, B)
  `B -> ccB.`
- **I10:** (GOTO I7, A)
  `A -> cA.`
- **I11:** (GOTO I7, c)
  `B -> c.cB`
  `A -> c.A`
  `B -> .ccB`
  `B -> .b`
  `A -> .cA`
  `A -> .a`
- **I12:** (GOTO I11, c)
  `B -> cc.B`
  `B -> c.cB`
  `A -> c.A`
  `B -> .ccB`
  `B -> .b`
  `A -> .cA`
  `A -> .a`

### LR(0) Parsing Table

| State | c | b | a | $ | S | B | A |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **0** | S2 | | | | 1 | | |
| **1** | | | | Acc | | | |
| **2** | S4 | S5 | | | | 3 | |
| **3** | R1 | R1 | R1 | R1 | | | |
| **4** | S7 | | S8 | | | | 6 |
| **5** | R6 | R6 | R6 | R6 | | | |
| **6** | R2 | R2 | R2 | R2 | | | |
| **7** | S11 | S5 | S8 | | | 9 | 10 |
| **8** | R4 | R4 | R4 | R4 | | | |
| **9** | R5 | R5 | R5 | R5 | | | |
| **10**| R3 | R3 | R3 | R3 | | | |
| **11**| S12 | S5 | S8 | | | | 10 |
| **12**| S12 | S5 | S8 | | | 9 | 10 |

---

## 2. What is Three-Address Code (TAC)? Explain Assignment, Unary, Boolean, and Control Flow statements with examples.

**Three-Address Code (TAC)** is an intermediate representation used by compilers where each instruction has at most three operands: usually two sources and one destination. It is a linearized representation of a syntax tree.

### Types of TAC Statements

1.  **Assignment Statements:**
    Perform binary operations and store the result in a temporary variable.
    *General Form:* `x = y op z`
    *Example:* `t1 = a + b`

2.  **Unary Operation Statements:**
    Perform an operation on a single operand.
    *General Form:* `x = op y`
    *Example:* `t2 = -c` (Unary minus) or `t3 = not d` (Logical negation).

3.  **Boolean and Relational Statements:**
    Used for conditional branching based on the comparison of two values.
    *General Form:* `if x relop y goto L`
    *Example:* `if a < b goto 105`

4.  **Control Flow (Unconditional) Statements:**
    Used for direct jumps to a specific label or address.
    *General Form:* `goto L`
    *Example:* `goto 200`

5.  **Procedure Calls and Parameters:**
    *   `param x`
    *   `call p, n` (Call procedure `p` with `n` parameters)
    *   `return y`

---

## 3. Define Backpatching. Explain the backpatching scheme for Boolean expressions and flow-of-control statements in detail.

**Backpatching** is a technique used in one-pass compilers to handle the generation of jump targets when the address of the target is not yet known. 

### Why is it needed?
In a single pass, when the compiler encounters an `if` statement, it generates a `goto` to the "else" block or the "exit" block. However, it hasn't parsed those blocks yet, so it doesn't know their starting addresses.

### How it Works
1.  **Lists of Jumps:** The compiler maintains lists of jump instructions that point to the same (yet unknown) location.
    -   `truelist`: Instructions that jump if the expression is true.
    -   `falselist`: Instructions that jump if the expression is false.
    -   `nextlist`: Instructions that jump to the statement immediately following the current construct.
2.  **Generating Jumps with Placeholders:** When a jump is generated, the target address is left empty (e.g., `if a < b goto _`).
3.  **Merging Lists:** As sub-expressions are combined (e.g., using `OR` or `AND`), their lists are merged using a `merge()` function.
4.  **Backpatching:** When the target label is finally defined (the address is known), a `backpatch(list, address)` function is called. This function iterates through the list of instructions and fills in the blank target field with the actual address.

---

## 4. Explain Quadruples, Triples, and Indirect Triples for: `a = b * -c + b * -c`.

### Three-Address Code (TAC)
1. `t1 = minus c`
2. `t2 = b * t1`
3. `t3 = minus c`
4. `t4 = b * t3`
5. `t5 = t2 + t4`
6. `a = t5`

### 1. Quadruples
A quadruple has four fields: `op`, `arg1`, `arg2`, and `result`.
| Index | op | arg1 | arg2 | result |
| :--- | :--- | :--- | :--- | :--- |
| (0) | uminus | c | | t1 |
| (1) | * | b | t1 | t2 |
| (2) | uminus | c | | t3 |
| (3) | * | b | t3 | t4 |
| (4) | + | t2 | t4 | t5 |
| (5) | = | t5 | | a |

### 2. Triples
A triple uses three fields: `op`, `arg1`, and `arg2`. Results are referenced by their index in the table.
| Index | op | arg1 | arg2 |
| :--- | :--- | :--- | :--- |
| (0) | uminus | c | |
| (1) | * | b | (0) |
| (2) | uminus | c | |
| (3) | * | b | (2) |
| (4) | + | (1) | (3) |
| (5) | = | a | (4) |

### 3. Indirect Triples
Indirect triples consist of a pointer array that points to the entries in a triples table. This allows for easier code reordering during optimization without moving the heavy triple structures.
| Execution Order | Triple Index |
| :--- | :--- |
| 100 | (0) |
| 101 | (1) |
| 102 | (2) |
| 103 | (3) |
| 104 | (4) |
| 105 | (5) |

---

## 5. Generate TAC for: `While (a < c or b > d) do If a = 1 then c = a * b + c else a = b - d * c`.

We use labels to represent control flow. Note the use of "short-circuit" evaluation for the `or` condition.

```text
L_start:
    if a < c goto L_then_block   // Short-circuit: if first part is true, enter loop
    if b > d goto L_then_block   // If second part is true, enter loop
    goto L_exit                  // Both false, exit while loop

L_then_block:
    if a == 1 goto L_if_true
    goto L_if_false

L_if_true:
    t1 = a * b
    t2 = t1 + c
    c = t2
    goto L_start                 // Back to while condition

L_if_false:
    t3 = d * c
    t4 = b - t3
    a = t4
    goto L_start                 // Back to while condition

L_exit:
    ...
```

---

## 6. Differentiate Parse Tree vs Annotated Parse Tree.

### Parse Tree
-   A graphical representation of the derivation of a string from the start symbol of a grammar.
-   It only shows the **syntactic structure** (how terminals and non-terminals relate).
-   Interior nodes are non-terminals; leaves are terminals.
-   *Example:* A tree showing that `3 + 4` follows the rule $E \to E + T$.

### Annotated Parse Tree
-   A parse tree that has been augmented with **attribute values** at each node.
-   Attributes can represent values (like the result of `3+4`), types (integer vs float), or locations in memory.
-   It is used in **Syntax-Directed Translation (SDT)** to perform semantic analysis and code generation.
-   *Example:* A node for `+` might have an attribute `val = 7`, and the `id` nodes might have attributes pointing to their entries in the symbol table.

---

## 9. What is Handle Pruning? Explain its role in shift-reduce parsing. Indicate the handles in `a a + a *` using [S->SS+|SS*|a].

### Handle Pruning
In bottom-up parsing, a **handle** is a substring that matches the right-hand side of a production, and whose reduction to the non-terminal on the left-hand side represents one step of the **reverse of a rightmost derivation**.

**Handle Pruning** is the process of finding a handle in the current sentential form and replacing it with the corresponding non-terminal. This process is repeated until only the start symbol remains.

### Role in Shift-Reduce Parsing
A shift-reduce parser maintains a stack. It "shifts" input symbols onto the stack until the top of the stack contains a handle. Then it "reduces" the handle to a non-terminal.

### Handles in `a a + a *` for grammar [S -> SS+ | SS* | a]
We work backwards from the input to the start symbol `S`:

1.  Input: `a a + a *`
    -   Handle: the first `a`.
    -   Reduction: `S a + a *` (using $S \to a$)
2.  Sentential Form: `S a + a *`
    -   Handle: the second `a`.
    -   Reduction: `S S + a *` (using $S \to a$)
3.  Sentential Form: `S S + a *`
    -   Handle: `S S +`.
    -   Reduction: `S a *` (using $S \to SS+$)
4.  Sentential Form: `S a *`
    -   Handle: `a`.
    -   Reduction: `S S *` (using $S \to a$)
5.  Sentential Form: `S S *`
    -   Handle: `S S *`.
    -   Reduction: `S` (using $S \to SS*$)

The sequence of handles pruned: `a`, `a`, `SS+`, `a`, `SS*`.

---

## 10. Represent `-(a * b) + (c + d) - (a + b + c + d)` in Quadruples, Triples, and Indirect Triples.

### 1. Quadruples
| Index | op | arg1 | arg2 | result |
| :--- | :--- | :--- | :--- | :--- |
| (0) | * | a | b | t1 |
| (1) | uminus | t1 | | t2 |
| (2) | + | c | d | t3 |
| (3) | + | t2 | t3 | t4 |
| (4) | + | a | b | t5 |
| (5) | + | t5 | c | t6 |
| (6) | + | t6 | d | t7 |
| (7) | - | t4 | t7 | t8 |

### 2. Triples
| Index | op | arg1 | arg2 |
| :--- | :--- | :--- | :--- |
| (0) | * | a | b |
| (1) | uminus | (0) | |
| (2) | + | c | d |
| (3) | + | (1) | (2) |
| (4) | + | a | b |
| (5) | + | (4) | c |
| (6) | + | (5) | d |
| (7) | - | (3) | (6) |

### 3. Indirect Triples
| Order | Index |
| :--- | :--- |
| 100 | (0) |
| 101 | (1) |
| 102 | (2) |
| 103 | (3) |
| 104 | (4) |
| 105 | (5) |
| 106 | (6) |
| 107 | (7) |
