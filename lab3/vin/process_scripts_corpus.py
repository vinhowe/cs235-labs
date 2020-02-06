from profanity_filter import ProfanityFilter

pf = ProfanityFilter()

with open('gp2.txt') as scripts_file:
    text = scripts_file.readlines()
    output = text[2::4]
    censored_output = []
    line_no = 0
    print('censoring')
    for line in output:
        print(f"line: {line}")
        censored_output.append(pf.censor(line))
    censored_output = "".join(censored_output)
    outFile = open('movie_scripts.txt', 'w')
    outFile.write(censored_output)
