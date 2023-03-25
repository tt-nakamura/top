// reference:
//  T. R. Kane and D. A. Levinson
//   "A Realistic Solution of the Symmetric Top Problem"
//    Journal of Applied Mechanics 45 (1978) 903

#include "top.h"
#include<cmath>

static double I(3);// axial moment of inertia / (mass cm^2)
static double J(3);// transverse moment of inertia / (mass cm^2)
static double r(0.2);// radius of spherical part of top / cm
static double h(4);// height of center of gravity from center of sphere / cm
static double mu_S(0.01);// coefficient of static friction
static double mu_K(0.009);// coefficient of kinematic friction
static double eps1(0.5);// threshold from sliding to rolling / cm/s
static double eps2(0.6);// threshold from rolling to sliding / cm/s
static double g(981);// acceleration of graivity / cm/s^2

static double r2(r*r), rh(r*h), IJ(I-J), mKS(mu_K/mu_S);

// functions to set parameters
void top::set_rh(double r_, double h_)
// r = radius of spherical part of top / cm
// h = height of center of gravity from BOTTOM point / cm
{ r = r_; h = h_-r; r2 = r*r; rh = r*h; }

void top::set_mIJ(double m, double I_, double J_)
// I,J = axial and transverse moments of inertia (cgs)
{ I = I_/m; J = J_/m; IJ = I-J; }

void top::set_mu(double mu_S_, double mu_K_)
// mu_S,mu_K = coefficients of static and kinematic friction
{ mu_S = mu_S_; mu_K = mu_K_; mKS = mu_K/mu_S; }

void top::set_eps(double eps1_, double eps2_)
// eps1 = threshold from sliding to rolling / cm/s
// eps2 = threshold from rolling to sliding / cm/s
{ eps1 = eps1_; eps2 = eps2_; }

void top::set_g(double g_) { g = g_; }
// acceleration of gravity / cm/s^2

static double a1,a2,a3;// acceleration of center of gravity
static double f2,f3;// friction force when start sliding
static int trace(0);// index of slide or roll
// trace == 0 if rolling (with a1,a2,a3 evaluation)
//          1 if rolling
//          2 if sliding steadily
//          3 if start sliding

