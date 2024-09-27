import re

def read_file(file_name):
    with open(file_name, 'r') as file:
        return file.readlines()

def parse_commands(lines):
    commands = []
    for line in lines:
        line = line.strip()
        if not line or line.startswith('#'):
            continue
        match = re.match(r'(\w+)\.fan\.\s*(.*)', line)
        if match:
            command_type = match.group(1)
            command_body = match.group(2)
            commands.append((command_type, command_body))
    return commands

def execute_commands(commands):
    stack = []
    for command_type, command_body in commands:
        if command_type == 'fm':
            stack.append(stack[-1] - 1)
        elif command_type == 'pm':
            stack.append(stack[-1] + 1)
        elif command_type == 'data.to.stack':
            # 假设 push 是将当前值压入堆栈
            value = int(command_body.split('.')[-1])
            stack.append(value)
        elif command_type == 'stack.to.data':
            # 出栈操作
            print(f"从堆栈取出: {stack.pop()}")
        elif command_type == 'stack.to.bool':
            # 判空操作
            print(f"堆栈是否为空: {len(stack) == 0}")

if __name__ == "__main__":
    file_name = "./test_pool/exp.fan"
    lines = read_file(file_name)
    commands = parse_commands(lines)
    execute_commands(commands)