#include "top.h"
#include<cmath>
#include<fstream>

static double degree(atan(1)/45); // 1 deg / radian    

main() {
    int j,k(0),n(500);
    double T(15),h(T/n),mu_S;
//    double w0(4*sqrt(1.5*981/4));
    double w0(90);
    std::ofstream f;
    Vec_DP y(10);
    top::set_rh(4, 2);
    top::set_mIJ(1, 20, 20);

    f.open("fig3a.txt");
    mu_S = 0.1;
    top::set_mu(mu_S, 0.9*mu_S);
    y = 0.;
    y[5] = w0;
    y[6] = w0*0.05;
    for(j=0; j<=n; j++) {
        f << j*h << ' ';
        f << acos(cos(y[1])*cos(y[2]))/degree << ' ';
        f << k << '\n';
        k = top::run(y,h);
    }
    f.close();

    f.open("fig3b.txt");
    mu_S = 0.05;
    top::set_mu(mu_S, 0.9*mu_S);
    y = 0.;
    y[5] = w0;
    y[6] = w0*0.05;
    for(j=0; j<=n; j++) {
        f << j*h << ' ';
        f << acos(cos(y[1])*cos(y[2]))/degree << ' ';
        f << k << '\n';
        k = top::run(y,h);
    }
    f.close();

    f.open("fig3c.txt");
    mu_S = 0.01;
    top::set_mu(mu_S, 0.9*mu_S);
    y = 0.;
    y[5] = w0;
    y[6] = w0*0.05;
    for(j=0; j<=n; j++) {
        f << j*h << ' ';
        f << acos(cos(y[1])*cos(y[2]))/degree << ' ';
        f << k << '\n';
        k = top::run(y,h);
    }
    f.close();
}