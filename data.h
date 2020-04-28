//
//  data.h
//  Date-A-Lytics-Terminal
//
//  Created by Evan Hilton on 3/25/20.
//  Copyright © 2020 Evan Hilton. All rights reserved.
//

#ifndef data_h
#define data_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "date.h"

void print_dating_statistics(date**, int);
float dates_per_year(date**, int);
float dates_per_month(date**, int);
float dates_per_week(date**, int);
char* time_of_day(date**, int);
int duration_per_date(date**, int);
int longest_date(date**, int);
int shortest_date(date**, int);
int favorite_place(date**, int);
int favorite_person(date**, int);
int favorite_year(date**, int);
int favorite_month(date**, int);
int favorite_day(date**, int);
float cost_per_date(date**, int);
float most_expensive_date(date**, int);
float least_expensive_date(date**, int);
float total_money_spent(date**, int);

#endif /* data_h */
