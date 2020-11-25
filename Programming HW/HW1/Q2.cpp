#include <iostream>

class Node {
public:
    explicit Node(int num = 1, Node *next_ptr = nullptr);
    int number;
    Node *next_node;
};

Node::Node(int num, Node *next_ptr) {
    number = num;
    next_node = next_ptr;
}

class List {
public:
    explicit List(int n = 1);
    Node *head();
    Node *getNextNode();
    void gotoNextNode();
    int getCurrentNodeValue();
    void deleteNextNode();
    int getCurrentLength();
private:
    Node *list_head;
    Node *current_node;
    int current_length;
};

List::List(int n) {
    int current_number = 1;
    list_head = new Node(current_number, list_head);
    Node *new_ptr, *pre_ptr = list_head;
    while(++current_number <= n) {
        new_ptr = new Node(current_number, list_head);
        pre_ptr->next_node = new_ptr;
        pre_ptr = new_ptr;
    }
    current_length = n;
    current_node = list_head;
}

Node *List::head() {
    return list_head;
}

Node *List::getNextNode() {
    return current_node->next_node;
}

void List::gotoNextNode() {
    current_node = current_node->next_node;
}

int List::getCurrentNodeValue() {
    return current_node->number;
}

void List::deleteNextNode() {
    Node *next_node_ptr = getNextNode();
    current_node->next_node = next_node_ptr->next_node;
    next_node_ptr->next_node = nullptr;
    delete(next_node_ptr);
    current_length--;
}

int List::getCurrentLength() {
    return current_length;
}

void playground(List *play_list, int m, int n) {
    int round = 1;
    while(round < m) {
        int i;
        for(i = 0; i < n - round - 1 - 4 + 1; i += 4) {
            play_list->gotoNextNode();
            play_list->gotoNextNode();
            play_list->gotoNextNode();
            play_list->gotoNextNode();
        }   //Loop unrolling
        while(i++ < n - round - 1)
            play_list->gotoNextNode();
        play_list->deleteNextNode();
        play_list->gotoNextNode();
        round++;
    }
}

int main() {
    int m, n;
    std::cin >> m >> n;
    List game_list = List(m);
    playground(&game_list, m, n);
    std::cout << game_list.getCurrentNodeValue();
}