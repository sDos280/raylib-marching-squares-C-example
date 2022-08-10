#include "raylib.h"
#include "resources\open-simplex-noise.c"

float remap(float x, float in_min, float in_max, float out_min, float out_max);
int getTileCase(int topleft, int topright, int buttomleft, int buttomright);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;

    const int rows = 400;
    const int columns = 400;

    const float squareSizeX = (float)screenWidth/(columns - 1);
    const float squareSizeY = (float)screenHeight/(rows - 1);

    float grid[columns][rows];

    float offsetz  = 0;

    struct osn_context *ctx;
    open_simplex_noise(GetRandomValue(1, 100), &ctx);

    InitWindow(screenWidth, screenHeight, "raylib [other] example - marching squres algorithm");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        offsetz += 0.01f;

        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < columns; c++)
            {
                // getting valuse from the open simplex noise
                grid[c][r] = remap((float)open_simplex_noise3(ctx, c*0.03, r*0.03, offsetz), -1, 1, 0, 1); 
            }
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            for (int r = 0; r < rows - 1; r++)
            {
                for (int c = 0; c < columns - 1; c++)
                {
                    // geting square case    see all the cases(and more information) in here: https://en.wikipedia.org/wiki/Marching_squares#Basic_algorithm
                    int Case = getTileCase((grid[c][r]) >= 0.5f ? 1 : 0, (grid[c + 1][r]) >= 0.5f ? 1 : 0, (grid[c][r + 1]) >= 0.5f ? 1 : 0, (grid[c + 1][r + 1]) >= 0.5f ? 1 : 0);

                    // geting square vertices position 
                    Vector2 topleftPoint = (Vector2){c * squareSizeX, r * squareSizeY};
                    Vector2 toprightPoint = (Vector2){(c + 1) * squareSizeX, r * squareSizeY};
                    Vector2 buttomleftPoint = (Vector2){c * squareSizeX, (r + 1) * squareSizeY};
                    Vector2 buttomrightPoint = (Vector2){(c + 1) * squareSizeX, (r + 1) * squareSizeY};

                    // geting square midle sides vertex position 
                    Vector2 middleupPoint = (Vector2){(topleftPoint.x + toprightPoint.x) * 0.5f, (topleftPoint.y + toprightPoint.y) * 0.5f};
                    Vector2 middledownPoint = (Vector2){(buttomleftPoint.x + buttomrightPoint.x) * 0.5f, (buttomleftPoint.y + buttomrightPoint.y) * 0.5f};
                    Vector2 middlerightPoint = (Vector2){(toprightPoint.x  + buttomrightPoint.x) * 0.5f, (toprightPoint.y + buttomrightPoint.y) * 0.5f};
                    Vector2 middleleftPoint = (Vector2){(topleftPoint.x + buttomleftPoint.x) * 0.5f, (topleftPoint.y + buttomleftPoint.y) * 0.5f};

                    // drawing the lines base on the case 
                    switch (Case)
                    {
                        case 0:
                            break;

                        case 1:
                            DrawLineV(middledownPoint, middleleftPoint, WHITE);
                            break;

                        case 2:
                            DrawLineV(middledownPoint, middlerightPoint, WHITE);
                            break;

                        case 3:
                            DrawLineV(middleleftPoint, middlerightPoint, WHITE);
                            break;

                        case 4:
                            DrawLineV(middleupPoint, middlerightPoint, WHITE);
                            break;

                        case 5:
                            DrawLineV(middleupPoint, middleleftPoint, WHITE);
                            DrawLineV(middledownPoint, middlerightPoint, WHITE);
                            break;

                        case 6:
                            DrawLineV(middleupPoint, middledownPoint, WHITE);
                            break;

                        case 7:
                            DrawLineV(middleupPoint, middleleftPoint, WHITE);
                            break;

                        case 8:
                            DrawLineV(middleupPoint, middleleftPoint, WHITE);
                            break;

                        case 9:
                            DrawLineV(middleupPoint, middledownPoint, WHITE);
                            break;

                        case 10:
                            DrawLineV(middleupPoint, middlerightPoint, WHITE);
                            DrawLineV(middledownPoint, middleleftPoint, WHITE);
                            break;

                        case 11:
                            DrawLineV(middleupPoint, middlerightPoint, WHITE);
                            break;

                        case 12:
                            DrawLineV(middleleftPoint, middlerightPoint, WHITE);
                            break;

                        case 13:
                            DrawLineV(middledownPoint, middlerightPoint, WHITE);
                            break;

                        case 14:
                            DrawLineV(middledownPoint, middleleftPoint, WHITE);
                            break;

                        case 15:
                            break;
                    }
                }
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    open_simplex_noise_free(ctx);

    CloseWindow();
    //--------------------------------------------------------------------------------------

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
