#ifndef header_h
#define header_h
#include <iostream>

using namespace std;

enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID_, STRING, COMMENT, UNDEFINED, END_OF_FILE};


class Token{
public:
    TokenType type;
    Token(){};
    Token(TokenType type_, string theValue, int theStart){
        type = type_;
        actualValue = theValue;
        lineNumberStart = theStart;
    }
    string actualValue;
    int lineNumberStart;
    void setLineNumber(int line){
        lineNumberStart = line;
    }

    string tokenSwitch(TokenType type) {
        switch (type) {
            case COMMA: return "COMMA"; break;
            case PERIOD: return "PERIOD"; break;
            case Q_MARK: return "Q_MARK"; break;
            case LEFT_PAREN: return "LEFT_PAREN"; break;
            case RIGHT_PAREN: return "RIGHT_PAREN"; break;
            case COLON: return "COLON"; break;
            case COLON_DASH: return "COLON_DASH"; break;
            case MULTIPLY: return "MULTIPLY"; break;
            case ADD: return "ADD"; break;
            case SCHEMES: return "SCHEMES"; break;
            case FACTS: return "FACTS"; break;
            case RULES: return "RULES"; break;
            case QUERIES: return "QUERIES"; break;
            case ID_: return "ID"; break;
            case STRING: return "STRING"; break;
            case COMMENT: return "COMMENT"; break;
            case UNDEFINED: return "UNDEFINED"; break;
            case END_OF_FILE: return "EOF"; break;
            default: return "UNDEFINED"; break;
    }
    }
        string GetTheName(TokenType type) const{
            switch(type){
                case COMMA:
                    return "COMMA";
                    break;
                case PERIOD:
                    return "PERIOD";
                    break;
                case Q_MARK:
                    return "Q_MARK";
                    break;
                case LEFT_PAREN:
                    return "LEFT_PAREN";
                    break;
                case RIGHT_PAREN:
                    return "RIGHT_PAREN";
                    break;
                case COLON:
                    return "COLON";
                    break;
                case COLON_DASH:
                    return "COLON_DASH";
                    break;
                case MULTIPLY:
                    return "MULTIPLY";
                    break;
                case ADD:
                    return "ADD";
                    break;
                case SCHEMES:
                    return "SCHEMES";
                    break;
                case FACTS:
                    return "FACTS";
                    break;
                case RULES:
                    return "RULES";
                    break;
                case QUERIES:
                    return "QUERIES";
                    break;
                case ID_:
                    return "ID";
                    break;
                case STRING:
                    return "STRING";
                    break;
                case COMMENT:
                    return "COMMENT";
                    break;
                case UNDEFINED:
                    return "UNDEFINED";
                    break;
                case END_OF_FILE:
                    return "End_Of_FILE";
                    break;
                default:
                    return "UNDEFINED";
                    break;
                    
            
        }
    return "ERROR"; // a string MUST be returned by the end
    }
    string toString(){
        ostringstream os;
        os << "(" << tokenSwitch(type) << "," << "\"" << actualValue <<  "\"," << lineNumberStart << ")";
        return os.str();
    }
};
#endif 
