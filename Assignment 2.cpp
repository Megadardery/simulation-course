#include <iostream>
#include <iomanip>

using namespace std;

void PRNG(long long seed) {
	const long long a = 871203214;
	const long long b = 194670251;
	const long long c = 1000000007;

	for (int i = 0; i < 100; i++) {
		seed = (seed % c * a % c + b) % c;
		cout << seed / (c-1.0) << endl;
	}

}

int main() {
	cout << fixed << setprecision(5);
  long long n;
  while (1) {
	  cout << "Enter seed: ";
		cin >> n;
		PRNG(n);
	}
}
