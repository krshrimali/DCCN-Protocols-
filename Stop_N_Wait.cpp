#include <iostream>

using namespace std;
typedef struct {
    int data;
} packet;

typedef struct {
    int kind;
    int seq;
    int ack;
    packet info;
    int err;
} frame;

frame DATA;

typedef enum {
    frame_arrival, err, timeout, no_event 
} event_type;

void from_network_layer(packet*);
void to_network_layer(packet*);

void from_physical_layer(frame*);
void to_physical_layer(frame*);

void wait_for_event_sender(event_type*);
void wait_for_event_receiver(event_type*);

void receiver();
void sender();

int i = 1; // data to be sent by sender
char turn; // r or s? 
int DISCONNECT = 0;
int main(int argc, char** argv) {
    while(!DISCONNECT) {
        sender();
        delay(400);
        receiver();
    }
}

void sender() {
    static int frame_to_send = 0;
    static frame s;
    packet buffer;
    event_type event;
    static int flag = 0;

    if(turn == 's') {    
        if(flag == 0) {
            from_network_layer(&buffer);
            inc(frame_to_send);
            s.info = buffer;
            s.seq = frame_to_send;
            printf("SENDER: INFO = %d SEQ NUMBER = %d ", s.info, s.seq);
            turn = 'r'; // comes turn of receiver now
            to_physical_layer(&s);
        }
        if(event == timeout) {
            printf("SENDER: RESENDING FRAME       ");
            turn = 'r';
            to_physical_layer(&s);
        }
    }
}

void receiver() {
    static int frame_expected = 0;
    frame r, s;
    event_type event;

    wait_for_event_receiver(&event);
    if(turn == 'r') {
        if(event == frame_arrival) {
            from_physical_layer(&r);
            if(r.seq == frame_expected) {
                to_network_layer(&r.info);
                inc(frame_expected);
            }
            else {
                printf("RECEIVER: ACK RESENT\n");
                turn = 's';
                to_physical_layer(&s);
            }

            if(event == err) {
                printf("RECEIVER: Garbled Frame\n");
                turn = 's'; // if frame not received, it has to be resent
            }
        }
    }
}

void from_network_layer(packet* buffer) {
    (*buffer).data = i;
    i++;
}

void to_physical_layer(frame *s) {
    s->err = random(4);
    DATA = *s;
}

void to_network_layer(packet* buffer) {
    printf("RECEIVER: Packet %d received, Ack sent \n", (*buffer).data);
    if(i > TOT_PACKETS) {
        DISCONNECT = 1; // DISCONNECT IF all packets received
        printf("\nDisconnected");
    }
}

void from_physical_layer(frame* buffer) {
    *buffer = DATA;
}

void wait_for_event_sender(event_type *e) {
    static int timer = 0;

    if(turn == 's') {
        timer++;
        if(timer == TIMEOUT) {
            *e = timeout;
            printf("Sender: Ack not received => TIMEOUT\n");
            timer = 0;
            return;
        }
        if(DATA.err = 0) {
            *e = err;
        }
        else {
            timer = 0;
            *e = frame_arrival;
        }
    }
}

}
