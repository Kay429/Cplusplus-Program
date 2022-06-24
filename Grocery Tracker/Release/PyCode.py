import re
import string


def PrintAllFrequency():
    ## Iterates through produce.txt counting how many times each item occurs
    ## Then prints each item along with its frequency
    i = 0
    frequencyDict = {} # Dictionary holds each item and its associated frequency
    itemList = [] # A list to hold all unique strings from the file
    f = open("produce.txt", "r")
    produce = f.readlines()
    f.close()
    for item in produce:
        item = item. rstrip('\n') # Strips away the newline character
        if item in frequencyDict:
            frequencyDict[item] += 1

        else:
            frequencyDict[item] = 1
            itemList.append(item) # If item is new to the dictionary, it is appended to the item list

    for item in itemList:
        print(item,  "-", frequencyDict[item])


def FindSpecificFrequency(userString):
    ## Given string userString,
    ##   searches produce.txt and counts occurences of userString
    ## Returns the number of times userString appears in produce.txt
    count = 0
    f = open("produce.txt", "r")
    produce = f.readlines()
    f.close()
    for item in produce:
        item = item. rstrip('\n')
        if item == userString:
            count += 1

    return count


def CreateHistogram():
    ## Determines frequency of each item in produce.txt
    ## Then writes information to frequency.dat
    i = 0
    frequencyDict = {} # Dictionary holds each item and its associated frequency
    itemList = [] # A list to hold all unique strings from the fileitemList = []
    f = open("produce.txt", "r")
    produce = f.readlines()
    f.close()
    for item in produce:
        item = item. rstrip('\n')
        if item in frequencyDict:
            frequencyDict[item] += 1

        else:
            frequencyDict[item] = 1
            itemList.append(item) # If item is new to the dictionary, it is appended to the item list

    f = open("frequency.dat", "w")
    for item in itemList:
        # format of text is:
        # item frequency\n
        f.write(item)
        f.write(" ")
        f.write(str(frequencyDict[item]))
        f.write("\n")
    f.close()