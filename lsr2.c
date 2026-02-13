/* slightly irregular polygonal shapes */
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <cairo/cairo.h>

// By fiddling, with uniform distro, these two give rough decent shapes.
// a Gaussian would be less surprising.
#define ANGLE_FXSZ .02
#define LEN_FXSZ 50.

float *wigglefactor(int q, const float hoveraround, const float effectsize)
{
   float *a=malloc(q*sizeof(float));

   for(int i=0;i<q;++i) 
       a[i]= hoveraround + effectsize * (-.5 + (float)rand()/RAND_MAX);

   // printf("%i random numbershovering around 100 (effect size=%2.2f):\n", q, effectsize);
   // for(i=0;i<q;++i) 
   //      printf("%4.6f ", a[i]);
   // printf("\n");

   return(a);
}

int main (int argc, char *argv[])
{
	if(argc!=3) {
		printf("Error. Pls supply 2 arguments 1) integer: number of vertices 2) random seed.\n");
		exit(EXIT_FAILURE);
	}
    int nvert=atoi(argv[1]);
    srand(atoi(argv[2]));

    int  i, w=800, h=600;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, w, h);
    cairo_t *cr = cairo_create(surface);

    /* canvas background */
    cairo_rectangle (cr, 0, 0, w, h); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 1); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    /* Drawing code goes here */
    cairo_set_line_width (cr, 1);
    cairo_set_source_rgba(cr, 0.8, 0.2, 0.4, 0.5);

    // convenience, centrepoint:
    float x0=w/2., y0=h/2.;
    // printf("centre=%2.2f,%2.2f\n", x0, y0); 

    // our points:
    float *xp=malloc(nvert*sizeof(float));
    float *yp=malloc(nvert*sizeof(float));
    const float sz=100.;
    float *wfac=wigglefactor(nvert, sz, LEN_FXSZ);

    const float baseradian=2*M_PI/nvert;
    float *brw=wigglefactor(nvert, baseradian, ANGLE_FXSZ); // base radian wiggle
    for(i=0;i<nvert;++i) 
        printf("%4.4f ", brw[i]); 
    printf("\n"); 

    for(i=0; i<nvert; ++i) {
        xp[i]=x0 + wfac[i]*cos(i*brw[i]);
        yp[i]=y0 + wfac[i]*sin(i*brw[i]);
    }

    cairo_arc(cr, x0, y0, 10, -M_PI, M_PI);
    for(i=0; i<nvert; ++i) {
        cairo_move_to (cr, xp[i], yp[i]);
        cairo_line_to (cr, x0, y0);
    }
    // cairo_line_to (cr, 0.5, 0.375);
    // cairo_rel_line_to (cr, 0.25, -0.125);
    // cairo_arc (cr, 0.5, 0.5, 0.25 * sqrt(2), -0.25 * M_PI, 0.25 * M_PI);
    // cairo_rel_curve_to (cr, -0.25, -0.125, -0.25, 0.125, -0.5, 0);
    // cairo_close_path (cr);
    cairo_stroke (cr);

    cairo_set_line_width (cr, 2);
    cairo_set_source_rgba(cr, 0.2, 0.9, 0.3, 0.75);
    cairo_move_to (cr, xp[0], yp[0]);
    for(i=1; i<nvert; ++i) {
        cairo_line_to (cr, xp[i], yp[i]);
    }
    cairo_close_path (cr);
    cairo_stroke (cr);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "lsr2.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    free(xp);
    free(yp);
    free(wfac);
    free(brw);

    return 0;
}

