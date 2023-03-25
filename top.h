#ifndef __TOP_H__
#define __TOP_H__

#include "Vec.h"
#include "Mat.h"

namespace top {
    void set_rh(double r, double h);
    void set_mIJ(double m, double I, double J);
    void set_mu(double mu_S, double mu_K);
    void set_eps(double eps1, double eps2);
    void set_g(double g);
    int run(Vec_DP& y, double t, double h=0.001);
}

void lusolv(Mat_DP& a, Vec_DP& b);
void rk4(const Vec_DP &y, const Vec_DP &dydx, double x, double h,
         Vec_DP &yout, void derivs(double, const Vec_DP &, Vec_DP &));

#endif // __TOP_H__