
#include <stdio.h>

#include "../USRMGMT/USRMGMT.h"
#include "../AUDSEC/AUDSEC.h"
#include "../MTHSEC/MTHSEC.h"

#include <windows.h>
#include <commctrl.h>




#define MAX_USERS 100
#define BTN_GO 1001
#define LIST_LIBS 1002

// Global variables
struct User users[MAX_USERS];
HWND hListBox, hGoBtn;

// Function prototypes
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void AddText(const char* text);
void LoadLibraryList();
void ExecuteSelectedLibrary();
void ReturnToMainMenu(void);
void ShowUserManagementMenu(void);
void ShowMathToolsMenu(void);
void ShowAuditMenu(void);
void ExecuteSelectedFunction(void);
void ShowAllUsers(void);
void ShowAddUserDialog(void);
void ShowPrimeCheckDialog(void);

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, int nCmdShow) {
    
    // Window class
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "LibSelector";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    RegisterClassA(&wc);
    
    // Create window
    HWND hwnd = CreateWindowA(
        "LibSelector",
        "Library Selector - SELECT then PRESS GO",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 500, 400,
        NULL, NULL, hInstance, NULL
    );
    
    if (!hwnd) return 0;
    
    // Create listbox (SINGLE selection mode)
    hListBox = CreateWindowA(
        "LISTBOX", "",
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_NOTIFY,
        10, 10, 460, 300,
        hwnd, (HMENU)LIST_LIBS, hInstance, NULL
    );
    
    // Create GO button
    hGoBtn = CreateWindowA(
        "BUTTON", "GO",
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        350, 320, 120, 30,
        hwnd, (HMENU)BTN_GO, hInstance, NULL
    );
    
    // Load users
    loadUsers(users, MAX_USERS);
    
    // Load library list
    LoadLibraryList();
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    // Focus on listbox
    SetFocus(hListBox);
    
    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND: {
            int cmd = LOWORD(wParam);
            
            if (cmd == BTN_GO) {
                // Get the first line to determine context
                char firstLine[100];
                SendMessageA(hListBox, LB_GETTEXT, 0, (LPARAM)firstLine);
                
                // Check what screen we're on
                if (strstr(firstLine, "=== SELECT A LIBRARY ===")) {
                    // Main menu - execute selected library
                    ExecuteSelectedLibrary();
                }
                else if (strstr(firstLine, "=== USER MANAGEMENT SYSTEM ===")) {
                    // In User Management - show user functions menu
                    ShowUserManagementMenu();
                }
                else if (strstr(firstLine, "=== MATH & SECURITY TOOLS ===")) {
                    // In Math Tools - show math functions menu
                    ShowMathToolsMenu();
                }
                else if (strstr(firstLine, "=== SECURITY AUDIT & ANALYSIS ===")) {
                    // In Security Audit - show audit functions menu
                    ShowAuditMenu();
                }
                else if (strstr(firstLine, "Available Functions:")) {
                    // In functions menu - execute selected function
                    ExecuteSelectedFunction();
                }
                else {
                    // Any other screen - return to main menu
                    ReturnToMainMenu();
                }
            }
            else if (cmd == LIST_LIBS) {
                if (HIWORD(wParam) == LBN_DBLCLK) {
                    // Double-click behaves like GO button
                    SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(BTN_GO, 0), 0);
                }
            }
            break;
        }
        case WM_SIZE: {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);
            
            // Listbox
            MoveWindow(hListBox, 10, 10, width - 20, height - 80, TRUE);
            
            // GO button (bottom right)
            MoveWindow(hGoBtn, width - 130, height - 60, 120, 30, TRUE);
            
            break;
        }
        
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
            
        default:
            return DefWindowProcA(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Add text to listbox
void AddText(const char* text) {
    SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)text);
}

