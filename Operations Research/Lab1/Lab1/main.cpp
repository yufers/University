#include <iostream>
#include <vector>
#include <set>
#include <numeric>
#include <string>

using namespace std;

const double EPS = 1e-9;
const int INF = 2;

// Функция для нахождения НОД
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Функция для вывода числа в виде дроби
string to_fraction(double val) {
    int den = 196; // Выбираем знаменатель для точности (можно адаптировать)
    int num = round(val * den);
    int g = gcd(abs(num), den);
    num /= g;
    den /= g;
    if (den == 1) return to_string(num);
    return "(" + to_string(num) + "/" + to_string(den) + ")";
}

// Функция решения системы линейных уравнений методом Гаусса
int gauss(vector<vector<double>> a, vector<double>& ans, vector<vector<double>>& basis) {
    int n = (int)a.size();
    int m = (int)a[0].size() - 1;

    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        for (int i = row; i < n; ++i)
            if (abs(a[i][col]) > abs(a[sel][col]))
                sel = i;

        if (abs(a[sel][col]) < EPS)
            continue;

        for (int i = col; i <= m; ++i)
            swap(a[sel][i], a[row][i]);

        where[col] = row;

        for (int i = 0; i < n; ++i) {
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j = col; j <= m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        }
        ++row;
    }

    ans.assign(m, 0);
    for (int i = 0; i < m; ++i) {
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    }

    set<int> free_vars;
    for (int i = 0; i < m; ++i) {
        if (where[i] == -1)
            free_vars.insert(i);
    }

    basis.assign(m, vector<double>(free_vars.size(), 0));
    int idx = 0;
    for (int var : free_vars) {
        for (int i = 0; i < m; ++i) {
            if (where[i] != -1)
                basis[i][idx] = -a[where[i]][var] / a[where[i]][i];
            else if (i == var)
                basis[i][idx] = 1;
        }
        idx++;
    }

    return free_vars.empty() ? 1 : INF;
}

// Функция вывода общего решения с корректными знаками
void print_solution(const vector<double>& ans, const vector<vector<double>>& basis) {
    int m = ans.size();
    cout << "Общее решение:\n";
    for (int i = 0; i < m; i++) {
        cout << "x" << i + 1 << " = " << to_fraction(ans[i]);
        for (int j = 0; j < basis[i].size(); j++) {
            if (basis[i][j] != 0) {
                if (basis[i][j] > 0) {
                    cout << " + " << to_fraction(basis[i][j]) << "x" << (m - basis[i].size() + j + 1);
                }
                else {
                    cout << " - " << to_fraction(-basis[i][j]) << "x" << (m - basis[i].size() + j + 1);
                }
            }
        }
        cout << endl;
    }
}

int main() {
    vector<vector<double>> matrix = {
        {6, -2, 2, 0, 5, 2},
        {-1, -13, 7, 11, 0, 17},
        {4, -7, 2, 1, 3, -6},
        {5, -15, 9 ,11, 5, 19}
    };
    vector<double> res;
    vector<vector<double>> basis;
    int found = gauss(matrix, res, basis);

    if (found == 0) {
        cout << "Система не имеет решений" << endl;
    }
    else {
        print_solution(res, basis);
    }
}
