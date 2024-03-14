#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include "noise.h"
#include <stdlib.h>

class PerlinNoise : public Noise
{
private:
    double frequency_;
    int permutation[256];

    void permute();
    int *getDir(int x);
    double fade(double t);
    double lerp(double t, double a, double b);

public:
    PerlinNoise(double frequency = 0.01) : frequency_(frequency)
    {
        for (int i = 0; i < 256; i++)
        {
            permutation[i] = i;
        }
        permute();
    }

    double generateSample(int x, int y);

    double **generate(int x, int y) override;

    double frequency() const { return frequency_; }
    void frequency(double frequency) { frequency_ = frequency; }

    void seed(int seed) { srand(seed); }
};

#endif // PERLIN_NOISE_H