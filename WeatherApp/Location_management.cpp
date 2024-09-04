//
// Created by Odinaka on 24/03/2024.
//

#include "Location_management.h"

Location_management::Location_management(double tempLat, double tempLon, std::string tempCity, std::string tempCountry) {
    latitude = tempLat;
    longitude = tempLon;
    city = tempCity;
    country = tempCountry;
}
Location_management::Location_management() {}

void Location_management::menu() {
   // void password_user();//login declaration
   //password_user();//login screen
    while (true)
    {
        int choice;
        char x;
        system("cls");
        cout << "\n\t\t\t-------------------------------------------";
        cout << "\n\t\t\t   LOCATION    MANAGEMENT  OPTIONS         ";
        cout << "\n\t\t\t-------------------------------------------";
        cout << "\n\t\t\t|1|      Add New Location                  ";
        cout << "\n\t\t\t|2|      Display Locations                 ";
        cout << "\n\t\t\t|3|      Modify  Locations                 ";
        cout << "\n\t\t\t|4|      Set Favorite  Location            ";
        cout << "\n\t\t\t|5|      Remove  Location                  ";
        cout << "\n\t\t\t|6|             Exit                       ";
        cout << "\n\t\t\t       ENTER [1][2][3][4][5][6]            ";
        cout << "\n\n            Please Enter a Value:              ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                do{
                    insert();
                    cout <<"\n\n\t\t\t Add another Employee Record (Y/N):";
                    cin>>x;
                }while(x == 'Y' || x == 'y' );
//                waitforenter();
                break;
            case 2:
                display();
                break;
            case 3:
                do{
//                    modify();
                    cout <<"\n\n\t\t\t Would you like to modify another Employee Record(Y/N):";
                    cin>>x;
                }while(x == 'Y' || x == 'y' );
//                waitforenter();
                break;
            case 4:
                system("cls");
                cout<<"\n\t\t\t>>Weather App System by Odi Dimoji<<\n\n";
                system("pause");
                //password_user();

                break;

            default:
                cout<<"\n\n\t\t\t Invalid Entry, Please try again.\n\n\t\t\t";
                break;

        }
        getch();

    }
}

//const int MAX_LOCATIONS = 100; // maximum number of employees
//Location_management location[MAX_LOCATIONS]; // array of employee objects
//int numLocations = 0; // number of employees currently in the array


void Location_management::insert()
{
    system ("cls");


    // insert new employee record
    cout<<"\n-------------------------- Insert Data----------------------------";
    cout<< "\n Enter city:";
    cin>> city;
    cout << "\n Enter country:";
    cin>> country;

    Location_management newLocation = queryLocation(city, country);
    //cout << newLocation.city << endl;



   // numLocations++; // increment number of employees in the array

    // write employee data to file
    fstream file("Employee_record.txt", ios::app| ios::out);
    file << newLocation.city << " " << newLocation.country << " " << newLocation.latitude << " " << newLocation.longitude << "\n";
    file.close();
}

size_t Location_management::writeCallback(char* ptr, size_t size, size_t nmemb, std::string* data) {
    size_t totalSize = size * nmemb;
    data->append((char*)ptr, totalSize);
    return totalSize;/*
    data->append(ptr, size * nmemb);
    return size * nmemb;*/
}

Location_management Location_management::queryLocation(string city, string country) {

    CURL *curl;
    CURLcode res = CURLE_OK;
    std::string response;
    string url = "https://us1.locationiq.com/v1/search?key=pk.280c6bf4adafbd077c18180c59cc52a2&q=" + city + "%20" + country + "&format=json&";


    try {
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();


        if (curl) {

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Location_management::writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            } else {
                // Print the response
                Json jsonResponse = Json::parse(response);
                //std::cout << "Response: " << jsonResponse.dump(4) << std::endl;
                if (jsonResponse.is_array()) {
                    int index = 1;
                    // Iterate over the array elements
                    for (const auto &location: jsonResponse) {
                        // Extract and display the 'display_name' field for each location
                        cout << "[" << index << "]" << location["display_name"] << endl;
                        index++;
                    }
                    // Prompt the user to enter the index of their chosen location
                    int userIndex;
                    cout << "Enter the index of your chosen location: ";
                    cin >> userIndex;

                    // Check if the entered index is valid
                    if (userIndex >= 1 && userIndex <= jsonResponse.size()) {
                        // Extract the longitude and latitude of the chosen location
                        double longitude = std::stod(jsonResponse[userIndex - 1]["lon"].get<std::string>());
                        double latitude = std::stod(jsonResponse[userIndex - 1]["lat"].get<std::string>());


                        Location_management temp(latitude, longitude, city, country);

                        cout << "Longitude: " << longitude << ", Latitude: " << latitude << endl;
                        return temp;

                        // Now you can use longitude and latitude as needed


                    } else {
                        cerr << "Invalid index. Please enter a valid index." << endl;
                    }
                } else {
                    cerr << "Invalid JSON response format. Expected an array." << endl;
                }

                curl_easy_cleanup(curl);
            }

            // Cleanup

            curl_global_cleanup();

        }
    }catch(const std::exception& e){
        cerr << "Error parsing JSON response: " <<endl;
        cout << e.what() << endl;

    }



    // Initialize curl session

    return Location_management();
}


