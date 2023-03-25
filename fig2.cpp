#include "top.h"
#include<cmath>
#include<fstream>

static double degree(atan(1)/45); // 1 deg / radian    

main() {
    int j,k(0),n(1000);
    double T(15),h(T/n),mu_S;
    Vec_DP y(10);
    std::ofstream f;
    top::set_rh(0.2, 4.2);
    top::set_mIJ(1, 3, 3);

    f.open("fig2a.txt");
    mu_S = 0.01;
    top::set_mu(mu_S, mu_S*0.9);
    y = 0.;
    y[1] = 30*degree;
    y[5] = 200;
    for(j=0; j<=n; j++) {
        f << j*h << ' ';
        f << acos(cos(y[1])*cos(y[2]))/degree << ' ';
        f << k << '\n';
        k = top::run(y,h);
    }
    f.close();

    f.open("fig2b.txt");
    mu_S = 0.02;
    top::set_mu(mu_S, mu_S*0.9);
    y = 0.;
    y[1] = 30*degree;
    y[5] = 200;
    for(j=0; j<=n; j++) {
        f << j*h << ' ';
        f << acos(cos(y[1])*cos(y[2]))/degree << ' ';
        f << k << '\n';
        k = top::run(y,h);
    }
    f.close();

    f.open("fig2c.txt");
    mu_S = 0.01;
    top::set_mu(mu_S, mu_S*0.9);
    y = 0.;
    y[1] = 30*degree;
    y[5] = 300;
    for(j=0; j<=n; j++) {
        f << j*h << ' ';
        f << acos(cos(y[1])*cos(y[2]))/degree << ' ';
        f << k << '\n';
        k = top::run(y,h);
    }
    f.close();

    f.open("fig2d.txt");
    mu_S = 0.02;
    top::set_mu(mu_S, mu_S*0.9);
    y = 0.;
    y[1] = 30*degree;
    y[5] = 300;
    for(j=0; j<=n; j++) {
        f << j*h << ' ';
        f << acos(cos(y[1])*cos(y[2]))/degree << ' ';
        f << k << '\n';
        k = top::run(y,h);
    }
    f.close();
}