/*  finally managed to make a circular path, without points. */
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <cairo/cairo.h>

#define PTS 16
int main (int argc, char *argv[])
{
    cairo_surface_t *surface;
    cairo_t *cr;

    int  i, w=480, h=480;
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, w, h);
    cr = cairo_create (surface);
    /* Examples are in 1.0 x 1.0 coordinate space */
//     cairo_scale (cr, w, h);
    cairo_rectangle (cr, 0, 0, w, h); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    /* Drawing code goes here */
    cairo_set_line_width (cr, 2);
    cairo_set_source_rgba(cr, 0.9, 0.7, 0.5, 0.2);
    float *xp, *yp, x0=w/2, y0=h/2;
    xp=calloc(PTS,sizeof(float));
    yp=calloc(PTS,sizeof(float));
    int sz=100;

    for(i=0; i<PTS; ++i) {//hexagon
        xp[i]=x0 + sz*cos(i*2*M_PI/PTS);
        yp[i]=y0 + sz*sin(i*2*M_PI/PTS);
    }


    for(i=0; i<PTS; ++i) {//hexagon
        cairo_move_to (cr, xp[i], yp[i]);
        cairo_line_to (cr, x0, x0);
    }
    // cairo_line_to (cr, 0.5, 0.375);
    // cairo_rel_line_to (cr, 0.25, -0.125);
    // cairo_arc (cr, 0.5, 0.5, 0.25 * sqrt(2), -0.25 * M_PI, 0.25 * M_PI);
    // cairo_rel_curve_to (cr, -0.25, -0.125, -0.25, 0.125, -0.5, 0);
    cairo_close_path (cr);

    cairo_stroke (cr);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "linestar.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    free(xp);
    free(yp);

    return 0;
}

