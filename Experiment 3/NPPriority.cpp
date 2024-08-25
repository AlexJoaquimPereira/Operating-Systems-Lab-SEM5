#include<iostream>
#include<iomanip>
#define not_arrived 0
#define arrived 1
#define completed 2
using namespace std;

int n; // Number of processes
int currentTime = 0, remainingTime = 0, globalOrder = 1;
float avgTurnaroundTime;
float avgWaitingTime;

typedef struct {
	int id, at, bt, pri, tat, wt, ct, order;
    int flag; // if process has arrived
}process;

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

// sorts the processes acc. to order of execution
bool cmp_order(const process p1, const process p2){
    return p1.order < p2.order;
}

// or I got this idea
/*
typedef enum {cmp, cmp_id, cmp_pri};
then use switch case
*/

bool compare(const process p1, const process p2){
    if(p1.at == p2.at) return (p1.pri < p2.pri);
    else return (p1.at < p2.at);
}

void swap (process p1, process p2){
    process temp = p1;
    p1 = p2;
    p2 = temp;
}

// if this program is done then we need to just use FCFS fun. and don't even sort it back
void prisort(process arr[], int n){
    int i, j;
    process key;
    for (i = 1; i < n; i++){
        for(j = 1; j < n - i - 1; j++){
            if(arr[j].at == arr[j+1].at){
                if(arr[j].pri > arr[j+1].pri)
                    swap(arr[j], arr[j+1]);
            }
            else if (arr[j].at > arr[j+1].at)
                swap(arr[j], arr[j+1]);
        }
    }
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

void NPP(process *pro){
    float awt = 0, atat = 0;
    int ctime = 0;
    int remctime = pro[0].at;
    for(int i = 0; i < n; i++) remctime += pro[i].bt;
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
        pro[index].order = globalOrder++;
        pro[index].flag = completed;
        remainingTime -= pro[index].bt;
        currentTime += pro[index].bt;
    }
    sort(pro, n, cmp_order);
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
}

void printNPP(process *pro){
    cout << "PID\tAT\tBT\tPri\tWT\tTAT" << endl;
    for (int i = 0; i < n; i++)
        cout << pro[i].id << "\t"
             << pro[i].at << "\t"
             << pro[i].bt << "\t"
             << pro[i].pri << "\t"
             << pro[i].tat << "\t"
             << pro[i].wt << endl;

    cout << "Avg waiting time: " << std::setprecision(4) << avgWaitingTime << endl
         << "Avg tat: " << std::setprecision(4) << avgTurnaroundTime << endl;

    prisort(pro, n);

    for (int i = 0; i < n; i++){
        cout << "|";
        for (int j = 0; j < pro[i].bt; j++){
            if (j == pro[i].bt / 2)
                cout << "P" << pro[i].id;
            else cout << " ";
        }
    }
    cout << "|";
    cout << endl;
    int global_ct = 0;
    cout << global_ct;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < pro[i].bt - 1; j++)
            cout << " ";
        global_ct += pro[i].bt;
        if (global_ct < 10)
            cout << "  " << global_ct;
        else
            cout << " " << global_ct;
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    cout << "Enter number of processes: ";
	cin >> n;
	process *processor = new process [n];
	cout << "Enter the processes (AT, BT, Pri):\n";
	for(int i = 0; i < n ; i++){
		processor[i].id = i + 1;
		cin >> processor[i].at >> processor[i].bt >> processor[i].pri;
        processor[i].wt = processor[i].tat = processor[i].order = -1;
        processor[i].flag = not_arrived;
        remainingTime += processor[i].bt;
	}
	sort(processor, n, cmp);
	NPP(processor);
	printNPP(processor);
	delete processor;
    return 0;
}
