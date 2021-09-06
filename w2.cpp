#include <iostream>
using namespace std;

int originRow;

void star(int row)
{
	if (row <= 0)
		return;

	char c = 'X';

	int curRow = originRow - row;   // Row�� 0���� ����
	float plusPosX = 10;			//ù Row���� ���� X ��ġ
	for (int i = 0; i < curRow; i++)
		plusPosX /= 2;

	float xPos = 0;
	for (int i = 0; i <= 40; i++) {

		if (i == (int)xPos) {
			cout << c;					//����ϰ�
			c = (c == 'X') ? 'O' : 'X';	//ox�ٲ��ֱ�
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
