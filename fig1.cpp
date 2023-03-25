#include "top.h"
#include<cmath>
#include<fstream>

static double degree(atan(1)/45); // 1 deg / radian    

main() {
    int j,k(0),n(200);
    double T(6),h(T/n);
    std::ofstream f("fig1.txt");
    Vec_DP y(0.,10);
    top::set_rh(13.8, 7.37);
    top::set_mIJ(1, 110, 69);
    top::set_mu(0.15, 0.14);
    y[1] = 90*degree;
    for(j=0; j<=n; j++) {
        f << j*h << ' ';
        f << y[4] << ' ';
        f << k << '\n';
        k = top::run(y,h);
    }
}