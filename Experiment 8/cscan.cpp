#include <iostream>
#include <cmath>
#define MAX 50
using namespace std;

void sort(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int CSCAN(int headPosition, int totalRequests, int requests[], int cylinders, bool direction) {
    int seekTime = 0;
    int currentPosition = headPosition;
    sort(requests, totalRequests);

    int i = 0;
    while (i < totalRequests && requests[i] < headPosition) i++;
    cout<<"\nSeek Sequence: ";
    cout << "[H: " << headPosition << "] -> ";

    if (direction == 0) {
        for (int j = i; j < totalRequests; j++) {
            seekTime += abs(currentPosition - requests[j]);
            cout << requests[j] << " -> ";
            currentPosition = requests[j];
        }
        if (currentPosition != cylinders - 1) {
            seekTime += abs(currentPosition - (cylinders - 1));
            cout << (cylinders - 1) << " -> ";
            currentPosition = 0;
            cout << "0 -> ";
            seekTime += cylinders - 1;
        }
        for (int j = 0; j < i; j++) {
            seekTime += abs(currentPosition - requests[j]);
            cout << requests[j] << " -> ";
            currentPosition = requests[j];
        }
    }
    else {
        for (int j = i - 1; j >= 0; j--) {
            seekTime += abs(currentPosition - requests[j]);
            cout << requests[j] << " <- ";
            currentPosition = requests[j];
        }
        if (currentPosition != 0) {
            seekTime += abs(currentPosition - 0);
            cout << "0 <- ";
            currentPosition = cylinders - 1;
            cout << (cylinders - 1) << " <- ";
            seekTime += cylinders - 1;
        }
        for (int j = totalRequests - 1; j >= i; j--) {
            seekTime += abs(currentPosition - requests[j]);
            cout << requests[j] << " <- ";
            currentPosition = requests[j];
        }
    }
    return seekTime;
}

int main() {
    int totalRequests, headPosition, requests[MAX], cylinders;
    
    cout << "Enter the number of requests: ";
    cin >> totalRequests;
    cout << "Enter the head position: ";
    cin >> headPosition;
    cout << "Enter the number of cylinders: ";
    cin >> cylinders;
    cout << "Enter the direction (0 for increasing disk number, 1 for decreasing): ";
    bool direction;
    cin >> direction;
    cout << "Enter the requests: ";
    for (int i = 0; i < totalRequests; i++)
        cin >> requests[i];
    int seek_time = CSCAN(headPosition, totalRequests, requests, cylinders, direction);
    cout << "\nTotal Seek Time: " << seek_time << endl;

    return 0;
}

/*
Example Input:
10
100
200
0
27
129
110
160
186
147
41
10
64
120
*/
