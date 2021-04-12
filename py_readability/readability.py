from cs50 import get_string
import string as s

text = get_string("Text: ")
# create words arary
words_array = text.split()
words = len(words_array)
# create translation tables
white_space = text.maketrans(" ", " ", s.whitespace)
punctuation = text.maketrans(" ", " ", s.punctuation)
# use translation tables to determine number of letters
letters = len(text.translate(white_space).translate(punctuation))
# count instances of sentence enders
sentences = text.count(".") + text.count("!") + text.count("?")
# implement Coleman-Liau formula
L = letters / float(words) * 100
S = sentences / float(words) * 100
index = round((0.0588 * L) - (0.296 * S) - 15.8)
print(words, letters, sentences, index)
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
