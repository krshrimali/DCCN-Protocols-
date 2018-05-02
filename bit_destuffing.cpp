#include <iostream>
#include <cstdio>
//#include <string.h>

using namespace std;
int strlen(char*);
bool str_compare(string, string, int, int);
void rightshift(string, int);

int main(int argc, char** argv) {
    // example Bit Data - 011101111110 
    // SFD - 01111110
    // EFD - 01111110 
    // char data[20] = "011101111110";
    string data = "0111011111101111110";
    string SFD = "01111110";
    char* EFD = "01111110";
    
    int count = 0;
    // cout << "Data: " << strlen(data) << endl;
    // cout << strlen(SFD) << endl;

    //int dataL = strlen(data);
    //int SFDL = strlen(SFD);

    int dataL = data.length();
    int SFDL = SFD.length();
    
    char* new_string[20];
    int toChange[10];
    cout << dataL << SFDL << endl;
    for(int i = 0; i <= dataL - SFDL; i++) {
        //cout << data[i:i+SFDL] << endl;
        // new_string[i] = data[i];
        if(str_compare(data, SFD, i, SFDL)) {
            toChange[count] = SFDL + i - 1; // add one after 6th one, this is 0
            count += 1;
        }
    }
    
    for(int i = 0; i < count; i++){
        rightshift(data, toChange[i]);
    }
    cout << data << endl;
    cout << count << endl;
}

/*bool search_string(subs, s) {
    int count = 0; 

}*/

int strlen(char* string_name) {
    int count = 0; int i = 0;
    while(true) {
        if(*(string_name + i) != '1' && *(string_name + i) != '0'){
            break;
        }
        i+=1; count += 1;
    }
    return count;
}

bool str_compare(char* original, char* new_, int start, int add) {
    // cout << start + add << endl;
    for(int i = start; i < start + add; i++) {
        // cout << *(original + i) << " " << *(new_ + i) << endl;
        if(*(original + i) != *(new_ + i-start))
            return false;
    }
    return true;
}

/*char* find_position(char* stringname, char* new_, int start, int add, char* destination) {
    for(int i = start; i < start + add; i++) {
        if(*(stringname + i) != *(new_ + i - start))
            return false;
    }
    return 
    
}*/

void rightshift(string data, int toChange) {
    int length_data = data.length();
    cout << toChange << endl;
    cout << data << endl;
    cout << "Initially: " <<  length_data << endl;
    for(int i = length_data; i >= toChange; i--){
        *(data + i + 1) = *(data + i);
        cout << i << endl;
    }
    cout << "Value now is: " << i << endl;
    *(data + 10) = 0;
    for(int i = 0; i < length_data + 1; i++) {
        cout << *(data + i) << endl;
        //cout << *(data + i) << endl;
        //cout << i << endl;
    }
    //cout << length_data << endl;
    //cout << strlen(data) << endl;
    //cout << "Final Value: " << endl;
    cout << data << endl;
}
