#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <Windows.h>
#include <math.h>

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
typedef struct _MyTree {
	string *word;
	string *meaning;
	_MyTree *left;
	_MyTree *right;
} _TreeNode;
void wordManager();
void showCommandInTree();
void showWords(_TreeNode *root);
void showWords(_TreeNode *root);
void removeAllNodes(_TreeNode *root);
_TreeNode* searchTreeNode(_TreeNode **root, _TreeNode **parent, string word);
void createTreeNode(_TreeNode **root, string word, string meaning);
void insertTreeNode(_TreeNode **root, string word, string meaning);
void removeTreeNode(_TreeNode **root, string word);
void deleteTreeNode(_TreeNode **root, string word);

// chapter 8 - heap
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
// Huffman code
#define MAX_CHARACTER_NUMBER 52 // the number of A~Z and a~z
#define MAX_HUFFMAN_HEAP_SIZE 65
typedef struct _Huffman {
	int value;
	int frequency;
	struct _Huffman *left;
	struct _Huffman *right;
} _HuffmanNode;
typedef struct _HuffmanMinHeapNode {
	int heap_size;
	_HuffmanNode* huffman[MAX_HUFFMAN_HEAP_SIZE];
} _HuffmanHeap;
typedef struct _MyHuffmanCode {
	unsigned long long code;
	int size;
} _HuffmanCode;
void huffmanTest();
void showCommandInHuffmanTest();
_HuffmanNode* makeTree(_HuffmanNode *left, _HuffmanNode *right);
void insertHuffmanNodeInMinHeap(_HuffmanHeap *heap, _HuffmanNode *node);
_HuffmanNode* deleteHuffmanNodeInMinHeap(_HuffmanHeap *heap);
void createHuffmanCode(_HuffmanNode *root, map<int, _HuffmanCode>* m, long long pCode, int size);
void deleteHuffmanNodes(_HuffmanNode *root);
int createHuffmanNodes(map<int, _HuffmanCode>* m);
void showHuffmanCode(map<int, _HuffmanCode> *m);
void encodeWord(map<int, _HuffmanCode> *m);
void decodeCode(map<int, _HuffmanCode> *m);

// chapter 9 - sorting : selection, insertion, bubble, shell, merge, quick, heap, radix
class Sorting {
private:
	const static int MAX_SIZE = 100000000;
	static int size;
	static map<string, int> Status;
	static CRITICAL_SECTION cs;
	static int count;
protected:
	int* arr;
	static int* _array;
	const static int unit[9];
public:
	void setSize(int size);
	int getSize();
	static void setArray();
	int* copyArray();
	static void showArray(int* arr, int size);
	static void showArray(vector<int>& v);
	static void initialize();
	static void reset();
	static void finish();
	static void showSortingStatus(string name, int status);
	void increaseCount();
	void decreaseCount();
	static int getCount();
	void updateStatus(string name, int status);
	static void showSortingProcess();
	virtual void sorting() = 0;
};

class SelectionSorting : public Sorting {
public:
	void sorting();
};

class InsertionSorting : public Sorting {
public:
	void sorting();
};

class BubbleSorting : public Sorting {
public:
	void sorting();
};

class ShellSorting : public Sorting {
public:
	void sorting();
};

class MergeSorting : public Sorting {
private:
	int* sorted;
public:
	void sorting();
	void merge(int* arr, int left, int right);
};

class QuickSorting : public Sorting {
public:
	void sorting();
	void quick(int* arr, int left, int right);
};

class HeapSorting : public Sorting {
public:
	void sorting();
};

class RadixSorting : public Sorting {
public:
	void sorting();
};

void sortingSimulation();
void showCommandInSorting();
void sortingManager(string command);