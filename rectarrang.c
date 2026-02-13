/* An upper left triangular set of boxes on a png image
 * looks like a preparation for Pair-Wise analyses */
#include <cairo/cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define CW 800 // canvas width
#define CH 600 // canvas height

// Subject to the following MARs (margins) we have a "drawable".
#define TMAR 50
#define BMAR 10
#define LMAR 10
#define RMAR 10

typedef struct /* pos_t */
{
    float x, y;
} pos_t;

int main (int argc, char *argv[])
{
	if(argc!=3) {
		printf("Usage: 2 integer args: 1) number of horizontal rectangles (x-dir) 2) number of vertical rectangles (y-dir)\n");
		exit(EXIT_FAILURE);
	}

    int vbarnums=atoi(argv[1]); // yes, it is the number of vertical bars.
    int hbarnums=atoi(argv[2]); 
    int i, j;

    // we start with the canvas. Set up surface, set bg etc.
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, CW, CH);
    cairo_t *cr = cairo_create (surface);
    cairo_rectangle (cr, 0, 0, CW, CH);
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    // now the drawable
    pos_t dtl;
    dtl.x=LMAR; // dtl: drawable top left
    dtl.y=TMAR;
    float dw=CW-LMAR-RMAR; // drawable width extent
    float dh=CH-TMAR-BMAR; // drawable height extent
                           //
    /* vertical divider how ar ewe going to section off the screen vertically */
    float vbarsz=(float)dw/vbarnums; // size of steps in x direction
    float hbarsz=(float)dh/hbarnums; // y direction.
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

    // rest of oclumns.
    for(i=1;i<hbarnums;i++)
        for(j=1;j<vbarnums;j++) {
            lb[i*vbarnums+j].x= lb[i*vbarnums+j-1].x + vbarsz;
            lb[i*vbarnums+j].y= lb[i*vbarnums+j-1].y;
            // printf("resti=%i\n", i*vbarnums+j);
        }
        

    for(i=0;i<hbarnums;i++) {
        for(j=0;j<vbarnums;j++)
            printf("%i: (%4.4f %4.4f) ", i*vbarnums+j, lb[i*vbarnums+j].x, lb[i*vbarnums+j].y);
        printf("\n");
    } 
    int im; // mod i, for changing colours.
    cairo_set_source_rgba(cr, 0.65, 0.8, 0.45, 0.6);
    for(i=0;i<hbarnums;i++) {
        for(j=0;j<vbarnums;j++) {
            im = (i*vbarnums+j)%3;
            switch(im) {
                case 0:
                    cairo_set_source_rgb(cr, 0.65, 0.8, 0.45); break;
                case 1:
                    cairo_set_source_rgb(cr, 0.15, 0.45, 0.6); break;
                case 2:
                    cairo_set_source_rgb(cr, 0.35, 0.2, 0.6);
            }
            cairo_rectangle(cr, lb[i*vbarnums+j].x, lb[i*vbarnums+j].y, vbarsz, hbarsz);
            cairo_fill(cr);
            cairo_set_source_rgb(cr, 1., 0.2, 0.2);
            // tiny circle in mid point
            cairo_arc(cr, lb[i*vbarnums+j].x + vbarsz/2., lb[i*vbarnums+j].y + hbarsz/2., 4, 0, 2*M_PI);
            cairo_fill(cr);
        }
    }

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "rectarrang.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    free(lb);

    return 0;
}
