// 9-7 stopwatch
#include <iostream>
#include <ctime>
using namespace std;

class StopWatch {
private:
	int startTime;
	int endTime;

public:
	StopWatch() {
		startTime = time(NULL);
	}

	void start() {
		startTime = time(NULL);
	}
	void stop() {
		endTime = time(NULL);
	}
	double getElapsedTime() {
		//Æ÷±â
	}

	
};

//https://doitnow-man.tistory.com/231