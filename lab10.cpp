#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class line{
public:
    string seg1;
    char seg1sign = '+';
    string seg1left;
    string seg1right;

    string seg2;
    char seg2sign = '+';
    string seg2left;
    string seg2right;

    void load(string &inputline){
        seg1 = inputline.substr(0, inputline.find(' '));
        seg2 = inputline.substr(inputline.find(' ') + 1);

        int i1 = 0;
        if(seg1[0] == '+' || seg1[0] == '-'){
            i1++;
        }
        if(seg1.find('.') != string::npos){
            seg1left =  seg1.substr(i1, seg1.find('.') - i1);
            seg1right = seg1.substr(seg1.find('.') + 1);
        }else{
            seg1left =  seg1.substr(i1);
            seg1right = "";
        }
        if(seg1[0] == '-'){
            seg1sign = '-';
        }

        int i2 = 0;
        if(seg2[0] == '+' || seg2[0] == '-'){
            i2++;
        }
        if(seg2.find('.') != string::npos){
            seg2left =  seg2.substr(i2, seg2.find('.') - i2);
            seg2right = seg2.substr(seg2.find('.') + 1);
        }else{
            seg2left =  seg2.substr(i2);
            seg2right = "";
        }
        if(seg2[0] == '-'){
            seg2sign = '-';
        }
 
    }

    bool validate(){
        for(int i = 0; i < seg1left.length(); i++){
            if(!isdigit(seg1left[i])) return false;
        }
        for(int i = 0; i < seg1right.length(); i++){
            if(!isdigit(seg1right[i])) return false;
        }
        for(int i = 0; i < seg2left.length(); i++){
            if(!isdigit(seg1left[i])) return false;
        }
        for(int i = 0; i < seg2right.length(); i++){
            if(!isdigit(seg1right[i])) return false;
        }
        return true;
    }
};

int main(){
    string inputfile;
    string inputline;
    cout << "What is your input file name?: ";
    cin >> inputfile;
    ifstream myFile(inputfile);
    while (getline(myFile, inputline)){
        line myline;
        myline.load(inputline);
        string mylineSeg1 = myline.seg1;
        string mylineSeg2 = myline.seg2;
        if(myline.validate()){
            cout << "placeholder";
        }else{
            cout << "Your input line is invalid. This line will be skipped";
        }
    }
}