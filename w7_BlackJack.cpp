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

	//3�� for �ݺ���: 3�� ���� m�� �ִ��� ������ ����� ����, ī�� �̱�
	for (int i = 0; i < n - 2; i++) {
		for (int j = i + 1; j < n - 1; j++) { //j�� i+1 �̱⿡ 1���� ����
			for (int k = j + 1; k < n; k++) {// k�� j+1�̱⿡ 2���� ����.
				sum = arr[i] + arr[j] + arr[k];
				if (sum <= m && sum>res) //���� m���ٴ� �۰� ���� ������� ũ��
					res = sum;
			}
		}
	}
	cout <<'\n'<< res << endl;
	return 0;

}