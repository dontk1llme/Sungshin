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

		if (res.find(w) != string::npos) { // 이미 있을 때
			cout << "    " << w << " is already in the word" << endl;
		}
		else if (q.find(w) == string::npos) { // 없는 문자일 때
			cout << "    " << w << " is not in the word" << endl;
			wrong++;
		}
		else {
			int i = 0;
			while (q.find(w, i) != string::npos) {
				res.replace(q.find(w, i), 1, w);
				i = q.find(w, i) + 1;
			}


			//않되. w를 char로 하고 받으려고 햇는데 실패
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
	cout << " ▒▒▒▒  League of Legends Hangman ▒▒▒▒ " << endl << endl;
	hangman();
	return 0;
}