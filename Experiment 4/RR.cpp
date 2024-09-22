#include<iostream>
#include<iomanip>
#include<stdlib.h>
#define pending true
#define finished false
#define MAX 50
using namespace std;

int n; // number of processes
int ts; // time sequence
float avgWT = 0, avgTAT = 0;

struct Gantt {
    int time;
    int procID;
};
Gantt gantt[MAX];

class process {
public:
    int id, bt, at, wt, tat, rt, pri;
    bool status; // whether process is pending
};

class Queue {
    int front, rear;
    process queue[MAX];
public:
    Queue() {
        front = 0;
        rear = -1;
    }

    void enqueue(process data) {
        queue[++rear] = data;
    }

    process dequeue() {
        if (front > rear) {
            cout << "\nQueue is empty\n";
            exit(1);
        }
        return queue[front++];
    }

    bool empty() {
        return (front > rear);
    }

    void printQueue() {
        cout << "Queue:  ";
        for (int i = rear; i >= front; i--) {
            cout << "P" << queue[i].id << "<-";
        }
        cout << "Top\n";
    }
};

Queue ready_queue;

void enqueueNewProcesses(process p[], int time) {
    for (int i = 0; i < n; i++) {
        if (p[i].status == pending && p[i].at <= time) {
            ready_queue.enqueue(p[i]);
            p[i].status = finished;
        }
    }
}

int RoundRobin(process p[]) {
    int gantt_iterator = 0;
    int time = 0;
    int remaining = n;

    while (remaining > 0) {
        enqueueNewProcesses(p, time);

        if (ready_queue.empty()) {
            time++;
            continue; // No process to execute, skip
        }

        ready_queue.printQueue();

        process current = ready_queue.dequeue();

        if (current.rt > ts) {
            // Execute process for TS
            time += ts;
            current.rt -= ts;
            enqueueNewProcesses(p, time);
            ready_queue.enqueue(current);
        } 
        else {
            time += current.rt;
            current.rt = 0;
            current.tat = time - current.at;
            current.wt = current.tat - current.bt;
            avgTAT += current.tat;
            avgWT += current.wt;
            remaining--;

            // Update the original process array with TAT and WT
            for (int i = 0; i < n; i++) {
                if (p[i].id == current.id) {
                    p[i].tat = current.tat;
                    p[i].wt = current.wt;
                    break;
                }
            }
        }

        gantt[gantt_iterator].procID = current.id;
        gantt[gantt_iterator].time = time;
        gantt_iterator++;
    }

    avgWT /= n;
    avgTAT /= n;
    return gantt_iterator;
}

void printRR(process *pro, int gantt_iterator) {
    cout << "PID\tAT\tBT\tTAT\tWT" << endl;
    for (int i = 0; i < n; i++)
        cout << pro[i].id << "\t"
             << pro[i].at << "\t"
             << pro[i].bt << "\t"
             << pro[i].tat << "\t"
             << pro[i].wt << "\n";

    cout << "\nAvg waiting time: " << avgWT;
    cout << "\nAvg turnaround time: " << avgTAT << endl;

    for (int i = 0; i < gantt_iterator; i++) {
        cout << "|";
        int space = gantt[i].time - (i == 0 ? 0 : gantt[i - 1].time);
        for (int j = 0; j < space; j++) {
            if (j == space / 2)
                cout << "P" << gantt[i].procID;
            else cout << " ";
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
        if (global_ct < 10)
            cout << "  " << global_ct;
        else
            cout << " " << global_ct;
    }
    cout << endl;
}

int main() {
    cout << "Enter number of processes: ";
    cin >> n;
    process *processor = new process[n];

    cout << "Enter the processes (AT, BT):\n";
    for (int i = 0; i < n ; i++) {
        processor[i].id = i + 1;
        cin >> processor[i].at >> processor[i].bt;
        processor[i].status = pending;
        processor[i].rt = processor[i].bt;
    }

    cout << "Enter the time sequence: ";
    cin >> ts;

    int gantt_iterator = RoundRobin(processor);
    printRR(processor, gantt_iterator);

    delete[] processor;
    return 0;
}

/*
Example Input:
5
0 3
2 6
4 4
6 5
8 2
4
*/
