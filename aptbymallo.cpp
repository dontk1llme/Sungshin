#include <iostream>
#include <algorithm>
using namespace std;

string m[100];	// ��� �Է�
int label[100][100];	// ���̺�
int countNum[100];	// ���� �� �� ���� ����
int n;		// ��� ����
int dfsN;

bool isValid(int a, int b)
{
	return (0 <= a && a < n) && (0 <= b && b < n);
}
void dfs(int a, int b, int lb, int n = 1)
{
	int x, y;
	label[a][b] = lb;
	dfsN++;
	for (int i = 0; i < 4; i++) {
		switch (i)
		{
		case 0: x = a - 1; y = b; break;
		case 1: x = a + 1; y = b; break;
		case 2: x = a; y = b - 1; break;
		case 3: x = a; y = b + 1; break;
		}
		if (isValid(x, y) && label[x][y] == n) {
			dfs(x, y, lb, n); 
		}
	}
}
bool isAllZero()	// label �迭�� ���� ��� 0���� üũ -> �������� ������ ���� ����
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (label[i][j] != 0) return false;
	return true;
}
void display(int n) {
	for (int i = 0; i < n; i++) {  // test : �������� ���
		for (int j = 0; j < n; j++)
			cout << label[i][j] << " ";
			cout << endl;
		}
}
void aptNumbering(int n) {
	int count = 0;	       // CC ���� �ʱ�ȭ
	int ccount = 0;			//
	for (int i = 0; i < n; i++) { // m �迭�� label�� 2���� ��ķ�
		for (int j = 0; j < n; j++) {
			label[i][j] = m[i].at(j) - '0';
		}
	}
	for (int i = 0; i < n; i++) {   // Connected Component �˰���
		for (int j = 0; j < n; j++)   // ���� Ž���ϸ鼭 label 1�� �κ��� dfs��
			if (label[i][j] == 1) {
				dfsN = 0;
				count++;	// ���ο� CC�� ã�� ������ ����				
				dfs(i, j, count + 1);
				countNum[ccount++] = dfsN;
				dfs(i, j, dfsN, count + 1);
			}
	}
	cout << ccount << endl;
	sort(countNum, countNum + ccount);	//����
	for (int i = 0; i < ccount; i++) {
		cout << countNum[i] << endl;
	}
}
int main()
{
	// �Է�
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> m[i];
	cout << endl;
	aptNumbering(n);
	display(n);

	return 0;
}