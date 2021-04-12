from sys import argv
from csv import reader


def count_repeats(seq, repeats, str_seq, start, next_pos):
    index = seq.find(str_seq, next_pos)
    l = len(str_seq)
    # print(start, index, l)
    end = index + l
    if (index == -1):
        # print("nothing")
        return
    elif (index == next_pos):
        # print("repeat")
        if start in repeats:
            repeats[start] += 1
        else:
            repeats[start] = 1
        count_repeats(seq, repeats, str_seq, start, end)
    else:
        # print("new")
        if index in repeats:
            repeats[index] += 1
        else:
            repeats[index] = 1
        count_repeats(seq, repeats, str_seq, index, end)
    return


def main():

    # open database
    with open(argv[1], 'r', newline='') as db_file:
        db_conts = reader(db_file)
        db = list(db_conts)
        # for row in db:
        #   print(', '.join(row))

    header = list(db[0])
    # print(header)

    # open sequence
    with open(argv[2], 'r') as seq_file:
        seq = str(seq_file.read())
        # print(seq)
    
    max_str = []

    for str_seq in header[1:]:
        repeats = {}
        count_repeats(seq, repeats, str_seq, 0, 0)
        # print(str_seq)
        # print(repeats)
        if (repeats != {}):
            max_val = max(repeats, key=repeats.get)
            max_str.append(str(repeats[max_val]))
            
    # print(max_str)
    
    match = "No match"
    for row in db:
        name = row[:1]
        str_sig = row[1:]
        if (str_sig == max_str):
            match = name[0]
    
    print(match) 

    # load each STR into mem
    # find STR
    # count STR's
    # repeat for each STR
    # compare sequnce STR to each row in db
    # if sequence found print(name)
    # if not found print("No match")


if __name__ == "__main__":
    main()
    
    # Lavender, 22, 33, 43, 12, 26, 18, 47, 41