# xwolf

Ray tracing engine with lighting. Navigate through a Minecraft-textured maze
using your arrow keys, and ESC to quit.

### config

includes/wolf.h
* \#define *WIN_WIDTH*, *WIN_HEIGHT*: window dimensions
* \#define *VIEW_DIST*: draw distance; determines horizon and fadeout
* \#define *TEX_MAP_SIZE*: hard cap on number of textures to load
* \#define *HI_RES*: 0 for off, nonzero for on

src/util.c
* static const char** *map*, *himap*: named XPM images

textures/
* XPM format
* images must be square; rectangular images do get garbled pretty cool though
* transparency not supported; renders as black

maps/
* rectangular array of space-separated uint values
* 0 = nothing; 1-N = solid, texture 1-N called to load
* a map must have at least one zero value for a player; top-left-most is chosen
* a map must be completely bounded by nonzero values along its edges

### make
`make do && ./wolf3d maps/good.map`
