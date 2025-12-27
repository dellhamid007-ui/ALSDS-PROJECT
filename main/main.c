
#include <stdio.h>

#include "../USRMGMT/USRMGMT.h"
#include "../AUDSEC/AUDSEC.h"
#include "../MTHSEC/MTHSEC.h"
#include "../ENCDEC/ENCDEC.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int MeasureTextRecAlt(Font font, const char* text, float fontSize, float spacing, float wrapWidth) {
    int lines = 1;
    int lineLength = 0;
    const char* p = text;

    while (*p) {
        if (*p == '\n') {
            lines++;
            lineLength = 0;
        } else {
            lineLength++;
            // Rough wrap check (optional)
            if (MeasureTextEx(font, "W", fontSize, spacing).x * lineLength > wrapWidth) {
                lines++;
                lineLength = 0;
            }
        }
        p++;
    }

    return (int)(lines * (fontSize + spacing));
}

void DrawTextRecAlt(Font font, const char* text, Vector2 pos, float fontSize, float spacing, Color color) { //
    int line = 0;
    const char* start = text;
    const char* p = text;

    while (*p) {
        if (*p == '\n') {
            int len = p - start;
            char lineStr[256] = {0};
            stringModifyN(lineStr, start, len);
            DrawTextEx(font, lineStr, (Vector2){pos.x, pos.y + line * (fontSize + spacing)}, fontSize, spacing, color);
            line++;
            start = p + 1;
        }
        p++;
    }

    // Draw last line
    if (p != start) {
        DrawTextEx(font, start, (Vector2){pos.x, pos.y + line * (fontSize + spacing)}, fontSize, spacing, color);
    }
}



void stringConcat(char dest[], const char src[]) //custom strcat 
{
    int i = 0;
    int j = 0;

    // Move i to the end of dest
    while (dest[i] != '\0')
        i++;

    // Copy src to the end of dest
    while (src[j] != '\0')
    {
        dest[i] = src[j];
        i++;
        j++;
    }

    dest[i] = '\0';
}

typedef enum {
    SCREEN_MAIN_MENU,
    SCREEN_ENCDEC,
    SCREEN_MTHSEC,
    SCREEN_USRMGMT,
    SCREEN_AUDSEC,
    SCREEN_LOGMGMT,
    SCREEN_HELP
} AppScreen;

typedef enum {
    MTH_NUMBERS,
    MTH_ARRAYS,
    MTH_MATRICES
} MathSection;

AppScreen currentScreen = SCREEN_MAIN_MENU;
static MathSection currentMath = MTH_NUMBERS;


