def get_length(dna):
    return len(dna)

def is_longer(dna1, dna2):
    return len(dna1) > len(dna2)

def count_nucleotides(dna, nucleotide):
    return len([1 for c in dna if c == nucleotide])

def contains_sequence(dna1, dna2):
    return dna2 in dna1

def is_valid_sequence(dna):
    return len([1 for c in dna if c == 'A' or c == 'T' or c == 'C' or c == 'G']) == len(dna)

def insert_sequence(dna1, dna2, index):
    return dna1[0:index] + dna2 + dna1[index:]

def get_complement(nucleotide):
    return {'A':'T', 'T':'A', 'C':'G', 'G':'C'}[nucleotide]

def get_complementary_sequence(dna):
    return ''.join([get_complement(c) for c in dna])
