/*--- LQueue.cpp ----------------------------------------------------------
  This file implements LQueue member functions.
  From:  "ADTs, Data Structures, and Problem Solving with C++", 2nd edition
         by Larry Nyhoff
-------------------------------------------------------------------------*/
 
#include <iostream>
using namespace std;

#include "LQueue.h"

//--- Definition of Queue constructor
Queue::Queue()
: myFront(0), myBack(0)
{}

//--- Definition of Queue copy constructor
Queue::Queue(const Queue & original)
{
   myFront = myBack = 0;
   if (!original.empty())
   {
      // Copy first node
      myFront = myBack = new Queue::Node(original.front());

      // Set pointer to run through original's linked list
      Queue::NodePointer origPtr = original.myFront->next;
      while (origPtr != 0)
      {
         myBack->next = new Queue::Node(origPtr->data);
         myBack = myBack->next;
         origPtr = origPtr->next;
      }
   }
}

//--- Definition of Queue destructor
Queue::~Queue()
{ 
  // Set pointer to run through the queue
  Queue::NodePointer prev = myFront,
                     ptr;
  while (prev != 0)
    {
      ptr = prev->next;
      delete prev;
      prev = ptr;
    }
}

//--- Definition of assignment operator
const Queue & Queue::operator=(const Queue & rightHandSide)
{
   if (this != &rightHandSide)         // check that not q = q
   {
      this->~Queue();                  // destroy current linked list
      if (rightHandSide.empty())       // empty queue
         myFront = myBack = 0;
      else
      {                                // copy rightHandSide's list
         // Copy first node
         myFront = myBack = new Queue::Node(rightHandSide.front());

         // Set pointer to run through rightHandSide's linked list
         Queue::NodePointer rhsPtr = rightHandSide.myFront->next;
         while (rhsPtr != 0)
         {
           myBack->next = new Queue::Node(rhsPtr->data);
           myBack = myBack->next;
           rhsPtr = rhsPtr->next;
         }
      }
   }
   return *this;
}

//--- Definition of empty()
bool Queue::empty() const
{ 
   return (myFront == 0); 
}

//--- Definition of enqueue()
void Queue::enqueue(const QueueElement & value, const int & value1)
{
   Queue::NodePointer newptr = new Queue::Node(value,value1);
   if (empty())
      myFront = myBack = newptr;
   else
   {
      myBack->next = newptr;
      myBack = newptr;
   }
}

//--- Definition of display()
void Queue::display(ostream & out) const
{
   Queue::NodePointer ptr;
   for (ptr = myFront; ptr != 0; ptr = ptr->next)
     out << ptr->data << "  ";
   out << endl;
}

//--- Definition of front()
QueueElement Queue::front() const
{
   if (!empty())
      return (myFront->data);
   else
   {
	return 0;
   }
}

//--- Definition of dequeue()
void Queue::dequeue()
{
   if (!empty())
   {
      Queue::NodePointer ptr = myFront;
      myFront = myFront->next;
      delete ptr;
      if (myFront == 0)     // queue is now empty
         myBack = 0;
   }   
   else
      cerr << "*** Queue is empty -- can't remove a value ***\n";
}

//time it takes to move to the front of the Q
int Queue::time_at_start() const {
  return (myFront -> start);
}

void Queue::move_to_front(const QueueElement & value)
{
  Queue::NodePointer ptr;
  Queue::NodePointer prev_ptr = 0;

//if chosen node is already in front
  if (myFront->data == value){
    return;
  }

  if (empty()){
    cerr<<"Q is empty!\n";
  }

  for (ptr = myFront; ptr != 0 /*not the first element*/ ; ptr = ptr->next){
  if (ptr->data == value){
      if (ptr == myFront){
        return;
      }
    else{
      prev_ptr->next = ptr->next;
      ptr->next = myFront;
      myFront = ptr;
    
      ptr = NULL;
      ptr = prev_ptr;
      break;
    }
  }
    prev_ptr = ptr;
}

}

void Queue::merge_two_queues(Queue & q2) {
    // base case
    
    Queue q3;
    
    if (empty()) {
        while (!q2.empty()) {
            enqueue(q2.front(), q2.myFront->start);
            q2.dequeue();
        }
        return;
    }
    
    while (!(empty() || q2.empty())) {
        if (front() <= q2.front()) {
            q3.enqueue(front(), myFront->start);
            dequeue();
            q3.display(cout);
        }
        else {
            q3.enqueue(q2.front(), q2.myFront->start);
            q2.dequeue();
            q3.display(cout);
        }
    }
    
    while (!empty()) {
        q3.enqueue(front(), myFront->start);
        dequeue();
        q3.display(cout);
    }
    
    while (!q2.empty()) {
        q3.enqueue(q2.front(), q2.myFront->start);
        q2.dequeue();
        q3.display(cout);
    }
    
    *this = q3;
    return;
    // free q3??
}


int Queue::size(){
  int count = 0;
  Queue::NodePointer ptr;

  for (ptr = myFront; ptr != 0; ptr = ptr->next){
    count++;
  }

  return count;
}


