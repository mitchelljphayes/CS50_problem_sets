from cs50 import get_int


# recursive print bricks function
def print_bricks(n):
    if n > 0:
        print_bricks(n - 1)
    else:
        return
    print(" " * (height - n), end="") 
    print("#" * n)


# control of program
b = False
while b == False:
    height = get_int("How high?\n")
    if (height < 9) & (height > 0):
        b = True
        print_bricks(height)

