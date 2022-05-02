"""

The Graph class in the module computes prime paths

"""


class ControlFlowGraph:
    """

    """
    def __init__(self, graph_file):
        """
        Arges:

            graph_file (str): The path of saved CFG graph


        """
        lines = graph_file.readlines()
        self.edges = {}
        self.nodes = set()
        self.inits = set()
        self.finals = set()
        for i in range(len(lines) - 2):
            line = lines[i]
            n, dest = (int(x) for x in line.split(' '))
            self.nodes.add(dest)
            try:
                self.edges[n].append(dest)
            except:
                self.edges[n] = [dest]

        init_line = lines[-2]
        init_nodes = set(int(x) for x in init_line.split(':')[1].split(' '))
        self.inits = init_nodes
        self.nodes.update(self.inits)

        final_line = lines[-1]
        final_nodes = set(int(x) for x in final_line.split(':')[1].split(' '))
        self.finals = final_nodes
        self.nodes.update(self.finals)

    def reachHead(self, path):
        """

        """

        first = path[0]
        non_final_nodes = self.nodes - self.finals
        for n in non_final_nodes:
            if first in self.edges[n] and n not in path:
                return False
        return True

    def reachEnd(self, path):
        """

        """

        last = path[-1]
        if last in self.finals:
            return True
        for n in self.edges[last]:
            if n not in path[1:]:
                return False
        return True

    def extend(self, path):
        """

        """

        extended_paths = []
        last = path[-1]
        if last in self.finals:
            return list()
        for n in self.edges[last]:
            if n not in path[1:]:
                extended_paths += [path + [n]]
        return extended_paths

    def computePrimePaths(self):
        """


        """

        self.primePaths = []
        try_paths = [[n] for n in self.nodes]
        while len(try_paths) > 0:
            new_try_paths = []
            for path in try_paths:
                if path[0] == path[-1] and len(path) >= 2:  # prime path
                    self.primePaths.append(path)
                elif self.reachEnd(path):
                    if self.reachHead(path):  # prime path
                        self.primePaths.append(path)
                else:  # extendable path
                    new_try_paths += self.extend(path)
            try_paths = new_try_paths
