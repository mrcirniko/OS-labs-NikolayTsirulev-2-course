#pragma once

#include <iostream>
#include <list>
#include <set>

class Topology {
private:
    using listType = std::list<std::list<int>>;

    listType list;
public:
    Topology() : list() {}

    void insert(int id, int parentId);
    int find(int id);
    void erase(int id);
    int getFirstId(int listId);
    std::set<int> getSetOfChilds(int id);
};