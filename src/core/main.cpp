#include "App.h"

#ifdef NDEBUG
    #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") // esconde o cmd quando roda em release
#endif

int main()
{
    DadosApp dApp;
    dApp.dJanela.Nome = "ArvoreGen";

    App app(dApp);
    app.Run();

    return 0;
}