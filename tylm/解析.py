import re

class Lexer:
    def __init__(self, input_string):
        self.input = input_string
        self.tokens = []

    def tokenize(self):
        token_patterns = [
            ('VERB', r'min\.is\.ints\.give\.int'),
            ('DEFINE', r'min\.define\.'),  # Define start
            ('BRANCH', r'branch\d+\.\.\w+\.\w+,.*'),
            ('TRUE', r'true\.\.\w+\.\w+'),
            ('FALSE', r'false\.\.\w+\.\w+'),
            ('END', r'end'),
            ('ID', r'\w+'),
            ('NUMBER', r'\d+')
        ]

        for pattern, regex in token_patterns:
            for match in re.finditer(regex, self.input):
                self.tokens.append((pattern, match.group()))

        return self.tokens

class Parser:
    def __init__(self, tokens):
        self.tokens = tokens
        self.index = 0

    def parse(self):
        if self.parse_define_verb():
            return True
        return False

    def parse_define_verb(self):
        if self.match('VERB'):
            self.consume()
            if self.match('DEFINE'):
                self.consume()
                if self.parse_branches():
                    if self.match('END'):
                        self.consume()
                        return True
        return False

    def parse_branches(self):
        while self.index < len(self.tokens):
            if self.match('BRANCH'):
                self.consume()
                if self.parse_true_branch():
                    if self.parse_false_branch():
                        continue
            else:
                break
        return True

    def parse_true_branch(self):
        if self.match('TRUE'):
            self.consume()
            return True
        return False

    def parse_false_branch(self):
        if self.match('FALSE'):
            self.consume()
            return True
        return False

    def match(self, token_type):
        if self.index < len(self.tokens) and self.tokens[self.index][0] == token_type:
            return True
        return False

    def consume(self):
        self.index += 1

    @property
    def current_token(self):
        return self.tokens[self.index]

class Interpreter:
    def __init__(self, lexer, parser):
        self.lexer = lexer
        self.parser = parser

    def interpret(self):
        tokens = self.lexer.tokenize()
        self.parser = Parser(tokens)
        if self.parser.parse():
            print("Parsing successful")
        else:
            print("Parsing failed")

def main():
    input_string = """
    # 定义最小值操作
    min.is.ints.give.int

    # 开始定义最小值操作
    min.define.
      # 定义条件分支
      branch0..ints_0.less,ints_1
      # 如果条件为真
      true..int.set.ints_0
      # 如果条件为假
      false..int.set.ints_1
    end
    """

    lexer = Lexer(input_string)
    interpreter = Interpreter(lexer, None)
    interpreter.interpret()

if __name__ == "__main__":
    main()