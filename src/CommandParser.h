#pragma once

#include <string>
#include <queue>
#include "Actions.h"
#include "FileStream.h"

typedef std::map<std::string, Action*(*)(double)> _pmap;

class CommandParser
{
public:
    CommandParser(std::string filename);
    ~CommandParser(void);

    void parse(std::queue<Action*> &queue);
private:
    FileStream m_input;
    static const _pmap parseMap;
};

template <class A>
Action* createAction(double value);
