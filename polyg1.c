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

// Subject to the following MARs (margins) we have a "drawable".
#define TMAR 50
#define BMAR 10
#define LMAR 10
#define RMAR 10

typedef struct /* pos_t */
{
    float x, y;
} pos_t;

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
    cairo_rel_move_to(cr, -norad*sin(pid2), norad*cos(pid2)); // because previously I put purad here, all except hexagons were not centering properly.

    // now we follow intuition, drawing straight line first, for Cairo we must negate the y.
    for(int i=0;i<nsides-1;++i)
        cairo_rel_line_to(cr, purad*cos(i*pid1), -purad*sin(i*pid1));
    cairo_close_path(cr);
    cairo_stroke(cr);
}

pos_t *posp(int vbarnums, int hbarnums, pos_t dtl, float vbarsz, float hbarsz)
{
    int i, j;

    /* vertical divider how ar ewe going to section off the screen vertically */
    int totpoints = hbarnums*vbarnums;
    printf("vbarsz=%4.4f h=%4.4f tot=%i\n", vbarsz, hbarsz, totpoints);
    pos_t *lb=calloc(totpoints, sizeof(pos_t)); /* ori: origin, lb, last bar, */

    // first point, top left
    lb[0].x= dtl.x;
    lb[0].y = dtl.y;
    // first row, only x changes
    for(i=1;i<vbarnums;i++) {
        lb[i].x= lb[i-1].x + vbarsz;
        lb[i].y= lb[i-1].y;
    }
    // first column
    for(i=1;i<hbarnums;i++) {
        lb[i*vbarnums].x= lb[(i-1)*vbarnums].x;
        lb[i*vbarnums].y= lb[(i-1)*vbarnums].y + hbarsz;
    }

    // rest of columns.
    for(i=1;i<hbarnums;i++)
        for(j=1;j<vbarnums;j++) {
            lb[i*vbarnums+j].x= lb[i*vbarnums+j-1].x + vbarsz;
            lb[i*vbarnums+j].y= lb[i*vbarnums+j-1].y;
        }
    for(i=0;i<hbarnums;i++) {
        for(j=0;j<vbarnums;j++)
            printf("%i: (%4.4f %4.4f) ", i*vbarnums+j, lb[i*vbarnums+j].x, lb[i*vbarnums+j].y);
        printf("\n");
    } 

    return lb;
}

int main (int argc, char *argv[])
{
	if(argc!=3) {
		printf("Usage: 2 integer args: 1) number of horizontal rectangles (x-dir) 2) number of vertical rectangles (y-dir)\n");
		exit(EXIT_FAILURE);
	}
    int vbarnums=atoi(argv[1]); // yes, it is the number of vertical bars.
    int hbarnums=atoi(argv[2]); 
    int totpoints = hbarnums*vbarnums;
    int nsides=6;
    int i, j;

    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IW, IH);

    /*  then a cairo_type is created from this surface */
    cairo_t *cr = cairo_create (surface);
    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, IW, IH); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.9); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    // get ready to call the lb creator
    pos_t dtl;
    dtl.x=LMAR; // dtl: drawable top left
    dtl.y=TMAR;
    float dw=IW-LMAR-RMAR; // drawable width extent
    float dh=IH-TMAR-BMAR; // drawable height extent
    float vbarsz=(float)dw/vbarnums; // size of steps in x direction
    float hbarsz=(float)dh/hbarnums; // y direction.
    // call it:
    pos_t *lb=posp(vbarnums, hbarnums, dtl, vbarsz, hbarsz);

    // draw the rectangles:
    int im;
    cairo_set_source_rgba(cr, 0.65, 0.8, 0.45, 0.6);
    for(i=0;i<hbarnums;i++) {
        for(j=0;j<vbarnums;j++) {
            im = (i*vbarnums+j)%3;
            switch(im) {
                case 0:
                    cairo_set_source_rgb(cr, 0.65, 0.4, 0.25); break;
                case 1:
                    cairo_set_source_rgb(cr, 0.15, 0.25, 0.6); break;
                case 2:
                    cairo_set_source_rgb(cr, 0.35, 0.2, 0.8);
            }
            cairo_rectangle(cr, lb[i*vbarnums+j].x, lb[i*vbarnums+j].y, vbarsz, hbarsz);
            cairo_fill(cr);
            cairo_set_source_rgb(cr, 1., 0.2, 0.2);
            // tiny circle in mid point
            cairo_arc(cr, lb[i*vbarnums+j].x + vbarsz/2., lb[i*vbarnums+j].y + hbarsz/2., 4, 0, 2*M_PI);
            cairo_fill(cr);
        }
    }

    // draw the polygons
    const float norad=40.; // notional radius, hardcoded
    for(i=0;i<hbarnums;i++) {
        for(j=0;j<vbarnums;j++) {
            nsides=5 + i*vbarnums+j;
            hx(surface, cr, norad, lb[i*vbarnums+j].x +vbarsz/2., lb[i*vbarnums+j].y + hbarsz/2., nsides);
        }
    }

    // closing
    free(lb);
    cairo_surface_write_to_png (surface, "polyg1.png");
    cairo_surface_destroy (surface);
    return 0;
}
