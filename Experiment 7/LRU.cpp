#include <iostream>
#define MAX 50
using namespace std;

int reference_string[MAX], n, frames;

void print_frame(int frame[], int n, int num, bool flag){
    cout << reference_string[num] << ": \t";
    if (flag) return;
    for (int i = 0; i < n; i++)
        frame[i] == -1 ? cout << "- " : cout << frame[i] << " ";
}

int find_LRU(int time[], int frames){
    int min = time[0], pos = 0;
    for (int i = 1; i < frames; i++){
        if (time[i] < min){
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void LRU(int reference[], int n, int frames){
    int frame[frames], time[frames];
    int page_faults = 0, count = 0;
    for (int i = 0; i < frames; i++){
        frame[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < n; i++){
        bool hit = false;
        // Check if the page is already present
        for (int j = 0; j < frames; j++){
            if (frame[j] == reference[i]){
                time[j] = ++count;
                hit = true;
                break;
            }
        }

        // If not found
        if (!hit){
            int pos = -1;
            // Check for an empty frame
            for (int j = 0; j < frames; j++){
                if (frame[j] == -1){
                    pos = j;
                    break;
                }
            }

            // If no empty frame is found, find the least recently used page
            if (pos == -1){
                pos = find_LRU(time, frames);
            }
            frame[pos] = reference[i];
            time[pos] = ++count;
            page_faults++;
        }
        print_frame(frame, frames, i, hit);
        cout << endl;
    }

    cout << "Number of page faults using LRU: " << page_faults << endl;
}

int main(){
    cout << "Enter number of pages: ", cin >> n;
    cout << "Enter the pages of the reference string: ";
    for (int i = 0; i < n; i++)
        cin >> reference_string[i];
    cout << "Enter number of frames: ", cin >> frames;

    LRU(reference_string, n, frames);

    return 0;
}

/*
12
1 2 3 4 1 2 5 1 2 3 4 5
3

21
4 2 3 0 3 2 1 7 5 5 1 2 0 3 0 2 0 1 7 0 7
3
*/