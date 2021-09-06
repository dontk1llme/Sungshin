//교재 15.2번
//하진님 코드, 말로님 코드 보고 공부해보기 ^^~

#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
	string name;
	string address;
	string number;
	string email;

public :
	virtual string toString() const {
		return "Person";
	}
};

class Student : public Person
{
private:
	int status;

public:
	string toString() const {
		return "Student";
	}
};

class Mydate {
public:
	int year;
	int month;
	int day;
};

class Employee : public Person
{
protected:
	string office;
	int salary;
	Mydate dateHired;

public: 
	string toString() const
	{
	return "Employee";
	}
};



class Faculty : public Employee
{ 
private:
	string officeHours;
	int rank;

public:
	string toString() const
	{
		return "Faculty";
	}
};

class Staff : public Employee
{
private:
	string title;

public:
	string toString() const
	{
		return "Staff";
	}
};



//virtual을 함수 안에서 구현할 수 잇는 조건
// 1. 함수를 virtual로 선언
// 2. 외부에서 함수 만들어서 그 매개변수로 주소전달하기 (&든 *든)
// 짜잔 다형성~
void why(Person& p) {
	cout << p.toString() << endl;
}




int main() {
	Person p;
	Student std;
	Employee e;
	Faculty f;
	Staff stf;

	//오버라이딩
	cout << p.toString() << endl;
	cout << std.toString() << endl;
	cout << e.toString() << endl;
	cout << f.toString() << endl;
	cout << stf.toString() << endl;

	//다형성
	why(p);
	why(std);
	why(e);
	why(f);
	why(stf);


	return 0;

}