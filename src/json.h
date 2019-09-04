/*! \file
    \brief Definition of preprocessor directives for dumping JSON formatted data over serial.

This file contains preprocessor `#define`s which can be used for dumping data
over serial in JSON format, pretty-printed.

# Usage:

- `jstart` to start a new JSON object.
- `jkey` to specify a key.
- `jval` to specify a value (this should come after `jkey`)
- `jnext` to insert a comma and signal the start of the next key-value pair.

Example:

    jstart;
    jkey("msg"); jval("hello, world");
    jend;

The above would print out the following over serial.

```
{
    "msg" : "hello, world"
}
```

There are also some convience functions:

- `jitem` which uses the variable name as the key, and the variable value as
  the value.
- `jfloat` which is like `jitem` but for floating-point values,
  printing them with 6 digits of precision.

\see Utils
*/

#ifndef JSON_H
#define JSON_H

#include <Arduino.h>

extern HardwareSerial* SerialCom;
extern int TABLEVEL;

// Start a new line at the correct indentation
#define jnewline SerialCom->print("\n"); for (int i = 0; i < TABLEVEL; ++i) SerialCom->print("\t")

/// Start a new object.
///
#define jstart jnewline; SerialCom->print(""); ++TABLEVEL; jnewline

/// Add key/value pairs to the object.
/**
You could also use `jkey(abc); jstart` to create a nested object under the key "abc"
*/
#define jkey(x) SerialCom->print("\"" #x "\" : ")
#define jval(...) SerialCom->print(__VA_ARGS__)

/// Prepare for the next item
///
#define jnext SerialCom->print(","); jnewline

/// Finish an object.
///
#define jend --TABLEVEL; jnewline; SerialCom->print("")

/// Shortcut for creating key-value pair using a variable name.
///
#define jitem(x) jkey(x); jval(x)

/// Shortcut for floats, with a more helpful amount of digits.
///
#define jfloat(x) jkey(x); jval(x, 6)

#endif
