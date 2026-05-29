# Solved Numericals and Practical Problems - Compiler Design (Master Version)

This document contains exhaustive, step-by-step solutions to specific numerical and practical problems found in the Compiler Design PYQs.

---

## 1. LALR(1) Parsing Items: [S->AA, A->aA|b]

### Augmented Grammar
(0) $S' \to S$
(1) $S \to AA$
(2) $A \to aA$
(3) $A \to b$

### LALR(1) Canonical Collection of Items
LALR(1) items are formed by merging LR(1) items that share the identical LR(0) "core".

| State | Item Set (Merged) | Lookahead |
| :---: | :--- | :---: |
| **I0** | $S' \to \cdot S, S \to \cdot AA, A \to \cdot aA, A \to \cdot b$ | $ |
| **I1** | $S' \to S \cdot$ | $ |
| **I2** | $S \to A \cdot A, A \to \cdot aA, A \to \cdot b$ | $ |
| **I36**| $A \to a \cdot A, A \to \cdot aA, A \to \cdot b$ | $ / a / b |
| **I47**| $A \to b \cdot$ | $ / a / b |
| **I5** | $S \to AA \cdot$ | $ |
| **I89**| $A \to aA \cdot$ | $ / a / b |

### State Transition Map
```text
I0 --S--> I1
I0 --A--> I2
I0 --a--> I36
I0 --b--> I47

I2 --A--> I5
I2 --a--> I36
I2 --b--> I47

I36 --A--> I89
I36 --a--> I36 (Loop)
I36 --b--> I47
```

---

## 2. SLR Parsing Table: [E -> E+T | T, T -> id]

### LR(0) Canonical Collection
- **I0:** $E' \to \cdot E, E \to \cdot E+T, E \to \cdot T, T \to \cdot id$
- **I1:** (Goto I0, E) $E' \to E \cdot, E \to E \cdot + T$
- **I2:** (Goto I0, T) $E \to T \cdot$
- **I3:** (Goto I0, id) $T \to id \cdot$
- **I4:** (Goto I1, +) $E \to E + \cdot T, T \to \cdot id$
- **I5:** (Goto I4, T) $E \to E + T \cdot$

### SLR Parsing Table
| State | id | + | $ | E | T |
| :---: | :---: | :---: | :---: | :---: | :---: |
| **0** | s3 | | | 1 | 2 |
| **1** | | s4 | acc | | |
| **2** | | r2 | r2 | | |
| **3** | | r3 | r3 | | |
| **4** | s3 | | | | 5 |
| **5** | | r1 | r1 | | |

*Note: r1: E->E+T, r2: E->T, r3: T->id. Reduction occurs for symbols in FOLLOW set.*

---

## 3. DAG for `(a/10 + (b-10)) * (a/10 + (b-10))`

### Step 1: Intermediate Code (TAC)
1. `t1 = a / 10`
2. `t2 = b - 10`
3. `t3 = t1 + t2`
4. `t4 = t3 * t3` (Reuse node t3)

### Step 2: ASCII Directed Acyclic Graph (DAG)
```text
           [ * ]
          /     \
        [ + ] <---+
       /     \    |
    [ / ]   [ - ] |
    /   \   /   \ |
   a    (10)     b
```

### Node Reuse Explanation
The sub-expression `(a/10 + (b-10))` is represented by the `[+]` node. In a syntax tree, this node would appear twice. In a DAG, the `[*]` node points to the same `[+]` node for both its left and right children, eliminating redundant computation.

---

## 4. SDT Trace for `2 + 3 * 4`

| Step | Current Stack / Action | Semantic Rule Applied | Value Computed |
| :--- | :--- | :--- | :--- |
| 1 | `F -> 2` | $F.val = num.val$ | $F.val = 2$ |
| 2 | `T -> F` | $T.val = F.val$ | $T.val = 2$ |
| 3 | `E -> T` | $E.val = T.val$ | $E.val = 2$ |
| 4 | `F -> 3` | $F.val = num.val$ | $F.val = 3$ |
| 5 | `T -> F` | $T.val = F.val$ | $T.val = 3$ |
| 6 | `F -> 4` | $F.val = num.val$ | $F.val = 4$ |
| 7 | `T -> T * F` | $T.val = T_1.val * F.val$ | $T.val = 3 * 4 = 12$ |
| 8 | `E -> E + T` | $E.val = E_1.val + T.val$ | $E.val = 2 + 12 = 14$ |

**Final Value:** 14

---

## 5. Basic Blocks Partitioning: i/j Loop Trace

### Code and Leader Identification
```text
1) i = 1             (Leader: Rule 1 - First)
2) j = 1             (Leader: Rule 2 - Target of jump at 11)
3) t1 = 10 * i       (Leader: Rule 2 - Target of jump at 9)
4) t2 = t1 + j
...
9) if j <= 10 goto 3
10) i = i + 1        (Leader: Rule 3 - Follows jump at 9)
11) if i <= 10 goto 2
```

### Block Mapping and Flow Diagram
| Block | Instructions | Source | Target |
| :---: | :--- | :---: | :---: |
| **B1** | 1 | Start | B2 |
| **B2** | 2 | B1, B4 | B3 |
| **B3** | 3, 4, 5, 6, 7, 8, 9 | B2, B3 | B4, B3 |
| **B4** | 10, 11 | B3 | B2, Exit |

### Control Flow Graph (CFG)
```text
[ B1 ]
  |
  v
[ B2 ] <-----+
  |          |
  v          |
[ B3 ] <---+ |
  |   \____| |
  |          |
  v          |
[ B4 ] ______|
  |
  v
[ Exit ]
```

---

## 6. Register Allocation for `(a+b)*(c+d)+e`

| Operation | Machine Instruction | Register Status |
| :--- | :--- | :--- |
| Load `a` | `LD R1, a` | R1=a, R2=?, R3=? |
| Load `b` | `LD R2, b` | R1=a, R2=b, R3=? |
| $a+b$ | `ADD R1, R1, R2` | R1=(a+b), R2=b, R3=? |
| Load `c` | `LD R2, c` | R1=(a+b), R2=c, R3=? |
| Load `d` | `LD R3, d` | R1=(a+b), R2=c, R3=d |
| $c+d$ | `ADD R2, R2, R3` | R1=(a+b), R2=(c+d), R3=d |
| Multiply | `MUL R1, R1, R2` | R1=((a+b)*(c+d)), R2=(c+d), R3=d |
| Load `e` | `LD R2, e` | R1=prod, R2=e, R3=d |
| Final Add | `ADD R1, R1, R2` | R1=result, R2=e, R3=d |
