// MatrixFunctions.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "linked-list.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "Addition of 2 sparse matrices" << endl << "A = " << endl;

	int T1[5][5] = { {10,0,0,0,0},{0,0,20,0,0},{0,30,40,0,0},{0,0,0,0,0},{0,0,0,0,50} };

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << T1[i][j] << " ";
		}
		cout << endl;
	}

	cout << "B = " << endl;
	int T2[5][5] = { {20,0,0,30,0},{0,0,0,0,0},{0,10,0,0,0},{0,0,0,40,0},{0,0,0,0,50} };

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << T2[i][j] << " ";
		}
		cout << endl;
	}


	LinkedList A, B, C;

	A.ArrayToList(T1);
	B.ArrayToList(T2);

	cout << "A + B = " << endl;
	C.AddTwoLists(A, B);
	C.PrintListToArray();
	cout << endl;

	cout << "Find2x2SubTable list A: " << endl;
	cout << "c = 80" << endl;
	A.FindSubTable(80);
	cout << "c = 40" << endl;
	A.FindSubTable(40);
	cout << "c = 100" << endl;
	A.FindSubTable(100);
}


