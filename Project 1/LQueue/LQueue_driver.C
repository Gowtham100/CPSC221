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
   cout << "Going to move element in 3rd position to the first:\n";
   q2.move_to_front(3);
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
 }
    system("PAUSE");
   return 0;

}

void activateRunway(Queue & queue, int currentTime, int & startTime, bool &runwayAvailable , int &length, string note){
  cout << '\t' <<  note << " from Queue " << queue.front() << endl;
  startTime = currentTime;
  runwayAvailable = false;

  //stats
  //length += currentTime - queue.frontTime();
}

void deactivateRunway(Queue & queue, string note, bool &runwayAvailable){
  queue.dequeue();
  cout << '\t' <<  note << " done " << queue.size() << " in Queue " << endl;
  runwayAvailable =  true;
}

void enqueue(Queue & queue, int & planeAdd, int currentTime, int & totalPlanes, int & maxSize){
  queue.enqueue(planeAdd++, currentTime);
  cout << queue.size() << " in Queue " << endl;

  if(queue.size() > maxSize){
    maxSize = queue.size();
  }

  totalPlanes++;


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
  int maxLSize = 0;
  int maxTSize = 0;

  int takeOffTime_start = -1 - takeOffTime;

  int landingTime_start = -1 - landingTime;

  int currentTime = 0;
  bool runwayAvailable = true;

  int totalTakeOffTime = 0;
  int totalLandTime = 0;

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
        enqueue(lQ, planeAdd, currentTime, totalPlanesLanding, maxLSize);
      }

      if (randTakeoff < takeOffRate){
        cout << '\t' << "Flight " << planeAdd << "Wants to take off || Adding to take off Q" ;
        enqueue(tQ, planeAdd, currentTime, totalPlanesTakeOff, maxTSize);
      }
    }
  }

    if(runwayAvailable){
      if(!tQ.empty() && lQ.empty()){
        runwayAvailable = false;
        activateRunway(tQ, currentTime, takeOffTime_start, runwayAvailable, totalTakeOffTime, "Taking off");
      }
      else if (!lQ.empty()){
        runwayAvailable = false;
        activateRunway(lQ, currentTime, landingTime_start, runwayAvailable, totalLandTime, "Landind");

      }
    }

    else{
      int nominalTakeOffTime = currentTime - takeOffTime_start;
      int nominalLandingTime = currentTime - landingTime_start;

      if (nominalTakeOffTime == takeOffTime && !tQ.empty()){
        runwayAvailable = false;
        deactivateRunway(tQ, "Take Off", runwayAvailable);
      }
      else if (nominalLandingTime == landingTime && !lQ.empty()){
        runwayAvailable = false;
        deactivateRunway(lQ, "Landing", runwayAvailable);
      }

    }

    if (currentTime > length){
      cout << "End sim" << endl;
      //break;
    }

    currentTime++;
  

}
