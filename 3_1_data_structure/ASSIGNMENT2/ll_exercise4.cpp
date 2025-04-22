#include <iostream>
using namespace std;

typedef string element;
struct Listnode {
    element data;
    Listnode *next;
};

Listnode *create_node(element data, Listnode *next) {
    Listnode *new_node = new Listnode();
    new_node->data = data;
    new_node->next = next;
    return new_node;
}
// 순회
void my_print(Listnode *head) {
    Listnode *cur = head;
    while (cur != NULL) {
        cout << cur->data << "-> ";
        cur = cur->next;
    }
    cout << "NULL\n";
}
void insert_front(Listnode *&head, element value) {
    head = create_node(value, head);
}
int main() {

    Listnode *head = NULL;
    insert_front(head, "APPLE");
    my_print(head);

    insert_front(head, "KIWI");
    my_print(head);

    insert_front(head, "BANANA");
    my_print(head);
}