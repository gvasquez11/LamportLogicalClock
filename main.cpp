#include <iostream>
using namespace std;

#include "LamportClock.cpp"
#include "verify.cpp"

int main()
{

    cout << "--------------------Algorithm Calculate--------------------" << endl;
    LamportClock clockAnalysis("input.txt");
    clockAnalysis.display();
    clockAnalysis.logicalClockAnalyzer();
    cout << endl;
    cout << "--------------------Algorithm Verify--------------------" << endl;
      Verify v1("verify.txt");
      v1.displayInputClock();
      v1.verifyAnalyzer();
  return 0;
}
