#include <stdio.h>
#include <string.h> /*strstr() için gerekli*/
#include <math.h>

/* Data structure to store filenames of read news */
char read_news_filenames[10][100]; /*  Maximum 10 news files*/
int num_read_news = 0;             /*Number of read news*/

/* Reads and displays the news text */
int read_news()
{
    FILE *file;
    char filename[100];
    int news_key;
    char choice = 'y'; /*Initially assume the user wants to continue */

    while (choice == 'y' || choice == 'Y')
    {
        printf("Which news do you want to read?\n");
        scanf("%d", &news_key);

        /*Generate the filename  */
        sprintf(filename, "%d.txt", news_key);

        /*check the news already read or not*/
        int already_read = 0; /* 0 = false, 1 = true */
        int i;
        for (i = 0; i < num_read_news; i++)
        {
            if (strcmp(read_news_filenames[i], filename) == 0)
            {
                printf("This news already readed, Do you want to read again? (y/n): ");
                scanf(" %c", &choice);
                if (choice == 'y' || choice == 'Y')
                {
                    already_read = 0; /*User wants to read again, set already_read to false */
                }
                else
                {
                    already_read = 1; /*User doesn't want to read again, set already_read to true*/
                }
                break;
            }
        }

        if (!already_read)
        {
            /*open file*/
            file = fopen(filename, "r");
            if (file == NULL)
            {
                printf("File does not exist.\n");
                return 1;
            }

            /*Read and print the news text line by line  */
            char line[500];
            while (fgets(line, sizeof(line), file) != NULL)
            {
                printf("%s", line);
            }

            /*close the file*/
            fclose(file);

            /*Save the filename of the read news */
            if (num_read_news < 10)
            { /*Prevent array overflow */
                strcpy(read_news_filenames[num_read_news], filename);
                num_read_news++;
            }
        }

        printf("Do you want to continue? yes(y) or no(n): ");
        scanf(" %c", &choice);
    }

    return 0;
}

/*Prints the list of read news*/
void list_read_news()
{
    if (num_read_news == 0)
    {
        printf("YOu dont choose any news before.\n");
    }
    else
    {
        printf("Readed news are listed below:\n");
        int i;
        for (i = 0; i < num_read_news; i++)
        {
            /*Check if the news has already been listed */
            int already_listed = 0;
            int j;
            for (j = 0; j < i; j++)
            {
                if (strcmp(read_news_filenames[i], read_news_filenames[j]) == 0)
                {
                    already_listed = 1;
                    break;
                }
            }

            if (!already_listed)
            {
                printf("%s\n", read_news_filenames[i]);
            }
        }
    }
}

/*Calculates the secret number from the news text*/
int get_decrypted_info()
{
    FILE *file;
    char filename[100];
    int key;
    int secret_number = 0; /*calculate secret number*/
    char line[500];
    char next;
    int number = 0;
    int numbers_flag = 0;

    double sum = 0;
    int n = 0;

    printf("Which news would you like to decrypt?\n");
    scanf("%d", &key);

    /*Generate the filename */
    sprintf(filename, "%d.txt", key);

    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File does not exist\n");
        return 1;
    }

    while ((next = fgetc(file)) != EOF)
    {
        if (numbers_flag)
        {
            if (next >= '0' && next <= '9')
            {
                number = number * 10 + (next - '0');
            }
            else
            {
                if (number > 0 && number < 10)
                {
                    double result = pow(number, 3) - pow(number, 2) + 2;
                    sum += pow(result, 2);
                    n++;
                }
                number = 0;
                numbers_flag = 0;
            }
        }
        else if (next == '#')
        {
            /*read the value after '#'*/
            next = fgetc(file);
            if (next >= '0' && next <= '9')
            {
                numbers_flag = 1;
                number = next - '0';
            }
            else
            {
            }
        }
    }

    if (n > 0)
    {
        printf("experiment key : %.2f\n", sum);
    }
    else
    {
        printf("Not found.\n");
    }

    fclose(file);
}

int main()
{
    int flag = 1;
    char key;

    printf("*********Daily Press*********\n");
    printf("Today's news listed for you!\n");
    printf("Title of 1. news: Astronot Alper Gezeravci'nin Dunya'ya donusu ertelendi.\n");
    printf("Title of 2. news: Bakan Kacir, Astronot Alper Gezeravci  ile Videokonferans Gorusmesi Gerceklestirildi.\n");
    printf("Title of 3. news: Alper Gezeravci uzayda 9. deneyi yapti.\n");
    printf("Title of 4. news: Astronotlarin uzaydaki ilk sozleri.\n");

    while (flag)
    {
        printf("What do you want to do?\n");
        printf("a. Read a new.\n");
        printf("b. List the readed news.\n");
        printf("c. Get decrypted information from the news.\n");
        scanf(" %c", &key); /*Space added to clear the previous \n character*/

        switch (key)
        {
        case 'a':
            read_news();
            break;
        case 'b':
            list_read_news();
            break;
        case 'c':
            get_decrypted_info();
            break;
        default:
            printf("EXITING\n");
            flag = 0;
            break;
        }
    }

    return 0;
}