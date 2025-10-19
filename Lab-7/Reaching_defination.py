import networkx as nx
import pydot
import re
import csv

def load_cfg(dot_path):
    G = nx.DiGraph(nx.nx_pydot.read_dot(dot_path))
    edges = [(u, v) for u, v, _ in G.edges(data=True)]
    return G, edges

def extract_definitions(G):
    definitions = {}
    def_map = {}
    counter = 1
    for node in G.nodes:
        label = G.nodes[node].get("label", "")
        defs = re.findall(r'\b([a-zA-Z_]\w*)\s*=\s*[^=]', label)
        gen = []
        for d in defs:
            def_label = f"D{counter}"
            def_map[def_label] = d
            gen.append(def_label)
            counter += 1
        definitions[node] = gen
    return definitions, def_map

def compute_kill_sets(definitions, def_map):
    kill_sets = {}
    for n in definitions:
        kill = set()
        for d in definitions[n]:
            var = def_map[d]
            for other_node, defs in definitions.items():
                if other_node != n:
                    for other_d in defs:
                        if def_map[other_d] == var:
                            kill.add(other_d)
        kill_sets[n] = kill
    return kill_sets

def reaching_definitions(G, edges, gen_sets, kill_sets):
    in_sets = {n: set() for n in G.nodes}
    out_sets = {n: set(gen_sets[n]) for n in G.nodes}
    changed = True
    while changed:
        changed = False
        for node in G.nodes:
            preds = [u for u, v in edges if v == node]
            new_in = set().union(*[out_sets[p] for p in preds]) if preds else set()
            new_out = (new_in - kill_sets[node]).union(gen_sets[node])
            if new_in != in_sets[node] or new_out != out_sets[node]:
                in_sets[node] = new_in
                out_sets[node] = new_out
                changed = True
    return in_sets, out_sets

def clean_var(var):
    return var[1:] if var.startswith('n') else var

def clean_set(var_set):
    return ", ".join(sorted([clean_var(v) for v in var_set])) if var_set else "-"

def save_to_csv(in_sets, out_sets, gen_sets, kill_sets, def_map, filename="s.csv"):
    with open(filename, "w", newline="") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["Node", "GEN", "KILL", "IN", "OUT"])
        for node in in_sets:
            writer.writerow([
                node,
                clean_set(gen_sets[node]),
                clean_set(kill_sets[node]),
                clean_set(in_sets[node]),
                clean_set(out_sets[node])
            ])
        writer.writerow([])
        writer.writerow(["Definition Mapping"])
        for d, var in def_map.items():
            writer.writerow([d, clean_var(var)])
    print(f"\n✅ Reaching definitions table saved as '{filename}'")

def run_reaching_definitions(dot_path):
    G, edges = load_cfg(dot_path)
    gen_sets, def_map = extract_definitions(G)
    kill_sets = compute_kill_sets(gen_sets, def_map)
    in_sets, out_sets = reaching_definitions(G, edges, gen_sets, kill_sets)
    save_to_csv(in_sets, out_sets, gen_sets, kill_sets, def_map)

if __name__ == "__main__":
    dot_file = r"C:\Users\HP\student_grades_cfg.dot"
    run_reaching_definitions(dot_file)
