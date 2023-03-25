#include "top.h"
#include<cmath>
#include<fstream>

static double degree(atan(1)/45); // 1 deg / radian    

main() {
    int j,k(0),n(200);
    double T,h;
    std::ofstream f;
    Vec_DP y(10);
    top::set_rh(1, 1.5);
    top::set_mIJ(1, 0.05, 0.07);
    top::set_mu(0.01, 0.009);

    f.open("fig4a.txt");
    T = 0.5;
    h = T/n;
    y = 0.;
    y[5] = 43.94;
    y[6] = 0.087;
    for(j=0; j<=n; j++) {
        f << j*h << ' ';
        f << acos(cos(y[1])*cos(y[2]))/degree << ' ';
        f << k << '\n';
        k = top::run(y,h);
    }
    f.close();

    f.open("fig4b.txt");
    T = 3;
    h = T/n;
    y = 0.;
    y[5] = 43.94;
    y[6] = 0.043;
    for(j=0; j<=n; j++) {
        f << j*h << ' ';
        f << acos(cos(y[1])*cos(y[2]))/degree << ' ';
        f << k << '\n';
        k = top::run(y,h);
    }
    f.close();

    f.open("fig4c.txt");
    y = 0.;
    y[5] = 43.94;
    y[6] = 0.022;
    for(j=0; j<=n; j++) {
        f << j*h << ' ';
        f << acos(cos(y[1])*cos(y[2]))/degree << ' ';
        f << k << '\n';
        k = top::run(y,h);
    }
    f.close();
}