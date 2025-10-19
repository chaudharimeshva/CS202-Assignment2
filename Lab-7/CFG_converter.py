import re
import sys

def preprocess_code(code):
    code = re.sub(r'//.*', '', code)  
    code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)  
    lines = [line.strip() for line in code.split('\n') if line.strip()]
    return lines

def find_leaders(lines):
    leaders = set()
    leaders.add(0)  
    for i, line in enumerate(lines):
        if re.search(r'\b(if|else if|else|for|while)\b', line):
            leaders.add(i)
            if i + 1 < len(lines):
                leaders.add(i + 1)
        if re.search(r'\b(return|break|continue)\b', line):
            if i + 1 < len(lines):
                leaders.add(i + 1)
    return sorted(list(leaders))

def create_basic_blocks(lines, leaders):

    blocks = []
    for i, leader in enumerate(leaders):
        start = leader
        end = leaders[i + 1] if i + 1 < len(leaders) else len(lines)
        block_lines = lines[start:end]
        blocks.append((f'B{i}', block_lines))
    return blocks

def create_edges(blocks):
    edges = []
    n = len(blocks)
    for i, (label, block) in enumerate(blocks):
        code = " ".join(block)
        if re.match(r'if\b', block[0]):
            if i + 1 < n:
                edges.append((label, blocks[i + 1][0], "true"))
            if i + 2 < n:
                edges.append((label, blocks[i + 2][0], "false"))
        elif re.match(r'(for|while)\b', block[0]):
            if i + 1 < n:
                edges.append((label, blocks[i + 1][0], "loop"))
                edges.append((blocks[i + 1][0], label, "back"))
        elif not re.search(r'\b(return|break|continue)\b', code):
            if i + 1 < n:
                edges.append((label, blocks[i + 1][0], "seq"))
    return edges

def escape_label(text, max_len=50):
    text = text.replace("\\", "\\\\").replace("\"", "\\\"")
    text = text.replace("{", "\\{").replace("}", "\\}")
    text = text.replace("<", "\\<").replace(">", "\\>")
    lines = text.split("\\n")
    wrapped_lines = []
    for line in lines:
        while len(line) > max_len:
            wrapped_lines.append(line[:max_len])
            line = line[max_len:]
        wrapped_lines.append(line)
    return "\\n".join(wrapped_lines)

def write_dot(blocks, edges, filename="cfg.dot"):
    with open(filename, "w", encoding="utf-8") as f:
        f.write("digraph CFG {\n")
        f.write("node [shape=box, style=filled, color=lightgray, fontname=Consolas];\n")
        for label, block in blocks:
            code = "\\n".join(block)
            code = escape_label(code)
            f.write(f'{label} [label="{label}:\\n{code}"];\n')
        for src, dst, typ in edges:
            f.write(f'{src} -> {dst} [label="{typ}"];\n')
        f.write("}\n")
    print(f"[+] CFG DOT file saved as {filename}")

def compute_metrics(blocks, edges):
    N = len(blocks)
    E = len(edges)
    CC = E - N + 2
    return N, E, CC

def main():
    if len(sys.argv) < 2:
        print("Usage: python cfg_generator.py <program.c>")
        sys.exit(1)

    c_file = sys.argv[1]
    output_file = c_file.replace(".c", "_cfg.dot")

    with open(c_file, "r", encoding="utf-8") as f:
        code = f.read()

    lines = preprocess_code(code)
    leaders = find_leaders(lines)
    blocks = create_basic_blocks(lines, leaders)
    edges = create_edges(blocks)
    write_dot(blocks, edges, output_file)

    N, E, CC = compute_metrics(blocks, edges)
    print(f"[+] Basic blocks: {N}")
    print(f"[+] Edges: {E}")
    print(f"[+] Cyclomatic Complexity: {CC}")

if __name__ == "__main__":
    main()
