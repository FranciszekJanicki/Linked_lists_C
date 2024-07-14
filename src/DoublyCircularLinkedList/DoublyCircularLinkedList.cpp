#include "DoublyCircularLinkedList.h"

template <class T>
DoublyCircularLinkedList<T>::DoublyCircularLinkedList() {

}

template <class T>
DoublyCircularLinkedList<T>::~DoublyCircularLinkedList() {

    for (int i = 0; i < length; ++i) {
        deleteNodeHead();
    }

    // OR
    /*
    for (int i = 0; i < length; ++i) {
        deleteNodeTail();
    }
    */

    if (head != nullptr) {
        delete head;
        head = nullptr;
    }
    if (tail != nullptr) {
        delete tail;
        tail = nullptr;
    }
}

template <class T>
/* be aware that this function takes node to the left and to the right of destination insertion,
so when iterating from the back and having current node to the left of node to be inserted and previous node to
the right of node to be inserted, then current goes as first parameter, previous as second parameter (opposing to iterating forward)
*/
void DoublyCircularLinkedList<T>::insertBetween(Node<T> *left, Node<T> *right, const T &data) {

    Node<T> *newest = nullptr;
    
    if (right != left) {
        newest = new Node<T>();
        newest->data = data;
        // join newest and right
        newest->next = right;
        right->prev = newest;
        // join newest and left
        newest->prev = left;
        left->next = newest;
    }

    ++length;
}

template <class T>
void DoublyCircularLinkedList<T>::addEmptyNodeHead(Node<T>* &newest) {
   
    newest = new Node<T>();

    // if list empty
    if (head == nullptr) {
        // join newest with head and tail and actualize
        newest->next = head;
        newest->prev = tail;
        head = tail = newest;
    } 
    // not empty
    else {
        // join newest and head
        newest->next = head;
        head->prev = newest;
        // join newest ant tail
        newest->prev = tail;
        tail->next = newest;
        // actualize head
        head = newest;
    }

    ++length;
}

template <class T>
void DoublyCircularLinkedList<T>::addNodeHead(const T &data) {
   
    Node<T> *newest = nullptr;
    addEmptyNodeHead(newest);
    newest->data = data;

    ++length;
}

template <class T>
void DoublyCircularLinkedList<T>::addEmptyNodeTail(Node<T>* &newest) {

    newest = new Node<T>();
    
    // if list empty
    if (tail == nullptr) {
        // join newest with head and tail and actualize
        newest->next = head;
        newest->prev = tail;
        tail = head = newest;
    } 
    // not empty
    else {
        // join newest and head
        newest->next = head;
        head->prev = newest;
        // join newest and tail
        newest->prev = tail;
        tail->next = newest;
        // actualize tail
        tail = newest;  
    }

    ++length;
}

template <class T>
void DoublyCircularLinkedList<T>::addNodeTail(const T &data) {
   
    Node<T> *newest = nullptr;
    addEmptyNodeTail(newest);
    newest->data = data;

    ++length;
}
template <class T>
void DoublyCircularLinkedList<T>::deleteNodeTail() {
    // if list empty
    if (head == nullptr) return;

    // if list has 1 element
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        return;
    }

    // with doubly list you dont need to iterate to find second to last, because you have tail->prev
    // dont need to use temp, because you can use tail->next after changing tail addres to release deleted node
    // actualize tail
    tail = tail->prev;
    // free memory
    delete tail->next;
    // join head and tail
    tail->next = head;
    head->prev = tail;

    --length;
}

template <class T>
void DoublyCircularLinkedList<T>::deleteNodeHead() {
    // if list empty
    if (length == 0) return;

    // if list has 1 element
    if (length == 1) {
        delete head;
        head = tail = nullptr;
        return;
    }

    // actualize head
    head = head->next;
    // free memory
    delete head->prev;
    // join head and tail
    head->prev = tail;
    tail->next = head;

    --length;
}

template <class T>
void DoublyCircularLinkedList<T>::insertNode(const int &index, const T &data) {
    // handle incorrect index, wont have to worry later
    if (index < 0 || index > length) return;

    Node<T> *current = nullptr;
    Node<T> *previous = nullptr;

    if (index == 0) addNodeHead(data); // this function checks if length is 0
    else if (index == length) addNodeTail(data); // this function checks if length is 0
    else {
        // check if its faster to iterate from the front or the back, find pointers to node on index and previous
        if (index < length/2) {
            current = head;
            for (int i = 0; i < index; ++i) {
                previous = current;
                current = current->next;
            }
            insertBetween(previous, current, data);

        } else {
            current = tail;
            for (int i = 0; i < index; ++i) {
                previous = current;
                current = current->prev;
            }
            insertBetween(current, previous, data); // !!! insertBetween function is made to take node to the left and to the right as parameters, so when
            // iterating backwards, the previous is on the right and current on the left !!!
        }

        // OR
        /* 
        current = getNode(index);
        previous = current->prev; // previous = getNode(index - 1);
        insertBetween(previous, current, data);
        }
        */

        // OR
        /* 
        previous = getNode(index - 1);
        current = previous->next; // current = getNode(index);
        insertBetween(previous, current, data);
        }
        */
    }

    current = nullptr;
    previous = nullptr;
}

