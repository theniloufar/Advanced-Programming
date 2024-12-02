#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define num_of_periods 3
#define column 3
typedef struct teachers_data teachers_data;
typedef struct courses_data courses_data;
void week_plan(courses_data coursesData[], teachers_data teachersData[], int num_of_courses, int num_of_teachers, vector<vector<int>> jadval, vector<vector<string>> &barname_haftegi);
void filling_barname_haftegi(vector<vector<string>> &barname_haftegi, string b, string chosen_course, int index_day);
int days_of_the_week_to_number(string day);
int course_with_lowest_name(vector<int> index_course, courses_data coursesData[]);
int clock_check(string start, string end, string a, string b);
void sorting_courses_name(courses_data coursesData[], int num_of_courses, vector<vector<string>> &barname_haftegi);
void scan_teachers_data(teachers_data teachersData[], int num_of_teachers);
void print_barname_haftegi(vector<vector<string>> barname_haftegi);
void scan_courses_data(courses_data coursesData[], int num_of_courses);
int teacher_check(courses_data coursesData[], int index_chosen_course, teachers_data teachersData[], int num_of_teachers, int period, int index_day, int result_index_course);
int which_teacher(vector<int> index_of_teachers, teachers_data teachersData[], int num_of_teachers);
int teacher_with_lowest_name(vector<int> index_of_teachers_with_less_workdays, teachers_data teachersData[]);
void days_of_the_week(int num_of_courses, courses_data coursesData[], teachers_data teachersData[], int num_of_teachers, int index_day, vector<vector<int>> &jadval, vector<vector<string>> &barname_haftegi);
void teachers_with_least_work_days(vector<int> index_of_teachers, teachers_data teacherData[], vector<int> &index_of_teachers_with_less_workdays);
void course_check(vector<int> &index_courses, int num_of_courses, courses_data coursesData[], vector<string> start, vector<string> end, vector<string> days, int period, int index_day, int &flag, vector<vector<int>> jadval);
struct teachers_data
{
    string teacher_name;
    int number_of_free_days;
    vector<string> free_days;
    int number_of_courses;
    vector<string> courses;
    vector<vector<int>> flag;
};
struct courses_data
{
    string course_name;
    string day_1;
    string day_2;
    string start_time;
    string end_time;
    int flag;
    int flag_no_existence_teacher;
    vector<vector<int>> flag_course;
};
int main()
{
    int num_of_courses = 0, num_of_teachers = 0;
    cin >> num_of_teachers;
    teachers_data teachersData[num_of_teachers];
    scan_teachers_data(teachersData, num_of_teachers);
    cin >> num_of_courses;
    courses_data coursesData[num_of_courses];
    scan_courses_data(coursesData, num_of_courses);
    vector<vector<int>> jadval{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    vector<vector<string>> barname_haftegi(num_of_courses, vector<string>(column, ""));
    sorting_courses_name(coursesData, num_of_courses, barname_haftegi);
    week_plan(coursesData, teachersData, num_of_courses, num_of_teachers, jadval, barname_haftegi);
    print_barname_haftegi(barname_haftegi);
}
void week_plan(courses_data coursesData[], teachers_data teachersData[], int num_of_courses, int num_of_teachers, vector<vector<int>> jadval, vector<vector<string>> &barname_haftegi)
{
    for (int i = 0; i < 5; i++)
    {
        days_of_the_week(num_of_courses, coursesData, teachersData, num_of_teachers, i, jadval, barname_haftegi);
    }
    for (int i = 0; i < num_of_courses; i++)
    {
        coursesData[i].flag = 1;
        coursesData[i].flag_no_existence_teacher = 1;
    }
    jadval = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    for (int i = 5; i < 10; i++)
    {
        days_of_the_week(num_of_courses, coursesData, teachersData, num_of_teachers, i, jadval, barname_haftegi);
    }
}
void sorting_courses_name(courses_data coursesData[], int num_of_courses, vector<vector<string>> &barname_haftegi)
{
    vector<string> courses_name;
    for (int i = 0; i < num_of_courses; i++)
    {
        courses_name.push_back(coursesData[i].course_name);
    }
    sort(courses_name.begin(), courses_name.end());
    for (int i = 0; i < barname_haftegi.size(); i++)
    {
        barname_haftegi[i][0] = courses_name[i];
    }
}
void print_barname_haftegi(vector<vector<string>> barname_haftegi)
{
    for (int i = 0; i < barname_haftegi.size(); i++)
    {
        cout << barname_haftegi[i][0] << '\n';
        if (barname_haftegi[i][1] == "")
        {
            cout << "Not Found\n";
        }
        else
        {
            cout << barname_haftegi[i][1] << '\n';
        }
        if (barname_haftegi[i][2] == "")
        {
            cout << "Not Found\n";
        }
        else
        {
            cout << barname_haftegi[i][2] << '\n';
        }
    }
}
void scan_teachers_data(teachers_data teachersData[], int num_of_teachers)
{
    string temp1;
    for (int i = 0; i < num_of_teachers; i++)
    {
        teachersData[i].flag = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
        cin >> teachersData[i].teacher_name;
        cin >> teachersData[i].number_of_free_days;
        for (int m = 0; m < teachersData[i].number_of_free_days; m++)
        {
            cin >> temp1;
            teachersData[i].free_days.push_back(temp1);
        }
        cin >> teachersData[i].number_of_courses;
        for (int m = 0; m < teachersData[i].number_of_courses; m++)
        {
            cin >> temp1;
            teachersData[i].courses.push_back(temp1);
        }
    }
}
void scan_courses_data(courses_data coursesData[], int num_of_courses)
{
    for (int i = 0; i < num_of_courses; i++)
    {
        cin >> coursesData[i].course_name;
        cin >> coursesData[i].day_1;
        cin >> coursesData[i].day_2;
        cin >> coursesData[i].start_time;
        cin >> coursesData[i].end_time;
        coursesData[i].flag = 1;
        coursesData[i].flag_no_existence_teacher = 1;
        coursesData[i].flag_course = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    }
}
int clock_check(string start, string end, string a, string b)
{
    int flag1 = 0;
    int flag2 = 0;
    if (a[0] > start[0])
    {
        flag1 = 1;
    }
    else if (a[0] == start[0])
    {
        if (a[1] > start[1])
        {
            flag1 = 1;
        }
        else if (a[1] == start[1])
        {
            if (a[3] > start[3])
            {
                flag1 = 1;
            }
            else if (a[3] == start[3])
            {
                if (a[4] >= start[4])
                {
                    flag1 = 1;
                }
            }
        }
    }
    if (b[0] < end[0])
    {
        flag2 = 1;
    }
    else if (b[0] == end[0])
    {
        if (b[1] < end[1])
        {
            flag2 = 1;
        }
        else if (b[1] == end[1])
        {
            if (b[3] < end[3])
            {
                flag2 = 1;
            }
            else if (b[3] == end[3])
            {
                if (b[4] <= end[4])
                {
                    flag2 = 1;
                }
            }
        }
    }
    if (flag1 == 1 && flag2 == 1)
    {
        return 1;
    }
    return 0;
}
void days_of_the_week(int num_of_courses, courses_data coursesData[], teachers_data teachersData[], int num_of_teachers, int index_day, vector<vector<int>> &jadval, vector<vector<string>> &barname_haftegi)
{
    int flag, index_teacher = 0, result_index_course;
    vector<int> index_courses;
    vector<string> days = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday"};
    vector<string> start = {"07:30", "09:30", "11:30"}, end = {"09:00", "11:00", "13:00"};
    for (int period = 0; period < num_of_periods; period++)
    {
        flag = 0;
        index_courses.clear();
        course_check(index_courses, num_of_courses, coursesData, start, end, days, period, index_day, flag, jadval);
        if (flag)
        {
            result_index_course = course_with_lowest_name(index_courses, coursesData);
            if ((index_teacher = teacher_check(coursesData, result_index_course, teachersData, num_of_teachers, period, index_day, result_index_course)) != -1)
            {
                coursesData[result_index_course].flag = 0;
                jadval[days_of_the_week_to_number(coursesData[result_index_course].day_1)][period] = 0;
                jadval[days_of_the_week_to_number(coursesData[result_index_course].day_2)][period] = 0;
                teachersData[index_teacher].flag[days_of_the_week_to_number(coursesData[result_index_course].day_1)][period] = 0;
                teachersData[index_teacher].flag[days_of_the_week_to_number(coursesData[result_index_course].day_2)][period] = 0;
                string b = teachersData[index_teacher].teacher_name + ": " + start[period] + " " + end[period];
                for (int i = 0; i < num_of_courses; i++)
                {
                    coursesData[i].flag_no_existence_teacher = 1;
                }
                filling_barname_haftegi(barname_haftegi, b, coursesData[result_index_course].course_name, index_day);
            }
            else
            {
                if (index_courses.size() > 1)
                {
                    coursesData[result_index_course].flag_no_existence_teacher = 0;
                    period--;
                }
                else
                {
                    for (int i = 0; i < num_of_courses; i++)
                    {
                        coursesData[i].flag_no_existence_teacher = 1;
                    }
                }
            }
        }
    }
}
void filling_barname_haftegi(vector<vector<string>> &barname_haftegi, string b, string chosen_course, int index_day)
{
    for (int i = 0; i < barname_haftegi.size(); i++)
    {
        if (barname_haftegi[i][0] == chosen_course)
        {
            if (index_day < 5)
            {
                barname_haftegi[i][1] = b;
            }
            else
            {
                barname_haftegi[i][2] = b;
            }
        }
    }
}
void course_check(vector<int> &index_courses, int num_of_courses, courses_data coursesData[], vector<string> start, vector<string> end, vector<string> days, int period, int index_day, int &flag, vector<vector<int>> jadval)
{
    for (int i = 0; i < num_of_courses; i++)
    {
        if (coursesData[i].day_1 == days[index_day] || coursesData[i].day_2 == days[index_day])
        {
            if (jadval[days_of_the_week_to_number(coursesData[i].day_1)][period] == 1 &&
                jadval[days_of_the_week_to_number(coursesData[i].day_2)][period] == 1)
            {
                if (coursesData[i].flag && coursesData[i].flag_no_existence_teacher)
                {
                    if (clock_check(coursesData[i].start_time, coursesData[i].end_time, start[period], end[period]))
                    {
                        index_courses.push_back(i);
                        flag = 1;
                    }
                }
            }
        }
    }
}
int course_with_lowest_name(vector<int> index_course, courses_data coursesData[])
{
    int index = 0;
    string min = coursesData[index_course[0]].course_name;
    if (index_course.size() == 1)
        return index_course[0];
    for (int i = 0; i < index_course.size(); i++)
    {
        if (coursesData[index_course[i]].course_name < min)
        {
            min = coursesData[index_course[i]].course_name;
            index = i;
        }
    }
    if (index == 0)
    {
        return index_course[0];
    }
    return index_course[index];
}
int teacher_check(courses_data coursesData[], int index_chosen_course, teachers_data teachersData[], int num_of_teachers, int period, int index_day, int result_index_course)
{
    vector<int> index_of_teachers;
    for (int i = 0; i < num_of_teachers; i++)
    {
        int flag = 0;
        if (teachersData[i].flag[days_of_the_week_to_number(coursesData[result_index_course].day_1)][period] == 0 ||
            teachersData[i].flag[days_of_the_week_to_number(coursesData[result_index_course].day_2)][period] == 0)
        {
            continue;
        }
        for (int j = 0; j < teachersData[i].number_of_free_days; j++)
        {
            if (teachersData[i].free_days[j] == coursesData[index_chosen_course].day_1)
            {
                flag++;
            }
        }
        for (int j = 0; j < teachersData[i].number_of_free_days; j++)
        {
            if (teachersData[i].free_days[j] == coursesData[index_chosen_course].day_2)
            {
                flag++;
            }
        }
        for (int j = 0; j < teachersData[i].number_of_courses; j++)
        {
            if (teachersData[i].courses[j] == coursesData[index_chosen_course].course_name)
            {
                flag++;
            }
        }
        if (flag == 3)
        {
            index_of_teachers.push_back(i);
        }
    }
    int result = which_teacher(index_of_teachers, teachersData, num_of_teachers);
    if (result == -1)
    {
        return -1;
    }
    return result;
}
int which_teacher(vector<int> index_of_teachers, teachers_data teachersData[], int num_of_teachers)
{
    int index;
    vector<int> index_of_teachers_with_less_workdays;
    if (index_of_teachers.size() == 0)
        return -1;
    teachers_with_least_work_days(index_of_teachers, teachersData, index_of_teachers_with_less_workdays);
    if (index_of_teachers_with_less_workdays.size() == 1)
    {
        return index_of_teachers_with_less_workdays[0];
    }
    index = teacher_with_lowest_name(index_of_teachers_with_less_workdays, teachersData);
    return index;
}
void teachers_with_least_work_days(vector<int> index_of_teachers, teachers_data teachersData[], vector<int> &index_of_teachers_with_less_workdays)
{
    int min = teachersData[index_of_teachers[0]].number_of_free_days;
    for (int i = 0; i < index_of_teachers.size(); i++)
    {
        if (teachersData[index_of_teachers[i]].number_of_free_days < min)
        {
            min = teachersData[index_of_teachers[i]].number_of_free_days;
        }
    }
    for (int i = 0; i < index_of_teachers.size(); i++)
    {
        if (teachersData[index_of_teachers[i]].number_of_free_days == min)
        {
            index_of_teachers_with_less_workdays.push_back(index_of_teachers[i]);
        }
    }
}
int teacher_with_lowest_name(vector<int> index_of_teachers_with_less_workdays, teachers_data teachersData[])
{
    int index = 0;
    string min = teachersData[index_of_teachers_with_less_workdays[0]].teacher_name;
    for (int i = 0; i < index_of_teachers_with_less_workdays.size(); i++)
    {
        if (teachersData[index_of_teachers_with_less_workdays[i]].teacher_name < min)
        {
            min = teachersData[index_of_teachers_with_less_workdays[i]].teacher_name;
            index = index_of_teachers_with_less_workdays[i];
        }
    }
    if (index == 0)
    {
        return index_of_teachers_with_less_workdays[0];
    }
    return index;
}
int days_of_the_week_to_number(string day)
{
    if (day == "Saturday")
        return 0;
    if (day == "Sunday")
        return 1;
    if (day == "Monday")
        return 2;
    if (day == "Tuesday")
        return 3;
    if (day == "Wednesday")
        return 4;
}