#include "header.h"

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
	getline(cin, command);
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
		else {
			return ret;
		}
	}
	return ret;
}