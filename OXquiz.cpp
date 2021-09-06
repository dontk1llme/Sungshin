#include <iostream>
using namespace std;

#define MAX 80

int countOX(char str[], int len)
{
    int sum, count;

    for (int i = 0; i < len; i++) {
        sum = 0;
        count = 0;
        for (int j = 0; j < len; j++)
        {
            if (str[j] == 'O') count++;
            if (str[j] == 'X') count = 0;
            sum += count;
        }
    }
    return sum;
}

int main()
{
    int n = 0;
    int result[30];
    char str[MAX];

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> str;
        result[i] = countOX(str, strlen(str));
    }

    for (int i = 0; i < n; i++)
        cout << result[i] << endl;
}