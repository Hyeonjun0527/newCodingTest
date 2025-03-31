#include <iostream>
using namespace std;

typedef string element;
struct Listnode {
    element data;
    Listnode *link;
};

Listnode *create_node(element data, Listnode *link) {
    Listnode *new_node = new Listnode();
    new_node->data = data;
    new_node->link = link;
    return new_node;
}
// 순회회
void my_print(Listnode *cur, Listnode *head) {
    cur = head;
    while (cur != NULL) {
        cout << cur->data << "-> ";
        cur = cur->link; // 다음으로 가.
    }
    cout << "NULL\n";
}
// 병합합
void sum_linklist(Listnode *a,
                  Listnode *b) { // a는 list1의 포인터, b는 list2의 포인터터
    while (a->link != NULL) {
        a = a->link;
    }
    a->link = b;
}
// 역순 순회
// https://chatgpt.com/c/67ea299a-2848-8006-a0ef-df284d24c2e6?model=o3-mini-high#
void reverse_print(Listnode *cur, Listnode *end) {
    cur = end;
    Listnode *before = new Listnode();

    while (before != NULL) {
    }
}

int main() {

    Listnode *head = NULL;
    Listnode *cur = NULL;
    int i;
    string initial_value = "A0";

    for (i = 0; i < 100; i++) {
        Listnode *new_node = create_node(initial_value, NULL);
        initial_value = "A" + to_string(i + 1);
        if (head == NULL) {
            head = new_node;
            cur = head;
        } else {
            cur->link = new_node;
            cur = new_node;
        }
    }
    initial_value = "B0";
    Listnode *head2 = NULL;
    Listnode *cur2 = NULL;
    for (i = 0; i < 100; i++) {
        Listnode *new_node = create_node(initial_value, NULL);
        initial_value = "B" + to_string(i + 1);
        if (head2 == NULL) {
            head2 = new_node;
            cur2 = head2;
        } else {
            cur2->link = new_node;
            cur2 = new_node;
        }
    }

    // 일단 헤드로 가 그리고, 순회해
    // my_print(cur, head);
    sum_linklist(cur, head2);
    my_print(cur2, head);
}