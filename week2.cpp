#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Person {
	char name[20];
	int age;
	float salary;
};

struct Rectangle1 {
	int w;
	int h;
};

class Rectangle {
private:
	int width;
	int height;

public:
	Rectangle() {}
	Rectangle(int w, int h)
		: width(w), height(h) {
	}

	int getWidth() { return width; }

	void setWidth(int w)
	{
		width = w;
	}

	int getHeight() { return height; }

	void setHeight(int h)
	{
		height = h;
	}

	int evalArea() {
		return(width * height);
	}
	int evalPerimeter() {
		return 2 * (width + height);
	}
	void output() {
		cout << evalArea() << endl;
		cout << evalPerimeter() << endl;
	}
};

class Goods {
private:
	string name;
	string maker;
	int price;
	int rate;
public:
	Goods() {
	}
	Goods(string nm, string mk, int pc, int rt)
		: name(nm), maker(mk), price(pc), rate(rt) {
	}
	~Goods() {}

	string getName() { return name; }

	void setName(string nm) { name = nm; }

	string getMaker() { return maker; }

	void setMaker(string mk) { maker = mk; }

	int getPrice() { return price; }

	void setPrice(int pc) { price = pc; }

	int getRate() { return rate; }

	void setRate(int rt) { rate = rt; }

	int getEvalPrice() {
		return price * (100 - rate) / 100;
	}

	void EvalPrice(int pc, int rt) {
		return;
	}
};



int main() {
	// struct Person
	cout << "<struct Person>" << endl;
	int n = 0;
	cin >> n;
	Person* person = new Person[n];
	
	
	for (int i = 0; i < n; i++) {
		cin >> person[i].name;
		cin >> person[i].age;
		cin >> person[i].salary;
	}

	for (int i = 0; i < n; i++) {
		cout << person[i].name;
	}	
	cout << endl;

	int sumAge = 0, sumSalary = 0;
	for (int i = 0; i < n; i++) {
		sumAge += person[i].age;
		sumSalary += person[i].salary;
	}

	cout << sumAge << endl;
	cout << sumSalary << endl;
	cout << " " << endl;



	//struct Rectangle
	cout << "<struct Rectangle>" << endl;
	int n2 = 0;
	int i2;
	Rectangle1 arr2[4] = { 0 };

	cin >> n2;
	for (i2 = 0; i2 < n2; i2++) {
		cin >> arr2[i2].w >> arr2[i2].h;
	}

	for (i2 = 0; i2 < n2; i2++) {
		cout << arr2[i2].w * arr2[i2].h << endl;
		cout << 2 * arr2[i2].w + 2 * arr2[i2].h << endl;
	}
	cout << " " << endl;


	//class Rectangle
	cout << "<class Rectangle>" << endl;
	int n3 = 0;
	cin >> n3;
	Rectangle* rectangle = new Rectangle[n3];

	for (int i = 0; i < n3; i++) {
		int width;
		int height;

		cin >> width >> height;

		rectangle[i].setWidth(width);
		rectangle[i].setHeight(height);
	}

	for (int i = 0; i < n3; i++) {
		cout << rectangle[i].evalArea() << endl;
		cout << rectangle[i].evalPerimeter() << endl;

	}
	cout << " " << endl;


	// class Goods
	cout << "<class Goods>" << endl;
	int n4 = 0;
	cin >> n4;
	Goods* goods = new Goods[n4];

	for (int i = 0; i < n4; i++) {
		string name;
		string maker;
		int price;
		int rate;

		cin >> name >> maker >> price >> rate;

		goods[i].setName(name);
		goods[i].setMaker(maker);
		goods[i].setPrice(price);
		goods[i].setRate(rate);
	}
	for (int i = 0; i < n4; i++) {
		cout << goods[i].getEvalPrice() << endl;

		int evalPrice = goods[i].getEvalPrice();
	}
	cout << " " << endl;


	return 0;

}