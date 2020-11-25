template <class T>
class Node {
private:
	T element;
	Node *next_node;
public:
	Node(T = NULL, Node<T> * = nullptr);
	T retrieve() const;
	Node<T> *getNext() const;
	void setElement(const T &);
	void setNext(Node<T> *);
};

template <class T>
Node<T>::Node(T ele, Node *next_ptr) {
	element = ele;
	next_node = next_ptr;
}

template <class T>
T Node<T>::retrieve() const {
	return element;
}

template <class T>
Node<T> *Node<T>::getNext() const {
	return next_node;
}

template <class T>
void Node<T>::setElement(const T & ele) {
	element = ele;
}

template <class T>
void Node<T>::setNext(Node<T> *next_ptr) {
	next_node = next_ptr;
}