// Load libraries into listbox
void LoadLibraryList() {
    SendMessageA(hListBox, LB_RESETCONTENT, 0, 0);
    
    AddText("=== SELECT A LIBRARY ===");
    AddText("");
    AddText("1. User Management System");
    AddText("2. Math & Security Tools");
    AddText("3. Security Audit & Analysis");
    AddText("4. Encryption & Decryption (Coming)");
    AddText("5. Log Management (Coming)");
    AddText("");
    AddText("Select an item above, then press GO button!");
}

// Execute the selected library
void ExecuteSelectedLibrary() {
    int selected = SendMessageA(hListBox, LB_GETCURSEL, 0, 0);
    
    if (selected == LB_ERR) {
        MessageBoxA(hListBox, "Please select a library first!", "No Selection", MB_OK);
        return;
    }
    
    // Get the selected text
    char buffer[100];
    SendMessageA(hListBox, LB_GETTEXT, selected, (LPARAM)buffer);
    
    // Clear listbox and show library features
    SendMessageA(hListBox, LB_RESETCONTENT, 0, 0);
    
    // Check which library was selected
    if (buffer[0] == '1' || strstr(buffer, "User Management")) {
        // User Management features
        AddText("=== USER MANAGEMENT SYSTEM ===");
        AddText("");
        AddText("Available Functions:");
        AddText("-------------------");
        AddText("1. initUsers - Initialize user list");
        AddText("2. displayUsers - Show all users");
        AddText("3. addUser - Add new user");
        AddText("4. deleteUser - Remove user");
        AddText("5. searchUser - Find user by name");
        AddText("6. changePassword - Update password");
        AddText("7. checkLogin - Verify credentials");
        AddText("8. blockUser - Block a user");
        AddText("9. unblockUser - Unblock user");
        AddText("10. changeRole - Change user/admin role");
        AddText("11. listAdmins - Show administrators");
        AddText("12. userStatistics - Show stats");
        AddText("13. saveUsers - Save to file");
        AddText("14. loadUsers - Load from file");
        AddText("");
        
        // Show current user count
        int count = 0;
        for (int i = 0; i < MAX_USERS; i++) {
            if (users[i].state != 999) count++;
        }
        
        char countMsg[50] = "Current users in system: ";
        // Convert count to string
        char numStr[10];
        int temp = count;
        int pos = 0;
        
        if (temp == 0) {
            numStr[0] = '0';
            numStr[1] = '\0';
            pos = 1;
        } else {
            char tempStr[10];
            int d = 0;
            while (temp > 0) {
                tempStr[d++] = (temp % 10) + '0';
                temp /= 10;
            }
            // Reverse
            for (int i = 0; i < d; i++) {
                numStr[i] = tempStr[d - 1 - i];
            }
            numStr[d] = '\0';
            pos = d;
        }
        
        // Add number to message
        for (int i = 0; i < pos; i++) {
            countMsg[25 + i] = numStr[i];
        }
        countMsg[25 + pos] = '\0';
        AddText(countMsg);
        
    }
    else if (buffer[0] == '2' || strstr(buffer, "Math")) {
        // Math Tools features
        AddText("=== MATH & SECURITY TOOLS ===");
        AddText("");
        AddText("Available Functions:");
        AddText("-------------------");
        AddText("1. isEven - Check if number is even");
        AddText("2. isPrime - Check for prime number");
        AddText("3. gcd - Greatest common divisor");
        AddText("4. lcm - Least common multiple");
        AddText("5. modExp - Modular exponentiation");
        AddText("6. factorial - Calculate factorial");
        AddText("7. sumDigits - Sum of digits");
        AddText("8. reverseNumber - Reverse digits");
        AddText("9. isPalindromeNumber - Check palindrome");
        AddText("10. sumDivisors - Sum of divisors");
        AddText("11. isPerfectNumber - Check perfect number");
        AddText("12. isArmstrong - Check Armstrong number");
        AddText("13. randomNumber - Generate random number");
        AddText("14. sumArray - Sum array elements");
        AddText("15. averageArray - Calculate average");
        AddText("16. maxArray - Find maximum value");
        AddText("17. minArray - Find minimum value");
        AddText("18. sortAscending - Sort array");
        AddText("19. displayMatrix - Show matrix");
        AddText("20. addMatrices - Matrix addition");
        AddText("21. multiplyMatrices - Matrix multiplication");
        AddText("22. transposeMatrix - Matrix transpose");
        AddText("23. determinant2x2 - 2x2 determinant");
        AddText("24. isSymmetric - Check symmetric matrix");
        AddText("25. isIdentity - Check identity matrix");
        AddText("");
        
        // Show some test results
        AddText("Quick Tests:");
        AddText("------------");
        
        // Test 1: isPrime
        char primeTest[50] = "isPrime(17) = ";
        // Manually check prime instead of calling function (to avoid compilation issues)
        int prime = 1;
        for (int i = 2; i <= 17/2; i++) {
            if (17 % i == 0) {
                prime = 0;
                break;
            }
        }
        strcat(primeTest, prime ? "PRIME" : "NOT PRIME");
        AddText(primeTest);
        
        // Test 2: gcd
        char gcdTest[50] = "gcd(48, 18) = ";
        // Calculate gcd manually
        int a = 48, b = 18;
        while (a % b != 0) {
            int rem = a % b;
            a = b;
            b = rem;
        }
        char gcdStr[10];
        int temp = b;
        int pos = 0;
        
        if (temp == 0) {
            gcdStr[0] = '0';
            gcdStr[1] = '\0';
            pos = 1;
        } else {
            char tempStr[10];
            int d = 0;
            while (temp > 0) {
                tempStr[d++] = (temp % 10) + '0';
                temp /= 10;
            }
            // Reverse
            for (int i = 0; i < d; i++) {
                gcdStr[i] = tempStr[d - 1 - i];
            }
            gcdStr[d] = '\0';
            pos = d;
        }
        
        // Add to gcdTest
        for (int i = 0; i < pos; i++) {
            gcdTest[13 + i] = gcdStr[i];
        }
        gcdTest[13 + pos] = '\0';
        AddText(gcdTest);
        
    }
    else if (buffer[0] == '3' || strstr(buffer, "Security Audit")) {
        // Security Audit features
        AddText("=== SECURITY AUDIT & ANALYSIS ===");
        AddText("");
        AddText("Available Functions:");
        AddText("-------------------");
        AddText("1. countUppercase - Count uppercase letters");
        AddText("2. countLowercase - Count lowercase letters");
        AddText("3. countDigits - Count digits");
        AddText("4. percentUppercase - Percentage uppercase");
        AddText("5. textLength - Get text length");
        AddText("6. displayTextStats - Show text statistics");
        AddText("7. veryStrongPassword - Check very strong password");
        AddText("8. generateKey - Generate random key");
        AddText("9. isHexKey - Check hexadecimal format");
        AddText("10. generateRandomPassword - Generate password");
        AddText("11. passwordScore - Calculate password score");
        AddText("12. averageScore - Average password score");
        AddText("13. displaySecurityReport - Show security report");
        AddText("14. countStrongUsers - Count users with strong passwords");
        AddText("15. showSecurityTips - Display security tips");
        AddText("16. checkEmailFormat - Validate email format");
        AddText("17. checkLoginFormat - Validate login format");
        AddText("18. generateHexKey - Generate hex key");
        AddText("19. top3Passwords - Show top 3 passwords");
        AddText("20. globalSecurityLevel - Calculate global security level");
        AddText("");
        
        // Show password test
        AddText("Password Test:");
        AddText("--------------");
        AddText("Testing password: 'Password123!'");
        
        // Manually calculate password score (simplified)
        char* testPass = "Password123!";
        int length = 0;
        while (testPass[length] != '\0') length++;
        
        int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
        for (int i = 0; i < length; i++) {
            if (testPass[i] >= 'A' && testPass[i] <= 'Z') hasUpper = 1;
            if (testPass[i] >= 'a' && testPass[i] <= 'z') hasLower = 1;
            if (testPass[i] >= '0' && testPass[i] <= '9') hasDigit = 1;
            if (testPass[i] == '!' || testPass[i] == '@' || testPass[i] == '#') hasSpecial = 1;
        }
        
        int score = 30; // Base
        score += (length - 8) * 2; // Length bonus
        if (hasUpper) score += 20;
        if (hasLower) score += 20;
        if (hasDigit) score += 15;
        if (hasSpecial) score += 15;
        
        if (score > 100) score = 100;
        
        char scoreMsg[50] = "Estimated score: ";
        char scoreStr[10];
        int temp = score;
        int pos = 0;
        
        if (temp == 0) {
            scoreStr[0] = '0';
            scoreStr[1] = '\0';
            pos = 1;
        } else {
            char tempStr[10];
            int d = 0;
            while (temp > 0) {
                tempStr[d++] = (temp % 10) + '0';
                temp /= 10;
            }
            // Reverse
            for (int i = 0; i < d; i++) {
                scoreStr[i] = tempStr[d - 1 - i];
            }
            scoreStr[d] = '\0';
            pos = d;
        }
        
        // Add to message
        for (int i = 0; i < pos; i++) {
            scoreMsg[17 + i] = scoreStr[i];
        }
        scoreMsg[17 + pos] = '/';
        scoreMsg[18 + pos] = '1';
        scoreMsg[19 + pos] = '0';
        scoreMsg[20 + pos] = '0';
        scoreMsg[21 + pos] = '\0';
        AddText(scoreMsg);
        
    }
    else {
        // Other libraries (coming soon)
        AddText("=== LIBRARY IN DEVELOPMENT ===");
        AddText("");
        AddText("This library is not implemented yet!");
        AddText("Check back later for updates.");
        AddText("");
        AddText("Press GO button again to select another library.");
    }
    
    // Add back button instruction
    AddText("");
    AddText("=================================");
    AddText("Press GO button to return to main menu");
}
void ReturnToMainMenu() {
    LoadLibraryList();
}

