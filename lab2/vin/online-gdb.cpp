/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <map>
#include <algorithm>

using namespace std;

static const vector<string> OPERATORS = {
  "(", ")", "+", "-", "*", "/", "%"
};

static const map<string, int> OPERATOR_PRECEDENCES = {
    {"*", 2},
    {"/", 2},
    {"%", 2},
    {"+", 1},
    {"-", 1}
};

static const string INVALID_INFIX_EXPRESSION = "invalid infix expression";

static const string INVALID_POSTFIX_EXPRESSION = "invalid postfix expression";

int infixOperatorPrecedence(string op) {
  map<string, int> opPrecedences = {
    {"*", 2},
    {"/", 2},
    {"%", 2},
    {"+", 1},
    {"-", 1}
  };
  if (opPrecedences.find(op) != opPrecedences.end()) {
    return opPrecedences[op];
  }
  // By default, no prcedence
  return 0;
}


bool isTokenInt(string input) {
  // https://stackoverflow.com/a/16575025/1979008
  char* p;
  // parameters are string as c string, endprt char pointer p, and the base,  10
  strtol(input.c_str(), &p, 10);
  
  return *p == NULL;
}

void addToPostfix(stringstream &postfix, string &op) {
  postfix << op << " ";
}

bool isTokenOperator(string &token) {
  return find(OPERATORS.begin(), OPERATORS.end(), token) != OPERATORS.end();
}

void popStackToPostfix(stringstream &postfix, stack<string> &opStack) {
  addToPostfix(postfix, opStack.top());
  opStack.pop();
}

bool processInfixOperator(stack<string> &opStack, stringstream &postfix, string &op) {
  if (opStack.empty() || opStack.top() == "(" || op == "(") {
    opStack.push(op);
  } else if (op == ")") {
    while (opStack.top() != "(") {
      popStackToPostfix(postfix, opStack);
      if (opStack.empty()) {
        return false;
      }
    }
    // Didn't return false so character must be parenthesis;
    // pop it
    opStack.pop();
  } else {
    int opPrecedence = infixOperatorPrecedence(op);

    while (opPrecedence <= infixOperatorPrecedence(opStack.top())) {
      popStackToPostfix(postfix, opStack);
      if (opStack.empty()) {
        break;
      }
    }

    opStack.push(op);
  }
  // Return true by default
  return true;
}

string infixToPostfix(string infixExpression) {
  stringstream postfix;
  stack<string> operators;
  vector<string> tokens;
  stringstream tokenStream(infixExpression);

  string streamToken;

  // Use stringstream to split with spaces
  while(getline(tokenStream, streamToken, ' ')) {
    tokens.push_back(streamToken);
    // TODO: IT MIGHT NOT BE NECESSARY TO CREATE A VECTOR;
    // WE MIGHT JUST BE ABLE TO DO WHAT WE NEED TO RIGHT
    // FROM THE STRINGSTREAM
  }

  for (auto token : tokens) {
    if (isTokenInt(token)) {
      addToPostfix(postfix, token);
    } else if (isTokenOperator(token)) {
      bool processOperatorSuccess = processInfixOperator(operators, postfix, token);
      if (!processOperatorSuccess) {
        cout << "invalid: " << infixExpression << endl;
        return INVALID_INFIX_EXPRESSION;
      }
    } else {
      cout << "invalid: " << infixExpression << endl;
      return INVALID_INFIX_EXPRESSION;
    }
  }

  while(!operators.empty()) {
    popStackToPostfix(postfix, operators);
  }

  string postfixString = postfix.str();
  // Remove trailing space
  postfixString = postfixString.substr(0, postfixString.size() - 1);

  // TODO: Make sure this works when Jacob gets postfixEvaluate working
  // if (!postfixEvaluate(postfixString)) {
  //   throw INVALID_POSTFIX_EXPRESSION:
  // }

  return postfixString;
}

int main()
{

  cout << infixToPostfix("4 * ( 2 + 4 - ( 2 + )  ) - 4 / 5") <<  endl;
  cout << infixOperatorPrecedence("a") << endl;
  return 0;
}
