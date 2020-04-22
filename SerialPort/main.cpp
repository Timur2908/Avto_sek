#pragma warning(disable : 4996)
#include<iostream>
#include "Uchas.h"
#include<fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <windows.h>
#include<locale>
#include<string>
#include<stdlib.h>
#include"SerialPort.h"
using namespace std;

char datac;
int n;
int k = 0;
string eng = "";
string file_adress = "";
string file_adress2 = "";
string f = "";
string time_str = "";

bool sortik(Uchas p, Uchas b) {
	return (p.getstime()< b.getstime() ? 1 : 0);
}

Uchas uch[1000];

void sort_time() {
	long long a, b, c;
	long long m;
	a = stoi(time_str.substr(0, 2));
	b = stoi(time_str.substr(3, 2));
	c = stoi(time_str.substr(6, 2));
	m = (a * 60000) + (b * 1000) + c;
	uch[k].settime(m);
	sort(uch, uch + k + 1, sortik);
	for (int i = 0; i <= k; i++) {
		cout << uch[i].getname() << " ";
		cout << uch[i].getsurname() << " ";
		cout << uch[i].getlastname() << ":";
		uch[i].gettime();
	}         
	k++;
}

void SetPos(int x, int y)
 {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
char output [MAX_DATA_LENGTH];
char incomingData[MAX_DATA_LENGTH];
char port [] = "\\\\.\\COM3";
int main() {
	system("color 02");
	setlocale(LC_ALL, "ru");
	cout << "Введите адрес файла в котором будет создан отчёт соревнований" << endl;
	cin >> file_adress;
	if (file_adress.find('"') != -1) {
		file_adress.erase(0, 1);
		file_adress.erase(file_adress.size() - 1, 1);
	}
	fstream fout;
	fout.open(file_adress, fstream::in | fstream::out | fstream::app);
	if (fout.is_open() == false) {
		cout << "Не удалось открыть файл" << endl;
	}
	else {
		cout << "Файл открыт" << endl;
	}

	cout << "Введите количество участников" << "\n";
	cin >> n;
	cout << "Введите ФИО, место обучения и возраст участников по порядку их проезда." << "\n";
	SetConsoleCP(1251);
	for (int i = 0; i < n; i++) {
		uch[i].setname();
		uch[i].setsurname();
		uch[i].setlastname();
		uch[i].setschool();
		uch[i].setage();
	}
	SetConsoleCP(866);

	SerialPort arduino(port);
	if (arduino.isConnected()) {
		cout << "Последовательный порт " << port << " подключен" << endl << endl;
	}
	else {
		cout << "Ошибка подключения последовательный порта" << endl << endl;
	}

	while (arduino.isConnected()) {
			arduino.writeSerialPort(&datac, MAX_DATA_LENGTH);
			arduino.readSerialPort(output, MAX_DATA_LENGTH);
			f = string(output);
			time_str = f.substr(f.find(':') + 1);
			if (output[0] == 'T') {
					SetPos(0, n + 8);
					sort_time();
				if (k == n) {
					fout << "Отчёт соревнований по робототехнике" << "\n";
					fout << "Участники:" << "\n";
					for (int i = 0; i < n; i++) {
						fout << uch[i].getname() << " ";
						fout << uch[i].getsurname() << " ";
						fout << uch[i].getlastname() << " ";
						fout << uch[i].getschool() << " ";
						fout << uch[i].getage() << "\n" << "\n";
					}
					fout << "Результаты времени:" << "\n";
					for (int i = 0; i < n; i++) {
						fout << uch[i].getname() << " ";
						fout << uch[i].getsurname() << " ";
						fout << uch[i].getlastname() << ":";
						fout << uch[i].getstime() / 60000 << "." << ((uch[i].getstime() / 1000) % 1000) << "." << (uch[i].getstime() % 1000) << "      " << "\n" << "\n";
		
					}
					fout << "Победители и призёры:" << "\n";
					fout << "Первое место " << uch[0].getname() << " " << uch[0].getsurname() << " " << uch[0].getlastname() << "\n";
					fout << "Второе место " << uch[1].getname() << " " << uch[1].getsurname() << " " << uch[1].getlastname() << "\n";
					fout << "Третье место " << uch[2].getname() << " " << uch[2].getsurname() << " " << uch[2].getlastname() << "\n";

					SetPos(0, (n * 2) + 9);
					cout << "Соревнования окончены!" << "\n";
					cout << "Победители и призёры:" << "\n";
					cout << "Первое место " << uch[0].getname() << " " << uch[0].getsurname() << " " << uch[0].getlastname() << "\n";
					cout << "Второе место " << uch[1].getname() << " " << uch[1].getsurname() << " " << uch[1].getlastname() << "\n";
					cout << "Третье место " << uch[2].getname() << " " << uch[2].getsurname() << " " << uch[2].getlastname() << "\n";
					cout << "Для выхода введите любой символ" << "\n";
					cin >> eng;
					if (eng != "") return 0;
				}
			}
			for (int i = 0; i < MAX_DATA_LENGTH; i++) {
				output[i] = { 0 };
			}
			f = "";
			time_str = "";
	}
	fout.close();
	return 0;
}