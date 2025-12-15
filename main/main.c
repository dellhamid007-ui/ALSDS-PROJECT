
#include <stdio.h>
#include "../USRMGMT/USRMGMT.h"
#include "../AUDSEC/AUDSEC.h"
#include "../MTHSEC/MTHSEC.h"
#include "../include/raylib.h"

    int main() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Raylib Test");
    SetTargetFPS(60);
    
    // Colors
    Color bgColor = {40, 44, 52, 255};      // Dark blue-gray
    Color panelColor = {50, 54, 62, 255};   // Slightly lighter
    Color accentColor = {86, 98, 246, 255}; // Bright blue
    Color textColor = WHITE;
    
    // Simple button state
    Rectangle button = {300, 400, 200, 50};
    bool buttonHover = false;
    int clickCount = 0;
    
    // Animation variable
    float circleRadius = 50;
    float circleSpeed = 2.0f;
    bool circleGrowing = true;
    
    printf("Raylib initialized!\n");
    printf("Window: %dx%d\n", screenWidth, screenHeight);
    
    // Main loop
    while (!WindowShouldClose()) {
        // Update
        Vector2 mousePos = GetMousePosition();
        
        // Button hover check
        buttonHover = CheckCollisionPointRec(mousePos, button);
        
        // Button click
        if (buttonHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            clickCount++;
            printf("Button clicked! Count: %d\n", clickCount);
        }
        
        // Animated circle
        if (circleGrowing) {
            circleRadius += circleSpeed * GetFrameTime();
            if (circleRadius > 100) circleGrowing = false;
        } else {
            circleRadius -= circleSpeed * GetFrameTime();
            if (circleRadius < 30) circleGrowing = true;
        }
        
        // Draw
        BeginDrawing();
        
        // Background
        ClearBackground(bgColor);
        
        // Title
        DrawText("Raylib Works Perfectly!", 100, 50, 40, textColor);
        DrawText("Everything is configured correctly", 100, 100, 20, (Color){200, 200, 200, 255});
        
        // Info panel
        DrawRectangle(100, 150, 600, 200, panelColor);
        DrawRectangleLines(100, 150, 600, 200, (Color){70, 70, 70, 255});
        
        // System info
        DrawText(TextFormat("FPS: %d", GetFPS()), 120, 170, 20, GREEN);
        DrawText(TextFormat("Frame Time: %.3f ms", GetFrameTime()*1000), 120, 200, 20, LIGHTGRAY);
        DrawText(TextFormat("Mouse: (%.0f, %.0f)", mousePos.x, mousePos.y), 120, 230, 20, LIGHTGRAY);
        DrawText(TextFormat("Click Count: %d", clickCount), 120, 260, 20, YELLOW);
        
        // Animated circle
        DrawCircle(screenWidth/2, 300, circleRadius, accentColor);
        DrawCircleLines(screenWidth/2, 300, circleRadius + 5, WHITE);
        
        // Button
        DrawRectangleRec(button, buttonHover ? (Color){100, 110, 255, 255} : accentColor);
        DrawRectangleLinesEx(button, 2, WHITE);
        DrawText("Click Me!", button.x + 50, button.y + 15, 20, WHITE);
        
        // Some shapes for visual test
        DrawRectangle(150, 400, 50, 50, RED);
        DrawRectangleLines(155, 405, 40, 40, WHITE);
        
        DrawCircle(250, 425, 25, GREEN);
        DrawCircleLines(250, 425, 30, WHITE);
        
        DrawTriangle((Vector2){350, 400}, 
                    (Vector2){325, 450}, 
                    (Vector2){375, 450}, BLUE);
        
        // Exit instruction
        DrawText("Press ESC or close window to exit", 250, 550, 18, LIGHTGRAY);
        
        EndDrawing();
    }
    
    CloseWindow();
    
    printf("Program exited cleanly.\n");
    return 0;
}