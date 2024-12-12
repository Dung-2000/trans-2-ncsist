#ifndef NTT_H
#define NTT_H

#include <vector>
#include <complex>

using namespace std;

const int MOD = 7681; // Common choice modulus

// Function declarations
vector<complex<double>> ntt(vector<complex<double>>& a, int n, bool inverse, int mod = MOD);
vector<double> poly_mult(const vector<double>& a, const vector<double>& b);


#endif
