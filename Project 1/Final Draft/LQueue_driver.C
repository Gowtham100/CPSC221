/*---------------------------------------------------------------------
                  Driver program to test the Queue class.
  ----------------------------------------------------------------------*/

#include <iostream>
#include "LQueue.h"
#include <array>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

void enqueue(Queue & queue, int & planeAdd, int currentTime, int & totalPlanes, int & maxSize);
void activateRunway(Queue & queue, int currentTime, int & startTime, bool & runwayAvailable , int & length, string note);
void deactivateRunway(Queue & queue, string note, bool & runwayAvailable);

void mainSim();
double avg ( int numerator, int denominator);

void print(Queue q)
{ q.display(cout); }

int main(void)
{
  int input = false;

  cout << "Press 1 to run simulation, 0 for Part A" << endl;
  cin >> input;

  if (input){
    mainSim();
  } else 
  {
   Queue q1;
   cout << "Queue created.  Empty? " << boolalpha << q1.empty() << endl;

   cout << "How many elements to add to the queue? ";
   int numItems;
   cin >> numItems;
   for (int i = 1; i <= numItems; i++) 
      q1.enqueue(100*i,0);

   cout << "Contents of queue q1 (via  print):\n";
   print(q1); 
   cout << endl;
   Queue q2;
   q2 = q1;
   cout << "Contents of queue q2 after q2 = q1 (via  print):\n";
   print(q2); 
   cout << endl;

   cout << "Queue q2 empty? " << q2.empty() << endl;

   cout << "Front value in q2: " << q2.front() << endl;

   while (!q2.empty())
   {
     cout << "Remove front -- Queue contents: ";
     q2.dequeue();
     q2.display(cout);
   }
   cout << "Queue q2 empty? " << q2.empty() << endl;
   cout << "Front value in q2?" << endl << q2.front() << endl;
   cout << "Trying to remove front of q2: " << endl;
   q2.dequeue();

   //---------------TESTS FOR MOVETOFRONT-------------//
   cout << "TESTS: move_to_front" << endl;
   Queue q3;
   q3.enqueue(200,0);
   q3.enqueue(5,0);
   q3.enqueue(50,0);
   q3.enqueue(150,0);
   q3.enqueue(300,0);

   cout << "Q3 b4 test: " << endl;
   print(q3);

   q3.move_to_front(50);

   cout << "Q3 after moving value 50: " << endl;
   print(q3);

   system("PAUSE");
   return 0;

 }

  

   // system("PAUSE");
   //return 0;

}

void activateRunway(Queue & queue, int currentTime, int & startTime, bool &runwayAvailable , int &length, string note){
  cout << '\t' <<  note << " of flight " << queue.front() << endl;
  startTime = currentTime;
  runwayAvailable = false;

  //stats
  length += currentTime - queue.time_at_start(); // length = length + (currenttime - time it take to move to the front )
}

void deactivateRunway(Queue & queue, string note, bool &runwayAvailable){
  queue.dequeue();
  cout << '\t' <<  note << " complete " << queue.size() << " plane(s) in flight " << endl;
  runwayAvailable =  true;
}

void enqueue(Queue & queue, int & planeAdd, int currentTime, int & totalPlanes, int & maxSize){
  queue.enqueue(planeAdd++, currentTime);
  cout << queue.size() << " in Queue " << endl;

  if(queue.size() > maxSize){
    maxSize = queue.size();
  }

  totalPlanes+=1;


}

double avg(int num, int din){
  if (din == 0){
    return 0;
  }

  return ((double)num)/din;
}

void mainSim(){
  int landingTime;
  int takeOffTime;

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
  cin  >> landRate;

  //takeOffRate
  cout << "Take Off rate (p/h): " ;
  cin  >> takeOffRate;


  //length of simulation
  cout << "Active time for airport? (min) : " ;
  cin  >> length;

  Queue lQ; //landing q
  Queue tQ; //takeoff q
//------------------------------------//
  int planeAdd = 1000;
  int maxLQSize = 0;
  int maxTQSize = 0;

  int takeOffTime_start = -1 - takeOffTime;

  int landingTime_start = -1 - landingTime;

  int currentTime = 0;
  bool runwayAvailable = true;

  int totalTakeOffTime = 0;
  int totalLandTime = 0;
  int totalPlanesLanding = 0;
  int totalPlanesTakeOff = 0;

  while (true){
    cout << "Time now : " << currentTime << endl;

    if (currentTime == length){
      cout << '\t' << "Simulation will end" << endl;
    }

    //random generation

 
    

    if (currentTime < length) {
      int randLand = rand() % 60;
      int randTakeoff = rand() % 60;
      //int flightStatus = rand() % 60;

      if (randLand < landRate) {
        cout << '\t' << "Flight " << planeAdd << " Wants to land || Adding to landing Q || " ;
        enqueue(lQ, planeAdd, currentTime, totalPlanesLanding, maxLQSize);
      }

      if (randTakeoff < takeOffRate){
        cout << '\t' << "Flight " << planeAdd << "  Wants to take off || Adding to take off Q || "  ;
        enqueue(tQ, planeAdd, currentTime, totalPlanesTakeOff, maxTQSize);
      }
    }

  

    if(runwayAvailable){
      if(!tQ.empty() && lQ.empty()){
        runwayAvailable = false;
        activateRunway(tQ, currentTime, takeOffTime_start, runwayAvailable, totalTakeOffTime, "Taking off");
      }
      //sinze landing iis first priority
      else if (!lQ.empty()){
        runwayAvailable = false;
        activateRunway(lQ, currentTime, landingTime_start, runwayAvailable, totalLandTime, "Landind");

      }
    }

    else{
      int nominalTakeOffTime = currentTime - takeOffTime_start;  // - (-1 - 3) = 6
      int nominalLandingTime = currentTime - landingTime_start;

      if (nominalTakeOffTime == takeOffTime && !tQ.empty()){    //6 == 3
        runwayAvailable = false;
        deactivateRunway(tQ, "Take Off", runwayAvailable);
      }
      else if (nominalLandingTime == landingTime && !lQ.empty()){
        runwayAvailable = false;
        deactivateRunway(lQ, "Landing", runwayAvailable);
      }

    }

    if (currentTime > length){
      cout << "End of program" << endl;
      break;
    }

    currentTime+=1;
  }
  cout << "STATISTICS" << endl;
  cout << "Maximum number of planes in landing queue was: " << maxLQSize << endl;
  //cout << "TOTAL LAND TIME: "<< totalLandTime << endl;
  //cout << "TOTAL TAKE OFF TIME: "<< totalTakeOffTime << endl;
  cout << "Average minutes spent waiting to land: " << avg(totalLandTime, totalPlanesLanding) << endl;
  cout << "Maximum number of planes in takeoff queue was: " << maxTQSize << endl;
  cout << "Average minutes spent waiting to takeoff: " << avg(totalTakeOffTime, totalPlanesTakeOff) << endl;

  system("PAUSE");

}



