# -*- coding: utf-8 -*-
import random

class BurstError:

    def __init__(self) -> None:
        pass
    
    def BE_msg_matrix(self, msg):
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

    def BE_generate_burst(self, matrix, a, b, burst):
        new_matrix = [row[:] for row in matrix]
        bits = ["0", "1"]
        corrupted_char = [random.choice(list(range(a, b))) for _ in range(burst)]
        for i in range(a, b):
            for j in range(0, len(new_matrix[0])):
                if i in corrupted_char:
                    new_matrix[i][j] = bits[random.randint(0, 1)]
        return (new_matrix)

    def BE_msg_matrix_text(self, matrix):
        msg = ""
        for i in range(0, len(matrix)):
            character = ""
            for j in range(0, len(matrix[0])):
                character += matrix[i][j]
            num = int(character, 2)
            msg += chr(num)
        return (msg)