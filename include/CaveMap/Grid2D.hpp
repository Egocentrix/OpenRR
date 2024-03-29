#pragma once

#include <vector>

#include "CaveMapCommon.hpp"

template <class T>
class Grid2D
{
public:
    Grid2D() = default;
    Grid2D(int width, int height);

    void resize(int width, int height);
    void addElement(const T &elem);

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

    bool isEdgeElement(int x, int y) const;
    bool isEdgeElement(GridCoordinate coord) const;
    bool isInBounds(int x, int y) const;
    bool isInBounds(GridCoordinate coord) const;

    T &getElement(int x, int y);
    T &getElement(GridCoordinate coord);
    const T &getElement(int x, int y) const;
    const T &getElement(GridCoordinate coord) const;

    // Enable range based for loops by forwarding the iterators
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    iterator begin() { return elements.begin(); }
    iterator end() { return elements.end(); }
    const_iterator begin() const { return elements.cbegin(); }
    const_iterator end() const { return elements.cend(); }

    std::vector<GridCoordinate> neighbourCoordinates(int x, int y, bool includeDiagonals = true, bool includeInvalid = false) const;
    std::vector<GridCoordinate> neighbourCoordinates(GridCoordinate coord, bool includeDiagonals = true, bool includeInvalid = false) const;
    std::vector<T *> neighboursOf(int x, int y, bool includeDiagonals = true, bool includeInvalid = false);
    std::vector<T *> neighboursOf(GridCoordinate coord, bool includeDiagonals = true, bool includeInvalid = false);

private:
    int linearIndex(int x, int y) const;
    int linearIndex(GridCoordinate coord) const;

    std::vector<T> elements{};

    int width_{0};
    int height_{0};
};

#include "Grid2D.tpp"
