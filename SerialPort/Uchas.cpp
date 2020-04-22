#include "Uchas.h"
#include <iostream>
#include <algorithm>
using namespace std;

void Uchas::setname() {
	cin >> name;
}
void Uchas::setsurname() {
	cin >> surname;
}
void Uchas::setlastname() {
	cin >> lastname;
}
void Uchas::setschool() {
	cin >> school;
}
void Uchas::setage() {
	cin >> age;
}
void Uchas::settime(int h) {
	time = h;
}

string Uchas::getname() {
	return name;
}
string Uchas::getsurname() {
	return surname;
}
string Uchas::getlastname() {
	return lastname;
}
string Uchas::getschool() {
	return school;
}
int Uchas::getage() {
	return age;
}
void Uchas::gettime() {
	if (time > 0) {
		cout << time / 60000 << "." << ((time / 1000) % 1000) << "." << (time % 1000) << "      " << "\n";
	}
}
int Uchas::getstime() {
	return time;
}