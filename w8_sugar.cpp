#include <iostream>
using namespace std;

//3x+5y=n �ƴѰ�? ��� y>x���� ��.
// n/5 �� ���� �� ���� 3���� ������. ����������� ����, �ƴϸ� y�� ���̸鼭.
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
//18�� �־��ٰ� ġ�� else�� ���� 15�� �ǰ� bag��1��
//�׷� if�� ���� n%5==0�̴ϱ� bag�� 1+3=4��

//4 �־��ٰ� ġ�� else�� ���� 1�� ��. �ٽ� else�� �ͼ� -2�Ǵϱ� 0���� �����ϱ� -1��

//6�־��ٰ� ġ�� else�� ���� 3�ǰ� bag=1, 3��else�ΰ��� bag=2�ǰ� ��