void Input::GetUserAction() 
{
      ....
      ....
      .....
        
        //[2] User clicks on the drawing area
        if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight && x >= 0) {
            // Sleep(x   * SECOND);
            // if (still click down):
            //  return DRAGGING;
            
            return DRAWING_AREA;
        }

        //[3] User clicks on the status bar
        return STATUS;
    }

}