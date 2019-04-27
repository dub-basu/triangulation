import matplotlib.pyplot as plt

times = {}

with open('actual_time.txt') as f:
    lines = f.read().split('\n')
    for line in lines:
        input_size, time_taken = list(map(float,line.split()))
        times[input_size] = time_taken

def plot_graph(times):
    inp_sizes = []
    time_list = []
    for input_size, time_taken in times.items():
        inp_sizes.append(input_size)
        time_list.append(time_taken)
    plt.plot(inp_sizes, time_list)
    plt.ylabel('Time taken')
    plt.xlabel('Input size')
    plt.savefig('report.png')

plot_graph(times)