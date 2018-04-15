// reference: http://computing.dcu.ie/~humphrys/Notes/Networks/data.code.html 

#define MAX_PKT_MTU 1024 // packet size in bytes: MTU

typedef enum{false, true} boolean; // boolean type
typedef unsigned int seq_nr; // sequence number
typedef struct {
   unsigned char data[MAX_PKT_MTU];
}packet; // packet having data of max. size (defined MTU)
typedef enum {data, ack, nak} frame_kind; // frame_kind definition

typedef struct {
    frame_kind kind;
    seq_nr seq;
    seq_nr ack;
    packet info; // network layer packet
}frame;

// wait for event to happen, return its type
void wait_in_event(event_type *event);

// fetch packet from n/w layer for transmission
void from_network(packet *p);

// deliver packet from inbound to n/w layer
void to_network(packet* p);

// go get inbound from physical layer, copy to r
void from_physical(frame *r);

// pass frame to physical layer for transmission
void to_physical(frame *s);

// start clock, and enable timeout event
void start_timer(seq_nr k);

// stop clock, and disable timeout event
void stop_timer(seq_nr k);

// start auxillary timer, enable ack_timeout event
void start_ack_timer(void);

// stop auxillary timer, disable ack_timeout event
void stop_ack_timer(void);

// allow n/w layer to cause network_layer_ready event
void enable_network_layer(void);

// forbid n/w layer from causing network_layer_ready event
void disable_network_layer(void);

// macro incrementor expanded in-line : incremented k circularly
#define inc(k) if (k < MAX_SEQ) k += 1; else k = 0;
