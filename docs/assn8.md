---
layout: math
title: "Assignment 8: Network Flow Problems"
---

# Assignment 8: Network Flow Problems

## Preface

I recommend using [Dinic's Algorithm](https://en.wikipedia.org/wiki/Dinic's_algorithm) whenever possible. It has decent performance ($O(V^2E)$ on general network, $O(\min\lbrace V^{2/3}E,E^{3/2}\rbrace)$ on unit capacity network) and simple implementation. Reference implementations can be found at [here (Chinese blog)](http://blog.csdn.net/STILLxjy/article/details/52039069) (I use this one) and [here (GeeksforGeeks)](https://www.geeksforgeeks.org/dinics-algorithm-maximum-flow/).

The most difficult part of solving a network flow problem is **to recognize that it is a network flow problem**, but CS97SI has eliminated this step for us! The second most difficult part is to construct the graph, and our solutions are mostly about that. The algorithm part is undoubtfully the easiest -- just write one and copy-paste everywhere!

## 1273 Drainage Ditches (1) 

Trivial network flow.

## 1274 The Perfect Stall (1) 

Trivial bipartite matching.

## 2112 Optimal Milking (4)

Always consider using binary search when the question is to minimize the maximum (or maximize the minimum).

We first find all pair shortest path (with Floyd-Warshall), then replace the original graph with direct connections between machines and cows, whose length are the shortest distance in the original graph. If we delete all connections longer than $d$, and we can still match all cows to machines, then the answer is less than $d$. Based on this fact, we can binary search the answer.

To find whether such match exists given $d$, connect the source to all $C$ cows with capacity 1, all $C$ cows to all $K$ machines with capacity 1 (excluding those distance larger than $d$), and all $K$ machines to the sink with capacity $m$. If the maximal flow is $K$ then such match is possible. This is very similar to solving bipartite matching with network flow.

## 3041 Asteroids (5)

We need [Kőnig's theorem](https://en.wikipedia.org/wiki/K%C3%B6nig%27s_theorem_(graph_theory)) for solving this problem, which is very important but not always covered by network flow tutorials. The theorem says that the size of the minimal vertex cover (a set of vertices that all edges connects to some of them) of a bipartite graph equals to the size of its maximal matching.

After having this theorem, the solution is straightforward. Create $N$ nodes for each row and $N$ nodes for each column, and connect nodes for row $i$ adn column $j$ for every asteroid at $(i,j)$, then find the size of the minimal vertex cover of the graph.