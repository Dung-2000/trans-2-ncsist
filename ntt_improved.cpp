#include <vector>
#include <complex>
#include <cmath>

// Define MOD here.  Choose a suitable prime number.  This example uses a Fermat prime.
const long long MOD = 65537; 

using namespace std;

// Function to perform NTT
vector<complex<double>> ntt(vector<complex<double>>& a, int n, bool inverse) {
    if (n == 1) return a;

    // Use references to avoid unnecessary copies
    vector<complex<double>>& a_even = a;
    vector<complex<double>> a_odd(n / 2);

    for (int i = 0; i < n / 2; ++i) {
        a_odd[i] = a[2 * i + 1];
    }

    vector<complex<double>> A_even = ntt(a, n / 2, inverse); // a is now a_even
    vector<complex<double>> A_odd = ntt(a_odd, n / 2, inverse);

    vector<complex<double>> A(n);
    double angle = 2 * M_PI / n * (inverse ? -1 : 1);
    complex<double> w(1, 0);
    complex<double> wn(cos(angle), sin(angle));

    for (int i = 0; i < n / 2; ++i) {
        A[i] = A_even[i] + w * A_odd[i];
        A[i + n / 2] = A_even[i] - w * A_odd[i];
        w *= wn;
    }

    if (inverse) {
        for (int i = 0; i < n; ++i) {
            A[i] /= n; // Division by n is simpler here.
        }
    }

    return A;
}

vector<double> poly_mult(const vector<double>& a, const vector<double>& b) {
    int n = 1;
    while (n < a.size() + b.size() - 1) n <<= 1;

    vector<complex<double>> a_complex(n);
    vector<complex<double>> b_complex(n);
    for (size_t i = 0; i < a.size(); ++i) a_complex[i] = complex<double>(a[i], 0);
    for (size_t i = 0; i < b.size(); ++i) b_complex[i] = complex<double>(b[i], 0);

    vector<complex<double>> A = ntt(a_complex, n, false);
    vector<complex<double>> B = ntt(b_complex, n, false);

    vector<complex<double>> C(n);
    for (int i = 0; i < n; ++i) C[i] = A[i] * B[i];

    vector<complex<double>> c_complex = ntt(C, n, true);
    vector<double> c(a.size() + b.size() - 1);
    for (size_t i = 0; i < c.size(); ++i) {
        c[i] = round(c_complex[i].real());
        //Modulo operation removed as it's not strictly necessary for polynomial multiplication and can be computationally expensive.
    }

    return c;
}
