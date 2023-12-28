# -*- coding: utf-8 -*-
import random

class BurstError:
    def __init__(self):
        self.matrix = []





def msg_matrix_encode(msg, matrix = []):
    for i in msg: 
        ascii_value = bin(ord(i))[2:]
        #print(ascii_value)
        #print(len(ascii_value))
        if len(ascii_value) < 7:
            missing_bits = 7 - len(ascii_value)
            cnt = 0
            while cnt < missing_bits:
                ascii_value = "0" + ascii_value
                cnt += 1
        matrix.append(list(ascii_value))
    return (matrix)

def generateBurst(matrix, a, b, burst):
    bits = ["0", "1"]
    corrupted_char = random.choices(list(range(a, b)), k = burst)
    print(corrupted_char)
    for i in range(a, b):
        for j in range(0, len(matrix[0])):
            if i in corrupted_char:
                matrix[i][j] = bits[random.randint(0, 1)]
    return (matrix)

def msg_matrix_decode(matrix, msg=""):
    for i in range(0, len(matrix)):
        character = ""
        for j in range(0, len(matrix[0])):
            character = character + matrix[i][j]
        num = int(character, 2)
        msg += chr(num)
    return (msg)

if __name__ == "__main__":
    msg = "Hello World"
    #msg = "An enormous puppy was looking down at her with large round eyes, and feebly stretching out one paw, trying to touch her. Poor little thing! said Alice, in a coaxing tone, and she tried hard to whistle to it; but she was terribly frightened all the time at the thought that it might be hungry, in which case it would be very likely to eat her up in spite of all her coaxing." 
    matrix = msg_matrix_encode(msg)
    matrix_dist = generateBurst(matrix, 0, len(matrix), 0)
    new_msg = msg_matrix_decode(matrix_dist)
    for row in matrix:
        print(row)
    print("\n")
    for row in matrix_dist:
        print(row)
    print("\n")
    print("Original msg: " + msg + " " + str(len(msg)))
    print("Modified msg: " + new_msg + " " + str(len(new_msg)))

