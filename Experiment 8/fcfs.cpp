#include <iostream>
#define MAX 50

using namespace std;

int FCFS(int headPosition, int totalRequests, int requests[]){
    int seekTime = 0, currentPosition = headPosition;
    cout << "\nSeek Sequence: ";
    cout << "[H: " << currentPosition << "]->";
    for (int i = 0; i < totalRequests; i++){
        seekTime += abs(currentPosition - requests[i]);
        currentPosition = requests[i];
        if (i==totalRequests-1) cout<<currentPosition;
        else cout << currentPosition << "->";
    }
    return seekTime;
}

int main(){
    int totalRequests, headPosition, requests[MAX];
    cout << "Enter the number of requests: ";
    cin >> totalRequests;
    cout << "Enter the head position: ";
    cin >> headPosition;
    cout << "Enter the requests: ";
    for (int i = 0; i < totalRequests; i++)
        cin >> requests[i];

    int seek_time = FCFS(headPosition, totalRequests, requests);
    cout << "\nTotal Seek Time: " << seek_time <<endl;

    return 0;
}

/*
10
100
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

/*
TestCase
8
50
176
79
34
60
92
11
31
114

*/
