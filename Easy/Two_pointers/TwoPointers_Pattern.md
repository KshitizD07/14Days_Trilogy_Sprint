The Two Pointer pattern is a fundamental algorithmic technique used to solve array and string problems efficiently. Instead of using nested loops which often result in O(n2)-time complexity-
two pointers allow you to traverse the data structure in a single pass, often achieving O(n) time complexity. 
When to use this pattern:
•	The array or string is sorted (or can be sorted). 
•	You need to find pairs or triplets that satisfy certain conditions. 
•	You need to modify the array in-place. 
•	You need to compare elements from different positions. 
•	You're looking for a subsequence or subarray with specific properties. 


Master Rules & Summary
Pattern Classification
1.	Same Direction (Slow-Fast): Used for in-place filtering (e.g., Remove Duplicates, Move Zeroes). 
2.	Opposite Direction: Used for comparing extremes or finding pairs (e.g., 2Sum, Container Water, Sorted Squares). 
3.	Fix One + Two Pointers: Used to reduce 3-element problems to 2-element problems (e.g., 3Sum). 
4.	Reverse Fill: Filling from back to front to save space (e.g., Merge Sorted Arrays). 
Key Master Rules
•	Rule 1: Sorted array? Think Two Pointers FIRST. 
•	Rule 2: Define pointer roles and invariants in comments before coding. 
•	Rule 3: Ensure at least one pointer moves in EVERY iteration to avoid infinite loops. 
•	Rule 4: Never re-sort data that is already sorted; exploit the existing structure. 
•	Rule 5: Distinguish between Index vs. Value (e.g., comparing i vs. nums[i]). 
