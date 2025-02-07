#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;


struct Array_2D { // ����������� ���������, ��� ��� ��� ������������� ��������� ������� ����� ����� ����� ������� �������
    int quantity; // ����������� �������
    int **array; // ���������� �������

    // �������� ������� (���������� ����)
    static void MakeArray_console(Array_2D &matrix) {
        cout << "Enter size of your matrix: \n";
        cin >> matrix.quantity;

        // ��������� ������ ��� ������� � ����.
        matrix.array = new int *[matrix.quantity];
        for (int i = 0; i < matrix.quantity; ++i) {
            matrix.array[i] = new int[matrix.quantity];
        }

        // ���������� ������� �������.
        cout << "Enter your matrix: \n";
        for (int i = 0; i < matrix.quantity; ++i) {
            for (int j = 0; j < matrix.quantity; ++j) {
                cin >> matrix.array[i][j];
            }
        }
    }

    // �������� ������� (�������� ����)
    static void MakeArray_file(Array_2D &matrix) {
        ifstream inFile("input.txt"); // ������� ������� ���� ��� ������

        if (inFile.is_open()) {
            ifstream fin("input.txt");
            fin >> matrix.quantity;
            // ��������� ������ ��� ������� � ����.
            matrix.array = new int *[matrix.quantity];
            for (int i = 0; i < matrix.quantity; ++i) {
                matrix.array[i] = new int[matrix.quantity];
            }

            // ���������� ������� �������.
            for (int i = 0; i < matrix.quantity; ++i) {
                for (int j = 0; j < matrix.quantity; ++j) {
                    fin >> matrix.array[i][j];
                }
            }

            fin.close();
        } else {
            cout << "���� �� ������. \n";
        }
    }

    // ����� ������� � �������
    static void PrintArray_file(Array_2D &matrix) {
        cout << "Matrix visualized: \n";
        for (int i = 0; i < matrix.quantity; ++i) {
            for (int j = 0; j < matrix.quantity; ++j) {
                cout << matrix.array[i][j] << "\t";
            }
            cout << "\n";
        }
    }

    // ����� ������� � ����
    static void PrintArray_console(Array_2D &matrix) {
        ifstream outFile("output.txt"); // ������� ������� ���� ��� ������

        if (outFile.is_open()) {
            ofstream fout("output.txt");

            fout << "Matrix visualized: \n";
            for (int i = 0; i < matrix.quantity; ++i) {
                for (int j = 0; j < matrix.quantity; ++j) {
                    fout << matrix.array[i][j] << "\t";
                }
                fout << "\n";
            }

            fout.close();
        } else {
            cout << "���� �� ������. \n";
        }

    }

    // �������� ������� �� "����"
    static void DeleteArray(Array_2D &matrix) {
        // ������������ ������, ���������� ��� �������
        for (int i = 0; i < matrix.quantity; ++i) {
            delete[] matrix.array[i];
        }
        delete[] matrix.array;
    }

    // �������������� �������
    static void EditArray(Array_2D &matrix) {
        int column;
        int row;
        int value;

        cout << "Enter column, row, and value to edit: \n";
        cin >> column >> row >> value;

        if (column < matrix.quantity and row < matrix.quantity) {
            matrix.array[column - 1][row - 1] = value; // -1, �.�. ������������ ��������� ������� ���������� � "1"
        } else {
            cout << "Invalid indexes. \n";
        }
    }

    // ������������ �������
    static double Determinant(int **matrix, int length) {
        // ���� ������� 2x2, �� ������������ ����������� �� ������� ad - bc
        if (length == 2) {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }

        double det = 0;

        for (int i = 0; i < length; ++i) {

            // ��������� ������ ��� ������ � ����.
            int **minor = new int *[length - 1];
            for (int g = 0; g < length - 1; ++g) {
                minor[g] = new int[length - 1];
            }

            // (������� �������. ����� ������ ����� ������)
            for (int j = 1; j < length; ++j) { // ���������� ������ ������� �� 2
                int l = 0;
                for (int k = 0; k < length; ++k) { // ���������� �������
                    if (k != i) { // ������� ���������, �� ��������� �� ������� ������� k � ��������� �������� i
                        minor[j - 1][l] = matrix[j][k];
                        ++l;
                    }
                }
            }

            // ���������� �������� ������� ��� ���������� ������������ ������
            // ����� �������, ����� �������� ������� ������ �� 2x2 � �������� �����
            if (i % 2 == 0) {
                det += matrix[0][i] * Determinant(minor, length - 1);
            } else {
                det -= matrix[0][i] * Determinant(minor, length - 1);
            }

            // ����������� ������, ���������� ��� �����
            for (int f = 0; f < length - 1; ++f) {
                delete[] minor[f];
            }
            delete[] minor;
        }

        return det;
    }

