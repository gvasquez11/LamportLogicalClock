#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Verify
{
private:
  int noProcess;
  int noEvents;
  int fileClock[5][25];
  string verifyResult[5][25];
  int recValues[25];
  int recLocation[25]; // This will keep track where a register was found
                      //Index will indicate process and value will represent event(column)
  char randChar;
  int loopCount;


public:
  Verify(string); //Constructor to read in txt file
  void displayInputClock();
  void verifyAnalyzer();
  void popRec(); //Function to populate the recieve events
  void popSend(); //Function to populate the send events
  void  popInternalEvents();
};

Verify::Verify(string filename)
{
  fstream ifile(filename, ios::in);
  if(!ifile.is_open())
  cout << "ERROR: Could not open file." << endl;
  else
  {
    cout << "How many processes? N = ";
    cin >> noProcess;
    cout << "How man events per process? M = ";
    cin >> noEvents;

    while(!ifile.eof())
    {
      for(int i = 0; i < noProcess; i++)
      {
        for(int j = 0; j < noEvents; j++)
        ifile >> fileClock[i][j];
      }
    }
  }
}

void Verify::displayInputClock()
{
  cout << endl;
  cout << "Table read in from verify.txt file" << endl;
  for(int i = 0; i < noProcess; i++)
  {
    for(int j = 0; j < noEvents; j++)
      cout << fileClock[i][j] << " ";
      cout << endl;
  }

}

void Verify::verifyAnalyzer()
{
  int num = noProcess;
  srand(time(0));
    for(int i = 0; i < noProcess; i++)
    {
      for(int j = 0; j < noEvents; j++)
      {
        if(fileClock[i][j] == 0)
        verifyResult[i][j] = "NULL";
        else if(fileClock[i][j] == 1 && j == 0)
        {
            randChar = 97 + rand() % 16;
            verifyResult[i][j] = randChar;
        }
        else
        {
          if(fileClock[i][j] > 1 && j == 0)
          {
          recLocation[i] = j;
          recValues[num] = fileClock[i][j];
          loopCount++;
          num--;
          }
          else if((fileClock[i][j] - fileClock[i][j-1]) > 1)
          {
          recLocation[i] = j;
          recValues[num] = fileClock[i][j];
          num--;
          loopCount++;
          }
          else
          {
            randChar = 97 + rand() % 16;
            verifyResult[i][j] = randChar;
            loopCount++;
          }
          verifyResult[i][j] = "?";
        }

      }
    }

   popRec();
   popSend();
   popInternalEvents();

    //Print out the verify Matrix
    cout << endl;
    cout << "Verify Matrix" << endl;
    for(int i = 0; i < noProcess; i++)
    {
      for(int j = 0; j < noEvents; j++)
        cout <<  verifyResult[i][j] << " ";
        cout << endl;
    }
}

void Verify::popRec()
{
  int num = noProcess;
  string rTemp;
  for(int i = 0; i < noProcess; i++)
  {
      rTemp = num + '0';
      verifyResult[i][recLocation[i]]  = "r" + rTemp;
      num--;
  }

}

void Verify::popSend()
{
int num = noProcess;
string stemp;
for(int i = 0; i < noProcess; i++)
{
  for(int j = 0; j < noEvents; j++)
  {
    for(int x = 0; x <= num; x++)
    {
      if(fileClock[i][j] + 1 == recValues[x])
      {
        stemp = x + '0';
        verifyResult[i][j] = "s" + stemp;

      }
    }

  }
}

}

void Verify::popInternalEvents()
{
  for(int i = 0; i < noProcess; i++)
  {
    for(int j = 0; j < noEvents; j++)
    {
      if(verifyResult[i][j] == "?")
      {
        randChar = 97 + rand() % 16;
        verifyResult[i][j] = randChar;
      }

    }

  }
}
