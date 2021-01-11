#include "Grid2D.hpp"

template <class T>
bool Grid2D<T>::isInBounds(int x, int y) const
{
    return x >= 0 && x < width && y >= 0 && y < height;
}

template <class T>
bool Grid2D<T>::isInBounds(GridCoordinate coord) const
{
    return isInBounds(coord.x, coord.y);
}

template <class T>
bool Grid2D<T>::isEdgeElement(int x, int y) const
{
    return x == 0 || x == width - 1 || y == 0 || y == height - 1;
}

template <class T>
bool Grid2D<T>::isEdgeElement(GridCoordinate coord) const
{
    return isEdgeElement(coord.x, coord.y);
}

template <class T>
int Grid2D<T>::linearIndex(int x, int y) const
{
    return x + width * y;
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
    width = newwidth;
    height = newheight;
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
std::vector<GridCoordinate> Grid2D<T>::neighbourCoordinates(int x, int y, bool includeDiagonals) const
{
    return neighbourCoordinates(GridCoordinate{x, y}, includeDiagonals);
}

template <class T>
std::vector<GridCoordinate> Grid2D<T>::neighbourCoordinates(GridCoordinate current, bool includeDiagonals) const
{
    std::vector<GridCoordinate> neighbours{};

    int dx[] = {0, -1, 1, 0, -1, -1, 1, 1};
    int dy[] = {-1, 0, 0, 1, -1, 1, -1, 1};

    for (int i = 0; i < (includeDiagonals ? 8 : 4); i++)
    {
        GridCoordinate neighbour = {current.x + dx[i], current.y + dy[i]};

        if (isInBounds(neighbour))
        {
            neighbours.push_back(neighbour);
        }
    }

    return neighbours;
}

template <class T>
std::vector<T *> Grid2D<T>::neighboursOf(int x, int y, bool includeDiagonals)
{
    return neighboursOf(GridCoordinate{x,y}, includeDiagonals);
}

template <class T>
std::vector<T *> Grid2D<T>::neighboursOf(GridCoordinate current, bool includeDiagonals)
{
    std::vector<T *> neighbours{};

    for (auto coord : neighbourCoordinates(current, includeDiagonals))
    {
        neighbours.push_back(&elements[linearIndex(coord)]);
    }
    return neighbours;
}
