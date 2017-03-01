"""
Task 2

Read all the content of a text file into a string and show some info about it.

Objectives:
- use documentation!!!
- basic work with files
- variable declarations
- string operations
"""

# Let's use the __main__ ! Put all your code inside it!

# Open the file with the name 'fisier_input'

# Read all the content in a single string

# Let's play with that string!
#  - count the number of words
#  - make it uppercase
#  - count occurances of parantheses, other characters or the word 'Python'
#  - print the last 10 characters
#  - bonus - whatever you find interesting (e.g. use some regular expressions
#            to parse it)

# Use methods, declare and assign variables
# All changes should be made on a copy of the string

# Hint for strings: https://docs.python.org/2/library/string.html#string-functions
# Hint for files: https://docs.python.org/2/library/io.html#text-i-o
#  & Operatii cu fisiere section from the lab


if __name__ == "__main__":
    file = open("fisier_input", "r")
    word_count = 0
    single_string = ""

    for line in file:
        single_string = single_string + line

    strings = single_string.split()
    word_count = word_count + len(strings)

    char_occ = 0
    for character in strings:
        if character.find(".")!= -1:
            char_occ = char_occ + 1

    print word_count
    print single_string.upper()
    print char_occ
    print single_string[len(single_string)-11:len(single_string)]
