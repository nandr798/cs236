#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Lexer.h"
#include "Token.h"
using namespace std;

int main(int argc, char* argv[]){
    VS_MEM_CHECK

    Lexer lexer;
    string inputFile;
    string line;
    stringstream ss;
    ifstream in(argv[1]);
    
//    cout << argv[1] << endl;
    if (!in){
        cerr << "Unable to open " << argv[1] << " for input" << endl;
        return 2;
    }
    //stringstream theString;
    /*for(string line; getline(in, line);){
        theString << line << endl;
    }*/

    while(getline(in, line))
    {
//        cout << line << endl;
        ss << line << endl;
    }
    vector<Token*> tokens = lexer.Run(ss.str());

    for (unsigned int i = 0; i < tokens.size(); i++)
    {
        cout << tokens.at(i)->toString() << endl;
    }
    cout << "Total Tokens = " << tokens.size() << endl;
    
    /*
    for (unsigned int i = 0; i < tokens.size(); i++)
    {
        delete tokens.at(i);
    }
    */

    return 0;
}
