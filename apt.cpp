#include <iostream>
#include <algorithm>
using namespace std;

int n;
int danji_num;
int label[26][26] = { 0, };	// ���̺�(house)
int danji_max[314] = { 0, };


bool isValid(int a, int b)
{
	return (0 <= a && a < n) && (0 <= b && b < n);
}

void dfs(int a, int b, int danji_num)
{

	label[a][b] = -1;
	danji_max[danji_num]++;
	int x, y;
	int cur_house;

	for (int i = 0; i < 4; i++) {
		switch (i)
		{
		case 0: x = a - 1; y = b; break;
		case 1: x = a + 1; y = b; break;
		case 2: x = a; y = b - 1; break;
		case 3: x = a; y = b + 1; break;
		}
		cur_house = label[x][y];
		if (isValid(x, y) && cur_house == 1) dfs(x, y, danji_num);
	}
	return;
}

void search() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (label[i][j] == 1) {
				dfs(i, j, ++danji_num);
			}
		}
	}
	return;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf_s("%1d", &label[i][j]);
		}
	}

	search();

	//�� ���� ��
	sort(danji_max + 1, danji_max + danji_num + 1);
	cout << danji_num << "\n";

	//���� �� ���� ��
	if (danji_num != 0) {
		for (int i = 1; i <= danji_num; i++) {
			cout << danji_max[i] << "\n";
		}
	}

	//NxN���� ���
	//����� �� �����µ� ��� ����ؾ� ���� ��. 
	//�ڵ� �������⿡�� �õ��� �ôµ� ��𿡼� �󺧸��� �ؾ� ����?
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (label[i][j] == -1) label[i][j] = danji_max[i];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << label[i][j] << " ";
		}
		cout << "\n";
	}


	return 0;
}