#ifndef __VECTOR__
#define __VECTOR__

/**
 * 2D Vector class
 * Can represent positions, directions, offsets, or velocities in 2D space
 */
class Vector {
  private:
    float x;
    float y;

  public:
    Vector(float x = 0, float y = 0);

    float getX() const;

    float getY() const;

    void set(float x, float y);

    /**
     * Add another vector to this vector
     * Modifies this vector by adding the components of the given vector
     * @param vector The vector to add to this one
     */
    void sum(const Vector &vector);

    /**
     * Subtract another vector from this vector
     * Modifies this vector by subtracting the components of the given vector
     * @param vector The vector to subtract from this one
     */
    void sub(const Vector &vector);
};

#endif
