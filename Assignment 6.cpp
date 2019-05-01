#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;

const int N = 1e5 , soupN = 2 , saladN = 4;

double soupStations [soupN ];
double saladStations[saladN];

double getMin(double currentT , double spendT , double* arr , int siz)
{
    double minT = arr[0];
    int minidx = 0;

    for (int i = 1 ; i<siz ; ++i) // gets the minimum time and update it
    {
        if (arr[i] < minT)
        {
            minT = arr[i];
            minidx = i;
        }
    }
    arr[minidx]+=spendT;
    return (minT-currentT>0 ? (minT-currentT + spendT) : spendT );
}
double saladTime (double currentT , double spendT) // returns the time spend in the salad
{
    return getMin(currentT,spendT,saladStations,saladN);
}

double soupTime (double currentT , double spendT) // returns the time spend in the soup
{
    return getMin(currentT,spendT,soupStations,soupN);
}

int main()
{
    std::mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    std::normal_distribution<double> IAT(60, 12); // inter arrival time of customers (converted to seconds)
    std::normal_distribution<double> cashierPay(40, 10); // Time to collect money from customers (converted to seconds)
    std::normal_distribution<double> getSoup(120, 20); // Time to serve customer and give him soup (converted to seconds)
    std::normal_distribution<double> getSalad(60, 15); // Time to serve customer and give him soup (converted to seconds)
    std::discrete_distribution<int> soupProb{0.4,0.6}; // 40% -> no soup , 60% -> soup

    bool soupP; // bool because soupProb returns 0 or 1 only
    double cashierT , soupT , saladT; // variables to store data every loop in them
    double TotalTimeSalad = 0; // total time by customers who got salad only
    double TotalTimeSoup  = 0; // total time by customers who got salad and soup
    double LastArrivalT = 0; // last customer arrived when
    double currentArrival; // current customer arrived when
    for (int i = 0 ; i<N ; ++i ) // loops N times
    {
        soupP = soupProb(rng); // will the customer take soup?

        currentArrival = LastArrivalT + IAT(rng);
        LastArrivalT = currentArrival;

        cashierT = cashierPay(rng);
        saladT = saladTime(currentArrival+cashierT,getSoup(rng));

        if (soupP)
        {
            soupT = soupTime(currentArrival+cashierT+saladT,getSoup(rng));
            TotalTimeSoup += (cashierT+saladT+soupT);
        }
        else TotalTimeSalad += (cashierT + saladT);

    }
    cout << "Average time spent without soup : " << fixed << setprecision(3) << TotalTimeSalad/N << " seconds = " << TotalTimeSalad/(N*60) << " minutes\n\n" ;
    cout << "Average time spent with soup : "    << fixed << setprecision(3) << TotalTimeSoup/N  << " seconds = " << TotalTimeSoup/(N*60)  << " minutes\n\n";
    //int n123 ;cin >> n123; // to stop the console and prevent it from halting
    return 0;
}
