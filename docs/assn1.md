---
layout: math
title: "Assignment 1: Coding Exercise"
---

# Assignment 1: Coding Exercise

## 1000 A+B Problem (0)

It's so easy that you don't even need to write code yourself.

## 1004 Financial Management (0)

The problem itself is boring, but you should learn how to check EOF and set output precision. They are very useful when dealing with input/output formats in many POJ problems.

## 1003 Hangover (1)

Just do what it tells you to do.

## 1007 DNA Sorting (2)

For each string, you can simply compare all pairs of characters in $O(n^2)$, or keep tracs of how many A's, C's, G's and T's there are before each character, and count inversions in $O(n)$. Both are acceptable for this problem.

## 2136 Vertical Histogram (2)

Beware that you cannot print any spaces after the last `*` in a row. One way to achieve this is only printing spaces before printing a `*`. You will need to know where the previous `*` is and how many space between them you should print.

## 2140 Herd Sums (3)

Sum of consecutive integers from $a$ to $b$ (inclusive) is $S=(a+b)(b-a+1)/2$. Notice that $a+b$ and $b-a+1$ must have different parity. If $2S$ is the product of an odd number and an even number, they corresponds to a valid and unique solution by letting the larger number be $a+b$ and the smaller be $b-a+1$. Therefore, the problem is reduced to counting how many ways $2S$ can be decomposed into an odd number and an even number, which can be solved by simple enumeration in $O(\sqrt S)$.

## 1504 Adding Reversed Numbers (3)

Making use of conversion functions between integer and string in standard libraries (in C and C++, `atoi` for string to integer, and `sprintf` for integer to string) can save you a lot of time. Reverse the two strings, convert to integers, add, convert back to string, reverse again, remove leading zeros, and output.

## 1806 Manhattan 2025 (4)

Pretty straightforward. Just print what it tells you to print.

## 1001 Exponentiation (5)

Basic big integer operation. To avoid operating non-integers, remove the decimal point, do integer multiplications, and put it back in the right place.

## 1922 Ride to School (5)

There is an important observation: if A departs later than Charley but arrives earlier, Charley arrives no later than A. If Charley has never followed A, he must arrive earlier than A. If Charley follows A at some time, he either follows A all the way to the destination, or changes to follow another faster person, who must arrive earlier than A.

Based on the observation, we only need to find the earliest arriving person who departs later than Charley, and Charley will arrive at the same time as that person.

## 3251 Big Square (6, challenge problem)

## 1403 Hotline (9, challenge problem)