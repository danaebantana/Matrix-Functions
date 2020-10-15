#include "linked-list.h"
#include <iostream>

using namespace std;

//Constructor of class.
LinkedList::LinkedList() {
	head = NULL;
}

//Build cnode.
LinkedList::cnode* LinkedList::Create_cnode(int key)
{
	cnode* cn = new cnode;
	cn->data = key;
	cn->next = NULL;
	cn->start = NULL;

	return cn;
}

//Build lnode.
LinkedList::lnode* LinkedList::Create_lnode(int column, int key)
{
	lnode* ln = new lnode;
	ln->data = key;
	ln->column = column;
	ln->next = NULL;

	return ln;
}

//1st part
//Adding function of cnode. These nodes represent a non-zero row of a matrix.
void LinkedList::Add_cnode(cnode* ptr, int key)
{
	if (head == NULL) {
		head = Create_cnode(key);
	}
	else if (ptr->next == NULL) {
		ptr->next = Create_cnode(key);
	}
	else if (ptr->next != NULL) {
		Add_cnode(ptr->next, key);
	}

}

//Adding function of lnode. It adds the first node of each line and if there already is one, then it calls Add_lnode2.
void LinkedList::Add_lnode1(cnode* ptr, int column, int key)
{
	if (head == NULL) {
		cout << "Array is Empty!" << endl;
	}
	else if (ptr->start == NULL) {
		ptr->start = Create_lnode(column, key);
	}
	else if (ptr->start != NULL) {
		Add_lnode2(ptr->start, column, key);
	}
}

//Adding function of lnode. If end of line not found then it recursively calls itself.
void LinkedList::Add_lnode2(lnode* ptr, int column, int key)
{
	if (ptr->next == NULL) {
		ptr->next = Create_lnode(column, key);
	}
	else {
		Add_lnode2(ptr->next, column, key);
	}
}

//Search for a cnode node based on a key/value. It is called recursively until the node with data equal to the key is found and the pointer pointing to this node is returned.
LinkedList::cnode* LinkedList::Search(cnode* ptr, int key)
{
	cnode* tmp = ptr;
	if (tmp->data != key) {
		Search(tmp->next, key);
	}
	else {
		return tmp;
	}
}

//Returns the head node.
LinkedList::cnode* LinkedList::GetHeadPointer()
{
	return head;
}

//Taking as an argument a sparse 5x5 array with integer elements it turns it into a linked list of only non-zero array elements.
void LinkedList::ArrayToList(int Array[5][5])
{
	for (int i = 0; i < 5; i++) {
		bool flag = false;
		for (int j = 0; j < 5; j++) {
			if (Array[i][j] != 0) flag = true;
		}
		if (flag) {
			Add_cnode(head, i + 1);  //nodes that show that a row of a matrix has at least one element.
			cnode* tmp = Search(head, i + 1);
			for (int j = 0; j < 5; j++) {
				if (Array[i][j] != 0) {
					Add_lnode1(tmp, j + 1, Array[i][j]);
				}
			}
		}
	}
};

//Print linked list as an array/matrix. It checks if a line exists or if it is a zero line. 
//If it exists then PrintLine function is called for each line. Otherwise it means that the row only contains zero elements and the respective line is printed.
void LinkedList::PrintListToArray()
{
	cnode* h = this->head;
	for (int i = 1; i < 6; i++) {
		if (h->data == i) {
			PrintLine(h->start);
			h = h->next;
			cout << endl;
		}
		else {
			cout << "0 0 0 0 0" << endl;
		}
	}
}

//Prints the elements of each row. For each column it checks if a node exists or not and the respective action is made.
void LinkedList::PrintLine(lnode* ptr)
{
	for (int i = 1; i < 6; i++) {
		if (ptr != NULL) {
			if (ptr->column == i) {
				cout << ptr->data << " ";
				ptr = ptr->next;
			}
			else {
				cout << "0 ";
			}
		}
		else {
			cout << "0 ";
		}
	}
}

//Add the two linked lists.
void LinkedList::AddTwoLists(LinkedList A, LinkedList B)
{
	cnode* head1 = A.GetHeadPointer();
	cnode* head2 = B.GetHeadPointer();
	//initialize new List C.
	cnode* tmp = head;
	this->head = AddTwoListsPrivate1(head1, head2, tmp);
}

