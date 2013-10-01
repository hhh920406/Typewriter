def is_valid_word(wordlist, word):
    return word in wordlist


def make_str_from_row(board, row_index):
    word = ''
    for i in range(len(board[row_index])):
        word += board[row_index][i]
    return word


def make_str_from_column(board, column_index):
    word = ''
    for i in range(len(board)):
        word += board[i][column_index]
    return word


def board_contains_word_in_row(board, word):
    for row_index in range(len(board)):
        if word in make_str_from_row(board, row_index):
            return True
    return False


def board_contains_word_in_column(board, word):
    for column_index in range(len(board[0])):
        if word in make_str_from_column(board, column_index):
            return True
    return False


def board_contains_word(board, word):
    return board_contains_word_in_row(board, word) or board_contains_word_in_column(board, word)


def word_score(word):
    l = len(word)
    if l < 3:
        return 0
    elif l <= 6:
        return l
    elif l <= 9:
        return l * 2
    else:
        return l * 3


def update_score(player_info, word):
    player_info[1] += word_score(word)


def num_words_on_board(board, words):
    cnt = 0
    for word in words:
        if board_contains_word(board, word):
            cnt += 1
    return cnt


def read_words(words_file):
    words = []
    while True:
        line = words_file.readline()
        if not line:
            break
        words.append(line.rstrip('\n'))
    return words


def read_board(board_file):
    board = []
    i = 0
    while True:
        line = board_file.readline()
        if not line:
            break
        board.append([])
        for j in range(len(line)):
            if line[j] == '\n':
                continue
            board[i].append(line[j])
        i += 1
    return board
