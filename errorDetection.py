# -*- coding: utf-8 -*-
import random

class BurstError:

    def __init__(self) -> None:
        pass
    
    def BE_msg_matrix(self, msg):
        matrix = []
        for i in msg: 
            ascii_value = bin(ord(i))[2:]
            if len(ascii_value) < 8:
                missing_bits = 8 - len(ascii_value)
                cnt = 0
                while cnt < missing_bits:
                    ascii_value = "0" + ascii_value
                    cnt += 1
            matrix.append(list(ascii_value))
        ones = []
        parity = ["0", "0", "0", "0", "0", "0", "0", "0"]
        for j in range(0, len(matrix[0])):
            cnt_ones = 0
            cnt_zeros = 0
            for i in range(0, len(matrix)):
                if matrix[i][j] == "1":
                    cnt_ones += 1
                elif matrix[i][j] == "0":
                    cnt_zeros += 1
            ones.append(cnt_ones)

        for k in range(0, len(ones)):
            if ones[k] % 2 == 1:
                parity[k] = "1"
        matrix[len(matrix)-1] = parity
        return (matrix)

    def BE_generate_burst(self, matrix, a, b, burst):
        new_matrix = [row[:] for row in matrix]
        bits = ["0", "1"]
        corrupted_char = [random.choice(list(range(a, b))) for _ in range(burst)]
        for i in range(a, b):
            for j in range(1, len(new_matrix[0])):
                if i in corrupted_char:
                    #if new_matrix[i][j] == "1":
                    #    new_matrix[i][j] = "0"
                    #elif new_matrix[i][j] == "0":
                    #    new_matrix[i][j] = "1"
                    #new_matrix[i][j] = "1" if new_matrix[i][j] == "0" else  "0"
                    new_matrix[i][j] = bits[random.randint(0, 1)]
        return (new_matrix)

    def BE_msg_matrix_text(self, matrix):
        #msg = ""
        ascii_string = ''
        for row in matrix:
            try:
                ascii_string += chr(int(''.join(map(str, row)), 2))
            except ValueError:
                print("")
        return (ascii_string)
    '''
message = "Hello World"
burst = BurstError()
p_matrix = burst.BE_msg_matrix(message)
msg_no_corrupted = burst.BE_msg_matrix_text(p_matrix)
print(msg_no_corrupted)
for row in p_matrix:
    print(row)
print("")
p_matrix_corrupted = burst.BE_generate_burst(p_matrix, 0, len(p_matrix), random.randint(0, 4))
for row in p_matrix_corrupted:
    print(row)

msg_corrupted = burst.BE_msg_matrix_text(p_matrix_corrupted)
print(msg_corrupted)
'''