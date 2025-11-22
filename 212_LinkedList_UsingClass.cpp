// LINKED LIST

/* A Linked List is a linear data structure where elements (called nodes) 
   are stored non-contiguously. Each node contains:
     1. Data (value)
     2. Pointer (reference to the next node)

   ⚡ Differences from arrays/vectors:
   1. Dynamic Size: Linked lists can grow/shrink at runtime, 
      while arrays are fixed-size.
   2. Memory Allocation: Each node is allocated separately (heap),
      unlike arrays which require a contiguous memory block.
   3. Insert/Delete: Efficient if the node reference is known 
      (O(1) by pointer update), unlike arrays which may need element shifting.
   4. Random Access: Not supported (must traverse sequentially), 
      unlike arrays with O(1) access by index.
   5. Extra Memory: Linked lists use extra space for pointers.

   📌 Types of Linked Lists:
   - Singly Linked List: Node → Next
   - Doubly Linked List: Node → Prev + Next
   - Circular Linked List: Last node connects back to head

   ✅ Use when: frequent insertions/deletions are needed.
   ❌ Avoid when: random access or cache efficiency is important.
*/

    // Head pointer points to the first node which then points to the next node and so on
    // We can't access a node directly, we have to traverse from head to that node

    // The last node points to NULL indicating the end of the list
    // Head -> node1 -> node2 -> node3 -> NULL

    // Tail pointer points to the last node
    // head -> node1 -> node2 -> node3 (tail)
    // tail->next = NULL


    // Ways to implement a linked list in C++:
    // 1. Using built-in STL containers (std::list, std::forward_list)
    // 2. By manually creating Node classes/structs

#include<iostream> // include IO library for cout, endl — used throughout for printing and error messages
using namespace std; // bring std names into global namespace for brevity (acceptable for small learning code)

// Node class representing each element in the linked list
class Node{ // class defines the structure for one node; minimal public members for simplicity
    public:
    int data; // payload stored in the node — type int here, could be templated in production
    Node* next; // pointer to the next node in the sequence; NULL indicates end

    // Constructor
    Node(int val){ // constructs a node with given value; this is invoked when using new Node(val)
        data = val; // store payload
        next = NULL; // initialize next to NULL — node starts as a standalone element until linked
    }
}; // end Node class — only holds data and linkage; memory allocated with new must be freed with delete later

// we will need another class to link these nodes
class List{ // List manages the head/tail pointers and provides operations on the linked list
    Node* head; // pointer to first node; invariant: head==NULL => list empty
    Node* tail; // pointer to last node; invariant: tail==NULL <=> head==NULL (both NULL if empty)
    int size; // number of nodes currently in the list; maintained to allow O(1) size queries
    
    public:
    List(){ // constructor: creates an empty list
        head = tail = NULL; // no nodes initially, so both head and tail are NULL
        size=0; // size starts at 0 and must be updated on every successful insert/delete
        // now we create functions push_front, push_back, pop_front, pop_back etc.
        // head is either null (no node) or not null (atleast one node)    
    }

// PUSH FRONT

    // CASE 1: If linked list is empty :
        /*
        1. We create a new Node
        2. We make both head and tail to point towards the new node
        */
     // If the linked list is not empty
        /* CASE 2:
        1. we create a new node
        2. newNode-> next = head
        3. head = newnode
        */

    void push_front(int val){  // Insert at beginning; amortized O(1) time and O(1) extra memory
        Node* newNode = new Node(val); // dynaimc allocation on heap: must be deleted later when node removed or in destructor
       //  Node newNode(val); // static implementation, data get deleted as we get out of function (commented out — would create stack-allocated node which would be invalid after function returns)
       if(head==NULL){ // case 1: list empty — handle separately to keep tail correct
        head = tail = newNode; // both head and tail point to the single node in the list
        size++; // increment size because we added the first node
        return; // exit early: insertion complete for empty list case
       }
       else{ // case 2: there is at least one node already
        newNode->next = head;// *(newNode).next = head — link new node's next to current head (order matters)
        head = newNode; // update head to new node (now first)
       }
       size++; // increment size for the non-empty case (we intentionally increment twice in code flow? NOTE: not duplicate because we returned earlier in empty case)
    }
    // Print a linked list

