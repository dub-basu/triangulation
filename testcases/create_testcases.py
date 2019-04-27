from random import randint

RANGE_X_NEG = -100
RANGE_X_POS = 100
RANGE_Y_NEG = -100
RANGE_Y_POS = 100
INPUT_SIZE = 100
FILENAME = "input1.txt"

def get_random_point():
    pt = (randint(RANGE_X_NEG, RANGE_X_POS + 1), randint(RANGE_Y_NEG, RANGE_Y_POS))
    return(pt)

with open(FILENAME, 'w+') as f:
    for i in range(INPUT_SIZE):
        point = get_random_point()
        pt_string =  str(point).replace(' ','')
        f.write(pt_string)
        f.write('\n')
        