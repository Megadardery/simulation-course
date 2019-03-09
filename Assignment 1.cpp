#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;

//219 █ 220 ▄  221 ▌  222 ▐  223 ▀  254 ■
char HIST = 219;

const int nFREQ_C1 = 5, nFREQ_C2 = 21, nFREQ_X = 30, nFREQ_P = 35;

int freq_c1[nFREQ_C1];
const int C1_OFF = 43;

int freq_c2[nFREQ_C2];
const int C2_OFF = 80;

int freq_x[nFREQ_X];
const int X_FACT = 1000;

int freq_p[nFREQ_P];
const int P_OFF = -10, P_FACT = 100000;

void drawHistogram(ostream& out, int freq[], int n, int off = 0, int factor = 1, int max_width = 70);

int main() {
	char resp;
	
	cout << "Welcome! This is Assignment 1 in Simulation course by Ahmed Nasr Eldardery - 20170034\n";
	cout << "Just one thing to set up before we start :)\n";
	cout << "The default character for histogram graph is: " << HIST << ". Is this character rendered correctly?\n";
	cin >> resp;
	if (resp == 'n') {
		cout << "Please enter a character to use for histogram graph:\n";
		cin >> HIST;
	}
	else {
		cout << "Would you like to draw a narrow histogram instead of a blended histogram?\n";
		cin >> resp;
		if (resp == 'y') {
			HIST = 254;
		}
	}
	cout << "All set! Thanks for using my app!\n";

	cout << left << fixed;
	const double FIXED_COSTS = 1000000;
	const double PRICE = 249;

	std::mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

	std::discrete_distribution<int> c1g{ 1,2,4,2,1 };
	std::uniform_real_distribution<double> c2g(80, 100);
	std::normal_distribution<double> xg(15000, 4500);


	const int myRuns[] = { 10,1000000 };
	for (int k = 0; k < 2; k++) {
		int RUNS = myRuns[k];

		cout << "######################################################################################";
		for (int temp = RUNS * 10; temp /= 10;) cout << "#";
		cout << endl << "#############################RESULTS FOR " << RUNS << " SIMULATION RUNS#############################" << endl;
		for (int temp = RUNS * 10; temp /= 10;) cout << "#";
		cout << "######################################################################################";
		cout << endl << endl;

		cout << "======================================FIRST " << min(RUNS, 100) << " RUNS=======================================" << endl << endl;

		int nLoses = 0;
		double maxProfit = 0;
		double maxLoss = 0;
		double probLoss;
		double avgProfit = 0;
		
		cout << setw(15) << "N" << setw(15) << "C1" << setw(15) << "C2" << setw(20) << "X" << setw(20) << "Profit" << endl;
		for (int i = 0; i < RUNS; i++) {
			int c1 = c1g(rng) + C1_OFF;
			double c2 = c2g(rng);
			double x = xg(rng);


			++freq_c1[c1 - C1_OFF];
			++freq_c2[int(c2 - C2_OFF)];
			++freq_x[int(x / X_FACT)];

			double profit = (PRICE - c1 - c2)*x - FIXED_COSTS;

			if (i < 100)
				cout << setw(15) << i+1 << setw(15) << c1 << setw(15) << c2 << setw(20) << x << setw(20) << profit << '\n';

			++freq_p[int(profit / P_FACT - P_OFF + 0.5)];

			if (profit < 0) {
				++nLoses;
				if (-profit > maxLoss)
					maxLoss = -profit;
			}
			if (profit > maxProfit)
				maxProfit = profit;

			avgProfit += profit;
		}
		probLoss = nLoses *1.0 / RUNS;
		avgProfit /= RUNS;
		cout << endl << endl;


		cout << "Average profit is: " << avgProfit << endl;
		cout << "Max profit is: " << maxProfit << endl;
		cout << "Max Loss is: " << maxLoss << endl;
		cout << "Probility of loss is: " << probLoss << endl;
		cout << endl;

		cout << "========================DISTRIBUTION FOR C1: Direct labor cost==========================" << endl << endl;
		drawHistogram(cout, freq_c1, nFREQ_C1, C1_OFF, 1);
		cout << endl;

		cout << "=============================DISTRIBUTION FOR C2: parts cost============================" << endl << endl;
		drawHistogram(cout, freq_c2, nFREQ_C2, C2_OFF, 1);
		cout << endl;

		cout << "================================DISTRIBUTION FOR DEMAND=================================" << endl << endl;
		drawHistogram(cout, freq_x, nFREQ_X, 0, X_FACT);
		cout << endl;

		cout << "================================DISTRIBUTION FOR PROFIT=================================" << endl << endl;
		drawHistogram(cout, freq_p, nFREQ_P, P_OFF, P_FACT);
		cout << endl;
	}
	cout << "####################################CONCLUSIONS########################################" << endl << endl;
	cout <<
		"The results are more accurate when we run more simulations.\n" <<
		"We can notice that the Histogram of the variables fits the definition much more accurately for the second test.\n" <<
		"It is also apparent that loss is almost guarenteed in the long run.\n" << endl;
}

void drawHistogram(ostream& out, int freq[], int n, int off, int factor, int max_width) {
	const char* format = "%d - ";

	char temp[100];
	int mx = 1;
	for (int i = 0; i < n; i++) {
		mx = max(mx, freq[i]);
	}
	if (mx < max_width)
		mx = max_width / 2;
	for (int i = 0; i < n; i++) {
		sprintf(temp, format, factor * (i + off));
		out << left << setw(15) << temp;
		
		int en = 1.0 * freq[i] * max_width / mx + 0.5;
		
		for (int j = 0; j < en; j++) {
			out << HIST;
		}
		out << endl;
	}
	out << endl;
}
