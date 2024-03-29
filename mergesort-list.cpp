#include <iostream>
using namespace std;
 
// Node structure
struct Node {
    int data;
    Node* next;
};
 
// function to insert in list
void insert(int x, Node** head)
{
    if (*head == NULL) {
        *head = new Node;
        (*head)->data = x;
        (*head)->next = NULL;
        return;
    }
    Node* temp = new Node;
    temp->data = (*head)->data;
    temp->next = (*head)->next;
    (*head)->data = x;
    (*head)->next = temp;
}
 
// function to print the list
void print(Node* head)
{
    Node* temp = head;
    while (temp != NULL) {

        cout << temp->data;
        
        if (temp->next) {
            cout << " -> "; 
        }

        temp = temp->next;
    }
    cout << endl;
}
 
Node* merge(Node* firstNode, Node* secondNode)
{
    Node* merged = new Node;
    Node* temp = new Node;
 
    // merged is equal to temp so in the end we have the top
    // Node.
    merged = temp;
 
    // while either firstNode or secondNode becomes NULL
    while (firstNode != NULL && secondNode != NULL) {
 
        if (firstNode->data <= secondNode->data) {
            temp->next = firstNode;
            firstNode = firstNode->next;
        }
 
        else {
            temp->next = secondNode;
            secondNode = secondNode->next;
        }
        temp = temp->next;
    }
 
    // any remaining Node in firstNode or secondNode gets
    // inserted in the temp List
    while (firstNode != NULL) {
        temp->next = firstNode;
        firstNode = firstNode->next;
        temp = temp->next;
    }
 
    while (secondNode != NULL) {
        temp->next = secondNode;
        secondNode = secondNode->next;
        temp = temp->next;
    }
    // return the head of the sorted list
    return merged->next;
}
 
// function to calculate the middle Element
Node* middle(Node* head)
{
    Node* slow = head;
    Node* fast = head->next;
 
    while (!slow->next && (!fast && !fast->next)) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
 
// function to sort the given list
Node* sort(Node* head)
{
  if(head == NULL){
    return NULL ;
  }
 
    if (head->next == NULL) {
        return head;
    }
 
    Node* mid = new Node;
    Node* head2 = new Node;
    mid = middle(head);
    head2 = mid->next;
    mid->next = NULL;

    Node* finalhead = merge(sort(head), sort(head2));
    return finalhead;
}

int main() {
    Node* head = NULL;
    int n[] = { 2,1,4,3,6,5,8,7 };
    for (int i = 0; i < 8; i++) {
        insert(n[i], &head); // inserting in the list
    }
    cout << "Sorted Linked List is: \n";
    print(sort(head)); // printing the sorted list returned
                       // by sort()
    return 0;
}
 
