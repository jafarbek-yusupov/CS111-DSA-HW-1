#include <iostream>
using namespace std;
typedef string str;

struct Data {
    int eid;
    str name;
    str date_of_birth;
    str phone_number;
    str address;

    Data(int eid=0, str name="", str dob="", str ph="", str drs=""): 
        eid(eid), name(name), date_of_birth(dob), phone_number(ph), address(drs){}

    void update(const Data& updd){
        if(updd.eid !=0) eid = updd.eid; 
        if(!updd.name.empty()) name = updd.name;
        if(!updd.date_of_birth.empty()) date_of_birth = updd.date_of_birth;
        if(!updd.phone_number.empty()) phone_number = updd.phone_number;
        if(!updd.address.empty()) address = updd.address;
    }
    
    bool compare(const Data& d2) const{
        return
        eid == d2.eid &&
        name == d2.name && 
        date_of_birth == d2.date_of_birth &&
        phone_number == d2.phone_number && 
        address == d2.address;
    }

    bool operator==(const Data& d2) const{
        return compare(d2);
    }

    void print() const{
        cout << "employee id: " << eid << " | " 
             << "name: " << name << " | " 
             << "date of birth: " << date_of_birth << " | " 
             << "phone number: " << phone_number << " | " 
             << "address: " << address << ";\n";
    }
};

class Employee{
public:
    Employee(Data d, Employee* nxt=nullptr): data(d), next(nxt){}
    // Employee ID, Name, Date of Birth, Phone number address
private:
    Data data;
    Employee* next;
    friend class EmpLinkedList;
};

class EmpLinkedList{
private:
    Employee* head;
public:
    EmpLinkedList();
    ~EmpLinkedList();

    bool isEmpty() const;
    Employee* Front() const;
    Employee* Back() const;
    void printList();
    
    void addFront(Data d);
    void addBack(Data d);
    void deleteFront();
    void deleteBack();

    // Employee* find(Data d);
    bool find(int id);
    void modify(Data d, int idx);
    void add(Data d, int idx);
    void del(int idx);
    int count();
};

EmpLinkedList::EmpLinkedList(): head(nullptr){};
EmpLinkedList::~EmpLinkedList(){};

bool EmpLinkedList::isEmpty() const{ return head == nullptr;};
Employee* EmpLinkedList::Front() const{ return head;}
Employee* EmpLinkedList::Back() const{ 
    if(isEmpty()){ return head;}
    Employee* back=head; 
    while(back->next!=nullptr){ back=back->next;}; 
    return back;
}

void EmpLinkedList::printList(){ 
    for(Employee* i=head; i!=nullptr; i=i->next){ 
        cout 
        << "employee id: " << i->data.eid << " | " 
        << "name: " << i->data.name << " | " 
        << "date of birth: " << i->data.date_of_birth << " | " 
        << "phone number: " << i->data.phone_number << " | " 
        << "address: " << i->data.address << ";\n"; 
    };
};

void EmpLinkedList::addFront(Data d){
    Employee* nn = new Employee(d); nn->next = head; head = nn;
};

void EmpLinkedList::addBack(Data d){
    Employee*  nn = new Employee(d); 
    if(isEmpty()){ head=nn; return;}
    Employee* tail=head;
    while(tail->next!=nullptr){ tail = tail->next;}
    tail->next = nn;
}

void EmpLinkedList::deleteFront(){
    if(!head){ return;}
    Employee* oldHead = head;
    head = head->next;
    delete oldHead;
};

void EmpLinkedList::deleteBack(){
    if(!head){ return;} Employee* preTail=head;
    while(preTail->next->next!=nullptr){ preTail=preTail->next;}
    delete preTail->next; preTail->next = nullptr;
};

// Employee* EmpLinkedList::find(Data d){
//     for(Employee* i=head; i!=nullptr; i=i->next){ if(d==i->data){ return i;}}
//     return nullptr;    
// };

bool EmpLinkedList::find(int id){
    for(Employee* i=head; i!=nullptr; i=i->next){ 
        if(i->data.eid == id){ cout << "employee found:\n";i->data.print(); return true;}
    }
    cout << "empl with id " << id << " not found\n";
    return false; 
};

void EmpLinkedList::modify(Data d, int idx){
    int cnt=0; Employee* toBeUpd=head;
    for(toBeUpd; toBeUpd!=nullptr && cnt<idx; toBeUpd=toBeUpd->next){ cnt++;}
    if(toBeUpd!=nullptr) toBeUpd->data.update(d);
};

void EmpLinkedList::add(Data d, int idx){
    if(idx==0){ addFront(d); return;}
    Employee* nn = new Employee(d);
    int cnt=0; Employee* b4nn=head;
    for(b4nn=head; b4nn!=nullptr && cnt<idx-1; b4nn=b4nn->next){ cnt++;}
    if(b4nn!=nullptr){ nn->next = b4nn->next; b4nn->next = nn;} 
};

void EmpLinkedList::del(int idx){    
    if(idx==0){ deleteFront(); return;}  
    int cnt=0; Employee* bytbd=head; 
    for(bytbd; bytbd!=nullptr && cnt<idx-1; bytbd=bytbd->next){ cnt++;};
    if(bytbd!=nullptr && bytbd->next!=nullptr ){
        Employee* toDel = bytbd->next;
        bytbd->next = toDel->next; delete toDel;    
    }
};

int EmpLinkedList::count(){
    int cnt=0;
    for(Employee* i=head; i!=nullptr; i=i->next){ cnt++;}
    return cnt;
};

void runTests(){
    cout << "\n===== testing =====\n\n";
    EmpLinkedList list;
    
    // test 1: is empty
    cout << "test 1 - empty: " << (list.isEmpty() ? "yes" : "no") << "\n";
    cout << "count: " << list.count() << "\n\n";
    
    // test 2: add front
    list.addFront(Data(101, "john", "1990-01-15", "998901234567", "tashkent"));
    cout << "test 2 - after addFront:\n";
    list.printList();
    cout << "count: " << list.count() << "\n\n";
    
    // test 3: add back
    list.addBack(Data(102, "jane", "1985-05-20", "998907654321", "samarkand"));
    list.addBack(Data(103, "ali", "1995-03-10", "998909876543", "bukhara"));
    cout << "test 3 - after 2 addBack:\n";
    list.printList();
    cout << "count: " << list.count() << "\n\n";
    
    // test 4: modify index 1
    cout << "test 4 - modify index 1:\n";
    list.modify(Data(0, "jane smith", "", "111111", ""), 1);
    list.printList();
    
    // test 5: add at index
    cout << "\ntest 5 - add at index 2:\n";
    list.add(Data(105, "sara", "2000-06-15", "998903334455", "namangan"), 2);
    list.printList();
    cout << "count: " << list.count() << "\n\n";
    
    // test 6: delete front
    cout << "test 6 - deleteFront:\n";
    list.deleteFront();
    list.printList();
    cout << "count: " << list.count() << "\n\n";
    
    // test 7: delete at index
    cout << "test 7 - delete index 1:\n";
    list.del(1);
    list.printList();
    cout << "count: " << list.count() << "\n\n";
    
    // test 8: delete back
    cout << "test 8 - deleteBack:\n";
    list.deleteBack();
    list.printList();
    cout << "count: " << list.count() << "\n\n";
    
    // test 9: find
    cout << "test 9 - find employee with id 102:\n";
    list.find(102);
    // cout << (found ? "found!" : "not found") << "\n";
    
    cout << "\n===== done =====\n";
}

int main(){  
    runTests();
    return 0;
}