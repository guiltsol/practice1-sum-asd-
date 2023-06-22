#include <ctime>
#include <iostream>
#include <random>
#include <string>
using namespace std;


struct Node {
    string val; //��������
    Node* next; //��������� �� ��������� ������� ������

    Node(string _val) : val(_val), next(nullptr) {} //������������
};

struct list {
    Node* first; //��������� �� ������ ������
    Node* last;  //��������� �� ����� ������

    list() : first(nullptr), last(nullptr) {} //������������

    bool is_empty() { //������� �������� �� ������� ������
        return first == nullptr;
    }

    void push_back(string _val) { //������� ������� � ����� ������
        Node* p = new Node(_val);
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }
    void push_first(string _val) { //������� ������� � ������ ������
        Node* p = new Node(_val);
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        p->next = first;
        first = p;
    }

    void push_insert(Node* x, string _val) { //������� ������� �������� � ������
                                             //����� ������������� ��������
        Node* p = new Node(_val);
        p->next = x->next;
        x->next = p;
    }

    void print() { //������� ������ ������
        if (is_empty())
            return;
        Node* p = first;
        while (p) {
            cout << p->val << " ";
            p = p->next;
        }
        cout << endl;
    }

    int find1(string _val) { //������� ������ �������� � ������ �� ��������
        Node* p = first;
        int pos = 0;
        while (p && p->val != _val) {
            p = p->next;
            pos++;
        }
        return (p && p->val == _val) ? pos
            : -1; //���������� -1 ���� ������� �� ������
    }

    void remove_first() { //������� �������� �� ������ ������� ��������
        if (is_empty())
            return;
        Node* p = first;
        first = p->next;
        delete p;
    }

    void remove_last() { //������� �������� �� ������ ���������� ��������
        if (is_empty())
            return;
        if (first == last) {
            remove_first();
            return;
        }
        Node* p = first;
        while (p->next != last)
            p = p->next;
        p->next = nullptr;
        delete last;
        last = p;
    }

    void remove(string _val) { //������� �������� �� ������ �������� �� ��������
        if (is_empty())
            return;
        if (first->val == _val) {
            remove_first();
            return;
        }
        else if (last->val == _val) {
            remove_last();
            return;
        }
        Node* slow = first;
        Node* fast = first->next;
        while (fast && fast->val != _val) {
            fast = fast->next;
            slow = slow->next;
        }
        if (!fast) {
            cout << "This element does not exist" << endl;
            return;
        }
        slow->next = fast->next;
        delete fast;
    }
    void remove_index(int index) { //�������� �������� �� ������ �� �������
        if (is_empty() || index < 0)
            return;
        if (index == 0) {
            remove_first();
            return;
        }
        int i = 0;
        Node* p = first;
        Node* prev = NULL;
        while (p != NULL && i < index) {
            prev = p;
            p = p->next;
            i++;
        }
        if (p == NULL)
            return;
        prev->next = p->next;
        delete p;
    }

    Node* operator[](const int index) { //���������� ��������� ��� ��������� ��
                                        //������� � ������
        if (is_empty())
            return nullptr;
        Node* p = first;
        for (int i = 0; i < index; i++) {
            p = p->next;
            if (!p)
                return nullptr;
        }
        return p;
    }
    void clear() { //������� ������
        Node* current = first;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        first = nullptr;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "������� 3(������ ������)" << endl; //������� 3 � ���������
    list l;
    cout << l.is_empty(); //�������� �� ������� ������
    cout << " - ������ ����!" << endl;
    l.push_back("3"); //������� �������� � ����� ������
    l.push_back("123");
    l.push_back("8");
    cout << "�������� � ����� ������ 3 ��������:" << endl;
    l.print();         //������ ����� ������
    l.push_first("7"); //������� �������� � ������ ������
    cout << "�������� � ������ ������� 7:" << endl;
    l.print();
    cout << "����� �������� 123 � ����� ������:" << endl;
    cout << l.find1("123") << " - index ���������� ��������"
        << endl; //����� � ����� ������� �������� � ������
    cout << "������� ������� 99 ����� ������� �������� ������:" << endl;
    l.push_insert(l[0], "99"); //������� �������� ����� ������������� ����� �
                               //������� ���������� ���������
    l.print();
    cout << l.is_empty() << " - ������ �� ����!" << endl;
    cout << "������ ������� 123 �� ������:" << endl;
    l.remove("123"); //�������� �������� �� ������ �� ��������
    l.print();
    cout << "������ ������ ������� �� ������:" << endl;
    l.remove_first(); //�������� �� ������ ������� ��������
    l.print();
    cout << "������ ��������� ������� �� ������:" << endl;
    l.remove_last(); //�������� �� ������ ���������� ��������
    l.print();
    cout << "������ ������� �� ������ �� ������� 1:" << endl;
    l.remove_index(1); //�������� �� ������ �� �������
    l.print();
    cout << "������� 3 ����� �������� � ������ ������:" << endl;
    l.push_first("22"); //������� �������� � ������ ������
    l.push_first("30"); //������� �������� � ������ ������
    l.push_first("17"); //������� �������� � ������ ������
    l.print();
    cout << "������� ������� �� ������� 3:" << endl;
    cout << l[3]->val << endl; //��������� � ��������� �� ������� � ������
    cout << "������ ��� ������ ����� ���:" << endl;
    l.print();
    cout << "������� ��� ������..." << endl;
    l.clear(); //������� ������
    cout << "������ ��� ��������� ������ ����� ���:" << endl;
    l.print();
    cout << "---------------------"
        << "�������� ������ ����� ������������ ������ �� ���������� "
        "�������(������� 1)"
        << endl; //�������� ������ ����� ������������ ������ �� ����������
                 //�������(������� 1)
    list k;
    srand(time(NULL)); // �������������� ������
    int n;
    cout << "������� n: ";
    cin >> n;                    //������ ������ �������
    string* arr = new string[n]; //�������� ������ ��� ������
    for (int i = 0; i < n; i++) { //��������� ���������� �������
        arr[i] = to_string(rand() % 100);
    }
    cout << "��� ������:" << endl;
    for (int i = 0; i < n; i++) { //����� � ������� �������
        cout << arr[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) { //���������� ������
        k.push_first(arr[i]);
    }
    cout << "��� ������ ����������� ����� ������� push_first" << endl;
    k.print(); //����� ������
    cout << "---------------------"
        << "�������� ������ ����� ������������ ������, �� ���� � ���������� "
        "(������� 2)"
        << endl; //�������� ������ ����� ������������ ������, �� ���� �
                 //����������(������� 2)
    list z;
    srand(time(NULL)); // �������������� ������
    int p;
    cout << "������� n: ";
    cin >> p;                     //������ ������ �������
    string* arr1 = new string[p]; //�������� ������ ��� ������
    for (int i = 0; i < p; i++) { //��������� ������ � ����������
        cout << "arr[" << i << "]= ";
        cin >> arr1[i];
        cout << endl;
    }
    cout << "��� ������:" << endl; //����� �������
    for (int i = 0; i < p; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < p; i++) { // ���������� ������
        z.push_back(arr1[i]);
    }
    cout << "��� ������ ����������� ����� ������� push_back" << endl;
    z.print(); // ����� ������
    return 0;
}