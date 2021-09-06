// 교재 11.6번

#include <iostream>
#include <cstring>
using namespace std;

int* count(const char* s)
{
	int* counts = new int[10]; //이렇게 쓰는 거 맞나?... 
	for (int i = 0; i < 10; i++)
		counts[i] = 0;

	for (int i = 0; i < strlen(s); i++) //문자열 길이만큼 반복
	{
		if (isdigit(s[i]))		//문자열의 문자가 숫자인지 판단
			counts[s[i]-'0']++; //ASCII라고 생각했음. 문자열이니까.
								// 솔직히 -'0' 없으면 안나와서 걍 찍은거임 근데나옴
	}

	return counts;
}


int main()
{
	int* counts = count("SSN is 343 32 4545 and ID is 434 34 4323");

	cout << "SSN is 343 32 4545 and ID is 434 34 4323" << endl;
	for (int i = 0; i < 10; i++)
		cout <<"위의 문자열에서 " << i << "의 개수는 " << counts[i] <<"개"<< endl;

	return 0;

}

