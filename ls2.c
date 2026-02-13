/* hslightly irregular polygonal shapes */
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <cairo/cairo.h>

int main (int argc, char *argv[])
{
	if(argc!=2) {
		printf("Error. Pls supply argument (integer: number of vertices).\n");
		exit(EXIT_FAILURE);
	}
    int nvert=atoi(argv[1]);

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
    printf("centre=%2.2f,%2.2f\n", x0, y0); 

    // our points:
    float *xp=malloc(nvert*sizeof(float));
    float *yp=malloc(nvert*sizeof(float));
    int sz=100;

    const float baseradian=2*M_PI/nvert;
    printf("br=%4.4f\n", baseradian); 
    for(i=0; i<nvert; ++i) {
        xp[i]=x0 + sz*cos(i*baseradian);
        yp[i]=y0 + sz*sin(i*baseradian);
        printf("(%4.4f,%4.4f\n", cos(i*baseradian), sin(i*baseradian));
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
    cairo_surface_write_to_png (surface, "ls2.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    free(xp);
    free(yp);

    return 0;
}

