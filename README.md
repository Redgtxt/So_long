# so_long

![42 School](https://img.shields.io/badge/42-Lisboa-000000?style=flat-square&logo=42&logoColor=white)
![Milestone](https://img.shields.io/badge/milestone-2-informational?style=flat-square)
![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Graphics](https://img.shields.io/badge/graphics-MiniLibX%20%7C%20X11-8A2BE2?style=flat-square)
![Norm](https://img.shields.io/badge/norminette-passing-success?style=flat-square)
![Flags](https://img.shields.io/badge/flags-Wall%20%7C%20Wextra%20%7C%20Werror-critical?style=flat-square)

> A small top-down 2D game in C: collect everything, then reach the exit — on a map the program refuses to load unless it can prove the level is winnable.

The player walks around a tile map, picks up every collectible, and leaves through the exit, which only opens once the last item is taken. The game reads its level from a `.ber` text file, draws it with MiniLibX — 42's thin layer over X11, which gives a window, images and keyboard events and nothing else — and counts every move.

The game loop is the easy part. Most of the code is in the loader, because the map comes from a file anyone can edit. Before a window ever opens, the map has to be rectangular, closed by walls, made only of known characters, with exactly one start and one exit, at least one collectible — and every collectible and the exit must actually be reachable from the start.

---

## Table of contents

- [Usage](#usage)
- [Building](#building)
- [Map format](#map-format)
- [Architecture](#architecture)
- [Proving the map is winnable](#proving-the-map-is-winnable)
- [Design notes](#design-notes)
- [Edge cases handled](#edge-cases-handled)
- [What I would change now](#what-i-would-change-now)
- [What I took away from it](#what-i-took-away-from-it)

---

## Usage

```bash
./so_long map.ber
```

| Key | Action |
| --- | --- |
| `W` `A` `S` `D` | Move up, left, down, right |
| `ESC` | Quit |
| Window close button | Quit |

Each move is printed to the terminal and shown in the top-left corner of the window. Walking into a wall does nothing and does not count as a move.

## Building

MiniLibX is bundled in `mlx-linux/` and built by the Makefile. It needs the X11 development headers:

```bash
sudo apt install libx11-dev libxext-dev zlib1g-dev   # Debian / Ubuntu
```

```bash
make        # builds libft, MiniLibX, then ./so_long
make clean  # removes the object files
make fclean # also removes the binary
make re     # fclean + all
```

Compiled with `-Wall -Wextra -Werror`. `libft` is my own C library from the first project, including `get_next_line`, which reads the map.

## Map format

A `.ber` file is a grid of characters, one row per line:

| Character | Tile |
| --- | --- |
| `1` | Wall |
| `0` | Floor |
| `P` | Player start |
| `C` | Collectible |
| `E` | Exit |

```
11111111111111111111
1P000000000000000001
100000000000000000E1
10000000000000000001
10111111111111111111
100C0000000000000001
11111111111111111111
```

The exit is in reach from the first move, but it stays closed until the player goes down through the gap in the inner wall, picks up the collectible and comes back.

## Architecture

```
main
 ├─ check_name          the file must end in .ber
 ├─ read_map            pass 1: count rows, measure the first row
 │   └─ build_matrix    pass 2: one get_next_line string per row
 │       ├─ check_walls          first/last row and column are all '1'
 │       ├─ check_rectangular    every row has the same width
 │       └─ check_letters
 │           ├─ find_player          locate P
 │           ├─ check_conditions     1 P, 1 E, ≥ 1 C, no other characters
 │           └─ check_path_player_to flood fill on a copy of the map
 ├─ create_window       refuse maps larger than the screen
 ├─ store_sprites       load the 32×32 XPM tiles once
 ├─ draw_map
 └─ mlx_loop            key_hook ─▶ move_player ─▶ redraw + move counter
```

All state lives in one `t_data` struct passed to every function and to the MiniLibX hooks: the MiniLibX handles, the map (`t_map`), the player's position, collectible count and moves (`t_player`), and the loaded images (`t_imgs`).

The map is a `char **` — the same array the loader validated is the game state. A move rewrites two cells (the old position becomes `0`, the new one `P`) and redraws the grid, choosing the open or closed exit sprite from how many collectibles are left.

## Proving the map is winnable

`check_path_player_to` copies the map and runs a recursive flood fill from the player's start:

```c
void	flood_fill(t_flood_fill *fill, int x, int y)
{
	if (x < 0 || x >= fill->columns || y < 0 || y >= fill->rows
		|| fill->matrix_copy[y][x] == '1')
		return ;
	if (fill->matrix_copy[y][x] == 'E')
	{
		fill->found_exit = 1;
		return ;            /* the exit is reached, but not walked through */
	}
	if (fill->matrix_copy[y][x] == 'V')
		return ;            /* already visited */
	if (fill->matrix_copy[y][x] == 'C')
		fill->collectibles--;
	fill->matrix_copy[y][x] = 'V';
	flood_fill(fill, x - 1, y);
	flood_fill(fill, x + 1, y);
	flood_fill(fill, x, y - 1);
	flood_fill(fill, x, y + 1);
}
```

The map is accepted only if the fill reaches the exit **and** the collectible counter reaches zero.

The fill treats the exit as a dead end on purpose. In the game, stepping onto a closed exit is refused, and stepping onto an open one ends the level. Either way the player never walks *through* it. A collectible that can only be reached by crossing the exit cell is therefore unreachable, and the flood fill rejects the map instead of reporting it as winnable.

## Design notes

- **Validate on a copy.** The flood fill marks cells as visited by overwriting them with `V`, so it runs on a duplicate of the map. The copy is freed on every path out of the function, including the error ones.

- **Read the file twice instead of growing an array.** The first pass counts the rows, so the second pass can allocate the row array exactly once. That avoids a hand-written `realloc`, which the subject does not allow.

- **One way to quit.** `ESC` and the window's close button both call `close_window`, which only ends `mlx_loop`. The cleanup — every image, the window, the display connection and the map — happens once, after the loop returns, in `main`.

- **Sprites load once.** The six XPM images are loaded before the first frame and reused for every redraw, rather than read from disk on each move.

- **The move counter only counts real moves.** `move_player` returns early on walls and on the closed exit, so pressing into a wall leaves the counter unchanged.

## Edge cases handled

| Case | Behaviour |
| --- | --- |
| Wrong number of arguments | `Error`, exit 1 |
| File not ending in `.ber` | `Error` |
| Missing or empty file | `Error` |
| Gap in the outer wall | `Error` |
| Rows of different lengths, including a trailing empty line | `Error` |
| Zero or several `P`, zero or several `E`, zero `C` | `Error` |
| Any character outside `0 1 C E P` | `Error` |
| A collectible or the exit cut off from the start | `Error` — caught by the flood fill |
| Map larger than the screen | `Error`, before the window opens |
| Walking into the exit before collecting everything | Blocked, no move counted |

## What I would change now

- **Say which rule failed.** Every invalid map prints the same `Error` to standard output. It should go to standard error, followed by the reason — "map is not rectangular", "no path to the exit".
- **Check the shape before the walls.** `check_walls` runs first and reads every row at the first row's width, so a shorter row is read past its end before `check_rectangular` rejects it. The map is still refused, but only after an out-of-bounds read.
- **The screen-size check has its arguments swapped.** MiniLibX's `mlx_get_screen_size(mlx, &width, &height)` is called with height first, so a wide map is compared against the screen's height. Some maps that would fit are rejected.
- **The `.ber` check looks at the first dot in the path.** `levels/one.ber` works, but `./one.ber` is rejected, because the first `.` is the one in `./`. Checking the last four characters is the correct test.
- **Redraw only what changed.** Each move redraws the whole grid. Only two tiles, the exit and the counter can change, so a large map does far more work than it needs to.
- **An iterative flood fill.** The recursive version is the clearest, but its depth grows with the number of floor tiles, so a very large open map could overflow the stack.

## What I took away from it

- Event-driven programs: after `mlx_loop` starts, nothing happens unless a hook fires, so every piece of state the hooks need has to live in one struct passed to them.
- Treating input as hostile. Most of the code is validation, because a map file is user input, and every rule in the subject turned into a check with its own error path.
- The flood fill as a real tool, not an exercise. It answers "is every item reachable?" in a few lines, and choosing to stop at the exit cell made it match the game's rules instead of a generic connectivity test.
- Owning cleanup across a library boundary: MiniLibX hands out images, a window and a display connection, and each has its own destroy call, in the right order.

---

**Author** — Hugo Pinto ([`hguerrei`](https://profile.intra.42.fr/users/hguerrei) · [@Redgtxt](https://github.com/Redgtxt))
