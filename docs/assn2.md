---
layout: math
title: "Assignment 2: Mathematics"
---

# Assignment 2: Mathematics

## 1799 Yeehaa! (1)

(TODO: add a figure)

$$
r=(R-r)\sin\frac{\pi}{n}\implies r=\frac{R}{1+1/\sin\frac{\pi}{n}}
$$

## 1401 Factorial (1)

Number of trailing 0's equals to 5's power in $n!$'s factorization. We are counting how many 10's we can divide from $n!$, and $10=2\times5$, and $n!$ apparently has much more 2's than 5's, so the number of 5's is the bottleneck. The answer is 

$$
\sum_{i=1}^{\lfloor\log_5 n\rfloor} \lfloor\frac{n}{5^i}\rfloor
$$

## 2262 Goldbach's Conjecture (2)

Trivial.

## 2242 The Circumference of the Circle (2)

There are may formulas for the radius of the circumscribed circle of a triangle, but the best one for this problem is $R=\frac{abc}{4A}​$, where ​$a,b,c​$ are lengths of the three edges, and its area ​$A=\sqrt{s(s-a)(s-b)(s-c)}, s=\frac{a+b+c}{2}​$.

Refer to the Wikipedia page [Circumscribed Circle](https://en.wikipedia.org/wiki/Circumscribed_circle#Other_properties) for more properties and formulas.

## 1654 Area (3)

(TODO: add a figure)

For each step, accumulate the area of a small triangle between the step and the original point. It can be effectively computed with vector cross product. Suppose you are at $(x,y)$ before the step, and $(x+\Delta x,y+\Delta y)$ after, the area of the triangle is $\Delta A=(x,y)\times(\Delta x,\Delta y)=x\Delta y-y\Delta x$. Notice that it can be negative. That's what we called **signed area**, and we can only get the correct when using signed area, as it will cancel out areas outside the polygon when we finish a closed path.

## 2309 BST (3)

Let `lowbit(x)` be the lowest 1-bit in `x`'s binary representation (For example, `lowbit(20)==lowbit(0b10100)==0b100==4` ). Observe that the size of the subtree rooted at `x` is `lowbit(x)*2-1`, so the output is `x-lowbit(x)+1` and `x+lowbit(x)-1`.

The `lowbit` function can be efficiently computed as `lowbit(x)=x&(-x)`. It is useful in several data structures.

## 2693 Chocolate Chip Cookies (4)

(TODO: add a figure)

A simple observation is that we only need to consider circles that has at least two points on its border (imaging moving the circle around). Simply checking all these circles against all points ($O(n^3)$) is enough for passing the test.

We can use vector math to find the center of the circle (solving quadratic equations also works but seems cumbersome). Let $\textbf{v}_m=(x_m,y_m)=(\frac{x_1+x_2}{2},\frac{y_1+y_2}{2})$ be the midpoint of two points, and $\textbf{v}_h=(x_h,y_h)=(y_1-y_2,x_2-x_1)$ be the vector between two points rotated by 90 degree, then $\textbf{v}_c=(x_c,y_c)=\textbf{v}_m+\textbf{v}_h\frac{\sqrt{R^2-\lVert\textbf{v}_h\rVert^2/4}}{\lVert\textbf{v}_h\rVert}$

## 2084 Game of Connections (4)

Cut the circle open between point 1 and point 2n and pull it into a straight line. Because connections between 2n points on the line don't intersect, every arrangement of connection uniquely maps to (i.e. bijection) a **valid bracket sequence of length 2n**: the left end of a connection is the left bracket, and vice versa. We can count bracket sequences using DP: `dp[i][j]=dp[i-1][j-1]+dp[i-1][j+1]`, where `dp[i][j]` means there are `j` left brackets in excess when the sequence length is `i`, and `dp[2*n][0]` gives the answer.

As the hint in CS 97SI says, the number is too large for any fixed-sized integer types, so we must implement big integers if we are using languages that don't natively support them (such as C and C++). In this question we only need big integer addition, which is relatively easy to implemement. Just think about how you do large number addition on paper, and translate the process into code.

## 2085 Inversion (5)

To find the lexicographically smallest permutation, we greedily choose the smallest possible number at every step. By "possible" we mean that the remaining numbers can still make enough inverse pairs. By observing the following facts:

* $k$ numbers can make $k(k-1)/2$ inverse pairs at most. 
* The order of numbers behind a number doesn't affect how many inverse pairs it makes.

We can come up with the following algorithm. Suppose that at some time we have $k+1$ numbers left and wants to choose one number to append to the sequence. If $k(k-1)/2\leq m$ we choose the smallest number, otherwise choose the $(m-k(k-1)/2)$-th smallest number. Notice that we always take the smallest or largest number from remaining numbers, except once. Therefore, we can simply use an array to keep track of remaining numbers, and the complexity is $O(n)$.

## 1426 Find the Multiple (6)

Let $L$ be the number of digits of $m$. The problem says $L\leq100$, but it turns out that for $1\leq n\leq200$ we can always find $m$ within the range of 64-bit integer, or $L\leq18$. Therefore, a brute force search with complexity $O(2^L)$ is enough for an AC.

A better approach resembles the backpack problem and runs in $O(nL)$. Let $\lbrace 10^i, 0\leq i \leq n\rbrace$ be "items" and the backpack "wraps" by modulo $n$. The DP equation is `dp[i][j]=dp[i-1][j] || dp[i-1][(j-10^i)%n]`, where `dp[i][j]` means whether there is a `i`-digit `0-1` number that equals to `j` modulo `n`. We also need to keep track of the previous state of each state to recover $m$ when we find a solution.

## 2356 Find a Multiple (7, challenge problem)



## 1148 Utopia Divided (9, challenge problem)

