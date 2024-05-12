# Лабораторая работа №1 

## Задание: 
Написать программу на языке C/C++ для перемножения двух матриц
Исходные данные: файл(ы) содержащие значения исходных матриц
Выходные данные: файл со значениями результирующей матрицы, время выполнения, объем задачи# Parallel-programming-Lab-2

## Ключевые файлы: 
1. Cгенерированны матрицы в папке `matrices` разных размеров
2. Результат перемножение матриц в папке `results`
3. Файл статистики: `Info`
4. В папке `сonsumed time` находятся файлы времени выплонения для разного количества потоков

В данной лабораторной продемострирована реализация параллельного вычисления матриц:

```
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
```

### Характеристики компьютера
- CPU - IntelCore i5-11600KF 3.90GHz 
- GPU - NVIDIA GeForce GTX 1060 6GB
- RAM - 16 GB

### Визуализация 
![Зависимость времени от количества потоков](https://github.com/Vouchiko/Parallel-programming-Lab-2/blob/main/consumed%20time/Picture.png)

## Вывод:
Опираясь на полученные результаты можно сделать вывод, стандарт OpenMP позволяет ускорить выполняемую операцию. Каждый поток работает над своей частью результирующей матрицы, что позволяет эффективнее использовать вычислительные ресурсы и уменьшить время выполнения операции умножения, а увеличение количества поток положительно сказывается на производительности
   
