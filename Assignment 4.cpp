#include <bits/stdc++.h>
#include<chrono>
#include "Histogram.h"

using namespace std;

template<typename T>
class triangular_distribution {
public:
	T a, b, c;
	triangular_distribution(T _a, T _b, T _c) : a(_a), b(_b), c(_c) {}

	template<class URNG>
	T operator()(URNG& g) {
		double range = (g.max() - g.min());
		double x = (g() - g.min());
		double crit = (c - a) * range / (b - a);

		T y;
		
		if (x < crit)
			y = a + sqrt((b - a)*(c - a)*(x) / range) ;
		else
			y = b - sqrt((b - a)*(b - c)*(range - x) / range);
		
		return y;
	}
};

const int N = 1e6;
int main() {
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	
	exponential_distribution <double> exponential(1);
	uniform_real_distribution <double> uniform(2, 4);
	normal_distribution <double> normal(3, 0.5);
	triangular_distribution <double> triangular(2, 4, 3.3);
	
	double totalWaiting = 0;
	double maxWait = 0;
	int nWait = 0;
	int nWaitMinute = 0;


	double arriveTime = 0;
	double m1Avail = 0, m2Avail = 0, m3Avail = 0;
	double m1Free = 0, m2Free = 0, m3Free = 0;
	for (int i = 0; i < N; i++) {
		double interTime = exponential(rng);
		arriveTime += interTime;

		if (arriveTime > m1Avail) {
			m1Free += arriveTime - m1Avail;
			m1Avail = arriveTime;
		}
		if (arriveTime > m2Avail) {
			m2Free += arriveTime - m2Avail;
			m2Avail = arriveTime;

		}
		if (arriveTime > m3Avail){
			m3Free += arriveTime - m3Avail;
			m3Avail = arriveTime;
		}

		double firstAvail = min(m1Avail, min(m2Avail, m3Avail));
		double waitingTime = 0;
		double startTime = arriveTime;
		if (firstAvail > arriveTime) {
			waitingTime = firstAvail - arriveTime;
			startTime = firstAvail;
		}
		if (startTime >= m1Avail) {
			m1Avail = startTime + uniform(rng);
		}
		else if (startTime >= m2Avail) {
			m2Avail = startTime + normal(rng);
		}
		else if (startTime >= m3Avail) {
			m3Avail = startTime + triangular(rng);
		}
		else
			assert(0);

		if (waitingTime > 0.0000001) {
			totalWaiting += waitingTime;
			++nWait;
			if (waitingTime > 1)
				++nWaitMinute;
			if (waitingTime > maxWait)
				maxWait = waitingTime;

		}

	}
	

	cout <<
		"\nAverage waiting time: " << 1.0 * totalWaiting / N <<
		"\nProbability of waiting: " << 100.0 * nWait / N << "%" <<
		"\nProbability of waiting more than 1 minute: " << 100.0 * nWaitMinute / N << "%" <<
		"\nMaximum waiting time: " << maxWait <<
		"\nUtilization of the first ATM machine: " << 100* (arriveTime - m1Free) /arriveTime <<
		"\nUtilization of the second ATM machine: " << 100 * (arriveTime - m2Free) / arriveTime <<
		"\nUtilization of the third ATM machine: " << 100 * (arriveTime - m3Free) / arriveTime <<
		"\n";

}
