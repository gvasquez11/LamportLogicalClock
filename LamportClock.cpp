#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class LamportClock
{
private:
  vector <int> events; //Max is 25
  vector<int> logicalCount;// = new int[5][25];//results logical count matrix
  string **inputMatrix; //= new int[5][25]; //input matrix
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
        cout << "What is the value of process? N = ";
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
