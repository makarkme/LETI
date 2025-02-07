#include <iostream>
#include <windows.h>
#include <fstream>
#include <algorithm>

using namespace std;

const int SIZE_GENDER = 7;
const int SIZE_GRADES = 8;
const int SIZE_ARRAY_STUDENT = 6;
const int SIZE_FULLNAME = 100;

const int SIZE_ARRAY_TEACHER = 2;
const int SIZE_ACADEMICDEGREE = 50;
const int SIZE_DISCIPLINE = 200;
const int SIZE_EMAIL = 30;
const int SIZE_GROUPNUMBER = 100000;
const int SIZE_REQUESTTEACHER = 50;

struct Student {
    char fullName[SIZE_FULLNAME]{};
    char gender[SIZE_GENDER]{};
    int groupNumber{};
    int groupListNumber{};
    float grades[SIZE_GRADES]{};
    float averageGrades{};
    int id{};
};

struct Teacher { // ИДЗ №4
    char fullName[SIZE_FULLNAME]{};
    char gender[SIZE_GENDER]{};
    int age{};
    char academicDegree[SIZE_ACADEMICDEGREE]{};
    char discipline[SIZE_DISCIPLINE]{};
    char email[SIZE_EMAIL]{};
    char groupNumber[SIZE_GROUPNUMBER]{};
};

void CreateEntry(Student &arrayStudent) {
    ofstream fout("students.txt", ios::app); // Открытие файла (дозаписывание)

    cout << "Введите ФИО студента: \n";
    cin.ignore();
    cin.getline(arrayStudent.fullName, SIZE_FULLNAME);
    fout << "ФИО: " << arrayStudent.fullName << "\n";

    cout << "Введите пол студента: \n";
    cin >> arrayStudent.gender;
    fout << "Пол: " << arrayStudent.gender << "\n";

    cout << "Введите номер группы студента: \n";
    cin >> arrayStudent.groupNumber;
    fout << "Номер группы: " << arrayStudent.groupNumber << "\n";

    cout << "Введите номер студента в группе: \n";
    cin >> arrayStudent.groupListNumber;
    fout << "Номер в группе: " << arrayStudent.groupListNumber << "\n";

    cout << "Введите оценки студента: \n";
    fout << "Оценки: ";
    for (int i = 0; i < SIZE_GRADES; ++i) {
        cin >> arrayStudent.grades[i];
        fout << arrayStudent.grades[i] << " ";

        arrayStudent.averageGrades += arrayStudent.grades[i] / 8;
    }

    fout << "Средний балл: " << arrayStudent.averageGrades << "\n";
    fout << "-------------------------------------------------------------- \n";

    fout.close();
}

void CreateEntry(Teacher &arrayTeacher) { // Используем перегрузку функции
    cout << "Введите ФИО преподавателя: \n";
    cin.ignore();
    cin.getline(arrayTeacher.fullName, SIZE_FULLNAME);

    cout << "Введите пол преподавателя: \n";
    cin >> arrayTeacher.gender;

    cout << "Введите возраст преподавателя: \n";
    cin >> arrayTeacher.age;

    cout << "Введите учёную степень преподавателя: \n";
    cin.ignore();
    cin.getline(arrayTeacher.academicDegree, SIZE_ACADEMICDEGREE);

    cout << "Введите наименование дисциплины преподавателя: \n";
    cin.getline(arrayTeacher.discipline, SIZE_DISCIPLINE);

    cout << "Введите email преподавателя: \n";
    cin >> arrayTeacher.email;

    cout << "Введите номер группы, у которой преподаватель ведёт занятия: \n";
    cin >> arrayTeacher.groupNumber;
}

void PrintEntry(Student &arrayStudent) { // Принимаем ссылку на 1 конкретного студента
    cout << "ФИО: " << arrayStudent.fullName << "\n";
    cout << "Пол: " << arrayStudent.gender << "\n";
    cout << "Номер группы: " << arrayStudent.groupNumber << "\n";
    cout << "Номер в группе: " << arrayStudent.groupListNumber << "\n";
    cout << "Оценки: ";
    for (int i = 0; i < SIZE_GRADES; ++i) {
        cout << arrayStudent.grades[i] << " ";
    }
    cout << "\n";
    cout << "Средний балл: " << arrayStudent.averageGrades << "\n";
    cout << "ID: " << arrayStudent.id << "\n";
}

