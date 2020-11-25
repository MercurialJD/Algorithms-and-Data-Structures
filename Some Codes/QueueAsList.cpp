#ifndef INCLUDE_SINGLE_LIST
#include "SingleList.cpp"
#define INCLUDE_SINGLE_LIST
#endif

template <class T>
class QueueAsList {
private:
	SingleList<T> list;
public:
	QueueAsList(SingleList<T> & = new SingleList<T>());
	bool isEmpty() const;
	T getFrontValue() const;
	void push(T const &);
	T pop();
};

template <class T>
QueueAsList<T>::QueueAsList(SingleList<T> & input_list) {
	list = input_list;
}

template <class T>
bool QueueAsList<T>::isEmpty() const {
	return list.isEmpty();
}

template <class T>
T QueueAsList<T>::getFrontValue() const {
	return list.getFrontValue;
}

template <class T>
void QueueAsList<T>::push(T const & ele) {
	list.pushBack(ele);
}

template <class T>
T QueueAsList<T>::pop() {
	if(isEmpty()) {
		throw UnderFlow();
	}
	return list.popFront();
}
