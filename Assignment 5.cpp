#include <bits/stdc++.h>
#include <random>
using namespace std;

const int N = 1e6, M = 20;

mt19937 rng(time(0));
normal_distribution<double> IAT(60.0 / 40.0, 6.0 / 40.0);
normal_distribution<double> ST(6, 1);

double Simulate(int CLERKS, int MAX_CUSTOMERS, double LEASE);

const double SALE = 22, COST = 10.0 / 60, RATE = 20.0 / 60;
int main() {
	cout << fixed;
	double run1 = Simulate(2, 3, 200);
	double run2 = Simulate(6, 15, 2000);
	cout << "CONCLUSION: it is better to go with the " << (run1 > run2 ? "first" : "second") << " approach!\n";

}

double Simulate(int CLERKS, int MAX_CUSTOMERS, double LEASE) {

	double arriveTime = 0, processTime = 0;
	double freeTime[M] = {};
	double inShop[M] = {};

	double totalRevenue = 0;
	double totalCost = 0;

	int totalLeft = 0;
	int totalWait = 0;
	int numOfDays = 0;

	for (int i = 0; i < N; ++i) {
		arriveTime += IAT(rng);

		//find the first slot available for our customer to stand in.
		int slotIdx = find_if(inShop, inShop + MAX_CUSTOMERS, [arriveTime](int x) {return x <= arriveTime; }) - inShop;

		//if no place for customer
		if (slotIdx >= MAX_CUSTOMERS) {
			++totalLeft;
			continue;
		}

		//find the first free clerk
		int clerkIdx = min_element(freeTime, freeTime + CLERKS) - freeTime;


		double waiting = freeTime[clerkIdx] - arriveTime;
		if (waiting > 0.000001) {
			++totalWait;

			totalCost += COST * waiting;
			processTime = freeTime[clerkIdx];
		}
		else
			processTime = arriveTime;

		if (processTime > 10 * 60) {
			memset(inShop, 0, sizeof inShop);
			memset(freeTime, 0, sizeof freeTime);
			arriveTime = 0;
			numOfDays++;
			continue;
			totalCost += LEASE;
			totalCost += 10*60 * COST;
			--i;
		}
		inShop[slotIdx] = freeTime[clerkIdx] = processTime + ST(rng);
		totalRevenue += SALE;
	}
	numOfDays++;
	totalCost += LEASE;
	totalCost += 10 * 60 * COST;

	double totalProfit = totalRevenue - totalCost;
#define PRINT(a,b) cout << (a) << (b) << endl
	PRINT("Number of days: ", numOfDays);
	PRINT("Number of customers: ", N);
	cout << "-----------------------------\n";
	PRINT("Probability of waiting :", totalWait * 100.0 / N);
	PRINT("Probability of leaving :", totalLeft * 100.0 / N);
	cout << "-----------------------------\n";
	PRINT("Total Cost : ", totalCost);
	PRINT("Total Revenue : ", totalRevenue);
	PRINT("Total Profit : ", totalProfit);
	cout << "==============================\n\n";

	return totalProfit;
}



/*
Task #5 {Submit in the week starting 20th April}

Tie One On, an exclusive men’s clothing store specializing in ties,
is planning to develop a store in a new shopping mall.
Customers are expected to arrive at the store location at random
at an average rate of 40 per hour. I.e. IAT : Normal Distr. {60/40;6/40} (minutes).
The store will be open 10 hours per day. Service time (of a customer) is assumed
to follow a normal distribution {6,1} (minutes).
The average sale to a customer is $22. Clerks are paid $20/hr.
(including all benefits), and the cost of having a waiting customer
is estimated to be $10 per customer per hour.
One possibility is to have a small store staffed by 2 clerks This store,
however, will only have room for a maximum of 3 customers to be present.
Another possibility is to have a larger store with 6 clerks.
The larger store can accommodate up to a total of 15 customers.
It is believed that customers who arrive when the store is full will shop elsewhere.
If the small store leases for $200 per day and the large store leases for $ 2000 per day,
which configuration should be used?

Develop a computer program to solve the above problem (via the simulation approach)
*/
