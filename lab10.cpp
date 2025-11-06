#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//class line handles all functions and variables for the lines including the addition/subtraction on them
class line{
public:
    //defines segment1 parts
    string seg1; //whole 1st number
    char seg1sign = '+'; //defaults sign to +
    string seg1left; //left part before the decimal
    string seg1right; //right part after the decimal
    //defines segment2 parts
    string seg2; //whole 2nd number
    char seg2sign = '+'; //defaults sign to + 
    string seg2left; //left part before the decimal
    string seg2right; //right part after the decimal
    //load function that takes a raw input line and parts it out into segment variables
    void load(string &inputline){
        seg1 = inputline.substr(0, inputline.find(' '));
        seg2 = inputline.substr(inputline.find(' ') + 1);
        //parsing and splitting up seg1
        int i1 = 0;
        if(seg1[0] == '+' || seg1[0] == '-'){
            i1++;
        }
        if(seg1.find('.') != string::npos){
            seg1left = seg1.substr(i1, seg1.find('.') - i1);
            seg1right = seg1.substr(seg1.find('.') + 1);
        }else{
            seg1left = seg1.substr(i1);
            seg1right = "";
        }
        if(seg1[0] == '-'){
            seg1sign = '-';
        }
        //parsing and splitting up seg2
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
    //addzeros function lines up both segments with leading and trailing 0s so left and right sides are same number of characters
    void addzeros(){
        //handles adding 0s to left side of numbers 
        while(seg1left.length() != seg2left.length()){
            if(seg1left.length() > seg2left.length()){
                seg2left.insert(0, "0");
            }else{
                seg1left.insert(0, "0");
            }
        }
        //handles adding 0s to the right side of numbers
        while(seg1right.length() != seg2right.length()){
            if(seg1right.length() > seg2right.length()){
                seg2right += "0";
            }else{
                seg1right += "0";
            }
        }
    }
    //stripzeros handles removing excess leading and trailing 0s after addition.
    string stripzeros(string &stripped){
        //handles when there is a decimal
        if(stripped.find('.') != string::npos){
            int pos = stripped.find('.');
            for(int i = 1; i < pos-1; i++){
                if(stripped[i] == '0'){
                    stripped.erase(i, 1);
                    pos--;
                    i--;
                }else{
                    break;
                }
            }
            for(int i = stripped.length()-1; i > pos+1; i--){
                if(stripped[i] == '0'){
                    stripped.erase(i, 1);
                }else{
                    break;
                }
            }
            if(stripped == "+0.0" || stripped == "-0.0") return ("0");
        //handles when there is no decimal
        }else{
            for(int i = 1; i < stripped.length()-1; i++){
                if(stripped[i] == '0'){
                    stripped.erase(i, 1);
                    i--;
                }else{
                    break;
                }
            }
            if(stripped == "+0" || stripped == "-0") return ("0");
        }
        return(stripped);
    }
    //validate returns boolean based on if the inputs seg1 and seg2 are valid doubles
    bool validate(){
        //checks seg1 for validity
        if(seg1left.empty()) return false;
        if(seg1right == "" && seg1.find('.') != string::npos) return false;
        for(int i = 0; i < seg1left.length(); i++){
            if(!isdigit(seg1left[i])) return false;
        }
        for(int i = 0; i < seg1right.length(); i++){
            if(!isdigit(seg1right[i])) return false;
        }
        //checks seg2 for validity
        if(seg2left.empty()) return false;
        if(seg2right == "" && seg2.find('.') != string::npos) return false;
        for(int i = 0; i < seg2left.length(); i++){
            if(!isdigit(seg2left[i])) return false;
        }
        for(int i = 0; i < seg2right.length(); i++){
            if(!isdigit(seg2right[i])) return false;
        }
        return true;
    }
    //add function adds together the two doubles
    string add(){
        addzeros();
        string rightside = "";
        string leftside = "";
        int carry = 0;
        int sum = 0;
        //handles case where signs are the same so addition can be done
        if(seg1sign == seg2sign){
            //adds right sides
            for(int i = seg1right.length()-1; i >= 0; i--){
                sum = (seg1right[i] - '0') + (seg2right[i] - '0') + carry;
                carry = sum / 10;
                rightside.insert(0, to_string(sum % 10));
            }
            //adds left side
            for(int i = seg1left.length()-1; i >= 0; i--){
                sum = (seg1left[i] - '0') + (seg2left[i] - '0') + carry;
                carry = sum / 10;
                leftside.insert(0, to_string(sum % 10));
            }
            //adds carry value if neccessary
            if(carry != 0){
                leftside.insert(0,to_string(carry));
            }
            //inserts the sign
            leftside.insert(0, 1, seg1sign);
            if (!rightside.empty()){
                leftside = leftside + "." + rightside;
            }
            //returns added output with zeros stripped.
            return(stripzeros(leftside));
        //else handles if the signs are not the same by passing off to subtract
        //order passed based off which value is greater as greater-lesser with the sign of the greater will yield correct output.
        }else{
            if(seg1left > seg2left){
                return(subtract(1,2));
            }else if(seg1left < seg2left){
                return(subtract(2,1));
            }else{
                if(seg1right >= seg2right){
                    return(subtract(1,2));
                }else if(seg1right < seg2right){
                    return(subtract(2,1));
            }
        }
        }
        return("error");
    }
    //subtract function is used when signs do not agree. Parameters are used to indicate which value is greater and thus is first in subtraction.
    string subtract(int first, int sec){
        string rightside = "";
        string leftside = "";
        int carry = 0;
        int diff = 0;
        //handles if seg1 is greater.
        if(first == 1){
            for(int i = seg1right.length()-1; i >= 0; i--){
                diff = (seg1right[i] - '0') - (seg2right[i] - '0') - carry;
                if(diff < 0){
                    diff += 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
                rightside.insert(0, to_string(diff));
            }
            for(int i = seg1left.length()-1; i >= 0; i--){
                diff = (seg1left[i] - '0') - (seg2left[i] - '0') - carry;
                if(diff < 0){
                    diff += 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
                leftside.insert(0, to_string(diff));
            }
            leftside.insert(0, 1, seg1sign);
        //handles if seg2 is greater
        }else{
            for(int i = seg2right.length()-1; i >= 0; i--){
                diff = (seg2right[i] - '0') - (seg1right[i] - '0') - carry;
                if(diff < 0){
                    diff += 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
                rightside.insert(0, to_string(diff));
            }
            for(int i = seg2left.length()-1; i >= 0; i--){
                diff = (seg2left[i] - '0') - (seg1left[i] - '0') - carry;
                if(diff < 0){
                    diff += 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
                leftside.insert(0, to_string(diff));
            }
            leftside.insert(0, 1, seg2sign);
        }
        //if the right is not empty, combines both sides
        if (!rightside.empty()){
            leftside = leftside + "." + rightside;
        }
        //returns final value with zeros stripped
        return(stripzeros(leftside));
    }
};
//main handles file input, iterating through lines, and calling class methods.
int main(){
    string inputfile;
    string inputline;
    cout << "What is your input file name?: ";
    cin >> inputfile;
    ifstream myFile(inputfile);
    if(!myFile.is_open()){
        cout << "Invalid file name";
        return(1);
    }
    //parses through every line 1 at a time
    while (getline(myFile, inputline)){
        //creates new myline and loads it
        line myline;
        myline.load(inputline);
        //if line is valid then prints the results of calling add method on myline
        if(myline.validate()){
            cout << myline.add() << "\n";
        //if line is not valid prints out such.
        }else{
            cout << "Your input line is invalid. This line will be skipped\n";
        }
    }
}