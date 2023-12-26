# -*- coding: utf-8 -*-



if __name__ == "__main__":
    
    msg = "Hello World"
    sendMsg = ""
    #matriz = [[0 for _ in range(3)] for _ in range(3)]
    
    matrix = []
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
        print(ascii_value + " " + str(len(ascii_value)) + " " + str(ord(i)))
    
    j = 0
    cnt = 0
    for i in matrix:
        element = matrix[j]
        if element == "1":
            cnt += 1
        
