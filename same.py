def read_file(file_path, encoding='utf-8'):
    with open(file_path, 'r', encoding=encoding, errors='replace') as file:
        content = file.readlines()
    return content

def find_same_parts(file1_lines, file2_lines):
    same_lines = []

    for line1, line2 in zip(file1_lines, file2_lines):
        words1 = line1.strip().split()
        words2 = line2.strip().split()

        same_words = [word1 for word1, word2 in zip(words1, words2) if word1 == word2]
        same_line = ' '.join(same_words)

        if same_lines and same_line == same_lines[-1]:
            same_lines.append(same_line)
        else:
            same_lines.append(same_line)

    return same_lines

file1_path = 'initmem.txt'
file2_path = 'goalmem.txt'

file1_lines = read_file(file1_path, encoding = 'cp949')
file2_lines = read_file(file2_path, encoding = 'cp949')

same_lines = find_same_parts(file1_lines, file2_lines)

print("Same parts by word :")
for line in same_lines:
    print(line)