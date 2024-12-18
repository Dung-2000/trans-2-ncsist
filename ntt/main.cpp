#include "ntt.h"
#include <fstream>
#include <sstream>

/*
The provided code implements a polynomial multiplication algorithm using the Number Theoretic Transform (NTT). NTT is a fast Fourier transform algorithm designed specifically for multiplying polynomials over a finite field.

Here's a breakdown of the code:

**1. NTT Function:**

* This function performs the NTT on a given polynomial `a` of length `n`.
* It uses a divide-and-conquer approach to recursively compute the NTT of even and odd indexed elements of `a`.
* It combines the transformed halves using the twiddle factor `w` and returns the transformed polynomial `A`.
* If `inverse` is `true`, it performs the inverse NTT, scaling the result by `1/n`.

**2. Poly_Mult Function:**

* This function performs polynomial multiplication using the NTT.
* It first computes the NTT of both polynomials `a` and `b`.
* It then element-wise multiplies the transformed polynomials `A` and `B`.
* Finally, it applies the inverse NTT to the result `C` and rounds the real parts of the complex numbers to obtain the integer coefficients of the product polynomial.

**3. Main Function:**

* The `main` function serves as an example of how to use the `poly_mult` function for polynomial multiplication.
* It reads two polynomials `a` and `b` from input files.
* It calls the `poly_mult` function to compute their product and stores the result in `result`.
* It writes the product polynomial to an output file.

**Overall,** this code provides a fast and efficient way to perform polynomial multiplication using the NTT algorithm. It is commonly used in various applications, including signal processing, cryptography, and computer algebra.
*/

// Function to perform NTT
vector<complex<double>> ntt(vector<complex<double>>& a, int n, bool inverse, int mod) {
    if (n == 1) {
        return a;
    }

    vector<complex<double>> a_even(n / 2);
    vector<complex<double>> a_odd(n / 2);
    for (int i = 0; i < n / 2; ++i) {
        a_even[i] = a[2 * i];
        a_odd[i] = a[2 * i + 1];
    }

    vector<complex<double>> A_even = ntt(a_even, n / 2, inverse);
    vector<complex<double>> A_odd = ntt(a_odd, n / 2, inverse);

    vector<complex<double>> A(n);
    double angle = 2 * M_PI / n * (inverse ? -1 : 1);
    complex<double> w(1, 0);
    complex<double> wn(cos(angle), sin(angle));

    for (int i = 0; i < n / 2; ++i) {
        A[i] = fmod((A_even[i] + w * A_odd[i]).real(), mod) + fmod((A_even[i] + w * A_odd[i]).imag(), mod) * complex<double>(0, 1);

        A[i + n / 2] = fmod((A_even[i] - w * A_odd[i]).real(), mod) + fmod((A_even[i] - w * A_odd[i]).imag(), mod) * complex<double>(0, 1);
        w *= wn;
    }

    if (inverse) {
        for (int i = 0; i < n; ++i) {
            A[i] = fmod((A[i] / complex<double>(n,0)).real(), mod) + fmod((A[i] / complex<double>(n,0)).imag(), mod) * complex<double>(0, 1);
        }
    }

    return A;
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

    vector<complex<double>> A = ntt(a_complex, n, false, MOD);
    vector<complex<double>> B = ntt(b_complex, n, false, MOD);

    vector<complex<double>> C(n);
    for (int i = 0; i < n; ++i) {
        C[i] = A[i] * B[i];
    }

    vector<complex<double>> c_complex = ntt(C, n, true, MOD);
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
