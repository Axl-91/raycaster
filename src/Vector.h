#ifndef __VECTOR__
#define __VECTOR__

class Vector {
  private:
    float x;
    float y;

  public:
    Vector(float posX = 0, float posY = 0);

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

    /**
     * Calculate the distance between this vector and another vector
     * @param vector The other vector to calculate distance to
     * @return The Euclidean distance between the two vectors
     */
    float distance(const Vector &vector) const;

    ~Vector();
};

#endif
