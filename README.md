# 🚀 Tech Interview Preparation & Revision Hub

A structured, comprehensive repository for technical interview preparation, covering **Data Structures & Algorithms (DSA)** in C++, **System Design fundamentals**, and **Linux & Operating System concepts**.

---

## 📌 Table of Contents

- [Overview](#-overview)
- [Repository Structure](#-repository-structure)
- [Data Structures & Algorithms](#-data-structures--algorithms)
  - [Pattern Guides](#pattern-guides)
  - [Problems by Difficulty & Pattern](#problems-by-difficulty--pattern)
  - [Sorting & Core Algorithms](#sorting--core-algorithms)
- [System Design Foundations](#-system-design-foundations)
- [Linux & Operating Systems](#-linux--operating-systems)
- [How to Run Solutions](#-how-to-run-solutions)
- [Key Takeaways & Master Rules](#-key-algorithmic-master-rules)

---

## 🎯 Overview

This repository is designed for targeted interview preparation and revision across core Computer Science domains:
- **Clean C++ Solutions**: Idiomatic, readable, and time/space complexity-optimized solutions.
- **Problem Notes & Breakdowns**: Markdown summaries alongside code explaining intuition, edge cases, and patterns.
- **System Design Core Topics**: High-level and low-level architectural concepts (sessions, cookies, scaling, state management).
- **OS & Linux**: Deep dives into filesystems, file operations, and OS internals.

---

## 📂 Repository Structure

```plaintext
.
├── Easy/                       # Easy DSA problems categorized by pattern
│   └── Two_pointers/
├── Medium/                     # Medium DSA problems categorized by pattern
│   ├── Sliding_Window/
│   └── Two_pointers/
├── Hard/                       # Hard DSA problems categorized by pattern
│   └── Two_pointers/
├── Sorting/                    # Core sorting algorithms & partition strategies
│   ├── Heap/
│   ├── Merge/
│   └── Quick/
├── System Design/              # System design study notes & architectural patterns
├── linux/                      # Linux filesystem & OS study modules
└── Leetcode_daily/             # Daily LeetCode challenges & solutions
```

---

## 🧠 Data Structures & Algorithms

### Pattern Guides
- 📖 [Two Pointers Pattern Guide & Master Rules](Easy/Two_pointers/TwoPointers_Pattern.md)

---

### Problems by Difficulty & Pattern

#### 🟢 Easy

| Problem # | Title | Pattern | Solution (C++) | Notes |
| :---: | :--- | :---: | :---: | :---: |
| **26** | Remove Duplicates from Sorted Array | Two Pointers | [Solution](Easy/Two_pointers/26_RemoveDuplicates.cpp) | [Notes](Easy/Two_pointers/26.md) |
| **27** | Remove Element | Two Pointers | [Solution](Easy/Two_pointers/27_MoveElement.cpp) | [Notes](Easy/Two_pointers/27.md) |
| **88** | Merge Sorted Array | Two Pointers (Reverse Fill) | [Solution](Easy/Two_pointers/88_MergeSortedArray.cpp) | [Notes](Easy/Two_pointers/88.md) |
| **125** | Valid Palindrome | Two Pointers | [Solution](Easy/Two_pointers/125_ValidPalindrome.cpp) | — |
| **283** | Move Zeroes | Two Pointers (Slow-Fast) | [Solution](Easy/Two_pointers/283_Move%20Zeroes.cpp) | [Notes](Easy/Two_pointers/283.md) |
| **344** | Reverse String | Two Pointers | [Solution](Easy/Two_pointers/344_ReverseString.cpp) | — |
| **680** | Valid Palindrome II | Two Pointers | [Solution](Easy/Two_pointers/680_ValidPalindrome.cpp) | — |
| **977** | Squares of a Sorted Array | Two Pointers | [Solution](Easy/Two_pointers/977_SquareOfSortedArray.cpp) | [Notes](Easy/Two_pointers/977.md) |

#### 🟡 Medium

| Problem # | Title | Pattern | Solution (C++) | Notes |
| :---: | :--- | :---: | :---: | :---: |
| **3** | Longest Substring Without Repeating Characters | Sliding Window | [Solution](Medium/Sliding_Window/3_LongestSubstring.cpp) | — |
| **5** | Longest Palindromic Substring | Two Pointers / Expansion | [Solution](Medium/Two_pointers/5_LongestPalindromicSubstring.cpp) | — |
| **11** | Container With Most Water | Two Pointers | [Solution](Medium/Two_pointers/11_ContainerWithMostWater.cpp) | [Notes](Medium/Two_pointers/11.md) |
| **15** | 3Sum | Two Pointers (Fix One + 2P) | [Solution](Medium/Two_pointers/15_3Sum.cpp) | [Notes](Medium/Two_pointers/15.md) |
| **16** | 3Sum Closest | Two Pointers | [Solution](Medium/Two_pointers/16_%23SumClosest.cpp) | — |
| **18** | 4Sum | Two Pointers | [Solution](Medium/Two_pointers/18_4Sum.cpp) | — |
| **75** | Sort Colors (Dutch National Flag) | Two Pointers / 3-Way Partition | [Solution](Medium/Two_pointers/75_SortColors.cpp) | [Notes](Medium/Two_pointers/75.md) |
| **167** | Two Sum II - Input Array Is Sorted | Two Pointers | [Solution](Medium/Two_pointers/167_TwoSum_II.cpp) | [Notes](Medium/Two_pointers/167.md) |

#### 🔴 Hard

| Problem # | Title | Pattern | Solution (C++) | Notes |
| :---: | :--- | :---: | :---: | :---: |
| **42** | Trapping Rain Water | Two Pointers | [Solution](Hard/Two_pointers/42_TrappingRainWater.cpp) | [Notes](Hard/Two_pointers/42.md) |

#### 📅 LeetCode Daily
- [3121. Count the Number of Special Characters II](Leetcode_daily/3121_Count_the_Number_of_Special_Characters_II.md)

---

### ⚡ Sorting & Core Algorithms

| Category | Algorithm / Technique | Implementation |
| :--- | :--- | :--- |
| **Heap** | Heap Insertion & Heapify | [`Insertion.cpp`](Sorting/Heap/Insertion.cpp) |
| **Merge Sort** | Standard Merge Sort & Inversions | [`Merge_sort.cpp`](Sorting/Merge/Merge_sort.cpp), [`Merge_sort2.cpp`](Sorting/Merge/Merge_sort2.cpp) |
| **Quick Sort** | Hoare's Partitioning Scheme | [`Hoare_partition.cpp`](Sorting/Quick/Hoare_partition.cpp) |
| **Quick Sort** | Lomuto's Partitioning Scheme | [`Lomuto_partition.cpp`](Sorting/Quick/Lomuto_partition.cpp) |

---

## 🏛️ System Design Foundations

Essential architectural notes and high-level concepts for system design rounds:

- 🌐 [Client-Server Architecture](System%20Design/Client-Server%20Architecture.md) — Fundamentals of communication, request-response lifecycles, and protocols.
- 🍪 [Cookies](System%20Design/Cookies.md) — Client-side storage, security flags (`HttpOnly`, `Secure`, `SameSite`).
- 🔑 [Sessions](System%20Design/Session.md) — Server-side session management vs. client-side tokens.
- 🔄 [State Management](System%20Design/STATE%20MANAGEMENT.md) — Stateful vs. Stateless architectures, sticky sessions, centralized stores.
- 📈 [Scaling](System%20Design/SCALING.md) — Vertical vs. Horizontal scaling, bottleneck identification.
- ⚖️ [Scaling Algorithms & Strategies](System%20Design/SCALING%20ALGO.md) — Load balancing algorithms (Round Robin, Least Connections, Consistent Hashing).

---

## 🐧 Linux & Operating Systems

Comprehensive breakdown of OS internals and Linux system concepts:

- 📑 [Module 1: Filesystem & File Operations Notes](linux/Modules/mod1.md)
- 📄 [Module 1: Filesystem & File Operations PDF Guide](linux/Modules/Mod_1_Filesystem_and_File_Operations.pdf)

---

## 💻 How to Run Solutions

Ensure you have a C++ compiler (`g++` or `clang++` supporting C++17 or above).

### Compile and Run:
```bash
# Example: Running Trapping Rain Water
g++ -std=c++17 "Hard/Two_pointers/42_TrappingRainWater.cpp" -o solution
./solution
```

---

## 💡 Key Algorithmic Master Rules

1. **Sorted Array?** Consider **Two Pointers** or **Binary Search** first.
2. **Subarray / Substring Condition?** Consider **Sliding Window** or prefix sums.
3. **In-place Filtering?** Use **Slow-Fast Two Pointers** to maintain an $O(1)$ auxiliary space footprint.
4. **Extreme Comparisons / Pairs?** Use **Opposite-Direction Two Pointers** starting from `left = 0` and `right = n - 1`.
5. **Triplet / Quadruplet Reductions?** Sort first, fix outer element(s), and apply two pointers on the remainder.
