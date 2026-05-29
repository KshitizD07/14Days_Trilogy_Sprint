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
This modularity makes porting compilers across different platforms far more efficient than rewriting a single-pass compiler from scratch.

#### 2. Enhanced Code Optimization
A single-pass compiler must generate machine code as soon as it recognizes a syntactic structure. This "on-the-fly" generation prevents the compiler from seeing the broader context of the program. 
In contrast, a two-pass compiler stores the entire program (or large blocks of it) in an IR. This allows the optimizer to perform:
- **Global Data Flow Analysis:** Understanding how values move across the entire function.
- **Dead Code Elimination:** Removing instructions that will never be executed.
- **Register Allocation:** Efficiently assigning limited CPU registers to variables across multiple statements.
- **Loop Optimization:** Moving invariant code outside of loops to improve performance.

#### 3. Resolution of Forward References
In many programming languages (like C or Java), a variable or function can be referenced before its actual definition appears in the source file. 
- A **single-pass compiler** struggles with this, often requiring "backpatching" or limiting the language's flexibility.
- A **two-pass compiler** handles this naturally. Pass 1 scans the entire program, identifying all labels, variables, and function definitions and storing them in a **Symbol Table**. When Pass 2 generates the code, it has a complete map of all addresses, allowing it to resolve all forward references accurately.

#### 4. Reduced Memory Requirements for Each Pass
While a two-pass compiler might seem slower due to the second traversal, each pass can be more focused. In the early days of computing with limited RAM, breaking the compiler into passes allowed each part of the compiler to fit into memory sequentially. Even today, this modularity keeps the compiler's internal state cleaner and easier to manage.

#### 5. Independent Development and Testing
Because the interface between the front end and back end is a well-defined IR, different engineering teams can work on different parts of the compiler simultaneously. One team can focus on the intricacies of parsing a new language feature, while another focuses on optimizing for the latest CPU instructions, without interfering with each other's progress.

---

## 2. Define token, lexeme, and pattern with examples. Explain the role of Lexical Analyzer in detail.

### Fundamental Concepts in Lexical Analysis

1.  **Lexeme:** 
    A lexeme is a sequence of characters in the source program that matches the pattern for a specific token and is identified by the lexical analyzer as a single logical unit. It is the "raw text" found in the code.
    *Example:* In the statement `int count = 10;`, the lexemes are `int`, `count`, `=`, `10`, and `;`.

2.  **Token:**
    A token is a pair consisting of a **token name** and an optional **attribute value**. The token name is an abstract symbol representing a lexical unit (e.g., a keyword, an identifier). The token names are the input symbols that the parser uses.
    *Example:* The lexeme `count` might be categorized under the token `<ID, pointer_to_symbol_table_entry>`. The lexeme `10` would be the token `<NUMBER, 10>`.

3.  **Pattern:**
    A pattern is a description of the form that the lexemes of a token may take. Patterns are typically specified using **Regular Expressions**.
    *Example:* The pattern for an identifier (ID) might be `letter(letter|digit)*`. The pattern for a number might be `digit+`.

### Detailed Role of the Lexical Analyzer (Scanner)

The Lexical Analyzer is the very first phase of the compiler. Its primary purpose is to read the input characters and group them into tokens. However, its responsibilities extend beyond simple tokenization:

#### 1. Tokenization and Buffering
The scanner reads the source program character by character. To do this efficiently, it uses **input buffering** techniques (like two-buffer schemes) to reduce the number of system calls and handle long lexemes (like string literals) that might cross buffer boundaries.

#### 2. Stripping Whitespace and Comments
The Lexical Analyzer filters out characters that are not necessary for the later phases of compilation. This includes removing spaces, tabs, newlines, and all forms of comments. This simplifies the task of the parser, which only sees a stream of meaningful tokens.

#### 3. Interaction with the Symbol Table
When the scanner identifies an identifier (like a variable name), it doesn't just pass the token to the parser. It checks the **Symbol Table** to see if that identifier has been seen before. If it's new, it adds it; if not, it retrieves the reference. The token passed to the parser often includes a pointer to the entry in the symbol table.

