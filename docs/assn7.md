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

(Solved)

## 3255 Roadblocks (5)

(Solved)

## 1556 The Doors (5)

(Solved)

## 2502 Subway (6)

(Solved)

## 1344 Tree Size Problem (6)

## 3463 Sightseeing (6)

(Solved)

## 2135 Farm Tour (7)

## 2404 Jogging Trails (9, challenge problem)