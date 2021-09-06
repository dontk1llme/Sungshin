// ���� 11.6��

#include <iostream>
#include <cstring>
using namespace std;

int* count(const char* s)
{
	int* counts = new int[10]; //�̷��� ���� �� �³�?... 
	for (int i = 0; i < 10; i++)
		counts[i] = 0;

	for (int i = 0; i < strlen(s); i++) //���ڿ� ���̸�ŭ �ݺ�
	{
		if (isdigit(s[i]))		//���ڿ��� ���ڰ� �������� �Ǵ�
			counts[s[i]-'0']++; //ASCII��� ��������. ���ڿ��̴ϱ�.
								// ������ -'0' ������ �ȳ��ͼ� �� �������� �ٵ�����
	}

	return counts;
}


int main()
{
	int* counts = count("SSN is 343 32 4545 and ID is 434 34 4323");

	cout << "SSN is 343 32 4545 and ID is 434 34 4323" << endl;
	for (int i = 0; i < 10; i++)
		cout <<"���� ���ڿ����� " << i << "�� ������ " << counts[i] <<"��"<< endl;

	return 0;

}

