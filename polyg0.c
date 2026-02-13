/* Exercises in slope
 *
 * A major mistake you can make is to send a line to the rad*sin(angle) just like that.
 * NO, it must be done relative to the point you moved to.
*/
#include <cairo/cairo.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define IW 800. // image/canvas width
#define IH 600. // height

void hx(cairo_surface_t *surface, cairo_t *cr, float norad, float x0, float y0, int nsides)
{
    cairo_set_source_rgba(cr, 0.105, 0.4, 0., 0.3);
    cairo_arc(cr, x0, y0, 3, 0, 2*M_PI);
    cairo_fill(cr);

    const float pid1=2*M_PI/nsides; // pi divided once
    const float pid2=pid1/2.; // divided twice
    const float purad=norad * 2 * sin(pid2); // putative radius
    printf("purad=%4.4f\n", purad); 

    cairo_set_source_rgba(cr, 0.65, 0.8, 0.45, 0.6);
    cairo_move_to (cr, x0, y0);
    // intuition: flip the 30 (negativize sin() and rotate -100 (negativize cos() and switch cos and sin between x and y).
    // however in cairo convention, its +y is our -y, so reverse the y component (i.e. cos - now in y position - is not negativized.
    cairo_rel_move_to(cr, -purad*sin(pid2), purad*cos(pid2));

    // now we follow intuition, drawing straight line first, for Cairo we must negate the y.
    for(int i=0;i<nsides-1;++i)
        cairo_rel_line_to(cr, purad*cos(i*pid1), -purad*sin(i*pid1));
    cairo_close_path(cr);
    cairo_stroke(cr);
}

int main (int argc, char *argv[])
{
	if(argc!=2) {
		printf("Usage: 1 arg, integer. Furthermore only 5 to 10.\n");
		exit(EXIT_FAILURE);
	}

    int nsides=atoi(argv[1]);
    if((nsides<5) | (nsides>10)) {
        printf("Only 5 to 10 sides allowed.\n");
		exit(EXIT_FAILURE);
    }

    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IW, IH);

    /*  then a cairo_type is created from this surface */
    cairo_t *cr = cairo_create (surface);
    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, IW, IH); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.9); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    float x0=IW/2.,  y0=IH/2.;
    float norad=100.; // notional radius
    hx(surface, cr, norad, x0, y0, nsides);

    cairo_surface_write_to_png (surface, "polyg0.png");
    cairo_surface_destroy (surface);
    return 0;
}
