import matplotlib.pyplot as plt
import re

def read_data():
    file_path = input("Enter the file path: ")
    # file_path = '08/output.log'
    ys = []
    legend = []

    # regular expression pattern to match program name and a float number
    pattern = re.compile(r'\$!.//(\w+\_\d+_\d+): (\d+\.\d+)')
    with open(file_path, 'r') as f:
        content = f.read()

    # find all matches of the pattern in the content
    matches = pattern.findall(content)

    # group the matches by the program name
    programs = {}
    for match in matches:
        program_name = match[0]
        time = float(match[1])
        if program_name not in programs:
            programs[program_name] = []
        programs[program_name].append(time)

    return programs



def create_graphs(ys):

    x, legend = [], []
    while 1:
        y = input("Enter the number of threads Press 'q' to quit: ")
        if y == 'q':
            break
        else:
            x.append(int(y))

    
    for (program_name, values) in ys.items():
        plt.plot(x, values, marker='o', linestyle='-')
        legend.append(program_name)
    
    plt.title('Execution Time comparison')
    plt.xlabel('Number of Threads')
    plt.ylabel('Time (s)')
    plt.legend(legend)
    plt.show()
    plt.savefig('execution_time.png')

if __name__ == '__main__':
    create_graphs(read_data())