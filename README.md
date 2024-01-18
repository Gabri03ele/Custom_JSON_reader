# Reader for JSON files

This is a project done for an exam using C++.
It is a reader for a custom type of JSON files.
It reads: numbers (double), strings, booleans, nulls, lists and dictionaries.

###A note about strings:
All characters between double quotes are extracted as such. The strings may contain the character " preceded by a character of \, i.e.,
the string may contain the substring \". In this case, therefore, the string does not end with that occurrence of ".
Strings only end when the character " is not preceded by \.

###A note about lists:
A list is a sequence of heterogeneous values separated by commas and enclosed in two square brackets. 
The values contained in the list can be of six types: list (recursion), dictionary (defined below), string enclosed between double quotes,
number of type double, boolean or null (indicating the absence of a value).

###A note about dictionaries:
A dictionary is a set of pairs: key : value
separated by commas and enclosed by two braces. Note that key and value are separated by a ':' character. 
Keys can only be strings enclosed in double quotes (again, these strings can contain escape characters '\'). 
Values can be: list, dictionary, string enclosed in double quotes (possibly with escape characters '1'), double, boolean or null.


### Compile the file

From within the parent directory:

$ mkdir build
$ make

For a "debug" build, do this instead:

$ make debug

To use compile sanitizers:

$ make sanitizers

### Run the code

After compilation, from within the parent directory:

$ ./build/res
