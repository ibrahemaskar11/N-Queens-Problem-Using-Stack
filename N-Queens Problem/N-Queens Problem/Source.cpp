#include <iostream>
using namespace std;
template<class H>
class Node {
public:
	H item;
	Node* next;
	Node(H);
};
template<class H>
Node<H> ::Node(H val) {
	item = val;
}
template<class H>
class DynamicStack {
	Node<H>* top;
public:
	DynamicStack();
	~DynamicStack();
	void push(H);
	H pop();
	bool isEmpty();
	void display();
	H peak();
};
template<class H>
DynamicStack<H>::DynamicStack() {
	top = NULL;
}
template<class H>
DynamicStack<H>::~DynamicStack() {
	while (top != NULL) {
		H temp = pop();
	}
}
template<class H>
bool DynamicStack<H>::isEmpty() {
	return top == NULL;
}
template<class H>
void DynamicStack<H>::push(H val) {
	Node<H>* elem = new Node<H>(val);
	if (isEmpty()) {
		top = elem;
	}
	else {
		elem->next = top;
		top = elem;
	}
}
template<class H>
H DynamicStack<H>::pop() {
	if (isEmpty()) {
		cout << "Stack is Empty\n";
		system("PAUSE");
		exit(1);
	}
	else {
		H data = top->item;
		if (top->next == NULL) {
			delete(top);
			top = NULL;
		}
		else {
			Node<H>* ptr = top;
			top = top->next;
			delete(ptr);
		}
		return data;
	}
}
template<class H>
H DynamicStack<H>::peak() {
	if (isEmpty()) {
		cout << "Stack is Empty\n";
		system("PAUSE");
		exit(1);
	}
	else {
		return top->item;
	}
}
template<class H>
void DynamicStack<H>::display() {
	if (isEmpty()) {
		cout << "Stack is Empty\n";
		system("PAUSE");
		exit(1);
	}
	cout << "Stack: ";
	Node<H>* ptr = top;
	while (ptr != NULL) {
		cout << ptr->item << " ";
		ptr = ptr->next;
	}
	cout << endl;
}
void main() {
	DynamicStack<int> x;
	x.push(1);
	x.push(2);
	x.push(3);
	x.push(4);

	x.display();


	cout << "Top element is ";
	cout << x.peak() << endl;


	x.pop();
	x.pop();

	x.display();

	cout << "Top element is ";
	cout << x.peak() << endl;
	x.pop();
	x.pop();
	x.pop();

}