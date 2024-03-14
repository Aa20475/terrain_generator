#include "perlin_noise.h"
#include <cmath>
#include <utility>
#include <stdlib.h>

double PerlinNoise::generateSample(int x, int y)
{
    double x_double = x * frequency();
    double y_double = y * frequency();

    const int X = static_cast<int>(std::floor(x_double)) & 255;
    const int Y = static_cast<int>(std::floor(y_double)) & 255;

    const double xf = x - std::floor(x);
    const double yf = y - std::floor(y);

    double* dots = new double[4];

    for (int i = 0; i < 4; i++)
    {
        int xDiff = (i % 2 == 0) ? 1 : 0;
        int yDiff = (i < 2) ? 1 : 0;

        int* constVector = getDir(permutation[permutation[X+xDiff] + Y+yDiff]);
        dots[i] = (xf - xDiff) * constVector[0] + (yf - yDiff) * constVector[1];
    }

    const double u = fade(xf);
    const double v = fade(yf);

    return lerp(u,
        lerp(v, dots[0], dots[1]),
        lerp(v, dots[3], dots[2])
    );
}

double **PerlinNoise::generate(int w, int h){
    double **noise = new double *[h];
    for (int i = 0; i < h; i++)
    {
        noise[i] = new double[w];
        for (int j = 0; j < w; j++)
        {
            noise[i][j] = generateSample(i, j);
        }
    }
    return noise;
}

void PerlinNoise::permute()
{
    for (int e = 255; e > 0; e--)
        std::swap(permutation[e], permutation[rand() % e]);
}

int *PerlinNoise::getDir(int x)
{
    int *direction = new int[2];
    x = x & 3;

    switch (x)
    {
    case 0:
        direction[0] = 1;
        direction[1] = 1;
        break;
    case 1:
        direction[0] = -1;
        direction[1] = 1;
        break;
    case 2:
        direction[0] = -1;
        direction[1] = -1;
        break;
    default:
        direction[0] = 1;
        direction[1] = -1;
        break;
    }

    return direction;
}

double PerlinNoise::fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::lerp(double t, double a, double b)
{
    return a + t * (b - a);
}