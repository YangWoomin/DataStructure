#include "header.h"

/* max heap simulation
*/
void maxHeapSimulation() {
	_ArrayHeap *heap = NULL;
	heap = (_ArrayHeap*)malloc(sizeof(_ArrayHeap));
	if (heap == NULL) {
		return;
	}
	heap->heap_size = 0;
	memset(heap->values, 0, sizeof(heap->values));

	string command;
	showCommandInArrayHeap();
	getline(cin, command); getline(cin, command);
	while (command != "q") {
		if (command == "i") {
			if (heap->heap_size < ARRAY_HEAP_MAX_NUM) {
				string value;
				cout << "Enter a number : ";
				getline(cin, value);
				insertArrayHeap(&heap, atoi(value.c_str()));
			}
			else {
				cout << "The heap is full" << endl;
			}
		}
		else if (command == "d") {
			int value = deleteArrayHeap(&heap);
			if (value) {
				cout << value << " is deleted" << endl;
			}
			else {
				cout << "The heap is empty" << endl;
			}
		}
		else if (command == "q") {
			break;
		}
		showArrayHeap(&heap);
		showCommandInArrayHeap();
		getline(cin, command);
	}
	free(heap);
}

void showCommandInArrayHeap() {
	cout << "*****************" << endl;
	cout << "* i : insert\t*" << endl;
	cout << "* d : delete\t*" << endl;
	cout << "* q : quit\t*" << endl;
	cout << "*****************" << endl;
}

void showArrayHeap(_ArrayHeap **heap) {
	if (*heap) {
		for (int i = 1; i <= (*heap)->heap_size; i++) {
			cout << (*heap)->values[i] << " ";
		}
		cout << endl;
	}
}

void insertArrayHeap(_ArrayHeap **heap, int value) {
	if (*heap) {
		int i = ++((*heap)->heap_size);
		while (i != 1 && value > (*heap)->values[i / 2]) {
			(*heap)->values[i] = (*heap)->values[i / 2];
			i /= 2;
		}
		(*heap)->values[i] = value;
	}
}

int deleteArrayHeap(_ArrayHeap **heap) {
	int ret = 0;
	if (*heap) {
		if ((*heap)->heap_size > 1) {
			ret = (*heap)->values[1];
			int temp = (*heap)->values[((*heap)->heap_size)--];
			int i = 1;
			while (i <= (*heap)->heap_size) {
				if (i < (*heap)->heap_size && (*heap)->values[i] < (*heap)->values[i + 1]) {
					i++;
				}
				if (temp < (*heap)->values[i]) {
					(*heap)->values[i / 2] = (*heap)->values[i];
					i *= 2;
				}
				else {
					break;
				}
			}
			(*heap)->values[i / 2] = temp;
		}
		else if ((*heap)->heap_size == 1) {
			return (*heap)->values[((*heap)->heap_size)--];
		}
	}
	return ret;
}

/* Huffman code
*/
void huffmanSimulation() {
	map<int, _HuffmanCode> *m = new map<int, _HuffmanCode>();
	if (m == NULL) {
		return;
	}
	string command;
	showCommandInHuffmanTest();
	getline(cin, command); getline(cin, command);
	while (command != "q") {
		if (command == "n") {
			int result = createHuffmanNodes(m);
			if (result == 0) {
				
			}
			else if (result == -1) {
				cout << "Invalid sentence" << endl;
			}
			else if (result == -2) {
				cout << "Memory allocation failed" << endl;
			}
		}
		else if (command == "s") {
			showHuffmanCode(m);
		}
		else if (command == "e") {
			encodeWord(m);
		}
		else if (command == "d") {
			decodeCode(m);
		}
		else {
			cout << "Invalid command" << endl;
		}
		showCommandInHuffmanTest();
		getline(cin, command);
	}
	free(m);
}