static void eom(double t, const Vec_DP& y, Vec_DP& f)
// equation of motion
// y[:5] = q1,q2,q3,q4,q5 (coordinates)
// y[5:] = u1,u2,u3,u4,u5 (velocities)
// f[:5] = RHS of kinematical differential equation
// f[5:] = RHS of dynamical differential equation
{
    const double &q1(y[0]), &q2(y[1]), &q3(y[2]);
    const double &u1(y[5]), &u2(y[6]), &u3(y[7]);
    const double &u4(y[8]), &u5(y[9]);
    double c1(cos(q1)),c2(cos(q2)),c3(cos(q3));
    double s1(sin(q1)),s2(sin(q2)),s3(sin(q3));
    double s1c2(s1*c2),c1c2(c1*c2);
    double s22(s2*s2),c2s3(c2*s3),c22s33(c2s3*c2s3);
    double rc(h + r*c2*c3), rc2(rc*rc);
    double u12(u1*u2),u13(u1*u3),u23(u2*u2 + u3*u3);
    double cc13(c1*c3 - s1*s2*s3),sc13(s1*c3 + c1*s2*s3);
    double cs13(c1*s3 + s1*s2*c3),ss13(s1*s3 - c1*s2*c3);
    double gr((g + r*u23)*h),IJr(IJ - h*rc);
    int i;

    // kinematic diff eq
    f[0] = (c3*u1 - s3*u2)/c2;
    f[1] = s3*u1 + c3*u2;
    f[2] = u3 - f[0]*s2;
    f[3] = u4 + r*(u1*ss13 + u2*sc13 + u3*c1c2);
    f[4] = u5 - r*(u1*cs13 + u2*cc13 - u3*s1c2);

    if(trace <= 1) {// rolling
        static Mat_DP A(3,3);
        static Vec_DP b(3);
        
        A[0][0] = r2*(s22 + c22s33) + I;
        A[1][1] = r2*s22 + rc2 + J;
        A[2][2] = r2*c22s33 + rc2 + J;
        A[0][1] = A[1][0] = r*rc*c2s3;
        A[0][2] = A[2][0] =-r*rc*s2;
        A[1][2] = A[2][1] = r2*s2*c2s3;
        
        b[0] = rh*(u12*s2 + u13*c2s3);
        b[1] = gr*s2 - u13*IJr;
        b[2] = gr*c2s3 + u12*IJr;
        
        lusolv(A,b);
        for(i=0; i<3; i++) f[i+5] = b[i];
        f[8] = f[9] = 0;

        if(trace) return;
        // evaluate acceleration of center of gravity
        const double &p1(f[5]), &p2(f[6]), &p3(f[7]);
        a1 = h*((u13 - p2)*s2 - (u12 + p3)*c2s3 - u23*c2*c3);
        a2 = r*p1*ss13 + p2*(r*sc13 + h*s1c2)
            + p3*(r*c1c2 + h*cc13)
            - h*(u13*s1c2 - u12*cc13 + u23*cs13);
        a3 = -r*p1*cs13 - p2*(r*cc13 + h*c1c2)
            + p3*(r*s1c2 + h*sc13)
            + h*(u13*c1c2 + u12*sc13 - u23*ss13);
    }
    else {// sliding
        static Mat_DP A(5,5);
        static Vec_DP b(5);

        A[0][0] = r2*(s22 + c22s33) + I;
        A[1][1] = r2*s22 + rc2 + J;
        A[2][2] = r2*c22s33 + rc2 + J;
        A[3][3] = A[4][4] = 1;
        A[0][1] = A[1][0] = r*rc*c2s3;
        A[0][2] = A[2][0] =-r*rc*s2;
        A[0][3] = A[3][0] = r*ss13;
        A[0][4] = A[4][0] = -r*cs13;
        A[1][2] = A[2][1] = r2*s2*c2s3;
        A[1][3] = A[3][1] = r*sc13 + h*s1c2;
        A[1][4] = A[4][1] =-r*cc13 - h*c1c2;
        A[2][3] = A[3][2] = r*c1c2 + h*cc13;
        A[2][4] = A[4][2] = r*s1c2 + h*sc13;
        A[3][4] = A[4][3] = 0;
        
        b[0] = rh*(u12*s2 + u13*c2s3);
        b[1] = gr*s2 - u13*IJr;
        b[2] = gr*c2s3 + u12*IJr;
        b[3] = h*(u13*s1c2 - u12*cc13 + u23*cs13);
        b[4] =-h*(u13*c1c2 + u12*sc13 - u23*ss13);

        if(trace == 2) {// steady sliding
            double v(mu_K/sqrt(u4*u4 + u5*u5));
            double v4(v*u4), v5(v*u5), hv4(h*v4), hv5(h*v5);
            double ug(h*(u12*c2s3 - u13*s2 + u23*c2*c3) - g);
            A[3][1] -= s2*hv4;
            A[4][1] -= s2*hv5;
            A[3][2] -= c2s3*hv4;
            A[4][2] -= c2s3*hv5;
            b[3] += ug*v4;
            b[4] += ug*v5;
        }
        else {// start sliding
            b[3] += f2;
            b[4] += f3;
        }
        lusolv(A,b);
        for(i=0; i<5; i++) f[i+5] = b[i];
    }
}

static void run_(Vec_DP& y, double h)
// input:
//   y = initial conditions of dependent variables
//   h = time step of integration / sec
// output:
//   y = updated state of dependent variables
// assume y.size()==10
{
    double t, &u4(y[8]), &u5(y[9]);
    double v(sqrt(u4*u4 + u5*u5));
    static Vec_DP f(10);
    // examine conditions for sliding or rolling
    // Kane and Levinson, fig2
    if(trace == 3 && v <= eps2)
        ;// start sliding
    else if(v > eps1)
        trace = 2;// steady sliding
    else if(trace >= 2)
        trace = 1;// start rolling
    else {
        trace = 0;
        eom(t,y,f);// evaluate a1,a2,a3
        // Kane and Levinson, eq(14)
        if(sqrt(a2*a2 + a3*a3) >= mu_S*(a1+g)) {
            trace = 3;// start sliding
            f2 = mKS*a2;
            f3 = mKS*a3;
        }
        else trace = 1;// steady rolling
    }
    if(trace == 1) u4 = u5 = 0;
    eom(t,y,f);
    rk4(y,f,t,h,y,eom);
}

int top::run(Vec_DP& y, double t, double h)
// input:
//   y = initial conditions of dependent variables
//   t = duration of integration / sec
//   h = time step of integration / sec
// output:
//   y = final state of dependent variables
// return 0 if rolling, 1 if sliding
// assume y.size()==10 and t>0 and h>0
{
    while(t>0) {
        if(t<h) h=t;
        run_(y,h);
        t-=h;
    }
    return (trace >= 2);
}