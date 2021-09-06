#include <iostream>
using namespace std;

//3x+5y=n 아닌겨? 대신 y>x여야 함.
// n/5 해 보고 그 값을 3으로 나누기. 나누어떨어지면 정답, 아니면 y를 줄이면서.
int main() {
	int n;
	int bag = 0;

	cin >> n;

	while (1) {
		if (n % 5 == 0) {
			bag = bag + (n / 5);
			cout << bag << endl;
			break;
		}
		else {
			n = n - 3;
			if (n < 0) {
				cout << "-1" << endl;
				break;
			}
			bag++;
		}
	}
	return 0;
}
//18을 넣엇다고 치면 else로 가서 15가 되고 bag이1됨
//그럼 if로 가서 n%5==0이니까 bag은 1+3=4됨

//4 넣엇다고 치면 else로 가서 1이 됨. 다시 else로 와서 -2되니까 0보다 작으니까 -1됨

//6넣엇다고 치면 else로 가서 3되고 bag=1, 3은else로가서 bag=2되고 끗