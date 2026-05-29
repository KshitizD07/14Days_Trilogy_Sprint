# Extra Questions and Advanced Topics - Compiler Design Solutions

This document covers additional topics and questions found in the Previous Year Questions (PYQs).

---

## 5. Postfix Translation for `a * b + c`: Detailed Trace

### Step 1: Priority Table (ISP & ICP)
| Operator | In-Stack Priority (ISP) | Incoming Priority (ICP) |
| :---: | :---: | :---: |
| `+` , `-` | 2 | 2 |
| `*` , `/` | 4 | 4 |
| `^` | 5 | 6 |
| `id` | 8 | 7 |
| `$` | 0 | - |

### Step 2: Stack-Based Trace
| Input Symbol | Stack | Postfix Expression | Action |
| :--- | :--- | :--- | :--- |
| `a` | `$` | `a` | Output `a` |
| `*` | `$ *` | `a` | Push `*` (ICP > ISP of $) |
| `b` | `$ *` | `a b` | Output `b` |
| `+` | `$ +` | `a b *` | Pop `*` (ISP * > ICP +), Push `+` |
| `c` | `$ +` | `a b * c` | Output `c` |
| `$` | `$` | `a b * c +` | Pop all until `$` |

**Final Result:** `a b * c +`

---

## 1. Operator Precedence Parser & Table

### Operator Precedence Table for `+, *, id`
| | `+` | `*` | `id` | `$` |
| :---: | :---: | :---: | :---: | :---: |
| **`+`** | `·>` | `<·` | `<·` | `·>` |
| **`*`** | `·>` | `·>` | `<·` | `·>` |
| **`id`**| `·>` | `·>` | | `·>` |
| **`$`** | `<·` | `<·` | `<·` | |

**Relations:**
- `id` has higher precedence than `+` and `*`.
- `*` has higher precedence than `+`.
- `+` and `*` are left-associative (reflected by `·>` in their own rows/cols).

---

## 4. Main issues in the design of a Code Generator.
(Input, Target, Selection, Allocation, Order, Management - detailed in previous version)
