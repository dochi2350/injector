with open('temp.txt', 'r') as file:
    lines = file.readlines()

lines = [line for line in lines if len(line.strip().split()) == 8]

for line in lines:
    print(line)