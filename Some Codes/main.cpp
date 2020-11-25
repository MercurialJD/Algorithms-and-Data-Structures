#include <iostream>
#include "TreeAsList.cpp"

int main() {
	TreeAsList<int> tree1(1, nullptr);
	tree1.insertChild(2);
	tree1.insertChild(3);
	tree1.insertChild(4);
	(tree1.getChild(0))->insertChild(5);
	(tree1.getChild(0))->insertChild(6);
    (tree1.getChild(1))->insertChild(7);
    ((tree1.getChild(1))->getChild(0))->insertChild(8);
	(tree1.getChild(2))->insertChild(9);
	(tree1.getChild(2))->insertChild(10);
	SingleList<int> BFS;
	tree1.BFSToList(&BFS);
	std::cout << (tree1.getChild(1))->retrieve() << std::endl;
	for(int i = 0; i < 10; i++) {
		std::cout << BFS.popFront() << " " << std::endl;
	}
	std::cout << tree1.getDegree() << tree1.getChild(1)->isRoot() << tree1.getChild(2)->isLeaf();
	return 0;
}