# xwolf

Ray tracing with lighting.
Navigate through a Minecraft-textured maze with your arrow keys and ESC.

### config
- **load_textures** explicitly names and orders texture files
- **TEX_MAP_SIZE** imposes an artificial limit, change if necessary
- **
- maps are rectangular array of space-separated uint values
- 0 = nothing; 1-N = solid texture N
- a map must be completely bounded by nonzero values
- a map must contain a nonzero value

### make
`make do` is quick and cleans up after itself
usage: `./wolf3d mapfile`
