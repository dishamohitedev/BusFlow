#include <stdio.h>
#include <string.h>
void toLowerCase(char str[]);
struct Bus 
{
    int busno;
    char source[100];
    char destination[100];
    char date[12];
    int totalseats;
    int fare;
    int seats[80];   
};
struct Bus buses[5];
int buscount = 0;
void initBuses() 
{
    buscount = 5;
    buses[0].busno =101;
    strcpy(buses[0].source, "Mumbai");
    strcpy(buses[0].destination, "Pune");
    strcpy(buses[0].date, "01-02-2026");
    buses[0].totalseats = 50;
    buses[0].fare = 1000;
    buses[1].busno =102;
    strcpy(buses[1].source, "Mumbai");
    strcpy(buses[1].destination, "Delhi");
    strcpy(buses[1].date, "02-02-2026");
    buses[1].totalseats = 50;
    buses[1].fare = 2000;
    buses[2].busno=103;
    strcpy(buses[2].source, "Mumbai");
    strcpy(buses[2].destination, "Banglore");
    strcpy(buses[2].date, "03-02-2026");
    buses[2].totalseats = 50;
    buses[2].fare = 5000;
    buses[3].busno=104;
    strcpy(buses[3].source, "Mumbai");
    strcpy(buses[3].destination, "Ahemdabad");
    strcpy(buses[3].date, "04-02-2026");
    buses[3].totalseats = 50;
    buses[3].fare = 4000;
    buses[4].busno =105;
    strcpy(buses[4].source, "Mumbai");
    strcpy(buses[4].destination, "Nashik");
    strcpy(buses[4].date, "05-02-2026");
    buses[4].totalseats = 50;
    buses[4].fare = 800;
    for (int i = 0; i<buscount; i++)
    {
        for (int j = 0; j<buses[i].totalseats && j<80; j++)
        {
            buses[i].seats[j] = 0;
        }
    }
}
void displayBuses() 
{
  printf("\n Available Buses:");
  for (int i = 0; i<buscount; i++) 
  {
    printf("\n BusNo: %d | %s -> %s | Date:%s | Seats: %d | Fare: %d\n", buses[i].busno, buses[i].source, buses[i].destination,buses[i].date, buses[i].totalseats, buses[i].fare);
    }
}
void toLowerCase(char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] + 32;
        }
        i++;
    }
}
void searchbus()
{
    char sour[100],dest[100],date[12];
    char bussour[100],busdest[100];
    int found = 0;
    printf("\n Enter Source:");
    scanf("%s",sour);
    printf("\n Enter Destination:");
    scanf("%s",dest);
    printf("\n Enter Date (dd-mm-yyyy):");
    scanf("%s",date);
    toLowerCase(sour);
    toLowerCase(dest);
    printf("\nMatching Buses:\n");
    for (int i = 0; i < buscount; i++)
    { 
      strcpy(bussour, buses[i].source);
      strcpy(busdest, buses[i].destination);
      toLowerCase(bussour);
      toLowerCase(busdest);
      if (strcmp(bussour, sour) == 0 && strcmp(busdest, dest) == 0 && strcmp(buses[i].date, date) == 0)
      {
        printf("BusNo: %d | %s -> %s | Date:%s | Seats:%d | Fare:%d\n",buses[i].busno,buses[i].source, buses[i].destination, buses[i].date, buses[i].totalseats,buses[i].fare);
        found = 1;
      }
    }
    if (found == 0)
    {
        printf("No matching buses found.\n");
    }
}
void main() 
{
    initBuses();
    displayBuses();
    searchbus();
}