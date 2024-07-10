import heapq
class MCWP:
    def __init__(self, graph_file):
        lines = graph_file.readlines()
        self.edges = {}
        self.nodes = set()
        self.inits = set()
        self.finals = set()

        for i in range(len(lines) - 2):
            line = lines[i]
            n, dest, weight = (int(x) for x in line.split(" "))
            self.nodes.add(n)
            self.nodes.add(dest)
            if n not in self.edges:
                self.edges[n] = []
            self.edges[n].append((dest, weight))

        init_line = lines[-2]
        init_nodes = set(int(x) for x in init_line.split(":")[1].split(" "))
        self.inits = init_nodes
        self.nodes.update(self.inits)

        final_line = lines[-1]
        final_nodes = set(int(x) for x in final_line.split(":")[1].split(" "))
        self.finals = final_nodes
        self.nodes.update(self.finals)
        
    def MCWP(self, begin_node, end_node):
        MCWP_path = []
        # Priority queue to hold (cost, node, path)
        queue = [(0, begin_node, [])]
        # Dictionary to hold the minimum cost to reach each node
        min_cost = {node: float('inf') for node in self.nodes}
        min_cost[begin_node] = 0
        # Dictionary to hold the best path to reach each node
        best_path = {node: [] for node in self.nodes}

        while queue:
            current_cost, current_node, path = heapq.heappop(queue)
            # Include current_node in the path
            path = path + [current_node]

            if current_node == end_node:
                return path

            if current_cost > min_cost[current_node]:
                continue

            for neighbor, weight in self.edges.get(current_node, []):
                cost = current_cost + weight
                if cost < min_cost[neighbor]:
                    min_cost[neighbor] = cost
                    best_path[neighbor] = path
                    heapq.heappush(queue, (cost, neighbor, path))
        
        return []
        #return MCWP_path
