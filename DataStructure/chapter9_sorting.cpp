#include "header.h"

int Sorting::size = 0;
int* Sorting::_array = NULL;
CRITICAL_SECTION Sorting::cs;
int Sorting::count = 0;

void sortingSimulation() {
	Sorting::initialize();
	showCommandInSorting();
	string command; cin >> command;
	while (command != "f") {
		if (command == "c") {
			Sorting::reset();
		}
		else if (command == "o") {
			Sorting::showArray(NULL, 0);
		}
		else {
			sortingManager(command);
		}
		showCommandInSorting();
		cin >> command;
	}
	Sorting::finish();
}

void showCommandInSorting() {
	cout << "*************************" << endl;
	cout << "* c : create an array\t*" << endl;
	cout << "* o : show origin array\t*" << endl;
	cout << "* --------------------- *" << endl;
	cout << "*    example : sib \t*" << endl;
	cout << "* --------------------- *" << endl;
	cout << "* s : selection sorting\t*" << endl;
	cout << "* i : insertion sorting\t*" << endl;
	cout << "* b : bubble sorting\t*" << endl;
	cout << "* e : shell sorting\t*" << endl;
	cout << "* m : merge sorting\t*" << endl;
	cout << "* q : quick sorting\t*" << endl;
	cout << "* h : heap sorting\t*" << endl;
	cout << "* r : radix sorting\t*" << endl;
	cout << "* --------------------- *" << endl;
	cout << "* f : finish\t\t*" << endl;
	cout << "*************************" << endl;
}

int Sorting::getSize() { return size; }
void Sorting::setSize(int size) { this->size = size; }
void Sorting::setArray() {
	if (_array != NULL) {
		delete _array;
	}
	do {
		cout << "Range : " << 1 << " ~ " << Sorting::MAX_SIZE << endl;
		cout << "Input the size of an array : ";
		cin >> size;
	} while (size < 1 || size > Sorting::MAX_SIZE);
	cout << "Wait a second to create the array that contains random number." << endl;
	_array = new int[size];
	if (_array == NULL) {
		cout << "Memory allocation failed" << endl;
		exit(1);
	}
	srand((unsigned int)time(NULL));
	this_thread::sleep_for((rand() % 5 + 1) * 1s);
	for (int i = 0; i < size; i++) {
		_array[i] = rand();
	}
}

