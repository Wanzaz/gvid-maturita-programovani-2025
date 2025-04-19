#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* Je dáno Σ={a}, N={S, A, B, C}. Pravidlo gramatiky má tvar „řetězec->řetězec“. */
/* Napiš funkci, která ověří, zda zadaný řetězec je */
/* ◦ pravidlem gramatiky typu 3 */
/* ◦ pravidlem gramatiky typu 2 */
/* ◦ Napiš funkci, která bude systematicky generovat prvních N vět jazyka zadaného */
/*     gramatickými pravidly S->aA, A->bB, B->cA, B->c. Zapiš tyto věty na samo- */
/*     statné řádky výstupu. */



#define MAX_RULE_LEN 50

typedef struct {
    char lhs[MAX_RULE_LEN]; // levá strana pravidla
    char rhs[MAX_RULE_LEN]; // pravá strana pravidla
} GrammarRule;


// Vrací 1, pokud je znak neterminál (velké písmeno A–Z)
int isNonTerminal(char c) {
    return c >= 'A' && c <= 'Z';
}

// Vrací 1, pokud je pravidlo typu 2 (levá strana = 1 neterminál)
int isType2Rule(GrammarRule rule) {
    return strlen(rule.lhs) == 1 && isNonTerminal(rule.lhs[0]);
}

// Parsuje pravidlo ve formátu "X->abc" do struktury GrammarRule
int parseRule(const char* input, GrammarRule* rule) {
    const char* arrow = strstr(input, "->");
    if (!arrow) {
        return 0; // Chybí '->'
    }

    int lhsLen = arrow - input;
    if (lhsLen >= MAX_RULE_LEN) return 0;

    strncpy(rule->lhs, input, lhsLen);
    rule->lhs[lhsLen] = '\0';

    strncpy(rule->rhs, arrow + 2, MAX_RULE_LEN - 1);
    rule->rhs[MAX_RULE_LEN - 1] = '\0';

    return 1;
}


int main(int argc, char *argv[])
{
        const char* testRules[] = {
        "S->aA",
        "A->bB",
        "B->cA",
        "B->c",
        "AB->a",   // neplatné pro typ 2
        "a->A",    // neplatné pro typ 2
        "X->",     // ε je platné pro typ 2
    };

    int numRules = sizeof(testRules) / sizeof(testRules[0]);

    printf("=== Ověření pravidel typu 2 ===\n\n");

    for (int i = 0; i < numRules; i++) {
        GrammarRule rule;
        if (!parseRule(testRules[i], &rule)) {
            printf("Pravidlo \"%s\" je ve špatném formátu (chybí '->')\n", testRules[i]);
            continue;
        }

        if (isType2Rule(rule)) {
            printf("Pravidlo \"%s\" JE typu 2 (bezkontextová gramatika)\n", testRules[i]);
        } else {
            printf("Pravidlo \"%s\" NENÍ typu 2 (levá strana není jeden neterminál)\n", testRules[i]);
        }
    }

    return 0;
}