    // "���������� ���������� ��������� ������� �, ������� ��������� ����� ��������� � ����������� ������� ������� B."
    static void PersonalTask(Array_2D &matrix_A, Array_2D &matrix_B) {
        int length = min(matrix_A.quantity,
                         matrix_B.quantity); // ������� ����������� ����� �� ������, ���� ������� ������ ������������
        int count = 0;

        if (matrix_A.quantity == matrix_B.quantity) {
            for (int i = 0; i < length; ++i) {
                int amount = 0;
                for (int j = 0; j < length; ++j) { // ������� ����� ����� ������� ������� B
                    amount += matrix_B.array[j][i];
                }
                for (int j = 0; j < length; ++j) {
                    if (matrix_A.array[j][i] > amount) { // ������������
                        count += 1;
                    }
                }
            }
        }

        if (matrix_A.quantity > matrix_B.quantity) {
            for (int i = 0; i < length; ++i) {
                int amount = 0;
                for (int j = 0; j < length; ++j) { // ������� ����� ����� ������� ������� B
                    amount += matrix_B.array[j][i];
                }
                for (int j = 0; j < matrix_A.quantity; ++j) {
                    if (matrix_A.array[j][i] > amount) { // ������������
                        count += 1;
                    }
                }
            }
        }

        if (matrix_A.quantity < matrix_B.quantity) {
            for (int i = 0; i < length; ++i) {
                int amount = 0;
                for (int j = 0; j < matrix_B.quantity; ++j) { // ������� ����� ����� ������� ������� B
                    amount += matrix_B.array[j][i];
                }
                for (int j = 0; j < length; ++j) {
                    if (matrix_A.array[j][i] > amount) { // ������������
                        count += 1;
                    }
                }
            }
        }

        cout << "Result: " << count << "\n";
    }

};

int main() {
    // ��������� 3 �������
    Array_2D matrix_A{};
    Array_2D matrix_B{};
    Array_2D matrix_C{};

    while (true) {
        int response_1;
        cout << "Enter '1' to work with matrix A. \n";
        cout << "Enter '2' to work with matrix B. \n";
        cout << "Enter '3' to work with matrix C. \n";
        cout << "Enter '4' to find my task. \n";
        cout << "Enter '5' to quit the menu and finish. \n";
        cout << "Enter command: \n";
        cin >> response_1;
        if (response_1 == 1) {
            int response_2;
            cout << "Enter '1' to make matrix A (console). \n";
            cout << "Enter '2' to make matrix A (file). \n";
            cout << "Enter '3' to print matrix A (console). \n";
            cout << "Enter '4' to print matrix A (file). \n";
            cout << "Enter '5' to edit matrix A. \n";
            cout << "Enter '6' to find determined matrix A. \n";
            cout << "Enter '7' to delete matrix A. \n";
            cout << "Enter command: \n";
            cin >> response_2;
            switch (response_2) {
                case 1:
                    Array_2D::MakeArray_console(matrix_A); // �����������: matrix_A.MakeArray_console(matrix_A);
                    break;
                case 2:
                    Array_2D::MakeArray_file(matrix_A);
                    break;
                case 3:
                    Array_2D::PrintArray_file(matrix_A);
                    break;
                case 4:
                    Array_2D::PrintArray_console(matrix_A);
                    break;
                case 5:
                    Array_2D::EditArray(matrix_A);
                    break;
                case 6:
                    cout << "Determinant: " << Array_2D::Determinant(matrix_A.array, matrix_A.quantity) << "\n";
                    break;
                case 7:
                    Array_2D::DeleteArray(matrix_A);
                    break;
                default:
                    continue;
            }
        } else if (response_1 == 2) {
            int response_2;
            cout << "Enter '1' to make matrix B (console). \n";
            cout << "Enter '2' to make matrix B (file). \n";
            cout << "Enter '3' to print matrix B (console). \n";
            cout << "Enter '4' to print matrix B (file). \n";
            cout << "Enter '5' to edit matrix B. \n";
            cout << "Enter '6' to find determined matrix B. \n";
            cout << "Enter '7' to delete matrix B. \n";
            cout << "Enter command: \n";
            cin >> response_2;
            switch (response_2) {
                case 1:
                    Array_2D::MakeArray_console(matrix_B);
                    break;
                case 2:
                    Array_2D::MakeArray_file(matrix_B);
                    break;
                case 3:
                    Array_2D::PrintArray_file(matrix_B);
                    break;
                case 4:
                    Array_2D::PrintArray_console(matrix_B);
                    break;
                case 5:
                    Array_2D::EditArray(matrix_B);
                    break;
                case 6:
                    cout << "Determinant: " << Array_2D::Determinant(matrix_B.array, matrix_B.quantity) << "\n";
                    break;
                case 7:
                    Array_2D::DeleteArray(matrix_B);
                    break;
                default:
                    continue;
            }
        } else if (response_1 == 3) {
            int response_2;
            cout << "Enter '1' to make matrix C (console). \n";
            cout << "Enter '2' to make matrix C (file). \n";
            cout << "Enter '3' to print matrix C (console). \n";
            cout << "Enter '4' to print matrix C (file). \n";
            cout << "Enter '5' to edit matrix C. \n";
            cout << "Enter '6' to find determined matrix C. \n";
            cout << "Enter '7' to delete matrix C. \n";
            cout << "Enter command: \n";
            cin >> response_2;
            switch (response_2) {
                case 1:
                    Array_2D::MakeArray_console(matrix_C);
                    break;
                case 2:
                    Array_2D::MakeArray_file(matrix_C);
                    break;
                case 3:
                    Array_2D::PrintArray_file(matrix_C);
                    break;
                case 4:
                    Array_2D::PrintArray_console(matrix_C);
                    break;
                case 5:
                    Array_2D::EditArray(matrix_C);
                    break;
                case 6:
                    cout << "Determinant: " << Array_2D::Determinant(matrix_C.array, matrix_C.quantity) << "\n";
                    break;
                case 7:
                    Array_2D::DeleteArray(matrix_C);
                    break;
                default:
                    continue;
            }
        } else if (response_1 == 4) {
            Array_2D::PersonalTask(matrix_A, matrix_B);
        } else if (response_1 == 5) {
            Array_2D::DeleteArray(matrix_A);
            Array_2D::DeleteArray(matrix_B);
            Array_2D::DeleteArray(matrix_C);
            break;
        }
    }
    return 0;
}