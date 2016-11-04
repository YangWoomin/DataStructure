#include "header.h"

void expressionTest() {
	string expression;
	_Queue *head = NULL, *node = NULL;
	cout << "Enter infix expression : ";
	getline(cin, expression);
	while (expression != "q") {
		if ((head = convertInfixToPostfix(expression)) != NULL) {
			cout << "Correct expression!" << endl;
			while ((node = dequeue(&head)) != NULL) {
				if (node->type == 0) {
					cout << node->value << " ";
				}
				else {
					printf("%c ", node->value);
				}
				node->left = NULL;
				node->right = NULL;
				free(node);
			}
			cout << endl;
		}
		else {
			cout << "Wrong infix expression!" << endl;
		}
		cout << "Enter infix expression : ";
		getline(cin, expression);
	}
}

void stackPush(_Stack **head, int value) {
	_Stack *node = (_Stack*)malloc(sizeof(_Stack));
	if (node == NULL) {
		return;
	}
	node->value = value;
	node->next = NULL;
	if (*head) {
		node->next = (*head);
	}
	(*head) = node;
}

int stackPop(_Stack **head) {
	if (*head) {
		int value = (*head)->value;
		_Stack *temp = *head;
		(*head) = (*head)->next;
		temp->next = NULL;
		free(temp);
		return value;
	}
	return 0;
}

int stackPeek(_Stack **head, int index) {
	int ret = -1, i = 0;
	_Stack *temp = *head;
	while (temp && i < index) {
		i++;
		temp = temp->next;
	}
	if (temp) {
		ret = temp->value;
	}
	return ret;
}

void freeStack(_Stack **head) {
	int element = -1;
	while ((element = stackPop(head)) != 0);
}

void enqueue(_Queue **head, int value, int type) {
	_Queue *node = (_Queue*)malloc(sizeof(_Queue));
	if (node == NULL) {
		return;
	}
	node->value = value;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	
	if (*head) {
		if ((*head)->left) {
			node->left = (*head)->left;
			node->right = (*head);
			(*head)->left->right = node;
			(*head)->left = node;
		}
		else {
			(*head)->left = node;
			(*head)->right = node;
			node->left = (*head);
			node->right = (*head);
		}
	}
	else {
		(*head) = node;
	}
}

_Queue* dequeue(_Queue **head) {
	if (*head) {
		_Queue *temp = (*head);
		if ((*head)->right) {
			*head = (*head)->right;
			if ((*head)->right == temp) {
				(*head)->right = NULL;
				(*head)->left = NULL;
			}
			else {
				(*head)->left = temp->left;
				temp->left->right = (*head);
			}
		}
		else {
			*head = NULL;
		}
		return temp;
	}
	return NULL;
}

void freeQueue(_Queue **head) {
	_Queue *temp = NULL;
	while ((temp = dequeue(head)) != NULL) {
		temp->left = NULL;
		temp->right = NULL;
		free(temp);
	}
}

bool leftBracket(_Stack **stackHead, int value) {
	string leftBracket = "({[";
	int index = leftBracket.find(value);
	if (index >= 0) {
		if (stackPeek(stackHead, 0) == -1) {
			stackPush(stackHead, value);
			return true;
		}
		int i = 0, bracket, check = -1;
		while ((bracket = stackPeek(stackHead, i++)) != -1) {
			check = leftBracket.find(bracket);
			if (check >= 0) {
				if (check < index) {
					return false;
				}
				else {
					stackPush(stackHead, value);
					return true;
				}
			}
		}
	}
	return false;
}

bool rightBracket(_Stack **stackHead, _Queue **queueHead, int value) {
	string leftBracket = "({[";
	string rightBracket = ")}]";
	string operators = "/*%+-";
	int index = rightBracket.find(value);
	if (index >= 0) {
		int element, check = -1;
		while ((element = stackPop(stackHead)) != 0) {
			check = operators.find(element);
			if (check >= 0) {
				enqueue(queueHead, element, 1);
				continue;
			}
			check = leftBracket.find(element);
			if (check >= 0) {
				if (index == check) {
					return true;
				}
				else {
					return false;
				}
			}
			return false;
		}
	}
	return false;
}

