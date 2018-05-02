// insert 0 after 11111 
// author: Kushashwa Ravi Shrimali

#include <iostream>
using namespace std;

// user defined functions

// takes input from user to the array till length given
void  input(int*, int);

// shows output of the array (stream) to the user
void output(int*, int);

// stuff bit 1 to the stream based on 5 1s
int* stuff_bit(int*, int, int);

int main(int argc, char** argv) {
    // input bit stream
    int* stream; int N, count; // count is to count number of 1s
    cout << "Enter length of the stream" << endl;
    cin >> N;
    stream = new int[N];
    
    input(stream,  N);
    output(stream, N);
    
    // stuff bits based on 5 1s
    for(int i = 0; i < N; i++) {
        count = 0;
        while(*(stream + i) == 1) {
            count += 1;
            if(count == 5) {
                stream = stuff_bit(stream, i, N);
                cout << "5 1s occured here. " << i << endl;
                break;
            }
            i += 1;
        }
    }
}

void input(int* stream, int N) {
    cout << "Enter stream: ";
    for(int i = 0; i < N; i++) {
        cin >> *(stream + i);
    }
}

void output(int* stream, int N) {
    cout << "Entered stream: ";
    for(int i = 0; i < N; i++) {
        cout <<  *(stream + i);
    }
    cout << endl;
}

int* stuff_bit(int* stream, int pos, int N) {
    int* new_stream = new int[N + 1];

    for(int i = 0; i <= pos; i++) {
        *(new_stream + i) = *(stream + i);
    }
    
    // stuff 0 bit to the stream after 5 1s position
    *(new_stream + (pos + 1)) = 0;

    for(int j = pos + 1; j < N + 1; j++) {
        *(new_stream + (j + 1)) = *(stream + j);
    }

    output(new_stream, N + 1);
    
    return new_stream;
}
