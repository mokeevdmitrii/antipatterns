//
// Created by dmitry on 5/14/20.
//

#ifndef ANTIPATTERNS_ASTAR_H
#define ANTIPATTERNS_ASTAR_H

#include "Constants/GamePlayConstants.h"
#include <algorithm>
#include <set>
#include <vector>

class AStar {
public:
  struct Point {
    int x = 0;
    int y = 0;
    int f = 0;
    int g = 0;
    int h = 0; //из формул A*

    Point(int x_, int y_);

    Point() {}

    bool operator<(const Point &b) const;
  };

  struct cmp {
    bool operator()(Point a, Point b);
  };

  class Graph {
  private:
    std::vector<std::vector<int>>
        adj; //поле/матрица если мы не можем пройти по клетке, то ее значение -1
    std::vector<std::vector<bool>>
        open_list_bool; //проверка в открытом списке или нет
    std::vector<std::vector<bool>>
        close_list; // проверка в закрытом списке по индексу точки
    int count_in_open_list = 0;
    int width = 0;
    int length = 0;

  public:
    Graph() = default;

    explicit Graph(const std::vector<std::vector<int>> &map);

    std::pair<int, int> size();

    int GetWidth();

    int GetLength();

    int h(const Point &end, const Point &now);

    int g(const Point &current, const Point &now);

    void MyErase(const Point &now, std::set<Point, cmp> &open_list);

    void change_g_h_f(const Point &current, Point &now,
                      std::set<Point, cmp> &open_list,
                      std::vector<std::vector<std::pair<int, int>>> &parents);

    bool inside_close_list(const Point &now);

    bool inside_open_list(const Point &now);

    void assign_h_g_f(const Point& end, Point &current, Point &now,
                      std::set<Point, cmp> &open_list,
                      std::vector<std::vector<std::pair<int, int>>> &parents,
                      bool &status);

    void A_star(int x1, int y1, int x2, int y2,
                std::vector<std::vector<std::pair<int, int>>> &parents);
  };

private:
  Graph our_graph;

public:
  explicit AStar(const std::vector<std::vector<int>> &map);

  std::vector<std::pair<int, int>> AlgorithmAStar(std::pair<int, int> start,
                                                  std::pair<int, int> end);

  std::pair<int, int> GetPoint(std::pair<int, int> start,
                               std::pair<int, int> end);

  std::vector<std::pair<int, int>> GetRoad(std::pair<int, int> start,
                                           std::pair<int, int> end);
};

#endif // ANTIPATTERNS_ASTAR_H