void PrintEntry(Teacher &arrayTeacher) {
    cout << "ФИО: " << arrayTeacher.fullName << "\n";
    cout << "Пол: " << arrayTeacher.gender << "\n";
    cout << "Возраст: " << arrayTeacher.age << "\n";
    cout << "Учёная степень: " << arrayTeacher.academicDegree << "\n";
    cout << "Наименование дисциплины: " << arrayTeacher.discipline << "\n";
    cout << "Email: " << arrayTeacher.email << "\n";
    cout << "Номер группы: " << arrayTeacher.groupNumber << "\n";
}

void SortByGroupNumber(Student arrayStudent[], int groupNumber) { // Создаём копию массива студентов, работаем с ним
    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
        if (arrayStudent[i].groupNumber == groupNumber) {
            PrintEntry(arrayStudent[i]);
        }
    }
}

void TopStudents(Student arrayStudent[]) { // Сортировка пузырьком
    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
        for (int j = 0; j < SIZE_ARRAY_STUDENT - i - 1; ++j) {
            if (arrayStudent[j].averageGrades < arrayStudent[j + 1].averageGrades) {
                swap(arrayStudent[j], arrayStudent[j + 1]);
            }
        }
    }

    cout << "Топ студентов: \n";
    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
        cout << arrayStudent[i].fullName << " " << "(" << arrayStudent[i].averageGrades << ")\n";
    }
}

void AboutGenders(Student arrayStudent[]) {
    int male = 0;
    int female = 0;
    string strMale = "Мужской";
    string strFemale = "Женский";
    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
        if (arrayStudent[i].gender == strMale) {
            male += 1;
        }
        if (arrayStudent[i].gender == strFemale) {
            female += 1;
        }
    }
    cout << "Мужчин: " << male << "\n";
    cout << "Женщин: " << female << "\n";
}

void AboutGradesStudents(Student arrayStudent[]) {
    int array_3[SIZE_ARRAY_STUDENT]{};
    int array_45[SIZE_ARRAY_STUDENT]{};
    int array_5[SIZE_ARRAY_STUDENT]{};

    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {

        bool has_3 = FALSE;
        bool has_4 = FALSE;
        bool has_5 = FALSE;

        for (int j = 0; j < SIZE_GRADES; ++j) {
            if (arrayStudent[i].grades[j] == 3) {
                has_3 = TRUE;
            }
            if (arrayStudent[i].grades[j] == 4) {
                has_4 = TRUE;
            }
            if (arrayStudent[i].grades[j] == 5) {
                has_5 = TRUE;
            }
        }

        if (has_3 == TRUE) {
            array_3[i] = 1;
        } else if (has_4 == TRUE and has_5 == TRUE) {
            array_45[i] = 1;
        } else if (has_4 == FALSE and has_5 == TRUE) {
            array_5[i] = 1;
        }
    }

    cout << "Студенты, которые учатся на тройки: \n";
    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
        if (array_3[i] == 1) {
            PrintEntry(arrayStudent[i]);
        }
    }

    cout << "Студенты, которые учатся на 4 и 5: \n";
    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
        if (array_45[i] == 1) {
            PrintEntry(arrayStudent[i]);
        }
    }

    cout << "Студенты, которые учатся только на 5: \n";
    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
        if (array_5[i] == 1) {
            PrintEntry(arrayStudent[i]);
        }
    }
}

void SortByGroupListNumber(Student arrayStudent[], int groupListNumber) {
    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
        if (arrayStudent[i].groupListNumber == groupListNumber) {
            PrintEntry(arrayStudent[i]);
        }
    }
}

