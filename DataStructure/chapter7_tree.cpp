#include "header.h"

void wordManager() {
	string command;
	_TreeNode *root = NULL;
	showCommandInTree();
	getline(cin, command);
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
			_TreeNode *node = searchTreeNode(&root, NULL, word);
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
		// cin >> command;
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


void showWords(_TreeNode *root) {
	if (root) {
		showWords(root->left);
		cout << "Word : " << *(root->word) << endl;
		cout << "Meaning : " << *(root->meaning) << endl << endl;
		showWords(root->right);
	}
}

void removeAllNodes(_TreeNode *root) {
	if (root) {
		removeAllNodes(root->left);
		removeAllNodes(root->right);
		free(root);
	}
}

_TreeNode* searchTreeNode(_TreeNode **root, _TreeNode **parent, string word) {
	_TreeNode *node = *root, *temp = NULL;
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

void createTreeNode(_TreeNode **root, string word, string meaning) {
	_TreeNode *node = NULL, *parent = NULL;
	node = searchTreeNode(root, &parent, word);
	if (node != NULL) {
		return;
	}
	
	node = (_TreeNode*)malloc(sizeof(_TreeNode));
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

void insertTreeNode(_TreeNode **root, string word, string meaning) {
	if (!word.empty() && !meaning.empty()) {
		_TreeNode *node = searchTreeNode(root, NULL, word);
		if (node == NULL) {
			createTreeNode(root, word, meaning);
		}
		else {
			cout << "The word already exists" << endl;
		}
	}
}

void removeTreeNode(_TreeNode **root, string word) {
	_TreeNode *node = NULL, *parent = NULL, *child = NULL, *pchild = NULL;
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

void deleteTreeNode(_TreeNode **root, string word) {
	if (!word.empty()) {
		_TreeNode *node = searchTreeNode(root, NULL, word);
		if (node == NULL) {
			cout << "The word doesn't exist" << endl;
		}
		else {
			removeTreeNode(root, word);
		}
	}
}