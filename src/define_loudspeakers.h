/* define_loudspeakers.c 1.00b1----> x-max4.2

written by Ville Pulkki 1999-2003
Helsinki University of Technology 
and 
Unversity of California at Berkeley

See copyright in file with name COPYRIGHT  */

#include "vbap.h"

t_class *def_ls_class;                /* so max can identify your object */
void def_ls_bang(t_def_ls *x);
void def_ls_int(t_def_ls *x, long n);
void def_ls_read_directions(t_def_ls *x, t_symbol *s, int ac, t_atom *av);
void def_ls_read_triplets(t_def_ls *x, t_symbol *s, int ac, t_atom *av);
void *def_ls_new(t_symbol *s, int ac, t_atom *av);
void def_ls(float g[3], long ls[3], t_def_ls *x);
void ls_angles_to_cart(t_ls *ls);
void choose_ls_triplets(t_def_ls *x);
int any_ls_inside_triplet(int a, int b, int c, t_ls lss[MAX_LS_AMOUNT], int ls_amount);
void add_ldsp_triplet(int i, int j, int k, t_def_ls *x);
float vec_angle(t_ls v1, t_ls v2);
float vec_length(t_ls v1);
float vec_prod(t_ls v1, t_ls v2);
float vec_prod(t_ls v1, t_ls v2);
float vol_p_side_lgth(int i, int j, int k, t_ls lss[MAX_LS_AMOUNT]);
void ls_cross_prod(t_ls v1, t_ls v2, t_ls *res);
int lines_intersect(int i, int j, int k, int l, t_ls lss[MAX_LS_AMOUNT]);
void calculate_3x3_matrixes(t_def_ls *x);
void choose_ls_tuplets(t_def_ls *x);
int calc_2D_inv_tmatrix(float azi1, float azi2, float inv_mat[4], float mat[4]);
void sort_2D_lss(t_ls lss[MAX_LS_AMOUNT], int sorted_lss[MAX_LS_AMOUNT], int ls_amount);
void initContent_ls_directions(t_def_ls *x, int ac, t_atom *av);

void vbap_def_ls(t_def_ls *x, t_symbol *s, int ac, t_atom *av);
