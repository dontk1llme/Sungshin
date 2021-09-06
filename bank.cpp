#include <iostream>
#include <time.h>
using namespace std;

struct Customer {
	int	id;		// 고객 아이디
	int	tArrival;		// 도착시간
	int	tService;	// 서비스 시간

	Customer(int i = 0, int tArr = 0, int tServ = 0)
		: id(i), tArrival(tArr), tService(tServ) { }
	~Customer() { }
};

inline void error(const char* str) { //const
	cout << str << endl;
	exit(1);
};

#define MAX_QUEUE_SIZE	100

class CustomerQueue	  // ArrayQueue와 유사, Customer 타입 데이터만 다름.
{
	int	front;
	int	rear;
	int w;

	int waits[MAX_QUEUE_SIZE];
	Customer data[MAX_QUEUE_SIZE];
public:
	CustomerQueue() { front = rear = w = 0; }	// 생성자, 초기화
	bool isEmpty() { return front == rear; }
	bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; }
	void enqueue(Customer& val) {
		if (isFull() == false) {
			rear = (rear + 1) % MAX_QUEUE_SIZE;
			data[rear] = val;
			waits[w++] = rear - front;
		}

	}
	Customer dequeue() {
		if (isEmpty()) error("공백 상태 에러");
		else {
			front = (front + 1) % MAX_QUEUE_SIZE;
			return data[front];
		}
	}
	int restWaitTime(int c) { //2번
		int rwt = 0;
		for (int i = front + 1; i <= rear; i++) {
			rwt += c - data[i].tArrival;
		}
		return rwt;
	}
	void display() {
		cout << " (큐: ";
		int dt = 0;
		for (int i = front + 1; i <= rear; i++) {
			dt = data[i].id;
			cout << dt;
		}
		cout << ")" << endl;
	}
	void copy(CustomerQueue q) { // 내용 복사
		front = q.front;
		rear = q.rear;
		for (int i = 0; i <= rear; i++) {
			data[i] = q.data[i];
			waits[i] = q.waits[i]; 
		}
	}
	int howmany() {
		int count = 0;
		int maxi = (front < rear) ? rear : rear + MAX_QUEUE_SIZE;
		for (int i = front + 1; i <= maxi; i++)
			count++;
		return count;
	}
	int getMaxOnlyWait(int c) { // 5번
		int gmow = 0;
		for (int i = front + 1; i <= rear; i++) {
			if (gmow < c - data[i].tArrival)
				gmow = c - data[i].tArrival;
		}
		return gmow;
	}
	int getWaitMax() {
		int gwm = 0;
		for (int i = 0; i <= rear; i++) {
			if (gwm < waits[i])
				gwm = waits[i];
		}
		return gwm;
	}
	int getService() {
		int gs = 0;
		for (int i = front + 1; i <= rear; i++) {
			gs += data[i].tService;
		}
		return gs;

	}

};

class BankSimulator
{
	int	nSimulation;          //입력: 시뮬레이션 시간 10분
	double	probArrival;           //입력: 단위 시간 고객 수 0.5
	int	tMaxService;          //입력: 고객 서비스 최대 시간 5분

	int	totalWaitTime;        //출력: 전체 대기 시간 7분
	int	nCustomers;          //출력: 고객 수 6명		
	int	nServedCustomers; //출력: 서비스 받은 고객 수 3명

	int num1;

	int allWaitTime;	// 출력: 모든 고객의 총 대기시간 (2)
	int totalServiceTime; // 출력: 서비스 시간의 총합 (3)
	int count; //고객이 3번인지 알기위한 count(4)
	int num4; // 출력: 3번 고객이 도착하였을 때 기다리는 고객수 (4)

	int waitTime[MAX_QUEUE_SIZE]; // 5번에 대기시간 저장하는 배열
	int num5; // 출력: 5번

	int plusTime;



	CustomerQueue  que, que2;

	// 랜덤값 반환 (0.0~<1.0)
	double Random() { return rand() / (double)RAND_MAX; }
	// 단위시간 고객 수 보다 큰지 체크
	bool IsNewCustomer() { return Random() > probArrival; }
	// 고객당 서비스 시간 최대 5분 * 랜덤값(0.0~<1.0)
	int RandServiceTime() { return (int)(tMaxService * Random()) + 1; }

