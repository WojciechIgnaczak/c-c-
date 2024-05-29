#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
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
    //Sprawdzanie wejscia
    string type = argv[2];
    if (argc != 3 || (type != "h" && type != "m30" && type != "m5")) {
        cout <<"Invalid input" << endl;
        return 1;}

    // Wczytanie danych JSON z pliku
    ifstream input_file("solar_panel_data_20240522.json");
    if (!input_file.is_open()) {
        cout << "Could not open the file!" << endl;
        return 1;}


    // Wektor  do przechowywania danych
    vector<vector<string>> data_array;

    // Wczytanie i przetwarzanie kazdej linii pliku
    string line;
    while (getline(input_file, line)) {
        try {
            json jsonData = json::parse(line);
            if (jsonData.contains("data")) {
                auto data = jsonData["data"];
                for (auto i = data.begin(); i != data.end(); ++i) {
                    string timestamp = i.key();
                    double U = i.value()["U"];
                    double I = i.value()["I"];
                    data_array.push_back({timestamp, to_string(U), to_string(I)});
                }
            }
        } catch (json::parse_error& e) {
            cerr << "JSON parse error: " << e.what() << "Skipping line: " << line << endl;
        }
    }

    // Wybor odpowiedniej funkcji na podstawie argumentu
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
    // Przechowywanie sumy napiecia, sumy natezenia i liczby pomiarów dla kazdej godziny
    vector<double> sum_U_per_hour(24, 0.0);
    vector<double> sum_I_per_hour(24, 0.0);
    vector<int> count_per_hour(24, 0);

    // Iteracja po wszystkich odczytanych danych
    for ( auto entry : data_array) {
        string timestamp = entry[0];
        double U = stod(entry[1]);
        double I = stod(entry[2]);

        // Pobranie godziny z timestampu
        int hour = stoi(timestamp.substr(8, 2));

        // Dodanie danych do sumy i zwiekszenie liczby pomiarów w danej godzinie
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
            cout << hour << ":00  " << avg_U << "        " << avg_I << endl;
        }
    }
}


void calculateHalfHourlyAverage(vector<vector<string>>& data_array) {
    // Przechowywanie sumy napiecia, sumy natezenia i liczby pomiarów dla kazdego 30-minutowego okresu
    vector<FiveMinuteData> half_hourly_data(48);

    // Iteracja po wszystkich odczytanych danych
    for ( auto entry : data_array) {
        string timestamp = entry[0];
        double U = stod(entry[1]);
        double I = stod(entry[2]);

        // Pobranie godziny i minuty z timestampu
        int hour = stoi(timestamp.substr(8, 2));
        int minute = stoi(timestamp.substr(10, 2));

        // Okreslenie indeksu dla danego 30-minutowego okresu
        int half_hour_index = hour * 2 + (minute >= 30);//jesli wieksze od 30 to 1 jesli nie to 0

        // Dodanie danych do sumy i zwiekszenie liczby pomiarów w danym 30-minutowym okresie
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
            cout << hour << ":" << (minute < 10 ? "0" : "") << minute << "\t\t" << avg_U << "\t\t" << avg_I << endl;
        }
    }
}



void calculateFiveMinuteAverage(vector<vector<string>>& data_array) {
    // Przechowywanie sumy napiecia, sumy natezenia i liczby pomiarów dla kazdej 5-minutowej
    vector<FiveMinuteData> five_minute_data(288);

    // Iteracja po wszystkich odczytanych danych
    for ( auto entry : data_array) {
        string timestamp = entry[0];
        double U = stod(entry[1]);//konwersja na double
        double I = stod(entry[2]);

        // Pobranie godziny i minuty z timestampu
        int hour = stoi(timestamp.substr(8, 2));
        int minute = stoi(timestamp.substr(10, 2));

        // Okreslenie indeksu dla danej 5-minutowej
        int five_minute_index = hour * 12 + minute / 5;

        // Dodanie danych do sumy i zwiekszenie liczby pomiarów w danej 5-minutowej
        five_minute_data[five_minute_index].sum_U += U;
        five_minute_data[five_minute_index].sum_I += I;
        five_minute_data[five_minute_index].count++;
    }

    // Wyswietlenie srednich wartosci napiecia i natezenia co 5 minut
    cout << "5 Minutest\tAverage U\tAverage I" << endl;
    cout << "------------------------------------------" << endl;
    for (int i = 0; i < 288; ++i) {
        if (five_minute_data[i].count > 0) {
            int hour = i / 12;
            int minute = (i % 12) * 5;
            double avg_U = five_minute_data[i].sum_U / five_minute_data[i].count;
            double avg_I = five_minute_data[i].sum_I / five_minute_data[i].count;
            cout << hour << ":" << (minute < 10 ? "0" : "") << minute << "\t\t" << avg_U << "\t\t" << avg_I << endl;
        }
    }
}
