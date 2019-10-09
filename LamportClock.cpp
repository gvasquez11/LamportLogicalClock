#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class LamportClock
{
private:
  //vector <int> events; //Max is 25
  //vector<int> logicalCount; //results logical count matrix
  string inputMatrix[5][25]; //input matrix
  int logicalClock[5][25]; // matrix that has the clock values for each
  int numOfProcess; //This is the N value(rows)
  int numOfEvents; // M value shows the max number(columns)

public:
  //Constructor to read in the file
  LamportClock(string filename)
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
      //  inputMatrix = new string*[numOfProcess];
        for(int i = 0; i < numOfProcess; i++)
            //inputMatrix[i] = new string[numOfEvents];

            while(!ifile.eof())
            {
              for(int i = 0; i < numOfProcess; i++)
              {
                  for (int j = 0; j < numOfEvents; j ++)
                  ifile >> inputMatrix[i][j];
              }

            }
      }
  }

  void display();
  void logicalClockAnalyzer(); // Function to get logical clock values for event

};

  //Display function to show the table that was inputed to text file
void LamportClock::display()
  {
    cout << endl;
    cout << "Table inputed to intput.txt"<< endl;
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
        logicalClock[row][col] = logicalClock[row][col-1] + 1;
        else
        logicalClock[row][col] = -1;

    }
  }

  //Loop to print out the logical clock matrix
  for(int i = 0; i < numOfProcess; i++)
  {
      for(int j = 0; j < numOfEvents; j++)
      cout << logicalClock[i][j] << " ";
      cout << endl;
  }

}
