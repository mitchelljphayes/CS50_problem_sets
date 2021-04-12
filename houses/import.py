from csv import reader
from cs50 import SQL
from sys import argv

# determine correct number of CL args
if len(argv) != 2:
    print("usage: python import.py [characters.csv]")
    exit()

# link up db
char_db = SQL("sqlite:///students.db")

# open file
with open(argv[1], 'r', newline='') as characters_file:
    fconts = reader(characters_file)
    chars_list = list(fconts)

# read in all the names
    for char in chars_list[1:]:
        full_name = char[0].split()
        house = char[1]
        birth = char[2]
        # case for no middle name
        if len(full_name) == 2:
            first_name = full_name[0]
            middle_name = None
            last_name = full_name[1]
        # case for middle name
        elif len(full_name) == 3:
            first_name = full_name[0]
            middle_name = full_name[1]
            last_name = full_name[-1]
        # insert character record into db
        char_db.execute('INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)',
                        first_name, middle_name, last_name, house, int(birth))

