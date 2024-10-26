import pandas as pd
import matplotlib.pyplot as plt


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
    plt.plot(sorted_array_data['array_size'], sorted_array_data['execution_time'], label='Отсортированный')
    plt.plot(nearly_sorted_array_data['array_size'], nearly_sorted_array_data['execution_time'],
             label='Почти отсортированный')
    plt.plot(random_array_data['array_size'], random_array_data['execution_time'], label='Случайный')
    plt.plot(reverse_sorted_array_data['array_size'], reverse_sorted_array_data['execution_time'], label='Обратный')

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