    void print(){
        Node* temp = head;//creating a temporary variable because we can't traverse back in LL. We use temp to walk without moving head
        if(head==NULL){cout<<"[Empty]"<<endl; return;} // immediate return for empty list: avoids printing strange output, explicit user-friendly message
        cout<<"["; // start display bracket
        while(temp != NULL){ // traverse until NULL (end marker)
         cout<<temp->data; // print data at current node
         temp = temp->next; // move to next node (may become NULL when we reach tail)
         if(temp!=NULL) cout<<" -> "; // if there is a next node, print arrow separator
         else cout<<"]"<<endl; // after traversing the linked list, close bracket and newline when we reached end
        }
    }

    // GET SIZE OF LINKED LIST
    int get_size() {
    return size; // return maintained size in O(1) time — accurate only if all ops update size correctly
    }


// PUSH_BACK IN LL

    // CASE 1: If linked list is empty :
        /*
        1. We create a new Node
        2. We make both head and tail to point towards the new node
        */
     // If the linked list is not empty
        /* CASE 2:
        1. we create a new node
        2. tail-> next = newNode
        3. tail = newnode
        */

    void push_back(int val){ // append at end; O(1) time due to tail pointer
        Node* newNode = new Node(val); // dynaimc allocation — new node initially standalone
       //  Node newNode(val); // static implementation, data get deleted as we get out of function (commented)
       if(head==NULL){ // case 1: empty list — must update both head and tail
        head = tail = newNode;
        size++; // increment size because list was empty and we added first node
        return; // early return to avoid falling through into size++ again
       }
       else{ // case 2: non-empty list — link from current tail to new node
        tail->next = newNode;// *(tail).next = newNode — connect previous last node to new node
        tail = newNode; // update tail to be new node
       }
       size++; // increment size for non-empty case
    }

// POP_FRONT IN LL
    // Only needed when ll is not empty

    void pop_front(){ // remove from head; O(1) time
    if (head != NULL) { // only proceed if list not empty — guard against underflow
        Node* temp = head; // temp holds pointer to old head so we can delete it safely after moving head

        if (head == tail) { // single node case: after removal list becomes empty
            head = tail = NULL; // reset both pointers to NULL to avoid dangling tail/head
        } else {
            head = head->next; // move head to next node; works when there are >= 2 nodes
        }

        delete temp; // free memory of removed node; prevents memory leak
        size--; // decrement size since we removed an element
    }
    else {
        cout << "Error : Linked List is already empty" << endl; // user-friendly error message on invalid pop
    }
    }

// POP_BACK IN LL
    // Only needed when ll is not empty

    void pop_back(){ // remove last element; O(n) time worst-case because we must find second-last unless single node
    if(head != NULL){ // guard: only if list not empty
        if(head == tail){ // single node case — simpler to handle separately
            delete head; // free the only node
            head = tail = NULL; // list becomes empty, reset pointers
        } else {
            Node* temp = head; // start traversal from head
            while(temp->next != tail){ // move until temp points to second-last node (temp->next == tail)
                temp = temp->next; // advance
            }
            delete tail; // free last node
            tail = temp; // update tail to second-last node
            tail->next = NULL; // new tail must point to NULL to mark end
        }
        size--; // decrease element count after successful removal
    }
    else {
        cout<<"Error : Linked list is already empty"<<endl; // error message for invalid pop_back call
    }
 }

 // INSERT IN LL

