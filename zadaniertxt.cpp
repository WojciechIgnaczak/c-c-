#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void calculateHourlyAverage(vector<vector<string>>& data_array);
void calculateHalfHourlyAverage(vector<vector<string>>& data_array);
void calculateFiveMinuteAverage(vector<vector<string>>& data_array);

struct FiveMinuteData {
    double sum_U = 0.0;
    double sum_I = 0.0;
    int count = 0;
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Invalid input" << endl;
        return 1;
    }
    
    string type = argv[2];
    if (type != "h" && type != "m30" && type != "m5") {
        cout << "Invalid input type" << endl;
        return 1;
    }

    ifstream input_file("solar_panel_data_20240522.json");
    if (!input_file.is_open()) {
        cout << "Could not open the file!" << endl;
        return 1;
    }

    // Wektor do przechowywania danych
    vector<vector<string>> data_array;

    string line;
    while (getline(input_file, line)) {
        size_t data_pos = line.find("\"data\"");
        if (data_pos != string::npos) {
            size_t start_pos = line.find('{', data_pos);
            size_t end_pos = line.rfind('}');
            if (start_pos != string::npos && end_pos != string::npos && end_pos > start_pos) {
                string data_str = line.substr(start_pos + 1, end_pos - start_pos - 1);
                stringstream ss(data_str);
                string pair;
                while (getline(ss, pair, ',')) {
                    size_t colon_pos = pair.find(':');
                    if (colon_pos != string::npos) {
                        string key = pair.substr(0, colon_pos);
                        string value = pair.substr(colon_pos + 1);
                        key.erase(remove(key.begin(), key.end(), '"'), key.end());
                        value.erase(remove(value.begin(), value.end(), '"'), value.end());
                        size_t u_pos = value.find("\"U\":");
                        size_t i_pos = value.find("\"I\":");
                        if (u_pos != string::npos && i_pos != string::npos) {
                            string timestamp = key;
                            double U = stod(value.substr(u_pos + 4, value.find(',', u_pos) - u_pos - 4));
                            double I = stod(value.substr(i_pos + 4));
                            data_array.push_back({timestamp, to_string(U), to_string(I)});
                        }
                    }
                }
            }
        }
    }

    input_file.close();

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

void calculateHourlyAverage(vector<vector<string>>& data_array) {
    // Przechowywanie napiecia, natezenia, liczby pomiarow
    vector<double> sum_U_per_hour(24, 0.0);
    vector<double> sum_I_per_hour(24, 0.0);
    vector<int> count_per_hour(24, 0);

    // czas, u, i
    for (auto entry : data_array) {
        string timestamp = entry[0];
        double U = stod(entry[1]);
        double I = stod(entry[2]);
        int hour = stoi(timestamp.substr(8, 2)); // Pobranie godziny z timestampu

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
            cout << hour << ":00  " << avg_U << "        " << avg_I << endl;
        }
    }
}

void calculateHalfHourlyAverage(vector<vector<string>>& data_array) {
    // Przechowywanie napiecia, natezenia, liczby pomiarow
    vector<FiveMinuteData> half_hourly_data(48);

    for (auto entry : data_array) { // iteracja po kazdym elemencie
        string timestamp = entry[0];
        double U = stod(entry[1]);
        double I = stod(entry[2]);

        // Pobranie godziny i minuty
        int hour = stoi(timestamp.substr(8, 2));
        int minute = stoi(timestamp.substr(10, 2));

        // Okreslenie indeksu
        int half_hour_index = hour * 2 + (minute >= 30); // jesli wieksze od 30 to 1 jesli nie to 0

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
    // Przechowywanie sumy napiecia, sumy natezenia i liczby pomiarow dla kazdej 5-minutowej
    vector<FiveMinuteData> five_minute_data(288);

    // Iteracja po wszystkich odczytanych danych
    for (auto entry : data_array) {
        string timestamp = entry[0];
        double U = stod(entry[1]); // konwersja na double
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
    cout << "5 Minutes\tAverage U\tAverage I" << endl;
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
