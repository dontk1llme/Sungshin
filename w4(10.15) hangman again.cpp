#include <iostream>
#include <ctime>
using namespace std;

string words[] = { "program", "write", "that", "mallo", "lopppii", "chupppa", "dontkillme" };

void hangman() {
	srand(time(0));
	int sz = sizeof(words) / sizeof(words[0]);
	string q = words[rand() % sz];
	string res(q.length(), '*');

	int wrong = 0;
	int startindex;

	while (res != q)
	{
		string w;
		cout << "(Guess) Enter a letter in word " << res << " > ";
		cin >> w;

		if (res.find(w) != string::npos) { // �̹� ���� ��
			cout << "    " << w << " is already in the word" << endl;
		}
		else if (q.find(w) == string::npos) { // ���� ������ ��
			cout << "    " << w << " is not in the word" << endl;
			wrong++;
		}
		else {
			int i = 0;
			while (q.find(w, i) != string::npos) {
				res.replace(q.find(w, i), 1, w);
				i = q.find(w, i) + 1;
			}


			//�ʵ�. w�� char�� �ϰ� �������� �޴µ� ����
			//int i = 0;
			//int x;
			//x = q.find(w, i);
			//while (x != -1) {
			//	res[x] = w;
			//	i = x + 1;
			
		}
	}
	cout << "The word is " << res << ". You missed " << wrong << " time" << endl << endl
	<< "Do you want to guess for another word? Enter y or n > ";

	while (true) {
		cin >> res;
		if (res == "y") {
			hangman();
			return;
		}
		else if (res == "n") {
			return;
		}
		else {
			cout << "Enter y or n > ";
		}
	}
}

int main() {
	cout << " �ƢƢƢ�  League of Legends Hangman �ƢƢƢ� " << endl << endl;
	hangman();
	return 0;
}