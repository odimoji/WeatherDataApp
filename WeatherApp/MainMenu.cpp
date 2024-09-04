//
// Created by Odinaka on 17/04/2024.
//

#include "MainMenu.h"
#include "Location_management.h"
#include "WeatherForecast.h"
#include "HistoricalWeather.h"
#include "AirQuality.h"



void MainMenu::menu() {
    // void password_user();//login declaration
    //password_user();//login screen
    while (true)
    {
        int choice;
        char x;
        system("cls");
        cout << "\n\t\t\t-------------------------------------------";
        cout << "\n\t\t\t        WEATHER APPLICATION                ";
        cout << "\n\t\t\t-------------------------------------------";
        cout << "\n\t\t\t|1|      Location Management               ";
        cout << "\n\t\t\t|2|      Weather Forecast                  ";
        cout << "\n\t\t\t|3|      Historical Weather                ";
        cout << "\n\t\t\t|4|      Air Quality                       ";
        cout << "\n\t\t\t|5|      Extra Features                    ";
        cout << "\n\t\t\t|6|             Exit                       ";
        cout << "\n\t\t\t       ENTER [1][2][3][4][5][6]            ";
        cout << "\n\n            Please Enter a Value:              ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                do{Location_management locationMenu;
                    locationMenu.menu();
                    cout <<"\n\n\t\t\t Add another Location (Y/N):";
                    cin >> x;
                } while (x == 'Y' || x == 'y');
                break;
            case 2:
                do{
                    WeatherForecast wfMenu;
                    wfMenu.menu();
                }while (x == 'Y' || x == 'y');
                break;
                //display();
                break;
            case 3:
                do{
                    HistoricalWeather hfMenu;
                    hfMenu.menu();
//                    modify();
                    cout <<"\n\n\t\t\t Would you like to modify another Employee Record(Y/N):";
                    cin>>x;
                }while(x == 'Y' || x == 'y' );
//                waitforenter();
                break;
            case 4:
                AirQuality aqMenu;
                aqMenu.menu();

                break;



        }
        getch();

    }
}
