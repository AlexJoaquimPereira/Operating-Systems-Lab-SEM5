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

int LOOK(int headPosition, int totalRequests, int requests[], bool direction) {
    int seekTime = 0, currentPosition = headPosition;
    sort(requests, totalRequests);

    int i = 0;
    while (i < totalRequests && requests[i] < headPosition) i++;
    cout<<"\nSeek Sequence: ";
    cout << "[H: " << headPosition << "] -> ";
    int left = i - 1;
    int right = i;
    if (direction) {
        while (left >= 0) {
            seekTime += abs(currentPosition - requests[left]);
            //cout << "(Distance: " << abs(currentPosition - requests[left]) << ", ";
            cout << requests[left] << " <- ";
            currentPosition = requests[left];
            left--;
        }

        if (right < totalRequests) {
            seekTime += abs(currentPosition - requests[right]);
            //cout << "(Distance: " << abs(currentPosition - requests[right]) << ", ";
            cout << requests[right] << " -> ";
            currentPosition = requests[right];
            right++;
        }

        while (right < totalRequests) {
            seekTime += abs(currentPosition - requests[right]);
            //cout << "(Distance: " << abs(currentPosition - requests[right]) << ", ";
            cout << requests[right] << " -> ";
            currentPosition = requests[right];
            right++;
        }
    } else { // Moving right (increasing)
        while (right < totalRequests) {
            seekTime += abs(currentPosition - requests[right]);
            //cout << "(Distance: " << abs(currentPosition - requests[right]) << ", ";
            cout << requests[right] << " -> ";
            currentPosition = requests[right];
            right++;
        }

        // Once right is done, reverse direction to the left (decreasing)
        if (left >= 0) {
            seekTime += abs(currentPosition - requests[left]);
            //cout << "(Distance: " << abs(currentPosition - requests[left]) << ", ";
            cout << requests[left] << " <- ";
            currentPosition = requests[left];
            left--;
        }

        // Continue processing remaining requests to the left
        while (left >= 0) {
            seekTime += abs(currentPosition - requests[left]);
            //cout << "(Distance: " << abs(currentPosition - requests[left]) << ", ";
            cout << requests[left] << " <- ";
            currentPosition = requests[left];
            left--;
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
    cout << "Enter the direction (0 for increasing disk number, 1 for decreasing): ";
    bool direction;
    cin >> direction;
    
    cout << "Enter the requests: ";
    for (int i = 0; i < totalRequests; i++) {
        cin >> requests[i];
    }
    int seek_time = LOOK(headPosition, totalRequests, requests, direction);
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
