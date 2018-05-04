#ifndef VBAP_H
#define VBAP_H

#include <math.h>

#ifndef WIN32

#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>

#endif

#include "ext.h"

#if defined( WIN32) || defined(WINxx)
#define SPRINTF sprintf
#else
#define SPRINTF sprintf
#endif

#ifdef WIN32
// don't know where it is in win32, so add it here
#define M_PI        3.14159265358979323846264338327950288   /* pi */
#endif

#define MAX_LS_SETS 100            // maximum number of loudspeaker sets (triplets or pairs) allowed
#define MAX_LS_AMOUNT 55    // maximum amount of loudspeakers, can be increased
#define MIN_VOL_P_SIDE_LGTH 0.01

#define VBAP_VERSION "vbap - v1.0.7 - 3 may 2018 - (c) Ville Pulkki 1999-2018"
#define DFLS_VERSION "define_loudspeakers - v1.0.7 - 3 may 2018 - (c) Ville Pulkki 1999-2018"

static float rad2ang = (float) (360.0f / (2.0f * M_PI));
static float atorad  = (float) ((2.0f * M_PI) / 360.0f);

#ifdef VBAP_OBJECT
// We are inside vbap object, so sending matrix from define_loudspeakers is a simple call to the vbap receiver...
#define sendLoudspeakerMatrices(x, list_length, at) \
                    vbap_matrix(x, gensym("loudspeaker-matrices"),(int)list_length, at); \
                    vbap_bang(x)
#else
// We are inside define_loudspeaker object, send matrix to outlet
#define sendLoudspeakerMatrices(x,list_length, at) \
                    outlet_anything(x->x_outlet0, gensym("loudspeaker-matrices"), (short)list_length, at);
#endif


/* A struct for a loudspeaker instance */
typedef struct
{                    // distance value is 1.0 == unit vectors
    float x;  // cartesian coordinates
    float y;
    float z;
    float azi;  // polar coordinates
    float ele;
    int   channel_nbr;  // which speaker channel number
}            t_ls;

/* A struct for all loudspeaker sets */
typedef struct t_ls_set
{
    int             ls_nos[3];  // channel numbers
    float           inv_mx[9]; // inverse 3x3 or 2x2 matrix
    struct t_ls_set *next;  // next set (triplet or pair)
}            t_ls_set;

#ifdef VBAP_OBJECT
typedef struct vbap                /* This defines the object as an entity made up of other things */
{
    t_object x_ob;
    long     x_azi;    // panning direction azimuth
    long     x_ele;        // panning direction elevation
    void     *x_outlet0;                /* outlet creation - inlets are automatic */
    void     *x_outlet1;
    void     *x_outlet2;
    void     *x_outlet3;
    void     *x_outlet4;
    float    x_set_inv_matx[MAX_LS_SETS][9];  // inverse matrice for each loudspeaker set
    float    x_set_matx[MAX_LS_SETS][9];      // matrice for each loudspeaker set
    long     x_lsset[MAX_LS_SETS][3];          // channel numbers of loudspeakers in each LS set
    long     x_lsset_available;                // have loudspeaker sets been defined with define_loudspeakers
    long     x_lsset_amount;                                   // amount of loudspeaker sets
    long     x_ls_amount;                      // amount of loudspeakers
    long     x_dimension;                      // 2 or 3
    long     x_spread;                         // speading amount of virtual source (0-100)
    double   x_gain;                         // general gain control (0-2)
    float    x_spread_base[3];                // used to create uniform spreading

    // define_loudspeaker data
    long     x_ls_read;                            // 1 if loudspeaker directions have been read
    long     x_triplets_specified;  // 1 if loudspeaker triplets have been chosen
    t_ls     x_ls[MAX_LS_AMOUNT];   // loudspeakers
    t_ls_set *x_ls_set;                    // loudspeaker sets
    long     x_def_ls_amount;                // number of loudspeakers
    long     x_def_ls_dimension;        // 2 (horizontal arrays) or 3 (3d setups)
}            t_vbap;

// define loudspeaker data type...
typedef t_vbap t_def_ls;
#else
/* define_loudspeakers maxmsp object */
typedef struct
{
    t_object x_ob;				/* gotta say this... it creates a reference to your object */
    long x_ls_read;	 			// 1 if loudspeaker directions have been read
    long x_triplets_specified;  // 1 if loudspeaker triplets have been chosen
    t_ls x_ls[MAX_LS_AMOUNT];   // loudspeakers
    t_ls_set *x_ls_set;			// loudspeaker sets
    void *x_outlet0;			/* outlet creation - inlets are automatic */
    long x_def_ls_amount;			// number of loudspeakers
    long x_def_ls_dimension;		    // 2 (horizontal arrays) or 3 (3d setups)
} t_def_ls;
#endif

/** Enable/Disable traces */
static bool _enable_trace = false;
void traces(t_def_ls *x, long n)
{
    _enable_trace = n ? true : false;
}


#define maxmsp_addfloat(m) class_addmethod(local_c, (method)m, "float", A_LONG, 0)
#define maxmsp_addint(m)   class_addmethod(local_c, (method)m, "int",   A_LONG, 0)
#define maxmsp_addlist(m)  class_addmethod(local_c, (method)m, "list",   A_GIMME, 0)
#define maxmsp_addbang(m)  class_addmethod(local_c, (method)m, "bang",  0)

#define maxmsp_addftx(m, index) class_addmethod(local_c, (method)m, "ft"#index, A_FLOAT, 0)
#define maxmsp_addinx(m, index) class_addmethod(local_c, (method)m, "in"#index, A_LONG, 0)

#define maxmsp_addmess(m, n, ...) class_addmethod(local_c, (method)m,n,__VA_ARGS__)
#define maxmsp_newobject(a)     object_alloc((t_class*)a)
#define maxmsp_class_register() class_register(CLASS_BOX, local_c);

#define maxmsp_create_class(n, cl, mnew, mfree, typesize, ...) \
t_class *local_c = class_new(n, (method)mnew, (method)mfree, (short)typesize, __VA_ARGS__); \
cl = local_c;

#define maxmsp_class_obexoffset_set(clazz, ztruct, field) class_obexoffset_set(local_c, calcoffset(ztruct, field))
#define maxmsp_CLASS_ATTR_ATOM_VARSIZE(cl, van, i, type, vals, valsc, valcsmax) CLASS_ATTR_ATOM_VARSIZE(local_c, van, i, type, vals,valsc,valcsmax)

#define maxmsp_dsp_initclass() class_dspinit(local_c)

#ifdef WIN32
int main();
#define maxmsp_main() int main(void)
#else
int main() __attribute__((visibility("default")));
#define maxmsp_main() __attribute__((visibility("default"))) int main(void)
#endif

#endif
