# Matrix-Functions
 Functions on 5x5 sparse matrices in the form of linked lists.
 
 This program was assigned to me as a mid-term project for the Subject “Data Structures”. The aim of this assignment was to implement functions in sparse arrays/matrices i.e.    matrices most of which are zero. The representation of sparse matrices will be done using linked lists. 

# What it does
The program consists of 2 parts and is designed for 5x5 sparse matrices. First of all, the given matrices are converted into linked lists ignoring the zero values. Then they are added together to form a new linked list which is printed in a proper matrix form (including zeros). Secondly, a matrix in linked list form is scanned for 2x2 matrices whose sum of elements is greater than a given integer c. If such 2x2 sub-matrices exist, they are printed on the console.

# Basic Structures
To understand the program there are two basic structures to get familiar with; the “cnode” and the “lnode” which have three parts each. The "cnode" contains the “data” part that  shows a row in which the matrix has at least one non-zero element, the “next” part that refers to the next non-zero row, and the “start” part that refers to the first non-zero element of the row. When a non-zero element of a row/line is found, the “lnode” gets used. The parts “column” and “data” display the column and the value of the element that was found, and the part “next” refers to the next non-zero element of the same row of the matrix.

# Project Parts
 MatrixFunctions.cpp : This file contains the 'main' function. Program execution begins and ends there.
 
 Linked-list.h: Header file which contains the class "LinkedList" and its functions declaration.
 
 Linked-list.cpp: File that contains the definition of the functions declared in the "Linked-List.h" file.

