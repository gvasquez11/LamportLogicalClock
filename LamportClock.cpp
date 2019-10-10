#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class LamportClock
{
private:
  int sendEvents[10]; //max number of send events that are possible is 1-9
  int eventFlag[25]; //array to keep track of where there was a flag
  string inputMatrix[5][25]; //input matrix
  int logicalClock[5][25]; // matrix that has the clock values for each
  int numOfProcess; //This is the N value(rows)
  int numOfEvents; // M value shows the max number(columns)
  int sendNum;
  int recValue; //The number order of the recieve message i.e. r1 r2 r3
  int sendCounter;

public:
  LamportClock(string); //Constructor to read in the file
  void display();
  void logicalClockAnalyzer(); // Function to get logical clock values for event
  int clockLoop(int);

};

LamportClock::LamportClock(string filename)
{
  fstream ifile(filename, ios::in);
  if(!ifile.is_open())
    cout << "ERROR: Could not open file." << endl;
  else
  {
    cout << "What is the value of processes? N = ";
    cin >> numOfProcess;
    cout << "What is the number of events per process? M = ";
    cin >> numOfEvents;

        while(!ifile.eof())
        {
          for(int i = 0; i < numOfProcess; i++)
          {
              for (int j = 0; j < numOfEvents; j ++)
              ifile >> inputMatrix[i][j];
          }

        }
  }
  //Initalize logical clock all to -1
  for(int i = 0; i < numOfProcess; i++)
  {
    for(int j = 0; j < numOfEvents; j++)
      logicalClock[i][j] = -1;
  }

}

  //Display function to show the table that was inputed to text file
void LamportClock::display()
  {
    cout << endl;
    cout << "Table read in from intput.txt"<< endl;
    for(int i = 0; i < numOfProcess; i++)
    {
      for (int j = 0; j < numOfEvents; j ++)
          cout << inputMatrix[i][j] << " ";

          cout << endl;
    }

  }

void LamportClock::logicalClockAnalyzer()
{

  cout << endl;
  cout << "Logical Clock Matrix" << endl;
  for(int row = 0; row < numOfProcess; row++)
  {
    for(int col = 0; col < numOfEvents; col++)
    {

        if(inputMatrix[row][col] == "NULL")
        logicalClock[row][col] = 0;
        else if(inputMatrix[row][col].at(0) != 'r' && col == 0)
        logicalClock[row][col] = 1;
        else if(inputMatrix[row][col].at(0) != 'r')
        {
          if(inputMatrix[row][col].at(0) == 's' && inputMatrix[row][col-1].at(0) != 'r')
          {
            sendNum = inputMatrix[row][col].at(1) - '0';
            logicalClock[row][col] = logicalClock[row][col-1] + 1;
            sendEvents[sendNum-1] = logicalClock[row][col];
          }
          logicalClock[row][col] = logicalClock[row][col-1] + 1;
        }
        else if(inputMatrix[row][col].at(0) == 'r')
        {

          int tempRec = inputMatrix[row][col].at(1) - '0';
          int tempClockVal = clockLoop(tempRec);
              if(sendEvents[tempRec] != -1) //if it doesn't equal -1 that means theres a value in the send array
                logicalClock[row][col] = sendEvents[tempRec-1]+1;
        }
        else
        logicalClock[row][col] = -1;
    }

  }
  //recValue = inputMatrix[0][2].at(1) - '0';
  //cout << "Testing recValue " << recValue << endl;

  //Testing send event array
  for (int i = 0; i < 10; i++)
    cout << "Send event " << i + 1 << " is: " << sendEvents[i] << endl;

  //Loop to print out the logical clock matrix
  for(int i = 0; i < numOfProcess; i++)
  {
      for(int j = 0; j < numOfEvents; j++)
      cout << logicalClock[i][j] << " ";
      cout << endl;
  }

}

int LamportClock::clockLoop(int r)
{
  return -7;
}
