#include <Windows.h>

struct ExchangeData
{
  int  iPluginAPI;
  int  iStarCraftBuild;
  BOOL bNotSCBWmodule;                //Inform user that closing BWL will shut down your plugin
  BOOL bConfigDialog;                 //Is Configurable
};
