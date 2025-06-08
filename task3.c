#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// List of C keywords (you can expand this list)
char *keywords[] = {
    "int", "float", "char", "if", "else", "while", "for", "return", "void"
};
int isKeyword(const char *word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>';
}

int isIdentifierStart(char ch) {
    return isalpha(ch) || ch == '_';
}

int isIdentifierChar(char ch) {
    return isalnum(ch) || ch == '_';
}

int main() {
    FILE *fp;
    char ch, buffer[100];
    int i = 0;

    fp = fopen("input.c", "r");  // Input file containing code
    if (fp == NULL) {
        printf("Error: Cannot open file\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        // Handle identifiers and keywords
        if (isIdentifierStart(ch)) {
            buffer[i++] = ch;
            while ((ch = fgetc(fp)) != EOF && isIdentifierChar(ch)) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;

            if (isKeyword(buffer))
                printf("Keyword: %s\n", buffer);
            else
                printf("Identifier: %s\n", buffer);

            if (ch != EOF)
                ungetc(ch, fp);  // Push back the last read character
        }
        // Handle operators
        else if (isOperator(ch)) {
            printf("Operator: %c\n", ch);
        }
        // Ignore other characters
    }

    fclose(fp);
    return 0;
}
