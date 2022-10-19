import networkx as nx
import matplotlib.pyplot as plt

g = nx.read_graph6("graph.g6")
nx.draw(g, with_labels=True)
plt.savefig("graph.png")
