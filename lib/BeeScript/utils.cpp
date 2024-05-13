#include "utils.h"

/**
 * Call a function for each value in an input string.
 * The input string is treated as space-separated values, multiple subsequent spaces are automatically skipped.
 * If a value function call returns `false`, no further values are processed and the function returns `false`.
 * If all values function calls return `true`, the function also returns `true`.
 *
 * @param input The command input.
 * @param valueFn The function to call for each value.
 * @return Whether all value function calls were successful.
 */
bool forEachValue(const String &input, const std::function<bool(String)> &valueFn) {
    int startIndex = 0;

    while (startIndex < input.length()) {
        // Get the end index, or set it to the string length if no space is found.
        int endIndex = input.indexOf(' ', startIndex);
        if (endIndex < 0) {
            endIndex = input.length();
        }

        // Get the input part.
        const String val = input.substring(startIndex, endIndex < 0 ? input.length() : endIndex);

        // Already set the next starting point.
        startIndex = endIndex + 1;

        // Skip empty values.
        if (val == "") {
            continue;
        }

        // Run the function with the value.
        if (!valueFn(val)) {
            return false;
        }
    }

    return true;
}
