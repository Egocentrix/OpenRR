#pragma once

#include <vector>

struct GridCoordinate
{
    int x;
    int y;
};

template <class T>
class Grid2D
{
private:
    std::vector<T> elements{};

    int width{0};
    int height{0};

    int linearIndex(int x, int y) const;

public:
    Grid2D() = default;
    Grid2D(int width, int height);

    void resize(int width, int height);
    void addElement(const T& elem);

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    bool isEdgeElement(int x, int y) const;
    bool isInBounds(int x, int y) const;

    T &getElement(int x, int y);

    // Enable range based for loops by forwarding the iterators
    typename std::vector<T>::iterator begin() { return elements.begin(); }
    typename std::vector<T>::iterator end() { return elements.end(); }

    std::vector<GridCoordinate> neighboursOf(int x, int y, bool includeDiagonals = true) const;
};

#include "Grid2D.tpp"
