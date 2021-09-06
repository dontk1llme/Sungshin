#include <iostream>
using namespace std;
#define MAX 80

int dial(char str[], int len)
{
    int sum = 0;

    for (int i = 0; i<len ; i++)
    {
        switch (str[i])
        {
        case 'A':
        case 'B':
        case 'C': sum += 3; break;
        case 'D':
        case 'E':
        case 'F': sum += 4; break;
        case 'G':
        case 'H':
        case 'I': sum += 5; break;
        case 'J':
        case 'K':
        case 'L': sum += 6; break;
        case 'M':
        case 'N':
        case 'O': sum += 7; break;
        case 'P':
        case 'Q':
        case 'R':
        case 'S': sum += 8; break;
        case 'T':
        case 'U':
        case 'V': sum += 9; break;
        case 'W': 
        case 'X':
        case 'Y':
        case 'Z': sum += 10; break;
        }
    }
    return sum;
}

int main()
{
    int n;
    char s[MAX];
    int result[30];

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> s;
        result[i] = dial(s, strlen(s));
    }
    for (int i=0; i<n; i++) 
        cout << result[i] << endl;
}