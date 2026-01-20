#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *next;
    Node *prev;
    Node(int val)
    {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};
void insert_at_tail(Node *&head, int val)
{
    Node *newNode = new Node(val);
    if (head == nullptr)
    {
        head = newNode;
        return;
    }
    Node *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
}
void middle_slow_and_fast(Node *head)
{
    if (head == nullptr)
        return;
    Node *slow = head;
    Node *fast = head;
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    cout << "Middle element: " << slow->data << endl;
}
void middle(Node *head)
{
    if (head == nullptr)
        return;
    Node *current = head;
    int count = 0;
    while (current != nullptr)
    {
        count++;
        current = current->next;
    }
    int mid = count / 2;
    current = head;
    for (int i = 0; i < mid; i++)
    {
        current = current->next;
    }
    cout << "Middle element: " << current->data << endl;
}
void display(Node *head)
{
    Node *current = head;
    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}
int main()
{
    Node *head = new Node(10);
    Node *second = new Node(20);
    Node *third = new Node(30);

    head->next = second;
    second->prev = head;
    second->next = third;
    third->prev = second;
    display(head);
    insert_at_tail(head, 40);
    insert_at_tail(head, 50);
    display(head);
    middle(head);
    middle_slow_and_fast(head);
    return 0;
}
