#include <ctime>
#include <iostream>
#include <random>
#include <string>
using namespace std;


struct Node {
    string val; //значение
    Node* next; //указатель на следующий элемент списка

    Node(string _val) : val(_val), next(nullptr) {} //конструкторы
};

struct list {
    Node* first; //указатель на начало списка
    Node* last;  //указатель на конец списка

    list() : first(nullptr), last(nullptr) {} //конструкторы

    bool is_empty() { //функция проверки на пустоту списка
        return first == nullptr;
    }

    void push_back(string _val) { //функция вставки в конец списка
        Node* p = new Node(_val);
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }
    void push_first(string _val) { //функция вставки в начало списка
        Node* p = new Node(_val);
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        p->next = first;
        first = p;
    }

    void push_insert(Node* x, string _val) { //функция вставки элемента в список
                                             //после определенного значения
        Node* p = new Node(_val);
        p->next = x->next;
        x->next = p;
    }

    void print() { //функция печати списка
        if (is_empty())
            return;
        Node* p = first;
        while (p) {
            cout << p->val << " ";
            p = p->next;
        }
        cout << endl;
    }

    int find1(string _val) { //функция поиска элемента в списке по значению
        Node* p = first;
        int pos = 0;
        while (p && p->val != _val) {
            p = p->next;
            pos++;
        }
        return (p && p->val == _val) ? pos
            : -1; //возвращает -1 если элемент не найден
    }

    void remove_first() { //функция удаления из списка первого элемента
        if (is_empty())
            return;
        Node* p = first;
        first = p->next;
        delete p;
    }

    void remove_last() { //функция удаления из списка последнего элемента
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

    void remove(string _val) { //функция удаления из списка элеметка по значению
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
    void remove_index(int index) { //удаление элемента из списка по индексу
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

    Node* operator[](const int index) { //перегрезка оператора для обращения по
                                        //индексу в списке
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
    void clear() { //очистка списка
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
    cout << "Задание 3(методы списка)" << endl; //Задание 3 с функциями
    list l;
    cout << l.is_empty(); //проверка на пустоту списка
    cout << " - Список пуст!" << endl;
    l.push_back("3"); //вставка элемента в конец списка
    l.push_back("123");
    l.push_back("8");
    cout << "Добавили в конец списка 3 элемента:" << endl;
    l.print();         //печать всего списка
    l.push_first("7"); //вставка элемента в начало списка
    cout << "Добавили в начало элемент 7:" << endl;
    l.print();
    cout << "Поиск элемента 123 в нашем списке:" << endl;
    cout << l.find1("123") << " - index найденного элемента"
        << endl; //поиск и вывод индекса элемента в списке
    cout << "Вставим элемент 99 после первого элемента списка:" << endl;
    l.push_insert(l[0], "99"); //вставка элемента после определенного числа с
                               //помощью перегрузки оператора
    l.print();
    cout << l.is_empty() << " - Список не пуст!" << endl;
    cout << "Удалим элемент 123 из списка:" << endl;
    l.remove("123"); //удаление элемента из списка по значению
    l.print();
    cout << "Удалим первый элемент из списка:" << endl;
    l.remove_first(); //удаление из списка первого элемента
    l.print();
    cout << "Удалим последний элемент из списка:" << endl;
    l.remove_last(); //удаление из списка последнего элемента
    l.print();
    cout << "Удалим элемент из списка по индексу 1:" << endl;
    l.remove_index(1); //удаление из списка по индексу
    l.print();
    cout << "Добавим 3 новых элемента в начало списка:" << endl;
    l.push_first("22"); //вставка элемента в начало списка
    l.push_first("30"); //вставка элемента в начало списка
    l.push_first("17"); //вставка элемента в начало списка
    l.print();
    cout << "Выведем элемент по индексу 3:" << endl;
    cout << l[3]->val << endl; //обращение к элементку по индексу в списке
    cout << "Сейчас наш список имеет вид:" << endl;
    l.print();
    cout << "Очистим наш список..." << endl;
    l.clear(); //очистка списка
    cout << "Теперь наш очищенный список имеет вид:" << endl;
    l.print();
    cout << "---------------------"
        << "создание списка через динамический массив со случайными "
        "числами(Задание 1)"
        << endl; //создание списка через динамический массив со случайными
                 //числами(Задание 1)
    list k;
    srand(time(NULL)); // инициализируем рандом
    int n;
    cout << "Введите n: ";
    cin >> n;                    //вводим размер массива
    string* arr = new string[n]; //выделяем память под массив
    for (int i = 0; i < n; i++) { //заполняем случайными числами
        arr[i] = to_string(rand() % 100);
    }
    cout << "Наш массив:" << endl;
    for (int i = 0; i < n; i++) { //вывод в консоль МАССИВА
        cout << arr[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) { //заполнение СПИСКА
        k.push_first(arr[i]);
    }
    cout << "Наш список заполненный через функцию push_first" << endl;
    k.print(); //вывод списка
    cout << "---------------------"
        << "создание списка через динамический массив, но ввод с клавиатуры "
        "(Задание 2)"
        << endl; //создание списка через динамический массив, но ввод с
                 //клавиатуры(Задание 2)
    list z;
    srand(time(NULL)); // инициализируем рандом
    int p;
    cout << "Введите n: ";
    cin >> p;                     //вводим размер массива
    string* arr1 = new string[p]; //выделяем память под массив
    for (int i = 0; i < p; i++) { //заполняем МАССИВ с клавиатуры
        cout << "arr[" << i << "]= ";
        cin >> arr1[i];
        cout << endl;
    }
    cout << "Наш массив:" << endl; //вывод МАССИВА
    for (int i = 0; i < p; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < p; i++) { // Заполнение списка
        z.push_back(arr1[i]);
    }
    cout << "Наш список заполненный через функцию push_back" << endl;
    z.print(); // вывод списка
    return 0;
}