#ifndef NOISE_H
#define NOISE_H

/**
 * @brief The Noise class is an interface for noise generators.
 * 
 * This class provides a common interface for different types of noise generators.
 * Subclasses of this class can implement their own noise generation algorithms.
 */
class Noise {
public:
    /**
     * @brief Generates a 2D array of noise values.
     * 
     * This method generates a 2D array of noise values based on the given dimensions.
     * The noise values can be used for terrain generation, procedural texture generation, etc.
     * 
     * @param x The width of the noise array.
     * @param y The height of the noise array.
     * @return A 2D array of noise values.
     */
    virtual double** generate(int x, int y) = 0;
};

#endif // NOISE_H