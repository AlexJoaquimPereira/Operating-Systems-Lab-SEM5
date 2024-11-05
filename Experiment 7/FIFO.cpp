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

void FIFO(int reference_string[], int n, int frames){
    int frame[frames], frame_count = 0, page_faults = 0, k = 0;
    for (int i = 0; i < frames; i++)
        frame[i] = -1;
    bool flag = false;
    for (int i = 0; i < n; i++){
        flag = false;
        // check if page present
        for (int j = 0; j < frames; j++){
            if (frame[j] == reference_string[i]){
                flag = true;
                break;
            }
        }
        // if page not present
        if (flag == false){
            // check if frame isn't full
            if (frame_count < frames)
                frame[frame_count++] = reference_string[i], page_faults++;
            else{
                frame[k] = reference_string[i];
                k = (k + 1) % frames;
                page_faults++;
            }
        }
        print_frame(frame, frames, i, flag);
        cout << endl;
    }
    cout << "Number of page faults: " << page_faults << endl;
}

int main(){
    cout << "Enter number of pages: ", cin >> n;
    cout << "Enter the pages of the reference string: ";
    for (int i = 0; i < n; i++)
        cin >> reference_string[i];
    cout << "Enter number of frames: ", cin >> frames;
    FIFO(reference_string, n, frames);
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