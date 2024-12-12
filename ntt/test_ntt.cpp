#include "ntt.h"
#include <cassert>
#include <iostream>


int test_poly_mult() {
    // Test case 1: Simple multiplication
    vector<double> a = {1, 2, 3};
    vector<double> b = {4, 5};
    vector<double> expected_result = {4, 13, 22, 15};
    vector<double> result = poly_mult(a, b);

    assert(result == expected_result);

    // Test case 2: Zero padding
    a = {1, 2};
    b = {1};
    expected_result = {1, 2};
    result = poly_mult(a, b);
    assert(result == expected_result);


    // Test case 3: Larger polynomials
    a = {1, 2, 3, 4, 5};
    b = {6, 7, 8, 9, 10};
    expected_result = {6, 19, 40, 70, 110, 98, 74, 50};
    result = poly_mult(a, b);
    assert(result == expected_result);

        // Test case 4: Modulo operation
    a = {7680, 7680};
    b = {2,2};
    expected_result = {15360%MOD, 30720%MOD, 15360%MOD};
    result = poly_mult(a, b);

    vector<double> expected_result_mod = {7679, 7678, 7679};
    assert(result == expected_result_mod);

    cout << "All test cases passed!" << endl;
    return 0;
}

int main(){
    test_poly_mult();
    return 0;

}
