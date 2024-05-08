# BeeScript

Each line is interpreted as a command, followed by input for that command.
For example:

```
foo bar baz
```

would run the "foo" command with "bar baz" as its input.

Lines starting with a `#` character are treated as comments.

```
# This is a comment.
    # Comments can also be indented.
```

Any leading and trailing whitespace is trimmed from each line,
and if any error occurs, script execution is stopped.

## Commands

### `hold`

Hold one or more keys.

```
# Hold the shift key.
hold shift

# Hold the ctrl and c keys.
hold ctrl c
```

### `press`

Press (and release) one or more keys.

```
press enter

# Press the Windows key + r.
press super r
```

### `release`

Release one or more keys.
If no arguments are given, all held keys are released.

```
# Release the shift and b keys.
release shift b

# Release all keys.
release
```

### `delay`

Make the script delay (i.e. wait, sleep) for the given amount of milliseconds.
The argument must be a valid number.

```
# Delay for 100 milliseconds.
delay 100
```

### `type`

Type a string, pressing and releasing each character key.
For capital letters, the shift key is held automatically while sending the key.

```
type https://example.com

# This will type a lowercase and uppercase a. 
type aA
```

### `typeln`

`type` a string, followed by pressing enter.

```
typeln Hello world

# Is the same as:
type Hello world
press enter
```

## Keys

All available key names can be found in [lib/BeeScript/keys.cpp](lib/BeeScript/keys.cpp).
Single characters all map to their own key.
Note that some keys have multiple names,
e.g. `super`, `windows`, and `command` all refer to the same key.
