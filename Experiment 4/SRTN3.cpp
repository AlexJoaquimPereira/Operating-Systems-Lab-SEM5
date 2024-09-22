#include<iostream>
#include<iomanip>
#define pending true
#define finished false
#define MAX 50
using namespace std;

int n; // number of processes
float avgWT = 0, avgTAT = 0;

struct Gantt{
    int time;
    int procID;
};
Gantt gantt[MAX];

class process{
  public:
    int id, bt, at, wt, tat, rt;
    bool status; // whether process is working
};

int minimum(process p[]){
    int min = __INT_MAX__;
    for (int i = 0; i < n; i++)
        if (p[i].at < min)
            min = p[i].at;
    return min;
}

int SRTN (process p[]){
    int total_time = minimum(p);
    int k = 0;
    gantt[0].procID = 0;
    gantt[0].time = total_time;
    int gantt_iterator = 0;
    // cout << "Gantt Chart: " << total_time;
    while (true){
        // finds process with shortest remaining time at this clock tick
        int rt = __INT_MAX__;
        for (int j = 0; j < n; j++){
            if (p[j].status == pending && p[j].rt < rt && p[j].at <= total_time){
                k = j;
                rt = p[j].rt;
            }
        }
        // runs the process for p[k].rt clock ticks
        int j, check = 0;
        for (j = 0; j < p[k].rt; j++){
            // checks if there is another process which has arrived
            for (int l = 0; l < n; l++){
                if (l != k){
                    if (p[l].at == total_time + j){
                        if (p[l].rt < (p[k].rt - j)){
                            check = 1;
                            break;
                        }
                    }
                }
            }
            if (check)
                break;
        }
        total_time += j;
        // calculating tat and wt ie. process completed
        if (j == p[k].rt){
            p[k].status = finished;
            p[k].tat = total_time - p[k].at;
            avgTAT += p[k].tat;
            p[k].wt = p[k].tat - p[k].bt;
            avgWT += p[k].wt;
        }
        else p[k].rt -= j;
        // puts it in gantt chart
        gantt_iterator++;
        gantt[gantt_iterator].time = total_time;
        cout << gantt[gantt_iterator].time << endl; // debug
        gantt[gantt_iterator].procID = k + 1;
        // this is to check if all processes are completed
        int if_finished = 0;
        for (int i = 0; i < n; i++)
            if (p[i].status == pending)
                if_finished = 1;
        if (!if_finished)
            break;
    }
    return gantt_iterator;
}

void printSRTN(process *pro, int gantt_iterator){
    cout << "PID\tAT\tBT\tTAT\tWT" << endl;
    for (int i = 0; i < n; i++)
        cout << pro[i].id << "\t"
             << pro[i].at << "\t"
             << pro[i].bt << "\t"
             << pro[i].tat << "\t"
             << pro[i].wt << "\n";

    cout << "\nAvg waiting time: " << avgWT / n;
    cout << "\nAvg turnaround time: " << avgTAT / n << endl;

    for (int i = 1; i <= gantt_iterator; i++){
        cout << "|";
        int space = gantt[i].time - gantt[i - 1].time;
        for (int j = 0; j < space; j++){
            if (j == space / 2)
                cout << "P" << gantt[i].procID;
            else cout << " ";
        }
    }
    cout << "|";
    cout << endl;
    int global_ct = minimum(pro);
    cout << global_ct;
    for (int i = 1; i <= gantt_iterator; i++){
        int space = gantt[i].time - gantt[i - 1].time;
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

int main(){
    cout << "Enter number of processes: ";
    cin >> n;
    process *processor = new process[n];
    /*
    cout << "Enter the arrival times: \n";
    for (int i = 0; i < n; i++){
        processor[i].id = i + 1;
        cin >> processor[i].at;
    }
    cout << "Enter the burst times: \n";
    for (int i = 0; i < n; i++){
        cin >> processor[i].bt;
        processor[i].status = pending;
        processor[i].rt = processor[i].bt;
    }
    */
    cout << "Enter the processes (AT, BT):\n";
	for(int i = 0; i < n ; i++){
		processor[i].id = i + 1;
		cin >> processor[i].at >> processor[i].bt;
		processor[i].status = pending;
        processor[i].rt = processor[i].bt;
	}
    int gantt_iterator = SRTN(processor);
    printSRTN(processor, gantt_iterator);
    delete processor;
    return 0;
}
