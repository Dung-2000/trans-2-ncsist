#include <iostream>
#include <vector>
#include <complex>
#include <fstream>
#include <sstream>

using namespace std;

const int MOD = 7681; // Common choice modulus

// Function to perform NTT
vector<complex<double>> ntt(vector<complex<double>>& a, int n, bool inverse) {
    // ... (rest of the NTT function remains the same)
}


vector<double> poly_mult(const vector<double>& a, const vector<double>& b) {
    int n = 1;
    while (n < a.size() + b.size() - 1) {
        n <<= 1;
    }

    vector<complex<double>> a_complex(n);
    vector<complex<double>> b_complex(n);
    for (int i = 0; i < a.size(); ++i) {
        a_complex[i] = complex<double>(a[i], 0);
    }
    for (int i = 0; i < b.size(); ++i) {
        b_complex[i] = complex<double>(b[i], 0);
    }

    vector<complex<double>> A = ntt(a_complex, n, false);
    vector<complex<double>> B = ntt(b_complex, n, false);

    vector<complex<double>> C(n);
    for (int i = 0; i < n; ++i) {
        C[i] = A[i] * B[i];
    }

    vector<complex<double>> c_complex = ntt(C, n, true);
    vector<double> c(a.size() + b.size() - 1);
    for (int i = 0; i < c.size(); ++i) {
        c[i] = round(c_complex[i].real()); // Round to nearest integer
        c[i] = fmod(c[i], MOD); // Reduce modulo MOD
    }

    return c;
}


int main() {
    // Example usage with file input/output:
    ifstream input_a("input_a.txt");
    ifstream input_b("input_b.txt");
    ofstream output("output.txt");

    string line;
    vector<double> a, b;

    getline(input_a, line);
    stringstream ss_a(line);
    double val;
    while (ss_a >> val) {
        a.push_back(val);
        if (ss_a.peek() == ',') {
            ss_a.ignore();
        }
    }

    getline(input_b, line);
    stringstream ss_b(line);
    while (ss_b >> val) {
        b.push_back(val);
        if (ss_b.peek() == ',') {
            ss_b.ignore();
        }
    }

    vector<double> result = poly_mult(a, b);

    for (double val : result) {
        output << val << ",";
    }
    output << endl;

    return 0;
}
