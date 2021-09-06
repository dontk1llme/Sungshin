//���� 15.2��
//������ �ڵ�, ���δ� �ڵ� ���� �����غ��� ^^~

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



//virtual�� �Լ� �ȿ��� ������ �� �մ� ����
// 1. �Լ��� virtual�� ����
// 2. �ܺο��� �Լ� ���� �� �Ű������� �ּ������ϱ� (&�� *��)
// ¥�� ������~
void why(Person& p) {
	cout << p.toString() << endl;
}




int main() {
	Person p;
	Student std;
	Employee e;
	Faculty f;
	Staff stf;

	//�������̵�
	cout << p.toString() << endl;
	cout << std.toString() << endl;
	cout << e.toString() << endl;
	cout << f.toString() << endl;
	cout << stf.toString() << endl;

	//������
	why(p);
	why(std);
	why(e);
	why(f);
	why(stf);


	return 0;

}