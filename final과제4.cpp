#include <iostream>
using namespace std;

#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define MAX_ARR_SIZE 100



int sec_low[MAX_ARR_SIZE];
int sec_high[MAX_ARR_SIZE];
int sec_arr[MAX_ARR_SIZE];
int index = 0;
int arrSize = 0;
bool flag = true;
int leftNum;
int rightNum;
int pivotPos;

int partition(int list[], int left, int right)
{
    int tmp;
    int pivot = list[right]; 	// �ǹ� ���� 
    int low = left;  	// right�� pivot
    int high = right - 1;
    int i = 0;

    while (low <= high) {

        // low�� high�� �������� �ʴ� �� �ݺ� 
             //pivot���� ū �� ã�� ������ low ����

        for (; low <= right && list[low] < pivot; low++);
        //pivot���� ���� �� ã�� ������ high ����
        for (; high >= left && list[high] > pivot; high--);
        if (low < high) {

            sec_high[index] = high;
            sec_low[index] = low;// low�� high�� �������� �ʾ�����
            index++;
            SWAP(list[low], list[high], tmp); 	// ���õ� �� ��� ��ȯ

            for (int i = 0; i < arrSize; i++)
                cout << list[i] << " ";
            cout << endl;
            //2��..?
        }
    }
    SWAP(list[low], list[right], tmp); // pivot�� high ��� ��ȯ 

    if (flag)
    {
        pivotPos = low;
        leftNum = low;
        rightNum = arrSize - low - 1;

        for (int i = 0; i < arrSize; i++)
            sec_arr[i] = list[i];

        flag = false;
    }

    return low;
}
// �� ���� : �迭�� left ~ right �׸���� ������������ �����ϴ� �Լ�
void quick_sort(int list[], int left, int right)
{
    int q; // pivot
    if (left < right) { //���� ����: left >= right
        q = partition(list, left, right); 	//q�� pivot
        quick_sort(list, left, q - 1);    	//���� ����Ʈ recursion
        quick_sort(list, q + 1, right);		//������ ����Ʈ recursion
    }
}


//����������
int partition_down(int list[], int left, int right)
{
    int tmp;
    int pivot = list[left]; 	// �ǹ� ���� 
    int low = left + 1;  	// left�� pivot
    int high = right;
    int i = 0;

    while (low <= high) {
        for (; low <= right && list[low] > pivot; low++);
        for (; high >= left && list[high] < pivot; high--);
        if (low < high) {		// low�� high�� �������� �ʾ�����
            SWAP(list[low], list[high], tmp); 	// ���õ� �� ��� ��ȯ

        }
    }
    SWAP(list[left], list[high], tmp); // pivot�� high ��� ��ȯ 

    return high;
}
//������������
void quick_sort_down(int list[], int left, int right)
{
    int q; // pivot
    if (left < right) { //���� ����: left >= right
        q = partition_down(list, left, right); 	//q�� pivot
        quick_sort_down(list, left, q - 1);    	//���� ����Ʈ recursion
        quick_sort_down(list, q + 1, right);		//������ ����Ʈ recursion
    }
}



int main() {
    //�Է�
    int size;
    cin >> size;
    int* list = new int[size];
    int* list6 = new int[size];
    for (int i = 0; i < size; i++) {
        cin >> list[i];
    }

    arrSize = size;

    memcpy(list6, list, sizeof(int) * size);
    //1��
    int num1 = list[size - 1];



    //5��
    quick_sort(list, 0, size - 1);


    //6��(quick sort ����)
    int p;
    cin >> p;
    for (int j = 0; j < p; j++) {
        int a, b;
        cin >> a >> b;
        quick_sort_down(list6, 0, a - 1);
        quick_sort(list6, 0, b - 1);
    }


    cout  << endl;


    //1�����
    cout << num1 << endl;



    //2��. 
    if (index < 2)
        cout << "low=high=-1" << endl;
    else
        cout << sec_low[1] << " " << sec_high[1] << endl;

    //3
    for (int i = 0; i < size; i++) {
        cout << sec_arr[i] << " ";
    }
    cout << endl;

    //4
    cout << pivotPos << " " << leftNum << " " << rightNum << endl;


    //5�����
    for (int i = 0; i < size; i++) {
        cout << list[i] << " ";
    }
    cout << endl;

    //6�����
    for (int j = 0; j < size; j++) {
        cout << list6[j] << " ";
    }
    cout << endl;

    return 0;
}