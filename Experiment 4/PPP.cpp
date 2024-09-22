#include <iostream>
#include <iomanip>
#define not_arrived 0
#define arrived 1
#define completed 2
#define MAX 50

using namespace std;

int n; // Number of processes
int currentTime = 0, remainingTime = 0;
float avgTurnaroundTime;
float avgWaitingTime;

typedef struct {
    int id, at, bt, pri, tat, wt, ct, rt;
    int flag; // if process has arrived
} process;

struct Gantt {
    int time;
    int procID;
};
Gantt gantt[MAX];

// Sorts the processes according to arrival time
bool cmp(const process p1, const process p2) {
    return (p1.at < p2.at);
}

// Main sorting function (insertion sort)
void sort(process arr[], int n, bool (*compare)(const process, const process)) {
    int i, j;
    process key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && compare(key, arr[j])) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int PP_Preemptive(process *pro) {
    int gantt_iterator = 0;
    float awt = 0, atat = 0;
    
    for (int i = 0; i < n; i++) {
        pro[i].rt = pro[i].bt;
        pro[i].flag = not_arrived;
    }

    while (remainingTime > 0) {
        //process status
        for (int i = 0; i < n; i++) {
            if (pro[i].flag == not_arrived && pro[i].at <= currentTime)
                pro[i].flag = arrived;
        }
        // highest priority at that time
        int index = -1;
        int highest_priority = __INT_MAX__;
        for (int i = 0; i < n; i++) {
            if (pro[i].flag == arrived && pro[i].pri < highest_priority && pro[i].rt > 0) {
                highest_priority = pro[i].pri;
                index = i;
            }
        }

        if (index == -1) {
            currentTime++;
            continue;
        }

        // Run the process for 1 time unit
        pro[index].rt -= 1;
        remainingTime -= 1;
        currentTime++;

        if (gantt_iterator == 0 || gantt[gantt_iterator - 1].procID != pro[index].id) {
            gantt[gantt_iterator].procID = pro[index].id;
            gantt[gantt_iterator].time = currentTime;
            gantt_iterator++;
        }
        // proc complete
        if (pro[index].rt == 0) {
            pro[index].flag = completed;
            pro[index].ct = currentTime;
            pro[index].tat = pro[index].ct - pro[index].at;
            pro[index].wt = pro[index].tat - pro[index].bt;
            atat += pro[index].tat;
            awt += pro[index].wt;
        }
    }

    avgTurnaroundTime = atat / n;
    avgWaitingTime = awt / n;
    return gantt_iterator;
}

void printPP(process *pro, int gantt_iterator) {
    cout << "PID\tAT\tBT\tPri\tTAT\tWT" << endl;
    for (int i = 0; i < n; i++) {
        cout << pro[i].id << "\t"
             << pro[i].at << "\t"
             << pro[i].bt << "\t"
             << pro[i].pri << "\t"
             << pro[i].tat << "\t"
             << pro[i].wt << "\n";
    }

    cout << "\nAvg waiting time: " << avgWaitingTime;
    cout << "\nAvg turnaround time: " << avgTurnaroundTime << endl;

    for (int i = 0; i < gantt_iterator; i++) {
        cout << "|";
        int space = gantt[i].time - (i == 0 ? 0 : gantt[i - 1].time);
        for (int j = 0; j < space; j++) {
            if (j == space / 2)
                cout << "P" << gantt[i].procID;
            else
                cout << " ";
        }
    }
    cout << "|";
    cout << endl;

    int global_ct = 0;
    cout << global_ct;
    for (int i = 0; i < gantt_iterator; i++) {
        int space = gantt[i].time - (i == 0 ? 0 : gantt[i - 1].time);
        for (int j = 0; j < space - 1; j++)
            cout << " ";
        global_ct += space;
        cout << (global_ct < 10 ? "  " : " ") << global_ct;
    }
    cout << endl;
}

int main(int argc, char const *argv[]) {
    cout << "Enter number of processes: ";
    cin >> n;
    process *processor = new process[n];
    cout << "Enter the processes (AT, BT, Pri):\n";
    for (int i = 0; i < n; i++) {
        processor[i].id = i + 1;
        cin >> processor[i].at >> processor[i].bt >> processor[i].pri;
        processor[i].flag = not_arrived;
        processor[i].rt = processor[i].bt;
        remainingTime += processor[i].rt;
    }
    sort(processor, n, cmp);
    int gantt_iterator = PP_Preemptive(processor);
    printPP(processor, gantt_iterator);
    delete[] processor;
    return 0;
}
/*
4
0 10 5
1 6 4
3 2 2
5 4 0
 */