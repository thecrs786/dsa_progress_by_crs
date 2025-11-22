/*
    Circular Singly Linked List (CSLL) in C++:

    - Unlike a normal singly linked list, the last node's next pointer points back to the head, forming a circle.
    - There is no NULL in a proper circular linked list.
    - Benefits:
        1. Infinite traversal starting from any node.
        2. Useful for round-robin scheduling, buffering, or cyclic data processing.
    - Special care is needed for single-node lists and empty lists.
    - Two approaches:
        a) Maintain both head and tail pointers (simplifies operations)
        b) Only maintain tail pointer (head can be deduced as tail->next)
*/

#include<iostream>
using namespace std;

// Node structure for CSLL
class Node{
public:
    int val;        // Data stored in the node
    Node* next;     // Pointer to the next node

    Node(int data){
        val = data;     // Store the value
        next = NULL;    // Initialize next pointer
    }
};

// Circular singly linked list class
class List{
public:
    Node* tail;     // Points to the last node
    Node* head;     // Points to the first node (optional but convenient)
    int size;       // Number of nodes in the list

    // Constructor: initialize empty list
    List(){
        head = tail = NULL;
        size = 0;
    }

    // ---------------------------
    // 1. PUSH FRONT
    // ---------------------------
    void push_front(int val){
        Node* newNode = new Node(val);  // Create new node

        if(head==NULL){                 // List is empty
            newNode->next = newNode;    // Circular link: node points to itself
            head = tail = newNode;      // Single node: head and tail are same
            size++;
            return;
        }

        newNode->next = head;           // New node points to old head
        tail->next = newNode;           // Old tail points to new head to maintain circularity
        head = newNode;                 // Update head to new node

        size++;
    }

    // Push front without using head pointer (for reference)
    /*
    void push_front(int val){
        Node* newNode = new Node(val);

        if(tail==NULL){
            newNode->next = newNode; // Circular link
            tail = newNode;
            size++;
            return;
        }

        newNode->next = tail->next;  // tail->next is current head
        tail->next = newNode;

        size++;
    }
    */

    // ---------------------------
    // 2. PUSH BACK
    // ---------------------------
    void push_back(int val){
        Node* newNode = new Node(val); // Create new node

        if(head==NULL){               // Empty list
            newNode->next = newNode;  // Circular link for single-node list
            head = tail = newNode;
            size++;
            return;
        }

        newNode->next = head;   // New node points to head to maintain circularity
        tail->next = newNode;   // Old tail points to new node
        tail = newNode;         // Update tail

        size++;
    }

    // Push back without using head pointer
    /*
    void push_back(int val){
        Node* newNode = new Node(val);

        if(tail==NULL){
            newNode->next = newNode; // Circular link
            tail = newNode;
            size++;
            return;
        }

        newNode->next = tail->next; // tail->next is head
        tail->next = newNode;
        tail = newNode;

        size++;
    }
    */

    // ---------------------------
    // 3. POP FRONT
    // ---------------------------
    void pop_front(){
        if(head!=NULL){
            Node* temp = head;      // Store old head for deletion

            if(head==tail){         // Single-node list
                head = tail = NULL;
            }
            else{                   // Multi-node
                head = head->next; // move head to next node
                tail->next=head;     // tail now points to new head

               // temp->next = NULL  optional because we're deleteing temp anyway.            
            }


            delete temp;             // Free memory
            size--;
        }
        else cout<<"Error : List is already empty"<<endl;
    }

    // Pop front without head pointer
    /*
    void pop_front(){
        if(tail!=NULL){
            Node* temp = tail->next;  // tail->next is head

            if(tail->next==tail){     // Single-node
                tail = NULL;
            }
            else{
                tail->next = temp->next; // Update tail->next to new head
              // temp->next = NULL  optional because we're deleteing temp anyway           
            }

            delete temp;
            size--;
        }
        else cout<<"Error : List is already empty"<<endl;
    }
    */

