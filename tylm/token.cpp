#include <iostream>
#include <cstring>
#include <string>
#include <vector>

// 定义 TokenType 枚举，用于表示不同的词法单元类型
enum TokenType
{
    IDENTIFIER,   // 标识符
    NUMBER,       // 数字
    OPERATOR,     // 运算符
    KEYWORD,      // 关键字
    EOF_TOKEN     // 文件结束标记
};

// 定义 Token 结构体，存储词法单元的信息
struct Token
{
    TokenType type;          // 词法单元类型
    std::string value;       // 词法单元值
    int line_number;         // 当前词法单元所在的行号

    // 构造函数
    Token(TokenType t, const std::string& v, int ln) : type(t), value(v), line_number(ln) {}
};

// 词法分析器类
class Lexer
{
public:
    // 构造函数
    Lexer(const std::string& input) : input(input), pos(0), current_line(1) {}

    // tokenize 函数，进行词法分析并返回词法单元列表
    std::vector<Token> tokenize()
    {
        std::vector<Token> tokens; // 存储词法单元的向量
        while (pos < input.size()) // 遍历输入字符串
        {
            skipWhitespace();      // 忽略空白字符
            if (isAlpha(input[pos])) // 如果当前字符为字母或下划线，则读取标识符
            {
                tokens.push_back(readIdentifier());
            }
            else if (isdigit(input[pos])) // 如果当前字符为数字，则读取数字
            {
                tokens.push_back(readNumber());
            }
            else if (isOperator(input[pos])) // 如果当前字符为运算符，则读取运算符
            {
                tokens.push_back(readOperator());
            }
            else if (input[pos] == '/') // 处理注释
            {
                if (input[pos + 1] == '/')
                {
                    readLineComment(); // 行注释
                }
                else if (input[pos + 1] == '*')
                {
                    readBlockComment(); // 块注释
                }
                else
                {
                    tokens.push_back(Token(OPERATOR, "/", current_line)); // 单个斜杠作为运算符
                }
            }
            else // 其他符号
            {
                tokens.push_back(Token(OPERATOR, std::string(1, input[pos]), current_line));
            }
        }
        tokens.push_back(Token(EOF_TOKEN, "", current_line)); // 添加文件结束标记
        return tokens;
    }

private:
    std::string input;          // 输入字符串
    size_t pos;                 // 当前位置指针
    int current_line;           // 当前行号

    // 忽略空白字符
    void skipWhitespace()
    {
        while (pos < input.size() && isspace(input[pos]))
        {
            if (input[pos] == '\n')
            {
                current_line++; // 换行时行号增加
            }
            pos++;
        }
    }

    // 判断是否为字母或下划线
    bool isAlpha(char c)
    {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    }

    // 判断是否为运算符
    bool isOperator(char c)
    {
        return strchr("+-*/%<>=!&|", c) != nullptr;
    }

    // 读取标识符
    Token readIdentifier()
    {
        size_t start = pos;
        while (pos < input.size() && (isAlpha(input[pos]) || isdigit(input[pos])))
        {
            pos++;
        }
        std::string identifier = input.substr(start, pos - start);
        return Token(IDENTIFIER, identifier, current_line);
    }

    // 读取数字
    Token readNumber()
    {
        size_t start = pos;
        while (pos < input.size() && isdigit(input[pos]))
        {
            pos++;
        }
        std::string number = input.substr(start, pos - start);
        return Token(NUMBER, number, current_line);
    }

    // 读取运算符
    Token readOperator()
    {
        size_t start = pos;
        pos++;
        std::string op = input.substr(start, pos - start);
        return Token(OPERATOR, op, current_line);
    }

    // 读取行注释
    void readLineComment()
    {
        pos += 2; // 跳过 "//"
        while (pos < input.size() && input[pos] != '\n')
        {
            pos++;
        }
        if (input[pos] == '\n')
        {
            current_line++; // 换行时行号增加
        }
        pos++;
    }

    // 读取块注释
    void readBlockComment()
    {
        pos += 2; // 跳过 "/*"
        while (pos + 1 < input.size() && !(input[pos] == '*' && input[pos + 1] == '/'))
        {
            if (input[pos] == '\n')
            {
                current_line++; // 换行时行号增加
            }
            pos++;
        }
        if (pos + 1 < input.size())
        {
            pos += 2; // 跳过 "*/"
        }
    }
};

// 主函数
int main()
{
    // 测试输入字符串
    std::string input = "int x = 5; // This is a comment\n"
                        "/* This is a block comment */\n"
                        "x = x + 3;";
    Lexer lexer(input); // 创建词法分析器对象
    std::vector<Token> tokens = lexer.tokenize(); // 进行词法分析

    // 输出词法单元信息
    for (const auto& token : tokens)
    {
        std::cout << "Type: " << token.type << ", Value: " << token.value << ", Line: " << token.line_number << std::endl;
    }

    return 0;
}