#### 4. Error Detection and Recovery
The Lexical Analyzer is the first line of defense against malformed input. It detects errors such as:
-   **Invalid Characters:** Characters that are not part of the language's alphabet.
-   **Malformed Tokens:** A numeric literal like `123a` (if the language doesn't allow it).
-   **Unclosed Literals:** A string constant that starts with `"` but never ends.
Recovery usually involves skipping characters until a valid token can be found or reporting the error and continuing to scan.

#### 5. Coordinating with the Parser
The Lexical Analyzer usually works as a subroutine of the parser. The parser calls a function (like `getNextToken()`), the scanner reads enough characters to identify the next lexeme, packages it as a token, and returns it. This demand-driven approach keeps the process synchronized.

---

## 3. What are the limitations of Top-Down Parsing? Discuss Left Recursion and Left Factoring with examples.

### Limitations of Top-Down Parsing

Top-down parsing (like Recursive Descent or LL(1) parsing) attempts to construct the parse tree starting from the root and moving down to the leaves. While intuitive, it suffers from several critical limitations:

1.  **Left Recursion:** This is the most famous limitation. If a grammar has a rule like $A \to A\alpha$, a top-down parser will enter an infinite loop trying to expand $A$ before it ever consumes an input symbol.
2.  **Backtracking:** Some top-down parsers (non-predictive) might need to try multiple productions for a non-terminal. If a choice leads to a failure, the parser must "backtrack" or undo its work and try another path. This can lead to exponential time complexity in the worst case.
3.  **Inability to Handle Ambiguity:** Top-down parsers require the grammar to be unambiguous and often strictly **LL(1)** (Left-to-right, Leftmost derivation, with 1-symbol lookahead). Many natural ways of writing grammars (like the "dangling else" problem) are not LL(1).
4.  **Order of Productions:** The order in which productions are checked can affect the outcome if the grammar is not carefully structured, leading to incorrect parses or early failures.

### Left Recursion and its Elimination

**Left Recursion** occurs when the leftmost symbol in a production is the non-terminal itself.
*Immediate Left Recursion:* $A \to A\alpha \mid \beta$ (where $\beta$ does not start with $A$).

**Elimination Rule:**
Replace the recursive production with:
1.  $A \to \beta A'$
2.  $A' \to \alpha A' \mid \epsilon$

**Example:**
Grammar for simple addition: $E \to E + T \mid T$
Here, $\alpha = "+ T"$ and $\beta = T$.
*Transformed Grammar:*
$E \to T E'$
$E' \to + T E' \mid \epsilon$

### Left Factoring

**Left Factoring** is a grammar transformation used to resolve "common prefix" issues. If a non-terminal $A$ has two productions $A \to \alpha \beta_1$ and $A \to \alpha \beta_2$, a predictive parser won't know which one to choose when it sees the start of $\alpha$.

**Elimination Rule:**
Replace the productions with:
1.  $A \to \alpha A'$
2.  $A' \to \beta_1 \mid \beta_2$

**Example:**
The "Dangling Else" problem:
$S \to \text{if } E \text{ then } S \mid \text{if } E \text{ then } S \text{ else } S$
Common prefix: $\alpha = \text{if } E \text{ then } S$.
*Transformed Grammar:*
$S \to \text{if } E \text{ then } S S'$
$S' \to \text{else } S \mid \epsilon$
This allows the parser to defer the decision of whether an `else` exists until after it has parsed the `then` clause.

---

## 4. Explain the 6 phases of a compiler with a detailed example of the statement: a = b + c * 60.

A compiler operates in a sequence of phases, each transforming the program from one representation to another. Consider the statement: `a = b + c * 60`.

### Phase 1: Lexical Analysis (Scanning)
The scanner reads the characters and groups them into tokens.
- `a` $\to$ `<id, 1>`
- `=` $\to$ `<assignment_op>`
- `b` $\to$ `<id, 2>`
- `+` $\to$ `<add_op>`
- `c` $\to$ `<id, 3>`
- `*` $\to$ `<mul_op>`
- `60` $\to$ `<num, 60>`
*Output:* A stream of tokens. The symbol table now contains entries for `a`, `b`, and `c`.

### Phase 2: Syntax Analysis (Parsing)
The parser uses the tokens to build a **Parse Tree** or **Syntax Tree** based on the language's grammar. It enforces operator precedence (multiplication before addition).
```text
      =
     / \
   id,1 +
       / \
     id,2 *
         / \
       id,3 num,60
```

### Phase 3: Semantic Analysis
The semantic analyzer checks the tree for logical errors. It ensures variables are declared and types are compatible.
*Example:* If `b` and `c` are floating-point numbers, the semantic analyzer might perform **type coercion**, converting the integer `60` into a floating-point `60.0` so the multiplication is valid.
```text
   inttofloat(60)
```

### Phase 4: Intermediate Code Generation
The compiler generates a machine-independent low-level representation, such as **Three-Address Code (TAC)**.
```text
t1 = inttofloat(60)
t2 = id3 * t1
t3 = id2 + t2
id1 = t3
```

### Phase 5: Code Optimization
The optimizer analyzes the TAC to make it more efficient.
- **Constant Folding:** If `60` is constant, it stays as is.
- **Algebraic Simplification:** If the statement was `a = b + 0`, it would simplify to `a = b`.
In our case, it might just keep the logic but ensure registers are used efficiently.

### Phase 6: Code Generation
The final phase translates the optimized intermediate code into the target machine's assembly or machine language.
```assembly
LDF R2, id3      ; Load 'c' into Register 2
MULF R2, R2, #60.0 ; Multiply R2 by 60.0
LDF R1, id2      ; Load 'b' into Register 1
ADDF R1, R1, R2  ; Add R2 to R1
STF id1, R1      ; Store result into 'a'
```

---

## 5. Consider the grammar [S->ACB|CbB|Ba, A->da|BC, B->g|ε, C->h|c]. Find FIRST and FOLLOW and check if LL(1).

### Step 1: Calculate FIRST Sets
-   **FIRST(C)** = {h, c} (Directly from $C \to h$ and $C \to c$)
-   **FIRST(B)** = {g, $\epsilon$} (Directly from $B \to g$ and $B \to \epsilon$)
-   **FIRST(A)**:
    -   From $A \to da$: {d}
    -   From $A \to BC$: Since $B \to \epsilon$, FIRST(A) includes FIRST(B) - {$\epsilon$} $\cup$ FIRST(C).
    -   FIRST(A) = {d, g, h, c}
-   **FIRST(S)**:
    -   From $S \to ACB$: FIRST(A) = {d, g, h, c}
    -   From $S \to CbB$: FIRST(C) = {h, c}
    -   From $S \to Ba$: FIRST(B) - {$\epsilon$} $\cup$ {a} = {g, a}
    -   FIRST(S) = {d, g, h, c, a}

### Step 2: Calculate FOLLOW Sets
-   **FOLLOW(S)** = {$} (S is the start symbol)
-   **FOLLOW(A)**:
    -   From $S \to ACB$: FOLLOW(A) includes FIRST(CB). Since $C \ne \epsilon$, it's FIRST(C) = {h, c}.
    -   FOLLOW(A) = {h, c}
-   **FOLLOW(C)**:
    -   From $S \to ACB$: FOLLOW(C) includes FIRST(B). Since $B \to \epsilon$, it also includes FOLLOW(S).
    -   From $S \to CbB$: FOLLOW(C) includes {b}.
    -   From $A \to BC$: FOLLOW(C) includes FOLLOW(A).
    -   FOLLOW(C) = {g, $, b, h, c}
-   **FOLLOW(B)**:
    -   From $S \to ACB$: FOLLOW(B) includes FOLLOW(S).
    -   From $S \to CbB$: FOLLOW(B) includes FOLLOW(S).
    -   From $A \to BC$: FOLLOW(B) includes FIRST(C) = {h, c}.
    -   FOLLOW(B) = {$, h, c}

### Step 3: LL(1) Check
A grammar is LL(1) if for every non-terminal $A$ with productions $A \to \alpha \mid \beta$:
1.  FIRST($\alpha$) $\cap$ FIRST($\beta$) = $\emptyset$
2.  If $\alpha \Rightarrow^* \epsilon$, then FIRST($\beta$) $\cap$ FOLLOW(A) = $\emptyset$

**Check Non-terminal S:**
-   $S \to ACB$ (FIRST = {d, g, h, c})
-   $S \to CbB$ (FIRST = {h, c})
**Intersection:** {h, c} $\cap$ {d, g, h, c} = {h, c} $\ne \emptyset$.

**Conclusion:** The grammar is **NOT LL(1)** because there is a first-first conflict on non-terminal S for symbols 'h' and 'c'.

---

## 6. What is Bootstrapping? Explain with T-diagrams.

### Definition of Bootstrapping
Bootstrapping is the process of writing a compiler for a language in the language itself. This is a common technique used to create self-hosting compilers. Since a compiler is a complex program, writing it in a high-level language is much easier than writing it in assembly.

### T-Diagrams
A T-diagram represents a compiler by three components:
-   **S:** The Source language it translates.
-   **T:** The Target language it generates.
-   **I:** The Implementation language the compiler is written in.
The notation is often written as $S \xrightarrow{I} T$.

### The Bootstrapping Process (Example)
Suppose we want to create a compiler for a new language **L** that runs on machine **M**, and we want the compiler to be written in **L**.

**Step 1:** Write a small subset of L (let's call it $L_{small}$) in a language that already exists on machine M (e.g., C or Assembly).
-   Compiler 1: $L_{small} \xrightarrow{C} M$

**Step 2:** Write the full compiler for L in $L_{small}$.
-   Compiler 2: $L \xrightarrow{L_{small}} M$

**Step 3:** Use Compiler 1 to compile Compiler 2.
-   $(L \xrightarrow{L_{small}} M)$ compiled by $(L_{small} \xrightarrow{C} M)$ $\implies$ **Result:** $L \xrightarrow{M} M$

Now you have a compiler for L that runs on M and is written in machine code (M). You can now discard the C version and continue developing the compiler in L itself.

---

## 10. Explain Cross-Compilers and their significance in embedded systems.

### Definition of a Cross-Compiler
A **Cross-Compiler** is a compiler that runs on one computer architecture (the **host** machine) but produces executable code for a different architecture (the **target** machine). 

For example, a compiler running on an Intel x86 Windows PC that generates binary code for an ARM-based microcontroller is a cross-compiler.

### Significance in Embedded Systems

#### 1. Resource Constraints
Embedded systems (like those in microwaves, cars, or medical devices) often have extremely limited resources. They might have only a few kilobytes of RAM and a slow processor. Running a full-featured compiler, which requires significant memory for parsing trees and optimization algorithms, is physically impossible on such hardware.

#### 2. Lack of Operating System
Many embedded targets do not run a standard operating system with a file system, which is a prerequisite for most compilers to manage source files and temporary objects. Cross-compilation allows developers to use the rich environment of a modern OS (Linux, Windows) to write and build code.

#### 3. Development Speed
Compiling code on a powerful desktop CPU is orders of magnitude faster than it would be on a low-power microcontroller. This significantly shortens the "edit-compile-test" cycle for developers.

#### 4. Specialized Toolchains
Embedded development often requires specialized libraries and header files specific to the target hardware (e.g., hardware abstraction layers). Cross-compilers are bundled into "toolchains" (like `arm-none-eabi-gcc`) that include everything needed to build for that specific hardware.

#### 5. Debugging and Simulation
By using a host machine, developers can use sophisticated debuggers, simulators, and static analysis tools that are not available on the target device. They can catch logic errors before ever deploying the code to the physical hardware.

---

## 12. Compare and contrast Compiler vs Interpreter.

| Feature | Compiler | Interpreter |
| :--- | :--- | :--- |
| **Mechanism** | Translates the entire source program into machine code in one go. | Translates and executes the source code line-by-line or statement-by-statement. |
| **Execution Speed** | Very Fast. Once compiled, the program runs directly as machine code. | Slower. The overhead of translation happens during every execution. |
| **Memory Usage** | Higher during compilation (generates object files), but efficient during execution. | Lower initial memory, but keeps the source/IR and interpreter in memory during run. |
| **Error Handling** | Reports all syntactic/semantic errors only after scanning the entire file. | Reports errors immediately as they are encountered during execution. |
| **Intermediate Code** | Generates an object file (e.g., .exe, .obj) which is stored. | Does not produce a separate permanent object file. |
| **Optimization** | Can perform complex, global optimizations as it sees the whole program. | Limited to local optimizations or Just-In-Time (JIT) compilation. |
| **Portability** | Target-specific. You need a different version of the binary for every OS/CPU. | Highly portable. The same source runs on any machine with the interpreter installed. |
| **Examples** | C, C++, Rust, Go. | Python, JavaScript, Ruby, PHP. |

**Hybrid Approaches:** Modern languages like **Java** and **C#** use a hybrid approach. They are compiled into a platform-independent "Bytecode" (e.g., .class files), which is then interpreted or JIT-compiled by a Virtual Machine (JVM or CLR) on the target system. This combines the portability of an interpreter with the performance benefits of a compiler.
