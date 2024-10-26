import numpy as np
import matplotlib.pyplot as plt
import os

def plot_asymptotic_complexity():
    n = np.linspace(1, 10000, 20000)  # Количество элементов массива

    # Данные для каждого алгоритма
    complexities = {
        'Selection Sort': {
            'Лучший': n**2,
            'Средний': 10*n**2,
            'Худший': 20*n**2,
        },
        'Insertion Sort': {
            'Лучший': n,
            'Средний': n**2,
            'Худший': 10*n**2,
        },
        'Bubble Sort': {
            'Лучший': n,
            'Средний': n**2,
            'Худший': 10*n**2,
        },
        'Merge Sort': {
            'Лучший': n * np.log(n),
            'Средний': 10 * n * np.log(n),
            'Худший': 20 * n * np.log(n),
        },
        'Quick Sort': {
            'Лучший': n * np.log(n),
            'Средний': 10 * n * np.log(n),
            'Худший': n**2,
        },
        'Shell Sort': {
            'Лучший': n * (np.log(n)**2),
            'Средний': np.nan,
            'Худший': n**2,
        },
        'Shell Sort Hibbard': {
            'Лучший': n * np.log(n),
            'Средний': n**(5/4),
            'Худший': n**(3/2),
        },
        'Shell Sort Pratt': {
            'Лучший': n,
            'Средний': n * (np.log(n)**2),
            'Худший': 10 * n * (np.log(n)**2),
        },
        'Heap Sort': {
            'Лучший': n * np.log(n),
            'Средний': 10 * n * np.log(n),
            'Худший': 20 * n * np.log(n),
        },
    }

    # Построение графиков для каждого алгоритма
    for algorithm, cases in complexities.items():
        plt.figure(figsize=(10, 6))
        for case_name, values in cases.items():
            if np.isnan(values).any():
                continue  # Пропустить, если оценки нет
            plt.plot(n, values, label=f'{case_name}')

        plt.title(f'Асимптоты сложности {algorithm}')
        plt.xlabel('N')
        plt.ylabel('T(N)')
        plt.legend()
        plt.grid(True)
        plt.xlim([1, 30])
        plt.ylim([1, 3000])

        # Сохранение графика
        filename = os.path.join(os.getcwd(), f'{algorithm}.png')
        plt.savefig(filename)
        plt.close()

# Вызов функции
plot_asymptotic_complexity()

