#ifndef PUNITY_H
#define PUNITY_H

#include "conf.h"
#include "points.h"

typedef t_real (*wfsd_t)(int,int,t_real,t_real*);

typedef struct
{
        int dim;
        int npts;
        t_real *pts;
        t_real *dlt;
        t_real (*wfs)(int,t_real,t_real*);
	t_real (*wfsd)(int,int,t_real,t_real*);
	t_real rmax;
	kdnode_t *kdt;
	char *bdry;
} punity_t;

t_real cubic_window( int, t_real, t_real * );

t_real cubic_window_deriv( int, int, t_real, t_real * );

t_real radial_deriv_evaluate( int, int *, t_real * );

t_real rational_radial_deriv_evaluate( int, int *, t_real *, t_real, int );

int punity_init( punity_t *, int, int, t_real *, t_real *, t_real (*)(int,t_real,t_real*), t_real (*)(int,int,t_real,t_real*) );

int punity_use_pbc( punity_t *, t_real * );

int punity_free( punity_t * );

int punity_neighbors( punity_t *, t_real *, int ** );

t_real punity_evaluate( punity_t *, int, t_real * );

t_real punity_evaluate_delta( punity_t *, int, t_real *, int );

t_real punity_window_deriv_evaluate( punity_t *, int, int *, t_real * );

t_real punity_window_deriv_evaluate_delta( punity_t *, int, int *, t_real *, int );

t_real punity_term_deriv_evaluate( punity_t *, int, int *, t_real *, int *, int );

t_real punity_term_deriv_evaluate_delta( punity_t *, int, int *, t_real *, int, int *, int );

t_real punity_eval_local_poly( punity_t *, int, int *, t_real * );

t_real punity_eval_local_poly_delta( punity_t *, int, int *, t_real *, int );

t_real punity_term_deriv_local_poly( punity_t *, int, int *, int *, t_real *, int *, int );

t_real punity_term_deriv_local_poly_delta( punity_t *, int, int *, int *, t_real *, int, int *, int );

t_real punity_term_deriv_local_radial( punity_t *, int, t_real (*)(int,int,t_real,t_real*), int *, t_real *, int *, int );

#endif

