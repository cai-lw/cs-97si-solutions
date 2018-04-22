---
layout: math
title: "Assignment 8: Network Flow Problems"
---

# Assignment 8: Network Flow Problems

## Preface

I recommend using [Dinic's Algorithm](https://en.wikipedia.org/wiki/Dinic's_algorithm) whenever possible. It has decent performance ($O(V^2E)$ on general network, $O(\min\lbrace V^{2/3}E,E^{3/2}\rbrace)$ on unit capacity network) and simple implementation. Reference implementations can be found at [here (Chinese blog)](http://blog.csdn.net/STILLxjy/article/details/52039069) (I use this one) and [here (GeeksforGeeks)](https://www.geeksforgeeks.org/dinics-algorithm-maximum-flow/).

For min-cost max-flow, I found this [tutorial (TopCoder)](https://www.topcoder.com/community/data-science/data-science-tutorials/minimum-cost-flow-part-one-key-concepts/) very helpful.

The most difficult part of solving a network flow problem is **to recognize that it is a network flow problem**, but CS 97SI has eliminated this step for us! The second most difficult part is to construct the graph, and our solutions are mostly about that. The algorithm part is undoubtfully the easiest -- just write one and copy-paste everywhere!

## 1273 Drainage Ditches (1) 

Trivial network flow.

## 1274 The Perfect Stall (1) 

Trivial bipartite matching.

## 2112 Optimal Milking (4)

Always consider using binary search when the question is to minimize the maximum (or maximize the minimum).

We first find all pair shortest path (with Floyd-Warshall), then replace the original graph with direct connections between machines and cows, whose length are the shortest distance in the original graph. If we delete all connections longer than $d$, and we can still match all cows to machines, then the answer is less than $d$. Based on this fact, we can binary search the answer.

To find whether such match exists given $d$, connect the source to all $C$ cows with capacity 1, all $C$ cows to all $K$ machines with capacity 1 (excluding those distance larger than $d$), and all $K$ machines to the sink with capacity $m$. If the maximal flow is $C$ then such match is possible. This is very similar to finding bipartite matching with network flow.

## 3041 Asteroids (5)

We need [Kőnig's theorem](https://en.wikipedia.org/wiki/K%C3%B6nig%27s_theorem_(graph_theory)) for solving this problem, which is very important but not always covered by network flow tutorials. The theorem says that the size of the minimal vertex cover (a set of vertices that all edges connects to some of them) of a bipartite graph equals to the size of its maximal matching.

After having this theorem, the solution is straightforward. Create $N$ nodes for each row and $N$ nodes for each column, and connect nodes for row $i$ and column $j$ for every asteroid at $(i,j)$, then find the size of the minimal vertex cover (= maximal matching) of the graph.

## 3308 Paratroopers (6)

This time, we need the max-flow min-cut theorem.

Similar to the previous problem, we can immediately make a bipartite graph, but then what? This time we let $s\rightarrow i$ have capacity $\log r_i$, $j\rightarrow t$ have capacity $\log c_j$, and $i\rightarrow j$ have infinite capacity. A cut on the network with finite cut cost obviously only cuts $s\rightarrow i$ and $j\rightarrow t$. If we find such a cut, and install laser guns in rows and columns corresponding to cut edges, all paratroopers can be killed, because all $i\rightarrow j$ edges have at least one side cut (otherwise $s$ and $t$ is connected), and the cut cost equals to the logarithm of the total cost of installing laser guns. Hence, finding the minimal cut (= maximal flow) in this network and exponentiating it gives the answer.

## 2195 Going Home (6) 

Note that nothing can block the man, so the distance between a house and a man is just their Manhattan distance. Don't do any BFS or Dijkstra on the map.

Connect each man to each house with capacity 1 and cost equal to their distance, and connect source to men and houses to sink with capacity 1 and cost 0, then find the min-cost max-flow.

## 2516 Minimum Cost (7) 

Straighforward min-cost max-flow. Different kinds of goods are totally independent, so find min-cost max-flow on $k$ networks and sum up the answer.

## 2455 Secret Milking Machine (7)

Use the same binary search idea as 2112. Beware of multiple edges between the same pair of nodes.

## 2226 Muddy Fields (7) 

We only need to consider boards that cover a maximal consecutive segment of muddy patches. Each muddy patch can be covered by exactly two such boards, one horizontal and one vertical. By mapping boards to nodes and muddy patches to edges, it becomes a minimal vertex cover problem, almost identical to 3041.

## 3281 Dining (7) 

Split each cow into two nodes $cow_i^1, cow_i^2$. Connect dishes to $cow^1$, drinks to $cow^2$, and $cow^1_i$ to $cow^2_i$, all with unit capacity. Each path like $s \rightarrow dish_i \rightarrow cow_i^1 \rightarrow cow_i^2 \rightarrow drink_i \rightarrow t$ corresponds to a fed cow, so just find the maximum flow.

## 2391 Ombrophobic Bovines (8, challenge problem)

Almost the same as 2112, just with a larger input, requiring an efficient implementation.

## 3498 March of the Penguins (8, challenge problem)

For the $i$-th floe, create an "in" node $u_i$ and an "out" node $v_i$, an edge from $s$ to $u_i$ with capacity $n_i$, and an edge from $u_i$ to $v_i$ with capacity $m_i$. If one can jump from floe $i$ to floe $j$, create an edge from $v_i$ to $u_j$ with infinite capacity. If we want to know whether it's possible to gather all penguins at the $k$-th floe, create an edge from $u_k$ to $t$ with infinite capacity, and see whether the maximum flow equals to the total number of penguins. We need to do this $N$ times, requiring a very efficient implementation.