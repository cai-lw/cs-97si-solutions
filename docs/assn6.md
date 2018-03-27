---
layout: math
title: "Assignment 6: Basic Graph Algorithms"
---

# Assignment 6: Basic Graph Algorithms 

## 1308 Is It A Tree? (1) 

Property 3 cannot be easily verified directly. Note that if the first two properties are satisfied, the root cannot have more than one path to another node. If there are two paths, they must meet somewhere, and at the meeting node there are two edges pointing at it, violating property 2. Therefore, we only need to rule out the case of having zero path, or in other words, unreachable.

Count the in-degree (how many edges are pointing to it) of each node and check the first two properties. If they are satisfied, find the root, then do a DFS or BFS from the root. If all nodes can be reached, it is a tree.

## 1258 Agri-Net (2) 

Trivial minimal spanning tree.

## 2488 A Knight's Journey (3) 

Naive DFS is fast enough for the given input range. Remember, always search the node with smallest lexicographical order first.

## 1164 The Castle (3) 

Trivial flood fill. Use bit operation to find whether a wall exists.

## 2395 Out of Hay (4) 

Recall that Kruskal's algorithm tries to add edges in the order of their weights. If the last edge added to the spanning tree has weight $w$, the answer to this problem is also $w$, because if we remove all edges with weight at least $w$, the Kruskal's algorithm will stop before completing a single connected spanning tree, which means the graph is not connected.

## 3177 Redundant Paths (4) 

(Solved)

## 1945 Power Hungry Cows (5) 

## 3275 Ranking the Cows (6) 

## 1985 Cow Marathon (7) 

(Solved)

## 2337 Catenyms (7) 

## 2186 Popular Cows (8, challenge problem) 

(Solved)

## 1944 Fiber Communications (8, challenge problem)