int main(void)
{

    #define MAX_USERS 100
    struct User users[MAX_USERS];
    loadUsers(users, MAX_USERS);


    const int screenWidth = 900;
    const int screenHeight = 600;


    

    InitWindow(screenWidth, screenHeight, "Security Utility Library System");
    SetTargetFPS(60);

    bool exitRequested = false;

    while (!WindowShouldClose() && !exitRequested)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen)
        {
            case SCREEN_MAIN_MENU:
            {
                DrawText("SECURITY UTILITY LIBRARY SYSTEM",
                         180, 50, 28, DARKGRAY);

                DrawText("Main Menu", 395, 95, 20, GRAY);

                Rectangle buttons[7] = {
                    {350, 150, 200, 42}, // ENCDEC
                    {350, 200, 200, 42}, // MTHSEC
                    {350, 250, 200, 42}, // USRMGMT
                    {350, 300, 200, 42}, // AUDSEC
                    {350, 350, 200, 42}, // LOGMGMT
                    {350, 400, 200, 42}, // HELP
                    {350, 460, 200, 42}  // EXIT
                };

                if (GuiButton(buttons[0], "ENCDEC - Encryption"))
                    currentScreen = SCREEN_ENCDEC;

                if (GuiButton(buttons[1], "MTHSEC - Math & Security"))
                    currentScreen = SCREEN_MTHSEC;

                if (GuiButton(buttons[2], "USRMGMT - User Management"))
                    currentScreen = SCREEN_USRMGMT;

                if (GuiButton(buttons[3], "AUDSEC - Audit & Security"))
                    currentScreen = SCREEN_AUDSEC;

                if (GuiButton(buttons[4], "LOGMGMT - Log Management"))
                    currentScreen = SCREEN_LOGMGMT;

                if (GuiButton(buttons[5], "Help"))
                    currentScreen = SCREEN_HELP;

                if (GuiButton(buttons[6], "Exit"))
                    exitRequested = true;

                DrawText("Raylib GUI - Academic Project",
                         330, 525, 14, LIGHTGRAY);
            } break;

            case SCREEN_ENCDEC:
            {
                static struct Message inputText = {"",200};
                static char outputText[200] = {0};
                static char keyText[30] = "";
                static char letter[2] = "";
                static bool editInput = false;
                static bool editKey = false;
                static bool editLetter = false;

                DrawText("ENCDEC - Encryption & Decryption",
                        240, 40, 26, DARKGRAY);

                // Input panel
                GuiPanel((Rectangle){50, 100, 350, 200}, "Input");
                GuiLabel((Rectangle){60, 140, 80, 20}, "Message:");
                GuiLabel((Rectangle){60, 205, 80, 20}, "Key:");
                GuiLabel((Rectangle){200, 205, 80, 20}, "Letter:");

                Vector2 mousePoint = GetMousePosition();

                    if (GuiTextBox((Rectangle){60, 165, 330, 30}, inputText.text, 200, editInput) || editInput){
                        editInput = true;
                        editKey = false;
                        editLetter = false;
                    }
                    else
                        editInput = false;

                    if (GuiTextBox((Rectangle){60, 230, 80, 30}, keyText, 29, editKey) || editKey){
                        editKey = true;
                        editInput = false;
                        editLetter = false;
                    }
                    else
                        editKey = false;
                    
                    if (GuiTextBox((Rectangle){200, 230, 80, 30}, letter, 2, editLetter) || editLetter){
                        editLetter = true;
                        editInput = false;
                        editKey = false;
                    }
                    else
                        editLetter = false;
               
                // Output panel
                GuiPanel((Rectangle){450, 100, 350, 200}, "Output");
                GuiLabel((Rectangle){460, 140, 80, 20}, "Result:");
                GuiTextBox(
                    (Rectangle){460, 165, 330, 30},
                    outputText, 200, false
                );

                

                // Action buttons (placeholders)
                if (GuiButton((Rectangle){150, 330, 160, 35}, "To Uppercase"))
                {
                    struct Message temp = inputText;
                    toUppercase(&temp);

                    stringModify(outputText, temp.text);
                }

                if (GuiButton((Rectangle){150, 420, 160, 35}, "To Lowercase")) {
                    struct Message temp = inputText;
                    toLowercase(&temp);

                    stringModify(outputText, temp.text);
                }

                if (GuiButton((Rectangle){150, 465, 160, 35}, "Valid Sub key?")) {
                    if(isValidKey(keyText) == 1){
                        stringModify(outputText, "The Key is Valid");
                    }
                    else stringModify(outputText, "The Key is not Valid");
                }

                if (GuiButton((Rectangle){150, 420, 160, 35}, "Count Character")) {
                    char l = letter[0];
                    int c = countCharacter(inputText, l);
                    sprintf(outputText,"%d",c);
                }

                if (GuiButton((Rectangle){150, 420, 160, 35}, "Coincidence Index")) {
                    double index = coincidenceIndex(inputText);
                    sprintf(outputText,"%lf",index);
                }

                if (GuiButton((Rectangle){150, 375, 160, 35}, "Reverse"))
                {
                    struct Message temp = inputText;
                    reverseMessage(&temp);

                    stringModify(outputText, temp.text);
                }

                if (GuiButton((Rectangle){420, 330, 160, 35}, "Caesar Encrypt"))
                {
                    struct Message temp = inputText;
                    encryptCesar(&temp, atoi(keyText));

                    stringModify(outputText, temp.text);
                }

                if (GuiButton((Rectangle){420, 375, 160, 35}, "Caesar Decrypt"))
                {
                    struct Message temp = inputText;
                    decryptCesar(&temp, atoi(keyText));

                    stringModify(outputText, temp.text);
                }

                if (GuiButton((Rectangle){420, 420, 160, 35}, "XOR Encrypt")) {
                    struct Message temp = inputText;
                    encryptXOR(&temp, (unsigned char)(keyText[0]));

                    toHexString((unsigned char*)temp.text,stringLength(temp.text),outputText);

                }

                if (GuiButton((Rectangle){420, 465, 160, 35}, "XOR Decrypt")) {
                    struct Message temp;

                    hexStringToBytes(inputText.text,stringLength(temp.text)/2,(unsigned char *)temp.text);

                    temp.text[stringLength(inputText.text)/2] = '\0';


                    decryptXOR(&temp, (unsigned char)(keyText[0]));

                    stringModify(outputText, temp.text);
                    
                }

                if (GuiButton((Rectangle){420, 510, 160, 35}, "Substitution Encrypt")) {
                    struct Message temp = inputText;
                    encryptSubstitution(&temp, keyText);

                    stringModify(outputText, temp.text);
                }

                if (GuiButton((Rectangle){420, 555, 160, 35}, "Substitution Decrypt")) {
                    struct Message temp = inputText;
                    decryptSubstitution(&temp, keyText);

                    stringModify(outputText, temp.text);
                }

                if (GuiButton((Rectangle){20, 20, 100, 35}, "< Back"))
                    currentScreen = SCREEN_MAIN_MENU;
            }
            break;

                case SCREEN_MTHSEC:
                {
                    static MathSection currentMath = MTH_NUMBERS;

                    // ---------- INPUT FIX (PUT HERE) ----------
                    Vector2 mousePoint = GetMousePosition();

                    // ---------- NUMBER TOOLS ----------
                    static char numberInput[16] = "";
                    static char numberOutput[64] = "";
                    static bool editNumber = false;   // ← PUT HERE

                    // ---------- ARRAY TOOLS ----------
                    static int arraySize = 5;
                    static char array[10][6] = {0};
                    static char arrayResult[64] = "";
                    static bool editArray[10] = {0};  // ← PUT HERE

                    DrawText("MTHSEC - Math & Security Tools", 260, 25, 26, DARKGRAY);

                    // Section selector
                    if (GuiButton((Rectangle){50, 70, 150, 35}, "Numbers"))
                        currentMath = MTH_NUMBERS;

                    if (GuiButton((Rectangle){220, 70, 150, 35}, "Arrays"))
                        currentMath = MTH_ARRAYS;

                    if (GuiButton((Rectangle){390, 70, 150, 35}, "Matrices"))
                        currentMath = MTH_MATRICES;

                    // ---------------- NUMBERS ----------------
                    if (currentMath == MTH_NUMBERS)
                    {
                        GuiPanel((Rectangle){50, 130, 800, 400}, "Number Tools");

                        GuiLabel((Rectangle){70, 170, 80, 20}, "Number:");

                        Rectangle numRect = {150, 165, 160, 30};

                        if (GuiTextBox(numRect, numberInput, 15, editNumber) || editNumber)
                        {
                            if (CheckCollisionPointRec(mousePoint, numRect) &&
                                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                                editNumber = true;
                        }
                        else editNumber = false;
                        

                        if (!CheckCollisionPointRec(mousePoint, numRect) &&
                            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                            editNumber = false;

                        if (GuiButton((Rectangle){100, 215, 200, 35}, "Check Prime"))
                        {
                            if(isPrime(atoi(numberInput)) == 1 ){
                                stringModify(numberOutput,"Yes");
                            }
                            else stringModify(numberOutput, "No");
                        }

                        if (GuiButton((Rectangle){100, 260, 200, 35}, "Factorial"))
                        {
                            int fact = factorial(atoi(numberInput));
                            sprintf(numberOutput, "%d", fact);
                        }
                        
                        if (GuiButton((Rectangle){100, 305, 200, 35}, "Check Even"))
                        {
                            if(isEven(atoi(numberInput)) == 1 ){
                                stringModify(numberOutput,"Yes");
                            }
                            else stringModify(numberOutput, "No");
                        }

                        if (GuiButton((Rectangle){100, 350, 200, 35}, "Sum Digits"))
                        {   
                            sprintf(numberOutput, "%d", sumDigits(atoi(numberInput)));
                        }

                        if (GuiButton((Rectangle){350, 215, 200, 35}, "Check Perfect Number"))
                        {
                            if(isPerfectNumber(atoi(numberInput)) == 1 ){
                                stringModify(numberOutput,"Yes");
                            }
                            else stringModify(numberOutput, "No");
                        }

                        if (GuiButton((Rectangle){350, 260, 200, 35}, "is Palindrome"))
                        {
                            if(isPalindromeNumber(atoi(numberInput)) == 1 ){
                                stringModify(numberOutput,"Yes");
                            }
                            else stringModify(numberOutput, "No");

                        }

                        if (GuiButton((Rectangle){350, 305, 200, 35}, "Sum Divisors"))
                        {
                            sprintf(numberOutput, "%d", sumDivisors(atoi(numberInput)));
                        }

                        if (GuiButton((Rectangle){350, 350, 200, 35}, "Reverse"))
                        {
                            sprintf(numberOutput, "%d", reverseNumber(atoi(numberInput)));
                        }

                        if (GuiButton((Rectangle){600, 215, 200, 35}, "is Armstrong"))
                        {
                            if(isArmstrong(atoi(numberInput)) == 1 ){
                                stringModify(numberOutput,"Yes");
                            }
                            else stringModify(numberOutput, "No");
                        }

                      //  if (GuiButton((Rectangle){600, 260, 200, 35}, "Generate Random"))
                      //  {

                      //  }

                      //  if (GuiButton((Rectangle){600, 305, 200, 35}, "Check Prime"))
                      // {

                      //  }

                      //  if (GuiButton((Rectangle){600, 350, 200, 35}, "Factorial"))
                      //  {

                      //  }

                        GuiLabel((Rectangle){500, 170, 260, 20}, numberOutput);
                        if (GuiButton((Rectangle){20, 20, 100, 35}, "< Back"))
                        currentScreen = SCREEN_MAIN_MENU;
                    }

                    // ---------------- ARRAYS ----------------
                    if (currentMath == MTH_ARRAYS)
                    {
                        GuiPanel((Rectangle){50, 130, 520, 320}, "Array Tools");

                        GuiLabel((Rectangle){70, 165, 60, 20}, "Size:");
                        GuiSpinner((Rectangle){130, 160, 60, 30},
                                NULL, &arraySize, 1, 10, false);

                        for (int i = 0; i < arraySize; i++)
                        {
                            Rectangle arrRect = {70 + i * 45, 210, 40, 30};

                            if (GuiTextBox(arrRect, array[i], 5, editArray[i]) || editArray[i])
                            {
                                if (CheckCollisionPointRec(mousePoint, arrRect) &&
                                    IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                                {
                                    // Unfocus others
                                    for (int j = 0; j < 10; j++)
                                        editArray[j] = false;

                                    editArray[i] = true;
                                }
                            }
                            else editArray[i] = false;

                            if (!CheckCollisionPointRec(mousePoint, arrRect) &&
                                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                                editArray[i] = false;
                        }

                        if (GuiButton((Rectangle){100, 270, 150, 35}, "Sum"))
                        {
                            int nums[10] = {0};

                        // Convert text input to integers
                        for (int i = 0; i < arraySize; i++)
                            nums[i] = atoi(array[i]);

                        int sum = sumArray(nums, arraySize);
                        sprintf(arrayResult,"%d",sum);
                        }

                        if (GuiButton((Rectangle){100, 325, 150, 35}, "Max"))
                        {
                            int nums[10] = {0};

                        // Convert text input to integers
                        for (int i = 0; i < arraySize; i++)
                            nums[i] = atoi(array[i]);

                        int max = maxArray(nums, arraySize);
                        sprintf(arrayResult,"%d",max);
                        }

                        if (GuiButton((Rectangle){270, 325, 150, 35}, "Min"))
                        {
                            int nums[10] = {0};

                        // Convert text input to integers
                        for (int i = 0; i < arraySize; i++)
                            nums[i] = atoi(array[i]);

                        int min = maxArray(nums, arraySize);
                        sprintf(arrayResult,"%d",min);
                        }

                        if (GuiButton((Rectangle){185, 380, 150, 35}, "Average"))
                        {
                            int nums[10] = {0};

                        // Convert text input to integers
                        for (int i = 0; i < arraySize; i++)
                            nums[i] = atoi(array[i]);

                        float avg = averageArray(nums, arraySize);
                        sprintf(arrayResult,"%.3f",avg);
                        }

                        if (GuiButton((Rectangle){270, 270, 150, 35}, "Sort"))
                        {
                           int nums[10] = {0};

                        // Convert text input to integers
                        for (int i = 0; i < arraySize; i++)
                            nums[i] = atoi(array[i]);

                        sortAscending(nums,arraySize);

                        // Convert back to strings
                        for (int i = 0; i < arraySize; i++)
                            sprintf(array[i], "%d", nums[i]);

                        stringModify(arrayResult, "Sorted");
                        }

                        GuiLabel((Rectangle){300, 165, 300, 20}, arrayResult);
                        if (GuiButton((Rectangle){20, 20, 100, 35}, "< Back"))
                        currentScreen = SCREEN_MAIN_MENU;
                    }

                    // ---------------- MATRICES ----------------

                    if (currentMath == MTH_MATRICES)
                    {
                        static int rowsA = 2, colsA = 2;
                        static int rowsB = 2, colsB = 2;

                        static char matA[5][5][6] = {0};
                        static char matB[5][5][6] = {0};
                        static char matR[5][5][6] = {0};
                        static char Result[32] = "";

                        static bool editMatA[5][5] = {0};
                        static bool editMatB[5][5] = {0};

                        DrawText("Matrix Dimensions", 50, 130, 18, DARKGRAY);

                        // -------- Matrix A size --------
                        GuiLabel((Rectangle){50, 160, 80, 20}, "A Rows:");
                        GuiSpinner((Rectangle){120, 155, 60, 30},
                                NULL, &rowsA, 1, 5, false);

                        GuiLabel((Rectangle){200, 160, 80, 20}, "A Cols:");
                        GuiSpinner((Rectangle){270, 155, 60, 30},
                                NULL, &colsA, 1, 5, false);

                        // -------- Matrix B size --------
                        GuiLabel((Rectangle){350, 160, 80, 20}, "B Rows:");
                        GuiSpinner((Rectangle){420, 155, 60, 30},
                                NULL, &rowsB, 1, 5, false);

                        GuiLabel((Rectangle){500, 160, 80, 20}, "B Cols:");
                        GuiSpinner((Rectangle){570, 155, 60, 30},
                                NULL, &colsB, 1, 5, false);

                        // -------- Matrix A --------
                        GuiPanel((Rectangle){40, 200, 260, 260}, "Matrix A");

                        for (int i = 0; i < rowsA; i++)
                        {
                            for (int j = 0; j < colsA; j++)
                            {
                                Rectangle rectA = {60 + j * 45, 240 + i * 40, 40, 30};

                                if (GuiTextBox(rectA, matA[i][j], 5, editMatA[i][j]) || editMatA[i][j])
                                {
                                    if (CheckCollisionPointRec(mousePoint, rectA) &&
                                        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                                    {
                                        // unfocus all first
                                        for (int x = 0; x < 5; x++)
                                            for (int y = 0; y < 5; y++)
                                            {
                                                editMatA[x][y] = false;
                                                editMatB[x][y] = false;
                                            }

                                        editMatA[i][j] = true;
                                    }
                                }
                                else editMatA[i][j] = false;

                                if (!CheckCollisionPointRec(mousePoint, rectA) &&
                                    IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                                    editMatA[i][j] = false;
                            }
                        }

                        // -------- Matrix B --------
                        GuiPanel((Rectangle){330, 200, 260, 260}, "Matrix B");

                        for (int i = 0; i < rowsB; i++)
                        {
                            for (int j = 0; j < colsB; j++)
                            {
                                Rectangle rectB = {350 + j * 45, 240 + i * 40, 40, 30};

                                if (GuiTextBox(rectB, matB[i][j], 5, editMatB[i][j]) || editMatB[i][j])
                                {
                                    if (CheckCollisionPointRec(mousePoint, rectB) &&
                                        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                                    {
                                        // unfocus all first
                                        for (int x = 0; x < 5; x++)
                                            for (int y = 0; y < 5; y++)
                                            {
                                                editMatA[x][y] = false;
                                                editMatB[x][y] = false;
                                            }

                                        editMatB[i][j] = true;
                                    }
                                }
                                else editMatB[i][j] = false;

                                if (!CheckCollisionPointRec(mousePoint, rectB) &&
                                    IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                                    editMatB[i][j] = false;
                            }
                        }

                        struct Matrix_ matA_ ; matA_.n = rowsA; matA_.p = colsA;
                        struct Matrix_ matB_ ; matB_.n = rowsB; matB_.p = colsB;
                        struct Matrix_ matR_ ;

                        for (int i = 0; i < rowsA; i++)
                            for (int j = 0; j < colsA; j++)
                                matA_.data[i][j] = atoi(matA[i][j]);

                        for (int i = 0; i < rowsB; i++)
                            for (int j = 0; j < colsB; j++)
                                matB_.data[i][j] = atoi(matB[i][j]);

                        // -------- Result --------
                        GuiPanel((Rectangle){620, 200, 260, 260}, "Result");

                        for (int i = 0; i < 5; i++)
                            for (int j = 0; j < 5; j++)
                                GuiLabel(
                                    (Rectangle){640 + j * 45, 240 + i * 40, 40, 20},
                                    matR[i][j]
                                );

                        // -------- Operations --------
                        if (GuiButton((Rectangle){180, 480, 100, 35}, "Add"))
                        {
                            addMatrices(matA_, matB_, &matR_ );
                            for (int i = 0; i < matR_.n; i++)
                                for (int j = 0; j < matR_.p; j++)
                                    sprintf(matR[i][j], "%d", matR_.data[i][j]);
                        }

                        if (GuiButton((Rectangle){300, 480, 100, 35}, "Multiply"))
                        {
                            multiplyMatrices(matA_, matB_, &matR_);
                            for (int i = 0; i < matR_.n; i++)
                                for (int j = 0; j < matR_.p; j++)
                                    sprintf(matR[i][j], "%d", matR_.data[i][j]);
                        }

                        if (GuiButton((Rectangle){420, 480, 120, 35}, "Transpose A"))
                        {
                            transposeMatrix(matA_, &matR_);
                            for (int i = 0; i < matR_.n; i++)
                                for (int j = 0; j < matR_.p; j++)
                                    sprintf(matR[i][j], "%d", matR_.data[i][j]);
                        }

                        if (GuiButton((Rectangle){550, 480, 120, 35}, "Is Identity?"))
                        {
                            if (isIdentity(matA_) == 1) // your function
                                stringModify(Result, "Yes");
                            else
                                stringModify(Result, "No");
                        }

                        if (GuiButton((Rectangle){680, 480, 140, 35}, "Determinant 2x2"))
                        {
                            if(rowsA == 2 && colsA == 2){
                                int temp[2][2];
                                for(int i =0; i <2; i++){
                                    for(int j =0; j<2; j++){
                                        temp[i][j] = matA_.data[i][j];
                                    }
                                }
                                int det = determinant2x2(temp); // your function
                                sprintf(Result, "%d", det);
                            }
                            else stringModify(Result, "Matrix isnt 2x2");
                        }

                        GuiLabel((Rectangle){680, 525, 280, 20}, Result);

                        if (GuiButton((Rectangle){20, 20, 100, 35}, "< Back"))
                        currentScreen = SCREEN_MAIN_MENU;
                    }
                }
                break;
                case SCREEN_USRMGMT:
                {
                    static char username[21] = "";
                    static char password[21] = "";
                    static int role = 0; // 0: user, 1: admin
                    static char outputText[1024] = "";
                    static char login[100]  = "";

                    DrawText("USRMGMT - User Management", 280, 40, 26, DARKGRAY);

                    // Input panel
                    GuiPanel((Rectangle){50, 100, 350, 220}, "Input");

                    GuiLabel((Rectangle){60, 130, 80, 20}, "Username:");
                    static bool editUsername = false;
                    static bool editPassword = false;
                    if (GuiTextBox((Rectangle){60, 155, 330, 30}, username, 20, editUsername)) {
                        editUsername = true;
                        editPassword = false;  // unfocus other field
                    }

                    GuiLabel((Rectangle){60, 195, 80, 20}, "Password:");
                    
                    if (GuiTextBox((Rectangle){60, 220, 330, 30}, password, 20, editPassword)) {
                        editPassword = true;
                        editUsername = false; // unfocus other field
                    }

                    GuiLabel((Rectangle){60, 260, 80, 20}, "Role:");
                    if (GuiButton((Rectangle){60, 285, 100, 30}, role == 0 ? "[X] User" : "[ ] User")) role = 0;
                    if (GuiButton((Rectangle){170, 285, 100, 30}, role == 1 ? "[X] Admin" : "[ ] Admin")) role = 1;

                    // Action buttons column
                    int buttonX = 420;
                    int buttonY = 150;
                    int buttonW = 200;
                    int buttonH = 35;
                    int buttonSpacing = 50;

                    if (GuiButton((Rectangle){buttonX, buttonY + 0 * buttonSpacing, buttonW, buttonH}, "Add User")) {
                        for (int i = 0; i < MAX_USERS; i++) {
                            if (users[i].state == 999) { // empty slot
                                stringModifyN(users[i].name, username, 20);
                                stringModifyN(users[i].password, password, 20);
                                users[i].role = role;
                                users[i].state = 0;
                                break;
                            }
                        }
                    }
                    if (GuiButton((Rectangle){buttonX, buttonY + 1 * buttonSpacing, buttonW, buttonH}, "Delete User")) { 
                        deleteUser(users, MAX_USERS, username);
                    }
                    if (GuiButton((Rectangle){buttonX, buttonY + 2 * buttonSpacing, buttonW, buttonH}, "Change Password")) { 
                        changePassword(users, MAX_USERS, username, password);
                    }
                    if (GuiButton((Rectangle){buttonX, buttonY + 3 * buttonSpacing, buttonW, buttonH}, "Block User")) { 
                        blockUser(users, MAX_USERS, username);
                    }
                    if (GuiButton((Rectangle){buttonX, buttonY + 4 * buttonSpacing, buttonW, buttonH}, "Unblock User")) {
                        unblockUser(users, MAX_USERS, username);
                     }

                     if (GuiButton((Rectangle){buttonX, buttonY + 5 * buttonSpacing, buttonW, buttonH}, "Save Users")) {
                        saveUsers(users, MAX_USERS);
                    }

                    if (GuiButton((Rectangle){buttonX, buttonY + 6 * buttonSpacing, buttonW, buttonH}, "Load Users")) {
                        loadUsers(users, MAX_USERS);
                    }

                    if (GuiButton((Rectangle){buttonX, buttonY + 7 * buttonSpacing, buttonW, buttonH}, "Global Security Level")) {
                        userStatistics(users,MAX_USERS);
                        stringModify(outputText,"User Statistics exported to user_stats.dat");

                    }

                    if (GuiButton((Rectangle){buttonX + buttonW+20, buttonY + 0* buttonSpacing, buttonW, buttonH}, "Login")) {
                        int l = checkLogin(users,MAX_USERS,username,password);
                        switch (l){
                        case -1: stringModify(login, "User does not exist"); break;
                        case 0: stringModify(login, "Wrong Password");break;
                        case 1: stringModify(login, "Login Successfull"); break;
                        }
                    }


                    DrawText(outputText,buttonX,buttonY - 40,20,BLACK);
                    DrawText(login, buttonX+buttonW+20, buttonY + 1*buttonSpacing, 20, BLACK);

                    // Output panel
                    GuiPanel((Rectangle){50, 330, 350, 200}, "Users");
                        int startY = 355;
                        int lineHeight = 20;
                        for (int i = 0; i < MAX_USERS; i++) {
                            if (users[i].state != 999) { // not deleted
                                char line[100];
                                snprintf(line, sizeof(line), "%s | Role: %s | State: %s",
                                        users[i].name,
                                        users[i].role == 1 ? "Admin" : "User",
                                        users[i].state == 1 ? "Blocked" : "Active");
                                DrawText(line, 60, startY + i * lineHeight, 14, DARKGRAY);
                            }
                        }
                    // Back button
                    if (GuiButton((Rectangle){20, 20, 100, 35}, "< Back"))
                        currentScreen = SCREEN_MAIN_MENU;
                } break;


                case SCREEN_AUDSEC:
                {
                    static bool showOutputWindow = false;
                    static char outputText[1024] = "";

                    DrawText("AUDSEC - Audit & Security Tools", 260, 25, 26, DARKGRAY);

                    // ---------- TEXT INPUT ----------
                    static char inputText[128] = "";
                    static bool editInput = false;

                    Vector2 mousePoint = GetMousePosition();

                    Rectangle inputRect = {50, 100, 400, 30};
                    GuiLabel((Rectangle){50, 80, 200, 20}, "Enter text / username / password:");
                    if (GuiTextBox(inputRect, inputText, 127, editInput) || editInput) {
                        if (CheckCollisionPointRec(mousePoint, inputRect) &&
                            IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                            editInput = true;
                        }
                    } else editInput = false;

                    if (!CheckCollisionPointRec(mousePoint, inputRect) &&
                        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        editInput = false;

                    // ---------- BUTTONS ----------
                    if (GuiButton((Rectangle){50, 150, 200, 35}, "Text Stats")) {
                        displayTextStats(inputText);          // Your function
                        stringModify(outputText, "Text stats calculated.\n"); 

                    }

                    if (GuiButton((Rectangle){270, 150, 200, 35}, "Generate Random Key")) {
                        generateKey(16, outputText);          // Your function
                    }

                    if (GuiButton((Rectangle){50, 200, 200, 35}, "Generate Random Password")) {
                        generateRandomPassword(12, outputText);  // Your function

                    }

                    if (GuiButton((Rectangle){270, 200, 200, 35}, "Check Strong Password")) {
                        if (veryStrongPassword(inputText))
                            stringModify(outputText, "Password is very strong!");
                        else
                            stringModify(outputText, "Password is NOT very strong!");

                    }

                    if (GuiButton((Rectangle){50, 250, 200, 35}, "Top 3 Passwords")) {
                        top3Passwords(users, MAX_USERS);         // Example, fill outputText inside function

                    }

                    if (GuiButton((Rectangle){270, 250, 200, 35}, "Global Security Level")) {
                        int level = globalSecurityLevel(users, MAX_USERS);
                        sprintf(outputText, "Global Security Level: %d%%", level);

                    }

                    if (GuiButton((Rectangle){50, 300, 200, 35}, "Generate Hex Key")) {
                        generateHexKey(16, outputText);

                    }

                    if (GuiButton((Rectangle){270, 300, 200, 35}, "Check Email Format")) {
                        int check = checkEmailFormat(inputText);
                        if(check == 1) stringModify(outputText, "Valid Email");
                        else stringModify(outputText, "Invalid Email");
                    }

                    if (GuiButton((Rectangle){50, 350, 200, 35}, "Password Score")) {
                        sprintf(outputText, "%d", passwordScore(inputText));

                    }

                    if (GuiButton((Rectangle){270, 350, 200, 35}, "Text Length")) {
                        sprintf(outputText, "%d", textLength(inputText));
                    }

                    if (GuiButton((Rectangle){50, 400, 200, 35}, "Uppercase percentage")) {
                        sprintf(outputText, "%%%.2f", percentUppercase(inputText));

                    }

                    if (GuiButton((Rectangle){270, 400, 200, 35}, "Check login Format")) {
                        int check = checkLoginFormat(inputText);
                        if(check == 1) stringModify(outputText, "Valid Login");
                        else stringModify(outputText, "Invalid Login");
                    }


                    DrawText(outputText,500,100,20,BLACK);

                    if (GuiButton((Rectangle){20, 20, 100, 35}, "< Back"))
                        currentScreen = SCREEN_MAIN_MENU;

                }
                break;

            case SCREEN_LOGMGMT:
                DrawText("LOGMGMT MODULE (placeholder)",
                         260, 280, 20, GRAY);
                if (GuiButton((Rectangle){20, 20, 100, 35}, "< Back"))
                    currentScreen = SCREEN_MAIN_MENU;
                break;

            case SCREEN_HELP:
                DrawText("HELP",
                         420, 80, 26, DARKGRAY);

                DrawText(
                    "This application is a graphical interface for\n"
                    "the Security Utility Library System project.\n\n"
                    "Each module corresponds to a C library:\n"
                    "- ENCDEC : Encryption & Decryption\n"
                    "- MTHSEC : Math & Security Tools\n"
                    "- USRMGMT: User Management\n"
                    "- AUDSEC : Audit & Security Analysis\n"
                    "- LOGMGMT: Log Management\n\n"
                    "Developed by Dellali Abdelhamid and Lehlouh Abdeljalil.",
                    180, 140, 18, GRAY
                );

                if (GuiButton((Rectangle){20, 20, 100, 35}, "< Back"))
                    currentScreen = SCREEN_MAIN_MENU;
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}