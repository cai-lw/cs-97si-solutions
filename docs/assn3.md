---
layout: math
title: "Assignment 3: Data Structures"
---

# Assignment 3: Data Structures

## 2418 Hardwood Species (1) 

Trivial usage of map. Be careful when reading inputs, as tree names can contain spaces. For C/C++ users, use `fgets`.

## 1330 Nearest Common Ancestors (3)

[Lowest common ancestor](https://en.wikipedia.org/wiki/Lowest_common_ancestor) is an important problem and has many algorithms. However in this problem we only process **ONE** query, so all these techniques are unnecessary. Just find the path to the root for two given nodes, and see where the two paths intersect.

## 3367 Expressions (3) 

(TODO: find a proof)

The sample input/output is complex enough for us to observe a pattern: (sorry I can't prove the pattern yet, but it passed POJ tests)

The answer is the sequence of characters of traversing the expression tree **layer by layer, bottom-up (start from the deepest layer), left to right**. This process is just the reverse of BFS, so you can do a right-to-left BFS and reverse the output to get the answer.

If you don't know how to build an expression tree, see [expression tree on Wikipedia](https://en.wikipedia.org/wiki/Binary_expression_tree).

## 1984 Navigation Nightmare (5) 

We first ignore queries and build the whole tree, then use DFS to find the coordinate of all nodes. A node's coordinate is determined by its parent's coordinate and the direction and length of the edge between them, which can be computed recursively.

Now we process queries in time order. Add edges one by one and use union-find sets to keep track of connectivity. If two nodes are not connected (belong to different sets) then output -1, otherwise output their distance.

## 1785 Binary Search Heap Construction (5) 

Sort nodes by key first. Then, according to the hint, we find the node with highest priority and let it be the root, and then split the array into two halves and solve then recursively.

If we find the root naively, the worst case complexity would be $O(n^2)$. To achieve $O(n\log n)$ we need a device for [Range minimum/maximum query](https://en.wikipedia.org/wiki/Range_minimum_query). Because the initial sorting already costs $O(n\log n)$, this is good enough.

Actually, the tree we are building is a [Cartesian tree](https://en.wikipedia.org/wiki/Cartesian_tree), and there are multiple algorithms that can construct it in $O(n)$. My solution uses one of them.

## 1988 Cube Stacking (6)

Use special union-find structure that:

* Always use the bottommost block as representative. (so we can't use rank optimization)
* Every block stores the distance to its parent block. (the distance can be uploaded when performing path compression)

For `M x y`, set the parent of `find(y)` to `find(x)` and update `find(y)`'s distance. (To find this distance, we need to additionally record the size of each set, which is easy to maintain) For `C x`, call `find(x)` and accumulate distances along the path to the bottom, performing path compression at the same time.

According to [Wikipedia](https://en.wikipedia.org/wiki/Disjoint-set_data_structure) , each `find` costs (amortized) $O(\log n)$ when using path compression alone, which is fast enough.

## 1703 Find them, Catch them (6) 

We still use union-find sets for this problem. For each person, create two elements $A_i$ and $\bar{A}_i$. For `D i j`, merge $A_i, \bar{A}_j$ and $\bar{A}_i, A_j$. For `A i j`, if $A_i, A_j$ are in the same set they are in the same gang, if $A_i, \bar{A}_j$ are in the same set they are in different gangs, otherwise we don't know.

## 2274 The Race (6) 

## 3321 Apple Tree (6) 

Knowing the following fact is crucial for this problem: in the depth-first traversal of a tree, **every subtree corresponds to a continuous interval**.

Do a DFS to find the traversal sequence, as well as the interval for each subtree. Now we can convert queries on subtree sum into interval sum on the sequence, which can be effectively found using Fenwick tree.

## 1175 Picture (7, challenge problem) 

## 1195 Mobile phones (8, challenge problem)

(Same as [Leetcode 302: Range Sum Query 2D - Mutable](https://leetcode.com/problems/range-sum-query-2d-mutable), subscribers only)

Obviously we need the two-dimensional version of Fenwick tree. The extension is straightforward and intuitive, so I just post my code here without further explanation. The complexity for both operations are $O(\log^2S)$.

The sum in a rectangle $[x,a]\times[y,b]$ (all boundaries are inclusive) can be expressed as `sum(a,b)-sum(a,x-1)-sum(y-1,b)+sum(x-1,y-1)`.

```c++
class Bitree2 {
    vector<vector<int> > a;
public:
    Bitree2(int n): a(n + 1, vector<int>(n + 1, 0)) {}
    void add(int i, int j, int d) {
        int j0 = j;
        while (i < a.size()) {
            j = j0;
            while (j < a.size()) {
                a[i][j] += d;
                j += j & (-j);
            }
            i += i & (-i);
        }
    }    
    int sum(int i, int j) {
        int ret = 0, j0 = j;
        while (i > 0) {
            j = j0;
            while (j > 0) {
                ret += a[i][j];
                j -= j & (-j);
            }
            i -= i & (-i);
        }
        return ret;
    }
};
```

## 2750 Potted Flower (9, challenge problem)

To avoid handling wrap-around intervals, notice that the sum of a wrap-around interval $[a,n]\cup[1,b]$ can be expressed as $S(1,n)-S(b+1,a-1)$, where $S(x,y)$ is the sum of a non-wrap-around interval $[x,y]$. Therefore, the maximum sum of wrap-around intervals equals to $S(1,n)$ minus the minimum sum of non-wrap-around intervals.

To find the answer, we need a data structure that can efficiently find the maximum and minimum interval sum of a mutable array. We use a segment tree which maintains 4 values on each node. Their definitions and update rules are summarized below. 

| Definition                                    | Update rule                                         |
| --------------------------------------------- | --------------------------------------------------- |
| $s(l,r)=S(l,r)$                               | $s(l,r)=s(l,m)+s(m',r)$                             |
| $ls(l,r)=\max_{l \leq b \leq r} S(l,b)$       | $ls(l,r)=\max\{ls(l,m), s(l,m)+ls(m',r) \}$         |
| $rs(l,r)=\max_{l \leq a \leq r} S(a,r)$       | $rs(l,r)=\max\{rs(m',r), s(m',r)+ls(l,m) \}$        |
| $ms(l,r)=\max_{l\leq a \leq b \leq r} S(a,b)$ | $ms(l,r)=\max\{ms(l,m),ms(m',r),rs(l,m)+ls(m',r)\}$ |

Same as other segment trees, single element update can be done in $O(\log n)$, and the maximum interval sum is just $ms(1,n)$ which can be read in $O(1)$. Finding the minimum interval sum is very similar, but the easiest way (requires least coding) is to instantiate another identical segment tree, just with all data negated.

Finally, beware that it's not allowed to use the whole array as an interval. This happens if and only if when all elements are positive, and then the answer will be $S(1,n)$ minus the smallest element. It's easy to check and answer this special case in an additional $O(1)$ time per query.