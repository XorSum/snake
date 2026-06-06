# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build & Run

This is a single-file C project with no build system. Compile and run directly:

```bash
gcc main.c -o snake && ./snake
```

On macOS, use `clang` (the default `cc`):

```bash
cc main.c -o snake && ./snake
```

## Architecture

Single `main.c` (~275 lines) — a classic terminal Snake game. No external dependencies beyond the C standard library (`stdio.h`, `time.h`, `stdlib.h`).

**Core data structure:** A singly linked list representing the snake body. Each node holds `(x, y)` coordinates on a **16×16 grid** with edge-wrapping (going off one side teleports to the opposite side).

**Key functions and their roles:**

| Function | Purpose |
|----------|---------|
| `createsnake()` | Allocates and initializes a 4-segment snake headed right at row 8 |
| `movehead(ch)` | Advances the snake one step in direction `ch` (w/a/s/d), with reversal protection |
| `cuttail()` | Removes the tail node after a non-food move |
| `biteself()` | Returns 1 if head overlaps any body segment → game over |
| `putfood(food)` | Randomly places food on an unoccupied cell |
| `textfood()` | Recursive helper that checks if a given (x, y) is occupied |
| `draw(len, step, flag)` | Renders the 16×16 grid in ASCII: `H`=head, `*`=body, `F`=food. Displays length and step count. `flag=1` shows an input prompt on invalid keys |
| `snake()` | Main game loop: reads input, moves, checks food/bite, redraws |
| `freesnake()` | Frees all nodes including food |

**Game flow:** `main()` → `snake()` → infinite loop reading stdin via `scanf`, one char at a time. Only `w/a/s/d` and newline are accepted as input; anything else triggers a re-draw with a prompt. Snake cannot reverse direction (e.g., going right, pressing `a` is ignored).
