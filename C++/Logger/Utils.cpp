#include "Utils.h"

using namespace std;

/*
TimeNow
Return The Current Full Date at the EXEC Time
*/
string TimeNow()
{
    auto dateTime = chrono::system_clock::now();
    time_t date = chrono::system_clock::to_time_t(dateTime);
    string timestamp = ctime(&date);
    return timestamp.substr(0, timestamp.length() - 1);
}

/*
GetRInteger
Get A Random Integer from minimum to maximum  all includes


@return integer
*/
int GetRInteger(int minimum, int maximum)
{
    int n = rand()%(maximum-minimum+1)+minimum;
    return n;
}

/*
GetRDouble
Get A Random Integer from minimum to less than maximum 


@return double
*/
double GetRDouble(double minimum, double maximum)
{
    double n = (double)rand()/RAND_MAX;
    return minimum + n * (maximum-minimum);
}
