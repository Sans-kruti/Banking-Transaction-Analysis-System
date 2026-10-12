# Banking Transaction Analysis System

## Overview
The Banking Transaction Analysis System is a menu-driven C application that applies the Divide and Conquer approach to banking transaction records. It implements Merge Sort, Quick Sort, and Binary Search to sort and search transactions efficiently.

## Features
- Store transaction ID, customer ID, date, transaction type, and amount.
- Sort transactions by transaction ID, customer ID, or amount.
- Search for transactions using Binary Search.
- Identify the highest and lowest transaction amounts.
- Display comparison counts and recursive function calls.
- Display a message when a transaction is not found.

## Algorithms Used
- **Merge Sort:** O(n log n) time complexity.
- **Quick Sort:** O(n log n) average time complexity; O(n²) worst case.
- **Binary Search:** O(log n) time complexity on sorted records.

## Technologies Used
- C Programming Language
- Structures and Arrays
- Divide and Conquer
- Algorithm Performance Analysis

## How to Compile and Run

Compile using GCC:

```bash
gcc banking_analysis.c -o banking_analysis
```

Run on Windows:

```bash
banking_analysis.exe
```

Run on Linux or macOS:

```bash
./banking_analysis
```

## Menu Options
1. Merge Sort
2. Quick Sort
3. Binary Search by Transaction ID
4. Find Highest and Lowest Transaction
5. Display All Transactions
0. Exit

## Objective
To apply Divide and Conquer algorithms to structured banking records, enforce search preconditions, and study algorithm scalability as the number of transactions increases.

## Limitations
- Supports up to 1,000 transactions per execution.
- Binary Search operates on transaction IDs after sorting.
- Transaction records are stored in memory and are not saved permanently.

## Author
Academic project for the study of Design and Analysis of Algorithms.
