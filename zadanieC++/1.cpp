#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

void calculateHourlyAverage( vector<vector<string>>& data_array);
void calculateHalfHourlyAverage( vector<vector<string>>& data_array);
void calculateFiveMinuteAverage( vector<vector<string>>& data_array);

struct FiveMinuteData {
    double sum_U = 0.0;
    double sum_I = 0.0;
    int count = 0;
};


int main(int argc, char* argv[]) {

    string type = argv[2];
    if (argc != 3 || (type != "h" && type != "m30" && type != "m5")) {
        cout <<"Invalid input" << endl;
        return 1;}

    ifstream input_file("solar_panel_data_20240522.json");
    if (!input_file.is_open()) {
        cout << "Could not open the file!" << endl;
        return 1;}

    // Wektor  do przechowywania danych
    vector<vector<string>> data_array;


    string line,time,U,I;
    int start_time=49,number_time=14,long_value=5,t=39;
    int counter=0,i=0;
    string target_letter="U";
    while (getline(input_file, line)) {
        int occurrences_in_line = 0;
        int pos = line.find(target_letter);
        while (pos != string::npos) {//zlicza ilosc U w linii
            occurrences_in_line++;
            pos = line.find(target_letter, pos + 1);
        }
        i=0;
        while(i<occurrences_in_line){
            try{
                time=line.substr(start_time+i*t,number_time);
                U=line.substr(start_time+number_time+7+i*t,long_value);
                I=line.substr(start_time+number_time+17+i*t,long_value);//49+14=65+17=82+4=86, t=86-49=37
                double U_d=stod(U),I_d=stod(I);
                data_array.push_back({time, U, I});
                i++;
            }catch(exception&e)
            {
               //cerr << "Exception: " << e.what() << endl;
               counter+=1;
               break;
            }
        }

    }
    cout<<"Quantity of skipping line: "<<counter<<endl;
// Wybor funkcji
    if (type == "h") {
        calculateHourlyAverage(data_array);
    } else if (type == "m30") {
        calculateHalfHourlyAverage(data_array);
    } else if (type == "m5") {
        calculateFiveMinuteAverage(data_array);
    }

    return 0;
}

void calculateHourlyAverage( vector<vector<string>>& data_array) {
    // Przechowywanie napiecia, natezenia,liczby pomiarow
    vector<double> sum_U_per_hour(24, 0.0);
    vector<double> sum_I_per_hour(24, 0.0);
    vector<int> count_per_hour(24, 0);

    // czas,u,i
    for ( auto entry : data_array) {
        string timestamp = entry[0];
        double U = stod(entry[1]);
        double I = stod(entry[2]);
        int hour = stoi(timestamp.substr(8, 2));// Pobranie godziny z timestampu

        // Dodanie liczby pomiarow w danej godzinie
        sum_U_per_hour[hour] += U;
        sum_I_per_hour[hour] += I;
        count_per_hour[hour]++;
    }

    // Wyswietlenie
    cout << "Hour  Average U  Average I" << endl;
    cout << "----------------------------" << endl;
    for (int hour = 0; hour < 24; ++hour) {
        if (count_per_hour[hour] > 0) {
            double avg_U = sum_U_per_hour[hour] / count_per_hour[hour];
            double avg_I = sum_I_per_hour[hour] / count_per_hour[hour];
            cout << hour << ":00  " << round(avg_U*100)/ 100 << "        " << round(avg_I* 100)/ 100 << endl;
        }
    }
}


void calculateHalfHourlyAverage(vector<vector<string>>& data_array) {
    // Przechowywanie napiecia, natezenia,liczby pomiarow
    vector<FiveMinuteData> half_hourly_data(48);

    for ( auto entry : data_array) {//iteracja po kazdym elemencie
        string timestamp = entry[0];
        double U = stod(entry[1]);
        double I = stod(entry[2]);

        // Pobranie godziny i minuty
        int hour = stoi(timestamp.substr(8, 2));
        int minute = stoi(timestamp.substr(10, 2));

        // Okreslenie indeksu
        int half_hour_index = hour * 2 + (minute >= 30);//jesli wieksze od 30 to 1 jesli nie to 0

        half_hourly_data[half_hour_index].sum_U += U;
        half_hourly_data[half_hour_index].sum_I += I;
        half_hourly_data[half_hour_index].count++;
    }

    // Wyswietlenie
    cout << "Half Hour\tAverage U\tAverage I" << endl;
    cout << "--------------------------------------" << endl;
    for (int half_hour = 0; half_hour < 48; ++half_hour) {
        if (half_hourly_data[half_hour].count > 0) {
            double avg_U = half_hourly_data[half_hour].sum_U / half_hourly_data[half_hour].count;
            double avg_I = half_hourly_data[half_hour].sum_I / half_hourly_data[half_hour].count;
            int hour = half_hour / 2;
            int minute = (half_hour % 2) * 30;
            cout << hour << ":" << (minute < 10 ? "0" : "") << minute << "\t\t" << round(avg_U* 100)/ 100 << "\t\t" << round(avg_I* 100)/ 100 << endl;
        }
    }
}



void calculateFiveMinuteAverage(vector<vector<string>>& data_array) {
    // Przechowywanie sumy napiecia, sumy natezenia i liczby pomiarow dla kazdej 5-minutowej
    vector<FiveMinuteData> five_minute_data(288);

    // Iteracja po wszystkich odczytanych danych
    for ( auto entry : data_array) {
        string timestamp = entry[0];
        double U = stod(entry[1]);//konwersja na double
        double I = stod(entry[2]);

        // Pobranie godziny i minuty
        int hour = stoi(timestamp.substr(8, 2));
        int minute = stoi(timestamp.substr(10, 2));

        // Okreslenie indeksu
        int five_minute_index = hour * 12 + minute / 5;


        five_minute_data[five_minute_index].sum_U += U;
        five_minute_data[five_minute_index].sum_I += I;
        five_minute_data[five_minute_index].count++;
    }

    // Wyswietlenie
    cout << "5 Minutest\tAverage U\tAverage I" << endl;
    cout << "------------------------------------------" << endl;
    for (int i = 0; i < 288; ++i) {
        if (five_minute_data[i].count > 0) {
            int hour = i / 12;
            int minute = (i % 12) * 5;
            double avg_U = five_minute_data[i].sum_U / five_minute_data[i].count;
            double avg_I = five_minute_data[i].sum_I / five_minute_data[i].count;
            cout << hour << ":" << (minute < 10 ? "0" : "") << minute << "\t\t" << round(avg_U* 100)/ 100 << "\t\t" << round(avg_I* 100)/ 100 << endl;
        }
    }
}