void ShowUserManagementMenu(void) {
    SendMessageA(hListBox, LB_RESETCONTENT, 0, 0);
    
    AddText("=== USER MANAGEMENT FUNCTIONS ===");
    AddText("");
    AddText("Select a function:");
    AddText("------------------");
    AddText("1. View All Users");
    AddText("2. Add New User");
    AddText("3. Delete User");
    AddText("4. Search User");
    AddText("5. Change Password");
    AddText("6. Block/Unblock User");
    AddText("7. Change User Role");
    AddText("8. User Statistics");
    AddText("9. Save Users to File");
    AddText("10. Load Users from File");
    AddText("");
    AddText("Press GO to execute selected function");
    AddText("or double-click a function");
}

void ExecuteSelectedFunction(void) {
    int selected = SendMessageA(hListBox, LB_GETCURSEL, 0, 0);
    
    if (selected == LB_ERR) {
        MessageBoxA(hListBox, "Please select a function first!", "No Selection", MB_OK);
        return;
    }
    
    char buffer[100];
    SendMessageA(hListBox, LB_GETTEXT, selected, (LPARAM)buffer);
    
    // Get first line to know which library we're in
    char firstLine[100];
    SendMessageA(hListBox, LB_GETTEXT, 0, (LPARAM)firstLine);
    
    if (strstr(firstLine, "USER MANAGEMENT")) {
        // User Management functions
        if (strstr(buffer, "View All Users")) {
            // Call your displayUsers function
            // We'll implement this next
            ShowAllUsers();
        }
        else if (strstr(buffer, "Add New User")) {
            // We'll create the add user dialog here
            ShowAddUserDialog();
        }
        // ... other user functions
    }
    else if (strstr(firstLine, "MATH & SECURITY TOOLS")) {
        // Math functions
        if (strstr(buffer, "Prime Check")) {
            ShowPrimeCheckDialog();
        }
        // ... other math functions
    }
    // ... etc for other libraries
}

