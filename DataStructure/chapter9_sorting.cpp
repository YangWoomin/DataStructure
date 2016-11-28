#include "header.h"

int Sorting::size = 0;
int* Sorting::_array = NULL;
map<string, int> Sorting::Status;
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
	cout << "Input the size of an array : ";
	cin >> size;
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

int* Sorting::copyArray() {
	int *newArray = new int[size];
	for (int i = 0; i < size; i++) {
		newArray[i] = _array[i];
	}
	return newArray;
}

void Sorting::showArray(int* arr, int size) {
	if (arr == NULL && size == 0) {
		arr = _array;
		size = Sorting::size;
	}
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void Sorting::initialize() {
	InitializeCriticalSection(&cs);
	reset();
}

void Sorting::reset() {
	Status.clear();
	setArray();
	count = 0;
}

void Sorting::finish() {
	DeleteCriticalSection(&cs);
	delete _array;
}

// too slow due to critical section control
void Sorting::showSortingStatus(string name, int status) {
	EnterCriticalSection(&cs);
	if (Status.find(name) == Status.end()) {
		Status.insert(pair<string, int>(name, status));
	}
	else {
		Status.find(name)->second = status;
	}
	system("cls");
	map<string, int>::iterator mi;
	for (mi = Status.begin(); mi != Status.end(); mi++) {
		cout << mi->first << " : " << mi->second << "%" << endl;
	}
	LeaveCriticalSection(&cs);
}

void Sorting::increaseCount() {
	EnterCriticalSection(&cs);
	count++;
	LeaveCriticalSection(&cs);
}

void Sorting::decreaseCount() {
	EnterCriticalSection(&cs);
	count--;
	LeaveCriticalSection(&cs);
}

int Sorting::getCount() {
	return count;
}

void Sorting::updateStatus(string name, int status) {
	if (Status.find(name) == Status.end()) {
		Status.insert(pair<string, int>(name, status));
	}
	else {
		Status.find(name)->second = status;
	}
}

void Sorting::showSortingProcess() {
	system("cls");
	map<string, int>::iterator mi;
	for (mi = Status.begin(); mi != Status.end(); mi++) {
		cout << mi->first << " : " << mi->second << "%" << endl;
	}
}

void SelectionSorting::sorting() {
	int *newArray = copyArray();
	if (newArray == NULL) {
		cout << "Memory copy failed" << endl;
		return;
	}
	int size = getSize();
	for (int i = 0; i < size; i++) {
		int min = i;
		for (int j = i + 1; j < size; j++) {
			if (newArray[i] > newArray[j]) {
				min = j;
			}
		}
		int temp = newArray[i];
		newArray[i] = newArray[min];
		newArray[min] = temp;
		// showSortingStatus("Selection", (i + 1) / (double)size * 100);
		updateStatus("Selection", (i + 1) / (double)size * 100);
	}
	// showArray(newArray, size);
	decreaseCount();
	cout << "Selection done!" << endl;
	delete newArray;
}

void InsertionSorting::sorting() {
	int *newArray = copyArray();
	if (newArray == NULL) {
		cout << "Memory copy failed" << endl;
		return;
	}
	int size = getSize();
	for (int i = 1; i < size; i++) {
		int key = newArray[i], j;
		for (j = i - 1; j >= 0 && newArray[j] > key; j--) {
			newArray[j + 1] = newArray[j];
		}
		newArray[j + 1] = key;
		// showSortingStatus("Insertion", (i + 1) / (double)size * 100);
		updateStatus("Insertion", (i + 1) / (double)size * 100);
	}
	// showArray(newArray, size);
	decreaseCount();
	cout << "Insertion done!" << endl;
	delete newArray;
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
		}
	}

	while (Sorting::getCount()) {
		this_thread::sleep_for(1s);
		Sorting::showSortingProcess();
	}

	vector<thread>::iterator vi;
	for (vi = threads.begin(); vi != threads.end(); vi++) {
		vi->join();
	}
}