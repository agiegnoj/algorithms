#include <regex>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

class FullNAND {
    
public:

    // allows multi-letter variable names 
    // operators: AND, OR, =>, <=, <=>, NOT
    //needs every binary expression to be parenthesized, even when the expression is homogenous (e.g. ((A AND B) AND C)|| (A AND (B AND C))) 
     
    string fullNAND(string logicalExpression) {
        if (balancedParentheses(logicalExpression))
        replaceExpressions(logicalExpression);
        return logicalExpression;
    }

    void replaceExpressions(string& logicalExpression) {
        unordered_map<string, string> nandMap;
        int nandCount = 1;

        auto replaceAndStore = [&](const regex& pattern, const string& replacement) {
            smatch match;
            while (regex_search(logicalExpression, match, pattern)) {
                string identifier =  "IDENT" + to_string(nandCount++);
                nandMap[identifier] = regex_replace(match.str(), pattern, replacement);
                logicalExpression = match.prefix().str() + identifier + match.suffix().str();
            }
        };

        replaceAndStore(regex("NOT\\s*(\\w+)", regex_constants::icase),  "($1 NAND $1)");
        replaceAndStore(regex(R"(\((\w+)\s*AND\s*(\w+)\))", regex_constants::icase), "(($1 NAND $2) NAND ($1 NAND $2))");
        replaceAndStore(regex(R"(\((\w+)\s*OR\s*(\w+)\))", regex_constants::icase), "(($1 NAND $1) NAND ($2 NAND $2))");
        replaceAndStore(regex(R"(\((\w+)\s*XOR\s*(\w+)\))", regex_constants::icase), "(($1 NAND ($2 NAND $2)) NAND (($1 NAND $1) NAND $2))");
        replaceAndStore(regex(R"(\((\w+)\s*<=>\s*(\w+)\))", regex_constants::icase), "(($1 NAND $2) NAND (($1 NAND $1) NAND ($2 NAND $2)))");
        replaceAndStore(regex(R"(\((\w+)\s*<=\s*(\w+)\))", regex_constants::icase), "(($1 NAND $1) NAND $2)");
        replaceAndStore(regex(R"(\((\w+)\s*=>\s*(\w+)\))", regex_constants::icase), "($1 NAND ($2 NAND $2))");
        

        for (auto it = nandMap.begin(); it != nandMap.end(); it++) {
            logicalExpression = regex_replace(logicalExpression, regex(it->first), it->second);
        }
    }

    private:
    
    bool balancedParentheses(string& s){

        s.insert(s.begin(), '(');
        s.push_back(')');

        stack <char> st;

        for (char c : s){
            if (c == '('){
                st.push(c);
            }else if (c == ')'){
                if (st.empty())
                return false;
                st.pop();
            }
        }
        return st.empty();
    }
};




