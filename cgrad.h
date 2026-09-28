#ifndef	CGRAD_H
#define CGRAD_H

void copy( int, double *, double * );
void project( int, double *, int, double * );
void bicgstab( int, int, double *, double *, double *, int, double, int, int * );
void bicgstabp( int, int, double *, double *, int, double *, double *, int, double, int, int * );
void ulanczos( int, int, double *, double *, double *, double *, double *, double *, int * );
void treiglr( int, double *, double *, double *, int, double *, int *, int * );
void treigqds( int, double *, double *, double *, int, double *, int *, int * );
void treigdqds( int, double *, double *, double *, int, double *, int *, int * );
void treigtridqds( int, double *, double *, double *, int, double *, int *, int * );
void sgsinvi( int, long *, long *, double *, long *, long *, double *, double *, double, double, int, int );
void nrandv( int, double * );
void sgsilanczoscr( int, int, int, long*, long*, double*, long*, long* , double*, double*, double*, double*, double*, double*, double*, int*, double, double*, int, int, int* );
int smsave( char *fn, long, long, long*, long*, double*, int );

#endif