void inputNumber(_Queue **head, int num[], int top) {
	int sum = 0, j;
	if (head) {
		for (j = 0; j < top; j++) {
			sum += num[j] * (power_recursive(10, top - (j + 1)));
		}
		enqueue(head, sum, 0);
	}
}

_Queue* convertInfixToPostfix(string expression) {
	_Stack *stackHead = NULL;
	_Queue *queueHead = NULL;
	int num[100] = { 0, }, top = 0;

	if (!expression.empty()) {
		int i, len = expression.size(), operatorFlag = 0, operandFlag = 0,
			leftBracketFlag = 0, rightBracketFlag = 0, operandFlag2 = 0;
		string operators = "+-/*%";
		string leftBrackets = "({[";
		string rightBrackets = ")}]";
		string operands = "0123456789";
		char space = ' ';
		for (i = 0; i < len; i++) {
			char element = expression[i];

			int operatorCheck = operators.find(element);
			if (operatorCheck >= 0) {
				if (operatorFlag) {
					freeStack(&stackHead);
					freeQueue(&queueHead);
					return NULL;
				}
				operatorFlag = 1;
				operandFlag = 0;
				leftBracketFlag = 0;
				rightBracketFlag = 0;

				if (operandFlag2) {
					operandFlag2 = 0;
					inputNumber(&queueHead, num, top);
				}
				
				if (stackPeek(&stackHead, 0) == -1) {
					stackPush(&stackHead, element);
				}
				else {
					int element2 = -1, j = 0;
					while ((element2 = stackPeek(&stackHead, j++)) != -1) {
						int check = operators.find(element2);
						if (check >= 0) {
							if (operatorCheck < check) {
								enqueue(&queueHead, stackPop(&stackHead), 1);
							}
						}
						stackPush(&stackHead, element);
						break;
					}
				}
				continue;
			}

			int operandCheck = operands.find(element);
			if (operandCheck >= 0) {
				if (operandFlag) {
					freeStack(&stackHead);
					freeQueue(&queueHead);
					return NULL;
				}
				if (!operandFlag2) {
					operandFlag2 = 1;
					memset(num, 0, sizeof(num));
					top = 0;
					operatorFlag = 0;
					leftBracketFlag = 0;
					rightBracketFlag = 0;
				}
				num[top++] = element - 48;
				continue;
			}

			if (space == element) {
				if (operandFlag2) {
					operandFlag = 1;
					operandFlag2 = 0;
					inputNumber(&queueHead, num, top);
				}
				continue;
			}

			int leftBracketCheck = leftBrackets.find(element);
			if (leftBracketCheck >= 0) {
				if (rightBracketFlag) {
					freeStack(&stackHead);
					freeQueue(&queueHead);
					return NULL;
				}
				if (operandFlag2) {
					operandFlag2 = 0;
					inputNumber(&queueHead, num, top);
				}
				operatorFlag = 0;
				leftBracketFlag = 1;
				if (leftBracket(&stackHead, element)) {
					continue;
				}
			}

			int rightBracketCheck = rightBrackets.find(element);
			if (rightBracketCheck >= 0) {
				if (leftBracketFlag) {
					freeStack(&stackHead);
					freeQueue(&queueHead);
					return NULL;
				}
				if (operandFlag2) {
					operandFlag2 = 0;
					inputNumber(&queueHead, num, top);
				}
				operatorFlag = 0;
				rightBracketFlag = 1;
				if (rightBracket(&stackHead, &queueHead, element)) {
					continue;
				}
			}
			freeStack(&stackHead);
			freeQueue(&queueHead);
			return NULL;
		}
		if (operatorFlag) {
			freeStack(&stackHead);
			freeQueue(&queueHead);
			return NULL;
		}
		if (operandFlag2) {
			operandFlag2 = 0;
			inputNumber(&queueHead, num, top);
		}
		int lastElement = 0;
		while ((lastElement = stackPop(&stackHead)) != 0) {
			enqueue(&queueHead, lastElement, 1);
		}
		return queueHead;
	}
	else {
		return NULL;
	}
}