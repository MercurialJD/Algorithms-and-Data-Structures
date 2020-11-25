#ifndef INCLUDE_STACK_AS_LIST
#include "StackAsList.cpp"
#define INCLUDE_STACK_AS_LIST
#endif
#ifndef INCLUDE_QUEUE_AS_LIST
#include "QueueAsList.cpp"
#define INCLUDE_QUEUE_AS_LIST
#endif

template <class T>
class TreeAsList {
private:
	T element;
	TreeAsList *parent_node;
	SingleList<TreeAsList *> children;
public:
	TreeAsList(T const & = T(), TreeAsList * = nullptr);
	
	//Accessors
	int getDegree() const;
	bool isRoot() const;
	bool isLeaf() const;
	T retrieve() const;
	TreeAsList *getParent() const;
	TreeAsList *getChild(int) const;
	int getHeight() const;
	int getSize() const;
	void BFSToList(SingleList<T> *) const;
	void DFSToList(SingleList<T> *) const;  //Here DFS is implemented by stack, but also can be implemented by recursive
	                                        //Which is listed below in the comment.
	
	//Mutators
	void setParent(TreeAsList *);
	void insertChild(T const &);
	void attach(TreeAsList *);
	void detach();
};

template <class T>
TreeAsList<T>::TreeAsList(T const & ele, TreeAsList *parent_ptr) {
	element = ele;
	setParent(parent_ptr);
}

template <class T>
int TreeAsList<T>::getDegree()	const {
	return children.getSize();
}

template <class T>
bool TreeAsList<T>::isRoot() const {
	return (getParent() == nullptr);
}

template <class T>
bool TreeAsList<T>::isLeaf() const {
	return (getDegree() == 0);
}

template <class T>
T TreeAsList<T>::retrieve() const {
	return element;
}

template <class T>
TreeAsList<T> *TreeAsList<T>::getParent() const {
	return parent_node;
}

template <class T>
TreeAsList<T> *TreeAsList<T>::getChild(int n) const {
	if(n < 0 || n >= getDegree()) {
		return nullptr;
	}
	Node<TreeAsList<T> *> *node_ptr = children.getHead();
	for(int i = 0; i < n; i++) {
		node_ptr = node_ptr->getNext();
	}
	return node_ptr->retrieve();
}	

template <class T>
int TreeAsList<T>::getHeight() const {
	int height = 0;
	for(Node<TreeAsList<T> *> *node_ptr = children.getHead(); node_ptr != nullptr; node_ptr = node_ptr->getNext()) {
		height = std::max(height, 1 + node_ptr->retrieve()->getHeight());
		}
	return height;
}

template <class T>
int TreeAsList<T>::getSize() const {
	int size = 1;
	for(Node<TreeAsList<T> *> *node_ptr = children.getHead(); node_ptr != nullptr; node_ptr = node_ptr->getNext()) {
		size += node_ptr->retrieve()->getSize();
	}
	return size;
}

template <class T>
void TreeAsList<T>::BFSToList(SingleList<T> *list) const {
    TreeAsList this_node = *this;
    TreeAsList *this_ptr = &this_node;
	QueueAsList<TreeAsList<T> *> tmp_store(*(new SingleList<TreeAsList<T> *>));
	tmp_store.push(this_ptr);
	while(!tmp_store.isEmpty()) {
		TreeAsList<T> *poped_node = tmp_store.pop();
		list->pushBack(poped_node->retrieve());
		if(!poped_node->isLeaf()) {
			for(Node<TreeAsList<T> *> *child_node = poped_node->children.getHead(); child_node != nullptr; child_node = child_node->getNext()) {
				tmp_store.push(child_node->retrieve());
			}
		}
	}
}

template <class T>
void TreeAsList<T>::DFSToList(SingleList<T> *list) const {
    TreeAsList this_node = *this;
    TreeAsList *this_ptr = &this_node;
    StackAsList<TreeAsList<T> *> tmp_store(*(new SingleList<TreeAsList<T> *>));
    tmp_store.push(this_ptr);
    while(!tmp_store.isEmpty()) {
        TreeAsList<T> *poped_node = tmp_store.pop();
        list->pushBack(poped_node->retrieve());
        if(!poped_node->isLeaf()) {
            StackAsList<TreeAsList<T> *> reverse_nodes(*(new SingleList<TreeAsList<T> *>));
            int node_count = 0;
            for(Node<TreeAsList<T> *> *child_node = poped_node->children.getHead(); child_node != nullptr; child_node = child_node->getNext()) {
                reverse_nodes.push(child_node->retrieve());
                node_count++;
            }
            for(int i = 0; i < node_count; ++i) {
                TreeAsList<T> *poped = reverse_nodes.pop();
                tmp_store.push(poped);
            }
        }
    }
}

/*
template <class T>
void TreeAsList<T>::DFSToList(SingleList<T> *list) const {
    TreeAsList this_node = *this;
    TreeAsList *this_ptr = &this_node;
    list->pushBack(this_ptr->retrieve());
    if(!this_ptr->isLeaf()) {
        for(Node<TreeAsList<T> *> *child_node = this_ptr->children.getHead(); child_node != nullptr; child_node = child_node->getNext()) {
            (child_node->retrieve())->DFSToList(list);
        }
    }
}
*/

template <class T>
void TreeAsList<T>::setParent(TreeAsList<T> *parent_ptr) {
	parent_node = parent_ptr;
}

template <class T>
void TreeAsList<T>::insertChild(T const & ele) {
    TreeAsList<T> *new_tree_node = new TreeAsList(ele, this);
	children.pushBack(new_tree_node);
}

template <class T>
void TreeAsList<T>::attach(TreeAsList<T> *subtree) {
	if(!subtree->isRoot()) {
		subtree->detach();
	}
	subtree->setParent(this);
	children.pushBack(subtree);
}

template <class T>
void TreeAsList<T>::detach() {
	if(isRoot()) {
		return;
	}
	getParent()->children.eraseTarget(this);
	setParent(nullptr);
}