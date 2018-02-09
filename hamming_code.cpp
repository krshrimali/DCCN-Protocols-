#include <iostream>
#include <math.h>

using namespace std;
int main() {
    int n, r;
    cout << "Enter number of bits: (Here, preferrably 4)" << endl;
    cin >> n;
    int* D = new int[n];

    cout << "Enter the message to be transmitted: " << endl; 
    for(int i = n-1; i >= 0; i--) {
        cin >> D[i];
    } 
    // print D

    cout << endl;

    if(n == 4) {
        r = 3; 
        int e = n + r;
        int* new_D = new int[e];

        for(int i = 1; i <= e; i++) {
            new_D[i] = 0;
        }
        
        // since r = 3 : 1, 2, 4

        for(int i = e, j = 3; i > 0; i--) {
            if(i == 1 || i == 2 || i == 4)
                continue;
            // cout << "i : " << i << " j: " << j <<  endl;
            // cout << j << " " << D[j] << endl;
            new_D[i] = D[j];
            //cout << "\n" << new_D[i] << endl;
            j--;
        }


        // 1 3 5 7
        // 2 3 6 7
        // 4 5 6 7
        int check[3][4] = { { 1, 3, 5, 7 }, { 2, 3, 6, 7 }, { 4, 5, 6, 7 } };
        // cout << check[0][2] << endl;

        for(int i = 0; i < r; i++) {
            int pos = pow(2, i);
            int count = 0; int toBeInserted = 0;
            for(int j = 0; j < 4; j++) {
                int check_pos = check[i][j];
                if(new_D[check_pos] == 1 && check_pos != pos)
                    count++;
            }
            if(count % 2 == 0){
                // even number of ones
                toBeInserted = 0;
            } else {
                toBeInserted = 1;
            }
            new_D[pos] = toBeInserted;
        }

        cout << "Transmitted message: " << endl;
        for(int i = e; i >= 1; i--) 
            cout << new_D[i] << "\n";
        cout << endl;
        
        cout << "Transmission work over.\n";
        // Receiver side
        int receiver_D[e]; 
        cout << "Enter Received Message.\n";
        for(int i = e; i > 0; i--) {
            cin >> receiver_D[i];
        }
        
        int new_[3];

        for(int i = 0; i < r; i++) {
            int pos = pow(2, i);
            int count = 0; int toBeInserted = 0;
            for(int j = 0; j < 4; j++) {
                int check_pos = check[i][j];
                if(receiver_D[check_pos] == 1)
                    count++;
            }
            if(count % 2 == 0){
                // even number of ones
                toBeInserted = 0;
            } else {
                toBeInserted = 1;
            }
            new_[i] = toBeInserted;
        }
        cout << "Binary equivalent of error position: ";
        for(int i = r-1; i >= 0; i--) {
           cout << new_[i];
        } 
        cout << endl;
        int error_position = 0;
        for(int i = 0; i < r; i++) {
            error_position += pow(2, i) * new_[i];
        }
        if(error_position == 0){
            cout << "No error." << endl;
        } else {
            cout << "Decimal equivalent of error position: ";
            cout << error_position << endl;
        }
        if(receiver_D[error_position] == 1) {
            receiver_D[error_position] = 0;
        }
        else {
            receiver_D[error_position] = 1;
        }
        
        cout << "Final corrected message.\n";
        for(int i = e; i > 0; i--) {
            cout << receiver_D[i] << endl;
        }
    }
    else {
        cerr << "Enter 4 bits only." << endl;
    }
}
