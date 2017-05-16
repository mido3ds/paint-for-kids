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
    color draw_clr = UI.DrawColor,
          last_draw_clr = draw_clr;
    int pen_width = UI.PenWidth,
        last_pen_width = pen_width;
};

#endif // !_CH_BORDER_