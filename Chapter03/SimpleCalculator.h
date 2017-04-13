#ifndef DS_CH03_SIMPLECALCULATOR_H
#define DS_CH03_SIMPLECALCULATOR_H

#include <string>
using std::string;

#include "Vector.h"
#include "Stack.h"

class SimpleCalculator {
public:
    SimpleCalculator() = default;
    explicit SimpleCalculator(const string &s) { _rpn = toRPN(s); }
    SimpleCalculator(const SimpleCalculator &rhs) = delete;
    ~SimpleCalculator() = default;

public:
    double calcu(const string &s)
    {
        Vector<string> rpn = toRPN(s);
        double d = 0.0, d1 = 0.0, d2 = 0.0;
        LinkStack<double> dstk;
        string strT;

        for (auto it = rpn.begin(); it != rpn.end(); ++it) {
            strT = *it;
            if (isdigit(strT[0])) {
                dstk.push(std::stod(strT));
            } else {
                d1 = dstk.top();
                dstk.pop();
                d2 = dstk.top();
                dstk.pop();

                if (strT == "+") {
                    d = d2 + d1;
                } else if (strT == "-") {
                    d = d2 - d1;
                } else if (strT == "*") {
                    d = d2 * d1;
                } else if (strT == "/") {
                    d = d2 / d1;
                }

                dstk.push(d);
            }
        }
        return dstk.top();
    }
    double getResult()
    {
        double d = 0.0, d1 = 0.0, d2 = 0.0;
        LinkStack<double> dstk;
        string strT;

        for (auto it = _rpn.begin(); it != _rpn.end(); ++it) {
            strT = *it;
            if (isdigit(strT[0])) {
                dstk.push(std::stod(strT));
            } else {
                d1 = dstk.top();
                dstk.pop();
                d2 = dstk.top();
                dstk.pop();

                if (strT == "+") {
                    d = d2 + d1;
                } else if (strT == "-") {
                    d = d2 - d1;
                } else if (strT == "*") {
                    d = d2 * d1;
                } else if (strT == "/") {
                    d = d2 / d1;
                }

                dstk.push(d);
            }
        }
        return dstk.top();
    }

private:
    const Vector<string> toRPN(const string &s)
    {
        Vector<string> vec;
        LinkStack<char> opStk;
        char tch[2] = { 0 };

        for (auto it = s.cbegin(); it != s.cend(); ++it) {
            if (isdigit(*it)) {
                auto tit = it;
                while (isdigit(*tit))
                    ++tit;
                vec.push_back(string(it, tit));
                it = --tit;
            } else {
                switch (*it) {
                case '(':
                    opStk.push(*it);
                    break;
                case ')':
                    tch[0] = opStk.top();
                    while (tch[0] != '(') {
                        vec.push_back(string(tch));
                        opStk.pop();
                        tch[0] = opStk.top();
                    }
                    opStk.pop();
                    break;
                case '+':
                case '-':
                    while (!opStk.empty()) {
                        tch[0] = opStk.top();
                        if (tch[0] == '(')
                            break;
                        opStk.pop();
                        vec.push_back(string(tch));
                    }
                    opStk.push(*it);
                    break;
                case '*':
                case '/':
                    while (!opStk.empty()) {
                        tch[0] = opStk.top();
                        if (tch[0] == '(' || tch[0] == '+' || tch[0] == '-')
                            break;
                        opStk.pop();
                        vec.push_back(string(tch));
                    }
                    opStk.push(*it);
                    break;
                default:
                    break;
                }
            }
        }
        while (!opStk.empty()) {
            tch[0] = opStk.top();
            opStk.pop();
            vec.push_back(string(tch));
        }
        return vec;
    }
    int priority(const char &ch)
    {
        switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
            return 3;
        default:
            break;
        }
        return -1;
    }

private:
    Vector<string> _rpn;
};

#endif // DS_CH03_SIMPLECALCULATOR_H
