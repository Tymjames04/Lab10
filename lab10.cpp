#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class line
{
public:
    string seg1;
    string seg2;

    void load(string &inputline)
    {
        int start = 0;
        for (int j = 0; j < 2; j++)
        {
            int space = inputline.find(' ', start);
            if (space == string::npos)
            {
                space = inputline.length();
            }
            string temp = inputline.substr(start, space - start);
            if(j == 0){
                seg1 = temp;
            }else{
                seg2 = temp;
            }
            start = space + 1;
        }
        cout << seg1;
        cout << seg2;
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
    }
}