#include <iostream>
#include <cmath>
#include <tuple>
#include <cstdlib>
#include <ctime>

const long N = 1.0e5;
const double eps = 1.0 / N;
const double pi = 3.14159265359;

typedef std::tuple<double, double, double> DoubleTuple;

double accuracy(double x) {
    //The function leaves the required number of decimal places.
    return trunc(x / eps) * eps;
}

double fun(double rho, double m) {
    return 1 / std::pow(pi, 2) / std::pow(rho, m);
}

DoubleTuple roulette() {
    //The function generates two random radius vector lengths and random cos of angle between them.
    srand(time(NULL));
    double rP = std::pow(eps * (rand()%(N+1)), 1.0/3.0);
    double mu = eps * (rand()%(N+1)) - 1; //mu == cos(rP, rQ)
    double rQ = std::pow(eps * (rand()%(N+1)), 1.0/3.0);
    return std::make_tuple(rP, mu, rQ);
}

double rho(DoubleTuple& points) {
    //The function returns distance between the ends of vectors rP and rQ by the cosine theorem.
    double rP = std::get<0>(points);
    double mu = std::get<1>(points);
    double rQ = std::get<2>(points);
    return std::sqrt(std::pow(rP, 2) + std::pow(rQ, 2) - 2*rP*rQ*mu);
}

double first_estimating(double fun(double arg, double m), double m) {
    double sum = 0;
    for(long i = 0; i < N; i++) {
        DoubleTuple foo = roulette();
        sum += fun(rho(foo), m);
    }
    return std::pow(4.0/3.0, 2) * eps * sum;
}

double second_estimating(double func(double arg, double m), double m) {
    double sum = 0;
    for(long i = 0; i < N; i++) {
        DoubleTuple foo = roulette();
        double rho_i = rho(foo);
        double rP = std::get<0>(foo);
        double mu = std::get<1>(foo);
        double l = rP*mu + std::sqrt(1 - std::pow(rP, 2)*(1 - std::pow(mu, 2)));
        sum += std::pow(rho_i, 2) * fun(rho_i, m) * l;
    }
    return 16.0 * eps / 3.0 * sum;
}

int main() {
    std::cout << "Integrand:\t 1 / pi^2 * 1 / rho^m\n" <<
    "m = 1\n" << "1st estimating:\t" << accuracy(first_estimating(fun, 1)) << std::endl <<
    "2nd estimating:\t" << accuracy(second_estimating(fun, 1)) << std::endl <<
    "m = 2\n" << "1st estimating:\t" << accuracy(first_estimating(fun, 2)) << std::endl <<
    "2nd estimating:\t" << accuracy(second_estimating(fun, 2)) << std::endl;
    return 0;
}