//Function that adds a cnode node and calls AddTwoListsPrivate2 and AddTwoListsPrivate3 to add lnode nodes and complete the new list.
LinkedList::cnode* LinkedList::AddTwoListsPrivate1(cnode* ptrA, cnode* ptrB, cnode* ptrC)
{
	if (head == NULL) {  //the list is empty.
		if (ptrA != NULL && ptrB != NULL) {
			if (ptrA->data == ptrB->data) { //check if matrices have elements in the same line.
				Add_cnode(head, ptrA->data);
				AddTwoListsPrivate2(ptrA->start, ptrB->start, head);
				AddTwoListsPrivate1(ptrA->next, ptrB->next, head);
			}
			else if (ptrA->data < ptrB->data) {
				Add_cnode(head, ptrA->data);
				AddTwoListsPrivate3(ptrA->start, head);
				AddTwoListsPrivate1(ptrA->next, ptrB, head);
			}
			else if (ptrA->data > ptrB->data) {
				Add_cnode(head, ptrB->data);
				AddTwoListsPrivate3(ptrB->start, head);
				AddTwoListsPrivate1(ptrA, ptrB->next, head);
			}
		}
	}
	//There already is a first node.
	else {
		if (ptrA != NULL && ptrB != NULL) {
			if (ptrA->data == ptrB->data) {
				Add_cnode(ptrC, ptrA->data);
				ptrC = Search(head, ptrA->data);
				AddTwoListsPrivate2(ptrA->start, ptrB->start, ptrC);
				AddTwoListsPrivate1(ptrA->next, ptrB->next, ptrC);
			}
			else if (ptrA->data < ptrB->data) {
				Add_cnode(ptrC, ptrA->data);
				ptrC = Search(head, ptrA->data);
				AddTwoListsPrivate3(ptrA->start, ptrC);
				AddTwoListsPrivate1(ptrA->next, ptrB, ptrC);
			}
			else if (ptrA->data > ptrB->data) {
				Add_cnode(ptrC, ptrB->data);
				ptrC = Search(head, ptrB->data);
				AddTwoListsPrivate3(ptrB->start, ptrC);
				AddTwoListsPrivate1(ptrA, ptrB->next, ptrC);
			}
		}
		else if (ptrA != NULL && ptrB == NULL) {
			while (ptrA != NULL) {
				ptrC = Create_cnode(ptrA->data);
				ptrA = ptrA->next;
			}
		}
		else if (ptrA == NULL && ptrB != NULL) {
			while (ptrB != NULL) {
				ptrC = Create_cnode(ptrB->data);
				ptrB = ptrB->next;
			}
		}
	}

	return head;
}

void LinkedList::AddTwoListsPrivate2(lnode* ptrA, lnode* ptrB, cnode* ptrC)
{
	if (ptrA != NULL && ptrB != NULL) {
		if (ptrA->column == ptrB->column) { //There are elements in the same column of the two matrices.
			Add_lnode1(ptrC, ptrA->column, ptrA->data + ptrB->data);
			AddTwoListsPrivate2(ptrA->next, ptrB->next, ptrC);
		}
		else if (ptrA->column < ptrB->column) { //If the column of the node in matrix A is smaller than the column of the node in matrix B then the element of A is added.
			Add_lnode1(ptrC, ptrA->column, ptrA->data);
			AddTwoListsPrivate2(ptrA->next, ptrB, ptrC);
		}
		else if (ptrA->column > ptrB->column) { //If the column of the node in matrix B is smaller than the column of the node in matrix A then the element of B is added.
			Add_lnode1(ptrC, ptrB->column, ptrB->data);
			AddTwoListsPrivate2(ptrA, ptrB->next, ptrC);
		}
	}
	//If one of the two matrices don't have an element left or are empty then the element that exists is added to matrix C.
	else if (ptrA != NULL && ptrB == NULL) {
		while (ptrA != NULL) {
			Add_lnode1(ptrC, ptrA->column, ptrA->data);
			ptrA = ptrA->next;
		}
	}
	else if (ptrA == NULL && ptrB != NULL) {
		while (ptrB != NULL) {
			Add_lnode1(ptrC, ptrB->column, ptrB->data);
			ptrB = ptrB->next;
		}
	}
}

