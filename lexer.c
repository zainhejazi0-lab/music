#include <stdio.h>
#include <string.h>

// Lexer function to analyze the music code word by word
void analyzeMusicCode(char *code)
{
    // Split the code by spaces or newlines
    char *word = strtok(code, " \n");

    while (word != NULL)
    {

        // --- Lesson 1: Notes ---
        if (strcmp(word, "Do") == 0 || strcmp(word, "Re") == 0 || strcmp(word, "Mi") == 0 ||
            strcmp(word, "Fa") == 0 || strcmp(word, "So") == 0 || strcmp(word, "La") == 0 ||
            strcmp(word, "Fi") == 0)
        {
            printf("[Lesson 1]: %s -> Pure Musical Note 🎵\n", word);
        }

        // --- Lesson 2: Loops & Restart ---
        else if (strcmp(word, "for") == 0 || strcmp(word, "music") == 0 || strcmp(word, "Restart") == 0)
        {
            printf("[Lesson 2]: %s -> Loop & Backtrack Command 🔄\n", word);
        }

        // --- Lesson 3: Functions, Chromatik & CSS ---
        else if (strcmp(word, "functions") == 0 || strcmp(word, "cromatik") == 0 || strcmp(word, "CSS") == 0)
        {
            printf("[Lesson 3]: %s -> Filter & Aesthetic Design 🎨\n", word);
        }

        // --- Lesson 4: Arrays ---
        else if (strcmp(word, "array") == 0)
        {
            printf("[Lesson 4]: %s -> Notes Container Array 📂\n", word);
        }

        // --- Lesson 5: Position ---
        else if (strcmp(word, "bosishen") == 0 || strcmp(word, "NewLine") == 0 || strcmp(word, "underLine") == 0)
        {
            printf("[Lesson 5]: %s -> Staff Position Adjustment 📈📉\n", word);
        }

        // --- Lesson 6: Harmony ---
        else if (strcmp(word, "harmony") == 0 || strcmp(word, "with") == 0)
        {
            printf("[Lesson 6]: %s -> Simultaneous Playback Chord 🎛️\n", word);
        }

        // --- Condition Lesson ---
        else if (strcmp(word, "check") == 0 || strcmp(word, "otherwise") == 0)
        {
            printf("[Conditions]: %s -> Smart Decision Logical Check ⚖️\n", word);
        }

        // --- Chromatic Unit (Sharp & Flat) ---
        else if (strcmp(word, "Do#") == 0 || strcmp(word, "Fa#") == 0 || strcmp(word, "Reb") == 0)
        {
            printf("[Chromatic]: %s -> Black Key (Sharp/Flat) ⚡\n", word);
        }

        // Error handling for strict rules
        else
        {
            printf("[Syntax Error ❌]: %s -> Unknown Symbol in music language!\n", word);
        }

        // Move to the next word
        word = strtok(NULL, " \n");
    }
}

int main()
{
    // Test code with all our lessons combined
    char myCode[] = "Do for functions array bosishen harmony check Do# ErrorWord";

    printf("--- Running music Language Compiler Lexer 🤖 ---\n\n");
    analyzeMusicCode(myCode);

    return 0;
}