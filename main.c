#include "raylib.h"
#include "open-simplex-noise.c"

float remap(float x, float in_min, float in_max, float out_min, float out_max);
int getTileCase(int topleft, int topright, int buttomleft, int buttomright);

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;

    const int rows = 400;
    const int columns = 400;

    const float tile_x = (float)screenWidth / (columns - 1);
    const float tile_y = (float)screenHeight / (rows - 1);

    float grid[columns][rows];

    double offset  = 0;

    struct osn_context *ctx;
    open_simplex_noise(GetRandomValue(1, 100), &ctx);

    InitWindow(screenWidth, screenHeight, "raylib [other] example - marching squres algorithm");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        offset += 0.01f;

        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < columns; c++)
            {
                grid[c][r] = remap((float)open_simplex_noise3(ctx, c*0.03, r*0.03, offset), -1, 1, 0, 1); 
            }
        }

        BeginDrawing();

            ClearBackground(BLACK);

            for (int r = 0; r < rows - 1; r++)
            {
                for (int c = 0; c < columns - 1; c++)
                {
                    int Case = getTileCase(grid[c][r] >= 0.5f ? 1 : 0, grid[c + 1][r] >= 0.5f ? 1 : 0, grid[c][r + 1] >= 0.5f ? 1 : 0, grid[c + 1][r + 1] >= 0.5f ? 1 : 0);

                    Vector2 topleftPoint = (Vector2){c * tile_x, r * tile_y};
                    Vector2 toprightPoint = (Vector2){(c + 1) * tile_x, r * tile_y};
                    Vector2 buttomleftPoint = (Vector2){c * tile_x, (r + 1) * tile_y};
                    Vector2 buttomrightPoint = (Vector2){(c + 1) * tile_x, (r + 1) * tile_y};

                    Vector2 middleUpPoint = (Vector2){(topleftPoint.x + toprightPoint.x) * 0.5f, (topleftPoint.y + toprightPoint.y) * 0.5f};
                    Vector2 middleDownPoint = (Vector2){(buttomleftPoint.x + buttomrightPoint.x) * 0.5f, (buttomleftPoint.y + buttomrightPoint.y) * 0.5f};
                    Vector2 middleRightPoint = (Vector2){(toprightPoint.x  + buttomrightPoint.x) * 0.5f, (toprightPoint.y + buttomrightPoint.y) * 0.5f};
                    Vector2 middleLeftPoint = (Vector2){(topleftPoint.x + buttomleftPoint.x) * 0.5f, (topleftPoint.y + buttomleftPoint.y) * 0.5f};

                    switch (Case)
                    {
                        case 0:
                            break;

                        case 1:
                            DrawLineV(middleDownPoint, middleLeftPoint, WHITE);
                            break;

                        case 2:
                            DrawLineV(middleDownPoint, middleRightPoint, WHITE);
                            break;

                        case 3:
                            DrawLineV(middleLeftPoint, middleRightPoint, WHITE);
                            break;

                        case 4:
                            DrawLineV(middleUpPoint, middleRightPoint, WHITE);
                            break;

                        case 5:
                            DrawLineV(middleUpPoint, middleLeftPoint, WHITE);
                            DrawLineV(middleDownPoint, middleRightPoint, WHITE);
                            break;

                        case 6:
                            DrawLineV(middleUpPoint, middleDownPoint, WHITE);
                            break;

                        case 7:
                            DrawLineV(middleUpPoint, middleLeftPoint, WHITE);
                            break;

                        case 8:
                            DrawLineV(middleUpPoint, middleLeftPoint, WHITE);
                            break;

                        case 9:
                            DrawLineV(middleUpPoint, middleDownPoint, WHITE);
                            break;

                        case 10:
                            DrawLineV(middleUpPoint, middleRightPoint, WHITE);
                            DrawLineV(middleDownPoint, middleLeftPoint, WHITE);
                            break;

                        case 11:
                            DrawLineV(middleUpPoint, middleRightPoint, WHITE);
                            break;

                        case 12:
                            DrawLineV(middleLeftPoint, middleRightPoint, WHITE);
                            break;

                        case 13:
                            DrawLineV(middleDownPoint, middleRightPoint, WHITE);
                            break;

                        case 14:
                            DrawLineV(middleDownPoint, middleLeftPoint, WHITE);
                            break;

                        case 15:
                            break;
                    }
                }
            }

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    
    open_simplex_noise_free(ctx);

    return 0;
}

int getTileCase(int topleft, int topright, int buttomleft, int buttomright)
{
    return topleft * 8 + topright * 4 + buttomright * 2 + buttomleft;
}

float remap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
