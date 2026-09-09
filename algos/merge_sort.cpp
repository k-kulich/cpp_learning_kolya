#include <iostream>
#include <vector>

void merge(std::vector<int>& arr, int start, int mid, int end) {
    std::vector<int> temp;
    // объединить части до и после mid
    int i{start}, j{mid+1};  // индексы двух кусков, чтобы мы могли идти и сравнивать
    // само слияние
    while (i <= mid && j <= end) {
        if (arr[i] < arr[j]) {
            temp.push_back(arr[i]);
            ++i;
        } else {
            temp.push_back(arr[j]);
            ++j;
        }
    }
    // остались ли где-то элементы
    while (i <= mid) {
        temp.push_back(arr[i]);
        ++i;
    }

    while (j <= end) {
        temp.push_back(arr[j]);
        ++j;
    }
    // копируем все обратно в arr
    for (int k = 0; k < temp.size(); ++k) {
        arr[start + k] = temp[k];  // чисто все копируем
    }
}

void merge_sort(std::vector<int>& arr, int start, int end) {
    if (start < end) {
        // get the center to slice
        int mid = (end - start) / 2;
        merge_sort(arr, start, mid);
        merge_sort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}


int main() {
    int n;
    std::vector<int> data{n};
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> data[i];
    }
    merge_sort(data, 0, n - 1);

    for (int val: data) {
        std::cout << val;
    }

    return 0;
}