void showCommandInHuffmanTest() {
	cout << "*************************" << endl;
	cout << "* n : new setence\t*" << endl;
	cout << "* s : show huffman code\t*" << endl;
	cout << "* e : encode a word\t*" << endl;
	cout << "* d : decode a code\t*" << endl;
	cout << "* q : quit\t\t*" << endl;
	cout << "*************************" << endl;
}

_HuffmanNode* makeTree(_HuffmanNode *left, _HuffmanNode *right) {
	_HuffmanNode *node = (_HuffmanNode*)malloc(sizeof(_HuffmanNode));
	if (node != NULL) {
		_HuffmanNode *leftTemp = left;
		while (leftTemp && leftTemp->right) {
			leftTemp = leftTemp->right;
		}
		_HuffmanNode *rightTemp = right;
		while (rightTemp && rightTemp->right) {
			rightTemp = rightTemp->right;
		}
		if (leftTemp && rightTemp) {
			if (rightTemp->frequency >= leftTemp->frequency) {
				node->left = left;
				node->right = right;
			}
			else {
				node->left = right;
				node->right = left;
			}
		}
		else {
			node->left = NULL;
			node->right = NULL;
		}
	}
	return node;
}

void insertHuffmanNodeInMinHeap(_HuffmanHeap *heap, _HuffmanNode *node) {
	int i = ++(heap->heap_size);
	while (i != 1 && heap->huffman[i / 2]->frequency > node->frequency) {
		heap->huffman[i] = heap->huffman[i / 2];
		i /= 2;
	}
	heap->huffman[i] = node;
}

_HuffmanNode* deleteHuffmanNodeInMinHeap(_HuffmanHeap *heap) {
	_HuffmanNode *ret = heap->huffman[1];
	_HuffmanNode *newNode = heap->huffman[heap->heap_size];
	heap->huffman[(heap->heap_size)--] = NULL;
	int i = 2;
	while (i <= heap->heap_size) {
		if (i < heap->heap_size && heap->huffman[i]->frequency > heap->huffman[i + 1]->frequency) {
			i++;
		}
		if (heap->huffman[i]->frequency < newNode->frequency) {
			heap->huffman[i / 2] = heap->huffman[i];
			i *= 2;
		}
		else {
			break;
		}
	}
	if (i > 2) {
		heap->huffman[i / 2] = newNode;
	}
	else {
		heap->huffman[1] = newNode;
	}
	return ret;
}

void createHuffmanCode(_HuffmanNode *root, map<int, _HuffmanCode>* m, long long pCode, int size) {
	if (root) {
		if (root->left != NULL) {
			createHuffmanCode(root->left, m, (pCode << 1) | 1, size + 1);
		}
		if (root->right != NULL) {
			createHuffmanCode(root->right, m, (pCode << 1) | 0, size + 1);
		}
		if (root->left == NULL && root->right == NULL) {
			_HuffmanCode huffmanCode;
			huffmanCode.code = pCode;
			huffmanCode.size = size;
			int value = root->value > 25 ? (root->value) + 71 : (root->value) + 65;
			m->insert(pair<int, _HuffmanCode>(value, huffmanCode));
		}
	}
}

void deleteHuffmanNodes(_HuffmanNode *root) {
	if (root) {
		if (root->left) {
			deleteHuffmanNodes(root->left);
		}
		if (root->right) {
			deleteHuffmanNodes(root->right);
		}
		free(root);
	}
}

