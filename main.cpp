#include <iostream>
#include <cmath>


const int N = 1e4;
const double eps = 1.0 / N;
const double pi = 3.14159265359;


double function (double rho) {

}

double FirstEstimating (double rho) {
    return std::pow((4.0/3.0), 2) * function(rho);
}

double SecondEstimating (double rho, double l) {
    return 16.0/(3.0 * N) * std::pow(rho, 2) * function(rho) * l;
}

double MonteCarloMethod () {

}

int main() {

    return 0;
}
