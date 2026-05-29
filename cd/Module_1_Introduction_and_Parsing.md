# Module 1: Introduction and Parsing - Compiler Design Solutions

This document contains detailed solutions to previous year questions (PYQs) for Module 1 of the Compiler Design syllabus. Each solution is structured to be suitable for a 10-mark university exam question.

---

## 1. What is a two-pass compiler? Explain its advantages over a single-pass compiler in detail.

### Definition of a Pass
In the context of compiler construction, a **pass** refers to a complete traversal of the source program or its intermediate representation. 

- **Single-Pass Compiler:** A single-pass compiler scans the source code and generates machine code in one go. It intertwines the analysis and synthesis phases.
- **Two-Pass Compiler:** A two-pass compiler separates the compilation process into two distinct stages:
    1.  **Pass 1 (Front End):** Focuses on the analysis of the source language. It performs lexical, syntax, and semantic analysis to verify the program's correctness and generates an **Intermediate Representation (IR)**.
    2.  **Pass 2 (Back End):** Focuses on the synthesis of the target machine code. It reads the IR, performs machine-independent and machine-dependent optimizations, and finally produces the object code for the target architecture.

### Advantages of a Two-Pass Compiler over a Single-Pass Compiler

#### 1. Machine Independence and Portability
The most significant advantage is the **separation of concerns**. By using an Intermediate Representation (IR), the front end (analysis) becomes independent of the target machine, and the back end (synthesis) becomes independent of the source language.
- To support a **new source language** for the same target machine, you only need to develop a new front end that produces the same IR.
- To support a **new target machine** for the same source language, you only need to develop a new back end that consumes that IR.

#### 2. Enhanced Code Optimization
A two-pass compiler stores the entire program (or large blocks of it) in an IR. This allows the optimizer to perform global data flow analysis, dead code elimination, and efficient register allocation.

---

## 2. Define token, lexeme, and pattern with examples. Explain the role of Lexical Analyzer in detail.

### Fundamental Concepts
1.  **Lexeme:** A sequence of characters matching a token pattern (e.g., `count`).
2.  **Token:** A pair consisting of a name and an attribute value (e.g., `<ID, 1>`).
3.  **Pattern:** A description of the form of lexemes, usually a Regular Expression (e.g., `[a-zA-Z_][a-zA-Z0-9_]*`).

### Detailed Role of the Lexical Analyzer
The Lexical Analyzer reads input characters and groups them into tokens. Its roles include tokenization, stripping whitespace/comments, interacting with the symbol table, and input buffering.

---

## 3. Grammar Transformation: Left Recursion and Left Factoring

**Target Grammar:**
1. $S \to Aa \mid b$
2. $A \to aAB \mid aA \mid Ac \mid Sd \mid a \mid \epsilon$
3. $B \to \epsilon$

### Step 1: Eliminate Indirect Left Recursion
We substitute $S \to Aa \mid b$ into $A \to Sd$.
- $A \to aAB \mid aA \mid Ac \mid (Aa \mid b)d \mid a \mid \epsilon$
- $A \to aAB \mid aA \mid Ac \mid Aad \mid bd \mid a \mid \epsilon$

### Step 2: Eliminate Immediate Left Recursion for A
Rules: $A \to A\alpha \mid \beta$. 
Here, $\alpha_1 = c$, $\alpha_2 = ad$.
$\beta_1 = aAB$, $\beta_2 = aA$, $\beta_3 = bd$, $\beta_4 = a$, $\beta_5 = \epsilon$.

**Transformed Rules for A:**
- $A \to (aAB \mid aA \mid bd \mid a \mid \epsilon) A'$
- $A' \to cA' \mid adA' \mid \epsilon$

