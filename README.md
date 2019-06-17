# xwolf

Ray casting with motion, texture and light. Navigate a Minecraft-y maze
using your arrow keys (ESC to quit).

### config

includes/wolf.h
* `WIN_WIDTH`, `WIN_HEIGHT`: window dimensions
* `VIEW_DIST`: draw distance; determines horizon and fadeout
* `TEX_MAP_SIZE`: hard cap on number of textures to load
* `HI_RES`: 0 for off, nonzero for on

src/util.c
* `map`, `himap`: named XPM images

### assets

textures/
* XPM format
* images must be square; rectangular images do get garbled pretty cool though
* transparency not supported; renders as black

maps/
* rectangular array of space-separated uint values representing cubes:
* 0 = walkable, empty; N > 0 = solid, texture N
* a map must have at least one zero value for a player; top-left-most is chosen
* a map must be completely bounded by nonzero values along its edges

### fast demo
`make do && ./wolf3d maps/good.map`
