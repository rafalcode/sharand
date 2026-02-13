# "sharand"
stands for "Shapes with Randomness"
leanign on libcairo, idea is to generate something looking 
like boulders which will serve for (say) a game of asteroids.

# hunch
I decided that introducing some randomness in the drawing of a hexagon
might be a useful first approximation.

I also wanted to introduce the latest and greatest random number geenrator, xorshiro.
Well, no, maybe later.

# Programs

# polyg0.c
Will make a polygon with 5 up to 10 sides. Follows an intuitive style of drawing whereby one side
is set to be the horizontal base nad drawing proceeds anticlockwise.
