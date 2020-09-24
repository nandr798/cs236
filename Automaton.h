#ifndef Automaton_h
#define Automaton_h
#include "Token.h"
#include <iostream>

using namespace std;

class Automaton{
protected:
    unsigned int newLines = 0;
    
public:
    Automaton(){}
    virtual ~Automaton(){};
    Automaton(TokenType type_) { type = type_; }
    virtual unsigned int Read(const std::string& input) = 0;
    virtual Token* CreateToken(std::string input, unsigned int lineNumber) {
                return new Token(type, input, lineNumber);
    }
    virtual unsigned int NewLinesRead() const { return newLines; }
    TokenType type;
};

class MatcherAutomaton : public Automaton{
private:
    string toMatch;
public:
    unsigned int Read(const string& input) {
        bool isMatch = true;
        unsigned int inputRead = 0;
        for (unsigned int i = 0; i < (unsigned int)toMatch.size() && isMatch; i++) {
            if (input[i] != toMatch[i]) {
                isMatch = false;
            }
        }
        if (isMatch) {
            inputRead = static_cast<unsigned int>(toMatch.size());
        }
            return inputRead;
        }
    MatcherAutomaton(){};
    MatcherAutomaton(string toMatch, TokenType tokenType) : Automaton(tokenType), toMatch(toMatch){};
};

class StringAutomaton : public Automaton
{
public:
    StringAutomaton() : Automaton(STRING) {}
    unsigned int Read(const string& input)
    {
        newLines = 0;
        unsigned int inputRead = 0;
        if (input.at(0) != '\'') return 0;
        inputRead++;
        bool isPair = false;
        unsigned int q = 0;
        do
        {
            switch (q)
            {
            case 0:
                while (input.at(inputRead) != '\'')
                {
                    if (input.at(inputRead) == '\n') newLines++;
                    inputRead++;
                    if (inputRead + 1 > input.size())
                    {
                        type = UNDEFINED;
                        return inputRead;
                    }
                }
                q = 1;
                break;
            case 1:
                while (input.at(inputRead) == '\'')
                {
                    isPair = !isPair;
                    inputRead++;
                    if (inputRead + 1 > input.size())
                    {
                        type = UNDEFINED;
                        return inputRead;
                    }
                }
                if (isPair) return inputRead;
                else q = 2;
                break;
            case 2:
                //if (input.at(inputRead) == '\n') newLines++;
                q = 0;
                break;
            case 3:
                return inputRead;
            }
        } while (inputRead < input.size());
        type = UNDEFINED;
        return inputRead;
        
        /*
        bool isPair = false;
        while (inputRead < input.size() - 1)
        {
            inputRead++;
            if (input.at(inputRead) == '\'')
            {
                isPair = !isPair;

                if (inputRead + 1 < input.size() && input.at(inputRead + 1) != '\'')
                {
                    return inputRead + 1;
                }

            }

            else
            {
                isPair = !isPair;
                inputRead++;
            }

            if (input.at(inputRead - 1) == '\n') newLines++;
        }

        if (!isPair) type = UNDEFINED;
        */
    }
};


/*class StringAutomaton : public Automaton{
public:
    StringAutomaton() : Automaton(STRING) {};
    int Read(const string& input){
        newLines = 0;
        unsigned int inputRead = 0;
        if(input.at(0) != '\''){return 0;}
        inputRead++;
        bool thePair = false;
        unsigned int number = 0;
       
        do{
            switch(number){
                case 0:
                    while(input.at(inputRead) != '\''){
                        if(input.at(inputRead) == '\n')newLines++;
                            inputRead++;
                        if(inputRead + 1 > input.size()){
                            type = UNDEFINED;
                            return inputRead;
                        }
                        inputRead++;
                    }
                    number = 1;
                    break;
                case 1:
                    while(input.at(inputRead) == '\''){
                        thePair = !thePair;
                        inputRead++;
                        if(inputRead + 1 > input.size()){
                            type = UNDEFINED;
                            return inputRead;
                        }
                    }
                    if(thePair) return inputRead;
                    else number = 2;
                    break;
                case 2:
                    number = 0;
                    break;
                case 3:
                    return inputRead;
            }
        } while(inputRead < input.size());
        type = UNDEFINED;
        return inputRead;
}
};*/

class CommentAutomaton : public Automaton{
public:
    CommentAutomaton(): Automaton(COMMENT){}
    unsigned int Read(const string& input){
        newLines = 0;
        unsigned int inputRead = 0;
        if(input.at(inputRead) != '#')return 0;
             inputRead++;
        
        unsigned int number = 0;
        do{
            switch(number){
                case 0:
                    if(input.at(inputRead) == '|'){
                        //newLines++;
                        inputRead++;
                        number = 2;
                        break;
                    }
                    else{
                        number = 1;
                        break;
                    }
                case 1:
                    while(input.at(inputRead) != '\n'){
                        //cout << input.at(inputRead);
                        inputRead++;
                        if(inputRead >= input.size()){
                            type = UNDEFINED;
                            return inputRead;
                        }
                    }
                    return inputRead;
                case 2:
                    while(input.at(inputRead) != '|'){
                        if(input.at(inputRead) == '\n') newLines++;
                        inputRead++;
                        if(inputRead >= input.size()){
                            type = UNDEFINED;
                            return inputRead;
                        }
                    }
                    number = 3;
                    break;
                case 3: if(input.at(inputRead + 1) == '#') return inputRead + 2;
                else if(input.at(inputRead) == '\n') newLines++;
                else{
                    inputRead++;
                    number = 2;
                    break;
                }
            }
        } while (inputRead < input.size());
        type = UNDEFINED;
        return inputRead;
    }
};




class ID : public Automaton{
public:
    ID() : Automaton(ID_) {}
    unsigned  int Read(const string& input){
        newLines = 0;
        unsigned int inputRead = 0;
        if(!isalpha(input.at(inputRead))) return 0;
        inputRead++;
        while(isalnum(input.at(inputRead))){
            inputRead++;
        }
        return inputRead;
    }
};


    


#endif /* Automaton_h */
