//includes all libraries needed and defines namespace
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
//creates Matrix class which holds a 2d vector of strings called mtx and a print method
class Matrix{
public:
    std::vector<vector<string>> mtx;
    //print method handles all printing for a matrix
    void print(){
        for (int i = 0; i < mtx.size(); ++i) {
            for (int j = 0; j < mtx[i].size(); ++j) {
                cout << mtx[i][j] << " ";
            }
        cout << endl;
        } 
    }
};
//load function takes in a file name and two matricies and loads the two matricies with the values held within the input file
void load(string &inputfile, Matrix &mtx1, Matrix &mtx2){
    int size = 0;
    ifstream myFile(inputfile);
    string line;
    int linecounter = 0;
    //iterates over all lines within the input file
    while(getline (myFile, line)) {
        //if on the first line simply extract the size value that is on that line and store it in size
        if(size == 0){
            size = std::stoi(line);
        }
        //for all other lines.
        else{
            int start = 0;
            //create an empty string vector named row
            vector<string> row; 
            //iterates over all N values of the NxN matrix using size
            for (int j = 0; j < size; j++) {
                //finds next index of space after the start index
                int space = line.find(' ', start);
                //if there is no space sets space to the length of the line which indicates the end of the row 
                if (space == string::npos){
                    space = line.length();
                }
                //sets temp to the substring from the starting index to the next space we found
                string temp = line.substr(start, space - start);
                //pushes the value we just extracted from the inputfile into the row.
                row.push_back(temp);
                //increments start by where we just found a space + 1 so that it goes onto find the next value in the input files line. 
                start = space + 1;
            }
            //uses counter linecounter to determine if we just finished a line in the 1st or 2nd matrix given
            //if less than the size, we are in the 1st matrix, so the row is added to that matrix
            if (linecounter < size){
                mtx1.mtx.push_back(row);
            }
            //if we are greater than the size, add the row to the second matrix
            else{
                mtx2.mtx.push_back(row);
            }
            //increment linecounter by 1 to keep track of total number of rows we have processed
            linecounter++;
        }
    }
}
//mtxAdd takes in two matricies and prints out the result of adding those two together
void mtxAdd(Matrix &mtx1, Matrix &mtx2){
    Matrix tempmtx;
    //loops over all values in the NxN matricies and adds their values. pushes these new values into a row which is then added into the tempmtx
    for (int i = 0; i < mtx1.mtx.size(); i++) {
        vector<string> row;
        for (int j = 0; j < mtx1.mtx[i].size(); j++) {
            int mtx1int = stoi(mtx1.mtx[i][j]);
            int mtx2int = stoi(mtx2.mtx[i][j]);
            row.push_back(to_string(mtx1int + mtx2int));
        }
        tempmtx.mtx.push_back(row);
    }
    //prints out the tempmtx which is the result of matrix addition of mtx1 and mtx2
    cout << "Matrix 1 and Matrix 2 added together:\n";
    tempmtx.print(); 
}
//mtxMultiply takes in two matricies and uses matrix multipliation algorithm to multiply them together
void mtxMultiply(Matrix &mtx1, Matrix &mtx2){
    Matrix outputMtx;
    //i loop handles row index for mtx1.
    for (int i = 0; i < mtx1.mtx.size(); i++){
        //creates new empty "row" for each new loop of i.
        vector<string> row;
        //j loop handles column index for mtx2
        for (int j = 0; j < mtx1.mtx.size(); j++){
            //sets sum to 0 for each loop of j which handles the columns
            int sum = 0;
            //k represents the column for mtx1 and the row for mtx2 in matrix multiplication.
            for (int k = 0; k < mtx1.mtx.size(); k++){
                //sums the integers at according indecies following matrix multiplication.
                int mtx1int = stoi(mtx1.mtx[i][k]);
                int mtx2int = stoi(mtx2.mtx[k][j]);
                sum+= mtx1int*mtx2int;
            }
            //adds the result of multiplication to the row
            row.push_back(to_string(sum));
        }
        //adds the row to the outputMtx
        outputMtx.mtx.push_back(row);
    }
    //prints out outputMtx which holds the result of matrix multiplication.
    cout << "Matrix 1 and Matrix 2 multiplied together:\n";
    outputMtx.print();
}
//mtxDiagonalSum takes in a matrix and returns the sum of the primary and secondary diagonals
void mtxDiagonalSum(Matrix &mtxz){
    //sum variables
    int maindiag = 0;
    int seconddiag = 0;
    //loops over the diagonals
    for (int i = 0; i < mtxz.mtx.size(); i++) {
        //gets main diagonal integer
        int mtxzint1 = stoi(mtxz.mtx[i][i]);
        //gets secondary diagonal integer
        int mtxzint2 = stoi(mtxz.mtx[i][mtxz.mtx.size()-1-i]);
        //adds integer to running total for main diagonal
        maindiag+=mtxzint1;
        //adds integer to running total for secondary diagonal
        seconddiag+=mtxzint2;
    }
    //prints out the diagonal values
    cout << "Sum of main diagonal: " << maindiag << endl;
    cout << "Sum of secondary diagonal: " << seconddiag << endl;
}
//mtxRowSwap takes in a matrix and two rows that will then be swapped
void mtxRowSwap(Matrix &mtxz, int row1, int row2){
    //creates copy of mtxz we passed in as parameter
    Matrix outputMtx = mtxz;
    //creates row called temp which stores row1
    vector<string> temp = outputMtx.mtx[row1];
    //sets row1 to row2
    outputMtx.mtx[row1] = outputMtx.mtx[row2];
    //sets row2 to the temp, which is row1
    outputMtx.mtx[row2] = temp;
    //prints out outputMtx which is now the matrix that was inputted with its specified rows swapped
    cout << "Matrix with rows " << row1 << " and " << row2 << " swapped:\n";
    outputMtx.print();
}
//mtxColSwap takes in a mtxz, col2, and col2 as parameters and swaps the two columns
void mtxColSwap(Matrix &mtxz, int col1, int col2){
    //creates outputMtx
    Matrix outputMtx;
    for (int i = 0; i < mtxz.mtx.size(); i++) {
        vector<string> row;
        for (int j = 0; j < mtxz.mtx[i].size(); j++) {
            //if our current column index, j, is out specified column1
            if(j == col1){
                //push back into row the value that is in this row, but at col2 index
                row.push_back(mtxz.mtx[i][col2]);
            //if out current column index, j, is out specified column2
            }else if(j == col2){
                //push back into row the value that is in this row, but at col1 index
                row.push_back(mtxz.mtx[i][col1]);
            //if this column is not one of the ones to be swapped, simply add its value to row
            }else{
                row.push_back(mtxz.mtx[i][j]);
            }
        }
        //add the row that was just constructed to outputMtx
        outputMtx.mtx.push_back(row);
    }
    //print out outputMtx which is the mtxz we passes in with its two columns swapped.
    cout << "Matrix with columns " << col1 << " and " << col2 << " swapped:\n";
    outputMtx.print();    
}
//mtxUpdateVal takes in a mtxz, a row, a col, and a val and then sets that index of mtxz to the new val.
void mtxUpdateVals(Matrix &mtxz, int row, int col, int val){
    Matrix outputMtx;
    for (int i = 0; i < mtxz.mtx.size(); i++) {
        vector<string> newrow;
        for (int j = 0; j < mtxz.mtx[i].size(); j++) {
            //if the current index is the desired row and column, push back the new value to outputMtx
            if(i == row && j == col){
                newrow.push_back(to_string(val));
            //if it is any other index, simply pass forward the value from mtxz into the outputMtx
            }else{
                newrow.push_back(mtxz.mtx[i][j]);
            }
        }
        outputMtx.mtx.push_back(newrow);
    }
    //print out the outputMtx
    cout << "Matrix with row value at " << row << " and " << col << " swapped for " << val << " :\n";
    outputMtx.print(); 
}
//helper function boundchecker checks if two bounds are valid for a given mtxz and returns a boolean
bool boundchecker(Matrix &mtxz, int b1, int b2){
    return((b1>=0 && b1<mtxz.mtx.size()) && (b2>=0 && b2<mtxz.mtx.size()));
}
//main function
int main(){
    Matrix mtx1;
    Matrix mtx2;
    string inputfile;
    //task1: takes in file name and calls load function which loads in the matricies. Then prints them both out.
    cout << "What is your input file name?: ";
    cin >> inputfile;
    load(inputfile, mtx1, mtx2);
    cout << "\n-----Task1-----\n";
    cout << "Vector 1\n";
    mtx1.print();
    cout << "Vector 2\n";
    mtx2.print();

    //task2: uses mtxAdd to print out the sum of the two matricies
    cout << "\n-----Task2-----\n";
    mtxAdd(mtx1,mtx2);

    //task3: asks user which matrix they want to be first in the multiplication and then multiplices the matricies together using mtxMutiply
    cout << "\n-----Task3-----\n";
    string task3mtx;
    cout << "What would you like the first factor matrix to be? \"matrix1\" or \"matrix2\": ";
    cin >> task3mtx;
    if (task3mtx == "matrix1"){
        mtxMultiply(mtx1,mtx2);
    }else if (task3mtx == "matrix2"){
        mtxMultiply(mtx2,mtx1);
    //handles error when input for desired matrix is invalid
    }else{
        cout << "you have inputted something invalid when selecting task3 matrix";
        return(1);
    }

    //task4: asks the user which matrix to take the diagonal of and then uses mtxDiagonalSum to print out those diagonals. 
    cout << "\n-----Task4-----\n";
    string task4mtx;
    cout << "Would you like to find the diagonal of \"matrix1\" or \"matrix2\"?: ";
    cin >> task4mtx;
    if (task4mtx == "matrix1"){
        mtxDiagonalSum(mtx1);
    }else if (task4mtx == "matrix2"){
        mtxDiagonalSum(mtx2);
    //handles error when input for desired matrix is invalid
    }else{
        cout << "You have entered an invalid matrix option for task4";
        return(1);
    }

    //task5: asks user for which matrix, and two row values to then swap the rows using boundchecker to check the inputted values and mtxRowSwap to swap them.
    cout << "\n-----Task5-----\n";
    string task5mtx;
    int task5row1;
    int task5row2;
    cout << "Which matrix do you want to swap a row in? \"matrix1\" or \"matrix2\": ";
    cin >> task5mtx;
    cout << "What is the 1st row you want to swap?: ";
    cin >> task5row1;
    cout << "What is the 2nd row you want to swap?: ";
    cin >> task5row2;
    if (task5mtx == "matrix1"){
        if (boundchecker(mtx1,task5row1,task5row2)) mtxRowSwap(mtx1,task5row1,task5row2);
        //handles if invalid index was entered
        else cout << "You have entered an invalid index";
    }else if (task5mtx == "matrix2"){
        if (boundchecker(mtx2,task5row1,task5row2)) mtxRowSwap(mtx2,task5row1,task5row2);
        //handles if invalid index was entered
        else cout << "You have entered an invalid index";
    //handles error when input for desired matrix is invalid
    }else{
        cout << "You have entered something invalid for task 5";
        return(1);
    } 

    //task6: asks user for which matrix, and two column values to then swap the columns using boundchecker to check the inputted values and mtxColSwap to swap them.
    cout << "\n-----Task6-----\n";
    string task6mtx;
    int task6col1;
    int task6col2;
    cout << "Which matrix do you want to swap a column in? \"matrix1\" or \"matrix2\": ";
    cin >> task6mtx;
    cout << "What is the 1st column you want to swap?: ";
    cin >> task6col1;
    cout << "What is the 2nd column you want to swap?: ";
    cin >> task6col2;
    if (task6mtx == "matrix1"){
        if (boundchecker(mtx1,task6col1,task6col2)) mtxColSwap(mtx1,task6col1,task6col2);
        //handles if invalid index was entered
        else cout << "You have entered an invalid index";
    }else if (task6mtx == "matrix2"){
        if (boundchecker(mtx2,task6col1,task6col2)) mtxColSwap(mtx2,task6col1,task6col2);
        //handles if invalid index was entered
        else cout << "You have entered an invalid index";
    //handles error when input for desired matrix is invalid
    }else{
        cout << "You have entered something invalid for task 6";
        return(1);
    }
    
    //task7: asks user for which matrix, a row, a column, and a value and then uses boundchecker to check the inputted values and mtxUpdateVals to get the updated matrix.
    cout << "\n-----Task7-----\n";
    string task7mtx;
    int task7row;
    int task7col;
    int task7val;
    cout << "Which matrix do you want to swap a value in? \"matrix1\" or \"matrix2\": ";
    cin >> task7mtx;
    cout << "What is the row you want to swap?: ";
    cin >> task7row;
    cout << "What is the column you want to swap?: ";
    cin >> task7col;
    cout << "What is the value to swap in?: ";
    cin >> task7val;
    if (task7mtx == "matrix1"){
        if (boundchecker(mtx1,task7row,task7col)) mtxUpdateVals(mtx1,task7row,task7col,task7val);
        //handles if invalid index was entered
        else cout << "You have entered an invalid index";
    }else if (task7mtx == "matrix2"){
        if (boundchecker(mtx2,task7row,task7col)) mtxUpdateVals(mtx2,task7row,task7col,task7val);
        //handles if invalid index was entered
        else cout << "You have entered an invalid index";
    //handles error when input for desired matrix is invalid
    }else{
        cout << "You have entered something invalid for task 7";
        return(1);
    }

}