void Sorting::showArray(int* arr, int size) {
	if (arr == NULL && size == 0) {
		arr = _array;
		size = Sorting::size;
	}
	if (size > 100) {
		cout << "The result is skipped because its size is larger than 100" << endl;
		return;
	}
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int* Sorting::copyArray() {
	int *newArray = new int[size];
	memcpy(newArray, _array, size * sizeof(int));
	return newArray;
}

void Sorting::initialize() {
	InitializeCriticalSection(&cs);
	reset();
}

void Sorting::reset() {
	setArray();
	count = 0;	
}

void Sorting::finish() {
	DeleteCriticalSection(&cs);
	delete _array;
}

void Sorting::increaseCount() {
	EnterCriticalSection(&cs);
	count++;
	LeaveCriticalSection(&cs);
}

void Sorting::decreaseCount(int *arr, int size, string type, double runtime) {
	EnterCriticalSection(&cs);
	cout << type + " finished! " << "Run time : " << runtime << " sec" << endl;
	showArray(arr, size);
	count--;
	LeaveCriticalSection(&cs);
}

int Sorting::getCount() {
	return count;
}

void SelectionSorting::sorting() {
	if (arr != NULL) delete arr;
	arr = copyArray();
	int size = getSize();
	DWORD start;
	DWORD end;
	start = GetTickCount();
	for (int i = 0; i < size; i++) {
		int min = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[min] > arr[j]) {
				min = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
	end = GetTickCount();
	decreaseCount(arr, size, "Selection sorting", (end - start) / (double)1000);
	delete arr;
}

void InsertionSorting::sorting() {
	if (arr != NULL) delete arr;
	arr = copyArray();
	int size = getSize();
	DWORD start;
	DWORD end;
	start = GetTickCount();
	for (int i = 1; i < size; i++) {
		int key = arr[i], j;
		for (j = i - 1; j >= 0 && arr[j] > key; j--) {
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
	}
	end = GetTickCount();
	decreaseCount(arr, size, "Insertion sorting", (end - start) / (double)1000);
	delete arr;
}

void BubbleSorting::sorting() {
	if (arr != NULL) delete arr;
	arr = copyArray();
	int size = getSize();
	DWORD start;
	DWORD end;
	start = GetTickCount();
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	end = GetTickCount();
	decreaseCount(arr, size, "Bubble sorting", (end - start) / (double)1000);
	delete arr;
}

void ShellSorting::sorting() {
	if (arr != NULL) delete arr;
	arr = copyArray();
	int size = getSize();
	DWORD start;
	DWORD end;
	start = GetTickCount();
	for (int gap = size / 2; gap > 0; gap /= 2) {
		if (gap % 2 == 0) {
			gap++;
		}
		for (int i = 0; i < gap; i++) {
			for (int j = i + gap; j < size; j = j + gap) {
				int key = arr[j], k;
				for (k = j - gap; k >= 0 && arr[k] > key; k = k - gap) {
					arr[k + gap] = arr[k];
				}
				arr[k + gap] = key;
			}
		}
	}
	end = GetTickCount();
	decreaseCount(arr, size, "Shell sorting", (end - start) / (double)1000);
	delete arr;
}

void MergeSorting::merge(int* arr, int left, int right) {
	if (left == right) return;
	int mid = (left + right) / 2;
	merge(arr, left, mid);
	merge(arr, mid + 1, right);
	int i = left, j = mid + 1, k = left;
	while (i <= mid && j <= right) {
		if (arr[i] > arr[j]) sorted[k++] = arr[j++];
		else sorted[k++] = arr[i++];
	}
	while (i <= mid) sorted[k++] = arr[i++];
	while (j <= right) sorted[k++] = arr[j++];
	for (int n = left; n <= right; n++) arr[n] = sorted[n];
}

void MergeSorting::sorting() {
	if (arr != NULL) delete arr;
	arr = copyArray();
	int size = getSize();
	sorted = new int[size];
	DWORD start;
	DWORD end;
	start = GetTickCount();
	merge(arr, 0, size - 1);
	end = GetTickCount();
	decreaseCount(arr, size, "Merge sorting", (end - start) / (double)1000);
	delete sorted, arr;
}

void QuickSorting::quick(int* arr, int left, int right) {
	if (left == right) return;
	int pivot = arr[left], i = left, j = right + 1, temp;
	while (i < j) {
		do { i++; } while (i <= j && arr[i] < pivot);
		do { j--; } while (j >= i && arr[j] > pivot);
		if (i < j) {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	temp = arr[j];
	arr[j] = pivot;
	arr[left] = temp;
	if(j > left) quick(arr, left, j - 1);
	if(j < right) quick(arr, j + 1, right);
}

void QuickSorting::sorting() {
	if (arr != NULL) delete arr;
	arr = copyArray();
	int size = getSize();
	DWORD start;
	DWORD end;
	start = GetTickCount();
	quick(arr, 0, size - 1);
	end = GetTickCount();
	decreaseCount(arr, size, "Quick sorting", (end - start) / (double)1000);
	delete arr;
}

void HeapSorting::sorting() {
	if (arr != NULL) delete arr;
	arr = copyArray();
	int size = getSize();
	DWORD start;
	DWORD end;
	start = GetTickCount();
	// push the numbers in the heap array
	for (int i = 0; i < size; i++) {
		int j = i, newOne = arr[j];
		while (j != 0 && arr[(j - 1) / 2] > newOne) {
			arr[j] = arr[(j - 1) / 2];
			j = (j - 1) / 2;
		}
		arr[j] = newOne;
	}
	// pop the numbers ascending
	int* arr2 = new int[size];
	for (int i = 0; i < size; i++) {
		arr2[i] = arr[0];
		int lastOne = arr[size - i - 1], j = 1;
		while(j < size - i - 1) {
			if (j + 1 < size - i - 1 && arr[j] > arr[j + 1]) j++;
			if (arr[j] < lastOne) arr[(j - 1) / 2] = arr[j];
			else break;
			j = j * 2 + 1;
		}
		arr[(j - 1) / 2] = lastOne;
	}
	end = GetTickCount();
	decreaseCount(arr2, size, "Heap sorting", (end - start) / (double)1000);
	delete arr, arr2;
}

// Using vectors is too slow
/*
void RadixSorting::sorting() {
	int size = getSize(), digit = 10;
	vector<int> queue, buckets[10];
	queue.reserve(size);
	for (int i = 0; i < size; i++) {
		buckets[_array[i] % digit].push_back(_array[i]);
	}
	while (1) {
		queue.clear();
		int check = 0;
		for (int i = 0; i < 10; i++) {
			if (!buckets[i].empty()) {
				queue.insert(queue.end(), buckets[i].begin(), buckets[i].end());
				buckets[i].clear();
				check++;
			}
		}
		if (check == 1) break;
		vector<int>::iterator vi;
		for (vi = queue.begin(); vi != queue.end(); vi++)
			buckets[((*vi) / digit) % 10].push_back(*vi);
		digit *= 10;
	}
	showArray(queue);
	decreaseCount();
}*/

// Using arrays is faster than using vectors
// However, it can cover the range of 1 ~ 30,000,000(MAX_SIZE, approximately, if this thread only runs).
// It also requires a lot of memory as arrays.
void RadixSorting::sorting() {
	int size = getSize(), digit = 10;
	int *queue = new int[size], *buckets[10], sizes[10] = { 0, };
	if (queue == NULL) exit(1);
	for (int i = 0; i < 10; i++) {
		buckets[i] = new int[size];
		if (buckets[i] == NULL) exit(1);
	}
	DWORD start;
	DWORD end;
	start = GetTickCount();
	for (int i = 0; i < size; i++) {
		buckets[_array[i] % 10][(sizes[_array[i] % 10])++] = _array[i];
	}
	while (1) {
		int check = 0, point = 0;
		for (int i = 0; i < 10; i++) {
			if (sizes[i] != 0) {
				memcpy(queue + point, buckets[i], sizes[i] * sizeof(int));
				point += sizes[i], check++;
			}
		}
		if (check == 1) break;
		memset(sizes, 0, 10 * sizeof(int));
		for (int i = 0; i < size; i++)
			buckets[(queue[i] / digit) % 10][(sizes[(queue[i] / digit) % 10])++] = queue[i];
		digit *= 10;
	}
	end = GetTickCount();
	decreaseCount(queue, size, "Radix sorting", (end - start) / (double)1000);
	for (int i = 0; i < 10; i++)
		delete buckets[i];
	delete queue;
}

void sortingManager(string command) {
	string check = "sibemqhr";
	vector<thread> threads;
	for (int i = 0; i < check.length(); i++) {
		int index = command.find(check[i]);
		if (index >= 0) {
			if (command[index] == 's') {
				SelectionSorting ss;
				threads.push_back(thread(&SelectionSorting::sorting, ss));
				ss.increaseCount();
			}
			else if(command[index] == 'i') {
				InsertionSorting is;
				threads.push_back(thread(&InsertionSorting::sorting, is));
				is.increaseCount();
			}
			else if (command[index] == 'b') {
				BubbleSorting bs;
				threads.push_back(thread(&BubbleSorting::sorting, bs));
				bs.increaseCount();
			}
			else if (command[index] == 'e') {
				ShellSorting es;
				threads.push_back(thread(&ShellSorting::sorting, es));
				es.increaseCount();
			}
			else if (command[index] == 'm') {
				MergeSorting ms;
				threads.push_back(thread(&MergeSorting::sorting, ms));
				ms.increaseCount();
			}
			else if (command[index] == 'q') {
				QuickSorting qs;
				threads.push_back(thread(&QuickSorting::sorting, qs));
				qs.increaseCount();
			}
			else if (command[index] == 'h') {
				HeapSorting hs;
				threads.push_back(thread(&HeapSorting::sorting, hs));
				hs.increaseCount();
			}
			else if (command[index] == 'r') {
				RadixSorting rs;
				threads.push_back(thread(&RadixSorting::sorting, rs));
				rs.increaseCount();
			}
		}
	}

	/* 
	I tried to print the progress of each sorting process. (ex : Insertion 77%)
	However, I think to know the precisional progress is impossible
	because I'm not able to know how the progress is going on 
	unless I already have the result of it. 
	*/

	vector<thread>::iterator vi;
	for (vi = threads.begin(); vi != threads.end(); vi++) {
		vi->join();
	}
}