from cs50 import SQL
from sys import argv

# make sure the user enters the right number of CL arguments
if len(argv) != 2:
    print("Usage: python roster.py [HOUSE NAME]")
    exit

# link to the db
char_db = SQL("sqlite:///students.db")

# bing CL arg to variable
house = argv[1]

# specify query
query = "SELECT * FROM students WHERE house = '{}' ORDER BY last, first;"

# execute query
students = char_db.execute(query.format(house))

# print each student returned in query
for student in students:
    if student['middle'] == None:
        out = "{s[first]} {s[last]}, born {s[birth]}".format(s=student)
    else:
        out = "{s[first]} {s[middle]} {s[last]}, born {s[birth]}".format(s=student)
    print(out)