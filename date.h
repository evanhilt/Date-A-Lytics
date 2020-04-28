//
//  date.h
//  Date-A-Lytics-Terminal
//
//  Created by Evan Hilton on 12/5/19.
//  Copyright © 2019 Evan Hilton. All rights reserved.
//

#define MAX 1000

#ifndef date_h
#define date_h

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

char SPECIAL_CHAR;
int make_date_flag;
extern const char *weekdays[7];
extern const char *month_abbrv[12];


typedef struct {
    int year;
    int month;
    int weekday;
    int month_day;
    int hour;
    int minute;
} date_time;

typedef struct {
    int date_id;
    int age;
    char *name;
    char *place;
    date_time time;
    int duration;
    int cost;
    char *notes;
} date;

int get_str(int, char*, char*);
int add_to_line(int, char*, char*);
void line_to_date(char*, date*);
void date_to_line(date*, char*);
void print_dates(date**, int);
void print_date(date **, int);
char* time_string(int, int);
int make_date(date*);
int check_input(char, char*, char*, char*);

#endif /* date_h */
