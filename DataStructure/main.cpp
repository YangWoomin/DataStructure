#include "header.h"

void showCommandInMain() {
	cout << "*****************************************" << endl;
	cout << "* l : linked list simulation\t\t*" << endl;
	cout << "* e : expression simulation(stack,queue)*" << endl;
	cout << "* w : word manager(tree)\t\t*" << endl;
	cout << "* m : max heap simulation(max heap)\t*" << endl;
	cout << "* h : huffman code simulation(min heap)\t*" << endl;
	cout << "* s : sorting simulation\t\t*" << endl;
	cout << "* g : graph simulation\t\t\t*" << endl;
	cout << "* q : quit\t\t\t\t*" << endl;
	cout << "*****************************************" << endl;
}

int main(void) {
	showCommandInMain();
	string command;	cin >> command;
	while (command != "q") {
		if (command == "l")	LinkedListSimulation();
		else if (command == "e") expressionSimulation();
		else if (command == "w") wordManager();
		else if (command == "m") maxHeapSimulation();
		else if (command == "h") huffmanSimulation();
		else if (command == "s") sortingSimulation();
		else if (command == "g") graphSimulation();
		else cout << "Invalid command" << endl;
		showCommandInMain(); cin >> command;
	}
	return 0;
}