def read_file(file_path, encoding='utf-8'):
    with open(file_path, 'r', encoding=encoding, errors='replace') as file:
        content = file.readlines()
    return content

def find_word_differences(file1_lines, file2_lines):
    diff_lines = []
    line_counts = {}

    for line1, line2 in zip(file1_lines, file2_lines):
        words1 = line1.strip().split()
        words2 = line2.strip().split()

        diff_words = [word1 for word1, word2 in zip(words1, words2) if word1 != word2]
        diff_line = ' '.join(diff_words)

        if diff_line not in line_counts:
            line_counts[diff_line] = 1
        else:
            line_counts[diff_line] += 1

        if line_counts[diff_line] <= 2:
            diff_lines.append(diff_line)

    return diff_lines

def main():
    file1_path = 'initmem.txt'
    file2_path = 'goalmem.txt'

    file1_lines = read_file(file1_path, encoding='cp949')
    file2_lines = read_file(file2_path, encoding='cp949')

    diff_lines = find_word_differences(file1_lines, file2_lines)

    print("Differences by word:")
    for line in diff_lines:
        print(line)

main()