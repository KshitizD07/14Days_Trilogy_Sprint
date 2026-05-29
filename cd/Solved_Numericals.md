# Solved Numericals and Practical Problems - Compiler Design

This document contains step-by-step solutions to specific numerical and practical problems found in the Compiler Design PYQs that were identified during the final audit.

---

## 1. Construct the LALR(1) parsing items for the grammar: [S->AA, A->aA|b].

### Augmented Grammar
(0) $S' \to S$
(1) $S \to AA$
(2) $A \to aA$
(3) $A \to b$

### LALR(1) Canonical Collection
LALR(1) items are formed by merging LR(1) items that share the same "core" (the LR(0) part).

- **$I_0$**: 
  $[S' \to \cdot S, \$]$
  $[S \to \cdot AA, \$]$
  $[A \to \cdot aA, a/b]$
  $[A \to \cdot b, a/b]$
- **$I_1$**: (GOTO $I_0, S$)
  $[S' \to S \cdot, \$]$
- **$I_2$**: (GOTO $I_0, A$)
  $[S \to A \cdot A, \$]$
  $[A \to \cdot aA, \$]$
  $[A \to \cdot b, \$]$
- **$I_{36}$**: (Merged GOTO $I_0, a$ and $I_2, a$)
  $[A \to a \cdot A, a/b/\$]$
  $[A \to \cdot aA, a/b/\$]$
  $[A \to \cdot b, a/b/\$]$
- **$I_{47}$**: (Merged GOTO $I_0, b$ and $I_2, b$)
  $[A \to b \cdot, a/b/\$]$
- **$I_5$**: (GOTO $I_2, A$)
  $[S \to AA \cdot, \$]$
- **$I_{89}$**: (Merged GOTO $I_{36}, A$)
  $[A \to aA \cdot, a/b/\$]$

---

## 2. Construct the SLR parsing table for: [E -> E+T | T, T -> id].

### LR(0) Canonical Collection
- **$I_0$**: $E' \to \cdot E, E \to \cdot E+T, E \to \cdot T, T \to \cdot id$
- **$I_1$**: $Goto(I_0, E) = [E' \to E \cdot, E \to E \cdot + T]$
- **$I_2$**: $Goto(I_0, T) = [E \to T \cdot]$
- **$I_3$**: $Goto(I_0, id) = [T \to id \cdot]$
- **$I_4$**: $Goto(I_1, +) = [E \to E + \cdot T, T \to \\cdot id]$
- **$I_5$**: $Goto(I_4, T) = [E \to E + T \\cdot]$

### FOLLOW Sets
- $FOLLOW(E) = \{\$, +\}$
- $FOLLOW(T) = \{\$, +\}$

### SLR Parsing Table
| State | id | + | $ | E | T |
| :---: | :---: | :---: | :---: | :---: | :---: |
| **0** | s3 | | | 1 | 2 |
| **1** | | s4 | acc | | |
| **2** | | r2 | r2 | | |
| **3** | | r3 | r3 | | |
| **4** | s3 | | | | 5 |
| **5** | | r1 | r1 | | |

---

## 3. Construct the DAG for: `(a/10 + (b-10)) * (a/10 + (b-10))`.

### Common Sub-expression Identification
The sub-expression `(a/10 + (b-10))` is used twice.

### DAG Nodes
1.  **Leaf(a)**
2.  **Leaf(10)**
3.  **Node(3):** `/` with children 1 and 2 ($a/10$)
4.  **Leaf(b)**
5.  **Node(5):** `-` with children 4 and 2 ($b-10$)
6.  **Node(6):** `+` with children 3 and 5 (result is the common sub-expression)
7.  **Node(7):** `*` with children 6 and 6 (final multiplication)

---

## 4. SDT Trace for input `2 + 3 * 4`.

### Grammar with Semantic Rules
1. $E \to E + T$ {$E.val = E_1.val + T.val$}
2. $E \to T$ {$E.val = T.val$}
3. $T \to T * F$ {$T.val = T_1.val * F.val$}
4. $T \to F$ {$T.val = F.val$}
5. $F \to (E)$ {$F.val = E.val$}
6. $F \to num$ {$F.val = num.val$}

### Trace
1.  **Scan '2':** $F \to 2$ ($F.val=2$) $\to T \to 2$ ($T.val=2$) $\to E \to 2$ ($E.val=2$).
2.  **Scan '3':** $F \to 3$ ($F.val=3$) $\to T \to 3$ ($T.val=3$).
3.  **Scan '4':** $F \to 4$ ($F.val=4$).
4.  **Apply rule 3 ($T \to T * F$):** $T.val = 3 * 4 = 12$.
5.  **Apply rule 1 ($E \to E + T$):** $E.val = 2 + 12 = 14$.
**Final Result:** 14

---

## 5. Basic Blocks Partitioning Example.

### Sequence
1) i = 1
2) j = 1
3) t1 = 10 * i
4) t2 = t1 + j
5) t3 = 8 * t2
6) t4 = t3 - 8
7) a[t4] = 0.0
8) j = j + 1
9) if j <= 10 goto 3
10) i = i + 1
11) if i <= 10 goto 2

### Leaders Identification
1.  **Instruction 1:** First instruction.
2.  **Instruction 2:** Target of `goto 2` (inst 11).
3.  **Instruction 3:** Target of `goto 3` (inst 9).
4.  **Instruction 10:** Follows conditional jump (inst 9).

### Blocks
-   **Block 1:** {1}
-   **Block 2:** {2}
-   **Block 3:** {3, 4, 5, 6, 7, 8, 9}
-   **Block 4:** {10, 11}

---

## 6. Register Allocation (3 Registers) for `(a+b)*(c+d)+e`.

Assume registers R1, R2, R3.

1.  **LD R1, a** (R1 = a)
2.  **LD R2, b** (R2 = b)
3.  **ADD R1, R1, R2** (R1 = a+b)
4.  **LD R2, c** (R2 = c)
5.  **LD R3, d** (R3 = d)
6.  **ADD R2, R2, R3** (R2 = c+d)
7.  **MUL R1, R1, R2** (R1 = (a+b)*(c+d))
8.  **LD R2, e** (R2 = e)
9.  **ADD R1, R1, R2** (R1 = (a+b)*(c+d)+e)

---

## 7. Role of `yylval` in YACC.

In YACC (Yet Another Compiler-Compiler), `yylval` is a global variable (usually a `union`) used to communicate semantic values between the lexical analyzer (`yylex`) and the parser (`yyparse`).
-   When `yylex` identifies a token (like a number), it stores the actual value (e.g., `5`) in `yylval` before returning the token type (e.g., `NUM`).
-   The parser then accesses this value using the `$` notation (e.g., `$1` refers to the value of the first symbol in a production).
