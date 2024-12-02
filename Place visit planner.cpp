#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

using namespace std;

const string LOCATION = "Location ";
const string NAME = "name";
const string OPENINGTIME = "openingTime";
const string CLOSINGTIME = "closingTime";
const string RANK = "rank";
const string END_PRINT = "---";

#define MINUTES_IN_AN_HOUR 60
#define MINUTES_IN_HALF_AN_HOUR 30
#define NUMBER_OF_ELEMENTS 4
#define NOT_FOUND -1
#define FOUND 0
#define NOT_VISITED_BEFORE 0
#define VISITED_BEFORE 1
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define EIGHT 8
#define TEN 10
#define FORTY_FIVE 45

struct place_info{
    vector<string> name;
    vector<int> openingTime;
    vector<int> closingTime;
    vector<int> rank;
    vector<int> visited_or_not;
};

const string VISIT_FROM = "Visit from ";
const string UNTIL = " until ";

int find_number_of_places(vector<string> readed_string){
    int num_of_places = readed_string.size() / NUMBER_OF_ELEMENTS - ONE;
    return num_of_places;
}

vector<int> find_order_of_datas(vector<string> readed_string){
    vector<int> main_order;
    vector<string> desired_order = { NAME,OPENINGTIME,CLOSINGTIME,RANK };
    for (int i=ZERO; i < NUMBER_OF_ELEMENTS; i++){ 
        for (int j = ZERO; j < NUMBER_OF_ELEMENTS; j++){ 
            if (desired_order[i] == readed_string[j]){
                main_order.push_back(j);
            }
        }
    }
    return main_order;
}

int convert_time_to_minutes(string string_time){
    int minutes = ZERO;
    minutes = stoi(string_time.substr(ZERO, TWO)) * MINUTES_IN_AN_HOUR + stoi(string_time.substr(THREE, TWO));
    return minutes;
}

place_info create_struction_for_places(vector<string> input_string){
    place_info place_info;
    int number_of_places = find_number_of_places(input_string);
    vector<int> order_of_informations = find_order_of_datas(input_string);
    for (int i = ONE; i <= number_of_places; i++){
        place_info.name.push_back(input_string[order_of_informations[ZERO] + i * NUMBER_OF_ELEMENTS]);
        place_info.openingTime.push_back(convert_time_to_minutes(input_string[order_of_informations[ONE] + i * NUMBER_OF_ELEMENTS]));
        place_info.closingTime.push_back(convert_time_to_minutes(input_string[order_of_informations[TWO] + i * NUMBER_OF_ELEMENTS]));
        int rank = stoi(input_string[order_of_informations[THREE] + i * NUMBER_OF_ELEMENTS]);
        place_info.rank.push_back(rank);
        place_info.visited_or_not.push_back(ZERO);
    }
    return place_info;
}

place_info read_input_from_file(string input_address){
    vector<string> readed_file;
    string filename = input_address;
    ifstream input_file(filename);
    string line_of_file;
    while (getline(input_file, line_of_file)){
        istringstream line(line_of_file);
        string file_element;
        while (getline(line, file_element, ',')){
            readed_file.push_back(file_element);
        }
    }
    input_file.close();
    place_info place_info = create_struction_for_places(readed_file);
    return place_info;
}

string convert_minutes_to_time(int minutes_from_midnight){
    string time = "";
    int hours = minutes_from_midnight / MINUTES_IN_AN_HOUR;
    int minutes = minutes_from_midnight % MINUTES_IN_AN_HOUR;
    if (hours < TEN){
        time += "0";
    }
    time += to_string(hours);
    time += ":";
    if (minutes < TEN){
        time += "0";
    }
    time += to_string(minutes);
    return time;
}

void print_output(int start, int finish, place_info place_info, int place_index){
    cout << LOCATION <<  place_info.name[place_index] << endl;
    cout << VISIT_FROM << convert_minutes_to_time(start) << UNTIL;
    cout << convert_minutes_to_time(finish) << endl << END_PRINT << endl;
}

bool check_place_is_open_or_not(int& start, int place_index, place_info place_info){
    return (start >= place_info.openingTime[place_index] && start <= place_info.closingTime[place_index]);
}

bool check_place_is_visitable_or_not(int& start, int place_index, place_info place_info){
    return (start + FORTY_FIVE <= place_info.closingTime[place_index]);
}

int choose_better_place_to_visit(int start, int chosen_place_index, int place_index, place_info place_info){
    if (chosen_place_index == NOT_FOUND){
        return place_index;
    }
    if (start >= place_info.openingTime[place_index]){
        if (place_info.rank[place_index] < place_info.rank[chosen_place_index]){
            return place_index;
        } 
        else{ 
            return chosen_place_index;
        }
    }
    else{
        if (place_info.openingTime[place_index] <= place_info.openingTime[chosen_place_index]  && place_info.rank[place_index] < place_info.rank[chosen_place_index]){ 
            return place_index;
        }
        return chosen_place_index;
    }
}

void update_start_and_finish(int& start, int& finish, place_info place_info,int chosen_place_index){
    if (start + MINUTES_IN_HALF_AN_HOUR < place_info.openingTime[chosen_place_index]){
        start = place_info.openingTime[chosen_place_index];
    }
    else{
        start += MINUTES_IN_HALF_AN_HOUR;
    }
    if (place_info.closingTime[chosen_place_index] - start >= MINUTES_IN_AN_HOUR){
        finish = start + MINUTES_IN_AN_HOUR;
    }
    else{
        finish = place_info.closingTime[chosen_place_index];
    }
}

int find_best_place(int &start, int &finish, place_info &place_info){
    int chosen_place_index = NOT_FOUND;
    for (int i = ZERO; i < place_info.name.size(); i++){
        if (check_place_is_open_or_not(start,i,place_info) && check_place_is_visitable_or_not(start, i, place_info) && place_info.visited_or_not[i] == NOT_VISITED_BEFORE){
            chosen_place_index = choose_better_place_to_visit(start,chosen_place_index, i, place_info);
        }
    }
    if (chosen_place_index == NOT_FOUND){
        for (int i = ZERO; i < place_info.name.size(); i++){
            if (start < place_info.openingTime[i] && check_place_is_visitable_or_not(start, i, place_info) && place_info.visited_or_not[i] == NOT_VISITED_BEFORE){
                chosen_place_index = choose_better_place_to_visit(start, chosen_place_index, i, place_info);
            }
        }
    }
    if (chosen_place_index >= FOUND){
        place_info.visited_or_not[chosen_place_index] = VISITED_BEFORE;
        update_start_and_finish(start, finish, place_info, chosen_place_index);
    }  
    return chosen_place_index;
}

int main(int argc, char* argv[]){
    place_info place_info = read_input_from_file(argv[ONE]);
    int finnish = EIGHT * MINUTES_IN_AN_HOUR, start = EIGHT * MINUTES_IN_AN_HOUR - MINUTES_IN_HALF_AN_HOUR;
    int index_of_place_to_visit = find_best_place(start, finnish, place_info);
    while (index_of_place_to_visit != NOT_FOUND){
        print_output(start, finnish, place_info, index_of_place_to_visit);
        start = finnish;
        index_of_place_to_visit = find_best_place(start, finnish, place_info);
    }
    return ZERO;
}