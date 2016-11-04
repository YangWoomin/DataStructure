#pragma once
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

// chapter 2
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

// chapter 5 - stack
typedef struct StackNode {
	char value;
	struct StackNode *next;
} operatorStack;
typedef struct QueueNode {
	int value;
	struct QueueNode *next;
} operandQueue;
void expressionTest();
bool checkInfix(string expression);
void operatorPush(operatorStack **head, char op);
char operatorPop(operatorStack **head);
bool bracketCheck(operatorStack **head, char op);
bool checkInfix(string expression);