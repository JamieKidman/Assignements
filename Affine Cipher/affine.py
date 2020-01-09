import string
import os
from math import gcd


# Creates an array of numbers up to m (hard coded m to 52 as thats what the task requires)
numberLine = {}
for x in range(0, 52):
    numberLine[x] = x

# Creates an array of uppercase and lower case characters
asciibet = list(string.ascii_letters)

# Creates a mapping of characters and numbers, so "a" = "1"
affineCalcBet = dict(zip(asciibet, numberLine))

# Creates a mapping of numbers to characters, so "1" = "a"
affineBet = dict(zip(affineCalcBet.values(), affineCalcBet.keys()))


# Tests if the a is co prime with m
def keyTest(keyA):
    if(gcd(keyA, 52) == 1):
        return True

    else:
        return False


# creates a mapping of keys to values, so im able to make "a" = "b" given a set of keys
def encryptCalc(keyA, keyB, varX):
    varX = affineCalcBet[varX]

    return affineBet[(keyA * varX + keyB) % 52]


# Creates a mapping of keys to values that is inverse to encryption, so im able to make "b" = "a" given a set of keys
def decryptCalc(keyA, keyB, varX):
    listA = list()

    for i in range(0, 52):
        listA.append(affineBet[(keyA * i + keyB) % 52])

    decryptBet = dict(zip(listA, asciibet))

    return decryptBet[varX]


#    Both mode 1 and 2 are near identical and could combine the two however this way mode is only evaluated once
#        (only diffence being they encrypt or decrypt)
#    The first for loop runs for every line in the file
#    The second for loop runs for every character in the line
def main():
    mode = input("Would you like to Encrypt: 1 or Decrypt: 2... : ")
    inputKeyA = int(input("Please Enter Your First Key: "))
    inputKeyB = int(input("Please Enter Your Second Key: "))
    inputFile = input("Please enter the name of the file: ")

    if os.path.isfile(inputFile):
        f = open(inputFile, "r")
        inLines = f.readlines()

        if(keyTest(inputKeyA)):
            if(mode == "1"):
                for i in range(0, len(inLines)):
                    currentLine = list(inLines[i])
                    for j in range(0, len(currentLine)):
                        if(currentLine[j] not in asciibet):
                            print(currentLine[j], end="")
                            j += 1
                        else:
                            print(encryptCalc(inputKeyA, inputKeyB, currentLine[j]), end="")

            if(mode == "2"):
                for i in range(0, len(inLines)):
                    currentLine = list(inLines[i])
                    for j in range(0, len(currentLine)):
                        if(currentLine[j] not in asciibet):
                            print(currentLine[j], end="")
                            j += 1
                        else:
                            print(decryptCalc(inputKeyA, inputKeyB, currentLine[j]), end="")

    else:
        print("Please try again")
    print()


main()
