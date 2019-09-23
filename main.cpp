#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Expr {
    char operation;
    int operand;
};

int lt(char op1, char op2) {
    if((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/')) {
        return 1;
    }
    return 0;
}

int main() {
    int parenthesis = 0;
    string expression;
    int n;
    cin >> expression;
    cin >> n;
    if(n > 0) {
        vector<Expr> operations(n);
        for (int i = 0; i < n; ++i) {
            cin >> operations[i].operation >> operations[i].operand;
        }
        expression += string(" ") + operations[0].operation + " " + to_string(operations[0].operand);
        for (int i = 1; i < n; ++i) {
            if (lt(operations[i - 1].operation, operations[i].operation)) {
                parenthesis += 1;
                expression += string(") ") + operations[i].operation + " " + to_string(operations[i].operand);
            } else {
                expression += string(" ") + operations[i].operation + " " + to_string(operations[i].operand);
            }
        }
    }
    cout << string(parenthesis, '(') << expression << endl;
    return 0;
}
