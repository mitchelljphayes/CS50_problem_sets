from cs50 import get_string
import itertools as it


# run the main steps
def main():
    cc_num = get_cc()
    co = cc_co(cc_num)
    valid = ccv(cc_num)
    if (valid):
        print(co)
    else:
        print("INVALID")


# get cc num from user and convert to a list
def get_cc():
    num = list(map(int, get_string("CC Number: ")))
    return num


# apply Luhn's Algorithm
def ccv(cc_num):
    # revers cc num
    cc_num.reverse()
    # even index(non-zeroth)
    e = list(it.islice(cc_num, 1, None, 2))
    # odd index(non-zeroth)
    o = list(it.islice(cc_num, 0, None, 2))
    e2 = [str(n * 2) for n in e]
    # flatten the numbers into digits
    e2f = list(it.chain.from_iterable(e2))
    luhn = 0
    for n in e2f:
        luhn += int(n)
    for n in o:
        luhn += n
    # take mod of total
    valid = luhn % 10 == 0
    return valid


# determine cc company by their number selections
def cc_co(cc_num):
    l = len(cc_num)
    if (l == 15) and (cc_num[0] == 3) and ((cc_num[1] == 7) or (cc_num[1] == 4)):
        return("AMEX")
    elif (l == 16) and (cc_num[0] == 5) and (cc_num[1] in range(1, 6)):
        return("MASTERCARD")
    elif (l == 13) or (l == 16) and (cc_num[0] == 4):
        return("VISA")
    else:
        return("INVALID")


# defining main
if __name__ == "__main__":
    main()

# 369421438430814

# 5673598276138003