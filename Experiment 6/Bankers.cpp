#include<iostream>
#include<vector>
#define MAX_SIZE 50

using namespace std;

int Available[MAX_SIZE]; //Available resources; [j] = k then k instances of j
int Max[MAX_SIZE][MAX_SIZE]; // resources in the system
int Allocation[MAX_SIZE][MAX_SIZE]; // Allocated resources
int Need[MAX_SIZE][MAX_SIZE]; // resources needed by process

int n; // no of processes
int m; // no of resource types

// Checks if processes are safe
bool safety(){
	int Work[m];
	bool Finish[n];
	for(int j = 0; j < m; j++) Work[j] = Available[j];
	for(int j = 0; j < n; j++) Finish[j] = false;
	
	int i;
	int safeSeq[n + 1]; // Safe sequence
	int count = 0;
	bool found = false;
    while (count < n){
        for (int i = 0; i < n; i++){
            if (!Finish[i]){
                int j;
                for (j = 0; j < m; j++){
                    if (Need[i][j] > Work[j])
                        break;
                }
                if (j == m){
                    for (int k = 0; k < m; k++)
                        Work[k] += Allocation[i][k];
                    safeSeq[count++] = i;
                    Finish[i] = true;
                    found = true;
                }
            }
        }
	}
	if(found){
		cout << "Safe sequence found: ";
		for(int j = 0; j < count; j++) cout << "P" << safeSeq[j] << " - ";
		cout << endl;
		return true;
	}
	cout << "Safe sequence not found\n";
	return false;
}

// Step 1 but inverted
bool step_1(int Request[], int i){
	for (int j = 0; j < m; j++)
		if(Request[j] > Need[i][j]) return false;
	return true;
}

// Step 2 inverted
bool step_2(int Request[], int i){
	for (int j = 0; j < m; j++)
		if(Request[j] > Available[j]) return false;
	return true;
}

// Request[] - request vector
// i - the process for which request
void Bankers(int Request[], int i){
	if(!step_1(Request, i)){ 
		cout << "Process has exceeded claim\n";
		return;
	}
	else if(!step_2(Request, i)){ 
		cout << "P" << i << " must wait till resources are available\n";
		return;
	}
	else{
		for(int j = 0; j < m; j++){
			Available[j] = Available[j] - Request[j];
			Allocation[i][j] = Allocation[i][j] + Request[j];
			Need[i][j] = Need[i][j] - Request[j];
		}
		if(safety()){
			cout << "Resources are allocated to P" << i << endl;
		}
		else {
			cout << "Resources are not allocated to P" << i << endl;
			for(int j = 0; j < m; j++){ // return back to OG state
				Available[j] = Available[j] + Request[j];
				Allocation[i][j] = Allocation[i][j] - Request[j];
				Need[i][j] = Need[i][j] + Request[j];
			}
		}
	}
}

void displaySystem() {
    cout << "Max Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << Max[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\nAllocation Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << Allocation[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << Need[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\nAvailable Resources:\n";
    for (int j = 0; j < m; j++) {
        cout << Available[j] << " ";
    }
    cout << endl;
}

int main(){
	cout << "Enter number of processes: ";
	cin >> n;
	cout << "Enter number of resource types: ";
	cin >> m;

	int Request[m]; // Request vector

	cout << "Enter Available resources:\n";
    for (int j = 0; j < m; j++) 
        cin >> Available[j];

	cout << "Enter Max matrix: \n";
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> Max[i][j];
	
	cout << "Enter Allocation matrix: \n";
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> Allocation[i][j];

	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			Need[i][j] = Max[i][i] - Allocation[i][j];

	int choice = 3;
	do{
		cout << "1. Enter a new request\n";
		cout << "2. Display the system\n";
		cout << "3. Exit\n";
		cin >> choice;
		switch (choice){
			case 1:
				int i;
				cout << "Enter the process: ";
				cin >> i;
				cout << "Enter a new request vector: ";
				for(int j = 0; j < m; j++)
					cin >> Request[j];
				Bankers(Request, i);
				displaySystem();
				break;
			case 2: displaySystem();
				break;
			default: cout << "Invalid option\n";
		}
	}while(choice != 3);
}


/*
3
3
3 3 2
7 5 3
3 2 2
9 0 2
0 1 0
2 0 0
3 0 2

3
3
7 7 10
3 6 8
4 3 3
3 4 4
2 2 3
2 0 3
1 2 4

4
3
1 0 0
5 2 0
1 0 0
2 1 2
1 2 1
2 1 0
1 0 0
0 1 2
1 1 1
*/