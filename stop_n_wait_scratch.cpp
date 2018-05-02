#include <iostream>

using namespace std;

struct packet {
    int data;
}

void sender();
void receiver();

int main(int argc, char** argv) {
    // with probability of 1/4 
    // make sure that some of them get lost as well from rec to sender
    // and from sender to rec

    // first send the data
    sender();

    receiver();
}

void sender() {

}
