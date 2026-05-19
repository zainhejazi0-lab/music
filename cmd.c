#include <windows.h>
#include <string.h>
#include <stdio.h>

#define BTN_COMPILE 101
#define TXT_CODE 102

HWND hEditCode;
HWND hButton;

// المتغير العالمي لحفظ حالة البوزيشن أثناء العزف
char currentPosition[20] = "Normal";

// دالة العزف الفيزيائي وتحويل النوتة إلى تردد بيانو حقيقي (0101) مع البوزيشن
void playPianoTone(char *note)
{
    int frequency = 0;

    if (strcmp(note, "Do") == 0)
        frequency = 261;
    else if (strcmp(note, "Do#") == 0 || strcmp(note, "Reb") == 0 || strcmp(note, "Dob") == 0)
        frequency = 277;
    else if (strcmp(note, "Re") == 0)
        frequency = 293;
    else if (strcmp(note, "Re#") == 0 || strcmp(note, "Mib") == 0)
        frequency = 311;
    else if (strcmp(note, "Mi") == 0)
        frequency = 329;
    else if (strcmp(note, "Fa") == 0)
        frequency = 349;
    else if (strcmp(note, "Fa#") == 0 || strcmp(note, "Sob") == 0 || strcmp(note, "Fab") == 0)
        frequency = 369;
    else if (strcmp(note, "So") == 0)
        frequency = 392;
    else if (strcmp(note, "So#") == 0 || strcmp(note, "Lab") == 0)
        frequency = 415;
    else if (strcmp(note, "La") == 0)
        frequency = 440;
    else if (strcmp(note, "La#") == 0 || strcmp(note, "Tib") == 0)
        frequency = 466;
    else if (strcmp(note, "Fi") == 0)
        frequency = 493;

    if (frequency > 0)
    {
        if (strcmp(currentPosition, "NewLine") == 0)
        {
            frequency *= 2; // صعود للأعلى (طبقة حادة ورفيعة) 📈
        }
        else if (strcmp(currentPosition, "underLine") == 0)
        {
            frequency /= 2; // نزول للأسفل (طبقة ضخمة وعميقة) 📉
        }
        Beep(frequency, 400); // إصدار الصوت الحقيقي 🔊
    }
}

// قاموس فحص الكلمات الصارم لجميع الدروس الـ 15 (الـ Lexer)
int isValidWord(char *word)
{
    char *validWords[] = {
        "Do", "Re", "Mi", "Fa", "So", "La", "Fi", "Do#", "Fa#", "Reb", "So#", "Lab", "Mib", "Re#", "La#", "Tib", "Sob", "Dob", "Fab",
        "functions", "cromatik", "CSS", "voice", "check", "otherwise", "array", "music", "myTrack",
        "for", "Restart", "bosishen", "NewLine", "underLine", "chromatic", "harmony", "with", "natural", "half", "scale", "up", "down", "vibrato"};
    for (int i = 0; i < 43; i++)
    {
        if (strcmp(word, validWords[i]) == 0)
            return 1;
    }
    return 0;
}

// دالة تفكيك كود المستخدم وعزفه بأمان دون إغلاق النافذة
void compileAndPlay(HWND hwnd)
{
    // مصفوفة نصية ثابتة ومحجوزة تتسع لـ 10000 حرف لمنع أي انهيار
    static char codeBuffer[10000];
    GetWindowText(hEditCode, codeBuffer, sizeof(codeBuffer));

    if (strlen(codeBuffer) == 0)
    {
        MessageBox(hwnd, "Error: Code Box is Empty!", "music Language Compiler", MB_ICONERROR);
        return;
    }

    strcpy(currentPosition, "Normal");

    // مصفوفة مؤشرات ثابتة ومحجوزة تتسع لـ 2000 كلمة كاملة ومنفصلة
    static char *words[2000];
    int tokenCount = 0;

    char *word = strtok(codeBuffer, " \r\n,");
    while (word != NULL && tokenCount < 2000)
    {
        if (!isValidWord(word))
        {
            static char errorMsg[256]; // تحديد حجم المصفوفة لمنع الـ compiler error
            sprintf(errorMsg, "[Syntax Error ❌]: Unknown token '%s' detected!", word);
            MessageBox(hwnd, errorMsg, "music Language Compiler", MB_ICONERROR);
            return;
        }
        words[tokenCount++] = word;
        word = strtok(NULL, " \r\n,");
    }

    // الـ Parser والـ Audio Engine: عزف النوتات
    for (int i = 0; i < tokenCount; i++)
    {
        if (strcmp(words[i], "bosishen") == 0)
        {
            if (i + 1 < tokenCount)
            {
                strcpy(currentPosition, words[i + 1]);
                i++;
            }
        }
        else if (strcmp(words[i], "functions") == 0 || strcmp(words[i], "harmony") == 0 ||
                 strcmp(words[i], "with") == 0 || strcmp(words[i], "NewLine") == 0 ||
                 strcmp(words[i], "underLine") == 0)
        {
            continue;
        }
        else
        {
            playPianoTone(words[i]);
            Sleep(80);
        }
    }

    MessageBox(hwnd, "[SUCCESS]: 100% Compiled! Every single note played beautifully! 🎹🔥", "music Language", MB_ICONINFORMATION);
}

// الدالة المسؤولة عن أحداث النافذة (رسم وتنسيق الأزرار)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_CREATE:
        hEditCode = CreateWindow("EDIT", "Do Re bosishen NewLine Mi Fa bosishen underLine Do",
                                 WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN,
                                 20, 30, 440, 130, hwnd, (HMENU)TXT_CODE, NULL, NULL);

        hButton = CreateWindow("BUTTON", "Compile & Play Piano 🚀",
                               WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                               130, 185, 220, 40, hwnd, (HMENU)BTN_COMPILE, NULL, NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wp) == BTN_COMPILE)
        {
            compileAndPlay(hwnd);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR args, int nshow)
{
    WNDCLASS wc = {0};
    wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(32, 32, 45));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = "musicLanguageGUI";
    wc.lpfnWndProc = WndProc;

    if (!RegisterClass(&wc))
        return -1;

    CreateWindow("musicLanguageGUI", "music Language Official C-GUI Compiler 🤖",
                 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                 400, 200, 500, 280, NULL, NULL, hInst, NULL);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}