#include "header.h"

int sub_iterative(int num) {
	int i, sum = 0;
	for (i = num; i > 0; i = i - 3) {
		sum += i;
	}
	return sum;
}

int sub_recursive(int num) {
	if (num < 0) return 0;
	return num + sub_recursive(num - 3);
}

int power_recursive(int base, int expo) {
	if (expo == 0) return 1;
	else if (expo % 2) return base * power_recursive(base * base, (expo - 1) / 2);
	else return power_recursive(base * base, expo / 2);
}

void hanoi_tower(int num, char from, char temp, char to) {
	if (num == 1) {
		cout << from << " >> " << to << " 1" << endl;
	}
	else {
		hanoi_tower(num - 1, from, to, temp);
		cout << from << " >> " << to << " " << num << endl;
		hanoi_tower(num - 1, temp, from, to);
	}
}