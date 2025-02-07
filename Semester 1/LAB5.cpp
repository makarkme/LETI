#include <iostream>
#include <windows.h>

using namespace std;

struct Book {
    int id = 0;
    string name;
    string author;
    double price = 0;

};

void Input_Book(Book *bk) { // На вход принимаем адрес
    cout << "   Введите название книги:";
    cin >> bk->name; // -> - это то же самое, что и bk.name, только для адресов в памяти, а не для самих значений
    cout << "   Введите автора книги:";
    cin >> bk->author;
    cout << "   Введите цену книги:";
    cin >> bk->price;
}

void Output_Book(Book *list, int n) {
    for (int i = 0; i < n; i++) {
        cout << "Книга № " << i + 1 << "\n";
        cout << "   id: " << list[i].id << "\n";
        cout << "   Название: " << list[i].name << "\n";
        cout << "   Автор: " << list[i].author << "\n";
        cout << "   Цена: " << list[i].price << "\n";
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
            return &list[i]; // возвращаем адрес искомого элемента списка (нужной книги)
        }
    }
}

void Replacement_Book(Book *search_book) { // Принимаем адрес из функции выше
    cout << "   Введите новое название книги:";
    cin >> search_book->name;
    cout << "   Введите нового автора книги:";
    cin >> search_book->author;
    cout << "   Введите новую цену книги:";
    cin >> search_book->price;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Количество книг:";
    int n;
    cin >> n;

    Book *list = new Book[n]; // Список, содержащий только объекты типа Book (создаём в куче)

    for (int i = 0; i < n; i++) {
        cout << "Книга № " << i + 1 << "\n";
        list[i].id = i + 1; // Сразу создаём уникальный id
        Input_Book(&list[i]); // Передаём именно адрес значения списка, так как иначе функция просто выполнится, но не поменяет наш конкретный список
        cout << "=========================" << "\n";
    }

    Output_Book(list, n);

    cout << "Общая стоимость книг: " << Absolute_Amount_Price(list, n) << "\n";
    cout << "Средняя стоимость книг: " << Average_Amount_Price(list, n) << "\n";

    cout << "Введите id книги, которую необходимо изменить:";
    int id;
    cin >> id;
    Replacement_Book(Search_By_ID(list, n, id)); // В функцию Replacement_Book передаётся результат работы функции Search_By_ID, то есть адрес нужной книги

    Output_Book(list, n);

    delete[]list; // Чистим кучу
}