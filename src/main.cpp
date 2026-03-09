#include <iostream>
#include <filesystem>
#ifdef _WIN32
#include <windows.h>
#endif
#include "steam-nocloud-noupdates/cloud_disable.hpp"
#include "steam-nocloud-noupdates/autoupdate_disable.hpp"
#include "steam-nocloud-noupdates/utility.hpp"

using namespace std;

int main()
{
#ifdef _WIN32
    SetConsoleTitleA("Steam NoCloud NoUpdates");
#endif

    try
    {
        FileUtility fileUtility;
        string steamRoot = fileUtility.resolveSteamRoot();
        string userDataPath = steamRoot + "/userdata";
        string steamAppsPath = steamRoot + "/steamapps";

        while (true)
        {
            cout << endl;
            cout << ">Enter 0 to change Steam directory" << endl;
            cout << ">Enter 1 to disable Steam Cloud for all games (per-game settings)" << endl;
            cout << ">Enter 2 to disable Auto-updates and Unschedule all game and Workshop updates" << endl;
            cout << ">Enter 3 to exit" << endl;
            cout << ">Select your option: " << endl;
            string input;
            cout << ">";
            getline(cin, input);
            cout << endl;

            if (input == "0")
            {
                steamRoot = fileUtility.promptSteamRoot();
                userDataPath = steamRoot + "/userdata";
                steamAppsPath = steamRoot + "/steamapps";
                cout << ">Steam directory updated to: " << steamRoot << endl;
            }
            else if (input == "1")
            {
                string acfIds = fileUtility.getAcfID(steamAppsPath);
                if (acfIds.empty())
                {
                    cout << ">There are no games in your steamapps folder" << endl;
                    continue;
                }
                
                CloudDisabler cloudDisabler;
                cloudDisabler.iterateSharedConfig(userDataPath, acfIds);
                cout << ">Success" << endl;
            }
            else if (input == "2")
            {
                string acfIds = fileUtility.getAcfID(steamAppsPath);
                if (acfIds.empty())
                {
                    cout << ">There are no games in your steamapps folder" << endl;
                    continue;
                }

                AutoUpdateDisabler autoUpdateDisabler;
                autoUpdateDisabler.iterateSteamApps(steamAppsPath);
                cout << ">Success" << endl;
            }
            else if (input == "3")
            {
                break;
            }
            else
            {
                cout << ">Invalid input" << endl;
            }
        }
    }
    catch (const exception &e)
    {
        cerr << ">Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
