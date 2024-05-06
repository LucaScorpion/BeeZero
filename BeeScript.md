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
# Hold the a key.
hold a

# Hold the b and c keys.
hold b c
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
# Release the a and b keys.
release a b

# Release all keys.
release
```

### `sleep`

Make the script sleep for the given amount of milliseconds.
The argument must be a valid number.

```
# Sleep for 100 milliseconds.
sleep 100
```

### `type`

Type a string, pressing and releasing each character key.
For capital letters, the shift key is held automatically while sending the key.

```
type https://example.com

# This will type a lowercase and uppercase a. 
type aA
```
