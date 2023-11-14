#include "utilities.h"
#include <stdbool.h>

int main()
{
    // array of daily readings
    reading daily_readings[100];

    char line[buffer_size];
    char filename[buffer_size];

    // get filename from the user
    printf("Please enter the name of the data file: ");

    // these lines read in a line from the stdin (where the user types)
    // and then takes the actual string out of it
    // this removes any spaces or newlines.
    fgets(line, buffer_size, stdin);
    sscanf(line, " %s ", filename);

    char choice;
    int counter = 0;
    float mean = 0;
    bool isRunning = true;
    float highest = 0;
    float lowest = 100000;
    char monthChosen[4];
    char month[4];


    while (isRunning)
    {
        FILE *input = fopen(filename, "r");
        if (!input)
        {
            printf("Error: File could not be opened\n");
            return 1;
        }

        printf("A: View all your blood iron levels\n");                       // BRONZE
        printf("B: View your average blood iron level\n");                    // BRONZE
        printf("C: View your lowest blood iron level\n");                     // SILVER
        printf("D: View your highest blood iron level\n");                    // SILVER
        printf("E: View the blood iron levels for a specific month\n");       // SILVER/GOLD
        printf("F: See some additional statistics about your iron levels\n"); // GOLD - see readme.md
        printf("G: Generate a graph of your iron levels\n");                  // GOLD/PLATINUM - see readme.md
        printf("Q: Exit the program\n");

        // get the next character typed in and store in the 'choice'
        choice = getchar();

        // this gets rid of the newline character which the user will enter
        // as otherwise this will stay in the stdin and be read next time
        while (getchar() != '\n');


        // switch statement to control the menu.
        switch (choice)
        {
        // this allows for either capital or lower case
        case 'A':
        case 'a':
            counter = 0;
            while (fgets(line, buffer_size, input))
            {
                // split up the line and store it in the right place
                // using the & operator to pass in a pointer to the bloodIron so it stores it
                tokeniseRecord(line, ",", daily_readings[counter].date, &daily_readings[counter].bloodIron);
                counter++;
            }
            for (int i = 0; i < counter; i++)
            {
                printf("%s - Blood iron: %.1f\n", daily_readings[i].date, daily_readings[i].bloodIron);
            }
            fclose(input);
            break;

        case 'B':
        case 'b':
            counter = 0;
            while (fgets(line, buffer_size, input))
            {
                // split up the line and store it in the right place
                // using the & operator to pass in a pointer to the bloodIron so it stores it
                tokeniseRecord(line, ",", daily_readings[counter].date, &daily_readings[counter].bloodIron);
                mean += daily_readings[counter].bloodIron;
                counter++;
            }
            mean /= counter;
            printf("Your average blood iron was %.2f\n", mean);
            fclose(input);
            break;

        case 'C':
        case 'c':
            lowest = 100000;
            counter = 0;
            while (fgets(line, buffer_size, input))
            {
                // split up the line and store it in the right place
                // using the & operator to pass in a pointer to the bloodIron so it stores it
                tokeniseRecord(line, ",", daily_readings[counter].date, &daily_readings[counter].bloodIron);
                if (daily_readings[counter].bloodIron < lowest){
                    lowest = daily_readings[counter].bloodIron;
                } 
                counter++;}
            printf("The lowest reading was %.2f\n", lowest);
            break;

        case 'D':
        case 'd':
            highest = 0;
            counter = 0;
            while (fgets(line, buffer_size, input))
            {
                // split up the line and store it in the right place
                // using the & operator to pass in a pointer to the bloodIron so it stores it
                tokeniseRecord(line, ",", daily_readings[counter].date, &daily_readings[counter].bloodIron);
                if (daily_readings[counter].bloodIron > highest){
                    highest = daily_readings[counter].bloodIron;
                } 
                counter++;}
            printf("The highest reading was %.2f\n", highest);
            break;

        case 'E':
        case 'e':
        counter = 0;
            printf("Choose the month you want to get the data for > ");
            printf("January:JAN\n");
            printf("February:FEB\n");
            printf("March:MAR\n");
            printf("April:APR\n");
            printf("May:MAY\n");
            printf("June:JUN\n");
            printf("July:JUL\n");
            printf("August:AUG\n");
            printf("September:SEP\n");
            printf("October:OCT\n");
            printf("November:NOV\n");
            printf("December:DEC\n");
            scanf("%s", monthChosen);
            while (fgets(line, buffer_size, input)){
                // split up the line and store it in the right place
                // using the & operator to pass in a pointer to the bloodIron so it stores it
                tokeniseRecord(line, ",", daily_readings[counter].date, &daily_readings[counter].bloodIron);
                memcpy(month, daily_readings[counter].date + 3, 3 * sizeof(char)); // Could've done with strtok to split the date at the '-' because it is in the form DD-MMM-YYYY 
                if (strcmp(month, monthChosen) == 0){
                    printf("%s - Blood iron: %.1f\n", daily_readings[counter].date, daily_readings[counter].bloodIron);
                    }
                }
            break;

        case 'F':
        case 'f':
            break;

        case 'G':
        case 'g':
            break;

        case 'Q':
        case 'q':
            isRunning = false;
            break;

        // if they type anything else:
        default:
            printf("Invalid choice\n");
            break;
        }
    }
    return 0;
}