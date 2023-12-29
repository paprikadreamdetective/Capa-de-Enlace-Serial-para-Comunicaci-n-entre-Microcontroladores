# -*- coding: utf-8 -*-
import random


def BE_msg_matrix(msg):
    matrix = []
    for i in msg: 
        ascii_value = bin(ord(i))[2:]
        if len(ascii_value) < 7:
            missing_bits = 7 - len(ascii_value)
            cnt = 0
            while cnt < missing_bits:
                ascii_value = "0" + ascii_value
                cnt += 1
        matrix.append(list(ascii_value))
    return (matrix)

def BE_generate_burst(matrix, a, b, burst):
    new_matrix = [row[:] for row in matrix]
    #new_matrix = copy.copy(matrix)
    bits = ["0", "1"]
    #corrupted_char = (Choices(list(range(a, b)), burst)).result
    corrupted_char = [random.choice(list(range(a, b))) for _ in range(burst)]
    #corrupted_char = choices.sequence(list(a, b), burst)
    #corrupted_char = random.choice(list(a, b))
    #corrupted_char = list.
    #corrupted_char = random.sample(list(range(a, b)), min(burst, b - a))
    #corrupted_char = random.choices(list(range(a, b)), k = burst)
    #print(corrupted_char)
    for i in range(a, b):
        for j in range(0, len(new_matrix[0])):
            if i in corrupted_char:
                new_matrix[i][j] = bits[random.randint(0, 1)]
    return (new_matrix)

def BE_msg_matrix_text(matrix):
    msg = ""
    for i in range(0, len(matrix)):
        character = ""
        for j in range(0, len(matrix[0])):
            character += matrix[i][j]
        num = int(character, 2)
        msg += chr(num)
    return (msg)

'''
class BurstError:

    def __init__(self):
        self.matrix = []
        self.matrix_corrupted = self.matrix
    def BE_msg_matrix(self, msg):
        for i in msg: 
            ascii_value = bin(ord(i))[2:]
            if len(ascii_value) < 7:
                missing_bits = 7 - len(ascii_value)
                cnt = 0
                while cnt < missing_bits:
                    ascii_value = "0" + ascii_value
                    cnt += 1
            self.matrix.append(list(ascii_value))
        return (self.matrix)
    
    def BE_generate_burst(self, a, b, burst):
        bits = ["0", "1"]
        #corrupted_char = (Choices(list(range(a, b)), burst)).result
        corrupted_char = [random.choice(list(range(a, b))) for _ in range(burst)]
        #corrupted_char = choices.sequence(list(a, b), burst)
        #corrupted_char = random.choice(list(a, b))
        #corrupted_char = list.
        #corrupted_char = random.sample(list(range(a, b)), min(burst, b - a))
        #corrupted_char = random.choices(list(range(a, b)), k = burst)
        #print(corrupted_char)
        for i in range(a, b):
            for j in range(0, len(self.matrix_corrupted[0])):
                if i in corrupted_char:
                    self.matrix_corrupted[i][j] = bits[random.randint(0, 1)]
        return (self.matrix_corrupted)
    
    def BE_msg_matrix_text(self):
        msg = ""
        for i in range(0, len(self.matrix_corrupted)):
            character = ""
            for j in range(0, len(self.matrix_corrupted[0])):
                character += self.matrix_corrupted[i][j]
            num = int(character, 2)
            msg += chr(num)
        return (msg)

'''