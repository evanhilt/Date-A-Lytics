//
//  date.c
//  Date-A-Lytics-Terminal
//
//  Created by Evan Hilton on 12/5/19.
//  Copyright © 2019 Evan Hilton. All rights reserved.
//
#include "date.h"

char SPECIAL_CHAR = '+';
int make_date_flag = 0;
const char *weekdays[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char *month_abbrv[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                              "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int get_str(int j, char* str, char *line) {
    for(int i = 0; line[j] != SPECIAL_CHAR; i++) {
        str[i] = line[j];
        j++;
    }
    j++;
    return j;
}

int add_to_line(int j, char* object, char* line) {
    int i = 0;
    for(i = 0; object[i] != '\0'; i++) {
        line[j] = object[i];
        j++;
    }
    line[j] = SPECIAL_CHAR;
    j++;
    return j;
}

void line_to_date(char *date_line, date *date_ptr) {
    int j = 0;

    char date_id_str[4];
    j = get_str(j, date_id_str, date_line);
    date_ptr->date_id = atoi(date_id_str);

    //time
    char year_str[5];
    j = get_str(j, year_str, date_line);
    date_ptr->time.year = atoi(year_str);

    char month_str[3];
    j = get_str(j, month_str, date_line);
    date_ptr->time.month = atoi(month_str);

    char weekday_str[8];
    j = get_str(j, weekday_str, date_line);
    date_ptr->time.weekday = atoi(weekday_str);

    char month_day_str[3];
    j = get_str(j, month_day_str, date_line);
    date_ptr->time.month_day = atoi(month_day_str);

    char hour_str[3];
    j = get_str(j, hour_str, date_line);
    date_ptr->time.hour = atoi(hour_str);

    char minute_str[3];
    j = get_str(j, minute_str, date_line);
    date_ptr->time.minute = atoi(minute_str);
    //time

    char age_str[4];
    j = get_str(j, age_str, date_line);
    date_ptr->age = atoi(age_str);

    date_ptr->name = malloc(100);
    j = get_str(j, date_ptr->name, date_line);

    date_ptr->place = malloc(100);
    j = get_str(j, date_ptr->place, date_line);

    char duration_str[4];
    j = get_str(j, duration_str, date_line);
    date_ptr->duration = atoi(duration_str);

    char cost_str[6];
    j = get_str(j, cost_str, date_line);
    date_ptr->cost = atoi(cost_str);

    date_ptr->notes = malloc(100);
    j = get_str(j, date_ptr->notes, date_line);
}

void date_to_line(date* date_ptr, char *line) {
    int j = 0;

    char date_id[7];
    sprintf(date_id, "%d", date_ptr->date_id);
    j = add_to_line(j, date_id, line);
    //time
    char year[5];
    sprintf(year, "%d", date_ptr->time.year);
    j = add_to_line(j, year, line);
    char month[3];
    sprintf(month, "%d", date_ptr->time.month);
    j = add_to_line(j, month, line);
    char weekday[2];
    sprintf(weekday, "%d", date_ptr->time.weekday);
    j = add_to_line(j, weekday, line);
    char month_day[3];
    sprintf(month_day, "%d", date_ptr->time.month_day);
    j = add_to_line(j, month_day, line);
    char hour[3];
    sprintf(hour, "%d", date_ptr->time.hour);
    j = add_to_line(j, hour, line);
    char minute[3];
    sprintf(minute, "%d", date_ptr->time.minute);
    j = add_to_line(j, minute, line);
    //time
    char age[4];
    sprintf(age, "%d", date_ptr->age);
    j = add_to_line(j, age, line);

    j = add_to_line(j, date_ptr->name, line);

    j = add_to_line(j, date_ptr->place, line);
    char duration[4];
    sprintf(duration, "%d", date_ptr->duration);
    j = add_to_line(j, duration, line);
    char cost[6];
    sprintf(cost, "%d", date_ptr->cost);
    j = add_to_line(j, cost, line);
    j = add_to_line(j, date_ptr->notes, line);
}

void print_dates(date** all_dates, int date_count) {
    printf("\x1b[36mAll dates\n\x1b[0m");
    for(int i=0; i < date_count; i++) {
        printf("%d ", i+1);
        printf("%s, ", all_dates[i]->name);
        printf("%s, ", weekdays[all_dates[i]->time.weekday - 1]);
        printf("%s ", month_abbrv[all_dates[i]->time.month - 1]);
        printf("%d, %d\n", all_dates[i]->time.month_day, all_dates[i]->time.year);
    }
}

void print_date(date ** all_dates, int i) {
    i--;
    float cost = ((float) all_dates[i]->cost) / 100;
    char *day_time = time_string(all_dates[i]->time.hour, all_dates[i]->time.minute);
    printf("Person Name: %s\n", all_dates[i]->name);
    printf("Person Age: %d\n", all_dates[i]->age);
    printf("Place: %s\n", all_dates[i]->place);
    printf("Date: ");
    printf("%s, ", weekdays[all_dates[i]->time.weekday - 1]);
    printf("%s ", month_abbrv[all_dates[i]->time.month - 1]);
    printf("%d, %d\n", all_dates[i]->time.month_day, all_dates[i]->time.year);
    printf("Time: %s\n", day_time);
    printf("Duration: %d min\n", all_dates[i]->duration);
    printf("Cost: $%.2f\n", cost);
    printf("Notes: %s\n", all_dates[i]->notes);
    free(day_time);
}

char* time_string(int hour, int minute) {
    char* am_pm;
    if (hour > 12) {
        hour = hour - 12;
        am_pm = "pm";
    } else {
        am_pm = "am";
    }
    char* buffer = malloc(10 * sizeof(char));
    snprintf(buffer, 10 * sizeof(char), "%d:%02d %s", hour, minute, am_pm);
    return buffer;
}

int make_date(date* date) {
    int date_id;
    int age;
    int duration;
    int cost;
    char *name = malloc(256);
    char *place = malloc(256);
    date_time time;
    char *notes = malloc(2560);
    printf("Type \'+\' and hit Enter to quite Date Maker.\nDo not use \'+\' char in responses.\n\x1b[0m");
    printf("Person Name: ");
    fflush(stdin);
    scanf("%[^\n]s", name);
//    scanf("%s", name);
    if(check_input(name[0], name, place, notes) == 1) {
        return 1;
    }
    printf("Person Age (number): ");
    scanf("%d", &age);
    if(check_input(age, name, place, notes) == 1) {
        return 1;
    }
    printf("Place: ");
    fflush(stdin);
    scanf("%[^\n]s", place);
    if(check_input(place[0], name, place, notes) == 1) {
        return 1;
    }
    printf("Year (number): ");
    scanf("%d", &time.year);
    if(check_input(getchar(), name, place, notes) == 1) {
        return 1;
    }
    printf("Month (number): ");
    scanf("%d", &time.month);
    if(check_input(getchar(), name, place, notes) == 1) {
        return 1;
    }
    printf("1(Sunday) - 7(Saturday)\n");
    printf("Weekday (number): ");
    scanf("%d", &time.weekday);
    if(check_input(getchar(), name, place, notes) == 1) {
        return 1;
    }
    printf("Month Day (number): ");
    scanf("%d", &time.month_day);
    if(check_input(getchar(), name, place, notes) == 1) {
        return 1;
    }
    printf("Hour (number): ");
    scanf("%d", &time.hour);
    if(check_input(getchar(), name, place, notes) == 1) {
        return 1;
    }
    int am_pm;
    printf("AM or PM? (0 or 1): ");
    scanf("%d", &am_pm);
    if(check_input(am_pm, name, place, notes) == 1) {
        return 1;
    }
    if (am_pm == 1 && time.hour < 12) {
        time.hour += 12;
    }
    printf("Minute (number): ");
    scanf("%d", &time.minute);
    if(check_input(getchar(), name, place, notes) == 1) {
        return 1;
    }
    printf("Duration (minutes): ");
    scanf("%d", &duration);
    if(check_input(duration, name, place, notes) == 1) {
        return 1;
    }
    printf("Cost (dollars): ");
    float costf;
    scanf("%f", &costf);
    if(check_input(getchar(), name, place, notes) == 1) {
        return 1;
    }
    cost = (int) roundf(costf * 100);
    printf("Notes: ");
    fflush(stdin);
    scanf("%[^\n]s", notes);
    if(check_input(notes[0], name, place, notes) == 1) {
        return 1;
    }
    fflush(stdin);
    date_id = time.year + time.month + time.weekday + time.month_day * time.year * time.month * time.weekday * time.month_day * time.year * time.month * time.weekday * time.month_day;
    date_id %= 1000000;
    date_id = abs(date_id);
    date->date_id = date_id;
    date->age = age;
    date->name = name;
    date->place = place;
    date->cost = cost;
    date->duration = duration;
    date->notes = notes;
    date->time = time;
    return 0;
}

int check_input(char c, char *name, char *place, char *notes) {
    if(c == '+') {
        free(name);
        free(place);
        free(notes);
        return 1;
    }
    return 0;
}
