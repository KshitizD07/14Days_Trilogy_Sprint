# Module 2: Efficient Parsers and Intermediate Code - Compiler Design Solutions

This document contains detailed solutions to previous year questions (PYQs) for Module 2 of the Compiler Design syllabus.

---

## 1. Construct the LR(0) canonical collection of items and the parsing table for the grammar: [S'->S, S->cB|ccA, A->cA|a, B->ccB|b].

### Step 1: Augmented Grammar
(0) $S' \to S$
(1) $S \to cB$
(2) $S \to ccA$
(3) $A \to cA$
(4) $A \to a$
(5) $B \to ccB$
(6) $B \to b$

### Step 2: Canonical Collection of LR(0) Items
- **$I_0$**: $S' \to \cdot S, S \to \cdot cB, S \to \cdot ccA$
- **$I_1$**: $Goto(I_0, S) = S' \to S \cdot$
- **$I_2$**: $Goto(I_0, c) = S \to c \cdot B, S \to c \cdot cA, B \to \cdot ccB, B \to \cdot b$
- **$I_3$**: $Goto(I_2, B) = S \to cB \cdot$
- **$I_4$**: $Goto(I_2, c) = S \to cc \cdot A, B \to c \cdot cB, A \to \cdot cA, A \to \cdot a$
- **$I_5$**: $Goto(I_2, b) = B \to b \cdot$
- **$I_6$**: $Goto(I_4, A) = S \to ccA \cdot$
- **$I_7$**: $Goto(I_4, c) = B \to cc \cdot B, A \to c \cdot A, B \to \cdot ccB, B \to \cdot b, A \to \cdot cA, A \to \cdot a$
- **$I_8$**: $Goto(I_4, a) = A \to a \cdot$
- **$I_9$**: $Goto(I_7, B) = B \to ccB \cdot$
- **$I_{10}$**: $Goto(I_7, A) = A \to cA \cdot$
- **$I_{11}$**: $Goto(I_7, c) = B \to c \cdot cB, A \to c \cdot A, B \to \cdot ccB, B \to \cdot b, A \to \cdot cA, A \to \cdot a$

### Step 3: GOTO Transition Map
```text
I0 --S--> I1
I0 --c--> I2
I2 --B--> I3
I2 --c--> I4
I2 --b--> I5
I4 --A--> I6
I4 --c--> I7
I4 --a--> I8
I7 --B--> I9
I7 --A--> I10
I7 --c--> I11
I11--c--> I7 (loop)
```

### Step 4: LR(0) Parsing Table
| State | c | b | a | $ | S | B | A |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **0** | s2 | | | | 1 | | |
| **1** | | | | acc | | | |
| **2** | s4 | s5 | | | | 3 | |
| **3** | r1 | r1 | r1 | r1 | | | |
| **4** | s7 | | s8 | | | | 6 |
| **5** | r6 | r6 | r6 | r6 | | | |
| **6** | r2 | r2 | r2 | r2 | | | |
| **7** | s11 | s5 | s8 | | | 9 | 10 |
| **8** | r4 | r4 | r4 | r4 | | | |
| **9** | r5 | r5 | r5 | r5 | | | |
| **10**| r3 | r3 | r3 | r3 | | | |
| **11**| s7 | s5 | s8 | | | | 10 |

---

## 2. Quadruples, Triples, and Indirect Triples for `a = b * -c + b * -c`.

### Step 1: Intermediate Code Generation (TAC)
1. `t1 = -c`
2. `t2 = b * t1`
3. `t3 = -c`
4. `t4 = b * t3`
5. `t5 = t2 + t4`
6. `a = t5`

### Step 2: Quadruples Table
| Index | op | arg1 | arg2 | result |
| :---: | :---: | :---: | :---: | :---: |
| (0) | uminus | c | | t1 |
| (1) | * | b | t1 | t2 |
| (2) | uminus | c | | t3 |
| (3) | * | b | t3 | t4 |
| (4) | + | t2 | t4 | t5 |
| (5) | = | t5 | | a |

### Step 3: Triples Table
| Index | op | arg1 | arg2 |
| :---: | :---: | :---: | :---: |
| (0) | uminus | c | |
| (1) | * | b | (0) |
| (2) | uminus | c | |
| (3) | * | b | (2) |
| (4) | + | (1) | (3) |
| (5) | = | a | (4) |

### Step 4: Indirect Triples
| Order | Pointer |
| :---: | :---: |
| 100 | (0) |
| 101 | (1) |
| 102 | (2) |
| 103 | (3) |
| 104 | (4) |
| 105 | (5) |

---

## 3. TAC for Nested Loop: `While (a < c or b > d) do If a = 1 then c = a * b + c else a = b - d * c`.

### Control Flow Mapping (Labels & Jumps)
```text
L1: if a < c goto L3      (Short-circuit OR)
    if b > d goto L3
    goto L5               (Exit While)

L3: if a == 1 goto L4     (IF block)
    goto Lelse

L4: t1 = a * b            (THEN part)
    t2 = t1 + c
    c = t2
    goto L1

Lelse: t3 = d * c         (ELSE part)
    t4 = b - t3
    a = t4
    goto L1

L5: ... (End)
```

### ASCII Control Flow Graph
```text
      [ Start (L1) ]
         |       |
      (True)   (False)
         |       |
         v       +-----> [ Exit (L5) ]
    [ Body (L3) ]
      /      \
   (If)     (Else)
    |          |
 [ L4 ]     [ Lelse ]
    \_________/
         |
         v
    [ Loop Back ]
```

---

## 9. Handle Pruning for `a a + a *` using [S->SS+|SS*|a].

### Stack Trace and Handle Identification
| Stack | Input | Action | Handle |
| :--- | :--- | :--- | :--- |
| $ | a a + a * $ | Shift | |
| $ a | a + a * $ | Reduce by S->a | **a** |
| $ S | a + a * $ | Shift | |
| $ S a | + a * $ | Reduce by S->a | **a** |
| $ S S | + a * $ | Shift | |
| $ S S + | a * $ | Reduce by S->SS+ | **S S +** |
| $ S | a * $ | Shift | |
| $ S a | * $ | Reduce by S->a | **a** |
| $ S S | * $ | Reduce by S->SS* | **S S *** |
| $ S | $ | Accept | |

**Handle Definitions:**
1. At step 2, `a` is the handle reduced to `S`.
2. At step 4, the second `a` is the handle.
3. At step 6, the entire prefix `S S +` is the handle reduced to `S`.
4. At step 8, `a` is the handle.
5. At step 9, `S S *` is the handle reduced to the start symbol `S`.
