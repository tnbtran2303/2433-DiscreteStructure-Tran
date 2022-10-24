/*****************************************************************************
 *
 *  Author:           Ngoc Tran
 *  Email:            tnbtran2303@gmail.com
 *  Label:            P02
 *  Title:            Max Cycle-Length of Sequences
 *  Course:           CMPS 2433
 *  Semester:         Fall 2022
 *
 *  Description:
 *        This program reads input files then compute and return maximum
 *              cycle length and sum of the numbers in the sequence
 *              for that cycle in an output file
 *
 *
 *  Files:
 *       NgocTran_P2.cpp      : driver program
 *       input1.txt           : Files contain data for testing
 *       input2.txt
 *
 *       output1.txt          : Files contain the output of the program
 *       output2.txt
 *
 *       input3.txt           : input file traded with Jarette Greene
 *       output3.txt
 *****************************************************************************/

#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

// Create a structure variable
struct Result {
  int Sum;
  int Length;
};

// Purpose: get the name and open input/output files
// Receives:
//		ifstream - input filestream to read information from file
// 		ofstream - output filestream to create and write
// Returns: no return type
void openFiles(ifstream &, ofstream &);

// Purpose: used to swap value of two variables
// Receives:
//		2 integers a and b passed by reference
// Returns: no return type
void swapValue(int &, int &);

// Purpose:
//    find maximum cycle length over all numbers between and
//        including both n and m
//    calculate the summation of sequence of numbers in
//              the maximum cycle above
// Receives: int a
// Return : a struct that has two int (sum and length)
Result cycleLength(int);

// Purpose: calculate the summation of sequence of numbers in
//               the maximum cycle above
// Receives: Two integers m & n
// Returns: sum, an int
int findSum(int);

int main() {
  // declare variables
  int m, n, count, total;

  ifstream infile;
  ofstream outfile;

  // open files to read and write in
  openFiles(infile, outfile);

  outfile << "Name: Ngoc Tran\n";
  outfile << "CMPS 2433 - Professor Stringfellow\n";
  outfile << "Program Assignment 2: Max Cycle-Length of Sequences\n\n";

  // print out table headers
  outfile << setw(10) << "m";
  outfile << setw(20) << "n";
  outfile << setw(20) << "max";
  outfile << setw(20) << "sum" << endl;

  // get first pair of data in the input file or
  // prime read before the test
  infile >> m >> n;

  // keep read in numbers until reaching the end of file
  while (!infile.eof()) {
    int max = 0;

    // swap postition of two numbers if m>n
    if (m > n) {
      swapValue(m, n);
    }

    outfile << setw(10) << m;
    outfile << setw(20) << n;

    // check if number in range (1,1000000)
    if (m <= 0 || m >= 1000000 || n >= 1000000) {
      outfile << setw(20) << "invalid input";
      outfile << setw(20) << "invalid input" << endl;
    }

    else {
      // loop through all integers in range [m,n]
      for (int i = m; i <= n; i++) {
        Result R;
        R = cycleLength(i);
        count = R.Length;
        // in case the following integer have same cycle length as
        // previous number
        if (count >= max) {
          max = count;
          total = R.Sum;
        }
      }
      outfile << setw(20) << max;
      outfile << setw(20) << total << endl;
    }
    // read in the next values
    infile >> m >> n;
  }

  // close the opened files
  infile.close();
  outfile.close();
}

// Purpose: get the name and open input/output files
void openFiles(ifstream &infile, ofstream &outfile) {
  char inFileName[40];
  char outFileName[40];
  cout << "Enter the input file name: ";
  cin >> inFileName;
  infile.open(inFileName); // open input file
  cout << "Enter the output file name: ";
  cin >> outFileName;
  outfile.open(outFileName); // open out putfile
}

// Purpose: used to swap value of two variables
void swapValue(int &a, int &b) {
  int temp = a; // copy content of a to temp variable
  a = b;        // copy content of b to a
  b = temp;     // copy back content of temp to b
}

// Purpose:
//    find maximum cycle length over all numbers between and
//        including both n and m
//    calculate the summation of sequence of numbers in
//              the maximum cycle above
Result cycleLength(int number) {
  Result R;
  int count = 1; // initialize cycle length to 1
  int sum = 0;

  // loop until number is equal to 1
  while (number != 1) {
    sum += number;
    if (number % 2 == 1) // number is odd
    {
      number = 3 * number + 1;
    } else {
      number = number / 2;
    }
    count++; // increase the cycle length by 1
  }

  // because the while loop stop when it gets to 1
  sum += number;
  R.Length = count;
  R.Sum = sum;
  return R;
}
