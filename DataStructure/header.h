#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

// chapter 2 - recursive
int sub_recursive(int num);
int sub_iterative(int num);
int power_recursive(int base, int expo);
void hanoi_tower(int num, char from, char temp, char to);

// chapter 4 - linked list
typedef struct ListNode {
	int value;
	struct ListNode *next;
} LinkedList;
void LinkedListTest();
void showCommand();
void insertNode(LinkedList **head, int value);
void deleteNode(LinkedList **head, int value);
void showList(LinkedList *head);
void reverseList(LinkedList **head);

// chapter 5, 6 - stack, queue
typedef struct _StackNode {
	int value;
	struct _StackNode *next;
} _Stack;
typedef struct _QueueNode {
	int value;
	int type;
	struct _QueueNode *left;
	struct _QueueNode *right;
} _Queue;
void expressionTest();
_Queue* convertInfixToPostfix(string expression);
void stackPush(_Stack **head, int value);
int stackPop(_Stack **head);
int stackPeek(_Stack **head, int index);
void freeStack(_Stack **head);
void enqueue(_Queue **head, int value, int type);
_Queue* dequeue(_Queue **head);
bool isEmptyQueue(_Queue **head);
void freeQueue(_Queue **head);
void inputNumber(_Queue **head, int num[], int top);
bool leftBracket(_Stack **stackHead, int value);
bool rightBracket(_Stack **stackHead, _Queue **queueHead, int value);
int calculatePostfix(_Queue **queueHead);

// chapter 7 - tree
typedef struct _TreeNode {
	string *word;
	string *meaning;
	_TreeNode *left;
	_TreeNode *right;
} _Tree;
void wordManager();
void showCommandInTree();
void showWords(_Tree *root);
void showWords(_Tree *root);
void removeAllNodes(_Tree *root);
_Tree* searchTreeNode(_Tree **root, _Tree **parent, string word);
void createTreeNode(_Tree **root, string word, string meaning);
void insertTreeNode(_Tree **root, string word, string meaning);
void removeTreeNode(_Tree **root, string word);
void deleteTreeNode(_Tree **root, string word);

//chapter 8 - heap
// array heap
#define ARRAY_HEAP_MAX_NUM 65
typedef struct _ArrayHeapNode {
	int heap_size;
	int values[ARRAY_HEAP_MAX_NUM];
} _ArrayHeap;
void maxHeapSimulation();
void showCommandInArrayHeap();
void showArrayHeap(_ArrayHeap **heap);
void insertArrayHeap(_ArrayHeap **heap, int value);
int deleteArrayHeap(_ArrayHeap **heap);