"""
Objectives:
- Lists
- Dict
- constructs: loops, conditionals
- more work with files
- functions
"""


import re
# function #1
"""
    Returns the number of lines in a file given as parameter.
    @param filename: the file's name
"""
def function1(filename):
    nr = 0
    file = open(filename,"r")
    for line in file:
        nr = nr + 1;
    return nr

# function #2
"""
    Reads the content of a file and fills the given list with the sentences
    found in the file
    @param filename: the file's name
    @param sentences: the list that will be contain the sentences
"""
def function2(filename, sentences):
    file = open(filename,"r")
    single_string = ""
    for line in file:
        single_string = single_string + line

    paragrafs = single_string.split("\n")
    for para in paragrafs:
        prop = para.split(".")
        for p in prop:
            sentences.append(p)

    return sentences
# function #3
"""
    Return a list of the top N most used words in a given file
    @param filename: the file's name
    @param n: the number of words in the top, default is 5
"""
def function3(filename, n):
    file = open(filename,'r')
    single_string = ""
    for line in file:
        single_string = single_string + line
    regex = re.compile('[^a-zA-Z,\.!?]')
    single_string = ' '.join([i for i in single_string.split() if i.isalpha()])

    dict = {}

    words = single_string.split(" ")

    for w in words:
        if w in dict:
            dict[w]= dict[w]+1
        else:
            dict[w] = 1

    return sorted(dict)[::-1][:n:]


#bonus 1p: implement your own sort method instead of using an existing one



if __name__ == "__main__":

    filename = "fisier_input"


    print function1(filename)
    sentences = []
    sentences = function2(filename,sentences)
    print sentences[0]
    list_print = function3(filename,3)

    for s in sentences:
        if len(s.split()) < 15 and len(s.split()) > 0:
            print s


    fileWrite = open("text_out",'w')
    for i in list_print:
        fileWrite.writelines(i+'\n')