### Step 3: Left Factoring for A
Common prefix 'a' in $A \to aAB A' \mid aA A' \mid a A'$.
- $A \to a (AB A' \mid A A' \mid A') \mid bd A' \mid A'$
- Deeper factoring: $A \to a A'' \mid bd A' \mid A'$
- $A'' \to AB A' \mid A A' \mid A'$

---

## 4. Compilation Phases Trace: `a = b + c * 60`

### Visual Pipeline
`Source Code` $\to$ **Lexical** $\to$ `Tokens` $\to$ **Syntax** $\to$ `Parse Tree` $\to$ **Semantic** $\to$ `Annotated Tree` $\to$ **Intermediate Code** $\to$ `TAC` $\to$ **Optimization** $\to$ **Code Generation** $\to$ `Target Code`

### 1. Lexical Analysis
| Lexeme | Token Category | Attribute |
| :--- | :--- | :--- |
| `a` | `ID` | Pointer to Symbol Table (Entry 1) |
| `=` | `ASSIGN_OP` | |
| `b` | `ID` | Pointer to Symbol Table (Entry 2) |
| `+` | `ADD_OP` | |
| `c` | `ID` | Pointer to Symbol Table (Entry 3) |
| `*` | `MUL_OP` | |
| `60` | `NUM` | Value 60 |

### 2. Syntax Analysis (Parse Tree)
```text
      =
     / \
  id(a) +
       / \
    id(b) *
         / \
      id(c) 60
```

### 3. Semantic Analysis
Checks types. If `b` and `c` are real, `60` is converted to `60.0` (inttofloat).

### 4. Intermediate Code Generation (TAC)
```text
t1 = inttofloat(60)
t2 = id(c) * t1
t3 = id(b) + t2
id(a) = t3
```

### 5. Symbol Table Chart
| Index | Name | Type | Scope | Offset |
| :---: | :---: | :---: | :---: | :---: |
| 1 | a | float | global | 0 |
| 2 | b | float | global | 4 |
| 3 | c | float | global | 8 |

---

## 5. FIRST and FOLLOW Analysis: Detailed Numerical

**Grammar:**
1. $S \to ACB \mid CbB \mid Ba$
2. $A \to da \mid BC$
3. $B \to g \mid \epsilon$
4. $C \to h \mid c$

### Step-by-Step Derivation

#### 1. FIRST Sets
-   **FIRST(B)** = {g, $\epsilon$}
-   **FIRST(C)** = {h, c}
-   **FIRST(A)**:
    -   From $A \to da$: {d}
    -   From $A \to BC$: Since $B \to \epsilon$, FIRST(A) includes (FIRST(B)-$\epsilon$) $\cup$ FIRST(C).
    -   FIRST(A) = {d, g, h, c}
-   **FIRST(S)**:
    -   From $S \to ACB$: FIRST(A) = {d, g, h, c}
    -   From $S \to CbB$: FIRST(C) = {h, c}
    -   From $S \to Ba$: (FIRST(B)-$\epsilon$) $\cup$ {a} = {g, a}
    -   **Final FIRST(S)** = {a, c, d, g, h}

#### 2. FOLLOW Sets
-   **FOLLOW(S)** = {$}
-   **FOLLOW(A)**: From $S \to ACB$, FOLLOW(A) = FIRST(CB) = FIRST(C) = {h, c}.
-   **FOLLOW(B)**: 
    -   From $S \to ACB$: FOLLOW(B) = FOLLOW(S) = {$}.
    -   From $A \to BC$: FOLLOW(B) = FIRST(C) = {h, c}.
    -   **Final FOLLOW(B)** = {$, h, c}
-   **FOLLOW(C)**:
    -   From $S \to ACB$: FOLLOW(C) = (FIRST(B)-$\epsilon$) $\cup$ FOLLOW(S) = {g, $}.
    -   From $S \to CbB$: FOLLOW(C) = {b}.
    -   From $A \to BC$: FOLLOW(C) = FOLLOW(A) = {h, c}.
    -   **Final FOLLOW(C)** = {b, g, h, c, $}

### LL(1) Parsing Table
| NT | a | b | c | d | g | h | $ |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **S** | $S \to Ba$ | | $S \to ACB$, $S \to CbB$ | $S \to ACB$ | $S \to ACB$, $S \to Ba$ | $S \to ACB$, $S \to CbB$ | |
| **A** | | | $A \to BC$ | $A \to da$ | $A \to BC$ | $A \to BC$ | |
| **B** | | | $B \to \epsilon$ | | $B \to g$ | $B \to \epsilon$ | $B \to \epsilon$ |
| **C** | | | $C \to c$ | | | $C \to h$ | |

**Conclusion:** The grammar is **NOT LL(1)** due to multiple entries (FIRST-FIRST conflicts) for S on 'c', 'h', and 'g'.

---

## 13. DFA Construction for `(a | b)* a`

### Step 1: Thompson's NFA
```text
      ε       a       ε
(1) ----> (2) ----> (3) ----> (6)
 ^         |         ^         |
 |   ε     v     ε   |         |
(0) ----> (4) ----> (5)        |  a
           |         ^         |-----> (7) [FINAL]
           |    b    |         |
           +---->----+         |
                ε              |
(LOOP) <-----------------------+
```

### Step 2: Subset Construction (NFA to DFA)
States:
- **A** = $\epsilon$-closure(0) = {0, 1, 2, 4}
- **B** = $\epsilon$-closure(move(A, a)) = {3, 6, 7, 1, 2, 4}
- **C** = $\epsilon$-closure(move(A, b)) = {5, 6, 1, 2, 4}

**Transition Table:**
| DFA State | Input 'a' | Input 'b' |
| :---: | :---: | :---: |
| **A** (Start) | B | C |
| **B** (Final) | B | C |
| **C** | B | C |

### Step 3: Minimized DFA
States {A, C} can be merged because they have identical transitions. State B remains separate as it is an accepting state.

```text
       b
     +---+
     |   |
     v   |         a
-->( S0 ) ----------------> (( S1 )) [FINAL]
     ^   |                   |   ^
     |   +<------------------+   |
     |             b             |
     |                           |
     +------------- a -----------+
```
*(S1 on 'a' stays at S1, on 'b' goes to S0)*
