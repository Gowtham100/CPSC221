#include <iostream>
#include "LQueue.h"
#include <array>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

void enqueue(Queue & queue, int & planeAdd, int currentTime, int & totalPlanes, int & maxSize);
void startRunway(Queue & queue, int currentTime, int & startTime, bool &ruwayAvailable , int &length, string note);

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

	Queue lQ; //landing q
	Queue tQ; //takeoff q
//------------------------------------//
	int planeAdd = 1000;
	int maxLSize = 0;
	int maxTSize = 0;

	int takeOffTime_start_A = -1 - takeOffTime;
	int takeOffTime_start_B = -1 - takeOffTime;

	int landingTime_start_A = -1 - landingTime;
	int landingTime_start_B = -1 - landingTime;

	int currentTime = 0;
	bool runwayAvailable = true;
	//bool runwayAvailable_B = true;

	while (true){
		cout << "Time now : " << currentTime << endl;

		if (currentTime == length){
			cout << '\t' << "Simulation will end" << endl;
		}

		//random generation

		int totalPlanesLanding = 0;
		int totalPlanesTakeOff = 0;

		if (currentTime < length) {
			int randLand = rand() % 60;
			int randTakeoff = rand() % 60;

			if (randLand < landRate) {
				cout << '\t' << "Flight " << planeAdd << "Wants to land || Adding to landing Q" ;
				enqueue(lQ, planeAdd, currentTime, totalPlanesLanding. maxLSize);
			}

			if (randTakeoff < takeOffRate){
				cout << '\t' << "Flight " << planeAdd << "Wants to take off || Adding to take off Q" ;
				enqueue(tQ, planeAdd, currentTime, totalPlanesTakeOff, maxTSize);
			}
		}

		if(ruwayAvailable){
			if(!tQ.empty() && lQ.empty){
				
			}
		}



	}

}

