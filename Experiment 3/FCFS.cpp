#include<iostream>
#include<algorithm>
#include<queue>
#include<ctime>
#include<iomanip>
using namespace std;

int n; // Number of processes
int avgTurnaroundTime;
int avgWaitingTime;

typedef struct {
	int id, at, bt, tat, wt;
	bool arrived;
}process;

bool cmp (const process p1, const process p2){
	return (p1.at < p2.at);
}

void printFCFS(process *p){
    cout << "Process\t" << "AT\t" << "BT\t" << "TAT\t" << "WT\t" << "\n";
    for(int i = 0; i < n; i++){
        cout << setw(7) << p[i].id << "\t"
             << setw(2) << p[i].at << "\t"
             << setw(2) << p[i].bt << "\t"
             << setw(3) << p[i].tat << "\t"
             << setw(2) << p[i].wt << "\n";
    }
    cout << "Average turnaround time: " << avgTurnaroundTime << endl;
    cout << "Average waiting time: " << avgWaitingTime << endl;
}

void FCFS(process *p){
    queue<process>pq;
    int proccount = 0;
    int totTurnaroundTime = 0;
    int totWaitingTime = 0;
    p[proccount].wt = 0;
    int cpuTime = 0;
    // do{
    for(int i = 0; i < n; i++){
        //if (p[proccount].at == cpuTime){
            //pq.push(p[proccount]);
            p[proccount + 1].wt = (p[proccount + 1].at + p[proccount + 1].bt+ p[proccount + 1]. wt) - p[proccount + 1].at;
            totWaitingTime += p[proccount].wt;
        //}
        //cpuTime++;
        //if(p[proccount].bt == cpuTime){
            //pq.pop();
            p[proccount].tat = cpuTime - p[proccount].at;
            totTurnaroundTime += p[proccount].tat;
            proccount++;
        //}
    }
    // }while (!pq.empty());
    avgTurnaroundTime = totTurnaroundTime / n;
    avgWaitingTime = totWaitingTime / n;
    printFCFS(p);
}

int main(){
	cout << "Enter number of processes: ";
	cin >> n;
	process *processor = new process [n];
	cout << "Enter the processes:\n";
	for(int i = 0; i < n ; i++){
		processor[i].id = i + 1;
		cin >> processor[i].at >> processor[i].bt;
		processor[i].arrived = false;
	}
	sort(processor, processor + n, cmp);
	FCFS(processor);
	printFCFS(processor);
	delete processor;
}
