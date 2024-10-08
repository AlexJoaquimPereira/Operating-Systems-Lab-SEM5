#include <iostream>
#include <iomanip>
#define BUFFERSIZE 5
using namespace std;

int mutex = 1, full = 0, empty = BUFFERSIZE;
int in = 0, out = 0, counter = 0;
char buffer[BUFFERSIZE];

void signal(int &S) {
    S++;
}

int wait(int &S) {
    if (S <= 0) {
        cout << "Cannot proceed due to insufficient resources\n";
        return 0;
    }
    S--;
    return 1;
}

void produce() {
    if (!wait(::empty) || !wait(mutex)) return; 
    char next_prod;
    
    cout << "Enter an item to produce: ";
    cin >> next_prod;

    buffer[in] = next_prod;
    in = (in + 1) % BUFFERSIZE;
    cout << "Item produced: " << next_prod << endl;
    
    counter++;
    signal(mutex);
    signal(full);
}

void consume() {
    if (!wait(full) || !wait(mutex)) return;
    char next_cons;
    
    next_cons = buffer[out];
    out = (out + 1) % BUFFERSIZE;
    cout << "Item consumed: " << next_cons << endl;
    
    counter--;
    signal(mutex);
    signal(::empty);
}

void display() {
    for(int i = 0; i < BUFFERSIZE; i++) cout << "----";
    cout << "-\n| ";
    for (int i = 0; i < BUFFERSIZE; ++i) {
        if ((out < in && i >= out && i < in) || (out > in && (i >= out || i < in)) || (in == out && counter > 0)) {
            cout << buffer[i] << " | ";
        } else {
            cout << "  | ";
        }
    }
    cout << endl;
    for(int i = 0; i < BUFFERSIZE; i++) cout << "----";
    cout << "-\n| ";
}

int main() {
    int choice;
    do {
        cout << "\nSelect the operation to be performed:\n";
        cout << "1. Produce \n";
        cout << "2. Consume \n";
        cout << "3. Display \n";
        cout << "4. Exit\n";
        cin >> choice;
        switch (choice) {
            case 1:
                produce();
                display();
                break;
            case 2:
                consume();
                display();
                break;
            case 3:
                display();
                break;
            case 4:
                break;
            default:
                cout << "Select a valid option" << endl;
        }
    } while (choice != 4);
    return 0;
}
