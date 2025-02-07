#include <iostream>
#include <windows.h>

using namespace std;

struct Book {
    int id = 0;
    string name;
    string author;
    double price = 0;

};

void Input_Book(Book *bk) { // �� ���� ��������� �����
    cout << "   ������� �������� �����:";
    cin >> bk->name; // -> - ��� �� �� �����, ��� � bk.name, ������ ��� ������� � ������, � �� ��� ����� ��������
    cout << "   ������� ������ �����:";
    cin >> bk->author;
    cout << "   ������� ���� �����:";
    cin >> bk->price;
}

void Output_Book(Book *list, int n) {
    for (int i = 0; i < n; i++) {
        cout << "����� � " << i + 1 << "\n";
        cout << "   id: " << list[i].id << "\n";
        cout << "   ��������: " << list[i].name << "\n";
        cout << "   �����: " << list[i].author << "\n";
        cout << "   ����: " << list[i].price << "\n";
    }
}

double Absolute_Amount_Price(Book *list, int n) {
    double amount = 0;
    for (int i = 0; i < n; i++) {
        amount += list[i].price;
    }
    return amount;
}

double Average_Amount_Price(Book *list, int n) {
    double amount = 0;
    for (int i = 0; i < n; i++) {
        amount += list[i].price;
    }
    return amount / n;
}

Book *Search_By_ID(Book *list, int n, int id) {
    for (int i = 0; i < n; i++) {
        if (id == list[i].id) {
            return &list[i]; // ���������� ����� �������� �������� ������ (������ �����)
        }
    }
}

void Replacement_Book(Book *search_book) { // ��������� ����� �� ������� ����
    cout << "   ������� ����� �������� �����:";
    cin >> search_book->name;
    cout << "   ������� ������ ������ �����:";
    cin >> search_book->author;
    cout << "   ������� ����� ���� �����:";
    cin >> search_book->price;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "���������� ����:";
    int n;
    cin >> n;

    Book *list = new Book[n]; // ������, ���������� ������ ������� ���� Book (������ � ����)

    for (int i = 0; i < n; i++) {
        cout << "����� � " << i + 1 << "\n";
        list[i].id = i + 1; // ����� ������ ���������� id
        Input_Book(&list[i]); // ������� ������ ����� �������� ������, ��� ��� ����� ������� ������ ����������, �� �� �������� ��� ���������� ������
        cout << "=========================" << "\n";
    }

    Output_Book(list, n);

    cout << "����� ��������� ����: " << Absolute_Amount_Price(list, n) << "\n";
    cout << "������� ��������� ����: " << Average_Amount_Price(list, n) << "\n";

    cout << "������� id �����, ������� ���������� ��������:";
    int id;
    cin >> id;
    Replacement_Book(Search_By_ID(list, n, id)); // � ������� Replacement_Book ��������� ��������� ������ ������� Search_By_ID, �� ���� ����� ������ �����

    Output_Book(list, n);

    delete[]list; // ������ ����
}