    // ---------------------------
    // 4. POP BACK
    // ---------------------------
    void pop_back(){
        if(head!=NULL){
            Node* temp = tail;

            if(head==tail){ // Single-node
                head = tail = NULL;
            }
            else{           // Multi-node: find node before tail
                Node* temp2 = head;
                while(temp2->next != tail){
                    temp2 = temp2->next;
                }
                temp2->next = head; // Maintain circularity
                tail = temp2;       // Update tail
              //// temp->next = NULL  optional because we're deleteing temp anyway  
            }

            delete temp;
            size--;
        }
        else cout<<"Error : List is already empty"<<endl;
    }

    // Pop back without head pointer
    /*
    void pop_back(){
        if(tail!=NULL){
            Node* temp = tail;

            if(tail->next==tail){    // Single-node
                tail=NULL;
            }
            else{
                Node* temp2 = tail->next;   // Start from head
                while(temp2->next!=tail){
                    temp2=temp2->next;      // Find node before tail
                }
                temp2->next = tail->next;   // Maintain circularity
                tail = temp2;               // Update tail
                // temp->next = NULL  optional because we're deleteing temp anyway
            }

            delete temp;
            size--;
        }
        else cout<<"Error : List is already empty"<<endl;
    }
    */

    // ---------------------------
    // 5. PRINT LIST
    // ---------------------------
    void print(){
        if(head == NULL){
            cout<<"[Empty List]"<<endl;
            return;
        }

        Node* temp = head;
        cout<<"[";
        do{
            cout<<temp->val;
            temp = temp->next;
            if(temp != head) cout<<" -> ";
        } while(temp != head);
        cout<<"]"<<endl;
    }

    // ---------------------------
    // 6. GET SIZE
    // ---------------------------
    int get_size(){ return size; }

};

/*
    Key Insights:

    1. Circular property is maintained by making tail->next always point to head.
    2. For single-node lists, newNode->next = newNode is mandatory.
    3. pop_back requires traversal if singly linked, as no previous pointer exists.
    4. Special cases for empty list and single-node list must be handled separately.
    5. Using head pointer simplifies push/pop operations but is optional.
*/

int main(){
    List l; // Create an empty circular linked list

    // Initially, the list is empty
    cout << "Initial empty list: ";
    l.print(); // Should show [Empty]

    // Push front on an empty list
    cout << "\nPush front 10 on empty list: ";
    l.push_front(10); // Adds 10 as the first node; head = tail = node; circular link: node->next = node
    l.print(); // List: 10 -> (points back to 10)

    // Push back on a single-node list
    cout << "\nPush back 20 on single-node list: ";
    l.push_back(20); // Adds 20 after tail; tail->next points to head; tail updated
    l.print(); // List: 10 -> 20 -> (points back to 10)

    // Push front on a multi-node list
    cout << "\nPush front 5 on multi-node list: ";
    l.push_front(5); // Adds 5 before head; tail->next updated to new head
    l.print(); // List: 5 -> 10 -> 20 -> (points back to 5)

    // Push back on multi-node list
    cout << "\nPush back 30: ";
    l.push_back(30); // Adds 30 after tail; tail->next points to head
    l.print(); // List: 5 -> 10 -> 20 -> 30 -> (points back to 5)

    // Pop front from multi-node list
    cout << "\nPop front: ";
    l.pop_front(); // Removes current head (5); tail->next updated to new head
    l.print(); // List: 10 -> 20 -> 30 -> (points back to 10)

    // Pop back from multi-node list
    cout << "\nPop back: ";
    l.pop_back(); // Removes current tail (30); finds new tail; tail->next updated to head
    l.print(); // List: 10 -> 20 -> (points back to 10)

    // Pop front repeatedly until list becomes empty
    cout << "\nPop front until empty: ";
    l.pop_front(); // Removes head (10)
    l.print(); // List: 20 -> (points back to itself)
    l.pop_front(); // Removes head (20), list becomes empty
    l.print(); // [Empty]
    l.pop_front(); // Attempt to pop from empty list, triggers error message
    l.print(); // [Empty]

    return 0;
}