void Location_management::display(){

    system("cls");
    int total = 1;
    fstream file;
    cout<<"\n---------------------------Stored Locations----------------------------";
    file.open("Employee_Record.txt", ios::in);
    if(!file)
    {
        cout<<"\n\n\t\t No data is present..";
        file.close();
    }
    else
    {
        cout <<"\n-------------------------------------------------";
        cout <<"\n|| NAME     || ID      || AGE     ||      CTC         ";
        cout <<"\n-------------------------------------------------";
        while(file >> city >> country >> latitude >> longitude )
        {
            cout << "\n";
            cout << total++ <<" "<< city << "\t" << country <<"\t\t"<< latitude <<"\t\t"<< longitude ;
        }
        file.close();
    }
//    waitforenter();
}

Location_management Location_management::chooseLocation() {
    cout << "\n---------------------------Choose location----------------------------";
    display(); // Display all locations

    int selectedLocationIndex;
    cout << "\nEnter the index of the location you want to choose: ";
    cin >> selectedLocationIndex;

    // Read the file to find the selected location
    Location_management selectedLocation;
    fstream file("Employee_Record.txt", ios::in);
    if (!file) {
        cerr << "Error opening file!" << endl;
        // Handle the error appropriately
        return selectedLocation; // Return an empty location object
    } else {
        int index = 0;
        while (file >> selectedLocation.city >> selectedLocation.country >> selectedLocation.latitude >> selectedLocation.longitude) {
            if (index + 1 == selectedLocationIndex) {
                // Found the selected location
                break;
            }
            index++;
        }
        file.close();
    }

    cout << "Selected Location:" << endl;
    cout << "City: " << selectedLocation.getCity() << endl;
    cout << "Country: " << selectedLocation.getCountry() << endl;
    cout << "Latitude: " << selectedLocation.getLatitude() << endl;
    cout << "Longitude: " << selectedLocation.getLongitude() << endl;
    return selectedLocation; // Return the selected location
}

/*
void Location_management::modify()
{
    system("cls");
    char checkedid[5];
    int found = 0;
    fstream file, file1;
    cout<<"\n---------------------------Employee Modify Data----------------------------";
    file.open("Employee_Record.txt", ios::in);
    if(!file)
    {
        cout<<"\n\n\t\t No data is present..";
        file.close();
    }
    else
    {
        cout<<"\nEnter Employee ID:";
        cin >> checkedid;
        file1.open("record.txt",ios::app|ios::out);
        file >> city >> country >> longitude >> latitude;
        while(!file.eof())
        {
            if(strcmp(checkedid,city)==0)
            {
                cout<< "\n Enter Name of Employee:";
                cin>>location[numLocations].city;
                cout << "\n Enter Employee ID[4 DIGITS]:";
                cin>>location[numLocations].country;
                cout << "\n Enter Employee Age:";
                cin>>location[numLocations].latitude;
                cout << "\n Enter Employee salary(per hour):";
                cin>>location[numLocations].longitude;
                cout << "\nEmployee details successfully modified";
                file1 << location[numLocations-1].city << " " << location[numLocations-1].country << " " << location[numLocations-1].latitude << " " << location[numLocations-1].longitude << "\n";
                found++;
                break;


            }
            else
            {
                file1 << location[numLocations-1].city << " " << location[numLocations-1].country << " " << location[numLocations-1].latitude << " " << location[numLocations-1].longitude << "\n";
                file >> city >> country >> latitude >> longitude;
            }
            if (found==0);
            cout << "\n Employee ID not found, please try again.";
            system("pause");
            modify();

        }
        file1.close();
        file.close();
        remove("Employee_Record.txt");
        rename("record.txt","Employee_Record.txt");
    }
    waitforenter();

}
void Location_management::waitforenter()
{
    cout <<"\n\n Press ENTER to go back:";
    cin.get();
}


*/
const string &Location_management::getCity() const {
    return city;
}

void Location_management::setCity(const string &city) {
    Location_management::city = city;
}

const string &Location_management::getCountry() const {
    return country;
}

void Location_management::setCountry(const std::string &country) {
    Location_management::country = country;
}

double Location_management::getLatitude() const {
    return latitude;
}

void Location_management::setLatitude(double latitude) {
    Location_management::latitude = latitude;
}

double Location_management::getLongitude() const {
    return longitude;
}

void Location_management::setLongitude(double longitude) {
    Location_management::longitude = longitude;
}






