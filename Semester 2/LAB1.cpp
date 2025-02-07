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

struct Teacher { // ��� �4
    char fullName[SIZE_FULLNAME]{};
    char gender[SIZE_GENDER]{};
    int age{};
    char academicDegree[SIZE_ACADEMICDEGREE]{};
    char discipline[SIZE_DISCIPLINE]{};
    char email[SIZE_EMAIL]{};
    char groupNumber[SIZE_GROUPNUMBER]{};
};

void CreateEntry(Student &arrayStudent) {
    ofstream fout("students.txt", ios::app); // �������� ����� (�������������)

    cout << "������� ��� ��������: \n";
    cin.ignore();
    cin.getline(arrayStudent.fullName, SIZE_FULLNAME);
    fout << "���: " << arrayStudent.fullName << "\n";

    cout << "������� ��� ��������: \n";
    cin >> arrayStudent.gender;
    fout << "���: " << arrayStudent.gender << "\n";

    cout << "������� ����� ������ ��������: \n";
    cin >> arrayStudent.groupNumber;
    fout << "����� ������: " << arrayStudent.groupNumber << "\n";

    cout << "������� ����� �������� � ������: \n";
    cin >> arrayStudent.groupListNumber;
    fout << "����� � ������: " << arrayStudent.groupListNumber << "\n";

    cout << "������� ������ ��������: \n";
    fout << "������: ";
    for (int i = 0; i < SIZE_GRADES; ++i) {
        cin >> arrayStudent.grades[i];
        fout << arrayStudent.grades[i] << " ";

        arrayStudent.averageGrades += arrayStudent.grades[i] / 8;
    }

    fout << "������� ����: " << arrayStudent.averageGrades << "\n";
    fout << "-------------------------------------------------------------- \n";

    fout.close();
}

void CreateEntry(Teacher &arrayTeacher) { // ���������� ���������� �������
    cout << "������� ��� �������������: \n";
    cin.ignore();
    cin.getline(arrayTeacher.fullName, SIZE_FULLNAME);

    cout << "������� ��� �������������: \n";
    cin >> arrayTeacher.gender;

    cout << "������� ������� �������������: \n";
    cin >> arrayTeacher.age;

    cout << "������� ������ ������� �������������: \n";
    cin.ignore();
    cin.getline(arrayTeacher.academicDegree, SIZE_ACADEMICDEGREE);

    cout << "������� ������������ ���������� �������������: \n";
    cin.getline(arrayTeacher.discipline, SIZE_DISCIPLINE);

    cout << "������� email �������������: \n";
    cin >> arrayTeacher.email;

    cout << "������� ����� ������, � ������� ������������� ���� �������: \n";
    cin >> arrayTeacher.groupNumber;
}

void PrintEntry(Student &arrayStudent) { // ��������� ������ �� 1 ����������� ��������
    cout << "���: " << arrayStudent.fullName << "\n";
    cout << "���: " << arrayStudent.gender << "\n";
    cout << "����� ������: " << arrayStudent.groupNumber << "\n";
    cout << "����� � ������: " << arrayStudent.groupListNumber << "\n";
    cout << "������: ";
    for (int i = 0; i < SIZE_GRADES; ++i) {
        cout << arrayStudent.grades[i] << " ";
    }
    cout << "\n";
    cout << "������� ����: " << arrayStudent.averageGrades << "\n";
    cout << "ID: " << arrayStudent.id << "\n";
}

void PrintEntry(Teacher &arrayTeacher) {
    cout << "���: " << arrayTeacher.fullName << "\n";
    cout << "���: " << arrayTeacher.gender << "\n";
    cout << "�������: " << arrayTeacher.age << "\n";
    cout << "������ �������: " << arrayTeacher.academicDegree << "\n";
    cout << "������������ ����������: " << arrayTeacher.discipline << "\n";
    cout << "Email: " << arrayTeacher.email << "\n";
    cout << "����� ������: " << arrayTeacher.groupNumber << "\n";
}

void SortByGroupNumber(Student arrayStudent[], int groupNumber) { // ������ ����� ������� ���������, �������� � ���
    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
        if (arrayStudent[i].groupNumber == groupNumber) {
            PrintEntry(arrayStudent[i]);
        }
    }
}

