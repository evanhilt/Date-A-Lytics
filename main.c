//
//  main.c
//  Date-A-Lytics-Terminal
//
//  Created by Evan Hilton on 12/4/19.
//  Copyright © 2019 Evan Hilton. All rights reserved.
//

#define MAX 1000

#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include "data.h"

int main(int argc, const char * argv[]) {
    
    int date_count = 0; //Use throughout
    
    //Load data into memory
    FILE *fptr;
    fptr = fopen("app_data.bin", "rb");
    if(fptr == NULL) {
        printf("Error Loading\n");
        exit(1);
    }
    char **date_strings = malloc(MAX);
    char *line = malloc(MAX);
    while(fgets(line, MAX, fptr)) {
        date_strings[date_count] = malloc(MAX);
        int i;
        for (i = 0; line[i] != '\0'; i++) {
            date_strings[date_count][i] = line[i];
        }
        date_strings[date_count][i] = '\0';
        date_count++;
    }
    free(line);
    fclose(fptr);
    
    //Transform strings into date objects
    date **all_dates = malloc(date_count * sizeof(date *));
    for(int i = 0; i < date_count; i++) {
        all_dates[i] = malloc(sizeof(date));
        line_to_date(date_strings[i], all_dates[i]);
        free(date_strings[i]);
    }
    free(date_strings);
    
    //Edit Data in Main App
    printf("\033[1;31m*** Welcome to Date-A-Lytics! ***\n\033[0m");
    while(1) {
        int in;
        printf("\033[1;31m");
        printf("What would you like to do?\n1. See dating data\n2. Add or remove a date\n3. Quit\n");
        printf("\033[0m");
        scanf("%d",&in);
        if (in == 1) {
            while(1) {
                printf("\x1b[33mWhat data would you like to see?\n1. All my dates\n2. My dating statistics\n3. Home\n\x1b[0m");
                scanf("%d",&in);
                if(in == 1) {
                    print_dates(all_dates, date_count);
                    while(1) {
                        printf("\x1b[36mEnter number of date for more info.\nEnter 0 to leave.\n\x1b[0m");
                        scanf("%d",&in);
                        if(in == 0) {
                            break;
                        } else {
                            print_date(all_dates, in);
                        }
                    }
                } else if (in == 2) {
                    print_dating_statistics(all_dates, date_count);
                } else if (in == 3){
                    break;
                }
            }
        } else if (in == 2) {
            while(1) {
                printf("\x1b[33mWhat data would you like do?\n1. Add a date\n2. Remove a date\n3. Home\n\x1b[0m");
                scanf("%d",&in);
                if(in == 1) {
                    printf("\x1b[36mAdd a date\n");
                    date *new_date = malloc(sizeof(date));
                    if(make_date(new_date)) {
                        free(new_date);
                    } else {
                        all_dates = (date **) realloc(all_dates, ((date_count + 1) * sizeof(date*)));
                        all_dates[date_count] = new_date;
                        date_count++;
                    }
                } else if(in == 2) {
                    printf("\x1b[36mRemove a date\n\x1b[0m");
                    print_dates(all_dates, date_count);
                    printf("\x1b[36mSelect a date to remove.\nEnter 0 to leave.\n\x1b[0m");
                    scanf("%d",&in);
                    if(in <= date_count && in != 0) {
                        for (int j = in - 1; j < date_count - 1; j++) {
                            all_dates[j] = all_dates[j + 1];
                        }
                        all_dates[date_count - 1] = NULL;
                        date_count--;
                    }
                } else if(in == 3){
                    break;
                }
            }
        } else if (in == 3) {
            break;
        }
    }
    
    //Transform date objects into strings
    date_strings = malloc(MAX);
    for(int i = 0; i < date_count; i++) {
        date_strings[i] = malloc(MAX);
        date_to_line(all_dates[i], date_strings[i]);
        free(all_dates[i]);
    }
    free(all_dates);
    
    //Load data into file
    fptr = fopen("app_data.bin", "wb");
    if(fptr == NULL) {
        printf("Error Saving\n");
        exit(1);
    }
    for (int i = 0; i < date_count; i++) {
        fprintf(fptr, "%s\n", date_strings[i]);
        free(date_strings[i]);
    }
    free(date_strings);
    fclose(fptr);
    return 0;
}
