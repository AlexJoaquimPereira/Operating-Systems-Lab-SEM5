// Original implementation using STL priority_queue
#include<iostream>
#include<algorithm>
#include<queue>
#include<ctime>
#include<iomanip>
using namespace std;

int n; // Number of processes
float avgTurnaroundTime;
float avgWaitingTime;

class process {
  public:
	int id;
    int at;
    int bt;
    int tat;
    int wt;
    int ct; // completion time
    unsigned int rt; // remaining time
	bool arrived; // whether process is working 

    // initialize remaining time
    // process(int rem) : rt(rem){}
    process(){
        tat = 0, wt = 0, arrived = false;
    }
 
    bool operator<(const process& p) const{
        return this->rt > p.rt;
    }
};

// sorts the processes acc. to arrival time
bool cmp (const process p1, const process p2){
	return (p1.at < p2.at);
}

// sorts the processes acc. to ID
bool cmp_id(const process p1, const process p2){
    return (p1.id < p2.id);
}

void SRTN(process *p){
    priority_queue<process>rq; // ready queue
    int proccount = 0; // current task
    int totTurnaroundTime = 0;
    int totWaitingTime = 0;
    int cpuTime = 0; // CPU ticks
    do{
        // process is running
        if (p[proccount].at == cpuTime){
            p[proccount].arrived = true;
            p[proccount].rt--;
        }
        cpuTime++;
        // incoming process -> push into rq
        if(p[proccount + 1].at == cpuTime){
            rq.push(p[proccount + 1]);
        }
        // top of rq < rt of current job -> push the job to rq, pop rq
        if(p[proccount].rt > rq.top().rt){
            p[proccount].arrived = false;
            rq.push(p[proccount]);
            proccount = rq.top().id - 1;
            rq.pop();
            p[proccount].arrived = true;
        }
        // process has ended
        if(p[proccount].rt == 0){
            p[proccount].ct = cpuTime;
            p[proccount].tat = p[proccount].ct - p[proccount].at;
            p[proccount].wt = p[proccount].tat - p[proccount].bt;
            p[proccount].arrived = false;
            totTurnaroundTime += p[proccount].tat;
            totWaitingTime += p[proccount].wt;
            proccount++;
        }
    }while (!rq.empty() && proccount > n);
    avgTurnaroundTime = totTurnaroundTime / n;
    avgWaitingTime = totWaitingTime / n;
}

void printSRTN(process *pro){
    // table
    cout << "PID\tAT\tBT\tWT\tTAT" << endl;
    for (int i = 0; i < n; i++)
        cout << pro[i].id << "\t" 
             << pro[i].at << "\t" 
             << pro[i].bt << "\t" 
             << pro[i].tat << "\t" 
             << pro[i].wt << "\n";

    cout << "Avg waiting time: " << std::setprecision(4) << avgWaitingTime << endl
         << "Avg tat: " << std::setprecision(4) << avgTurnaroundTime << endl;

    sort(pro, pro + n, cmp);

    /* gantt (will need to change)
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
    */
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
        processor[i].rt = processor[i].bt;
	}
	sort(processor, processor + n, cmp);
	SRTN(processor);
	printSRTN(processor);
	delete processor;
    return 0;
}