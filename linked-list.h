#pragma once
#include <iostream>
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

class LinkedList {
private:
	//2 structures.
	struct lnode  //line node. Node that refers to a non-zero element of a line of a matrix.
	{
		int column;
		int data;
		lnode* next;
	};

	struct cnode   //column node. Node that refers to a non-zero row of a matrix.
	{
		int data;
		cnode* next;
		lnode* start;
	};
	cnode* head;  //Pointer that refers to the start of a list.
	cnode* Create_cnode(int key);
	lnode* Create_lnode(int column, int key);
	cnode* Search(cnode* ptr, int key);
	cnode* GetHeadPointer();
	void Add_cnode(cnode* ptr, int key);
	void Add_lnode1(cnode* ptr, int column, int key);
	void Add_lnode2(lnode* ptr, int column, int key);
	void PrintLine(lnode* ptr);
	cnode* AddTwoListsPrivate1(cnode* ptrA, cnode* ptrB, cnode* ptrC);
	void AddTwoListsPrivate2(lnode* ptrA, lnode* ptrB, cnode* ptrC);
	void AddTwoListsPrivate3(lnode* ptr, cnode* ptrC);
	void FindSubTablePrivate(int c, cnode* ptr);
	void FindSubTableBetweenTwoLines(int c, lnode* ptr1, lnode* ptr2);

public:
	LinkedList();
	void ArrayToList(int Array[5][5]);
	void AddTwoLists(LinkedList A, LinkedList B);
	void PrintListToArray();
	void FindSubTable(int c);
};
#endif