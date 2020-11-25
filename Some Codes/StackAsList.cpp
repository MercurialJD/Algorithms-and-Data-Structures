#ifndef INCLUDE_SINGLE_LIST
#include "SingleList.cpp"
#define INCLUDE_SINGLE_LIST
#endif

template <class T>
class StackAsList {
private:
	SingleList<T> list;
public:
	StackAsList(SingleList<T> & = new SingleList<T>());
	bool isEmpty() const;
	T getFrontValue() const;
	void push(T const &);
	T pop();
};

template <class T>
StackAsList<T>::StackAsList(SingleList<T> & input_list) {
	list = input_list;
}

template <class T>
bool StackAsList<T>::isEmpty() const {
	return list.isEmpty();
}

template <class T>
T StackAsList<T>::getFrontValue() const {
	return list.getFrontValue;
}

template <class T>
void StackAsList<T>::push(T const & ele) {
	list.pushFront(ele);
}

template <class T>
T StackAsList<T>::pop() {
	if(isEmpty()) {
		throw UnderFlow();
	}
	return list.popFront();
}
