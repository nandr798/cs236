#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <cctype>
#include <iostream>
#include "Token.h"
#include "Automaton.h"
//#include "MatcherAutomaton.h"
#include <vector>

//using namespace std;

class Lexer{
public:
    unsigned int lineNumber;
    unsigned int maxRead;
    unsigned int inputRead;
    unsigned int maxNewLines;
    string input;
    Automaton* maxMachine;
    vector<Token*> tokens;
    vector<Automaton*> machines;
    //something to do with the matcherautomaton
    Lexer(){
        machines.push_back(new MatcherAutomaton(",",COMMA));
        machines.push_back(new MatcherAutomaton(".",PERIOD));
        machines.push_back(new MatcherAutomaton("?",Q_MARK));
        machines.push_back(new MatcherAutomaton("(",LEFT_PAREN));
        machines.push_back(new MatcherAutomaton(")",RIGHT_PAREN));
        machines.push_back(new MatcherAutomaton(":",COLON));
        machines.push_back(new MatcherAutomaton(":-",COLON_DASH));
        machines.push_back(new MatcherAutomaton("*",MULTIPLY));
        machines.push_back(new MatcherAutomaton("Schemes",SCHEMES));
        machines.push_back(new MatcherAutomaton("Facts",FACTS));
        machines.push_back(new MatcherAutomaton("Rules",RULES));
        machines.push_back(new MatcherAutomaton("Queries",QUERIES));
        machines.push_back(new CommentAutomaton());
        machines.push_back(new StringAutomaton());
        machines.push_back(new ID());
    };
    
    virtual ~Lexer(){
        for(unsigned int i = 0; i < machines.size(); i++){
            delete machines.at(i);
        }
        for(unsigned int i = 0; i < tokens.size(); i++){
            delete tokens.at(i);
        }
    }
    
    vector<Token*> Run(string input){
        lineNumber = 1;
        while (input.size() > 0){
            while(isspace(input.at(0))){
                if(input.at(0) == '\n'){
                    lineNumber++;
                }
                input.erase(0, 1);
                if(input.size() == 0){
                    Token* newToken= new Token(END_OF_FILE, input, lineNumber);
                    tokens.push_back(newToken);
                    return tokens;
                }
            }
            maxRead = 0;
            maxMachine = machines.at(0);
            for (unsigned int i = 0; i < machines.size(); i++){
                inputRead = machines[i]->Read(input);
                if (inputRead > maxRead){
                    maxRead = inputRead;
                    maxMachine = machines.at(i);
                    maxNewLines = machines.at(i)->NewLinesRead();
                }
            }
            if (maxRead > 0){
                string temp = input.substr(0, maxRead);
                Token* newToken = maxMachine->CreateToken(temp, lineNumber);
                lineNumber += maxNewLines;
                tokens.push_back(newToken);
            }
            else if (input == ""){}
            else{
                
                maxRead = 1;
                string temp = input.substr(0, maxRead);
                Token* newToken = new Token(UNDEFINED, temp, lineNumber);
                tokens.push_back(newToken);
            }
            input.erase(0, maxRead);
        }
        Token* newToken = new Token(END_OF_FILE, input, lineNumber);
        tokens.push_back(newToken);
        return tokens;
        
    }

};
    
#endif 