//Function that copies a line from one list to an other one.
void LinkedList::AddTwoListsPrivate3(lnode* ptr, cnode* ptrC)
{
	while (ptr != NULL) {
		Add_lnode1(ptrC, ptr->column, ptr->data);
		ptr = ptr->next;
	}
}

//2nd part
//Function that finds a 2x2 sub-matrix with the sum of elements greater than c.
void LinkedList::FindSubTable(int c)
{
	FindSubTablePrivate(c, head);
}

//Because we are looking for 2x2 submatrices we want to scan one line and the next of it. 
void LinkedList::FindSubTablePrivate(int c, cnode* ptr)
{
	if (ptr->next != NULL) {
		if (ptr->next->data - ptr->data == 1) { //means that there is a next consecutive line.
			FindSubTableBetweenTwoLines(c, ptr->start, ptr->next->start);
			FindSubTablePrivate(c, ptr->next);
		}
		//a line is missing.
		else {
			FindSubTableBetweenTwoLines(c, ptr->start, NULL);
			FindSubTableBetweenTwoLines(c, NULL, ptr->next->start);
			FindSubTablePrivate(c, ptr->next);
		}
	}
}

//finds and prints the 2x2 submatures in the list that the sum is greater than c.
void LinkedList::FindSubTableBetweenTwoLines(int c, lnode* ptr1, lnode* ptr2)
{
	int sum = 0;
	if (ptr1 != NULL && ptr2 != NULL) { //When both lines exist we add the all four elements, two from the top line and two from the bottom line. 
		//Checking each column combination,finding the sum and printing the 2x2 matrix.
		if (ptr1->column == ptr2->column) {
			sum = ptr1->data + ptr2->data;
			if (ptr1->next != NULL) {
				if (ptr1->next->column - ptr1->column == 1) {
					sum += ptr1->next->data;
				}
			}
			if (ptr2->next != NULL) {
				if (ptr2->next->column - ptr2->column == 1) {
					sum += ptr2->next->data;
				}
			}
			//After I have calculated the sum, I check to see if I will print the sub-matrix.
			if (sum > c) {
				//Checking each combination for the 2x2 sub-matrix
				//first line.
				if (ptr1->next != NULL) {
					if (ptr1->next->column - ptr1->column == 1) {  //neighbouring elements
						cout << ptr1->data << " " << ptr1->next->data << endl;
					}
					else { //no neighbouring element
						cout << ptr1->data << " 0" << endl;
					}
				}
				else {  //checking if the element is in the last column or not.
					if (ptr1->column < 5) {
						cout << ptr1->data << " 0" << endl;
					}
					else {
						cout << "0 " << ptr1->data << endl;
					}
				}
				//second line.
				if (ptr2->next != NULL) {
					if (ptr2->next->column - ptr2->column == 1) {
						cout << ptr2->data << " " << ptr2->next->data << endl;
					}
					else {
						cout << ptr2->data << " 0" << endl;
					}
				}
				else {
					if (ptr2->column < 5) {
						cout << ptr2->data << " 0" << endl;
					}
					else {
						cout << "0 " << ptr2->data << endl;
					}
				}
				cout << endl;
				FindSubTableBetweenTwoLines(c, ptr1->next, ptr2->next);
			}
			else {
				FindSubTableBetweenTwoLines(c, ptr1->next, ptr2->next);
			}
		}
		else if (ptr1->column < ptr2->column) {
			sum = ptr1->data;
			if (ptr1->next != NULL) {
				if (ptr1->next->column - ptr1->column == 1) {
					sum += ptr1->next->data;
				}
			}
			if (ptr2->column - ptr1->column == 1) {
				sum += ptr2->data;
			}
			//Checking each combination for the 2x2 sub-matrix
			if (sum > c) {
				if (ptr1->next != NULL) {
					if (ptr1->next->column - ptr1->column == 1) {
						cout << ptr1->data << " " << ptr1->next->data << endl;
					}
					else {
						cout << ptr1->data << " 0" << endl;
					}
				}
				else {
					if (ptr1->column < 5) {
						cout << ptr1->data << " 0" << endl;
					}
					else {
						cout << "0 " << ptr1->data << endl;
					}
				}
				if (ptr2->column - ptr1->column == 1) {
					cout << "0 " << ptr2->data << endl;
				}
				else {
					cout << "0 0" << endl;
				}
				cout << endl;
				FindSubTableBetweenTwoLines(c, ptr1->next, ptr2);
			}
			else {
				FindSubTableBetweenTwoLines(c, ptr1->next, ptr2);
			}
		}
		else if (ptr1->column > ptr2->column) {
			sum = ptr1->data;
			if (ptr1->column - ptr2->column == 1) {
				sum += ptr2->data;
			}
			if (ptr2->next != NULL) {
				if (ptr2->next->column - ptr2->column == 1) {
					sum += ptr2->next->data;
				}
			}
			//Checking each combination for the 2x2 sub-matrix
			if (sum > c) {
				cout << "0 " << ptr1->data << endl;
				if (ptr2->next != NULL) {
					if (ptr2->next->column - ptr2->column == 1) {
						cout << ptr2->data << " " << ptr2->next->data << endl;
					}
					else {
						cout << ptr2->data << " 0" << endl;
					}
				}
				else {
					if (ptr2->column < 5) {
						cout << ptr2->data << " 0" << endl;
					}
					else {
						cout << "0 " << ptr2->data << endl;
					}
				}
				cout << endl;
				FindSubTableBetweenTwoLines(c, ptr1, ptr2->next);
			}
			else {
				FindSubTableBetweenTwoLines(c, ptr1, ptr2->next);
			}
		}
	}
	//If one of the two pointers is null that means that one line is full of zeros. 
	//In that case we only have to add the values of the elements on the non-zero line.
	else if (ptr1 == NULL && ptr2 != NULL) {
		//Finding the sum and printing the 2x2 matrix.
		sum = ptr2->data;
		if (ptr2->next != NULL) {
			if (ptr2->next->column - ptr2->column == 1) {
				sum += ptr2->next->data;
			}
		}
		//Checking each combination for the 2x2 sub-matrix
		if (sum > c) {
			cout << "0 0" << endl;  //Because ptr1==NULL it means the top line of the sub-matrix has only zeros. 
			if (ptr2->next != NULL) {
				if (ptr2->next->column - ptr2->column == 1) {  //check if elements are neighbouring ones.
					cout << ptr2->data << " " << ptr2->next->data << endl;
				}
				else { //the element does not have a right neighbour element. So a zero is placed.
					cout << ptr2->data << " 0" << endl;
				}
			}
			else {
				if (ptr2->column < 5) {
					cout << ptr2->data << " 0" << endl;
				}
				else {
					cout << "0 " << ptr2->data << endl;
				}
			}
			cout << endl;
			FindSubTableBetweenTwoLines(c, ptr1, ptr2->next);
		}
		else {
			FindSubTableBetweenTwoLines(c, ptr1, ptr2->next);
		}
	}
	else if (ptr1 != NULL && ptr2 == NULL) {
		//Finding the sum and printing the 2x2 matrix.
		sum = ptr1->data;
		if (ptr1->next != NULL) {
			if (ptr1->next->column - ptr1->column == 1) {
				sum += ptr1->next->data;
			}
		}
		//Checking each combination for the 2x2 sub-matrix
		if (sum > c) {
			if (ptr1->next != NULL) {
				if (ptr1->next->column - ptr1->column == 1) {   //neighbouring elements.
					cout << ptr1->data << " " << ptr1->next->data << endl;
				}
				else {
					cout << ptr1->data << " 0" << endl;
				}
			}
			else {
				if (ptr1->column < 5) {
					cout << ptr1->data << " 0" << endl;
				}
				else {
					cout << "0 " << ptr1->data << endl;
				}
			}
			cout << "0 0" << endl; //Because ptr2==NULL it means the bottom line of the sub-matrix has only zeros.
			cout << endl;
			FindSubTableBetweenTwoLines(c, ptr1->next, ptr2);
		}
		else {
			FindSubTableBetweenTwoLines(c, ptr1->next, ptr2);
		}
	}
}