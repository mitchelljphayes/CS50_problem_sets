from cs50 import get_float


# function to implement greedy algorithm to return lowest number of coins
def minimum_coins(money):  # more comments
    m = int(100 * money)  # more comments
    c = 0
    while m >= 25:
        m -= 25
        c += 1
    while m >= 10:
        m -= 10
        c += 1
    while m >= 5:
        m -= 5
        c += 1
    while m >= 1:
        m -= 1
        c += 1
    # more comments
    return c


# function to propmt user to enter the amount of change
def get_money(prompt):
    m = 0.00  # more comments
    while m < 0.01:
        m = get_float(prompt)
    # more comments
    return m  # more comments


# main program
money = get_money("Change Owed: ")  # more comments
coins = minimum_coins(money)  # more comments
print(coins)