#include <iostream>
#include <algorithm>
using namespace std;

string m[100];	// 행렬 입력
int label[100][100];	// 레이블링
int countNum[100];	// 단지 내 집 개수 저장
int n;		// 행렬 차원
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
bool isAllZero()	// label 배열의 값이 모두 0인지 체크 -> 안전영역 없으니 실행 중지
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (label[i][j] != 0) return false;
	return true;
}
void display(int n) {
	for (int i = 0; i < n; i++) {  // test : 안전영역 출력
		for (int j = 0; j < n; j++)
			cout << label[i][j] << " ";
			cout << endl;
		}
}
void aptNumbering(int n) {
	int count = 0;	       // CC 개수 초기화
	int ccount = 0;			//
	for (int i = 0; i < n; i++) { // m 배열을 label에 2차원 행렬로
		for (int j = 0; j < n; j++) {
			label[i][j] = m[i].at(j) - '0';
		}
	}
	for (int i = 0; i < n; i++) {   // Connected Component 알고리즘
		for (int j = 0; j < n; j++)   // 맵을 탐색하면서 label 1인 부분은 dfs로
			if (label[i][j] == 1) {
				dfsN = 0;
				count++;	// 새로운 CC를 찾을 때마다 증가				
				dfs(i, j, count + 1);
				countNum[ccount++] = dfsN;
				dfs(i, j, dfsN, count + 1);
			}
	}
	cout << ccount << endl;
	sort(countNum, countNum + ccount);	//정렬
	for (int i = 0; i < ccount; i++) {
		cout << countNum[i] << endl;
	}
}
int main()
{
	// 입력
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> m[i];
	cout << endl;
	aptNumbering(n);
	display(n);

	return 0;
}