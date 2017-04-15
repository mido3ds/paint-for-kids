#ifndef __CH_FILL_COLOR__
#define __CH_FILL_COLOR__

#include "../ApplicationManager.h"
#include "../CMUgraphicsLib/colors.h"
#include "../Figures/CRectangle.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class ChFillColorAction : public Action {
public:
    ChFillColorAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();

    virtual void Execute();

    virtual void Undo();

private:
    color C = UI.FillColor,
          lastC = C;
};

#endif // !_CH_FILL_COLOR_
