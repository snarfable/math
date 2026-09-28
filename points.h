#ifndef POINTS_H
#define POINTS_H

#define DOMAIN_CUBE 0
#define DOMAIN_BOX 1
#define DOMAIN_SPHERE 2
#define DOMAIN_ELLIPSOID 3

#include "math_config.h"
#include "conf.h"

typedef struct
{
	int dim;
	int type;
	t_real *orig;
	t_real *params;
} shape_t;

void point_print( FILE *, int, t_real * );

void domain_indicator( t_real *, shape_t *, int * );

int sphere_intersection( int, t_real *, t_real, t_real *, t_real, t_real *, t_real *, t_real * );

void lens_gauss_point( int, t_real *, t_real, t_real *, t_real, t_real , t_real *, long *, t_real *, t_real *, t_real *, t_real * );

t_real lens_volume( int, t_real, t_real, t_real );

void sphere_gauss_point( int, t_real *, t_real, t_real *, long *, t_real *, t_real *, t_real *, t_real * );

int load_points( char *, int *, int *, t_real **, int );

int write_points( char *, int, int, t_real *, int );

int generate_cloud_macqueen( int, int, int, int (*)(t_real*,void*), t_real (*)(t_real*,void*), t_real *, t_real **, void *, void * );

int smooth_cloud_macqueen( int, int, int, int (*)(t_real*,void*), t_real (*)(t_real*,void*), t_real *, t_real *, void *, void * );

int smooth_cloud_bubble_mc( int, int, t_real *, int (*)(t_real*,void*), t_real (*)(t_real*,void*), t_real, t_real *, t_real *, t_real, t_real, int, int, void *, void * );

int generate_cloud_supports( int, int, t_real *, int, t_real, t_real * );

int generate_cloud_supports_min( int, int, t_real *, int, t_real, t_real *, t_real );

/**
 * Data structure for kd trees for use in nearest neighbor
 * set finding algorithms
 */
struct kdnode_s
{
        int dim;
        int depth;
	int npts;
	int idx;
	t_real split;
        t_real *pos;
        struct kdnode_s *left;
        struct kdnode_s *right;
};

typedef struct kdnode_s kdnode_t;

int kdtree_build_median( kdnode_t *, int, int, t_real *, int );

int kdtree_build_average( kdnode_t *, int, int, t_real *, int, int );

int kdtree_range_query( kdnode_t *, t_real *, t_real, int **, int *, int * );

void kdtree_walk( kdnode_t * );

void boundary_indicator( double *, shape_t *, double, int * );

void load_domain( char *, shape_t *, int * );

#endif

