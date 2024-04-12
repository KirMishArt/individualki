#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

// Функция, производную которой нужно найти
double f(double x) {
    return std::sin(x);
}

// Функция для вычисления второй производной
std::vector<double> secondDerivative(const std::vector<double>& xValues, double h) {
    int size = xValues.size();
    std::vector<double> result(size, 0.0);

    // Вычисление второй производной с использованием параллельного программирования OpenMP
#pragma omp parallel for
    for (int i = 1; i < size - 1; ++i) {
        result[i] = (f(xValues[i + 1]) - 2 * f(xValues[i]) + f(xValues[i - 1])) / (h * h);
    }

    return result;
}

int main() {
    double a = 0.0;
    double b = 10.0;
    int n = 1000;
    double h = (b - a) / n;

    std::vector<double> xValues(n + 1);
    for (int i = 0; i <= n; ++i) {
        xValues[i] = a + i * h;
    }

    std::vector<double> d2f = secondDerivative(xValues, h);

    // Вывод результатов
    for (int i = 0; i < d2f.size(); ++i) {
        std::cout << "x = " << xValues[i] << ", f''(x) = " << d2f[i] << std::endl;
    }

    return 0;
}