int main() {

    // Русифицируем консольный ввод/вывод
    // P.S. У каждого индивидуально, поэтому крутите значения кодировок здесь и в idle сами.
    // Если у вам win10/win11 + Clion с кодировкой win1251, то всё будет норм.
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Если у вас Clion, то файл будет лежать в: "C:\...\CLionProjects\(название проекта)\cmake-build-debug"
    // P.S. Программа сама создаёт и чистит файл
    ifstream fileCheck("students.txt"); // Проверка наличия файла
    if (fileCheck.good()) {
        ofstream outputFile("students.txt", ios::trunc); // Очистка файла
        outputFile.close();
        fileCheck.close();
    } else {
        cout << "Файл отсутствует. Создаем новый файл. \n\n";
        ofstream newFile("students.txt");
    }

    Student arrayStudent[SIZE_ARRAY_STUDENT];
    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
        arrayStudent[i].id = i; // Создаю генерацию id, чтоб пользователь мог точечно редактировать студентов
    }

    Teacher arrayTeacher[SIZE_ARRAY_TEACHER]; // ИДЗ №4
    char requestTeacher[SIZE_REQUESTTEACHER]{};

    int response;

    cout <<
         "0.   Завершение работы программы.\n"
         "1.   Создание новой записи о студенте.\n"
         "2.   Внесение изменений в уже имеющуюся запись.\n"
         "3.   Вывод всех данных о студентах.\n"
         "4.   Вывод информации обо всех студентах группы N. N – инициализируется пользователем.\n"
         "5.   Вывод топа самых успешных студентов с наивысшим по рейтингу средним баллом за прошедшую сессию.\n"
         "6.   Вывод количества студентов мужского и женского пола.\n"
         "7.   Вывод данных о студентах, которые не получают стипендию; учатся только на «хорошо» и «отлично»; учатся только на «отлично»;\n"
         "8.   Вывод данных о студентах, имеющих номер в списке – k. \n"

         "9.   Создание новой записи о преподавателе.\n" // ИДЗ №4
         "10.  Вывод информации о преподавателе по ФИО/номеру группы/наименованию дисциплины.\n";

    while (true) {
        cout << "Введите номер интересующей операции: \n";
        cin >> response;

        switch (response) {
            case 0:
                exit(-1);
            case 1:
                for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
                    CreateEntry(arrayStudent[i]);
                }
                break;
            case 2:
                cout << "Введите id студента, данные которого необходимо изменить: \n";
                int id;
                cin >> id;
                CreateEntry(arrayStudent[id]);
                break;
            case 3:
                for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
                    PrintEntry(arrayStudent[i]);
                    cout << "-------------------------------------------------------------- \n";
                }
                break;
            case 4:
                cout << "Введите номер группы студентов, данные которых необходимо вывести: \n";
                int groupNumber;
                cin >> groupNumber;
                SortByGroupNumber(arrayStudent, groupNumber);
                break;
            case 5:
                TopStudents(arrayStudent);
                break;
            case 6:
                AboutGenders(arrayStudent);
                break;
            case 7:
                AboutGradesStudents(arrayStudent);
                break;
            case 8:
                cout << "Введите номер студента(ов) в группе: \n";
                int groupListNumber;
                cin >> groupListNumber;
                SortByGroupListNumber(arrayStudent, groupListNumber);
                break;
            case 9: // ИДЗ №4
                for (int i = 0; i < SIZE_ARRAY_TEACHER; ++i) {
                    CreateEntry(arrayTeacher[i]);
                }
                break;
            case 10: // ИДЗ №4
                cout << "Введите ФИО/номер группы/наименование дисциплины: \n"; // ИДЗ №4
                cin >> requestTeacher;

                for (int i = 0; i < SIZE_ARRAY_TEACHER; ++i) {
                    // При использовании == для char[] сравниваются их адреса
                    // strcmp сравнивает разницу между элементами массивов. Если разницы нет, то == 0
                    if ((strcmp(requestTeacher, arrayTeacher[i].fullName) == 0) or
                        (strcmp(requestTeacher, arrayTeacher[i].groupNumber) == 0) or
                        (strcmp(requestTeacher, arrayTeacher[i].discipline) == 0)) {
                        PrintEntry(arrayTeacher[i]);
                        cout << "-------------------------------------------------------------- \n";
                    }
                }
                break;
            default:
                continue;
        }
    }
}