     void insert(int val, int pos){ // insert value 'val' at index 'pos' (0-based). Behaves like vector::insert semantics
       
        if(pos==0) {push_front(val); return ;} // if pos==0, insert at front using helper (push_front handles size)
        if(pos<0) {cout<<"Invalid Position"<<endl; return;} // negative positions invalid — early return

     Node* temp = head; // temp will be used for traversal — start from head

        // int idx=0;   if we hadn't declare size, use idx instead of size
       

        if(size==pos) {push_back(val); return; } // if pos equals current size, append at end — push_back updates size and tail

        
        if(pos>0 && pos<size){// not needed when size not used and we're using idx variable; this branch handles middle insertion (0 < pos < size)
         for(int i=0; i<pos-1; i++){ // move temp to node at index pos-1 (node before insertion position)
            // if(temp==NULL){cout<<"Invalid position"<<endl; return;} // defensive check commented out — not used because pos validated against size
            temp=temp->next; // advance pointer safely because pos < size guarantees temp won't be NULL in the loop
         }
        Node* newNode = new Node(val); // allocate new node to insert
        newNode->next = temp->next; // new node's next becomes successor of temp (can be tail as well)
        temp->next = newNode; // link predecessor to new node — insertion complete
        size++;} // increment size for the direct insertion path (push_front/push_back already did it)

        else if (pos>size) { 
            cout<<"Invalid Position"<<endl; return; // pos > size is out-of-bounds: can't insert past size
        }
     }

 // SEARCH IN LL
    
    int search(int val) { // return 0-based index of first occurrence of val; -1 if not found
    int idx = 0; // index counter
    Node* temp = head; // traversal pointer

    while (temp != NULL) { // traverse until end
        if (temp->data == val) { // compare payload with search value
            return idx; // found — return index immediately (first occurrence)
        }
        temp = temp->next; // move to next node
        idx++; // increment position counter
    }
    return -1; // not found — return -1 as sentinel
}

// DECONSTRUCTOR

    ~List() { // destructor: frees all nodes when a List object goes out of scope or is deleted
        Node* temp = head; // start from head
        while(temp != NULL) { // iterate through entire list
            Node* nextNode = temp->next; // save next pointer before deleting current node
            delete temp;         // free current node memory — prevents memory leaks
            temp = nextNode;     // move to next node
        }
        head = tail = NULL; // safety: reset pointers though object is being destroyed; prevents stale state
        size = 0; // reset size for completeness
    }


};


int main(){

    List ll; // create an instance of List on the stack; constructor initializes empty list

    ll.push_back(1);  // 1  -> appends 1 to empty list; after call: [1]
    ll.push_back(2);  // 1 -> 2  -> appends 2; after: [1 -> 2]
    ll.push_back(3);  // 1 -> 2 -> 3  -> appends 3; after: [1 -> 2 -> 3]

    cout<<"Current Size = "<<ll.get_size()<<endl; // prints current size maintained by class (should be 3)

    ll.print(); // prints the list contents to stdout

    ll.push_front(0);  // 0 -> 1 -> 2 -> 3  -> insert at head
    ll.push_front(-1); // -1 -> 0 -> 1 -> 2 -> 3
    ll.push_front(-2); // -2 -> -1-> 0 -> 1 -> 2 -> 3

    ll.print(); // print updated list after push_front operations

    ll.pop_front(); // -1-> 0 -> 1 -> 2 -> 3  -> remove first element (-2) safely with size-- and memory freed
    cout<<"Current Size = "<<ll.get_size()<<endl; // print size after pop_front

    ll.print(); // print list state after pop_front

    ll.pop_back(); // -1-> 0 -> 1 -> 2  -> remove last element (3) safely with size-- and memory freed
    

    ll.print(); // print after pop_back

    ll.insert(0,4); // insert value 0 at position 4 — with current list size 4 this becomes push_back equivalent: append to end
    cout<<"Current Size = "<<ll.get_size()<<endl; // print size after insert

    cout<<"1 seached on place : "<<ll.search(1)<<endl;  // search returns index of first occurrence of 1
    cout<<"2 seached on place : "<<ll.search(2)<<endl;  // search returns index of first occurrence of 2
    cout<<"-1 seached on place : "<<ll.search(-1)<<endl; // search returns index of -1 (head after pops) 
    

    return 0; // program ends; destructor ~List() will be called automatically for ll to free all nodes
}
