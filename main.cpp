#include <iostream>
using namespace std;

#include "LamportClock.cpp"

int main()
{

    LamportClock clockAnalysis("input.txt");
    clockAnalysis.display();
    clockAnalysis.logicalClockAnalyzer();

  return 0;
}
