# LI2 Card Games Suite

A collection of terminal-based card games developed in **C** for the **Software Laboratory II (LI2)** course at **University of Minho**.

## Projects Included

- **Phase 1: Golf** - A strategic card game where players try to earn the lowest number of points over nine holes.
- **Phase 2: Simple Simon** - A solitaire card game that requires careful planning and sequence building.
- **Phase 3: TBD** - Upcoming project phase.

## Technologies & Tools

- **Language:** C
- **Compiler:** GCC
- **Environment:** macOS / Linux (UMinho Lambda Server)
- **Version Control:** Git & GitHub

## Project Structure

- `main.c`: Main entry point for the integrated application.
- `menu_principal/`: Main menu system to select and launch the different games.
- `phase1_golf/`: Source code (logic and UI) specific to the Golf game.
- `phase2_simon/`: Source code (logic and UI) specific to the Simple Simon game.
- `common/`: Shared logic (cards, decks, piles) and helper functions used across all games.
- `tests/`: Automated test suite using CUnit.

## How to Build and Run

To compile and run the games, navigate to the specific phase folder:

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
