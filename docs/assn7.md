---
layout: math
title: "Assignment 7: Shortest Path Algorithms"
---

# Assignment 7: Shortest Path Algorithms

## 1125 Stockbroker Grapevine (1)

Trivial all-pair shortest path. Use Floyd-Warshall algorithm.

## 1847 Tram (1)

Edge weight is 0 if the switch is pointing at the edge, 1 otherwise. Then find the shortest path between A and B.

## 3259 Wormholes (3)

Trivial negative circle detection. Use Bellman-Ford algorithm.

## 3169 Layout (4) 

System of difference constraints. Lecture slides will tell you how to solve it.

$x_i-x_j\geq D$ is just $x_j-x_i\leq -D$.

Since "the cows are standing in the same order as they are numbered" (read problem description carefully!), don't forget to add implicit constraints $x_{i+1}-x_i\geq 0$.

## 2253 Frogger (4)

A simple $O(m\log m)$ solution is to add edges in increasing order of length, until the start point and the end point connects. This is fast enough, but there is faster solution.

Run a Dijkstra's algorithm with update rule changed to $d(u)\leftarrow\min\lbrace d(u),\max\lbrace d(v),w(u,v)\rbrace\rbrace$. We can prove that $d(v)$ is the minimum length of longest edge on paths to $u$, in the same way we prove the correctness of original Dijkstra's algorithm. This method has the same complexity as the original Dijkstra's algorithm, which can be as good as $O(m+n\log n)$.

## 3255 Roadblocks (5)

We first split evey undirected edge into two directed edges. This is okay because the problem allows a path to use edges multiple times. From now on, we only talk abou directed graph.

**Lemma**: Any non-shortest path contains an edge that doesn't belong to any shortest path.

**Proof**: Let $d(s,u)$ be the length of shortest path from the source $s$ to node $u$. Recall how shortest path algorithms works, and notice that $w(u,v)=d(s,v)-d(s,u)$ holds if and only if the edgeg $(u,v)$ belongs to some shortest path. If a path $(s, u_1, u_2, \dots, u_n, t)$ only contains such edges, its length will always be $d(s,u_1)+(d(s,u_2)-d(s,u_1))+\dots +(d(s,t)-d(s,u_n))=d(s,t)$, which means that it is a shortest path.

**Corollary**: Consider a second shortest path $p$. It must contain an edge $(u_p,v_p)$ that doesn't belong to any shortest path. Among all path from $s$ to $t$ that contain $(u_p,v_p)$, none of them is the shortest path (according to the lemma), so $p$ must be the shortest one.

**Solution**: For each edge $(u,v)$, let $f(u,v)$ be the length of the shortest path from $s$ to $t$ that contains it, and $f(u,v)=d(s,u)+w(u,v)+d(v,t)$, where $d(s,u)$ and $d(v,t)$ can be pre-computed for all nodes. Among $f(u,v)$ of all edges, the length of the shortest path (obviously) and the second shortest path (according to the corollary) are both included, so the second smallest value of $f(u,v)$ is the length of the second shortest path.

**Complexity**: Finding single source shortest path two times, plus $O(m)$ for finding $f(u,v)$.

## 1556 The Doors (5)

It is obvious that a shortest path changes direction only when it hits an obstacle. So we only need to consider sides of doors as vertices -- the shortest path must be straight line segments among them. Connect each pair of mutually visible vertices (which means nothing blocks the straight line between them) and find the shortest path. To check visibility, just naively loop through all pairs of vertices and all walls, which is $O(n^3)$.

## 2502 Subway (6)

Connect adjacant subway stations with length of travel time at subway speed, and connect all other pairs of points with length of travel time at walking speed, then find the shortest path.

## 1344 Tree Size Problem (6)

## 3463 Sightseeing (6)

The paths we are counting can only go through shortest edges (edge $(u,v)$ that $w(u,v)=d(u)-d(v)$) except going through shortest-plus-one edges ($w(u,v)=d(u)-d(v)+1$) no more than once. Since $d(u)$ are always non-decreasing along such paths, we can count them efficiently using DP. Let $dp(u,k)$ denote number of shortest or shortest-plus-one paths ending at $u$ that have gone through shortest-plus-one edges $k$ times ($k=0,1$). Then

$$
\begin{align}
dp(u,0)&=\sum_{w(u,v)=d(u)-d(v)}dp(v,0)\\
dp(u,1)&=\sum_{w(u,v)=d(u)-d(v)}dp(v,1)+\sum_{w(u,v)=d(u)-d(v)+1}dp(v,0)
\end{align}
$$

We can compute the $k=0$ part along with the Dijkstra algorithm, and then compute the $k=1$ in the order of increasing $d(u)$.

## 2135 Farm Tour (7)

## 2404 Jogging Trails (9, challenge problem)

We know that an Eulerian tour exists iff all nodes have even degree. If it is not true for our graph, we have to duplicate some edges. A Eulerian tour is shortest iff it has the smallest total length of duplicated edges, because all other edges (that is, all edges in the original graph) are traveled exactly once, and their total length is constant.

Let's eliminate one pair of odd nodes at a time, by duplicating all edges on the shortest path between them. If we try all arrangements for elimination (that is, try all ways of pairing up odd nodes), we can always find the optimal answer among them. That's because an optimal set of duplicated edges doesn't contain cycle, so it can always be decomposed into paths where no two paths share end nodes (choose two leaf nodes, remove all edges on paths between them, repeat), and all these paths must be shortest, so the optimal configuration is certainly visited by our searching process.

The number of such arrangements is $\frac{(2k)!}{k!2^k}$, where $k$ is half the number of odd nodes and $k\leq\lfloor n/2 \rfloor$. For $n\leq15$ this number is at most 135135, so exhaustive search methods can easily fit into the time limit.