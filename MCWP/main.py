from MCWP import MCWP

with open("./1.txt", "r") as file:
    graph = MCWP(file)

print("Nodes:", graph.nodes)
print("Edges:", graph.edges)
print("Initial nodes:", graph.inits)
print("Final nodes:", graph.finals)
print("Final nodes:", graph.MCWP(1, 5))