void TopStudents(Student arrayStudent[]) { // ���������� ���������
    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
        for (int j = 0; j < SIZE_ARRAY_STUDENT - i - 1; ++j) {
            if (arrayStudent[j].averageGrades < arrayStudent[j + 1].averageGrades) {
                swap(arrayStudent[j], arrayStudent[j + 1]);
            }
        }
    }

    cout << "��� ���������: \n";
    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
        cout << arrayStudent[i].fullName << " " << "(" << arrayStudent[i].averageGrades << ")\n";
    }
}

void AboutGenders(Student arrayStudent[]) {
    int male = 0;
    int female = 0;
    string strMale = "�������";
    string strFemale = "�������";
    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
        if (arrayStudent[i].gender == strMale) {
            male += 1;
        }
        if (arrayStudent[i].gender == strFemale) {
            female += 1;
        }
    }
    cout << "������: " << male << "\n";
    cout << "������: " << female << "\n";
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

    cout << "��������, ������� ������ �� ������: \n";
    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
        if (array_3[i] == 1) {
            PrintEntry(arrayStudent[i]);
        }
    }

    cout << "��������, ������� ������ �� 4 � 5: \n";
    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
        if (array_45[i] == 1) {
            PrintEntry(arrayStudent[i]);
        }
    }

    cout << "��������, ������� ������ ������ �� 5: \n";
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

    // ������������ ���������� ����/�����
    // P.S. � ������� �������������, ������� ������� �������� ��������� ����� � � idle ����.
    // ���� � ��� win10/win11 + Clion � ���������� win1251, �� �� ����� ����.
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // ���� � ��� Clion, �� ���� ����� ������ �: "C:\...\CLionProjects\(�������� �������)\cmake-build-debug"
    // P.S. ��������� ���� ������ � ������ ����
    ifstream fileCheck("students.txt"); // �������� ������� �����
    if (fileCheck.good()) {
        ofstream outputFile("students.txt", ios::trunc); // ������� �����
        outputFile.close();
        fileCheck.close();
    } else {
        cout << "���� �����������. ������� ����� ����. \n\n";
        ofstream newFile("students.txt");
    }

    Student arrayStudent[SIZE_ARRAY_STUDENT];
    for (int i = 0; i < SIZE_ARRAY_STUDENT; ++i) {
        arrayStudent[i].id = i; // ������ ��������� id, ���� ������������ ��� ������� ������������� ���������
    }

    Teacher arrayTeacher[SIZE_ARRAY_TEACHER]; // ��� �4
    char requestTeacher[SIZE_REQUESTTEACHER]{};

    int response;

    cout <<
         "0.   ���������� ������ ���������.\n"
         "1.   �������� ����� ������ � ��������.\n"
         "2.   �������� ��������� � ��� ��������� ������.\n"
         "3.   ����� ���� ������ � ���������.\n"
         "4.   ����� ���������� ��� ���� ��������� ������ N. N � ���������������� �������������.\n"
         "5.   ����� ���� ����� �������� ��������� � ��������� �� �������� ������� ������ �� ��������� ������.\n"
         "6.   ����� ���������� ��������� �������� � �������� ����.\n"
         "7.   ����� ������ � ���������, ������� �� �������� ���������; ������ ������ �� ������� � ��������; ������ ������ �� ��������;\n"
         "8.   ����� ������ � ���������, ������� ����� � ������ � k. \n"

         "9.   �������� ����� ������ � �������������.\n" // ��� �4
         "10.  ����� ���������� � ������������� �� ���/������ ������/������������ ����������.\n";

    while (true) {
        cout << "������� ����� ������������ ��������: \n";
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
                cout << "������� id ��������, ������ �������� ���������� ��������: \n";
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
                cout << "������� ����� ������ ���������, ������ ������� ���������� �������: \n";
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
                cout << "������� ����� ��������(��) � ������: \n";
                int groupListNumber;
                cin >> groupListNumber;
                SortByGroupListNumber(arrayStudent, groupListNumber);
                break;
            case 9: // ��� �4
                for (int i = 0; i < SIZE_ARRAY_TEACHER; ++i) {
                    CreateEntry(arrayTeacher[i]);
                }
                break;
            case 10: // ��� �4
                cout << "������� ���/����� ������/������������ ����������: \n"; // ��� �4
                cin >> requestTeacher;

                for (int i = 0; i < SIZE_ARRAY_TEACHER; ++i) {
                    // ��� ������������� == ��� char[] ������������ �� ������
                    // strcmp ���������� ������� ����� ���������� ��������. ���� ������� ���, �� == 0
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