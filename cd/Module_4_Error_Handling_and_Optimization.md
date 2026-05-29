# Module 4: Error Handling and Optimization - Compiler Design Solutions

This document contains detailed solutions to previous year questions (PYQs) for Module 4 of the Compiler Design syllabus.

---

## 1. List the methods of error recovery.
(Panic-mode, Phrase-level, Error productions, Global least-cost - detailed in previous version)

---

## 2. Give various methods of loop optimization.
(Code motion, Induction variable elimination, Strength reduction, Loop unrolling, Loop jamming - detailed in previous version)

---

## 3. DAG Construction: Detailed Numerical

**Expression:** `P = Q * -C + (a + b) + (a + b) * D`

### Step 1: Intermediate Code (TAC)
1. `t1 = -C`
2. `t2 = Q * t1`
3. `t3 = a + b`
4. `t4 = t2 + t3`
5. `t5 = t3 * D`  <-- **Note: Node t3 (a+b) is reused here.**
6. `P = t4 + t5`

### Step 2: ASCII Directed Acyclic Graph (DAG)
```text
           [ + ] (P)
          /     \
        [+]     [*]
       /   \   /   \
     [*]    [+]     D
    /   \  /   \
   Q     [-]    b
          |    /
          C   a
```

### Step 3: Value Numbering & Node Reuse Table
| Node | Operator | Left Child | Right Child | Label/Result |
| :---: | :---: | :---: | :---: | :---: |
| 1 | `leaf` | Q | | Q |
| 2 | `leaf` | C | | C |
| 3 | `uminus` | 2 | | -C |
| 4 | `*` | 1 | 3 | Q * -C |
| 5 | `leaf` | a | | a |
| 6 | `leaf` | b | | b |
| 7 | `+` | 5 | 6 | **(a+b)** |
| 8 | `+` | 4 | 7 | t4 |
| 9 | `leaf` | D | | D |
| 10 | `*` | **7** | 9 | t5 (reused node 7) |
| 11 | `+` | 8 | 10 | **P** |

---

## 8. Partitioning into Basic Blocks: Detailed Trace

**Sample Code:**
```text
1) i = 1
2) sum = 0
3) t1 = 10 * i
4) sum = sum + t1
5) i = i + 1
6) if i <= 10 goto 3
7) print sum
```

### Step 1: Leader Identification Mapping
- **Rule 1:** The first instruction is a leader. $\to$ **Instruction 1**
- **Rule 2:** Any instruction that is the target of a jump is a leader. $\to$ **Instruction 3** (Target of `goto 3`)
- **Rule 3:** Any instruction following a jump is a leader. $\to$ **Instruction 7** (Follows `if...goto`)

### Step 2: Block Mapping
- **Block 1 (B1):** {1, 2}
- **Block 2 (B2):** {3, 4, 5, 6}
- **Block 3 (B3):** {7}

### Step 3: Control Flow Graph (CFG)
```text
[ B1 ] (Entry)
  |
  v
[ B2 ] <-----+
  |   \______| (Back-edge: i <= 10)
  |
  v
[ B3 ] (Exit)
```

---

## 4. Explain Peephole optimization and its characteristics.
(Redundant elimination, Flow-of-control, Algebraic simplification, Strength reduction, Machine idioms - detailed in previous version)
