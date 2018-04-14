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

(Solved)

## 2502 Subway (6)

(Solved)

## 1344 Tree Size Problem (6)

## 3463 Sightseeing (6)

(Solved)

## 2135 Farm Tour (7)

## 2404 Jogging Trails (9, challenge problem)