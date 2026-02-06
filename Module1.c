#include <stdio.h>
#include <string.h>

enum Priority
{
  DISABLED = 1,
  EMERGENCY,
  PREGNANT,
  SENIOR,
  NORMAL
};

struct Passenger;
void toLowerCase(char str[]);
struct Passenger collectPassengerData();
enum Priority decidePriority(struct Passenger p);
void getSeatRange(enum Priority p, int *start, int *end);
int seatchoice(struct Passenger p);
void showSeatLegend();

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
struct Passenger
{
  char name[100];
  int age;
  int gender; 
  int emergency;  
};

struct Bus buses[5];
int buscount = 0;
int selectedBusIndex = -1;
int bookedSeatNumber = -1;

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
    printf("\n BusNo: %d | %s -> %s | Date:%s | Seats: %d | Fare: %d", buses[i].busno, buses[i].source, buses[i].destination,buses[i].date, buses[i].totalseats, buses[i].fare);
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
int searchbus()
{
  char sour[100],dest[100],date[12];
  char bussour[100],busdest[100];
  int found = 0;
  selectedBusIndex = -1; 

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
      selectedBusIndex = i;
    }
  }

  if (found == 0)
  {
    printf("No matching buses found.\n");
    return 0;
  }
  return 1;
}

void showseats(int index)
{
  printf("\nSeat Status (0 = Available, 1 = Booked):\n");
  for (int i = 0; i < buses[index].totalseats; i++)
  {
    printf("Seat %d : %d\n", i + 1, buses[index].seats[i]);
  }
}

void bookseat()
{
  int busNo, seatNo, index = -1;
  printf("\nEnter Bus Number to book seat: ");
  scanf("%d", &busNo);
  for (int i = 0; i < buscount; i++)
  {
    if (buses[i].busno == busNo)
    {
      index = i;
      break;
    }
  }
  if (index == -1)
  {
    printf("Invalid Bus Number.\n");
    return;
  }
  showseats(index);
  printf("\nEnter Seat Number to book: ");
  scanf("%d", &seatNo);
  if (seatNo < 1 || seatNo > buses[index].totalseats)
  {
    printf("Invalid Seat Number.\n");
    return;
  }
  if (buses[index].seats[seatNo - 1] == 1)
  {
    printf("Seat already booked.\n");
  }
  else
  {
    buses[index].seats[seatNo - 1] = 1;
    printf("Seat %d booked successfully!\n", seatNo);
  }
}

void showSeatLegend()
{
  printf("\nSeat Reservation Rules:\n");
  printf("Seats 1-2: Disabled\n");
  printf("Seats 3-4: Emergency\n");
  printf("Seats 5-6: Pregnant\n");
  printf("Seats 7-8: Senior Citizen\n");
  printf("Seats 9+ : Normal\n");
}

