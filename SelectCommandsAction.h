#pragma once
#include "Action.h"

class Input;
class Output;
class Grid;
class GameState;

class SelectCommandsAction :
    public Action
{
private:
    int numSelected; // to track num of commands
    int maxCommands; // min(5, health)
public:
    SelectCommandsAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual ~SelectCommandsAction();

};

