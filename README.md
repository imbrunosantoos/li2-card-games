# LI2 Card Games Suite

A collection of terminal-based card games developed in **C** for the **Software Laboratory II (LI2)** course at **University of Minho**.

> **Status: Complete ✅** — All three phases are implemented, tested and working. The final version plays four solitaires (Golf, Simple Simon, Klondike and FreeCell) through a single generic engine, with undo and save/load.

## Projects Included

- **Phase 1: Golf** — A solitaire where cards are moved to the discard pile to clear the tableau.
- **Phase 2: Simple Simon** — A solitaire focused on building and moving descending same-suit sequences between columns.
- **Phase 3: Generic Solitaire Engine** — A data-driven engine that reads every solitaire from text files in the `paciencias/` folder, written in a small **DSL** (one game per file). It ships with **Golf**, **Simple Simon**, **Klondike** and **FreeCell**, and supports:
  - validation of moves from the rules described in each file (`MOV`);
  - **automatic moves** (`AUTO`, e.g. completed K..A sequences going to a foundation);
  - **win detection** (`WIN`);
  - **undo** (step back through the move history);
  - **save / load** of a game state.

## Technologies & Tools

- **Language:** C
- **Compiler:** GCC
- **Environment:** macOS / Linux (UMinho Lambda Server)
- **Testing:** CUnit · AddressSanitizer · pmccabe
- **Version Control:** Git & GitHub

## Project Requirements (all met)

- No global variables.
- No `goto`, `break` or `continue`.
- Every function within **≤ 10** cyclomatic complexity and **≤ 15** statements (checked with `pmccabe`).
- Clear separation between **logic** and **interface**.
- Logic functions covered by **CUnit** tests.
- All functions documented.

## Project Structure

- `main.c`: Entry point — lists the solitaires found in `paciencias/` and launches the chosen one.
- `paciencias/`: Solitaire definitions in the DSL (`golf`, `simon`, `klondike`, `freecell`).
- `phase3/`: The generic engine — `logic/` (parser, engine, move rules, save/load, game loop) and `ui/` (menu, board display).
- `phase1_golf/`, `phase2_simon/`: Standalone source code (logic and UI) from the earlier phases.
- `menu_principal/`: Main menu system used by the earlier phases.
- `common/`: Shared logic (cards, decks, piles) used across all games.
- `tests/`: Automated test suite using CUnit.

## How to Build and Run

```bash
cd proj
make
./cardgames
```
To compile and execute the CUnit logic tests:

```bash
make test
```
To run pmccabe and ensure all functions meet the project requirements (Max 10 cyclomatic complexity, Max 15 instructions):

```bash
make pmccabe
```
To remove all compiled executables and clean the workspace:

```bash
make clean
```

## Authors

**[Bruno Santos](github.com/imbrunosantoos)**

**[Goncalo Cipreste](github.com/goncalocipreste-rgb)**
