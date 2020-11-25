#ifndef INCLUDE_NODE
#include "Node.cpp"
#define INCLUDE_NODE
#endif

class UnderFlow {
};

template <class T>
class SingleList {
private:
	Node<T> *list_head;
	Node<T> *list_tail;
	int size;
public:
	SingleList();
	SingleList(const SingleList &);
	
	//Accessors
	bool isEmpty() const;
	int getSize() const;
	T getFrontValue() const;
	Node<T> *getHead() const;
	Node<T> *getTail() const;
	int countTarget(const T &) const;
	
	//Mutators
	void pushFront(const T &);
	void pushBack(const T &);
	T popFront();
	int eraseTarget(const T &);
	void clearAll();
};

template <class T>
SingleList<T>::SingleList() {
	list_head = nullptr;
	list_tail = nullptr;
	size = 0;
}

template <class T>
SingleList<T>::SingleList(const SingleList<T> & list) {
	list_head = nullptr;
	list_tail = nullptr;
	if(list.isEmpty()) {
		return;
	}
	pushFront(list.getFrontValue());
	for(Node<T> *original = list.getHead()->getNext(), *copy = getHead(); original != nullptr; original = original->getNext(), copy = copy->getNext()) {
		copy->setNext(new Node<T>(original->retrieve(), nullptr));
		list_tail = copy->getNext();
	}
	size = list.getSize();
}

template <class T>
bool SingleList<T>::isEmpty() const {
	return (list_head == nullptr);
}

template <class T>
int SingleList<T>::getSize() const {
	return size;
}

template <class T>
T SingleList<T>::getFrontValue() const {
	if(isEmpty())	{
		throw UnderFlow();
	}
	return getHead()->retrieve();
}

template <class T>
Node<T> *SingleList<T>::getHead() const {
	return list_head;
}

template <class T>
Node<T> *SingleList<T>::getTail() const {
	return list_tail;
}

template <class T>
int SingleList<T>::countTarget(const T & target) const {
	int node_count = 0;
	for(Node<T> *ptr = getHead(); ptr != nullptr; ptr = ptr->getNext()) {
		if(ptr->retrieve() == target) {
			++node_count;
		}
	}
	return node_count;
}

template <class T>
void SingleList<T>::pushFront(const T & ele) {
	if(isEmpty()) {
		Node<T> *tmp_ptr = new Node<T>(ele, nullptr);
		list_head = tmp_ptr;
		list_tail = tmp_ptr;
	} else {
		list_head = new Node<T>(ele, getHead());
	}
	++size;
}

template <class T>
void SingleList<T>::pushBack(const T & ele) {
	if(isEmpty()) {
		Node<T> *tmp_ptr = new Node<T>(ele, nullptr);
		list_head = tmp_ptr;
		list_tail = tmp_ptr;
	} else {
		list_tail->setNext(new Node<T>(ele, nullptr));
		list_tail = getTail()->getNext();
	}
	++size;
}

template <class T>
T SingleList<T>::popFront() {
	if(isEmpty()) {
		throw UnderFlow();
	}
	T e = getFrontValue();
	Node<T> *tmp_ptr = list_head;
	list_head = list_head->getNext();
	delete tmp_ptr;
	--size;
	if(list_head == nullptr) {
		list_tail = nullptr;
	}
	return e;
}

template <class T>
int SingleList<T>::eraseTarget(const T & target) {
	if(isEmpty()) {
		throw UnderFlow();
	}
	int erase_count = 0;
	Node<T> *pre_ptr = nullptr;
	for(Node<T> *ptr = getHead(); ptr != nullptr; ptr = ptr->getNext()) {
		while(ptr->retrieve() == target) {
			if(ptr->getNext() != nullptr) {
				Node<T> *tmp_ptr = ptr->getNext();
				ptr->setElement(tmp_ptr->retrieve());
				ptr->setNext(tmp_ptr->getNext()); 
				tmp_ptr->setNext(nullptr);
				delete tmp_ptr;
				--size;
				++erase_count;
			} else {
				if(pre_ptr == nullptr) {
					list_head = nullptr;
					list_tail = nullptr;
					delete ptr;
					--size;
					++erase_count;
				} else {
					pre_ptr->setNext(nullptr);
					delete ptr;
					--size;
					++erase_count;
					list_tail = pre_ptr;
				}
				return erase_count;
			}
		}
		pre_ptr = ptr;
	}
	return erase_count;
}

template <class T>
void SingleList<T>::clearAll() {
    std::cout << "isEmpty: " << isEmpty() << std::endl;
	if(isEmpty()) {
		return;
	}
	std::cout << "this!" << std::endl;
	Node<T> *ptr = getHead();
	while(ptr != nullptr) {
		Node<T> *tmp_ptr = ptr;
		ptr = ptr->getNext();
		tmp_ptr->setNext(nullptr);
		delete tmp_ptr;
		list_head = ptr;
		--size;
	}
	list_tail = nullptr;
}
	