#include "header.h"

void expressionTest() {
	string expression;
	cout << "Enter infix expression : ";
	getline(cin, expression);
	while (expression != "q") {
		if (checkInfix(expression)) {
			cout << "Correct expression!" << endl;
		}
		else {
			cout << "Wrong infix expression!" << endl;
		}
		cout << "Enter infix expression : ";
		getline(cin, expression);
	}
}

void operatorPush(operatorStack **head, char op) {
	operatorStack *node = (operatorStack*)malloc(sizeof(operatorStack));
	if (node == NULL) {
		return;
	}
	node->value = op;
	node->next = NULL;
	if (*head) {
		node->next = (*head);
	}
	(*head) = node;
}

char operatorPop(operatorStack **head) {
	if (*head) {
		char op = (*head)->value;
		operatorStack *temp = *head;
		(*head) = (*head)->next;
		free(temp);
		return op;
	}
	else {
		return '\0';
	}
}

bool bracketCheck(operatorStack **head, char op) {
	string leftBracket = "({[";
	string rightBracket = ")}]";
	int check = leftBracket.find(op);
	if (check >= 0) {
		operatorPush(head, op);
		return true;
	}
	check = rightBracket.find(op);
	if (check >= 0) {
		char top = operatorPop(head);
		if (top == NULL) {
			return false;
		}
		int index = leftBracket.find(top);
		if (index < 0 || index != check) {
			return false;
		}
		else {
			return true;
		}
	}
	return false;
}

bool checkInfix(string expression) {
	operatorStack *operatorHead = NULL;

	if (!expression.empty()) {
		int i, len = expression.size(), operatorFlag = 0, operandFlag = 0,
			leftBracketFlag = 0, rightBracketFlag = 0;
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
					return false;
				}
				operatorFlag = 1;
				operandFlag = 0;
				leftBracketFlag = 0;
				rightBracketFlag = 0;
				continue;
			}
			int operandCheck = operands.find(element);
			if (operandCheck >= 0) {
				if (operandFlag) {
					return false;
				}
				operatorFlag = 0;
				leftBracketFlag = 0;
				rightBracketFlag = 0;
				continue;
			}
			if (space == element) {
				if (!operatorFlag) {
					operandFlag = 1;
				}
				continue;
			}
			int leftBracketCheck = leftBrackets.find(element);
			if (leftBracketCheck >= 0) {
				if (rightBracketFlag) {
					return false;
				}
				operatorFlag = 0;
				leftBracketFlag = 1;
				if (bracketCheck(&operatorHead, element)) {
					continue;
				}
			}
			int rightBracketCheck = rightBrackets.find(element);
			if (rightBracketCheck >= 0) {
				if (leftBracketFlag) {
					return false;
				}
				operatorFlag = 0;
				rightBracketFlag = 1;
				if (bracketCheck(&operatorHead, element)) {
					continue;
				}
			}
			return false;
		}
		operatorStack *temp = operatorHead;
		int flag2 = 0;
		while (temp) {
			flag2 = 1;
			operatorHead = operatorHead->next;
			free(temp);
			temp = operatorHead;
		}
		if (operatorFlag) {
			return false;
		}
		if (flag2) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}