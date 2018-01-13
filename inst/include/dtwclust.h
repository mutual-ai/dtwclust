#ifdef __cplusplus
extern "C" {
#endif

#ifndef DTWCLUST_H_
#define DTWCLUST_H_

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

SEXP dtw_basic(SEXP x, SEXP y, SEXP window,
               SEXP m, SEXP n, SEXP num_var,
               SEXP norm, SEXP step, SEXP backtrack, SEXP normalize,
               SEXP distmat)
{
    static SEXP(*fun)(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP) = NULL;
    if(fun == NULL)
        fun = (SEXP(*)(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP)) R_GetCCallable("dtwclust", "dtw_basic");
    return fun(x, y, window, m, n, num_var, norm, step, backtrack, normalize, distmat);
}

SEXP logGAK(SEXP x, SEXP y, SEXP nx, SEXP ny, SEXP num_var, SEXP sigma, SEXP window, SEXP logs)
{
    static SEXP(*fun)(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP) = NULL;
    if(fun == NULL)
        fun = (SEXP(*)(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP)) R_GetCCallable("dtwclust", "logGAK");
    return fun(x, y, nx, ny, num_var, sigma, window, logs);
}

#endif // DTWCLUST_H_

#ifdef __cplusplus
}
#endif
