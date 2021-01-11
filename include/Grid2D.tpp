#include "Grid2D.hpp"

template <class T>
bool Grid2D<T>::isInBounds(int x, int y) const
{
    return x >= 0 && x < width && y >= 0 && y < height;
}

template <class T>
bool Grid2D<T>::isEdgeElement(int x, int y) const
{
    return x == 0 || x == width - 1 || y == 0 || y == height - 1;
}

template <class T>
int Grid2D<T>::linearIndex(int x, int y) const
{
    return x + width * y;
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
std::vector<GridCoordinate> Grid2D<T>::neighbourCoordinates(int x, int y, bool includeDiagonals) const
{
    std::vector<GridCoordinate> neighbours{};

    int dx[] = {0, -1, 1, 0, -1, -1, 1, 1};
    int dy[] = {-1, 0, 0, 1, -1, 1, -1, 1};

    for (int i = 0; i < (includeDiagonals ? 8 : 4); i++)
    {
        int currentx = x + dx[i];
        int currenty = y + dy[i];

        if (isInBounds(currentx, currenty))
        {
            neighbours.emplace_back(GridCoordinate{currentx, currenty});
        }
    }

    return (neighbours);
}

template <class T>
std::vector<T *> Grid2D<T>::neighboursOf(int x, int y, bool includeDiagonals)
{
    std::vector<T *> neighbours{};

    for (auto coords : neighbourCoordinates(x, y, includeDiagonals))
    {
        neighbours.push_back(&elements[linearIndex(coords.x, coords.y)]);
    }
    return neighbours;
}