template <class T>
void DoublyCircularLinkedList<T>::removeNode(const T &index) {
    // handle incorrect index, wont have to worry later
    if (index < 0 || index > length) return;

    Node<T> *current = nullptr;
    Node<T> *previous = nullptr;
    Node<T> *next = nullptr;

    if (index == 0) deleteNodeHead();    
    else if (index == length) deleteNodeTail();
    else {
        // erase current node
        current = getNode(index);
        previous = current->prev; // previous = getNode(index - 1);
        // join previous and next to current
        previous->next = current->next;
        (current->next)->prev = previous;
        // free memory
        delete current; // delete getNode(index);
        --length;

        // OR
        // erase node between previous and next
        /*
        next = getNode(index + 1);
        previous = (current->prev)->prev; // previous = getNode(index - 1);
        // free memory
        delete previous->next; // delete getNode(index);
        // join previous and next       
        previous->next = next;
        next->prev = previous;  
        --length;  
        */

        // OR
        // erase node between previous and next
        /*
        previous = getNode(index - 1);
        current = (previous->next)->next;// current = getNode(index + 1); 
        // free memory
        delete previous->next; // delete getNode(index);
        // join previous and current
        previous->next = current;
        current->prev = previous;  
        --length;  
        */

       // OR
       /*
       if (index < length/2) {
            // find previous and next
            current = head;
            for (int i = 0; i < index; ++i) {
                previous = current;
                current = current->next;
            }
            next = current->next;
            // free memory
            delete current;
            previous->next = next;
            next->prev = previous;
            

        } else {
            // NOTE that here previous is on the right, next on the left, because of iterating backwards!
            // find previous and next
            current = tail;
            for (int i = 0; i < index; ++i) {
                previous = current;
                current = current->prev;
            }
            next = current->prev;
            // free memory
            delete current;
            // join next and previous (knowinh they are 'logically' swapped)
            next->next = previous;
            previous->prev = next;
        }   
        */

        // OR
        // swap previous and next when iterating backward and use same formula
        if (index < length/2) {
            // find previous and next
            current = head;
            for (int i = 0; i < index; ++i) {
                previous = current;
                current = current->next;
            }
            next = current->next;
            
        } else {
            // find previous and next
            current = tail;
            for (int i = 0; i < index; ++i) {
                previous = current;
                current = current->prev;
            }
            next = current->prev;
            // swap
            Node<T> *tmp = next;
            next = previous;
            previous = tmp;
        }          
        // free memory
        delete current;
        // join previous and next
        previous->next = next;
        next->prev = previous;
    }

    current = nullptr;
    previous = nullptr;
}

template <class T>
void DoublyCircularLinkedList<T>::removeNodeElement(const T &data) {

    Node<T> *current = head;
    Node<T> *previous = nullptr;

    while (current != nullptr) {
        
        if (current->data == data) {
            if (current == head) deleteNodeHead();
            else if (current == tail) deleteNodeTail();
            else {
                // erase current node
                // join previous and next to current
                previous->next = current->next;
                (current->next)->prev = previous;
                // free memory
                delete current;
            }
            // return; // dont stop iterating, remove all nodes with this data
        }

        previous = current;
        current = current->next;
    }

    previous = nullptr;
    current = nullptr;
}

template <class T>
void DoublyCircularLinkedList<T>::print() const {
    // if list empty then dont dereference nullptrs!
    if (head != nullptr) {
        Node<T> *current = head;
        for (int i = 0; i < length; ++i) {
            printf(nullptr, current->data);
            current = current->next;
        }
    current = nullptr;
    }
}

template <class T>
int DoublyCircularLinkedList<T>::getLength() const {
    return length;
}

template <class T>
T *DoublyCircularLinkedList<T>::getHead() const {
    return head;
}

template <class T>
T *DoublyCircularLinkedList<T>::getTail() const {
    return tail;
}

template <class T>
Node<T> *DoublyCircularLinkedList<T>::getNode(const int &index) const {
    // handle incorrect index, wont have to worry later
    if (index < 0 || index > length) return nullptr;

    Node<T> *current = nullptr;
    // check if its faster to iterate from the back or the front
    if (index < length/2) {
        // start from the head
        current = head;
        for (int i = 0; i < index; ++i) {
            // go forward
            current = current->next;
        }
    } else {
        // start from tail
        current = tail;
        for (int i = 0; i < index; ++i) {
            // go backward
            current = current->prev;
        }
    }

    return current;
}

template <class T>
T DoublyCircularLinkedList<T>::getData(const int &index) const {
    return getNode(index)->data;
}

template <class T>
void DoublyCircularLinkedList<T>::setData(const int &index, const T &data) {
    getNode(index)->data = data;
}

template <class T>
void DoublyCircularLinkedList<T>::assign(const T *array, const int &length) {
    if (array = nullptr || length == 0) return;

    // resize
    int sizeDifference = length - this->length;
    int i;
    if (sizeDifference > 0) {    
        for (i = 0; i < sizeDifference; ++i) {
            Node<T> *toAdd = nullptr;
            addEmptyNodeTail(toAdd);
        }
    } else if (sizeDifference < 0) {
        for (i = 0; i < -sizeDifference; ++i) {
            deleteNodeTail();
        }
    }

    /* this has shitty complexity as every iteration will call getNode function, which iterates to the index*/
    /* for (i = 0; i < length; ++i) {
        setData(i, array[i]);
    } 
    */
    Node<T> *current = head;
    for (i = 0; i < length; ++i) {
        current->data = array[i];
        current = current->next;
    }
}
