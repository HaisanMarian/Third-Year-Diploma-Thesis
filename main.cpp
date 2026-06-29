#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOUSER
#include <windows.h>
#endif

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include "raylib.h"
#include "Point.h"
#include "LineSegment.h"


const Color BACKGROUND = { 18, 18, 18, 255 };
const Color SIDEBAR    = { 26, 26, 26, 255 };
const Color ACCENT     = { 0, 150, 255, 255 };
const Color CARD_BG    = { 35, 35, 35, 255 };
const Color INPUT_BG   = { 45, 45, 45, 255 };

struct InputField {
    char text[16];
    Rectangle rect;
    bool active;
    const char* label;
};

// Допоміжна функція для малювання кнопки з hover-ефектом
bool MyButton(Rectangle rect, const char* text, Color baseColor) {
    bool hover = CheckCollisionPointRec(GetMousePosition(), rect);
    Color color = hover ? ColorBrightness(baseColor, 0.2f) : baseColor;
    
    DrawRectangleRounded(rect, 0.2f, 8, color);
    DrawRectangleRoundedLines(rect, 0.2f, 8, Fade(WHITE, 0.1f));
    
    int fontSize = 18;
    int tw = MeasureText(text, fontSize);
    DrawText(text, rect.x + (rect.width - tw)/2, rect.y + (rect.height - fontSize)/2, fontSize, WHITE);
    
    return (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    const int screenWidth = 1200;
    const int screenHeight = 800;
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Geometry Pro | Modern UI");
    SetTargetFPS(60);

    Point p1(150, 150);
    Point p2(450, 350);
    LineSegment ls(p1, p2, "blue");

    InputField inputs[4] = {
        {"150", {40, 140, 110, 35}, false, "P1 X"},
        {"150", {170, 140, 110, 35}, false, "P1 Y"},
        {"450", {40, 220, 110, 35}, false, "P2 X"},
        {"350", {170, 220, 110, 35}, false, "P2 Y"}
    };

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < 4; i++) inputs[i].active = CheckCollisionPointRec(GetMousePosition(), inputs[i].rect);
        }

        for (int i = 0; i < 4; i++) {
            if (inputs[i].active) {
                int key = GetCharPressed();
                while (key > 0) {
                    if ((key >= '0' && key <= '9') || key == '.' || key == '-') {
                        int len = strlen(inputs[i].text);
                        if (len < 12) { inputs[i].text[len] = (char)key; inputs[i].text[len + 1] = '\0'; }
                    }
                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    int len = strlen(inputs[i].text);
                    if (len > 0) inputs[i].text[len - 1] = '\0';
                }
            }
        }

        BeginDrawing();
        ClearBackground(BACKGROUND);

        // --- SIDEBAR ---
        DrawRectangle(0, 0, 320, screenHeight, SIDEBAR);
        DrawRectangleLines(319, 0, 1, screenHeight, Fade(WHITE, 0.05f));
        
        DrawText("GEOMETRY INTERFACE", 35, 35, 22, ACCENT);
        DrawRectangle(35, 65, 40, 3, ACCENT);

        // Point Blocks
        for(int i=0; i<2; i++) {
            DrawText(i==0 ? "START POINT" : "END POINT", 40, 110 + i*80, 14, GRAY);
        }

        for (int i = 0; i < 4; i++) {
            DrawRectangleRounded(inputs[i].rect, 0.2f, 8, INPUT_BG);
            if(inputs[i].active) DrawRectangleRoundedLines(inputs[i].rect, 0.2f, 8, ACCENT);
            DrawText(inputs[i].text, inputs[i].rect.x + 10, inputs[i].rect.y + 10, 18, WHITE);
            DrawText(inputs[i].label, inputs[i].rect.x, inputs[i].rect.y - 18, 12, DARKGRAY);

        }
        if (MyButton({40, 240, 240, 45}, "hello", ACCENT)) {

        }

            if (MyButton({40, 290, 240, 45}, "APPLY CHANGES", ACCENT)) {
                ls = LineSegment(Point(atof(inputs[0].text), atof(inputs[1].text)),
                                 Point(atof(inputs[2].text), atof(inputs[3].text)));
            }

        if (MyButton({40, 350, 115, 40}, "SHIFT ++", {50, 180, 100, 255})) ++ls;
        if (MyButton({165, 350, 115, 40}, "SHIFT --", {180, 60, 60, 255})) --ls;

        // Info Card
        Rectangle infoCard = {35, 420, 250, 140};
        DrawRectangleRounded(infoCard, 0.1f, 8, CARD_BG);
        DrawText("PROPERTIES", infoCard.x + 15, infoCard.y + 15, 16, GRAY);
        DrawText(TextFormat("Length: %.2f px", ls.getLength()), infoCard.x + 15, infoCard.y + 45, 20, WHITE);
        Point mid = ls.getMidpoint();
        DrawText(TextFormat("Mid: %.1f, %.1f", mid.getX(), mid.getY()), infoCard.x + 15, infoCard.y + 85, 16, ACCENT);

        // --- CANVAS AREA ---
        int cX = 360, cY = 40, cW = 800, cH = 720;
        DrawRectangleRounded({(float)cX, (float)cY, (float)cW, (float)cH}, 0.05f, 12, CARD_BG);
        
        BeginScissorMode(cX, cY, cW, cH);
            // Сітка з прозорістю
            for (int i = 0; i <= cW; i += 50) DrawLine(cX + i, cY, cX + i, cY + cH, Fade(WHITE, 0.03f));
            for (int i = 0; i <= cH; i += 50) DrawLine(cX, cY + i, cX + cW, cY + i, Fade(WHITE, 0.03f));

            Point s = ls[0]; Point e = ls[1];
            // Glow effect (декілька напівпрозорих ліній)
            for(int i=1; i<=4; i++) DrawLineEx({(float)(cX + s.getX()), (float)(cY + s.getY())}, 
                                             {(float)(cX + e.getX()), (float)(cY + e.getY())}, 3.0f + i*2, Fade(ACCENT, 0.1f));
            
            DrawLineEx({(float)(cX + s.getX()), (float)(cY + s.getY())}, 
                       {(float)(cX + e.getX()), (float)(cY + e.getY())}, 3.0f, WHITE);


            DrawCircleGradient(cX + s.getX(), cY + s.getY(), 8, ACCENT, BLANK);
            DrawCircle(cX + s.getX(), cY + s.getY(), 5, WHITE);
            
            DrawCircleGradient(cX + e.getX(), cY + e.getY(), 8, ACCENT, BLANK);
            DrawCircle(cX + e.getX(), cY + e.getY(), 5, WHITE);

            DrawCircle(cX + mid.getX(), cY + mid.getY(), 4, YELLOW);
        EndScissorMode();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}





