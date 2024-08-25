#include<iostream>
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
bool cmp(const process p1, const process p2){
    return (p1.at < p2.at);
}

// sorts the processes acc. to ID
bool cmp_id(const process p1, const process p2){
    return (p1.id < p2.id);
}

// Main sorting function (uses Insertion Sort as base)
// Function signature: sort(<array>, <array size>, <function to sort>)
void sort(process arr[], int n, bool (*compare)(const process, const process)){
    int i, j;
    process key;
    for (i = 1; i < n; i++){
        key = arr[i];
        j = i - 1;
        while (j >= 0 && compare (arr[j], key)) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void FCFS(process *pro){
    float awt = 0, atat = 0;
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
    sort(pro, n, cmp_id);
}

void printFCFS(process *pro){
    cout << "PID\tAT\tBT\tWT\tTAT" << endl;
    for (int i = 0; i < n; i++)
        cout << pro[i].id << "\t" << pro[i].at << "\t" << pro[i].bt << "\t" << pro[i].tat << "\t" << pro[i].wt << endl;

    cout << "Avg waiting time: " << std::setprecision(4) << avgWaitingTime << endl
         << "Avg tat: " << std::setprecision(4) << avgTurnaroundTime << endl;

    sort(pro, n, cmp);

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

int main(int argc, char const *argv[]){
    bool (*compare)(const process, const process); // pointer to comparison function
    cout << "Enter number of processes: ";
	cin >> n;
	process *processor = new process [n];
	cout << "Enter the arrival times:\n";
	for(int i = 0; i < n ; i++){
		processor[i].id = i + 1;
		cin >> processor[i].at;
		processor[i].arrived = false;
	}
    cout << "Enter the burst times:\n";
    for(int i = 0; i < n ; i++){
		cin >> processor[i].bt;
	}
	sort(processor, n, cmp);
	FCFS(processor);
	printFCFS(processor);
	delete processor;
    return 0;
}