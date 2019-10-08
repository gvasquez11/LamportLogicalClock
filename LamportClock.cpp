#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class LamportClock
{
private:
  vector <int> events; //Max is 25
  vector<int> logicalCount; //results logical count matrix
  string **inputMatrix; //input matrix
  int **logicalClock; // matrix that has the clock values for each
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
        inputMatrix = new string*[numOfProcess];
        for(int i = 0; i < numOfProcess; i++)
            inputMatrix[i] = new string[numOfEvents];

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
  int** logicalClockAnalyzer(); // Function to get logical clock values for event

};

  //Display function
void LamportClock::display()
  {

    for(int i = 0; i < numOfProcess; i++)
    {
      for (int j = 0; j < numOfEvents; j ++)
          cout << inputMatrix[i][j] << " ";

          cout << endl;
    }

  }

int** LamportClock::logicalClockAnalyzer()
{
  for(int row = 0; row < numOfProcess; row++)
  {
    for(int col = 0; col < numOfEvents; col++)
    {
        if(inputMatrix[row][0].at(0) != 'r' && col == 0)
        logicalClock[row][col] = 1;
        else if(inputMatrix[row][col].at(0) != 'r')
        logicalClock[row][col] = logicalClock[row][col-1] + 1;


    }

  }
  return logicalClock;

}
