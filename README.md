# Advent of Code

## Data

`data` dir contains various data that can be used for testing the produced
executables. See more in later paragraphs.

## Day 18

`snailfish` directory contains code for day 18 problem.

Two executables are produced to test and solve the snailfish problem.

* `test-add`

  * Tests addition by reading a file with snailfish numbers (one per line,
    without whitespace). All but the  last numbers are added and compared
    to the expected results which is the last number in the file. It also
    calculates and prints the magnituted of the sum.
  * Usage: `test-add <filename>` e.g. `test-add <path>/data/snailfish.add.3.txt`
    or `test-add <path>/data/snailfish.puzzle.txt` which is "day 18"'s puzzle
    data.

* `test-magn`

  * Tests calculations of a snailfish's number magnitude
  * Usage: `test-magn <filename>` where `<filename>` containts snailfish
    number and expected magnitudes (each on separate lines)

## Day 22

`reactor` initialization and boot sequence.

Executable is produced with the following usage:

`init-and-reboot <init-sequence-file> [<boot-sequence-file>]`

Data are in `[path]/data/reactor*` e.g. `reactor-puzzle-init.txt` and
`reactor-puzzle-boot.txt`.

**Rationale**:

* Reactor stores all the active cores in an `unordered_set<Point>` with
  a custom hash function and `Point` being a 3D point with int coordinates.
* Upon applying a boot or init step, cores are enabled if not already in
  the active cores set or removed from the active cores if already there.

