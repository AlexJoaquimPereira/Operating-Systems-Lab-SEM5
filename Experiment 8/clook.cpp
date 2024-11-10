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

int CLOOK(int headPosition, int totalRequests, int requests[], bool direction) {
    int seekTime = 0, currentPosition = headPosition;
    sort(requests, totalRequests);
    int i = 0;
    while (i < totalRequests && requests[i] < headPosition) i++;

    cout << "\nSeek Sequence: ";
    cout << "[H: " << headPosition << "] -> ";

    if (direction == 0) {
        for (int j = i; j < totalRequests; j++) {
            seekTime += abs(currentPosition - requests[j]);
            cout << requests[j] << " -> ";
            currentPosition = requests[j];
        }

        if (i > 0) {
            seekTime += abs(currentPosition - requests[0]);
            cout << requests[0] << " <- ";
            currentPosition = requests[0];
            for (int j = 1; j < i; j++) {
                seekTime += abs(currentPosition - requests[j]);
                cout << requests[j] << " -> ";
                currentPosition = requests[j];
            }
        }
    } 
    else {
        for (int j = i - 1; j >= 0; j--) {
            seekTime += abs(currentPosition - requests[j]);
            cout << requests[j] << " <- ";
            currentPosition = requests[j];
        }
        if (i < totalRequests) {
            seekTime += abs(currentPosition - requests[totalRequests - 1]);
            cout << requests[totalRequests - 1] << " -> ";
            currentPosition = requests[totalRequests - 1];

            for (int j = totalRequests - 2; j >= i; j--) {
                seekTime += abs(currentPosition - requests[j]);
                cout << requests[j] << " <- ";
                currentPosition = requests[j];
            }
        }
    }

    return seekTime;
}

int main() {
    int totalRequests, headPosition, requests[MAX];
    cout << "Enter the number of requests: ";
    cin >> totalRequests;
    cout << "Enter the head position: ";
    cin >> headPosition;
    cout << "Enter the direction (0 for increasing disk number, 1 for decreasing disk number): ";
    bool direction;
    cin >> direction;
    
    cout << "Enter the requests: ";
    for (int i = 0; i < totalRequests; i++) {
        cin >> requests[i];
    }

    int seek_time = CLOOK(headPosition, totalRequests, requests, direction);
    cout << "\nTotal Seek Time: " << seek_time << endl;

    return 0;
}

/*
Example Input:
10
100
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
