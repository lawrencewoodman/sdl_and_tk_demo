#include <tcl.h>
#include <tk.h>

#include "ball.h"
#include "ballscreen.h"

static Tcl_Interp *interp;

static int TkWin_displayWindow(void);
static void TkWin_createCommands(void);

int
TkWin_init(void)
{
  interp = Tcl_CreateInterp();
  if (Tcl_Init(interp) == TCL_ERROR) { return 0; }
  if (Tk_Init(interp) == TCL_ERROR) { return 0; }

  TkWin_createCommands();

  if (Tcl_EvalFile(interp, "sdl_and_tk.tcl") == TCL_ERROR ) {
    fprintf(stderr, "Error: Can't eval sdl_and_tk.tcl\n");
    return 0;
  }

  TkWin_displayWindow();

  return 1;
}

char *
TkWin_getWindowID(void)
{
  Tcl_Obj *result;

  if (Tcl_Eval(interp, "winfo id .screen") == TCL_ERROR)
    return NULL;

  result = Tcl_GetObjResult(interp);
  return Tcl_GetStringFromObj(result, NULL);
}

static int
TkWin_displayWindow(void)
{
  return Tcl_Eval(interp, "update");
}

static int
DestroyWindowCmd(ClientData clientData, Tcl_Interp *_interp,
                 int objc, Tcl_Obj *CONST objv[])
{
  if (objc != 1) {
    Tcl_WrongNumArgs(_interp, 1, objv, "");
  }

  Ball_destroy();
  BallScreen_destroy();
  Tcl_Eval(_interp, "exit");
  return TCL_OK;
}

static int
BallCmd(ClientData clientData, Tcl_Interp *_interp,
        int objc, Tcl_Obj *CONST objv[])
{
  char *direction;

  if (objc != 2) {
    Tcl_WrongNumArgs(_interp, 1, objv, "up|down|left|right");
    return TCL_ERROR;
  }

  direction = Tcl_GetString(objv[1]);

  if (strncmp(direction, "up", 2) == 0)
    Ball_up();
  else if (strncmp(direction, "down", 4) == 0)
    Ball_down();
  else if (strncmp(direction, "left", 4) == 0)
    Ball_left();
  else if (strncmp(direction, "right", 4) == 0)
    Ball_right();
  else {
    Tcl_AddErrorInfo(_interp,
      "Error: Should be ball up|down|left|right");
    return TCL_ERROR;
  }

  return TCL_OK;
}

static int
ScreenRefreshCmd(ClientData clientData, Tcl_Interp *_interp,
                 int objc, Tcl_Obj *CONST objv[])
{
  if (objc != 1) {
    Tcl_WrongNumArgs(_interp, 1, objv, "");
  }

  BallScreen_refresh();
  return TCL_OK;
}

static void
TkWin_createCommands(void)
{
  Tcl_CreateObjCommand(interp, "ball", BallCmd,
                       (ClientData) NULL,
                       (Tcl_CmdDeleteProc *) NULL);

  Tcl_CreateObjCommand(interp, "destroy_window", DestroyWindowCmd,
                       (ClientData) NULL,
                       (Tcl_CmdDeleteProc *) NULL);

  Tcl_CreateObjCommand(interp, "screen_refresh", ScreenRefreshCmd,
                       (ClientData) NULL,
                       (Tcl_CmdDeleteProc *) NULL);
}
