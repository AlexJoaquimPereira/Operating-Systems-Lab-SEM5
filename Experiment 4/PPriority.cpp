#include<iostream>
#include<iomanip>
#define not_arrived 0
#define arrived 1
#define completed 2
#define MAX 50
using namespace std;

int n; // Number of processes
int currentTime = 0, remainingTime = 0, globalOrder = 1;
float avgTurnaroundTime;
float avgWaitingTime;

typedef struct {
	int id, at, bt, pri, tat, wt, ct, rt;
    int flag; // if process has arrived
}process;

struct Gantt{
    int time;
    int procID;
};
Gantt gantt[MAX];

// sorts the processes acc. to arrival time
bool cmp (const process p1, const process p2){
	return (p1.at < p2.at);
}

// sorts the processes acc. to priority
bool cmp_pri (const process p1, const process p2){
	if(p1.at == p2.at) return (p1.pri < p2.pri);
    else return (p1.at < p2.at);
}

// sorts the processes acc. to ID
bool cmp_id(const process p1, const process p2){
    return (p1.id < p2.id);
}

// Main sorting function (uses insertion sort as base)
// sort(<array>, <array size>, <function to sort>)
void sort(process arr[], int n, bool (*compare)(const process, const process)){
    int i, j;
    process key;
    for (i = 1; i < n; i++){
        key = arr[i];
        j = i - 1;
        while (j >= 0 && compare (key, arr[j])) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int maxPri(process p[]){
    int min = __INT_MAX__;
    for (int i = 0; i < n; i++)
        if (p[i].pri < min)
            min = p[i].pri;
    return min;
}

int PP(process *pro){
    int total_time = maxPri(pro);
    float awt = 0, atat = 0;
    int ctime = 0;
    gantt[0].procID = 0;
    gantt[0].time = total_time;
    int remctime = pro[0].at;
    for(int i = 0; i < n; i++) remctime += pro[i].bt;
    // CPU clocks
    while (remainingTime){
        for (int i = 0; i < n; i++){
            if (pro[i].flag == not_arrived && pro[i].at <= currentTime)
                pro[i].flag = arrived;
        }
        int index = -1, highest_priority = __INT_MAX__;
        for (int i = 0; i < n; i++){
            if (pro[i].flag == arrived && (pro[i].pri < highest_priority))
                highest_priority = pro[i].pri, index = i;
        }
        if (index == -1){
            currentTime++;
            continue;
        }
        // pro[index].order = globalOrder++;
        pro[index].flag = completed;
        remainingTime -= pro[index].bt;
        currentTime += pro[index].bt;
    }
    // calc tat, wt, atat, awt
    for (int i = 0; i < n; i++){
        int ct = 0;
        ct += pro[i].at;
        for (int j = 0; j < i; j++)
            ct += pro[j].bt;
        ct += pro[i].bt;
        pro[i].tat = ct - pro[i].at;
        pro[i].wt = pro[i].tat - pro[i].bt;
        atat += pro[i].tat;
        awt += pro[i].wt;
    }
    avgTurnaroundTime = atat / n;
    avgWaitingTime = awt / n;
    return 0;
}

int PP_Preemptive(process *pro){
    int total_time = maxPri(pro) + 1;
    float awt = 0, atat = 0;
    int currentTime = 0;
    // int remainingTime = 0;
    int gantt_iterator = 0;
    gantt[0].procID = 0;
    gantt[0].time = total_time;
    for (int i = 0; i < n; i++) {
        pro[i].rt = pro[i].bt;
        pro[i].flag = not_arrived;
    }
    int prevproc = -1;
    // CPU simulation
    while (true) {
        // process status
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
        // runs the process for p[k].rt clock ticks
        int j, preempt = 0;
        for (j = 0; j < pro[index].rt; j++){
            // checks if there is another process which has arrived having higher pri
            for (int l = 0; l < n; l++){
                if (l != index){
                    if (pro[l].at == total_time + j){
                        if (pro[l].pri < (pro[index].pri)){
                            preempt = 1;
                            break;
                        }
                    }
                }
            }
            if (preempt)
                break;
        }
        if (index == -1) {
            currentTime++;
            continue;
        }
        total_time += j;
        currentTime += j;
        remainingTime -= j;
        pro[index].rt -= j;
        // process completed
        if (pro[index].rt == j) {
            pro[index].flag = completed;
            pro[index].rt = currentTime;
            pro[index].tat = pro[index].rt - pro[index].at;
            pro[index].wt = pro[index].tat - pro[index].bt;
            atat += pro[index].tat;
            awt += pro[index].wt;
        }
        else pro[index].rt -= j;
        // adds to gantt
        gantt_iterator++;
        gantt[gantt_iterator].time = total_time;
        cout << gantt[gantt_iterator].time << " " << index + 1 << endl; // debug
        gantt[gantt_iterator].procID = index + 1;
        // this is to check if all processes are completed
        int if_finished = 1;
        for (int i = 0; i < n; i++)
            if (pro[i].flag == arrived || pro[i].flag == not_arrived)
                if_finished = 0;
        if (if_finished)
            break;
    }
    avgTurnaroundTime = atat / n;
    avgWaitingTime = awt / n;
    return gantt_iterator;
}

void printPP(process *pro, int gantt_iterator){
    cout << "PID\tAT\tBT\tPri\tTAT\tWT" << endl;
    for (int i = 0; i < n; i++)
        cout << pro[i].id << "\t"
             << pro[i].at << "\t"
             << pro[i].bt << "\t"
             << pro[i].pri << "\t"
             << pro[i].tat << "\t"
             << pro[i].wt << "\n";

    cout << "\nAvg waiting time: " << avgWaitingTime;
    cout << "\nAvg turnaround time: " << avgTurnaroundTime << endl;

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
    int global_ct = maxPri(pro);
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

int main(int argc, char const *argv[]){
    cout << "Enter number of processes: ";
	cin >> n;
	process *processor = new process [n];
	cout << "Enter the processes (AT, BT, Pri):\n";
	for(int i = 0; i < n ; i++){
		processor[i].id = i + 1;
		cin >> processor[i].at >> processor[i].bt >> processor[i].pri;
        processor[i].flag = not_arrived;
        processor[i].rt = processor[i].bt;
        remainingTime += processor[i].rt;
	}
	sort(processor, n, cmp);
	int gantt_iterator = PP_Preemptive(processor);
	printPP(processor, gantt_iterator);
	delete processor;
    return 0;
}