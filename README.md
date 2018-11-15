# xwolf

Ray tracing with lighting. Navigate through a textured maze with your arrow keys (& ESC).

`make do`. Manually edit the #define HI_RES in includes/wolf.h to enable.

Make your own maps!
- rectangular array of space-separated uint values
- 0 = nothing; 1-N = solid, texture 1-N called to load
- a map must have empty space within for a player
- a map must be bounded by nonempty space along its edges
