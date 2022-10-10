/*****************************************************************************
*                    
*  Author:           Ngoc Tran
*  Email:            tnbtran2303@gmail.com
*  Label:            P01
*  Title:            Bitwise Operator
*  Course:           CMPS 2433
*  Semester:         Fall 2022
* 
*  Description:
*        This program reads input files then compute and return resulting value of different 
*         bitwise operators in an output file
*        
*       
*  Files:            
*       NgocTran_P1.cpp      : driver program 
*       input1.txt    : Files contain data for testing
*       input2.txt
*       output1.txt   : Files contain the output of the program
*       output2.txt 
*****************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

void openFiles (ifstream&, ofstream&);
void bitTable1(unsigned short arr[][6], int);
void populateTable1(unsigned short arr[][6],int, ifstream&);
void printTable1(unsigned short arr[][6], int, ofstream&);
void bitTable2(unsigned short arr[][10], ifstream&, int);
void printTable2(unsigned short arr[][10], int, ofstream&);



int main()
{  
  int n,m;
  ofstream outfile;
  ifstream infile;
  openFiles(infile,outfile);

  //PART A
  infile >> n;
  int numsOfRows1 = n+4;
  unsigned short arr[numsOfRows1][6];
  populateTable1(arr,numsOfRows1,infile);
  bitTable1(arr,numsOfRows1);
  printTable1(arr,numsOfRows1,outfile);

    //PART B
  infile >> n;
  int numsOfRows2 = n;
  unsigned short arr2[numsOfRows2][10];
  bitTable2(arr2, infile, numsOfRows2);
  printTable2(arr2,numsOfRows2,outfile);
  
}

//Purpose: opening input/output files
//Receives:
//		ifstream - input filestream to read information from file
// 		ofstream - output filestream to create and write 
//Returns: no return type
void openFiles (ifstream& infile, ofstream& outfile)
{
  char inFileName[40];
  char outFileName[40];
  cout<<"Enter the input file name: ";
  cin>>inFileName;
  infile.open(inFileName); //open input file
  cout<<"Enter the output file name: ";
  cin>> outFileName;
  outfile.open(outFileName);//open out putfile
}

//Purpose: compute and return resulting values of following 
//		bitwise operator : &,|,^,~		
//Receives: an array of n rows and 6 columns and number of rows
//Returns: no return type

void bitTable1(unsigned short arr[][6], int rows)
{
	//loop through table to compute
  for (int r = 0; r < 4; r++)  
  {
    for (int c = 2; c<6; c++){
      switch(c){
        case 2:
          arr[r][c] = (arr[r][0] & arr[r][1]);
          break;
        case 3:
          arr[r][c] = (arr[r][0] | arr[r][1]);
          break;
        case 4:
          arr[r][c] = (arr[r][0] ^ arr[r][1]);
          break;
        case 5:
        	//hard code truth table
          if(r==0 || r==1)
          		arr[r][c] = 1;
          else
		  		arr[r][c] = 0;
          break;
      }
    }
  }
  for (int r = 4; r < rows; r++)  
  {
    for (int c = 2; c<6; c++){
      switch(c){
        case 2:
          arr[r][c] = (arr[r][0] & arr[r][1]);
          break;
        case 3:
          arr[r][c] = (arr[r][0] | arr[r][1]);
          break;
        case 4:
          arr[r][c] = (arr[r][0] ^ arr[r][1]);
          break;
        case 5:
          arr[r][c] = ~(arr[r][0]);
          break;
      }
    }
  }
}

//Purpose: read in values for the first and second column (X&Y) 	
//Receives: an array of n rows and 6 columns, number of rows and 
//		input filesream to read in information
//Returns: no return type
void populateTable1(unsigned short arr[][6],int rows, ifstream& infile)
{
  //hard code truth table for first 4 rows
  arr[0][0] = 0;
  arr[1][0] = 0;
  arr[2][0] = 1;
  arr[3][0] = 1;
  
  arr[0][1] = 0;
  arr[1][1] = 1;  
  arr[2][1] = 0;
  arr[3][1] = 1;
  
  //read from file to get x and y
  for (int r = 4; r < rows; r++){
    for (int c = 0; c < 2; c++){
      infile >> arr[r][c] ;
    }
  }
}

//Purpose: print out the result to output file 	
//Receives: an array of n rows and 6 columns, number of rows and 
//		output filesream to write
//Returns: no return type
void printTable1(unsigned short arr[][6], int rows, ofstream& outfile)
{
  outfile << left;
  outfile  << setw(10) << "X";
  outfile << setw(10) << "Y";
  outfile << setw(10) << "&";
  outfile << setw(10) << "|";
  outfile << setw(10) << "^";
  outfile << setw(10) << "~";
  outfile << endl;
  for (int i=0; i<rows; i++){
    for (int j=0; j<6;j++){
      outfile << setw(10) << arr[i][j] ;
    }
    outfile << endl;
  }
}

//Purpose: compute and return resulting values of following 
//		bitwise operator : setbit(S), getBit(G), shiftLeft(<),
//		shiftRight(>), isEven(E), countOnes(C), isPower2(2)	
//Receives: an array of n rows and 10 columns and number of rows
//Returns: no return type
void bitTable2(unsigned short arr[][10], ifstream& infile, int rows)
{
    char op;
    //initialize table to one complement
    for (int r = 0; r < rows; r++){
        for (int c = 0; c < 10; c++){
          arr[r][c] = 65535;
        }
    }
    
    unsigned short temp;
    int count = 0;
    
  for (int r = 0; r < rows; r++)
  {
    infile >> op;
    infile >> arr[r][0];
    
    switch(op)
    {
        case '>':
            arr[r][3] = arr[r][0] >> 1;
        break;
        case '<':
            arr[r][4] = arr[r][0] << 1;
        break;
        case 'S':
            infile >> arr[r][1] >> arr[r][2];
            
            temp = 1 << arr[r][1];
            
            if(arr[r][2] == 1)
                arr[r][5] =  arr[r][0] | temp;
            if(arr[r][2] == 0)
                arr[r][5] =  arr[r][0] & ~temp;
        break;
        case 'G':
            infile >> arr[r][1];
            
            temp = 1 << arr[r][1];
            
            arr[r][6] = arr[r][0] & temp;
        break;
        case 'E':
            arr[r][7] = !(arr[r][0] & 1);
        break;
        case 'C':
            count = 0;
            
            for(int i = 0; i < 8; i++)
            {
                temp = 1 << i;
            
                if(arr[r][0] & temp)
                    count++;    
            }
        
            arr[r][8] = count;
        break;
        case '2':
            if(arr[r][0] != 0)
                arr[r][9] = ((arr[r][0] & (arr[r][0] - 1)) == 0);
            else
                arr[r][9] = 0;
        break;
    }
    
  }
}

//Purpose: print out the result to output file 	
//Receives: an array of n rows and 10 columns, number of rows and 
//		output filesream to write
//Returns: no return type
void printTable2(unsigned short arr[][10], int rows, ofstream& outfile)
{
  outfile << endl;
  outfile << left;
  outfile  << setw(7) << "X";
  outfile << setw(7) << "P";
  outfile << setw(7) << "V";
  outfile << setw(7) << ">>";
  outfile << setw(7) << "<<";
  outfile << setw(7) << "S";
  outfile << setw(7) << "G";
  outfile << setw(7) << "E";
  outfile << setw(7) << "C";
  outfile << setw(7) << "2";
  outfile << endl;
  
  for (int i=0; i<rows; i++){
    for (int j=0; j<10;j++){
        if(arr[i][j] == 65535)
            outfile << setw(7) << " " ;
        else
            outfile << setw(7) << arr[i][j] ;
    }
    outfile << endl;
  }
}

