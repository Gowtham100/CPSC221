// linked_list.cc -- functions for linked_list lab (cs221) 

#include "linked_list.h"

/**
 * Inserts a new Node (with key=newKey) at the head of the linked_list.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 * PRE: newKey is the value for the key in the new Node 
 * POST: the new Node is now the head of the linked_list
 */ 
void insert(Node*& head, int newKey) {
  Node * curr = new Node;
  curr->key  = newKey;
  curr->next = head;

  head = curr;
}

/**
 * Print the keys of a linked_list in order, from head to tail 
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 */ 
void print(Node* head) {
  std::cout << "[";
  for (Node* curr = head; curr != NULL; curr = curr->next){ 
    std::cout << curr->key;
    if (curr->next != NULL) std::cout << ", ";
  }
  std::cout << "]" << std::endl;
}

/** 
 * Returns the size (number of Nodes) of the linked_list  
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 */ 
int size(Node* head){ 
  if (! head) return 0; 
  return 1 + size(head->next); 
}

/**
 * Copies the keys in a linked list to a vector.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 * POST: a new vector<int> containing the keys in the correct order has been returned.  
 */ 
std::vector<int> to_vector(Node* head) {
  std::vector<int> result;
  for (Node* curr = head; curr != NULL; curr = curr->next){ 
    result.push_back(curr->key); 
  }
  return result; 
}

/** 
 * Delete the last Node in the linked_list
 * PRE: head is the first Node in a linked_list (if NULL, linked_list is empty) 
 * POST: the last Node of the linked_list has been removed
 * POST: if the linked_list is now empty, head has been changed
 * POST: else head remains the first Node in the linked_list
 */
void delete_last_element(Node*& head){
 // ******** WRITE YOUR CODE HERE ********
  if(head == NULL){
    return;
  }
  else if(head->next == NULL){
    delete head;
    head = NULL;
  }
  else{
  Node* curr = head;
  Node* tail = head->next;
  while(tail->next != NULL){
    curr = tail;
    tail = tail->next;
  }
  delete tail;
  curr->next = NULL;
}
}

/**
 * Removes an existing Node (with key=oldKey) from the linked_list. 
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 * PRE: oldKey is the value of the key in the Node to be removed 
 * PRE: if no Node with key=oldKey exists, the linked_list has not changed 
 * POST: if a Node with key=oldKey was found, then it was deleted
 * POST: other Nodes with key=oldKey might still be in the linked_list
 * POST: head is the new first Node of the linked_list, if updated
 */ 
void remove(Node*& head, int oldKey) {
  // ******** WRITE YOUR CODE HERE ********
  int headkey = head->key;
  if(head == NULL){
  return;
  }
  if(headkey == oldKey){
  Node* newhead = head->next;
  delete head;
  head = newhead;
  } 
  else{
  Node* temp = head;
  int tempkey = temp->key;
  Node* before = NULL;
  Node* after = NULL;
  while(temp->next != NULL && !(tempkey == oldKey)){
  before = temp;
  temp = temp->next;
  tempkey = temp->key;
  }
  if(temp != NULL && (tempkey == oldKey)){   //   Added & statement.
  after = temp->next;
  delete temp;
  before->next = after;
  }
  }

}

/**
 * Insert a new Node (with key=newKey) after an existing Node (with key=oldKey)
 * If there is no existing Node with key=oldKey, then no action.
 * PRE: head is the first Node in a linked_list (if NULL, linked_list is empty) 
 * PRE: oldKey is the value to look for (in the key of an existing Node)  
 * PRE: newKey is the value of the key in the new Node (that might be inserted) 
 * POST: if no Node with key=oldKey was found, then the linked_list has not changed
 * POST: else a new Node (with key=newKey) is right after the Node with key = oldKey.
 */
void insert_after(Node* head, int oldKey, int newKey){
  // ******** WRITE YOUR CODE HERE ********
  if(head == NULL){
  return;
  }
  else{
  Node* curr = head;
  int currkey = curr->key;
  Node* after = NULL;
  Node* newnode = new Node;
  
  while(curr->next != NULL && !(currkey == oldKey)){
  curr = curr->next;
  currkey = curr->key;
  }
  if(curr != NULL && (currkey == oldKey)){
  after = curr->next;
  newnode->next = after;
  curr->next = newnode;
  newnode->key = newKey;
  }
  else{return;}
  }

}

/** 
 * Create a new linked_list by merging two existing linked_lists. 
 * PRE: list1 is the first Node in a linked_list (if NULL, then it is empty)
 * PRE: list2 is the first Node in another linked_list (if NULL, then it is empty)
 * POST: A new linked_list is returned that contains new Nodes with the keys from 
 * the Nodes in list1 and list2, starting with the key of the first Node of list1, 
 * then the key of the first Node of list2, etc. 
 * When one list is exhausted, the remaining keys come from the other list.
 * For example: [1, 2] and [3, 4, 5] would return [1, 3, 2, 4, 5]
 */
Node* interleave(Node* list1, Node* list2){
// ******** WRITE YOUR CODE HERE ********
  if(list1 == NULL){return list2;}
  if(list2 == NULL){return list1;}
  //if lists are equal, copy one twice (i.e. 1,2,3 == 1,1,2,2,3,3)??
  /*else{
    Node* temp1 = list1;
    Node* temp2 = list1;
    list1 = list1->next;
    while(list1 != NULL && list2 != NULL){
    temp2->next = list2;
    list2 = list2->next;
    temp2 = temp2->next;
    temp2->next = list1;
    list1 = list1->next;
    temp2 = temp2->next;
    }*/
    Node * merge = new Node;
    if (list1 != NULL){
      merge->key = list1->key;
      if (list2 != NULL){
        //natural recursion
      merge->next = interleave(list2, list1->next);
    }else{
      merge->next = list1->next;
    }
    }
    else{
      merge = list2;
    }
    return merge;


}
