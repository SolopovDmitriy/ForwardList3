#include<iostream>
using namespace std;

#define tab	"\t"

class Element {
public:

	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext) {

		cout << "EConstructor:\t" << this << endl;
	}
	~Element() {
		Data = 0;
		pNext = nullptr;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;

private:
	int Data;
	Element* pNext;
};
class ForwardList {
public:
	
	ForwardList() {
		this->Head = nullptr;
		this->IndexList = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	
	~ForwardList() {
		for (Element* Temp = Head; Temp; ) {
			Element* to_del = Temp;
			Temp = Temp->pNext;
			delete to_del;
		}
		this->Head = nullptr;
		this->IndexList = -1;
		cout << "LDestructor:\t" << this << endl;
	}
	
	ForwardList(int data, ...) {
		cout << "ConstructorVariableParameters:\t" << this << endl;
		this->Head = nullptr;
		this->IndexList = 0;
		for (int* ptr = &data; *ptr != -1; ptr++) {
			push_back(*ptr);
		}
	}
	
	ForwardList(const ForwardList &Head) {
		cout << "CopyConstructor:\t" << this << endl;
		this->Head = nullptr;
		this->IndexList = 0;
		push_back_list(Head.Head);
	}
	
	ForwardList(int len) {
		this->Head = nullptr;
		this->IndexList = 0;
		for (int i = 0; i < len; i++) {
			push_front(0);
		}
	}
	
	void Set_IndexList(int IndexList) {
		this->IndexList = IndexList < 0 ? 0 : IndexList;
	}
	int Get_IndexList() const {
		return this->IndexList;
	}
	void Set_Head(Element *Head) {
		this->Head = Head;
	}
	Element* Get_Head() const {
		return this->Head;
	}
	bool ErrDelElementList() {
		if (Head == nullptr) {
			this->IndexList = 0;				
			return false;						
		}
		else if (this->IndexList <= 1) {		
			delete  Head->pNext;
			Head = nullptr;						
			this->IndexList = 0;				
			return false;						
		}
		return true;
	}
	
	void push_front(int Data) {
		Head = new Element(Data, Head);
		this->IndexList++;						
	}
	
	void push_back(int Data) {
		if (Head == nullptr) {						
			push_front(Data);						
			return;									
		}
		Element* Temp = Head;						
		while (Temp->pNext) {						
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);			
		this->IndexList++;							
	}
	
	void push_back_list(Element* Head1) {
		if (Head == Head1) return;
		while (Head) {						
			Head = Head->pNext;
		}
		for (Element* Temp1 = Head1; Temp1; Temp1 = Temp1->pNext) {
			push_back(Temp1->Data);
		}
	}

	
	void pop_front() {
		if (ErrDelElementList() == false) return;	
		Element* to_del = Head;						
		Head = Head->pNext;							
		delete to_del;								
		this->IndexList--;							
	}

	void pop_back() {
		if (ErrDelElementList() == false) return;	
		Element* Temp = Head;						
		while (Temp->pNext->pNext) {				
			Temp = Temp->pNext;						
		}
		delete Temp->pNext;							
		Temp->pNext = nullptr;						
		this->IndexList--;							
		return;
	}
	
	void insert(int Data, int index) {
		while (this->IndexList < index) {				
			push_back(0);								
		}
		if (index == 0) {
			push_front(Data);
			return;
		}
		Element* Temp = Head;							
		for (int i = 0; i < index - 1; i++) {			
			Temp = Temp->pNext;							
		}

		Temp->pNext = new Element(Data, Temp->pNext);	
		this->IndexList++;								

		return;
	}
	
	bool erase(int index) {
		if (this->IndexList <= index) return false;		
		Element* Temp = Head;							

		for (int i = 0; i < index - 1; i++) {			
			Temp = Temp->pNext;
		}
		Element* to_del = Temp->pNext;					
		Temp->pNext = Temp->pNext->pNext;				
		delete to_del;									

		if (this->IndexList != 0)						
			this->IndexList--;							
		return true;									
	}
	
	void print() {
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << endl << tab << " list: " << this->IndexList << endl;
	}

	void operator = (const ForwardList& Head) {
		cout << "AssignConstructor:\t" << this << endl;
		for (Element* temp = this->Head; temp;) {
			Element* to_del = temp;
			temp = temp->pNext;
			delete to_del;
		}
		this->Head = nullptr;
		this->IndexList = 0;
		push_back_list(Head.Head);
		return;
	}
	ForwardList operator +(const ForwardList& Head) {
		Element* temp;
		this->push_back_list(Head.Head);
		return *this;
	}
	int operator[](int index) {

		for (Element* Temp = Head; Temp; Temp = Temp->pNext) {
			if (index-- == 0)
				return Temp->Data;
		}
		return -1;
	}

private:
	Element* Head;
	int IndexList;
};



void main() {
	setlocale(LC_ALL, "");

	
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(7);
	list1.push_back(15);
	list1.push_back(30);
	list1.print();

	ForwardList list2{ 1,2,3,4,5,-1 };
	list2.print();
	ForwardList list3;
	list3 = list1 + list2;
	list3.print();
	
}