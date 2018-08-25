---
layout: math
title: "Assignment 4: Dynamic Programming (DP)"
---

# Assignment 4: Dynamic Programming (DP)

## 2663 Tri Tiling (1) 

Covered in lecture slides.

## 1163 The Triangle (1) 

A very classical DP introduction problem. $dp(i,j)=\max\lbrace dp(i-1,j-1),dp(i-1,j)\rbrace +a(i,j)$.

## 1160 Post Office (2) 

Let $dp(i,j)$ denotes the minimal sum of distances for the first $i$ villages, after building $j$ post offices among them, including one at the $i$-th village. The transition equation is straightforward: $dp(i,j)=\min_{k=j-1}^{i-1}\lbrace dp(k,j-1)+S(k,i)\rbrace$, where $S(k,i)$ denotes the sum of distances for villages in the interval $[k,i]$ when two post offices are at $k$-th and $i$-th villages and no other post office exists between them.

To efficiently compute $S(k,i)$, let's fix $k$ and increase $i$. Note that the boundary between villages served by the left post office and those served by the right one also increases monotonously, so we can use two pointer technique to maintaint the boundary, and compute each $S(k,i)$ in $O(1)$ with the assistance of a prefix sum array. This preprocessing takes $O(V^2)$, and the DP itself takes $O(V^2P)$.

## 2033 Alphacode (2)

(Same as [Leetcode 91: Decode Ways](https://leetcode.com/problems/decode-ways/))

To decode a character, you can consume 1 or 2 digits. Check whether consuming these digits are valid (the resulting number should be between 1 and 26 and has no leading zeros) and add decoding ways accordingly.

## 1159 Palindrome (3) 

(Same as [Leetcode 516: Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/))

Covered in lecture slides.

## 1050 To the Max (4) 

The one-dimensional version of the problem can be easily solved in $O(N)$. For the original two-dimensional problem, go through all possible upper and lower boundaries. For each case, combine all rows between boundaries into a single row, then solve the one-dimensional problem. The overall complexity is $O(N^3)$.

## 2127 Greatest Common Increasing Subsequence (6)

This is a pretty classical problem. The optimal solution is $O(N^2)$. See this [GeeksforGeeks article](https://www.geeksforgeeks.org/longest-common-increasing-subsequence-lcs-lis/) for the description of a $O(N^2)$ solution. However, the time limit of this question is (deliberately?) loose, so that carefully implemented $O(N^3)$ solution can also fit in.

## 1655 Balancing Act (6) 

Do a DFS to find the (rooted) subtree size for each node, then you can easily find the balance of each node. Note that for node $v$, the size of the connected component containing the root is $N$ minus the subtree size of $v$.

## 2292 Optimal Keypad (6) 

Same as any "dividing an array" problem, let $dp(i,j)$ be the minimal cost when dividing the first $i$ characters into $j$ keys, then $dp(i,j)=\min_{k=j-1}^{i-1}\lbrace dp(k,j-1)+cost(k,i)\rbrace$. As the scale of the problem is pretty small, you can just use brute force to compute $cost(k,i)$.

## 2430 Lazy Cows (7) 

## 2066 Minimax Triangulation (8, challenge problem)

(Note: this problem involves computational geometry. If you haven't learned it, skip this problem and come back after you learned Lecture 9)

Suppose that we connect two non-adjacant points $A_iA_j$ and divide the polygon into two, on of which is $A_iA_{i+1}\dots A_j$, (Note that this is not always possible, we will talk about how to check this later) and the triangulation of this polygon contains $A_iA_jA_k$. We have recursive sub-problems here: since we connected $A_iA_k$ and $A_jA_k$, we need to find the triangulation of $A_iA_{i+1}\dots A_k$ and $A_kA_{k+1}\dots A_j$. So we can devise an interval DP solution: Let $dp(i,j)$ be the minimax value of the polygon $A_iA_{i+1}\dots A_j$, the transition equation is $dp(i,j)=\max_{k=i+1}^{j-1}\lbrace\min\lbrace S_{\Delta A_iA_jA_k},dp(i,k),dp(k,j)\rbrace\rbrace$. Beware that you need to handle wrap-around intervals. The complexity of DP is $O(N^3)$

Now let's resolve the problem we left earlier: how to check whether $A_iA_j$ properly divides the polygon into two. For $A_iA_j$ to be valid, it must be entirely inside the polygon. We first make sure that $A_iA_j$ doesn't intersect with any edge of the polygon. If this test passed, $A_iA_j$ is either entirely outside or entirely inside the polygon, so we pick a random point on $A_iA_j$ and shoot a random ray from it for an inside-outside test. Using this method, testing each pair of points takes $O(N)$, so it takes $O(N^3)$ to test all of them, making the overall complexity of our solution $O(N^3)$.

## 1038 Bugs Integrated, Inc. (9, challenge problem)

Because $M$ is small, we fill the board column by column. When trying to put chips on column $i$, we need the state of column $i-1$ and $i-2$ to determine whether there are space for 2x3 or 3x2 chips. If we naively consider all $2^M$ states of a column, each state transition will take $O(2^{3M})$, which is unacceptable.

To cut down the number of states, let's first ignore bad squares on the plate. We only need to consider states that can be formed using 2x1 and 3x1 strips. There are only $S=201$ such states when $M=10$, significantly smaller than $2^{10}=1024$. Now let's put back the bad squares, and in some columns some states becomes impossible, so we ignore them when we perform state transition. In each state transition, we do a brute force search over all arrangements of chips in the new column, and check if they are valid. The overall complexity is $O(S^3N)$ with a fairly small constant, since many state transitions are not possible. Trying to calculate $S$ for larger $M$ reveals that $S$ is approximately $1.7^M$, so the complaxity can also be expressed as $O(1.7^{3M}N)$.