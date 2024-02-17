#include <iostream>
#include <algorithm>
#include <windows.h>
using namespace std;

struct Item {
    int value, weight;
    Item(int value, int weight) : value(value), weight(weight) {}
};

bool Compare(struct Item a, struct Item b) {
    return a.value > b.value;
}

void Knapsack(struct Item arr[], int N, int size) {
    sort(arr, arr + size, Compare);

    int K[5][61] = { 0 };

    for (int i = 0; i <= size; i++) {
        for (int w = 0; w <= N; w++) {
            if (i == 0 || w == 0) {
                K[i][w] = 0;
            }
            else if (arr[i - 1].weight <= w) {
                K[i][w] = max(arr[i - 1].value + K[i - 1][w - arr[i - 1].weight], K[i - 1][w]);
            }
            else {
                K[i][w] = K[i - 1][w];
            }
        }
    }
    cout << K[size][N]<<"\n";
}

DWORD WINAPI ThreadFunc(LPVOID lpParam) {
    struct Item* data = (struct Item*)lpParam;
    Knapsack(data, 60, 4);
    return 0;
}

int main() {
    setlocale(LC_ALL,"ru");
    HANDLE firstHThread;
    HANDLE secondHThread;
    DWORD IDThread;

    Item firstArray[5] = { {100, 10}, {280, 40}, {120, 20}, {120, 24}, {200, 30} };
    Item secondArray[5] = { {85, 7}, {210, 25}, {345, 34}, {85, 3}, {530, 45} };

    firstHThread = CreateThread(NULL, 0, ThreadFunc, firstArray, 0, &IDThread);
    

    if (firstHThread == NULL) {
        cout << "Невозможно создать поток 1" << endl;
        return 1;
    }   

    secondHThread = CreateThread(NULL, 0, ThreadFunc, secondArray, 0, &IDThread);

    if (secondHThread == NULL) {
        cout << "Невозможно создать поток 2" << endl;
        return 1;
    }

    cout << "Hello world\n";

    WaitForSingleObject(firstHThread, INFINITE);
    CloseHandle(firstHThread);

    WaitForSingleObject(secondHThread, INFINITE);
    CloseHandle(secondHThread);

    return 0;
}
