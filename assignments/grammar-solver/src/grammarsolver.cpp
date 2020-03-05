/*
 * File: grammarsolver.cpp
 * --------------------------
 */

#include "grammarsolver.h"
#include "map.h"
#include "strlib.h"

using namespace std;

const string RULE_DELIMITER = "::=";
const string EXP_RULES_DELIMETER = "|";
const string RULE_PARTS_DELIMETER = " ";

/**
 * Read an input stream with a BNF grammar rules into the map.
 * Keys of the map are non-terminal in the grammar
 * and values are expansion rules for the non-terminal.
 *
 * @param input - Input stream with BNF grammar rules
 * @param rules - Output map which is supposed to gain BNF rules
 */
void readGrammar(istream& input, Map<string, Vector<string>>& rules);

/**
 * Recursively generates grammar for a given symbol until it ends up with terminal.
 *
 * @param rules - Contains BNF rules
 * @param symbol - Symbol to generate
 * @return string which represents random generation of the symbol
 */
string generateExpansion(const Map<string, Vector<string>>& rules, const string& symbol);

/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */
Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    Map<string, Vector<string>> rules;
    readGrammar(input, rules);

    Vector<string> res;

    for (int i = 0; i < times; i++) {
        res.add(generateExpansion(rules, symbol));
    }

    return res;
}

void readGrammar(istream& input, Map<string, Vector<string>>& rules) {
    string rule;

    while (getline(input, rule)) {
        auto ruleParts = stringSplit(rule, RULE_DELIMITER);
        auto terminals = stringSplit(ruleParts[1], EXP_RULES_DELIMETER);

        if (rules.containsKey(ruleParts[0])) {
            throw "invalid grammar format: the same non-terminal occurs several times";
        }

        rules.add(ruleParts[0], terminals);
    }
}

string generateExpansion(const Map<string, Vector<string>>& rules, const string& symbol) {
    string res;

    if (!rules.containsKey(symbol)) {
        return symbol;
    } else {
        Vector<string> expRules = rules[symbol];
        int expRuleIndex = randomInteger(0, expRules.size() - 1);
        auto ruleParts = stringSplit(expRules[expRuleIndex], RULE_PARTS_DELIMETER);

        for (string part: ruleParts) {
            res += (generateExpansion(rules, part) + " ");
        }
    }

    return trim(res);
}
