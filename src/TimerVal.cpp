#include <iostream>
#include <chrono>
class TimerVal
{
 public:
  TimerVal() { start = std::chrono::steady_clock::now(); } // postcondition: elapsed()==0
  // reset the timer
  void restart() { start = std::chrono::steady_clock::now(); } // post: elapsed()==0
  double elapsed() const                  // return elapsed time in seconds
    { return  std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count(); }

    ~TimerVal(){}
 private:
    std::chrono::steady_clock::time_point start;
}; // timer