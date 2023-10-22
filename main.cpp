#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;


template <class  T>

class Node{
private:
    int id;
public:

    Node<T> * next;
    Node<T> * prev;
    T data;

    Node<T>(T value) {
        id  = 0;
        next = nullptr;
        prev = nullptr;
        data = value;
    }

    void setId(int id){
        this->id = id;
    }
    int getId(){
        return this->id;
    }

    void printNode(){
        if(this != nullptr){
            cout << "Node value: " <<this->data<<" ; Node id: " << this->getId()<<"; Address: "<< this<<endl;
        }else{
            cout<< "This node is NULL"<<endl;
        }
    }
};


template <class  T>

int compare(T first, T second){
    return first - second < 0 ? -1 :first - second == 0? 0 : 1;
}


template <class  T>
class linkedList {
private:
    int size;
    Node<T> *head;
    Node<T> *tail;
    int idQty;


public:


    linkedList<T>() {
        idQty = 1;
        size = 0;
        head = nullptr;
        tail = nullptr;
    }

    ~linkedList<T>() {
        this->clearList();
    }

    Node<T> *getHead() {
        return this->head;
    }

    int getSize() {
        return this->size;
    }

    void add_begin(T value) {

        auto *newNode = new Node<T>(value);
        newNode->next = this->head;

        if (this->size == 0) {
            this->tail = newNode;
        } else {
            this->head->prev = newNode;
        }
        this->head = newNode;

        newNode->setId(this->idQty);
        this->idQty++;
        this->size++;
    }

    void push_tail(T value) {
        auto *newNode = new Node<T>(value);
        newNode->prev = this->tail;


        if (size < 1) {
            this->head = newNode;
        } else {
            this->tail->next = newNode;
        }

        this->tail = newNode;

        newNode->setId(this->idQty);
        this->idQty++;
        this->size++;
    }

    Node<T> *searchNode(T value) {
        auto *tmp = this->getHead();
        while (tmp != nullptr) {
            if (tmp->data == value) {
                return tmp;
            }
            tmp = tmp->next;
        }
        return nullptr;
    }

    void deleteLast() {
        this->tail = this->tail->prev;
        delete this->tail->next;
        this->tail->next = nullptr;
        this->size--;
    }

    void deleteFirst() {
        this->head = this->head->next;
        delete this->head->prev;
        this->head->prev = nullptr;
        this->size--;
    }

    void deleteNodeValue(T value) {
        if (searchNode(value)) {
            searchNode(value)->next->prev = searchNode(value)->prev;
            searchNode(value)->prev->next = searchNode(value)->next;
            this->size--;
            cout << "Success" << endl;
        } else {
            cout << "Failed: invalid value" << endl;
        }
    }

    void deleteNodeIndex(int index) {
        if (this->index(index)) {
            this->index(index)->next->prev = this->index(index)->prev;
            this->index(index)->prev->next = this->index(index)->next;
            this->size--;
            cout << "Success" << endl;
        } else {
            cout << "Failed: invalid index" << endl;
        }
    }


    Node<T> *index(int i) {
        auto *tmp = this->getHead();
        for (int j = 0; j < this->size; j++) {
            if (j == i) {
                return tmp;
            }
            tmp = tmp->next;
        }
        return nullptr;
    }

    void newValue(int index, T value) {
        if (this->index(index)) {
            this->index(index)->data = value;
            cout << "Success" << endl;
        } else {
            cout << "Failed: invalid index" << endl;
        }
    }

    void clearList() {
        while (size != 0) {
            if (this->size == 1) {
                delete this->head;
                this->head = nullptr;
                this->tail = nullptr;
                this->size = 0;
            } else {
                this->deleteFirst();
            }
        }
    }


    void printList() {
        auto *tmp = this->getHead();
        if (tmp == nullptr) {
            cout << "Empty list" << endl;
            return;
        }
        while (tmp != nullptr) {
            tmp->printNode();
            tmp = tmp->next;
        }
    }

    void orderedInsert(T value) {
        if(!size){
            add_begin(value);
            return;
        }

        Node<T> *tmp = this->head;
        if (compare(this->head->data, value) >= 1) {
            this->add_begin(value);
            return;
        }
        auto *newNode = new Node(value);
        while(true){
            if (compare(tmp->data, value) >= 0) {
                newNode->prev = tmp->prev;
                auto tmp1 = tmp->prev;
                newNode->next = tmp;
                tmp->prev = newNode;
                tmp1->next = newNode;
                this->size++;
                newNode->setId(this->idQty);
                this->idQty++;
                return;
            }else{
            if(tmp->next){
                    tmp = tmp->next;
                }else{
                    this->push_tail(value);
                    return;
                }
            }
        }
    }
};


template <class T>
 T getRandom(){
    srand(time(0));
    return rand() % 1000;
 }



int main() {
    auto * first = new linkedList<int>();
    const int Qty = 1000;



    //Add begin
   auto t1 = chrono::high_resolution_clock::now();


    for(int i = 0; i<Qty; i++) {
        first->add_begin(getRandom<int>());
    }

   auto t2 = chrono::high_resolution_clock::now();
   auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
   printf("Add begin %d elements: Time measured: %.3d nanoseconds.\n",Qty, duration.count());

    first->clearList();

    //Add end
     t1 = chrono::high_resolution_clock::now();


    for(int i = 0; i<Qty; i++) {
        first->push_tail(getRandom<int>());
    }

     t2 = chrono::high_resolution_clock::now();
     duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    printf("Add end %d elements: Time measured: %.3d nanoseconds.\n",Qty, duration.count());

    first->clearList();


    //Add ordered
//    t1 = chrono::high_resolution_clock::now();
//
//
//    for(int i = 0; i<Qty; i++) {
//        first->orderedInsert(getRandom<int>());
//    }
//
//    t2 = chrono::high_resolution_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
//    printf("Add ordered %d elements: Time measured: %.3d nanoseconds.\n",Qty, duration.count());




    //Search random element by intdex
    t1 = chrono::high_resolution_clock::now();


    first->index(getRandom<int>());

    t2 = chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    printf("Search random element by index in %d elements: Time measured: %.3d nanoseconds.\n",Qty, duration.count());


    //Search random element and delete by index
    t1 = chrono::high_resolution_clock::now();


    first->deleteNodeIndex(getRandom<int>());

    t2 = chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    printf("Search random element by index and delete in %d elements: Time measured: %.3d nanoseconds.\n",Qty, duration.count());


    //Search random element  by value
    t1 = chrono::high_resolution_clock::now();


    first->searchNode(getRandom<int>());


    t2 = chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    printf("Search random element by value in  %d elements: Time measured: %.3d nanoseconds.\n",Qty, duration.count());

   //Search random element and delete  by value
    t1 = chrono::high_resolution_clock::now();


    first->deleteNodeValue(getRandom<int>());


    t2 = chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    printf("Search and delete random element by value in  %d elements: Time measured: %.3d nanoseconds.\n",Qty, duration.count());


    //clear list
    t1 = chrono::high_resolution_clock::now();


    first->clearList();


    t2 = chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    printf("Clear list  %d elements: Time measured: %.3d nanoseconds.\n",Qty, duration.count());






    return 0;
}