	// 신규 Customer 데이터 만들어서 큐에 삽입
	void InsertCustomer(int arrivalTime) {
		// Customer 데이터 : id, arrivalTime, ServiceTime)
		Customer a(++nCustomers, arrivalTime, RandServiceTime());
		// arrivalTime 주어지고, serviceTime 최대 5분 내에서 랜덤값
		cout << "  고객:" << a.id << " 서비스 시간:" << a.tService << "분" << endl;
		que.enqueue(a);
	}
	int getMaxWait() {
		int m = 0;
		for (int i = 1; i <= nCustomers; i++) {  //조심
			if (m < waitTime[i]) m = waitTime[i];
		}
		return m;
	}

public:
	BankSimulator() :nCustomers(0), totalWaitTime(0), nServedCustomers(0),
		allWaitTime(0), totalServiceTime(0), count(0), num4(0), num1(0)
	{   }

	void readSimulationParameters() { //사용자 입력 처리
		cout << "시뮬레이션 할 최대 시간 (예:10) = ";
		cin >> nSimulation;
		cout << "단위시간에 도착하는 고객 수 (예:0.5) = ";
		cin >> probArrival;
		cout << "한 고객에 대한 최대 서비스 시간 (예:5) = ";
		cin >> tMaxService;
		cout << "=============================";
		cout << endl;
	}

	void run() {
		int clock = 0;	         // 시뮬레이션 시간 체크 
		int serviceTime = -1;  // 서비스 받는 동안 시간 체크

		while (clock < nSimulation) {
			// 시뮬레이션 시간 10분 지났는지 체크 위해
			clock++;
			// 루프 돌면서 1부터 10까지 출력
			cout << "현재시각=" << clock << endl;

			// 새 고객 큐 삽입, clock=arrivalTime:고객 도착시간
			if (IsNewCustomer()) {
				InsertCustomer(clock);
				if (que.getWaitMax() >= que2.getWaitMax()) // 1번
					que2.copy(que); // 1번
				count++;				// 4번.
				if (count == 3) num4 = que.howmany();
			}

			// 고객 서비스 중이면 대기
			if (serviceTime > 0) {
				serviceTime--;
				totalServiceTime++; //(3)
			}
			else {										// 큐가 비어있으면 pass
				if (que.isEmpty()) continue;
				// 큐에서 고객 a를 꺼내서
				Customer a = que.dequeue();
				totalServiceTime++;
				// 서비스 받은 고객 수 증가
				nServedCustomers++;	//(3)
				// totalWaitTime에 고객 a의 대기시간 합산
				totalWaitTime += clock - a.tArrival;
				waitTime[a.id] = clock - a.tArrival;
				cout << "  고객 " << a.id << " 서비스 시작 (대기시간:   " << (clock - a.tArrival) << "분" << endl;
				// 현재 clock도 서비스 시간, 서비스 시간에서 1 빼기
				serviceTime = a.tService - 1;
			}
			allWaitTime = totalWaitTime + que.restWaitTime(clock);
			num5 = (getMaxWait() > que.getMaxOnlyWait(clock)) ? getMaxWait() : que.getMaxOnlyWait(clock);
			num1 = que.getWaitMax();
			plusTime = serviceTime + que.getService();
		}
	}
	void printStat() {  // 통계 출력
		printf("=============================\n");
		printf("서비스 받은 고객수 = %d\n", nServedCustomers);
		printf("전체 대기 시간= %d분\n", totalWaitTime);
		printf("서비스고객 평균대기시간 = %-5.2f분\n",
			(double)totalWaitTime / nServedCustomers);
		printf("현재 대기 고객 수= %d\n",
			nCustomers - nServedCustomers);
		cout << "은행 대기열 대기 고객 최대값 = " << num1; que2.display();
		cout << "모든 고객의 총 대기시간 = " << allWaitTime << endl;
		cout << "서비스 시간의 총합 = " << totalServiceTime << endl;
		cout << "3번 고객이 도착하였을 때 기다리는 고객 수 =" << num4 << endl;
		cout << "가장 오래 기다린 고객의 대기시간 = " << num5 << endl;
		cout << "대기 고객을 위한 추가 시간 = " << plusTime << endl;

	}
};

void main()
{
	srand((unsigned int)time(NULL));
	BankSimulator	sim;
	sim.readSimulationParameters(); // 사용자 입력
	sim.run();	 // 시뮬레이션
	sim.printStat();	 // 결과 출력
}
