// 9-8 Data
#include <iostream>
#include <ctime>
using namespace std;

class Date {
private:
	int year;
	int month;
	int day;

public:
	Date() {
		setDate(time(0));
	}

	Date(int elapseTime) {
		setDate(elapseTime);
	}

	Date(int y, int m, int d) {
		year = y;
		month = m;
		day = d;
	}

	int getYear() {
		return year;
	}

	int getMonth() {
		return month;
	}

	int getDay() {
		return day;
	}

	void setDate(int elapseTime) {
		int seconds = elapseTime;
		int minutes = seconds / 60;
		int hours = minutes / 60;
		day = hours / 24;

		//getYear
		year = 1970;
		while (day >= (isLeapYear(year) ? 366 : 365)) {
			day = day - (isLeapYear(year) ? 366 : 365);
			year++;
		}


		//getMonth
		month = 1;
		while (day >= getNumberOfDaysInMonth(year, month)) {
			day = day - getNumberOfDaysInMonth(year, month);
			month++;
		}
	}

	bool isLeapYear(int year) { // ������. (4�� ������, 100���� �ȶ�����, 400���δ� ������)
								// 400 or (4 and !100)
		return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
	}

	int getNumberOfDaysInMonth(int year, int month) {
		if (month == 1 || month == 3 || month == 5 || month == 7 ||
			month == 8 || month == 10 || month == 12)
			return 31;

		if (month == 4 || month == 6 || month == 9 || month == 11)
			return 30;

		if (month == 2) return isLeapYear(year) ? 29 : 28;

		return 0;

	}
};

int main() {
	Date date; 
	cout << date.getYear() << "�� " << date.getMonth() << "�� " << date.getDay() +1 << "��"<< endl;
	
	Date date2(555550);
	cout << date2.getYear() << "�� " << date2.getMonth() << "�� " << date2.getDay() <<"��"<< endl;

	Date date3(561555550);
	cout << date3.getYear() << "�� " << date3.getMonth() << "�� " << date3.getDay() << "��" << endl;

	Date date4(2021, 4, 27);
	cout << date4.getYear() << "�� " << date4.getMonth() << "�� " << date4.getDay() << "��" << endl;

}

//https://coding-factory.tistory.com/668