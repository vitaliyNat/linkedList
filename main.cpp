#include <iostream>

using namespace std;



class Node{
private:
    int id;
public:

    Node * next;
    Node * prev;
    int data;

    Node(int value) {
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

void swapPointers(Node * first, Node * second){
    auto pSwap = *first;
    *first = *second;
    *second = pSwap;
}

bool compare(Node *first, Node *second){
    return first->data - second->data < 0;
}


class linkedList{

private:
    int size;
    Node *head;
    Node *tail;
    int idQty;


public:
//    void setValue(T value){
//        this->value = value;
//    }
//    T getValue(){
//        return this->value;
//    }
//    void setPrev( linkedList<T>  * list){
//        this->prev = list;
//    }
//    linkedList<T> * getPrev(){
//        return this->prev;
//    }
//    void setNext(linkedList<T> *list){
//        this->next = list;
//    }
//    linkedList<T> * getNext(){
//        return this->next;
//    }
//
////    void setIndex(){
////        this->index = 0;
////
////    }


    linkedList() {
        idQty = 1;
        size = 0;
        head = nullptr;
        tail = nullptr;
    }

    Node * getHead(){
    return this->head;
    }
    int getSize(){
    return this->size;
    }

    void add_begin(int value){

        Node * newNode = new Node(value);
        newNode->next = this->head;

        if(this->size == 0){
            this->tail = newNode;
        }else{
            this->head->prev = newNode;
        }
        this->head = newNode;

        newNode->setId(this->idQty);
        this->idQty++;
        this->size++;


    }
    void push_tail(int value){
        Node * newNode = new Node(value);
        newNode->prev = this->tail;


        if(size < 1){
            this->head = newNode;
        }else{
            this->tail->next = newNode;
        }

        this->tail = newNode;

        newNode->setId(this->idQty);
        this->idQty++;
        this->size++;
    }

    Node * searchNode(int value){
        auto * tmp = this->getHead();
        while(tmp != nullptr){
           if(tmp->data == value){
               return tmp;
           }
            tmp = tmp->next;
        }
        return nullptr;
    }

    void deleteLast(){
    this->tail = this->tail->prev;
    delete this->tail->next;
    this->tail->next = nullptr;
    this->size--;

    }

    void deleteFirst(){
    this->head = this->head->next;
    delete this->head->prev;
    this->head->prev = nullptr;
    this->size--;
    }

    void deleteNodeValue(int value){
    if(searchNode(value)){
        searchNode(value)->next->prev = searchNode(value)->prev;
        searchNode(value)->prev->next = searchNode(value)->next;
        this->size--;
        cout<<"Success"<<endl;
    }
    else{
        cout<< "Failed: invalid value"<<endl;
    }

    }
    void deleteNodeIndex(int index){
        if(this->index(index)){
            this->index(index)->next->prev = this->index(index)->prev;
            this->index(index)->prev->next = this->index(index)->next;
            this->size--;
            cout<<"Success"<<endl;
        }
        else{
            cout<< "Failed: invalid value"<<endl;
        }

    }


    Node * index(int i){
        auto * tmp = this->getHead();
        for(int j = 0; j<this->size; j++){
            if(j == i){
                return tmp;
            }
            tmp = tmp->next;

        }
        return nullptr;
    }

    void newValue(int index, int value){
        if(this->index(index)){
            this->index(index)->data = value;
            cout<<"Success"<<endl;
        }else{
            cout<<"Failed: invalid index"<<endl;
        }
    }
    void clearList(){
        while(size != 0){
            if(this->size == 1){
                delete this->head;
                this->head = nullptr;
                this->tail = nullptr;
                this->size = 0;
            }else{
                this->deleteFirst();
            }
         }
    }



    void sort(){
        bool change;
        for(int i = 0; i<size-1;i++){
            change = false;
            for(int j = 0; j<size-i-1; j++){
                if(compare(this->index(j),this->index(j+1))){
                   // swap(j, j+1);
                    change = true;
                }
            }
            if(change) return;
        }
    }

    void printList(){
        auto * tmp = this->getHead();
        if(tmp == nullptr){
            cout<<"Empty list"<<endl;
            return;
        }
        while(tmp != nullptr){
            tmp->printNode();
            tmp = tmp->next;
        }
    }

};


 int getRandom(){

 }



int main() {
    auto * first = new linkedList();
    first->add_begin(14);
    first->add_begin(15);
    first->add_begin(14);
    first->add_begin(13);
    first->add_begin(19);
    first->push_tail(1);
    first->push_tail(8);
    first->push_tail(9);
    first->deleteLast();
    first->push_tail(20);



    first->printList();
    cout<< first->getHead()->data<<endl;
    first->searchNode(13)->printNode();
    cout<<first->getSize() << endl;
    first->deleteNodeValue(14);
    first->printList();
    cout<<endl;
    first->index(11)->printNode();
    //first->clearList();

    cout<<endl;
    first->printList();

    cout<<endl;
    //first->swap(1,2);
    //first->sort();
    //first->printList();
    cout<<endl;
    auto  * p = new Node(7);
    auto * q = new Node(9);
    swapPointers(p,q);
     p->printNode() ;
     q->printNode();
    return 0;
}
