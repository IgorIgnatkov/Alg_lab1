import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


def load_data(file_path):
    return pd.read_csv(file_path, sep=",", header=None,
                       names=['sort_type', 'array_type', 'array_size', 'execution_time'])


def plot_sorting_times(data):
    sorting_algorithms = data['sort_type'].unique()

    for algorithm in sorting_algorithms:
        algorithm_data = data[data['sort_type'] == algorithm]
        plot_algorithm_data(algorithm_data, algorithm)


def plot_algorithm_data(algorithm_data, algorithm):
    sorted_array_data = algorithm_data[algorithm_data['array_type'] == 'Отсортированный']
    nearly_sorted_array_data = algorithm_data[algorithm_data['array_type'] == 'Почти отсортированный']
    random_array_data = algorithm_data[algorithm_data['array_type'] == 'Случайный']
    reverse_sorted_array_data = algorithm_data[algorithm_data['array_type'] == 'Обратный']

    plt.figure(figsize=(10, 6))

    # Регрессия для каждого типа данных
    for data_subset, label in zip(
            [sorted_array_data, nearly_sorted_array_data, random_array_data, reverse_sorted_array_data],
            ['Отсортированный', 'Почти отсортированный', 'Случайный', 'Обратный']
    ):
        x = data_subset['array_size']
        y = data_subset['execution_time']

        # Полиномиальная регрессия (степень 2)
        coefficients = np.polyfit(x, y, 2)
        polynomial = np.poly1d(coefficients)

        # Построение графика
        plt.plot(x, y, label=label)

        # Добавление линии регрессии
        x_fit = np.linspace(x.min(), x.max(), 100)
        y_fit = polynomial(x_fit)
        plt.plot(x_fit, y_fit, linestyle='--', label=f'{label} - регрессия')

        # Сохранение регрессионной функции
        with open(f'{algorithm}_regression.txt', 'a') as f:
            f.write(f'{label} регрессия: {polynomial}\n')

    plt.title(f'{algorithm} - график')
    plt.xlabel('N (Размер массива)')
    plt.ylabel('t (сек)')
    plt.legend()
    plt.grid(True)
    plt.savefig(f'{algorithm}.png')
    plt.show()


def main():
    data = load_data('graph.txt')
    plot_sorting_times(data)


if __name__ == "__main__":
    main()