int createHuffmanNodes(map<int, _HuffmanCode>* m) {
	int alphabet[MAX_CHARACTER_NUMBER] = { 0, };
	string sentence;
	cout << "Input a sentence : ";
	getline(cin, sentence);
	if (!sentence.empty()) {
		for (int i = 0; i < sentence.length(); i++) {
			if (sentence[i] >= 65 && sentence[i] <= 90) {
				alphabet[sentence[i] - 65]++;
			}
			else if (sentence[i] >= 97 && sentence[i] <= 122) {
				alphabet[sentence[i] - 97 + 26]++;
			}
			else {
				return -1;
			}
		}

		_HuffmanHeap heap;
		heap.heap_size = 0;
		for (int i = 0; i < MAX_HUFFMAN_HEAP_SIZE; i++) {
			heap.huffman[i] = NULL;
		}
		int total = 0;
		for (int i = 0; i < MAX_CHARACTER_NUMBER; i++) {
			if (alphabet[i]) {
				_HuffmanNode *node = makeTree(NULL, NULL);
				if (node == NULL) {
					exit(1);
				}
				node->value = i;
				node->frequency = alphabet[i];
				insertHuffmanNodeInMinHeap(&heap, node);
				total++;
			}
		}

		for (int i = 0; i < total - 1; i++) {
			_HuffmanNode *node1 = deleteHuffmanNodeInMinHeap(&heap);
			_HuffmanNode *node2 = deleteHuffmanNodeInMinHeap(&heap);
			_HuffmanNode *newNode = makeTree(node1, node2);
			newNode->frequency = node1->frequency + node2->frequency;
			insertHuffmanNodeInMinHeap(&heap, newNode);
		}
		
		createHuffmanCode(heap.huffman[1], m, 0, 0);
		deleteHuffmanNodes(heap.huffman[1]);
		return 0;
	}
	return -1;
}

void showHuffmanCode(map<int, _HuffmanCode> *m) {
	if (m->size() == 0) {
		cout << "Make a new huffman code" << endl;
		return;
	}
	map<int, _HuffmanCode>::iterator mi;
	for (mi = m->begin(); mi != m->end(); mi++) {
		printf("%c : ", mi->first);
		for (int i = mi->second.size - 1; i >= 0; i--) {
			printf("%d", ((mi->second.code) >> i) & 1);
		}
		cout << endl;
	}
}

void encodeWord(map<int, _HuffmanCode> *m) {
	if (m->size() == 0) {
		cout << "Make a new huffman code" << endl;
		return;
	}
	cout << "Input a word : ";
	string word;
	getline(cin, word);
	if(!word.empty()) {
		string code = "code : ";
		for (int i = 0; i < word.length(); i++) {
			if (m->find(word[i]) != m->end()) {
				for (int j = m->find(word[i])->second.size - 1; j >= 0; j--) {
					string temp = string(((m->find(word[i])->second.code >> j) & 1) == 0 ? "0" : "1");
					code += temp;
				}
			}
			else {
				cout << "Invalid word" << endl;
				return;
			}
		}
		cout << code << endl;
	}
}

void decodeCode(map<int, _HuffmanCode> *m) {
	if (m->size() == 0) {
		cout << "Make a new huffman code" << endl;
		return;
	}
	cout << "Input a code : ";
	string codeStr;
	getline(cin, codeStr);
	if(!codeStr.empty()) {
		unsigned long long code = 0;
		int size = codeStr.length();
		for (int i = 0; i < size; i++) {
			if (codeStr[i] == '1') {
				code |= (1 << (size - i - 1));
			}
			else if (codeStr[i] == '0') {}
			else {
				cout << "Invalid code" << endl;
				return;
			}
		}
		string result = "";
		while (size > 0) {
			bool check = false;
			map<int, _HuffmanCode>::iterator mi;
			for (mi = m->begin(); mi != m->end(); mi++) {
				if (mi->second.size > size) {
					continue;
				}
				// Using a memory for this bitmask which is reusable
				// is enough to consider to save algorithms time.
				unsigned long long compareBit = power_recursive(2, mi->second.size) - 1;
				if ((compareBit & (code >> (size - mi->second.size))) == mi->second.code) {
					char ch = mi->first;
					result += ch;
					compareBit = power_recursive(2, size - mi->second.size) - 1;
					code &= compareBit;
					size -= mi->second.size;
					check = true;
					break;
				}
			}
			if (!check) {
				cout << "Invalid code" << endl;
				return;
			}
		}
		cout << result << endl;
	}
}