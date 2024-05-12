#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <string>
#include <omp.h>

using namespace std;
using namespace std::chrono;

typedef vector<vector<int>> Matrix;

void writeMatrix(const string& path, const string& filename, const Matrix& matrix) {
    ofstream file(path + filename);;
    if (!file.is_open()) {
        cout << "Ошибка: Невозможно создать файл " << filename << endl;
        exit(1);
    }
    file << matrix.size() << endl;
    for (const auto& row : matrix) {
        for (const auto& elem : row)
            file << elem << " ";
        file << endl;
    }
}

Matrix readMatrix(const string& filename) {
    ifstream file("matrices/" + filename);
    if (!file.is_open()) {
        cout << "Ошибка: Невозможно открыть файл " << filename << endl;
        exit(1);
    }
    int size;
    file >> size;
    Matrix matrix(size, vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            file >> matrix[i][j];
    return matrix;
}

Matrix randomMatrix(int size) {
    Matrix matrix(size, vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = rand() % 100;
    return matrix;
}

Matrix multiplyMatrix(const Matrix& a, const Matrix& b, const int threads_num) {
    int size = a.size();
    Matrix result(size, vector<int>(size, 0));
    
#pragma omp parallel num_threads(threads_num)
    {
#pragma omp for 
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                for (int k = 0; k < size; k++)
                    result[i][j] += a[i][k] * b[k][j];
    }
        return result;
    
    
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<int> sizes = { 100, 200, 500, 1000, 1500, 2000, 3000};
    ofstream file("consumed_time.txt");
    if (!file.is_open()) {
        cout << "Ошибка: Невозможно открыть файл consumed_time.txt" << endl;
        exit(1);
    }
    int threads_num = 1;
    file << "Количество потоков " << threads_num << endl;
    for (int size : sizes) {
        string filename1 = "matrix1_" + to_string(size) + ".txt";
        string filename2 = "matrix2_" + to_string(size) + ".txt";
        Matrix a = randomMatrix(size);
        Matrix b = randomMatrix(size);
        writeMatrix("matrices/", filename1, a);
        writeMatrix("matrices/", filename2, b);
        Matrix a_read = readMatrix(filename1);
        Matrix b_read = readMatrix(filename2);
        auto start = high_resolution_clock::now();
       
        Matrix c = multiplyMatrix(a_read, b_read, threads_num);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        
        file << "Размер матрицы: " << size << ", Время выполнения: " << duration.count() / 1000 << '.' << duration.count() % 1000 << " секунд" << endl;
        writeMatrix("results/", "result_" + to_string(size) + ".txt", c);
    }
    return 0;
}
