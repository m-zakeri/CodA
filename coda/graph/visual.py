import html

import graphviz as gv

from coda.antlr_gen.rule_utils import extract_exact_text
from coda.graph.utils import head_node, last_node


def build_node_template(node_label, node_contents):
    return f"""<
     <TABLE BORDER="0" CELLBORDER="1" CELLSPACING="0">
     <tr>
        <td width="30" height="20" fixedsize="true">{node_label}</td>
        <td width="9" height="9" fixedsize="true" style="invis" PORT="there"></td>
        <td width="9" height="9" fixedsize="true" style="invis"></td>
     </tr>
     <tr>
         <td width="30" height="30" fixedsize="true" sides="tlb"></td>
         <td width="50" height="30" fixedsize="false" sides="bt" PORT="here">{html.escape(str(node_contents))}</td>
         <td width="30" height="30" fixedsize="true" sides="brt"></td>
     </tr>
    </TABLE>
    >"""


def draw_CFG(graph, filename, token_stream, format="png"):
    gr = gv.Digraph(comment=filename, format=format, node_attr={"shape": "none"})
    gr.node("start", style="filled", fillcolor="#aaffaa", shape="oval")

    for node, args in list(graph.nodes.data())[:-1]:
        block_contents = stringify_block(token_stream, args)
        gr.node(str(node), label=build_node_template(node, block_contents))
    gr.node(str(last_node(graph)), label="end", style="filled", fillcolor="#ffaaaa", shape="oval")

    for f, t, args in graph.edges.data():
        gr.edge(str(f), str(t), label=args.get("state"))
    gr.edge("start", str(head_node(graph)))

    gr.render(f"{filename}.gv", view=True)


def stringify_block(token_stream, node_args):
    return [(rule.start.line, extract_exact_text(token_stream, rule)) for rule in node_args["data"]]
