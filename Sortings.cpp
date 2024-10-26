#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <numeric>

using namespace std;

// Функция для вывода массива
void printArray(const vector<int>& arr) {
    for (const int& value : arr) {
        cout << value << " ";
    }
    cout << endl;
}

// Генерация отсортированного массива
vector<int> generateSortedArray(int size) {
    vector<int> arr(size);
    iota(arr.begin(), arr.end(), 0); // Заполняем числами от 0 до size-1
    return arr;
}

// Генерация почти отсортированного массива
vector<int> generateNearlySortedArray(int size) {
    vector<int> arr = generateSortedArray(size);
    for (int i = 0; i < size / 10; ++i) {
        swap(arr[rand() % size], arr[rand() % size]);
    }
    return arr;
}

// Генерация массива в обратном порядке
vector<int> generateReversedArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = size - 1 - i;
    }
    return arr;
}

// Генерация случайного массива
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    generate(arr.begin(), arr.end(), []() { return rand() % 100; });
    return arr;
}

// Сохранение результатов в файл
void saveResults(ofstream& file, const string& sortType, const string& arrayType, int size, double time) {
    file << sortType << "," << arrayType << "," << size << "," << fixed << setprecision(6) << time << endl;
}

// Алгоритмы сортировки
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < leftArr.size() && j < rightArr.size()) {
        arr[k++] = (leftArr[i] <= rightArr[j]) ? leftArr[i++] : rightArr[j++];
    }
    while (i < leftArr.size()) arr[k++] = leftArr[i++];
    while (j < rightArr.size()) arr[k++] = rightArr[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void shellSort(vector<int>& arr) {
    for (int gap = arr.size() / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < arr.size(); ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void bubbleSort(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; ++i) {
        for (int j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void shellSortPratt(vector<int>& arr) {
    vector<int> gaps;
    int size = arr.size();
    // Послежовательность Пратта
    for (int i = 1; i < size; i *= 2)
    {
        for (int j = i; j < size; j *= 3)
        {
            gaps.push_back(j);
        }
    }
    // Сортировка шагов по убыванию
    insertionSort(gaps);
    for (int gap : gaps)
    {
        for (int i = gap; i < size; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void shellSortHibb(vector<int>& arr) {
    int i, j, k, increment, temp;
    int val;
    // Начальный шаг
    val = (int)log((float)arr.size() + 1) / log((float)2);
    increment = pow((float)2, val) - 1;
    while (increment > 0)
    {
        for (i = 0; i < increment; i++)
        {
            for (j = 0; j < arr.size(); j += increment)
            {
                temp = arr[j];
                for (k = j - increment; k >= 0 && temp < arr[k]; k -= increment)
                {
                    arr[k + increment] = arr[k];
                }
                arr[k + increment] = temp;
            }
        }
        val--;
        if (increment != 1)
            increment = pow((float)2, val) - 1;
        else
            increment = 0;
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void sortArray(vector<int>& arr, int sortType) {
    switch (sortType) {
    case 1: selectionSort(arr); break;
    case 2: insertionSort(arr); break;
    case 3: bubbleSort(arr); break;
    case 4: mergeSort(arr, 0, arr.size() - 1); break;
    case 5: quickSort(arr, 0, arr.size() - 1); break;
    case 6: shellSort(arr); break;
    case 7: shellSortPratt(arr); break;
    case 8: shellSortHibb(arr); break;
    case 9: heapSort(arr); break;      
    }
}


// Главная функция
int main() {
    setlocale(LC_ALL, "ru");

    ofstream outFile("results.csv");
    if (!outFile.is_open()) {
        cout << "Ошибка открытия файла для записи результатов.\n";
        return 1;
    }

    outFile << "Sort Type,Array Type,Size,Time\n"; 

    for (int sortType = 6; sortType <= 9; sortType++) { 

        for (int arrayType = 1; arrayType <= 4; arrayType++) { 

            for (int size = 10000; size <= 100000; size += 10000) { 

                vector<int> arr;

                switch (arrayType) {
                case 1: arr = generateSortedArray(size); break;
                case 2: arr = generateNearlySortedArray(size); break;
                case 3: arr = generateRandomArray(size); break;
                case 4: arr = generateReversedArray(size); break;
                }

                vector<int> arrCopy = arr;

                auto start = chrono::high_resolution_clock::now();

                sortArray(arrCopy, sortType);

                auto end = chrono::high_resolution_clock::now();

                chrono::duration<double> duration = end - start;

                string sortName;

                switch (sortType) {
                case 1: sortName = "Selection Sort"; break;
                case 2: sortName = "Insertion Sort"; break;
                case 3: sortName = "Bubble Sort"; break;
                case 4: sortName = "Merge Sort"; break;
                case 5: sortName = "Quick Sort"; break;
                case 6: sortName = "Shell Sort"; break;
                case 7: sortName = "Shell Sort Pratt"; break;
                case 8: sortName = "Shell Sort Hibb"; break;
                case 9: sortName = "Heap Sort"; break;
                }

                string arrayName;

                switch (arrayType) {
                case 1: arrayName = "Отсортированный"; break;
                case 2: arrayName = "Почти отсортированный"; break;
                case 3: arrayName = "Случайный"; break;
                case 4: arrayName = "Обратный"; break;
                }

                saveResults(outFile, sortName, arrayName, size, duration.count());
            }
        }
    }

    outFile.close();
    cout << "Результаты сохранены в файл results.csv\n";

    return 0;
}

