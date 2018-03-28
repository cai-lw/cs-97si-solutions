---
layout: math
title: "Assignment 5: Combinatorial Games"
---

# Assignment 5: Combinatorial Games 

## 2234 Matches Game (1) 

Trivial Nim.

## 2484 A Funny Game (2) 

For $N\geq 5$, after Alice's first move, the remaining coins form a sequence. Then, Bob removes the one or two coin(s) (depending on the parity of the number of coins) in the middle to split it into two sequences of same length. After that, Bob always imitates Alice's move to keep two sequences identical. In this way, Bob can always win.

For $N\leq 4$, it turns out that Alice can only win when $N\leq 2$.

## 3480 John (3) 

## 2505 A multiplication game (3) 

Simply do a DP on all reachable numbers from the largest down to 1, to find whether each number is a winning state or a losing state. The number of reachable numbers is 6623, so this is fast enough.

## 1678 I Love this Game! (3) 

(Solved)

## 1704 Georgia and Bob (5) 

## 2960 S-Nim (5) 

Just follow the definition on lecture slides and find the Grundy number of all single pile states, then XOR them together.

## 2232 New Stone-Forfex-Cloth Game (6) 

## 2348 Euclid's Game (6)

Consider "*turning points*" (TPs) where the number being subtracted from (`x`) becomes smaller than another number (`y`), and let the *distance* to the next TP be `x/y`(integral division). A move decreases the distance by any positive integer, without making it negative. If the distance becomes zero after a move, we reached a TP, and we reset the distance to the next TP.

As a single move cannot go through a TP, we only need to consider states of TPs. We can recursively find them as the following:

* If the next TP is a losing state, the current TP is a winning state. (Directly go to the next TP)
* If the next TP is a winning state, and the distance between the two TPs is 1, the current TP is a losing state. (You have no choice)
* If the next TP is a winning state, and the distance between the two TPs is larger than 1, the current TP is a winning state. (Decrease the distance to 1)

Each TP corresponds to a step in Euclid's greatest common divisor (GCD) algorithm, hence the name of the problem. All TPs, distances, and winning/losing states can be found with this algorithm in $O(\log n)$.

## 1143 Number Game (7)

(Solved)

## 3317 Stake Your Claim (7) 

## 1740 A New Stone Game (7) 