#include <iostream>
#include <time.h>
using namespace std;

struct Customer {
	int	id;		// �� ���̵�
	int	tArrival;		// �����ð�
	int	tService;	// ���� �ð�

	Customer(int i = 0, int tArr = 0, int tServ = 0)
		: id(i), tArrival(tArr), tService(tServ) { }
	~Customer() { }
};

inline void error(const char* str) { //const
	cout << str << endl;
	exit(1);
};

#define MAX_QUEUE_SIZE	100

class CustomerQueue	  // ArrayQueue�� ����, Customer Ÿ�� �����͸� �ٸ�.
{
	int	front;
	int	rear;
	int w;

	int waits[MAX_QUEUE_SIZE];
	Customer data[MAX_QUEUE_SIZE];
public:
	CustomerQueue() { front = rear = w = 0; }	// ������, �ʱ�ȭ
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
		if (isEmpty()) error("���� ���� ����");
		else {
			front = (front + 1) % MAX_QUEUE_SIZE;
			return data[front];
		}
	}
	int restWaitTime(int c) { //2��
		int rwt = 0;
		for (int i = front + 1; i <= rear; i++) {
			rwt += c - data[i].tArrival;
		}
		return rwt;
	}
	void display() {
		cout << " (ť: ";
		int dt = 0;
		for (int i = front + 1; i <= rear; i++) {
			dt = data[i].id;
			cout << dt;
		}
		cout << ")" << endl;
	}
	void copy(CustomerQueue q) { // ���� ����
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
	int getMaxOnlyWait(int c) { // 5��
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
	int	nSimulation;          //�Է�: �ùķ��̼� �ð� 10��
	double	probArrival;           //�Է�: ���� �ð� �� �� 0.5
	int	tMaxService;          //�Է�: �� ���� �ִ� �ð� 5��

	int	totalWaitTime;        //���: ��ü ��� �ð� 7��
	int	nCustomers;          //���: �� �� 6��		
	int	nServedCustomers; //���: ���� ���� �� �� 3��

	int num1;

	int allWaitTime;	// ���: ��� ���� �� ���ð� (2)
	int totalServiceTime; // ���: ���� �ð��� ���� (3)
	int count; //���� 3������ �˱����� count(4)
	int num4; // ���: 3�� ���� �����Ͽ��� �� ��ٸ��� ���� (4)

	int waitTime[MAX_QUEUE_SIZE]; // 5���� ���ð� �����ϴ� �迭
	int num5; // ���: 5��

	int plusTime;



	CustomerQueue  que, que2;

	// ������ ��ȯ (0.0~<1.0)
	double Random() { return rand() / (double)RAND_MAX; }
	// �����ð� �� �� ���� ū�� üũ
	bool IsNewCustomer() { return Random() > probArrival; }
	// ���� ���� �ð� �ִ� 5�� * ������(0.0~<1.0)
	int RandServiceTime() { return (int)(tMaxService * Random()) + 1; }

	// �ű� Customer ������ ���� ť�� ����
	void InsertCustomer(int arrivalTime) {
		// Customer ������ : id, arrivalTime, ServiceTime)
		Customer a(++nCustomers, arrivalTime, RandServiceTime());
		// arrivalTime �־�����, serviceTime �ִ� 5�� ������ ������
		cout << "  ��:" << a.id << " ���� �ð�:" << a.tService << "��" << endl;
		que.enqueue(a);
	}
	int getMaxWait() {
		int m = 0;
		for (int i = 1; i <= nCustomers; i++) {  //����
			if (m < waitTime[i]) m = waitTime[i];
		}
		return m;
	}

public:
	BankSimulator() :nCustomers(0), totalWaitTime(0), nServedCustomers(0),
		allWaitTime(0), totalServiceTime(0), count(0), num4(0), num1(0)
	{   }

	void readSimulationParameters() { //����� �Է� ó��
		cout << "�ùķ��̼� �� �ִ� �ð� (��:10) = ";
		cin >> nSimulation;
		cout << "�����ð��� �����ϴ� �� �� (��:0.5) = ";
		cin >> probArrival;
		cout << "�� ���� ���� �ִ� ���� �ð� (��:5) = ";
		cin >> tMaxService;
		cout << "=============================";
		cout << endl;
	}

	void run() {
		int clock = 0;	         // �ùķ��̼� �ð� üũ 
		int serviceTime = -1;  // ���� �޴� ���� �ð� üũ

		while (clock < nSimulation) {
			// �ùķ��̼� �ð� 10�� �������� üũ ����
			clock++;
			// ���� ���鼭 1���� 10���� ���
			cout << "����ð�=" << clock << endl;

			// �� �� ť ����, clock=arrivalTime:�� �����ð�
			if (IsNewCustomer()) {
				InsertCustomer(clock);
				if (que.getWaitMax() >= que2.getWaitMax()) // 1��
					que2.copy(que); // 1��
				count++;				// 4��.
				if (count == 3) num4 = que.howmany();
			}

			// �� ���� ���̸� ���
			if (serviceTime > 0) {
				serviceTime--;
				totalServiceTime++; //(3)
			}
			else {										// ť�� ��������� pass
				if (que.isEmpty()) continue;
				// ť���� �� a�� ������
				Customer a = que.dequeue();
				totalServiceTime++;
				// ���� ���� �� �� ����
				nServedCustomers++;	//(3)
				// totalWaitTime�� �� a�� ���ð� �ջ�
				totalWaitTime += clock - a.tArrival;
				waitTime[a.id] = clock - a.tArrival;
				cout << "  �� " << a.id << " ���� ���� (���ð�:   " << (clock - a.tArrival) << "��" << endl;
				// ���� clock�� ���� �ð�, ���� �ð����� 1 ����
				serviceTime = a.tService - 1;
			}
			allWaitTime = totalWaitTime + que.restWaitTime(clock);
			num5 = (getMaxWait() > que.getMaxOnlyWait(clock)) ? getMaxWait() : que.getMaxOnlyWait(clock);
			num1 = que.getWaitMax();
			plusTime = serviceTime + que.getService();
		}
	}
	void printStat() {  // ��� ���
		printf("=============================\n");
		printf("���� ���� ���� = %d\n", nServedCustomers);
		printf("��ü ��� �ð�= %d��\n", totalWaitTime);
		printf("���񽺰� ��մ��ð� = %-5.2f��\n",
			(double)totalWaitTime / nServedCustomers);
		printf("���� ��� �� ��= %d\n",
			nCustomers - nServedCustomers);
		cout << "���� ��⿭ ��� �� �ִ밪 = " << num1; que2.display();
		cout << "��� ���� �� ���ð� = " << allWaitTime << endl;
		cout << "���� �ð��� ���� = " << totalServiceTime << endl;
		cout << "3�� ���� �����Ͽ��� �� ��ٸ��� �� �� =" << num4 << endl;
		cout << "���� ���� ��ٸ� ���� ���ð� = " << num5 << endl;
		cout << "��� ���� ���� �߰� �ð� = " << plusTime << endl;

	}
};

void main()
{
	srand((unsigned int)time(NULL));
	BankSimulator	sim;
	sim.readSimulationParameters(); // ����� �Է�
	sim.run();	 // �ùķ��̼�
	sim.printStat();	 // ��� ���
}
