# Module 3: Syntax-Directed Translation and Symbol Tables - Compiler Design Solutions

This document contains detailed solutions to previous year questions (PYQs) for Module 3 of the Compiler Design syllabus.

---

## 1. What are the different methods of organizing the Symbol Table? Explain Linear List, Hash Table, and Tree-structured symbol tables in detail.

The **Symbol Table** is a critical data structure used by a compiler to store information about various entities encountered in the source code, such as variables, functions, classes, and constants.

### Methods of Organization

#### 1. Linear List (Unordered)
This is the simplest form of organization. Symbols are added to the list in the order they are encountered.
-   **Insertion:** Very fast, $O(1)$, as symbols are just appended to the end.
-   **Lookup:** Slow, $O(n)$, as the compiler must scan the entire list from beginning to end (or end to beginning for scope) to find an entry.
-   **Usage:** Only suitable for very small programs or toy compilers.

#### 2. Ordered List (Sorted)
Symbols are kept in alphabetical order.
-   **Insertion:** Slower, $O(n)$, because elements must be shifted to maintain order.
-   **Lookup:** Faster, $O(\log n)$, using binary search.
-   **Usage:** Rarely used because insertion is too frequent a task during compilation.

#### 3. Hash Table
This is the most common and efficient method. A hash function maps the symbol's name to an index in a fixed-size table.
-   **Insertion/Lookup:** Average case is $O(1)$. In the worst case (many collisions), it can degrade to $O(n)$, but good hash functions make this rare.
-   **Collision Handling:** Typically handled using **Chaining** (each bucket is a linked list of symbols) or **Open Addressing**.
-   **Usage:** Standard in modern production compilers.

#### 4. Tree-Structured (Binary Search Trees)
Symbols are stored in a balanced binary search tree (like an AVL tree or Red-Black tree).
-   **Insertion/Lookup:** $O(\log n)$ in both average and worst cases (if balanced).
-   **Advantages:** Naturally handles symbol order and can be easily extended to handle nested scopes by creating a new tree for each scope and linking it to its parent.
-   **Usage:** Used in compilers where scope management and ordered traversal are frequently required.

---

## 2. Discuss the various operations performed on a Symbol Table (Insert, Lookup, Scope Management).

### 1. Insert Operation
When a new identifier declaration is encountered (e.g., `int x;`), the compiler checks if `x` already exists in the **current scope**. If not, a new entry is created.
-   **Data Stored:** Name, Type, Scope, Memory Offset/Address, Line Number of declaration, and potentially visibility (public/private).

### 2. Lookup Operation
This is the most frequent operation. It happens every time a variable is used in an expression (e.g., `y = x + 5;`). 
-   **Mechanism:** The compiler searches for the identifier starting from the current inner-most scope and moving outwards to the global scope. 
-   **Failure:** If the identifier is not found in any visible scope, the compiler reports an "Undeclared Identifier" error.

### 3. Scope Management (Set and Reset Scope)
Compilers must handle nested scopes (e.g., blocks within functions, nested classes).
-   **Entering a Scope:** When a `{` is encountered, the compiler may create a new symbol table for that block and link it to the previous one (forming a "Scope Stack" or a "Display").
-   **Exiting a Scope:** When a `}` is reached, the compiler "pops" the current table. Depending on the language, it might delete the symbols or just mark them as inaccessible.

---

## 3. Explain the concept of an Activation Tree and its relationship with the control flow.

### Activation Tree
An **Activation Tree** is a graphical representation of the sequence of procedure calls (activations) during the execution of a program.
-   **Nodes:** Each node represents an "activation" (an instance of a procedure execution).
-   **Edges:** An edge from node $A$ to node $B$ means procedure $A$ called procedure $B$.
-   **Properties:**
    1.  The root is the activation of the `main` program.
    2.  The sequence of nodes visited in a **pre-order traversal** corresponds to the order in which activations begin.
    3.  A **post-order traversal** corresponds to the order in which activations terminate.
    4.  If procedure $A$ calls $B$ and $C$ in that order, $B$ and its sub-tree appear to the left of $C$ and its sub-tree.

### Relationship with Control Flow
The Activation Tree represents the **dynamic nesting** of procedure calls. At any point in time during execution, the path from the root to the currently executing node represents the set of **live activations** (procedures that have started but not yet finished). This path corresponds directly to the state of the **Run-time Stack**.

---

## 4. Define S-attributed and L-attributed Syntax-Directed Definitions (SDDs) with examples.

### 1. S-attributed SDD
In an S-attributed definition, every attribute is **synthesized**. A synthesized attribute is computed solely from the attributes of the node's children.
-   **Evaluation:** Can be done during a single bottom-up pass (e.g., during LR parsing).
-   **Example:** Evaluation of an expression.
    -   Production: $E \to E_1 + T$
    -   Semantic Rule: $E.val = E_1.val + T.val$

### 2. L-attributed SDD
In an L-attributed definition, attributes can be either synthesized or **inherited**, but with a restriction: an inherited attribute for a child node can only depend on:
1.  The attributes of its parent.
2.  The attributes of its **left** siblings.
-   **Evaluation:** Can be done during a single top-down, left-to-right pass (e.g., during LL parsing).
-   **Example:** Type propagation.
    -   Production: $D \to T L$
    -   Semantic Rule: $L.inh = T.type$ (Inherited from left sibling $T$).

---

## 5. Elaborate on the various fields in an Activation Record.

An **Activation Record** (also called a Stack Frame) is a block of memory used to store all the information needed for a single execution of a procedure.

### Typical Fields

1.  **Actual Parameters:** The values passed to the procedure by the caller.
2.  **Return Value:** Space for the value that the procedure will return to the caller.
3.  **Control Link (Dynamic Link):** A pointer to the activation record of the **caller**. This allows the stack to be unwound when the procedure finishes.
4.  **Access Link (Static Link):** A pointer to the activation record of the procedure's **lexical parent**. Used to access non-local variables in block-structured languages.
5.  **Saved Machine Status:** Stores the state of CPU registers and the Program Counter (PC) at the time of the call, so the caller can resume correctly.
6.  **Local Variables:** Storage for variables declared within the procedure that are only alive during its execution.
7.  **Temporaries:** Used to store intermediate results during the evaluation of complex expressions.

---

## 6. Explain various Run-time Storage Allocation strategies: Static, Stack, and Heap.

### 1. Static Allocation
Memory is allocated at compile time and remains fixed throughout the program's execution.
-   **Pros:** Very fast (no overhead for allocation/deallocation).
-   **Cons:** No support for recursion; no dynamic memory growth.
-   **Usage:** Global variables, constants, and languages like early Fortran.

### 2. Stack Allocation
Memory is allocated on a LIFO (Last-In, First-Out) stack. An activation record is pushed when a procedure is called and popped when it returns.
-   **Pros:** Supports recursion; efficient memory reuse (memory for locals is reclaimed immediately).
-   **Cons:** Only works for data whose lifetime is strictly nested with the procedure call.
-   **Usage:** Local variables in C, C++, Java, etc.

### 3. Heap Allocation
Memory is allocated from a large pool of free memory (the heap) and can be allocated and deallocated at any time.
-   **Pros:** Supports data with arbitrary lifetimes; supports dynamic data structures like linked lists and trees.
-   **Cons:** High overhead for management (allocation/deallocation); risk of fragmentation and memory leaks. Requires garbage collection or manual management.
-   **Usage:** Objects in Java/C#, `malloc` in C, `new` in C++.
