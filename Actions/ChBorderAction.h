#ifndef _CH_BORDER_
#define _CH_BORDER_

#include "../ApplicationManager.h"
#include "../CMUgraphicsLib/colors.h"
#include "../Figures/CRectangle.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class ChBorderAction : public Action {
public:
    ChBorderAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();

    virtual void Execute();

    virtual void Undo();

private:
    color C = UI.DrawColor,
          lastC = C;
    int w = UI.PenWidth,
        lastW = w;
};

#endif // !_CH_BORDER_
