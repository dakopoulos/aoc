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
