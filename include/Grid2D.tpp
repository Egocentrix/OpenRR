#include "Grid2D.hpp"

template <class T>
bool Grid2D<T>::isInBounds(int x, int y) const
{
    return x >= 0 && x < width_ && y >= 0 && y < height_;
}

template <class T>
bool Grid2D<T>::isInBounds(GridCoordinate coord) const
{
    return isInBounds(coord.x, coord.y);
}

template <class T>
bool Grid2D<T>::isEdgeElement(int x, int y) const
{
    return x == 0 || x == width_ - 1 || y == 0 || y == height_ - 1;
}

template <class T>
bool Grid2D<T>::isEdgeElement(GridCoordinate coord) const
{
    return isEdgeElement(coord.x, coord.y);
}

template <class T>
int Grid2D<T>::linearIndex(int x, int y) const
{
    return x + width_ * y;
}

template <class T>
int Grid2D<T>::linearIndex(GridCoordinate coord) const
{
    return linearIndex(coord.x, coord.y);
}

template <class T>
Grid2D<T>::Grid2D(int width, int height)
{
    resize(width, height);
}

template <class T>
void Grid2D<T>::resize(int newwidth, int newheight)
{
    elements.clear();
    elements.reserve(newwidth * newheight);
    width_ = newwidth;
    height_ = newheight;
}

template <class T>
void Grid2D<T>::addElement(const T &elem)
{
    elements.push_back(elem);
}

template <class T>
T &Grid2D<T>::getElement(int x, int y)
{
    if (!isInBounds(x, y))
    {
        return elements.at(0);
    }
    return elements.at(linearIndex(x, y));
}

template <class T>
T &Grid2D<T>::getElement(GridCoordinate coord)
{
    return getElement(coord.x, coord.y);
}

template <class T>
std::vector<GridCoordinate> Grid2D<T>::neighbourCoordinates(int x, int y, bool includeDiagonals, bool includeInvalid) const
{
    return neighbourCoordinates(GridCoordinate{x, y}, includeDiagonals, includeInvalid);
}

template <class T>
std::vector<GridCoordinate> Grid2D<T>::neighbourCoordinates(GridCoordinate current, bool includeDiagonals, bool includeInvalid) const
{
    std::vector<GridCoordinate> neighbours{};

    // Starting North, clockwise
    int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

    for (int i = 0; i < 8; i += (includeDiagonals ? 1 : 2))
    {
        GridCoordinate neighbour = {current.x + dx[i], current.y + dy[i]};

        if (includeInvalid || isInBounds(neighbour)) //only check bounds if !includeInvalid
        {
            neighbours.push_back(neighbour);
        }
    }
    return neighbours;
}

template <class T>
std::vector<T *> Grid2D<T>::neighboursOf(int x, int y, bool includeDiagonals, bool includeInvalid)
{
    return neighboursOf(GridCoordinate{x, y}, includeDiagonals, includeInvalid);
}

template <class T>
std::vector<T *> Grid2D<T>::neighboursOf(GridCoordinate current, bool includeDiagonals, bool includeInvalid)
{
    std::vector<T *> neighbours{};

    for (auto coord : neighbourCoordinates(current, includeDiagonals, includeInvalid))
    {
        neighbours.push_back(&getElement(coord));
    }
    return neighbours;
}
