
#include <iostream>
#include <iomanip>
using namespace std;

// Введення матриці
void input(int** a, int r, int c, int p = 0) {
    if (p == r * c) return;
    cin >> a[p / c][p % c];
    input(a, r, c, p + 1);
}

// Виведення матриці
void print(int** a, int r, int c, int p = 0) {
    if (p == r * c) return;
    cout << setw(5) << a[p / c][p % c];
    if (p % c == c - 1) cout << endl;
    print(a, r, c, p + 1);
}

// Перевірка нуля у стовпці
bool hasZero(int** a, int r, int j, int i = 0) {
    if (i == r) return false;
    if (a[i][j] == 0) return true;
    return hasZero(a, r, j, i + 1);
}

// Кількість стовпців з нулями
int countZero(int** a, int r, int c, int j = 0) {
    if (j == c) return 0;
    int count = 0;
    if (hasZero(a, r, j)) count = 1;
    return count + countZero(a, r, c, j + 1);
}

// Найдовша серія однакових чисел
int longestRun(int* a, int n, int j = 1,
    int current = 1, int best = 1) {
    if (j == n) return best;

    if (a[j] == a[j - 1]) current++;
    else current = 1;

    if (current > best) best = current;

    return longestRun(a, n, j + 1, current, best);
}

// Пошук рядка з найдовшою серією
void findRow(int** a, int r, int c,
    int& row, int& best, int i = 0) {
    if (i == r) return;

    int length = longestRun(a[i], c);
    if (length > best) {
        best = length;
        row = i;
    }

    findRow(a, r, c, row, best, i + 1);
}

int main() {
    int r, c;
    cout << "Rows and columns: ";
    cin >> r >> c;

    if (!cin || r < 1 || c < 1 || r > 40 || c > 40)
        return 1;

    int** a = new int* [r];
    for (int i = 0; i < r; i++)
        a[i] = new int[c];

    cout << "Enter matrix:\n";
    input(a, r, c);

    if (!cin) {
        for (int i = 0; i < r; i++) delete[] a[i];
        delete[] a;
        return 1;
    }

    cout << "Matrix:\n";
    print(a, r, c);

    cout << "Columns with zero = "
        << countZero(a, r, c) << endl;

    int row = 0, best = 0;
    findRow(a, r, c, row, best);

    cout << "Row number = " << row + 1 << endl;
    cout << "Longest run = " << best << endl;

    for (int i = 0; i < r; i++) delete[] a[i];
    delete[] a;

    return 0;
}
