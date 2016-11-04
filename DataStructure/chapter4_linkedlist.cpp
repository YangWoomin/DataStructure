#include "header.h"

void LinkedListTest() {
	LinkedList *head = NULL;
	char command;
	showCommand();
	cin >> command;
	while (command != 'q') {
		int num;
		if (command == 'i') {
			cin >> num;
			insertNode(&head, num);
			showList(head);
		}
		else if (command == 'd') {
			cin >> num;
			deleteNode(&head, num);
			showList(head);
		}
		else if (command == 's') {
			showList(head);
		}
		else if (command == 'r') {
			reverseList(&head);
			showList(head);
		}
		else {
			cout << "Unknown command" << endl;
		}
		showCommand();
		cin >> command;
	}
	LinkedList *temp = head;
	while (temp) {
		head = head->next;
		free(temp);
		temp = head;
	}
}

void showCommand() {
	cout << "*****************" << endl;
	cout << "* i : insert\t*" << endl;
	cout << "* d : delete\t*" << endl;
	cout << "* s : show\t*" << endl;
	cout << "* r : reverse\t*" << endl;
	cout << "*****************" << endl;
}

void insertNode(LinkedList **head, int value) {
	LinkedList *temp = *head;
	LinkedList *node = (LinkedList*)malloc(sizeof(LinkedList));
	if (node == NULL) {
		printf("Memory allocation failed\n");
		return;
	}
	node->value = value;
	node->next = NULL;

	if (temp) {
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = node;
	}
	else {
		*head = node;
	}
}

void deleteNode(LinkedList **head, int value) {
	LinkedList *temp = *head;
	if (temp) {
		if (temp->value == value) {
			if (temp->next) {
				*head = temp->next;
			}
			else {
				*head = NULL;
				free(temp);
				return;
			}
			free(temp);
			temp = *head;
		}
		LinkedList *temp2 = temp;
		temp = temp->next;
		while (temp != NULL) {
			if (temp->value == value) {
				if (temp->next) {
					temp2->next = temp->next;
				}
				else {
					temp2->next = NULL;
					free(temp);
					return;
				}
				free(temp);
				temp = temp2;
			}
			temp2 = temp;
			temp = temp->next;
		}
	}
}

void showList(LinkedList *head) {
	LinkedList *temp = head;
	while (temp) {
		cout << temp->value << " ";
		temp = temp->next;
	}
	cout << endl;
}

void reverseList(LinkedList **head) {
	LinkedList *p, *q, *r;
	p = *head;
	q = NULL;
	while (p) {
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}
	*head = q;
}