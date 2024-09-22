// Uses priorityQueue as a minheap instead of priority_queue
#include<iostream>
#include<algorithm>
#include<queue>
#include<ctime>
#include<iomanip>
using namespace std;

int n; // Number of processes
float avgTurnaroundTime;
float avgWaitingTime;

// class for processes
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
};

// Class for priority queue, which is a min heap internally
class priorityQueue { 
    int *harr;
    int capacity;
    int heap_size;
public: 
    priorityQueue(int capacity); // initializes heap
    void priorityQueueify(int i); // to heapify a subtree with the root at given index 
    int parent(int i) { return (i-1)/2; } 
    int left(int i) { return (2*i + 1); } // to get index of left child of node at index i 
    int right(int i) { return (2*i + 2); } // to get index of right child of node at index i 
    int extractMin(); // to extract the root which is the minimum element 
    void decreaseKey(int i, int new_val); // Decreases key value of key at index i to new_val 
    int getMin() { return harr[0]; } // Returns the minimum key (key at root) from min heap 
    void deletekey(int i); // Deletes a key stored at index i 
    void insertKey(int k); // Inserts a new key 'k' 
}; 
  
priorityQueue::priorityQueue(int cap) { 
    heap_size = 0; 
    capacity = cap; 
    harr = new int[cap]; 
} 

void priorityQueue::insertKey(int k) { 
    heap_size++; 
    int i = heap_size - 1; 
    harr[i] = k;  
    while (i != 0 && harr[parent(i)] > harr[i]) { 
       swap(&harr[i], &harr[parent(i)]); 
       i = parent(i); 
    } 
}

void priorityQueue::decreaseKey(int i, int new_val) {
    harr[i] = new_val; 
    while (i != 0 && harr[parent(i)] > harr[i]) { 
       swap(&harr[i], &harr[parent(i)]); 
       i = parent(i); 
    } 
} 

int priorityQueue::extractMin() { 
    if (heap_size <= 0) 
        return INT_MAX; 
    if (heap_size == 1) { 
        heap_size--; 
        return harr[0]; 
    } 
    int root = harr[0]; 
    harr[0] = harr[heap_size-1]; 
    heap_size--; 
    priorityQueueify(0); 
    return root; 
} 
 
void priorityQueue::deleteKey(int i) { 
    decreaseKey(i, INT_MIN); 
    extractMin(); 
} 

void priorityQueue::priorityQueueify(int i) { 
    int l = left(i); 
    int r = right(i); 
    int smallest = i; 
    if (l < heap_size && harr[l] < harr[i]) 
        smallest = l; 
    if (r < heap_size && harr[r] < harr[smallest]) 
        smallest = r; 
    if (smallest != i) { 
        swap(&harr[i], &harr[smallest]); 
        priorityQueueify(smallest); 
    } 
}  
void swap(int *x, int *y) { 
    int temp = *x; 
    *x = *y; 
    *y = temp; 
} 

void SRTN(process *p){
    priorityQueue rq(n); // ready queue
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
            rq.push(proccount + 1);
        }
        // top of rq < rt of current job -> push the job to rq, pop rq
        if(p[proccount].rt > rq.top().rt){
            p[proccount].arrived = false;
            rq.push(proccount);
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