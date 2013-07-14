voting_data = list(open("voting_record_dump109.txt"))

## Task 1
def create_voting_dict():
    voting_dict = {}
    for voting in voting_data:
        values = voting.split(' ')
        voting_dict[values[0]] = [int(values[i]) for i in range(len(values)) if i > 2]
    return voting_dict

## Task 2
def policy_compare(sen_a, sen_b, voting_dict):
    u = voting_dict[sen_a]
    v = voting_dict[sen_b]
    return sum([u[i] * v[i] for i in range(len(u))])

## Task 3
def most_similar(sen, voting_dict):
    similar = -1e100
    name = ""
    for key in voting_dict.keys():
        if key == sen:
            continue
        temp = policy_compare(sen, key, voting_dict)
        if temp > similar:
            similar = temp
            name = key
    return name

## Task 4
def least_similar(sen, voting_dict):
    similar = 1e100
    name = ""
    for key in voting_dict.keys():
        if key == sen:
            continue
        temp = policy_compare(sen, key, voting_dict)
        if temp < similar:
            similar = temp
            name = key
    return name

## Task 5
most_like_chafee    = 'Jeffords'
least_like_santorum = 'Feingold' 

# Task 6
def find_average_similarity(sen, sen_set, voting_dict):
    sum = 0.0
    for x in sen_set:
        sum += policy_compare(sen, x, voting_dict)
    return sum / len(sen_set)

most_average_Democrat = 'Alexander'

# Task 7

def find_average_record(sen_set, voting_dict):
    vec = []
    for sen in sen_set:
        vote = voting_dict[sen]
        if vec == []:
            vec = [0 for x in range(len(vote))]
        for i in range(len(vote)):
            vec[i] += vote[i]
    for i in range(len(vec)):
        vec[i] /= len(sen_set)
    return vec

average_Democrat_record = [-0.16279069767441862, -0.23255813953488372, 1.0, 0.8372093023255814, 0.9767441860465116, -0.13953488372093023, -0.9534883720930233, 0.813953488372093, 0.9767441860465116, 0.9767441860465116, 0.9069767441860465, 0.7674418604651163, 0.6744186046511628, 0.9767441860465116, -0.5116279069767442, 0.9302325581395349, 0.9534883720930233, 0.9767441860465116, -0.3953488372093023, 0.9767441860465116, 1.0, 1.0, 1.0, 0.9534883720930233, -0.4883720930232558, 1.0, -0.32558139534883723, -0.06976744186046512, 0.9767441860465116, 0.8604651162790697, 0.9767441860465116, 0.9767441860465116, 1.0, 1.0, 0.9767441860465116, -0.3488372093023256, 0.9767441860465116, -0.4883720930232558, 0.23255813953488372, 0.8837209302325582, 0.4418604651162791, 0.9069767441860465, -0.9069767441860465, 1.0, 0.9069767441860465, -0.3023255813953488]

# Task 8
def bitter_rivals(voting_dict):
    name1 = ""
    name2 = ""
    similar = 1e100
    for key1 in voting_dict.keys():
        for key2 in voting_dict.keys():
            if key1 == key2:
                continue
            temp = policy_compare(key1, key2, voting_dict)
            if temp < similar:
                similar = temp
                name1 = key1
                name2 = key2
    return (name1, name2)
