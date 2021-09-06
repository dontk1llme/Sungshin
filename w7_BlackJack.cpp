#include <iostream>
#define MAX 101
using namespace std;

int main() {
	int n, m;
	int sum = 0;
	int res = 0;
	int arr[MAX];
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	//3중 for 반복문: 3개 합이 m과 최대한 가깝게 만들기 위함, 카드 뽑기
	for (int i = 0; i < n - 2; i++) {
		for (int j = i + 1; j < n - 1; j++) { //j는 i+1 이기에 1에서 시작
			for (int k = j + 1; k < n; k++) {// k는 j+1이기에 2에서 시작.
				sum = arr[i] + arr[j] + arr[k];
				if (sum <= m && sum>res) //합이 m보다는 작고 이전 결과보다 크면
					res = sum;
			}
		}
	}
	cout <<'\n'<< res << endl;
	return 0;

}