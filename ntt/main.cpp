#include <iostream>
#include <vector>
#include <complex>

using namespace std;

// Function to perform NTT
vector<complex<double>> ntt(vector<complex<double>>& a, int n, bool inverse) {
    // Bit-reversal permutation
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    // Cooley-Tukey FFT algorithm
    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * M_PI / len * (inverse ? -1 : 1);
        complex<double> wlen(cos(angle), sin(angle));

        for (int i = 0; i < n; i += len) {
            complex<double> w(1);
            for (int j = 0; j < len / 2; j++) {
                complex<double> u = a[i + j];
                complex<double> v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    // If inverse NTT, divide by n
    if (inverse) {
        for (int i = 0; i < n; i++)
            a[i] /= n;
    }

    return a;
}

int main() {
    int n = 8; // Size of the input vector (power of 2)
    vector<complex<double>> a = {1, 2, 3, 4, 5, 6, 7, 8};

    // Perform NTT
    vector<complex<double>> A = ntt(a, n, false);

    cout << "NTT result:" << endl;
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;


    // Perform inverse NTT
    vector<complex<double>> a_inv = ntt(A, n, true);

    cout << "Inverse NTT result:" << endl;
    for (int i = 0; i < n; i++)
        cout << a_inv[i] << " ";
    cout << endl;

    return 0;
}