void ShowAllUsers(void) {
    SendMessageA(hListBox, LB_RESETCONTENT, 0, 0);
    
    AddText("=== ALL USERS ===");
    AddText("");
    
    int userCount = 0;
    int activeCount = 0;
    
    for (int i = 0; i < MAX_USERS; i++) {
        if (users[i].state != 999) { // Not deleted
            userCount++;
            
            char userLine[100];
            
            // Number
            char numStr[10];
            int temp = userCount;
            int pos = 0;
            
            if (temp == 0) {
                numStr[0] = '0';
                numStr[1] = '\0';
                pos = 1;
            } else {
                char tempStr[10];
                int d = 0;
                while (temp > 0) {
                    tempStr[d++] = (temp % 10) + '0';
                    temp /= 10;
                }
                // Reverse
                for (int j = 0; j < d; j++) {
                    numStr[j] = tempStr[d - 1 - j];
                }
                numStr[d] = '\0';
                pos = d;
            }
            
            // Build line: "1. username (Role) [Status]"
            userLine[0] = '\0';
            
            // Add number
            for (int j = 0; j < pos; j++) {
                userLine[j] = numStr[j];
            }
            userLine[pos] = '.';
            userLine[pos + 1] = ' ';
            
            // Add username
            int k = 0;
            while (users[i].name[k] != '\0' && k < 20) {
                userLine[pos + 2 + k] = users[i].name[k];
                k++;
            }
            userLine[pos + 2 + k] = ' ';
            userLine[pos + 3 + k] = '(';
            
            // Add role
            if (users[i].role == 1) {
                userLine[pos + 4 + k] = 'A';
                userLine[pos + 5 + k] = 'd';
                userLine[pos + 6 + k] = 'm';
                userLine[pos + 7 + k] = 'i';
                userLine[pos + 8 + k] = 'n';
                pos += 5;
            } else {
                userLine[pos + 4 + k] = 'U';
                userLine[pos + 5 + k] = 's';
                userLine[pos + 6 + k] = 'e';
                userLine[pos + 7 + k] = 'r';
                pos += 4;
            }
            
            userLine[pos + 9 + k] = ')';
            userLine[pos + 10 + k] = ' ';
            userLine[pos + 11 + k] = '[';
            
            // Add status
            if (users[i].state == 0) {
                userLine[pos + 12 + k] = 'A';
                userLine[pos + 13 + k] = 'c';
                userLine[pos + 14 + k] = 't';
                userLine[pos + 15 + k] = 'i';
                userLine[pos + 16 + k] = 'v';
                userLine[pos + 17 + k] = 'e';
                pos += 6;
            } else if (users[i].state == 1) {
                userLine[pos + 12 + k] = 'B';
                userLine[pos + 13 + k] = 'l';
                userLine[pos + 14 + k] = 'o';
                userLine[pos + 15 + k] = 'c';
                userLine[pos + 16 + k] = 'k';
                userLine[pos + 17 + k] = 'e';
                userLine[pos + 18 + k] = 'd';
                pos += 7;
            } else {
                userLine[pos + 12 + k] = 'D';
                userLine[pos + 13 + k] = 'e';
                userLine[pos + 14 + k] = 'l';
                userLine[pos + 15 + k] = 'e';
                userLine[pos + 16 + k] = 't';
                userLine[pos + 17 + k] = 'e';
                userLine[pos + 18 + k] = 'd';
                pos += 7;
            }
            
            userLine[pos + 19 + k] = ']';
            userLine[pos + 20 + k] = '\0';
            
            AddText(userLine);
            
            if (users[i].state == 0) activeCount++;
        }
    }
    
    if (userCount == 0) {
        AddText("No users found!");
    }
    
    AddText("");
    
    // Show summary
    char summary[100] = "Total: ";
    char countStr[10];
    int temp = userCount;
    int pos = 0;
    
    if (temp == 0) {
        countStr[0] = '0';
        countStr[1] = '\0';
        pos = 1;
    } else {
        char tempStr[10];
        int d = 0;
        while (temp > 0) {
            tempStr[d++] = (temp % 10) + '0';
            temp /= 10;
        }
        // Reverse
        for (int j = 0; j < d; j++) {
            countStr[j] = tempStr[d - 1 - j];
        }
        countStr[d] = '\0';
        pos = d;
    }
    
    // Add to summary
    for (int j = 0; j < pos; j++) {
        summary[7 + j] = countStr[j];
    }
    summary[7 + pos] = ' ';
    summary[8 + pos] = 'u';
    summary[9 + pos] = 's';
    summary[10 + pos] = 'e';
    summary[11 + pos] = 'r';
    summary[12 + pos] = 's';
    summary[13 + pos] = ' ';
    summary[14 + pos] = '(';
    
    // Add active count
    temp = activeCount;
    pos = 0;
    if (temp == 0) {
        countStr[0] = '0';
        countStr[1] = '\0';
        pos = 1;
    } else {
        char tempStr[10];
        int d = 0;
        while (temp > 0) {
            tempStr[d++] = (temp % 10) + '0';
            temp /= 10;
        }
        // Reverse
        for (int j = 0; j < d; j++) {
            countStr[j] = tempStr[d - 1 - j];
        }
        countStr[d] = '\0';
        pos = d;
    }
    
    for (int j = 0; j < pos; j++) {
        summary[15 + j] = countStr[j];
    }
    summary[15 + pos] = ' ';
    summary[16 + pos] = 'a';
    summary[17 + pos] = 'c';
    summary[18 + pos] = 't';
    summary[19 + pos] = 'i';
    summary[20 + pos] = 'v';
    summary[21 + pos] = 'e';
    summary[22 + pos] = ')';
    summary[23 + pos] = '\0';
    
    AddText(summary);
    AddText("");
    AddText("Press GO to return to User Management menu");
    
}