int generateticketid()
{
  static int id = 1000;
  return id++;
}
int seatchoice(struct Passenger p)
{
    int index = selectedBusIndex;

    if (index == -1)
    {
        printf("Invalid bus.\n");
        return 0;
    }

    printf("\n--- Seat Priority Information ---\n");
    showSeatLegend();

    int seatsRequired;
    printf("\nEnter number of seats required: ");
    scanf("%d", &seatsRequired);

    int seatNumbers[10];

    /* -------- BUILD MULTIPLE PRIORITY RANGES -------- */
    int ranges[5][2];
    int rangeCount = 0;

    if (p.gender == 2) { ranges[rangeCount][0] = 1; ranges[rangeCount][1] = 2; rangeCount++; }
    if (p.emergency == 1) { ranges[rangeCount][0] = 3; ranges[rangeCount][1] = 4; rangeCount++; }
    if (p.gender == 3) { ranges[rangeCount][0] = 5; ranges[rangeCount][1] = 6; rangeCount++; }
    if (p.age >= 60) { ranges[rangeCount][0] = 7; ranges[rangeCount][1] = 8; rangeCount++; }

    while (1)
    {
        int choice;
        printf("\nSeat Choice:\n1. Auto\n2. Manual\nEnter choice: ");
        scanf("%d", &choice);

        /* ---------------- AUTO ---------------- */
        if (choice == 1)
        {
            int count = 0, priorityCount = 0;

            /* Priority seats */
            for (int r = 0; r < rangeCount && count < seatsRequired; r++)
            {
                for (int i = ranges[r][0]; i <= ranges[r][1] && count < seatsRequired; i++)
                {
                    if (buses[index].seats[i - 1] == 0)
                    {
                        seatNumbers[count++] = i;
                        priorityCount++;
                    }
                }
            }

            /* Normal seats */
            for (int i = 9; i <= buses[index].totalseats && count < seatsRequired; i++)
            {
                if (buses[index].seats[i - 1] == 0)
                    seatNumbers[count++] = i;
            }

            if (count < seatsRequired)
            {
                printf("Not enough seats available.\n");
                continue;
            }

            for (int i = 0; i < seatsRequired; i++)
                buses[index].seats[seatNumbers[i] - 1] = 1;

            if (priorityCount < seatsRequired)
                printf("Priority seats allocated: %d, Remaining %d from Normal (FCFS)\n",
                       priorityCount, seatsRequired - priorityCount);

            printf("Auto-selected Seats: ");
            for (int i = 0; i < seatsRequired; i++)
                printf("%d ", seatNumbers[i]);
            printf("\n");

            break;
        }

        /* ---------------- MANUAL ---------------- */
        else if (choice == 2)
        {
            showseats(index);
            int valid = 1;

            for (int i = 0; i < seatsRequired; i++)
            {
                printf("Enter Seat %d: ", i + 1);
                scanf("%d", &seatNumbers[i]);

                if (seatNumbers[i] < 1 || seatNumbers[i] > buses[index].totalseats ||
                    buses[index].seats[seatNumbers[i] - 1] == 1)
                {
                    valid = 0;
                    break;
                }

                int allowed = 0;
                for (int r = 0; r < rangeCount; r++)
                    if (seatNumbers[i] >= ranges[r][0] && seatNumbers[i] <= ranges[r][1])
                        allowed = 1;

                if (!allowed && seatNumbers[i] >= 9)
                    allowed = 1;

                if (!allowed)
                {
                    printf("Seat %d not allowed for your priority.\n", seatNumbers[i]);
                    valid = 0;
                    break;
                }
            }

            if (!valid) continue;

            for (int i = 0; i < seatsRequired; i++)
                buses[index].seats[seatNumbers[i] - 1] = 1;

            printf("Seats booked: ");
            for (int i = 0; i < seatsRequired; i++)
                printf("%d ", seatNumbers[i]);
            printf("\n");

            break;
        }
        else
            printf("Invalid choice.\n");
    }

    return 1;
}


struct Passenger collectPassengerData()
{
  struct Passenger p;
  int Pregnant = 0;
  int Disabled = 0;
  printf("\nEnter Passenger Name: ");
  getchar();
  scanf("%[^\n]", p.name);
  printf("Enter Passenger Age: ");
  scanf("%d", &p.age);
  printf("Enter Gender (1 = Female, 0 = Male): ");
  scanf("%d", &p.gender);
  if (p.gender == 1)
  {
    printf("Is the passenger pregnant? (1 = Yes, 0 = No):");
    scanf("%d", &Pregnant);
  }
  printf("Is the passenger disabled? (1 = Yes, 0 = No): ");
  scanf("%d", &Disabled);
  printf("Emergency Case? (1 = Yes, 0 = No): ");
  scanf("%d", &p.emergency);
  if (Disabled == 1)
  {
    p.gender = 2;
  }
  else if (Pregnant == 1)
  {
    p.gender = 3; 
  }
  return p;
}

enum Priority decidePriority(struct Passenger p)
{
  if (p.gender == 2)
  {
    return DISABLED;
  }
  else if (p.emergency == 1)
  {
    return EMERGENCY;
  }
  else if (p.gender == 3)
  {
    return PREGNANT;
  }
  else if (p.age >= 60)
  {
    return SENIOR;
  }
  else
  {
    return NORMAL;
  }
}
void getSeatRange(enum Priority p, int *start, int *end)
{
  if (p == DISABLED)
  {
    *start = 1; *end = 2;
  }
  else if (p == EMERGENCY)
  {
    *start = 3; *end = 4;
  }
  else if (p == PREGNANT)
  {
    *start = 5; *end = 6;
  }
  else if (p == SENIOR)
  {
    *start = 7; *end = 8;
  }
  else
  {
    *start = 9;
    *end = buses[selectedBusIndex].totalseats;
  }
}

void main() 
{ 
  initBuses();
  displayBuses();
  if (!searchbus())
  {
    return;
  }
  int busNo;
  printf("\nEnter Bus Number: ");
  scanf("%d", &busNo);
  if (selectedBusIndex == -1 || buses[selectedBusIndex].busno != busNo)
  {
    printf("Invalid bus number selected.\n");
    return;
  }
  struct Passenger p = collectPassengerData();
  if (!seatchoice(p)) 
  {
    return;
  }
}