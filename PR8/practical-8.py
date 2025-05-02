import collections

def compute_first(grammar, non_terminal, first):
    if non_terminal in first:
        return first[non_terminal]
    first[non_terminal] = set()
    for production in grammar[non_terminal]:
        if production == "ε":
            first[non_terminal].add("ε")
        else:
            for symbol in production:
                if symbol.isupper():  # Non-terminal
                    first_set = compute_first(grammar, symbol, first)
                    first[non_terminal].update(first_set - {"ε"})
                    if "ε" not in first_set:
                        break
                else:  # Terminal
                    first[non_terminal].add(symbol)
                    break
    return first[non_terminal]

def compute_follow(grammar, start_symbol, first, follow):
    follow[start_symbol].add("$")  # End marker for the start symbol
    for non_terminal in grammar:
        for production in grammar[non_terminal]:
            for i, symbol in enumerate(production):
                if symbol.isupper():  # Non-terminal
                    trailer = follow[non_terminal]
                    for next_symbol in production[i + 1:]:
                        if next_symbol.isupper():
                            first_next = first[next_symbol]
                            follow[symbol].update(first_next - {"ε"})
                            if "ε" in first_next:
                                continue
                        else:
                            follow[symbol].add(next_symbol)
                        break
                    else:
                        follow[symbol].update(trailer)

def construct_parsing_table(grammar, first, follow):
    table = collections.defaultdict(dict)
    is_ll1 = True
    for non_terminal in grammar:
        for production in grammar[non_terminal]:
            first_set = set()
            if production == "ε":
                first_set = follow[non_terminal]
            else:
                for symbol in production:
                    if symbol.isupper():
                        first_set.update(first[symbol] - {"ε"})
                        if "ε" not in first[symbol]:
                            break
                    else:
                        first_set.add(symbol)
                        break
                else:
                    first_set.update(follow[non_terminal])
            for terminal in first_set:
                if terminal in table[non_terminal]:
                    is_ll1 = False
                table[non_terminal][terminal] = production
    return table, is_ll1

def validate_string(parsing_table, start_symbol, input_string):
    stack = ["$", start_symbol]
    input_string += "$"
    pointer = 0
    while stack:
        top = stack.pop()
        if top == input_string[pointer]:
            pointer += 1
        elif top in parsing_table:
            if input_string[pointer] in parsing_table[top]:
                production = parsing_table[top][input_string[pointer]]
                if production != "ε":
                    stack.extend(reversed(production))
            else:
                return "Invalid string"
        else:
            return "Invalid string"
    return "Valid string" if pointer == len(input_string) else "Invalid string"

def main():
    grammar = {
        "E": ["TA"],
        "A": ["+TA", "ε"],
        "T": ["FB"],
        "B": ["*FB", "ε"],
        "F": ["(E)", "id"]
    }
    start_symbol = "E"
    first, follow = {}, collections.defaultdict(set)
    for non_terminal in grammar:
        compute_first(grammar, non_terminal, first)
    compute_follow(grammar, start_symbol, first, follow)
    parsing_table, is_ll1 = construct_parsing_table(grammar, first, follow)
    print("Predictive Parsing Table:")
    for nt, rules in parsing_table.items():
        print(nt, rules)
    print("LL(1) Grammar:", "Yes" if is_ll1 else "No")
    input_string = "id+id*id"
    print("Validation:", validate_string(parsing_table, start_symbol, input_string))

if __name__ == "__main__":
    main()
