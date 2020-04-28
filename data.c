//
//  data.c
//  Date-A-Lytics-Terminal
//
//  Created by Evan Hilton on 3/25/20.
//  Copyright © 2020 Evan Hilton. All rights reserved.
//

#include "data.h"

void print_dating_statistics(date** all_dates, int date_count) {
    char *month_names[12] = {"January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"};
    char *weekday_names[12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    char *day_time = time_of_day(all_dates, date_count);
    printf("\x1b[36mMy dating statistics\n\x1b[0m");
    printf("\x1b[36mAverage dates per year: \x1b[0m%.2f\n", dates_per_year(all_dates, date_count));
    printf("\x1b[36mAverage dates per month: \x1b[0m%.2f\n", dates_per_month(all_dates, date_count));
    printf("\x1b[36mAverage dates per week: \x1b[0m%.2f\n", dates_per_week(all_dates, date_count));
    printf("\x1b[36mAverage time of day: \x1b[0m%s\n", day_time);
    printf("\x1b[36mAverage Duration for a date: \x1b[0m%d minutes\n",
           duration_per_date(all_dates, date_count));
    printf("\x1b[36mLongest date: \x1b[0m%d minutes\n", longest_date(all_dates, date_count));
    printf("\x1b[36mShortest date: \x1b[0m%d minutes\n", shortest_date(all_dates, date_count));
    int b = favorite_place(all_dates, date_count);
    if(b != date_count) {
        printf("\x1b[36mFavorite place: \x1b[0m%s\n", all_dates[b]->place);
    } else {
        printf("\x1b[36mFavorite place: \x1b[0mNo favorite\n");
    }
    b = favorite_person(all_dates, date_count);
    if(b != date_count) {
        printf("\x1b[36mFavorite person: \x1b[0m%s\n", all_dates[b]->name);
    } else {
        printf("\x1b[36mFavorite person: \x1b[0mNo favorite\n");
    }
    b = favorite_year(all_dates, date_count);
    if(b != 0) {
        printf("\x1b[36mBest year: \x1b[0m%d\n", b);
    } else {
        printf("\x1b[36mBest year: \x1b[0mNo favorite\n");
    }
    b = favorite_month(all_dates, date_count);
    if(b != 0) {
        printf("\x1b[36mBest month: \x1b[0m%s\n", month_names[b - 1]);
    } else {
        printf("\x1b[36mBest month: \x1b[0mNo favorite\n");
    }
    b = favorite_day(all_dates, date_count);
    if(b != 0) {
        printf("\x1b[36mBest day: \x1b[0m%s\n", weekday_names[b - 1]);
    } else {
        printf("\x1b[36mBest day: \x1b[0mNo favorite\n");
    }
    printf("\x1b[36mAverage cost per date: \x1b[0m$%.2f\n", cost_per_date(all_dates, date_count));
    printf("\x1b[36mMost expensive date: \x1b[0m$%.2f\n", most_expensive_date(all_dates, date_count));
    printf("\x1b[36mLeast expensive date: \x1b[0m$%.2f\n", least_expensive_date(all_dates, date_count));
    printf("\x1b[36mTotal money spent: \x1b[0m$%.2f\n", total_money_spent(all_dates, date_count));
    free(day_time);
}

float dates_per_year(date** all_dates, int date_count) {
    int* date_years = calloc(sizeof(int), date_count);
    int years = 0;
    for(int i=0; i<date_count; i++) {
        if(date_years[i] != 1) {
            years++;
            for(int j=0; j<date_count; j++) {
                if(all_dates[i]->time.year == all_dates[j]->time.year) {
                    date_years[j] = 1;
                }
            }
        }
    }
    free(date_years);
    return (float) date_count / (float) years;
}

float dates_per_month(date** all_dates, int date_count) {
    int* date_months = calloc(sizeof(int), date_count);
    int months = 0;
    for(int i=0; i<date_count; i++) {
        if(date_months[i] != 1) {
            months++;
            for(int j=0; j<date_count; j++) {
                if(all_dates[i]->time.month == all_dates[j]->time.month
                   && all_dates[i]->time.year == all_dates[j]->time.year) {
                    date_months[j] = 1;
                }
            }
        }
    }
    free(date_months);
    return (float) date_count / (float) months;
}

float dates_per_week(date** all_dates, int date_count) {
    int* date_weeks = calloc(sizeof(int), date_count);
    int weeks = 0;
    for(int i=0; i<date_count; i++) {
        if(date_weeks[i] != 1) {
            weeks++;
            for(int j=0; j<date_count; j++) {
                //Same month of the same year
                if(all_dates[i]->time.month == all_dates[j]->time.month
                   && all_dates[i]->time.year == all_dates[j]->time.year) {
                    //Days are in the same week
                    if((all_dates[i]->time.month_day >= all_dates[j]->time.month_day
                       && all_dates[i]->time.month_day - all_dates[j]->time.month_day < 7
                       && all_dates[i]->time.weekday >= all_dates[j]->time.weekday)
                       || (all_dates[j]->time.month_day >= all_dates[i]->time.month_day
                       && all_dates[j]->time.month_day - all_dates[i]->time.month_day < 7
                       && all_dates[j]->time.weekday >= all_dates[i]->time.weekday)) {
                        date_weeks[j] = 1;
                    }
                }
            }
        }
    }
    free(date_weeks);
    return (float) date_count / (float) weeks;
}

char* time_of_day(date** all_dates, int date_count) {
    int minutes = 0;
    for(int i=0; i<date_count; i++) {
        minutes += (all_dates[i]->time.hour * 60) + all_dates[i]->time.minute;
    }
    int ave = minutes / date_count;
    int ave_hour = ave / 60;
    int ave_minute = ave % 60;
    return time_string(ave_hour, ave_minute);
}

int duration_per_date(date** all_dates, int date_count) {
    int duration = 0;
    for(int i=0; i<date_count; i++) {
        duration += all_dates[i]->duration;
    }
    return duration / date_count;
}

int longest_date(date** all_dates, int date_count) {
    int longest = 0;
    for(int i=0; i<date_count; i++) {
        if (all_dates[i]->duration > longest) {
            longest = all_dates[i]->duration;
        }
    }
    return longest;
}

int shortest_date(date** all_dates, int date_count) {
    int shortest = INFINITY;
    for(int i=0; i<date_count; i++) {
        if(all_dates[i]->duration < shortest) {
            shortest = all_dates[i]->duration;
        }
    }
    return shortest;
}

int favorite_place(date** all_dates, int date_count) {
    if(date_count == 1) { return 0; }
    int best_index = date_count;
    int best_count = 1;
    int* places = calloc(sizeof(int), date_count);
    for(int i=0; i<date_count; i++) {
        int count = 0;
        if(places[i] != 1) {
            for(int j=0; j<date_count; j++) {
                if(strcmp(all_dates[i]->place, all_dates[j]->place) == 0) {
                    places[j] = 1;
                    count++;
                }
            }
            if(count > best_count) {
                best_count = count;
                best_index = i;
            } else if (count == best_count) {
               best_count = 1;
               best_index = date_count;
            }
        }
    }
    return best_index;
}

int favorite_person(date** all_dates, int date_count) {
    if(date_count == 1) { return 0; }
    int best_index = date_count;
    int best_count = 1;
    int* names = calloc(sizeof(int), date_count);
    for(int i=0; i<date_count; i++) {
        int count = 0;
        if(names[i] != 1) {
            for(int j=0; j<date_count; j++) {
                if(strcmp(all_dates[i]->name, all_dates[j]->name) == 0) {
                    names[j] = 1;
                    count++;
                }
            }
            if(count > best_count) {
                best_count = count;
                best_index = i;
            } else if (count == best_count) {
               best_count = 1;
               best_index = date_count;
            }
        }
    }
    return best_index;
}

int favorite_year(date** all_dates, int date_count) {
    if(date_count == 1) { return all_dates[0]->time.year; }
    int best = 0;
    int best_count = 1;
    int* years = calloc(sizeof(int), date_count);
    for(int i=0; i<date_count; i++) {
        int count = 0;
        if(years[i] != 1) {
            for(int j=0; j<date_count; j++) {
                if(all_dates[i]->time.year == all_dates[j]->time.year) {
                    years[j] = 1;
                    count++;
                }
            }
            if(count > best_count) {
                best_count = count;
                best = all_dates[i]->time.year;
            } else if (count == best_count) {
               best_count = 1;
               best = 0;
            }
        }
    }
    return best;
}

int favorite_month(date** all_dates, int date_count) {
    if(date_count == 1) { return all_dates[0]->time.month; }
    int best = 0;
    int best_count = 1;
    int* months = calloc(sizeof(int), date_count);
    for(int i=0; i<date_count; i++) {
        int count = 0;
        if(months[i] != 1) {
            for(int j=0; j<date_count; j++) {
                if(all_dates[i]->time.month == all_dates[j]->time.month) {
                    months[j] = 1;
                    count++;
                }
            }
            if(count > best_count) {
                best_count = count;
                best = all_dates[i]->time.month;
            } else if (count == best_count) {
               best_count = 1;
               best = 0;
            }
        }
    }
    return best;
}

int favorite_day(date** all_dates, int date_count) {
    if(date_count == 1) { return all_dates[0]->time.weekday; }
    int best = 0;
    int best_count = 1;
    int* days = calloc(sizeof(int), date_count);
    for(int i=0; i<date_count; i++) {
        int count = 0;
        if(days[i] != 1) {
            for(int j=0; j<date_count; j++) {
                if(all_dates[i]->time.weekday == all_dates[j]->time.weekday) {
                    days[j] = 1;
                    count++;
                }
            }
            if(count > best_count) {
                best_count = count;
                best = all_dates[i]->time.weekday;
            } else if (count == best_count) {
                best_count = 1;
                best = 0;
            }
        }
    }
    return best;
}

float cost_per_date(date** all_dates, int date_count) {
    float cost = 0;
    for(int i=0; i<date_count; i++) {
        cost += (((float)all_dates[i]->cost) / 100);
    }
    return cost / date_count;
}

float most_expensive_date(date** all_dates, int date_count) {
    float most = 0;
    for(int i=0; i<date_count; i++) {
        float cost = (((float)all_dates[i]->cost) / 100);
        if(cost > most) {
            most = cost;
        }
    }
    return most;
}

float least_expensive_date(date** all_dates, int date_count) {
    float least = INFINITY;
    for(int i=0; i<date_count; i++) {
        float cost = (((float)all_dates[i]->cost) / 100);
        if(cost < least) {
            least = cost;
        }
    }
    return least;
}

float total_money_spent(date** all_dates, int date_count) {
    float total = 0;
    for(int i=0; i<date_count; i++) {
        total += (((float)all_dates[i]->cost) / 100);
    }
    return total;
}
