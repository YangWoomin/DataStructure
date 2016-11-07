#include "header.h"

void wordManager() {
	string command;
	_Tree *root = NULL;
	showCommandInTree();
	getline(cin, command);
	while (command != "q") {
		if (command == "i") {
			string word, meaning;
			cout << "Enter a word : ";
			getline(cin, word);
			cout << "Enter meaning of the word : ";
			getline(cin, meaning);
			insertTreeNode(&root, word, meaning);
		}
		else if (command == "d") {
			string word;
			cout << "Enter the word : ";
			getline(cin, word);
			deleteTreeNode(&root, word);
		}
		else if (command == "s") {
			string word;
			cout << "Enter the word : ";
			getline(cin, word);
			_Tree *node = searchTreeNode(&root, NULL, word);
			if (node) {
				cout << "Word : " << *(node->word) << endl;
				cout << "Meaning : " << *(node->meaning) << endl;
			}
			else {
				cout << "The word doesn't exist" << endl;
			}
		}
		cout << endl;
		cout << "---------------------List of Words---------------------" << endl;
		showWords(root);
		cout << "----------------------End of List----------------------" << endl;
		showCommandInTree();
		getline(cin, command);
	}
	removeAllNodes(root);
	root = NULL;
}

void showCommandInTree() {
	cout << "*****************" << endl;
	cout << "* i : insert\t*" << endl;
	cout << "* d : delete\t*" << endl;
	cout << "* s : search\t*" << endl;
	cout << "* q : quit\t*" << endl;
	cout << "*****************" << endl;
}


void showWords(_Tree *root) {
	if (root) {
		showWords(root->left);
		cout << "Word : " << *(root->word) << endl;
		cout << "Meaning : " << *(root->meaning) << endl << endl;
		showWords(root->right);
	}
}

void removeAllNodes(_Tree *root) {
	if (root) {
		removeAllNodes(root->left);
		removeAllNodes(root->right);
		free(root);
	}
}

_Tree* searchTreeNode(_Tree **root, _Tree **parent, string word) {
	_Tree *node = *root, *temp = NULL;
	while (node) {
		temp = node;
		int check = word.compare(*(node->word));
		if (check < 0) {
			node = node->left;
		}
		else if (check > 0) {
			node = node->right;
		}
		else {
			return node;
		}
		if (parent) {
			*parent = temp;
		}
	}
	return NULL;
}

void createTreeNode(_Tree **root, string word, string meaning) {
	_Tree *node = NULL, *parent = NULL;
	node = searchTreeNode(root, &parent, word);
	if (node != NULL) {
		return;
	}
	
	node = (_Tree*)malloc(sizeof(_Tree));
	if (node == NULL) {
		return;
	}
	node->word = new string(word);
	node->meaning = new string(meaning);
	node->left = NULL;
	node->right = NULL;
	if (parent == NULL) {
		*root = node;
	}
	else {
		int check = word.compare(*(parent->word));
		if (check < 0) {
			parent->left = node;
		}
		else {
			parent->right = node;
		}
	}
}

void insertTreeNode(_Tree **root, string word, string meaning) {
	if (!word.empty() && !meaning.empty()) {
		_Tree *node = searchTreeNode(root, NULL, word);
		if (node == NULL) {
			createTreeNode(root, word, meaning);
		}
		else {
			cout << "The word already exists" << endl;
		}
	}
}

void removeTreeNode(_Tree **root, string word) {
	_Tree *node = NULL, *parent = NULL, *child = NULL, *pchild = NULL;
	node = searchTreeNode(root, &parent, word);
	if (node) {
		if (node->left && node->right) {
			child = node->left;
			while (child->right) {
				pchild = child;
				child = child->right;
			}
			free(node->word);
			free(node->meaning);
			node->word = new string(*(child->word));
			node->meaning = new string(*(child->meaning));
			free(child->word);
			free(child->meaning);
			if (pchild == NULL) {
				if (child->left) {
					node->left = child->left;
				}
				else {
					node->left = NULL;
				}
			}
			else {
				if (child->left) {
					pchild->right = child->left;
				}
				else {
					pchild->right = NULL;
				}
			}
			free(child);
		}
		else {
			if (node->left) {
				if (parent == NULL) {
					*root = node->left;
				}
				else if (parent->left == node) {
					parent->left = node->left;
				}
				else if (parent->right == node) {
					parent->right = node->left;
				}
			}
			else if (node->right) {
				if (parent == NULL) {
					*root = node->right;
				}
				else if (parent->left == node) {
					parent->left = node->right;
				}
				else if (parent->right == node) {
					parent->right = node->right;
				}
			}
			else {
				if (parent == NULL) {
					*root = NULL;
				}
				else if (parent->left == node) {
					parent->left = NULL;
				}
				else if (parent->right == node) {
					parent->right = NULL;
				}
			}
			free(node->word);
			free(node->meaning);
			free(node);
		}
	}
}

void deleteTreeNode(_Tree **root, string word) {
	if (!word.empty()) {
		_Tree *node = searchTreeNode(root, NULL, word);
		if (node == NULL) {
			cout << "The word doesn't exist" << endl;
		}
		else {
			removeTreeNode(root, word);
		}
	}
}