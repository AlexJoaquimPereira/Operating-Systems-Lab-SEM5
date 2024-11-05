#include<iostream>
#define MAX 50
using namespace std;

int reference_string[MAX], n, frames;

void print_frame(int frame[], int n, int num, bool flag){
    cout << reference_string[num] << ": \t";
    if (flag) return;
    for (int i = 0; i < n; i++)
        frame[i] == -1 ? cout << "- " : cout << frame[i] << " ";
}

int find(int frame[], int frames, int page) {
    for (int i = 0; i < frames; i++) {
        if (frame[i] == page) {
            return i;
        }
    }
    return -1;
}

int find_optimal(int frame[], int frames, int reference[], int n, int current_index) {
    int farthest = -1, target_index = -1;
    for (int i = 0; i < frames; i++) {
        int j;
        for (j = current_index + 1; j < n; j++) {
            if (reference[j] == frame[i]) {
                if (j > farthest) {
                    farthest = j;
                    target_index = i;
                }
                break;
            }
        }
        // If a page is not found replace it
        if (j == n) {
            return i;
        }
    }
    return (target_index == -1) ? 0 : target_index;
}

void Optimal(int reference[], int n, int frames) {
    int frame[frames];
    int page_faults = 0, ix = 0;
    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        bool hit = false;
        int page = reference[i];

        // Check if the page in the frame
        if (find(frame, frames, page) != -1)
            hit = true;
        else{
            page_faults++;
            if (frame[ix] == -1) {
                frame[ix] = page;
                ix = (ix + 1) % frames;
            }
            else {
                int target = find_optimal(frame, frames, reference, n, i);
                frame[target] = page;
            }
        }
        print_frame(frame, frames, i, hit);
        cout << endl;
    }

    cout << "Number of page faults: " << page_faults << endl;
}

int main() {
    cout << "Enter number of pages: ", cin >> n; 
    cout << "Enter the pages of the reference string: ";
    for (int i = 0; i < n; i++)
        cin >> reference_string[i];
    cout << "Enter number of frames: ", cin >> frames;
    Optimal(reference_string, n, frames);

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