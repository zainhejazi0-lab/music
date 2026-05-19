#include <stdio.h>
#include <string.h>

// دالة المحلل القواعدي (Parser) للتأكد من ترتيب الجمل الصارم
void parser(char *tokens[], int tokenCount)
{
    printf("--- Running music Language Parser 🤖 ---\n\n");

    for (int i = 0; i < tokenCount; i++)
    {

        // القواعد الصارمة لدرس البوزيشن (الدرس 5)
        if (strcmp(tokens[i], "bosishen") == 0)
        {
            // نتأكد أن الكلمة التالية هي NewLine أو underLine
            if (i + 1 < tokenCount && (strcmp(tokens[i + 1], "NewLine") == 0 || strcmp(tokens[i + 1], "underLine") == 0))
            {
                printf("[Parser Success]: Correct grammar! Position will change to: %s 📈\n", tokens[i + 1]);
                i++; // نقفز للكلمة التالية لأننا فحصناها بنجاح
            }
            else
            {
                printf("[Parser Error ❌]: Expected 'NewLine' or 'underLine' after 'bosishen'!\n");
            }
        }

        // القواعد الصارمة لدرس الهارموني (الدرس 6)
        else if (strcmp(tokens[i], "harmony") == 0)
        {
            // نتأكد أن بعد harmony هناك نوتة موسيقية ثم كلمة with ثم نوتة أخرى
            if (i + 2 < tokenCount && strcmp(tokens[i + 2], "with") == 0)
            {
                printf("[Parser Success]: Correct grammar! Harmony Chord created with: %s and %s 🎛️\n", tokens[i + 1], tokens[i + 3]);
                i += 3; // نقفز فوق كلمات الأكورد بالكامل
            }
            else
            {
                printf("[Parser Error ❌]: Incorrect harmony syntax! Use: harmony [Note] with [Note]\n");
            }
        }

        // القواعد الصارمة للنوتات الفردية العادية والكروماتيك (الدرس 1 ووحدة الكروماتيك)
        else if (strcmp(tokens[i], "Do") == 0 || strcmp(tokens[i], "Re") == 0 || strcmp(tokens[i], "Mi") == 0 || strcmp(tokens[i], "Do#") == 0)
        {
            printf("[Parser Success]: Valid single note sequence -> Ready to play: %s 🎵\n", tokens[i]);
        }
    }
}

int main()
{
    // 1. كود مرتب بشكل صحيح وصارم (مقبول)
    char *correctCode[] = {"Do", "bosishen", "NewLine", "harmony", "Do", "with", "Mi"};
    parser(correctCode, 7);

    printf("\n---------------------------------------\n\n");

    // 2. كود يحتوي على خطأ في القواعد (مرفوض)
    // هنا وضعنا كلمة Do بعد bosishen وهذا ممنوع في لغتنا!
    char *wrongCode[] = {"bosishen", "Do"};
    parser(wrongCode, 2);

    return 0;
}