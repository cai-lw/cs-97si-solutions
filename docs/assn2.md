---
title: "Assignment 2: Mathematics"
---

# Assignment 2: Mathematics

## 1799 Yeehaa! (1)

(TODO: add a figure)

$$
r=(R-r)\sin\frac{\pi}{n}\implies r=\frac{R}{1+1/\sin\frac{\pi}{n}}
$$

## 1401 Factorial (1)

Number of trailing 0's equals to 5's power in $$n!$$'s factorization. We are counting how many 10's we can divide from $$n!$$, and $$10=2\times5$$, and $$n!$$ apparently has much more 2's than 5's, so the number of 5's is the bottleneck. The answer is 
$$
\sum_{i=1}^{\lfloor\log_5 n\rfloor} \lfloor\frac{n}{5^i}\rfloor
$$

## 2262 Goldbach's Conjecture (2)

Trivial.

## 2242 The Circumference of the Circle (2)

There are may formulas for the radius of the circumscribed circle of a triangle, but the best one for this problem is $$R=\frac{abc}{4A}$$, where $$a,b,c$$ are lengths of the three edges, and its area $$A=\sqrt{s(s-a)(s-b)(s-c)}, s=\frac{a+b+c}{2}$$.

Reference: https://en.wikipedia.org/wiki/Circumscribed_circle#Other_properties

## 1654 Area (3)



## 2309 BST (3)

Let `lowbit(x)` be the lowest 1-bit in `x`'s binary representation (For example, `lowbit(20)==lowbit(0b10100)==0b100==4` ). Observe that the size of the subtree rooted at `x` is `lowbit(x)*2-1`, so the output is `x-lowbit(x)+1` and `x+lowbit(x)-1`.

The `lowbit` function can be efficiently computed as `lowbit(x)=x&(-x)`. It is useful in several data structures.

## 2693 Chocolate Chip Cookies (4)




## 2084 Game of Connections (4)



## 2085 Inversion (5)




## 1426 Find the Multiple (6)

Let $$L$$ be the number of digits of $$m$$. The problem says $$L\leq100$$, but it turns out that for $$1\leq n\leq200$$ we can always find $$m$$ within the range of 64-bit integer, or $$L\leq18$$. Therefore, a brute force search with complexity $$O(2^L)$$ is enough for an AC.

A better approach resembles the backpack problem and runs in $$O(nL)$$. Let $$\{10^i, 0\leq i \leq n\}$$ be "items" and the backpack "wraps" by modulo $$n$$. The DP equation is `dp[i][j]=dp[i-1][j] || dp[i-1][(j-10^i)\%n]`, where `dp[i][j]` means whether there is a `i`-digit `0-1` number that equals to `j` modulo `n`. We also need to keep track of the previous state of each state to recover $$m$$ when we find a solution.

## 2356 Find a Multiple (7, challenge problem)



## 1148 Utopia Divided (9, challenge problem)

