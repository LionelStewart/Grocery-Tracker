import re
import string
from os.path import exists

def createGroceryList(): 
    groceryList = {}
    groceryItems = open("CS210_Project_Three_Input_File.txt", "r")

    for groceryItem in groceryItems:
        groceryItem = groceryItem.strip('\n')

        if(groceryItem not in groceryList):
            groceryList[groceryItem] = 1
        else:
            groceryList[groceryItem] += 1
            
    groceryItems.close()

    # Write grocery list to frequency.dat file
    open("frequency.dat", "x")

    frequencyDat = open("frequency.dat", "w")

    for groceryItem, itemQuantity in groceryList.items():
            frequencyDat.write('{0} {1}\n'.format(groceryItem, str(itemQuantity)))

    frequencyDat.close()


if(not exists("frequency.dat")):
    createGroceryList()




def showGroceryList():
    frequencyDat = open("frequency.dat", "r")

    for line in frequencyDat:
        print(line, end="")

    frequencyDat.close() 


def findItemQuantity(groceryItem):
    frequencyDat = open("frequency.dat", "r")
    itemQuantity = 0

    for line in frequencyDat:
        match = re.search(groceryItem, line)

        if(match):
            itemQuantity = int(line.split()[1])

    frequencyDat.close() 
    return itemQuantity

def showHistogram():
    frequencyDat = open("frequency.dat", "r")

    for line in frequencyDat:
        line = line.split()
        groceryItem = line[0]
        itemQuantity = "*" * (int(line[1]))

        print(groceryItem, itemQuantity)

    frequencyDat.close() 