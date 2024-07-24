#include<iostream>
#include<algorithm>
#include<queue>
#include<ctime>
#include<iomanip>
using namespace std;

int n; // Number of processes
float avgTurnaroundTime;
float avgWaitingTime;

typedef struct {
	int id, at, bt, tat, wt, ct;
	bool arrived;
}process;

// sorts the processes acc. to arrival time
bool cmp (const process p1, const process p2){
	return (p1.at < p2.at);
}

// sorts the processes acc. to ID
bool cmp_id(const process p1, const process p2){
    return (p1.id < p2.id);
}

void FCFS(process *pro){
    int awt = 0, atat = 0;
    int ctime = 0; // clock ticks
    for (int i = 0; i < n; i++){
        if (pro[i].at > ctime)
            ctime = pro[i].at + pro[i].bt;
        else ctime += pro[i].bt;

        pro[i].ct = ctime;
        pro[i].tat = pro[i].ct - pro[i].at;
    }

    for (int i = 0; i < n; i++)
        pro[i].wt = pro[i].tat - pro[i].bt;

    for (int i = 0; i < n; i++)
        atat += pro[i].tat, awt += pro[i].wt;
    
    avgTurnaroundTime = atat / n;
    avgWaitingTime = awt / n;
    sort(pro, pro + n, cmp_id);
}

void printFCFS(process *pro){
    cout << "PID\tAT\tBT\tWT\tTAT" << endl;
    for (int i = 0; i < n; i++)
        cout << pro[i].id << "\t" << pro[i].at << "\t" << pro[i].bt << "\t" << pro[i].tat << "\t" << pro[i].wt << endl;

    cout << "Avg waiting time: " << std::setprecision(4) << avgWaitingTime << endl
         << "Avg tat: " << std::setprecision(4) << avgTurnaroundTime << endl;

    sort(pro, pro + n, cmp);

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
	cout << "Enter the processes (AT, BT):\n";
	for(int i = 0; i < n ; i++){
		processor[i].id = i + 1;
		cin >> processor[i].at >> processor[i].bt;
		processor[i].arrived = false;
	}
	sort(processor, processor + n, cmp);
	FCFS(processor);
	printFCFS(processor);
	delete processor;
    return 0;
}