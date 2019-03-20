#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;
const int N = 500;

template<typename T>
inline void printer(T a, T b, T c, T d, T e, T f, T g, T h) {
	cout <<
		setw(10) << a <<
		setw(10) << b <<
		setw(10) << c <<
		setw(10) << d <<
		setw(10) << e <<
		setw(10) << f <<
		setw(10) << g <<
		setw(10) << h << endl;
}


int main() {
    //freopen("out.txt" , "wt",stdout);
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	discrete_distribution<int> dd{ 20,40,20,10,10 };
int storage = 0;
	for (int supply = 1; supply <= 2; supply++) {
    double avdem = 0,avstor = 0, avshort = 0, avsold = 0, avsurplus = 0, avcos = 0, avprof = 0;
		printer("No.", "Available", "Demand", "Shortage", "Surplus", "Revenue", "Cost", "Profit");
		cout << "-----------------------------------------------------------------\n";

		for (int i = 0; i < N; i++) {
			int demand = dd(rng);
			storage += supply;
			int shortage = max(demand - storage, 0);
			int sold = min(storage, demand);
			int surplus = max(storage - demand, 0);
			int cost = shortage * 100 + surplus * 50;
			int profit = 450 * sold - cost;
			avdem+=demand;
			avshort+=shortage;
			avsold+=sold;
			avsurplus+=surplus;
			avcos+=cost;
			avprof+=profit;
			avstor+=storage;
			printer(i + 1, storage, demand, shortage, surplus, 450 * sold, cost, profit);
			storage -= sold;
		}
		cout << "-----------------------------------------------------------------\n";
		cout << "Average:\n";
		printer("No.", "Cost", "Demand", "Profit", "Shortage", "Sold", "Storage", "Surplus");
        printer(1.0*supply,avcos/N, avdem/N, avprof/N, avshort/N, avsold/N, avstor/N, avsurplus/N);
		cout << "-----------------------------------------------------------------\n";

	}

}
