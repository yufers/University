#include <iostream>
#include <vector>

using namespace std;

const double EPS = 1e-9; // ����������� ��� ��������� ����� � ��������� ������
const int INF = 2; // ���������, ������������ ����������� ���������� �������

// ������� ������� ������� �������� ��������� ������� ������
int gauss(vector<vector<double>> a, vector<double>& ans) {
	int n = (int)a.size();
	int m = (int)a[0].size() - 1;

	vector<int> where(m, -1); // ������, �������������, � ����� ������ ��������� ������� ����������
	for (int col = 0, row = 0; col < m && row < n; ++col) {
		int sel = row;
		for (int i = row; i < n; ++i) {
			if (abs(a[i][col]) > abs(a[sel][col])) {
				sel = i;
			}
		}

		if (abs(a[sel][col]) < EPS) {
			continue; // ���� ������� ������� ������� ���, ���������� ���� �������
		}

		// ������ ������ �������
		for (int i = col; i <= m; ++i) {
			swap(a[sel][i], a[row][i]);
		}

		where[col] = row; // ����������, ��� ��������� ������� ����������

		// ������ ��� ������ ������ - ��������� ��������� ���� ������� ������
		for (int i = 0; i < n; ++i) {
			if (i != row) {
				double c = a[i][col] / a[row][col];
				for (int j = col; j <= m; ++j) {
					a[i][j] -= a[row][j] * c;
				}
			}
		}
		++row;
	}

	ans.assign(m, 0); // ��������� ������ ������� ������
	for (int i = 0; i < m; ++i) {
		if (where[i] != -1) {
			ans[i] = a[where[i]][m] / a[where[i]][i]; // �������� ��� ������ ������
		}
	}

	int it = 0;
	for (auto i = 0; i < n; i++) {
		int val = 0;
		for (auto j = 0; j < m; j++) {
			val += a[i][j];
		}
		val += ans[it];
		cout << "x" << i + 1 << "=" << val << endl;
		it++;
		val = 0;
	}

	// �������� �� ������������ �������
	for (int i = 0; i < n; ++i) {
		double sum = 0;
		for (int j = 0; j < m; ++j) {
			sum += ans[j] * a[i][j];
		}
		if (abs(sum - a[i][m]) > EPS) {
			return 0; // ��� �������
		}
	}

	// �������� �� ����������� ���������� �������
	for (int i = 0; i < m; ++i) {
		if (where[i] == -1) {
			return INF; // ����������� ���������� �������
		}
	}

	return 1; // ������������ �������
}

int main() {
	vector<vector<double>> matrix = {
		{6, -2, 2, 0, 5, 2},
		{-1, -13, 7, 11, 0, 17},
		{4, -7, 2, 1, 3, -6},
		{5, -15, 9 ,11, 5, 19}
	};
	vector<double> res;
	int found = gauss(matrix, res);

	// ����� �������
	for (auto num : res) {
		cout << num << " ";
	}
}
