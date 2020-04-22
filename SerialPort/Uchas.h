#include <iostream>
using namespace std;
class Uchas
{
private:
	string name, lastname, surname, school;
	int age,time;
public:
	void setname();
	void setsurname();
	void setlastname();
	void setschool();
	void setage();
	void settime(int h);
	string getname();
	string getsurname();
	string getlastname();
	string getschool();
	int getage();
	void gettime();
	int getstime();
}; 