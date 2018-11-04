---
layout: math
title: "Assignment 10: String Algorithms"
---

# Assignment 10: String Algorithms

## 1936 All in All (1)

(Same as [Leetcode 392: Is Subsequence](https://leetcode.com/problems/is-subsequence/))

Let $dp(i)$ be the maximum length of prefix of $s$ that is a substring of $t$'s $i$-character prefix.

$$
dp(i)=
\begin{cases}
dp(i-1) &t_i \neq s_{dp(i-1)+1}\\
dp(i-1)+1 &t_i = s_{dp(i-1)+1}\\
\end{cases}
$$

## 2408 Anagram Groups (2)

For C++ users, maps are not recommended here, although they are straightforward to use. Not only `unordered_set` is not available in C++98, but since POJ doesn't turn on any optimization, STL containers are incredibly slow and can easily lead to TLE. Let's solve this problem with sorting.

Note that two strings are in the same anagram group iff they are the same after sorted by characters. Sort strings by their character-sorted version (breaking ties by the original string), then scan and find all anagram groups. Sort anagram groups by their size, and output the first 5.

## 2359 Questions (3)

Trivial [Josephus Problem](https://en.wikipedia.org/wiki/Josephus_problem#The_general_case). See the Wikipedia page if you don't know how to solve it quickly.

## 1750 Dictionary (3)

I don't think there is any natural interpretation to the definition of "dictionary", so please just look at [my code](https://github.com/cai-lw/cs-97si-solutions/tree/master/assn10/1750.cpp) (it's very short and simple).

## 2752 Seek the Name, Seek the Fame (4)

Recall how KMP works. If `next[i]=k`, the longest prefix-suffix of `S[0..i]` is `S[0..k]` (except `S[0..i]` itself), and other shorter prefix-suffixes are also prefix-suffixes of `S[0..k]`. So, just "jump back" (do `i=next[i]` until `i==-1`, as it does in KMP) from `n-1` and output all numbers produced.

## 1961 Period (5)

For a valid `K>1` we will have `S[0..N-N/K-1]==S[N/K..N-1]`, so the largest `K` corresponds to the longest prefix-suffix (as defined in the previous problem), which is `next[N-1]` (the `next` array in KMP). If `N-next[N-1]` divides `N` then `K==N/(N-next[N-1])`, otherwise the string can't be periodic and `K` doesn't exist. We can easily run KMP and output all results in $O(N)$.

## 1147 Binary codes (6) 

## 3261 Milk Patterns (6)

This is very simlar to 1961, except that repeating partterns may not start from the beginning of the string. So insted of KMP, we have to build suffix array to find equal substrings. If prefix starting at `i,j(i<j)` has longest common prefix of length `(j-i)*(K-1)`, then there is a pattern repeating itself `K` times starting at `i`.

## 2185 Milking Grid (7)

Let's first consider the one-dimensional version. A string `S` has period `T` if and only if `S[0..N-T-1]==S[T..N-1]`, so its smallest period corresponds to its longest prefix-suffix, which can be found by KMP in $O(N)$.

For the original two-dimensional problem, the answer is just the product of the smallest row period and the smallest column period.

## 3349 Snowflake Snow Snowflakes (7)

We need a string hash function that is invariant upon rotating or reversing. Simply adding or xor-ing all numbers (or after applying a single-variable function) together is a bad idea, since all permutations will have the same hash.

The hash function I use is xor-ing the polynomial hash of all rotations and reverses. Since adding/removing a charactor at front/back only takes $O(1)$ to update the polynomial hash, it only takes $O(L)$ to compute hashes of all rotations, (where $L$ is the length of the string, and $L=6$ in this problem) leading to a total complexity of $O(NL)$.

It should be noticed that, to completely avoid hash collision (so that exact equal comparison is not necessary) over $2^m$ objects, the hash value should use more than $2m$ bits, not just $m$, due to the infamous [birthday paradox](https://en.wikipedia.org/wiki/Birthday_problem). In competitive programming, this normally means a 64-bit hash.

## 3167 Cow Patterns (8, challenge problem)

## 2774 Long Long Message (9, challenge problem)

Simple $O(n^2)$ DP solution is not fast enough for this problem. However, if you meet this problem in an interview (it is indeed a common interview question), DO USE the DP solution because most interviewers don't know suffix array. :)

Create string $S=A\#B$ (where # is a character that doesn't appear in either $A$ or $B$) and construct the suffix array of $S$. For each pair of adjacant suffixes that one starts in the $A$ part and the other starts in the $B$ part, find their common prefix, and the longest one will be the answer. Complexity is $O(n\log n)$.

This is correct because of the monotonicity of longest common prefixes (LCPs) in the suffix array: for three suffixes $A<B<C$ we have $LCP(A,B)\geq LCP(A,C)\leq LCP(B,C)$. For a suffix starting in the $A$ part, its LCP in the $B$ part must be either its left-closest or right-closest $B$ part suffix. We can repeatly apply this argument and induce that we only need to consider adjacant pairs of suffixes.