#include "ext.h"  				

typedef struct testobj				
{
	Object x_ob;				
} t_testobj;

void *testobj_class;				

void testobj_ft1(t_testobj *x, /*long*/double n) { post("ft1=%f",n); }
void testobj_ft2(t_testobj *x, /*long*/double n) { post("ft2=%f",n); }
void testobj_ft3(t_testobj *x, /*long*/double n) { post("ft3=%f",n); }
void testobj_ft4(t_testobj *x, double g) { post("ft4=%f",g); }

void testobj_list(t_testobj *x, Symbol *s, int ac, Atom *av)
{
	for( int i = 0 ; i<ac ; i++ )
	{
		post("av[%d].a_type=%d float=%lf long=%ld",i,av[i].a_type,av[i].a_w.w_float,av[i].a_w.w_long);
	}
}

void *testobj_new(long n,double f)
{
	t_testobj *x = (t_testobj *)newobject(testobj_class);

	floatin(x,4);	
	floatin(x,3);	
	floatin(x,2);					
	floatin(x,1);					

	post("n=%ld f=%lf",n,f);

	return(x);
}

void main(void)
{
	setup((t_messlist **)&testobj_class, (method)testobj_new, 0L, (short)sizeof(t_testobj), 0L, A_DEFLONG,A_DEFFLOAT,0); 

	addmess((method)testobj_list, "list", A_GIMME, 0);
	addftx((method)testobj_ft1, 1);
	addftx((method)testobj_ft2, 2);
	addftx((method)testobj_ft3, 3);

	addftx((method)testobj_ft4, 4);
}

void testobj_int(t_testobj *x, /*long*/double n) { post("int=%f",n); }
