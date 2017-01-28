#include <iostream>
#include "LQueue.h"
#include <array>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

void print(Queue q){
	q.display(cout);
}

int main(void){
	mainSim();
}

void mainSim(){
	int landingTime;
	int takeOffIime;

	int landRate;
	int takeOffRate;

	int length;

	//landingTime
	cout << "Landing time (min): " ;
	cin  >> landingTime;

	//takeOffTime
	cout << "Take Off time (min): " ;
	cin  >> takeOffTime;

	//landRate
	cout << "Lading rate (p/h): " ;
	cin  << landRate;

	//takeOffRate
	cout << "Take Off rate (p/h): " ;
	cin  << takeOffRate;

	//length of simulation
	cout << "Active time for airport? (min) : " ;
	cin  << length;

	Queue lQ_A, lQ_B;
	Queue tQ_A, tQ_B;


}

