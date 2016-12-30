#include "header.h"

vector<Character> AccountManagement::originInfo;
int AccountManagement::hashTableSize;

void hashingSimulation() {
	AccountManagement* am[A_KIND_OF_HASHING] = {new LinearProbing(), new QuadraticProbing(), new DoubleHashing(), new Chaining()};
	showCommandInHashing();
	string command; cin >> command;
	while (command != "q") {
		if (command == "c") {
			AccountManagement::createOriginInfo();
			for (int i = 0; i < A_KIND_OF_HASHING; ++i)
				am[i]->createHashTable();
		}
		else if (command == "f") {
			for (int i = 0; i < A_KIND_OF_HASHING; ++i)
				am[i]->findUserInfo();
		}
		else if (command == "s") {
			for (int i = 0; i < A_KIND_OF_HASHING; ++i)
				am[i]->showHashTable();
		}
		showCommandInHashing();
		cin >> command;
	}
	for (int i = 0; i < A_KIND_OF_HASHING; ++i) delete am[i];
}

void showCommandInHashing() {
	cout << "*********************************" << endl;
	cout << "* c : create new users\t\t*" << endl;
	cout << "* f : find a user info\t\t*" << endl;
	cout << "* s : show users' info\t\t*" << endl;
	cout << "* q : quit\t\t\t*" << endl;
	cout << "*********************************" << endl;
}

void AccountManagement::createOriginInfo() {
	int size = 1;
	do {
		cout << "Input a new user number(1 ~ " << AccountManagement::MAX_USER_NUMBER << ") : ";
		cin >> size;
		if (size > AccountManagement::MAX_USER_NUMBER || size < 1) cout << "Invalid number" << endl;
		else break;
	} while (true);
	originInfo.clear();
	originInfo.reserve(size);
	srand((unsigned int)time(NULL));
	int i = 0;
	while(i < size) {
		string id = "", role = "";
		for(int i = 0; i < ID_MAX_LENGTH; ++i) id += rand() % 26 + 97;
		auto it = find_if(originInfo.begin(), originInfo.end(), 
			[&id](Character& character)->bool { return character.id == id; });
		if (it != originInfo.end()) continue;
		int level = rand() % 100 + 1;
		if (rand() % 3 == 0) role = string("Wizard");
		else if (rand() % 3 == 1) role = string("Warrior");
		else role = string("Healer");
		originInfo.push_back(Character(id, level, role));
		++i;
	}
	hashTableSize = findUpperBoundPrimeNumber(size);
	cout << "Hash table size : " << hashTableSize << endl;
}

int AccountManagement::findUpperBoundPrimeNumber(int size) {
	vector<int> primeNumbers; primeNumbers.push_back(2);
	int arrSize = ((size - 1) >> 6) + 1;
	unsigned long *numbers = new unsigned long[arrSize];
	memset(numbers, 0, sizeof(unsigned long) * arrSize);
	numbers[0] = 1;
	for (size_t i = 3; i * i <= size; i += 2) {
		if (!((numbers[i >> 6] >> ((i >> 1) % 32)) & 1)) {
			for (size_t j = i * i; j <= size; j += (i * 2)) {
				unsigned long temp = 1u << ((j >> 1) % 32);
				numbers[j >> 6] |= temp;
			}
		}
	}
	for (size_t i = 0; i < arrSize; ++i) {
		for (size_t j = 0; j < 32; ++j) {
			if (64 * i + j * 2 + 1 > size) break;
			if (!((numbers[i] >> j) & 1u)) 
				primeNumbers.push_back(64 * i + j * 2 + 1);
		}
	}
	delete numbers;
	if (primeNumbers.back() == size) return size;
	int upperBoundPrimeNumber = size + 1;
	while (true) {
		auto it = primeNumbers.begin();
		size_t check = 0;
		while (it != primeNumbers.end()) {
			if (upperBoundPrimeNumber % (*it) == 0) break;
			++check, ++it;
		}
		if (check == primeNumbers.size()) return upperBoundPrimeNumber;
		++upperBoundPrimeNumber;
	}
	return 0;
}

void AccountManagement::showHashTable() {
	auto it = hashTable.begin();
	int index = 1;
	while (it != hashTable.end()) {
		cout << index++;
		if (it->id.empty()) cout << " Not used" << endl;
		else cout << " id : " << it->id << ", level : " << it->level << ", role : " << it->role << endl;
		++it;
	}
}

void AccountManagement::findUserInfo() {
	if (hashTable.size() > 0) {
		cout << "Input a user id : ";
		string id; cin >> id;
		while (id.size() != ID_MAX_LENGTH) {
			cout << "The id length is " << ID_MAX_LENGTH << endl;
			cin >> id;
		}
		int firstIndex = 0;
		for (int i = 0; i < ID_MAX_LENGTH; ++i) firstIndex += id[i];
		firstIndex %= hashTableSize;
		int index = firstIndex, missCount = 0;
		do {
			if (hashTable[index].id == id) {
				cout << "id : " << hashTable[index].id << ", level : " << hashTable[index].level
					<< ", role : " << hashTable[index].role << " (missed count : " << missCount << ")" << endl;
				break;
			}
			index = (index + 1) % hashTableSize, ++missCount;
		} while (index != firstIndex);
		if (missCount && index == firstIndex) cout << "The user doesn't exist" << endl;
	}
}

void LinearProbing::createHashTable() {
	hashTable.clear();
	hashTable.assign(hashTableSize, Character("", 0, ""));
	auto it = originInfo.begin();
	int collisionCount = 0, i = 0;
	while (it != originInfo.end()) {
		int key = 0;
		for (int i = 0; i < it->id.size(); ++i) key += it->id[i];
		key %= hashTableSize;
		int originPosition = key;
		do {
			if (hashTable[key].id.empty()) {
				hashTable[key](*it);
				break;
			}
			else collisionCount++; 
			key = (key + 1) % hashTableSize;
		} while (originPosition != key);
		++it;
	}
	cout << "Collision count : " << collisionCount << endl;
}

void QuadraticProbing::createHashTable() {

}

void DoubleHashing::createHashTable() {

}

void Chaining::createHashTable() {

}