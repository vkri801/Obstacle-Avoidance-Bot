/*! \file src.ino
    \brief The "main" source file. See extended description.

Basically, Arduino is kindof a PITA sometimes.

Issue #0: Naming things.

The name of the "sketch" file must be the same as the folder name. Yup. That's
just an Arduino *thing*.


Issue #1: Multiple programs and `.ino` files.

If you have multiple `.ino` files in the source directory of an Arduino
~~program~~ I'm sorry, *sketch*, then the Arduino IDE just concatenates them
all together. Which means that (without workarounds), you cannot write multiple
programs in the same source directory.

This is a PITA for us, because, for example, we might want to write one program
to test the pathing logic, but another to analyse the signals from the MPU.

One avenue of solving this problem is to use the libraries feature of the IDE.
We could define the classes that we've used as libraries, and simply create many
sketches.

However, there are only two ways of creating libraries:

1. Put the source files in a .zip file, and tell the IDE where it is.
2. Put the source files in the `libraries` folder in `~/sketchbook`

These both suck: the first sucks because we still want to be able to develop
the source files, and the process of editing them is made less fluid when they
are inside a zip file. The second one sucks because it means that now the
project is spread out over many folders on the file system. If we went with the
second one, we'd have to tell a new user to first `git pull` and then copy the
relevant files into the correct folder.

Faced with these issues, we've come up with a new solution, which is actually
a very old solution: header guards.

We place header guards around each of the `.ino` files in the project, which 
check for the definition of a preprocessor variable. This way, we can easily
control the compilation of different programs from the same set of source files.

# Result of all of the above

The result of all of the above is that we have this one source file, `src.ino`,
with the same name as the folder, which just defines a single preprocessor variable,
which is used to control which program actually gets compiled.

\see main.ino

*/

/* #define ANALYSE_SIGNALS */
/* #define CLOSED_LOOP_CONTROL */
/* #define FIRE_EXTINGUISHING */
/* #define MPU_QUAT */
/* #define MAG_TEST */
/* #define VOLTAGE */
/* #define TUNING_ROTATE */
/* #define TUNING_TIMING */

#define MAIN

