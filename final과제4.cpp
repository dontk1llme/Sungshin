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
    int pivot = list[right]; 	// 피벗 설정 
    int low = left;  	// right는 pivot
    int high = right - 1;
    int i = 0;

    while (low <= high) {

        // low와 high가 역전되지 않는 한 반복 
             //pivot보다 큰 값 찾을 때까지 low 증가

        for (; low <= right && list[low] < pivot; low++);
        //pivot보다 작은 값 찾을 때까지 high 감소
        for (; high >= left && list[high] > pivot; high--);
        if (low < high) {

            sec_high[index] = high;
            sec_low[index] = low;// low와 high가 역전되지 않았으면
            index++;
            SWAP(list[low], list[high], tmp); 	// 선택된 두 요소 교환

            for (int i = 0; i < arrSize; i++)
                cout << list[i] << " ";
            cout << endl;
            //2번..?
        }
    }
    SWAP(list[low], list[right], tmp); // pivot과 high 요소 교환 

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
// 퀵 정렬 : 배열의 left ~ right 항목들을 오름차순으로 정렬하는 함수
void quick_sort(int list[], int left, int right)
{
    int q; // pivot
    if (left < right) { //종결 조건: left >= right
        q = partition(list, left, right); 	//q는 pivot
        quick_sort(list, left, q - 1);    	//왼쪽 리스트 recursion
        quick_sort(list, q + 1, right);		//오른쪽 리스트 recursion
    }
}


//내림차순용
int partition_down(int list[], int left, int right)
{
    int tmp;
    int pivot = list[left]; 	// 피벗 설정 
    int low = left + 1;  	// left는 pivot
    int high = right;
    int i = 0;

    while (low <= high) {
        for (; low <= right && list[low] > pivot; low++);
        for (; high >= left && list[high] < pivot; high--);
        if (low < high) {		// low와 high가 역전되지 않았으면
            SWAP(list[low], list[high], tmp); 	// 선택된 두 요소 교환

        }
    }
    SWAP(list[left], list[high], tmp); // pivot과 high 요소 교환 

    return high;
}
//내림차순으로
void quick_sort_down(int list[], int left, int right)
{
    int q; // pivot
    if (left < right) { //종결 조건: left >= right
        q = partition_down(list, left, right); 	//q는 pivot
        quick_sort_down(list, left, q - 1);    	//왼쪽 리스트 recursion
        quick_sort_down(list, q + 1, right);		//오른쪽 리스트 recursion
    }
}



int main() {
    //입력
    int size;
    cin >> size;
    int* list = new int[size];
    int* list6 = new int[size];
    for (int i = 0; i < size; i++) {
        cin >> list[i];
    }

    arrSize = size;

    memcpy(list6, list, sizeof(int) * size);
    //1번
    int num1 = list[size - 1];



    //5번
    quick_sort(list, 0, size - 1);


    //6번(quick sort 응용)
    int p;
    cin >> p;
    for (int j = 0; j < p; j++) {
        int a, b;
        cin >> a >> b;
        quick_sort_down(list6, 0, a - 1);
        quick_sort(list6, 0, b - 1);
    }


    cout  << endl;


    //1번출력
    cout << num1 << endl;



    //2번. 
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


    //5번출력
    for (int i = 0; i < size; i++) {
        cout << list[i] << " ";
    }
    cout << endl;

    //6번출력
    for (int j = 0; j < size; j++) {
        cout << list6[j] << " ";
    }
    cout << endl;

    return 0;
}