// Stub implementations for unimplemented functions
void ShowMathToolsMenu(void) {
    SendMessageA(hListBox, LB_RESETCONTENT, 0, 0);
    AddText("=== MATH TOOLS FUNCTIONS ===");
    AddText("");
    AddText("Coming Soon!");
    AddText("");
    AddText("Press GO to return to main menu");
}

void ShowAuditMenu(void) {
    SendMessageA(hListBox, LB_RESETCONTENT, 0, 0);
    AddText("=== SECURITY AUDIT FUNCTIONS ===");
    AddText("");
    AddText("Coming Soon!");
    AddText("");
    AddText("Press GO to return to main menu");
}

void ShowAddUserDialog(void) {
    // Simple implementation for now - we'll make it better
    SendMessageA(hListBox, LB_RESETCONTENT, 0, 0);
    AddText("=== ADD NEW USER ===");
    AddText("");
    AddText("This feature is under construction!");
    AddText("");
    AddText("For now, using default user data...");
    
    // Find first empty slot
    int slot = -1;
    for (int i = 0; i < MAX_USERS; i++) {
        if (users[i].state == 999) { // Deleted slot
            slot = i;
            break;
        }
    }
    
    if (slot == -1) {
        AddText("ERROR: User database full!");
    } else {
        // Add a test user
        stringModify(users[slot].name, "TestUser");
        stringModify(users[slot].password, "Password123!");
        users[slot].role = 0; // Regular user
        users[slot].state = 0; // Active
        
        AddText("Test user added: TestUser");
        AddText("Password: Password123!");
        AddText("Role: Regular User");
        AddText("Status: Active");
    }
    
    AddText("");
    AddText("Press GO to return to User Management");
}

void ShowPrimeCheckDialog(void) {
    SendMessageA(hListBox, LB_RESETCONTENT, 0, 0);
    AddText("=== PRIME NUMBER CHECKER ===");
    AddText("");
    AddText("Coming Soon!");
    AddText("");
    AddText("Press GO to return to Math Tools menu");
}