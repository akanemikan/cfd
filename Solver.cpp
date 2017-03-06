#include "Solver.h"

void Solver::CGSolver(const matrix &A, const source &b, source &x, int n)
{
    source r(n), p(n), y(n);
    //x.assign(n, 0.0);

    for(int i=0; i<n; ++i){
        double ax = 0.0;
        for(int j=0; j<n; ++j){
            ax += A[i][j]*x[j];
        }
        r[i] = b[i]-ax;
        p[i] = r[i];
    }

    double rr0 = (r & r), rr1;
    double alpha, beta;

    int k;
    for(k=0; k<10; ++k){
        for(int i=0; i<n; ++i){
            y[i] = A[i] & p;
        }

        alpha = rr0/(p & y);

       for(int i=0; i<n; ++i){
           x[i] += alpha*p[i];
           r[i] -= alpha*y[i];
       }

       rr1 = r & r;

       beta = rr1/rr0;
       for(int i=0; i<n; ++i){
           p[i] = r[i]+beta*p[i];
       }

       rr0 = rr1;
    }


}
