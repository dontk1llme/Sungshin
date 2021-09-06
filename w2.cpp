#include <iostream>
using namespace std;

int originRow;

void star(int row)
{
	if (row <= 0)
		return;

	char c = 'X';

	int curRow = originRow - row;   // Row를 0부터 시작
	float plusPosX = 10;			//첫 Row에서 다음 X 위치
	for (int i = 0; i < curRow; i++)
		plusPosX /= 2;

	float xPos = 0;
	for (int i = 0; i <= 40; i++) {

		if (i == (int)xPos) {
			cout << c;					//출력하고
			c = (c == 'X') ? 'O' : 'X';	//ox바꿔주기
			xPos += plusPosX;

		}
		else {
			cout << "-";
		}
	}
	cout << endl;

	star(row - 1);
}


int main(void)
{
	int row;
	cin >> row;
	originRow = row;
	star(row);
	return 0;
}
