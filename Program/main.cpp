// Lab_7_1_2
#include <iostream>
#include <iomanip>
using namespace std;

int myrand(const int& min, const int& max) {
	return min > 0 ?
		rand() % (max - min + 1) + min :
		rand() % (abs(min) + max + 1) + min;
}

void full_matrix(int** matrix, const int* size, const int* dia, int i = 0, int j = 0)
{
	matrix[i][j] = myrand(dia[0], dia[1]);

	j++;
	if (j == size[1]) {
		i++;
		j = 0;
	}

	if (i < size[0])
		full_matrix(matrix, size, dia, i, j);
}

void draw_matrix(int** matrix, const int* size, int i = 0, int j = 0)
{
	cout << setw(4) << matrix[i][j];

	j++;
	if (j == size[1]) {
		i++;
		j = 0;
		cout << endl;
	}

	if (i < size[0])
		draw_matrix(matrix, size, i, j);
}

void get_sum_count(int** matrix, const int* size, int& sum, int& count, int i = 0, int j = 0)
{
	if (matrix[i][j] % 6 == 0 && (i + j) % 5 != 0) {
		sum += matrix[i][j];
		count++;
		matrix[i][j] = 0;
	}

	j++;
	if (j == size[1]) {
		i++;
		j = 0;
	}

	if (i < size[0])
		get_sum_count(matrix, size, sum, count, i, j);
}

unsigned char get_status(int** matrix, const int* size, int i = 0, int j = 1, unsigned char status = 0) {
	if (status == 3)
		return status;

	if (status != 1 && matrix[j][1] == matrix[i][1]) 
		status++;

	if (status < 2 && matrix[j][0] == matrix[i][0]) 
		status += 2;

	j++;
	if (j == size[0]) {
		i++;
		j = i + 1;
	}

	if (i < size[0]-1)
		status = get_status(matrix, size, i, j, status);
	return status;
}

void sort(int** matrix, const int* size, const int &status, int i = 0, int j = 1) {
	switch (status)
	{
	case 2:
		if (matrix[j][1] < matrix[j + 1][1]) goto swp;
		break;
	case 3:
		if (matrix[j][3] < matrix[j + 1][3]) goto swp;
		break;
	default:
		if (matrix[j][0] > matrix[j + 1][0]) goto swp;
		break;
	swp:
		swap(matrix[j], matrix[j + 1]);
	}
	
	j++;
	if (j >= size[0] - i - 1) {
		i++;
		j = 0;
	}

	if (i < size[0]-1)
		sort(matrix, size, status, i, j);			
}

void main() {
	srand(time(NULL));

	int** matrix = nullptr,
		dia[2] = { 11, 74 },
		size[2] = { 8, 9 },
		sum = 0, count = 0;
	matrix = new int* [size[0]];

	for (int i = 0; i < size[0]; i++)
		matrix[i] = new int[size[1]];

	full_matrix(matrix, size, dia);
	draw_matrix(matrix, size);
	cout << endl << "// sort" << endl;
	sort(matrix, size, get_status(matrix, size));
	draw_matrix(matrix, size);
	cout << endl << "// sum and count" << endl;
	get_sum_count(matrix, size, sum, count);
	draw_matrix(matrix, size);
	cout << "sum: " << sum << endl
		<< "count: " << count << endl;

	for (int i = 0; i < size[0]; i++)
		delete[] matrix[i];

	delete[] matrix;
}