#include <stdio.h>
#include <string.h>

struct Passenger;
void toLowerCase(char str[]);
struct Passenger collectPassengerData();
int seatchoice();
void showSeatLegend();
void addToWaitingList(struct Passenger p);
void reallocateSeat();
void saveTicketToFile();
void saveSeatsToFile();
void loadSeatsFromFile();

struct Bus 
{
  int busno;
  char source[100];
  char destination[100];
  char date[12];
  char departure[10];
  char arrival[10];
  int totalseats;
  int fare;
  int seats[80];   
};
struct Passenger
{
  char name[100];
  int age;
  int gender;        
  int pregnant;      
  int disabled;     
  int emergency;     
};

struct Bus buses[15];
int buscount = 0;
int selectedBusIndex = -1;
int bookedSeatNumber = -1;
#define MAX_PASSENGERS 10
struct Passenger passengers[MAX_PASSENGERS];
int passengerCount = 0;
int allocatedSeats[MAX_PASSENGERS];
int lastGeneratedTicketId = -1;
#define MAX_WAITING 20
struct Passenger waitingList[MAX_WAITING];
int waitingCount = 0;

void initBuses() 
{
  buscount = 11;

  buses[0].busno =64;
  strcpy(buses[0].source, "Mumbai");
  strcpy(buses[0].destination, "Pune");
  strcpy(buses[0].date, "01-02-2026");
  strcpy(buses[0].departure, "06:00");
  strcpy(buses[0].arrival, "09:30");
  buses[0].totalseats = 50;
  buses[0].fare = 1000;

  buses[1].busno = 85;
  strcpy(buses[1].source, "Mumbai");
  strcpy(buses[1].destination, "Pune");
  strcpy(buses[1].date, "01-02-2026");
  strcpy(buses[1].departure, "12:00");
  strcpy(buses[1].arrival, "15:30");
  buses[1].totalseats = 50;
  buses[1].fare = 1200;

  buses[2].busno = 912;
  strcpy(buses[2].source, "Mumbai");
  strcpy(buses[2].destination, "Pune");
  strcpy(buses[2].date, "01-02-2026");
  strcpy(buses[2].departure, "18:00");
  strcpy(buses[2].arrival, "21:30");
  buses[2].totalseats = 50;
  buses[2].fare = 1100;


  buses[3].busno =401;
  strcpy(buses[3].source, "Mumbai");
  strcpy(buses[3].destination, "Delhi");
  strcpy(buses[3].date, "02-02-2026");
  strcpy(buses[3].departure, "07:00");
  strcpy(buses[3].arrival, "21:00");
  buses[3].totalseats = 50;
  buses[3].fare = 2000;

  buses[4].busno = 728;
  strcpy(buses[4].source, "Mumbai");
  strcpy(buses[4].destination, "Delhi");
  strcpy(buses[4].date, "02-02-2026");
  strcpy(buses[4].departure, "16:00");
  strcpy(buses[4].arrival, "06:00");
  buses[4].totalseats = 50;
  buses[4].fare = 2300;


  buses[5].busno = 222;
  strcpy(buses[5].source, "Mumbai");
  strcpy(buses[5].destination, "Banglore");
  strcpy(buses[5].date, "03-02-2026");
  strcpy(buses[5].departure, "06:00");
  strcpy(buses[5].arrival, "20:00");
  buses[5].totalseats = 50;
  buses[5].fare = 3500;

  buses[6].busno = 989;
  strcpy(buses[6].source, "Mumbai");
  strcpy(buses[6].destination, "Banglore");
  strcpy(buses[6].date, "03-02-2026");
  strcpy(buses[6].departure, "17:00");
  strcpy(buses[6].arrival, "07:00");
  buses[6].totalseats = 50;
  buses[6].fare = 3300;


  buses[7].busno = 563;
  strcpy(buses[7].source, "Mumbai");
  strcpy(buses[7].destination, "Ahemdabad");
  strcpy(buses[7].date, "04-02-2026");
  strcpy(buses[7].departure, "05:30");
  strcpy(buses[7].arrival, "13:30");
  buses[7].totalseats = 50;
  buses[7].fare = 1800;

  buses[8].busno = 294;
  strcpy(buses[8].source, "Mumbai");
  strcpy(buses[8].destination, "Ahemdabad");
  strcpy(buses[8].date, "04-02-2026");
  strcpy(buses[8].departure, "14:00");
  strcpy(buses[8].arrival, "22:00");
  buses[8].totalseats = 50;
  buses[8].fare = 1700;


  buses[9].busno = 811;
  strcpy(buses[9].source, "Mumbai");
  strcpy(buses[9].destination, "Nashik");
  strcpy(buses[9].date, "05-02-2026");
  strcpy(buses[9].departure, "08:00");
  strcpy(buses[9].arrival, "11:30");
  buses[9].totalseats = 50;
  buses[9].fare = 900;

  buses[10].busno = 376;
  strcpy(buses[10].source, "Mumbai");
  strcpy(buses[10].destination, "Nashik");
  strcpy(buses[10].date, "05-02-2026");
  strcpy(buses[10].departure, "18:00");
  strcpy(buses[10].arrival, "21:30");
  buses[10].totalseats = 50;
  buses[10].fare = 850;

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
  printf("\nAvailable Routes:\n");
  for (int i = 0; i < buscount; i++)
  {
    int alreadyPrinted = 0;
    for (int j = 0; j < i; j++)
    {
      if (strcmp(buses[i].source, buses[j].source) == 0 && strcmp(buses[i].destination, buses[j].destination) == 0)
      {
        alreadyPrinted = 1;
        break;
      }
    }
    if (!alreadyPrinted)
    {
      printf("%s -> %s\n", buses[i].source, buses[i].destination);
    }
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
void convertTo12Hour(char time24[], char time12[])
{
  int hour, minute;
  char period[3];
  sscanf(time24, "%d:%d", &hour, &minute);
  if (hour == 0)
  {
    hour = 12;
    strcpy(period, "AM");
  }
  else if (hour < 12)
  {
    strcpy(period, "AM");
  }
  else if (hour == 12)
  {
        strcpy(period, "PM");
  }
    else
    {
        hour -= 12;
        strcpy(period, "PM");
    }

    sprintf(time12, "%02d:%02d %s", hour, minute, period);
}
int searchbus()
{
  char sour[100],dest[100];
  char bussour[100],busdest[100];
  int found = 0;
  selectedBusIndex = -1; 

  printf("\n Enter Source:");
  scanf("%s",sour);
  printf("\n Enter Destination:");
  scanf("%s",dest);

  toLowerCase(sour);
  toLowerCase(dest);

  printf("\nMatching Buses:\n");
  for (int i = 0; i < buscount; i++)
  { 
    strcpy(bussour, buses[i].source);
    strcpy(busdest, buses[i].destination);

    toLowerCase(bussour);
    toLowerCase(busdest);

    if (strcmp(bussour, sour) == 0 && strcmp(busdest, dest) == 0) 
    {
      char dep12[15], arr12[15];
      convertTo12Hour(buses[i].departure,dep12);
      convertTo12Hour(buses[i].arrival, arr12);
      printf("BusNo: %d | %s -> %s | Date: %s | Dep: %s | Arr: %s | Fare:%d\n",buses[i].busno, buses[i].source, buses[i].destination, buses[i].date, dep12, arr12, buses[i].fare);
      found = 1;
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
void printAllowedSeats(struct Passenger p)
{
  printf("Allowed seats: ");
  if (p.disabled)   printf("1-2 ");
  if (p.emergency)  printf("3-4 ");
  if (p.pregnant)   printf("5-6 ");
  if (p.age >= 60)  printf("7-8 ");
  printf("9+\n");
}

int generateticketid()
{
  FILE *fp;
  int id=1000;
  fp = fopen("ticketid.txt", "r");
  if (fp != NULL)
  {
    fscanf(fp, "%d", &id);
    fclose(fp);
  }
  fp = fopen("ticketid.txt", "w");
  if (fp == NULL)
  {
    return id;
  }
  fprintf(fp, "%d", id + 1);
  fclose(fp);
  return id;
}
int seatchoice()
{
  int index = selectedBusIndex;
  if (index == -1)
  {
    printf("Invalid bus.\n");
    return 0;
  }
  printf("\n--- Seat Priority Information ---");
  showSeatLegend();
  int choice;
  printf("\nSeat Choice:\n1. Auto\n2. Manual\nEnter choice: ");
  scanf("%d", &choice);
  if (choice == 1)
  {
    for (int i = 0; i < passengerCount; i++)
    {
      int seatFound = 0;
      if (passengers[i].disabled)
      {
        for (int s = 1; s <= 2; s++)
        if (buses[index].seats[s - 1] == 0)
        {
          allocatedSeats[i] = s;
          buses[index].seats[s - 1] = 1;
          seatFound = 1;
          break;
        }
      }
      if (!seatFound && passengers[i].emergency == 1)
      {
        for (int s = 3; s <= 4; s++)
        if (buses[index].seats[s - 1] == 0)
        {
          allocatedSeats[i] = s;
          buses[index].seats[s - 1] = 1;
          seatFound = 1;
          break;
        }
      }
      if (!seatFound && passengers[i].pregnant)
      {
        for (int s = 5; s <= 6; s++)
        if (buses[index].seats[s - 1] == 0)
        {
          allocatedSeats[i] = s;
          buses[index].seats[s - 1] = 1;
          seatFound = 1;
          break;
        }
      }
      if (!seatFound && passengers[i].age >= 60)
      {
        for (int s = 7; s <= 8; s++)
        if (buses[index].seats[s - 1] == 0)
        {
          allocatedSeats[i] = s;
          buses[index].seats[s - 1] = 1;
          seatFound = 1;
          break;
        }
      }
      if (!seatFound)
      {
        for (int s = 9; s <= buses[index].totalseats; s++)
        if (buses[index].seats[s - 1] == 0)
        {
          allocatedSeats[i] = s;
          buses[index].seats[s - 1] = 1;
          seatFound = 1;
          break;
        }
      }
      if (!seatFound)
      {
        printf("\nSeats are FULL.\n");
        for (int j = i; j < passengerCount; j++)
        {
          addToWaitingList(passengers[j]);
        }
        return 0;
     }
    }
    printf("\n--- Seat Allocation Summary (AUTO) ---\n");
    for (int i = 0; i < passengerCount; i++)
    printf("Passenger %d -> Seat %d\n", i + 1, allocatedSeats[i]);
    return 1;
  }
  else if (choice == 2)
  {
    int full = 1;
    for (int s = 0; s < buses[index].totalseats; s++)
    {
      if (buses[index].seats[s] == 0)
      {
        full = 0;
        break;
      }
    }
    if (full)
    {
      printf("\nSeats are FULL.\n");
      for (int i = 0; i < passengerCount; i++)
      {
        addToWaitingList(passengers[i]);
      }
      return 0;
    }
    showseats(index);
    for (int i = 0; i < passengerCount; i++)
    {
      int seat;
      while (1)
      {
        printf("Passenger %d (Allowed seats: ", i + 1);
        if (passengers[i].disabled)   printf("1-2 ");
        if (passengers[i].emergency)  printf("3-4 ");
        if (passengers[i].pregnant)   printf("5-6 ");
        if (passengers[i].age >= 60)  printf("7-8 ");
        printf("9+)");
        printf("\n Enter seat no. : ");
        if (scanf("%d", &seat) != 1)
        {
          printf("Invalid input. Please enter a number.\n");
          while (getchar() != '\n');
          continue;
        }
        if (seat < 1 || seat > buses[index].totalseats)
        {
          printf("Invalid seat number.\n");
          continue;
        }
        if (buses[index].seats[seat - 1] == 1)
        {
          printf("Seat already booked.\n");
          continue;
        }
        int allowed = 0;
        if (passengers[i].disabled  && seat >= 1 && seat <= 2) allowed = 1;
        if (passengers[i].emergency && seat >= 3 && seat <= 4) allowed = 1;
        if (passengers[i].pregnant  && seat >= 5 && seat <= 6) allowed = 1;
        if (passengers[i].age >= 60 && seat >= 7 && seat <= 8) allowed = 1;
        if (seat >= 9) allowed = 1;
        if (!allowed)
        {
          printf("Seat not allowed for this passenger.\n");
          continue;
        }
        buses[index].seats[seat - 1] = 1;
        allocatedSeats[i] = seat;
        break;
      }  
    }
    printf("\n--- Seat Allocation Summary (MANUAL) ---\n");
    for (int i = 0; i < passengerCount; i++)
    printf("Passenger %d -> Seat %d\n", i + 1, allocatedSeats[i]);
    return 1;
  }
  else
  {
    printf("Invalid choice.\n");
    return 0;
  }
}

struct Passenger collectPassengerData()
{
  struct Passenger p;
  printf("\nEnter Passenger Name: ");
  getchar();
  scanf("%[^\n]", p.name);
  printf("Enter Passenger Age: ");
  scanf("%d", &p.age);
  printf("Enter Gender (1 = Female, 0 = Male): ");
  scanf("%d", &p.gender);
  if (p.gender == 1)
  {
    printf("Is the passenger pregnant? (1 = Yes, 0 = No): ");
    scanf("%d", &p.pregnant);
  }
  else
  {
    p.pregnant = 0;
  }
  printf("Is the passenger disabled? (1 = Yes, 0 = No): ");
  scanf("%d", &p.disabled);
  printf("Emergency Case? (1 = Yes, 0 = No): ");
  scanf("%d", &p.emergency);
  return p;
}
void generateTicketAndSummary()
{
  if (selectedBusIndex < 0 || selectedBusIndex >= buscount)
  {
    printf("\n Ticket generation failed: Invalid bus index.\n");
    return;
  }
  if (passengerCount <= 0)
  {
    printf("\n No passengers booked.\n");
    return;
  }
  lastGeneratedTicketId = generateticketid();
  int ticketId = lastGeneratedTicketId;
  int totalFare = passengerCount * buses[selectedBusIndex].fare;
  printf("\n====================================");
  printf("\n        TEMPORARY TICKET");
  printf("\n====================================");
  printf("\nTicket ID      : %d", ticketId);
  printf("\nTotal Seats    : %d", passengerCount);
  printf("\nTotal Fare     : %d", totalFare);
  printf("\nBooked Seat no.: ");
  for (int i = 0; i < passengerCount; i++)
  {
    printf("%d ", allocatedSeats[i]);
  }
  printf("\n====================================\n");
}

void saveTicketToFile()
{
  FILE *fp = fopen("tickets.txt", "a");
  if (fp == NULL)
  {
    printf("Error opening ticket file.\n");
    return;
  }
  fprintf(fp, "Ticket ID: %d\n", lastGeneratedTicketId);
  fprintf(fp, "Bus No: %d\n", buses[selectedBusIndex].busno);
  fprintf(fp, "Passengers: %d\n", passengerCount);
  fprintf(fp, "Total Fare: %d\n", passengerCount * buses[selectedBusIndex].fare);
  for (int i = 0; i < passengerCount; i++)
  {
    fprintf(fp, "Name: %s | Age: %d | Seat: %d\n", passengers[i].name,passengers[i].age,allocatedSeats[i]);
  }
  fprintf(fp, "-----------------------------------\n");
  fclose(fp);
}
void saveSeatsToFile()
{
  FILE *fp = fopen("seats.dat", "wb");
  if (fp == NULL)
  {
    return;
  }      
  fwrite(buses, sizeof(struct Bus), buscount, fp);
  fclose(fp);
}
void loadSeatsFromFile()
{
  FILE *fp = fopen("seats.dat", "rb");
  if (fp == NULL)
  {
    return;
  }    
  fread(buses, sizeof(struct Bus), buscount, fp);
  fclose(fp);
}

int confirmTicket()
{
  char choice[10];
  printf("\n====================================");
  printf("\n        TICKET CONFIRMATION");
  printf("\n====================================");
  printf("\nConfirm Ticket?");
  printf("\nEnter Yes / No (Y/N/1/0): ");
  scanf("%s", choice);
  toLowerCase(choice);
  if (strcmp(choice, "y") == 0 || strcmp(choice, "yes") == 0 || strcmp(choice, "1") == 0)
  {
    return 1;  
  }
  else if (strcmp(choice, "n") == 0 || strcmp(choice, "no") == 0 || strcmp(choice, "0") == 0)
  {
    return 0;   
  }
  else
  {
    printf("\nInvalid input. Ticket NOT confirmed.\n");
  }
}
void bookingCompletionDisplay()
{
  printf("\n====================================");
  printf("\n         FINAL TICKET DETAILS");
  printf("\n====================================");
  printf("\nTicket ID      : %d", lastGeneratedTicketId);
  printf("\nBus Number     : %d", buses[selectedBusIndex].busno);
  printf("\nRoute          : %s -> %s", buses[selectedBusIndex].source, buses[selectedBusIndex].destination);
  printf("\nDate           : %s", buses[selectedBusIndex].date);
  printf("\n------------------------------------");
  for (int i = 0; i < passengerCount; i++)
  {
    printf("\nPassenger %d", i + 1);
    printf("\nName       : %s", passengers[i].name);
    printf("\nAge        : %d", passengers[i].age);
    printf("\nSeat No.   : %d", allocatedSeats[i]);
    printf("\n------------------------------------");
  }
  printf("\nTotal Passengers : %d", passengerCount);
  printf("\nFare per Seat    : %d", buses[selectedBusIndex].fare);
  printf("\nTotal Fare       : %d", passengerCount * buses[selectedBusIndex].fare);
  printf("\n====================================");
  printf("\n BOOKING SUCCESSFUL!");
  printf("\n Happy Journey!");
  printf("\nThank you for choosing our Bus Service.");
  printf("\n====================================\n");
}
void cancelTicket()
{
  int enteredTicketId;
  printf("\n====================================");
  printf("\n        TICKET CANCELLATION");
  printf("\n====================================");
  printf("\nEnter Ticket ID to cancel: ");
  scanf("%d", &enteredTicketId);
  if (enteredTicketId != lastGeneratedTicketId || lastGeneratedTicketId == -1)
  {
    printf("\n Invalid Ticket ID.");
    printf("\nCancellation Failed.\n");
    return;
  }
  for (int i = 0; i < passengerCount; i++)
  {
    int seat = allocatedSeats[i];
    buses[selectedBusIndex].seats[seat - 1] = 0;
  }
  printf("\n------------------------------------");
  printf("\n TICKET CANCELLED SUCCESSFULLY");
  printf("\nWe are sorry to inform you that");
  printf("\nyour ticket has been cancelled.");
  printf("\n------------------------------------");
  reallocateSeat();
  saveSeatsToFile();
  passengerCount = 0;
  lastGeneratedTicketId = -1;
}

void addToWaitingList(struct Passenger p)
{
  if (waitingCount >= MAX_WAITING)
  {
    printf("\nWaiting List is FULL.\n");
    return;
  }
  waitingList[waitingCount] = p;
  waitingCount++;
  printf("\n====================================");
  printf("\n      WAITING LIST CONFIRMATION");
  printf("\n====================================");
  printf("\nPassenger Name : %s", p.name);
  printf("\nWaiting Number : WL %d", waitingCount);
  printf("\nStatus         : Waiting");
  printf("\n====================================\n");
}
void reallocateSeat()

{
  if (waitingCount == 0)
  {
    return;
  }
  int index = selectedBusIndex;
  for (int s = 0; s < buses[index].totalseats; s++)
  {
    if (buses[index].seats[s] == 0)  
    {
      int selected = -1;
      for (int i = 0; i < waitingCount; i++)
      {
        if (waitingList[i].disabled)
        {
          selected = i;
          break;
        }
      }
      if (selected == -1)
      {
        for (int i = 0; i < waitingCount; i++)
        {
          if (waitingList[i].emergency)
          {
            selected = i;
            break;
          }
        }
      }
      if (selected == -1)
      {
        for (int i = 0; i < waitingCount; i++)
          {
            if (waitingList[i].pregnant)
            {
              selected = i;
              break;
            }
          }
      }
      if (selected == -1)
      {
        for (int i = 0; i < waitingCount; i++)
        {
          if (waitingList[i].age >= 60)
          {
            selected = i;
            break;
          }
        }
      }
      if (selected == -1 && waitingCount > 0)
      {
        selected = 0;
      }
      if (selected != -1)
      {
        buses[index].seats[s] = 1;
        printf("\n====================================");
        printf("\n  WAITING LIST SEAT REALLOCATED");
        printf("\n====================================");
        printf("\nPassenger Name : %s", waitingList[selected].name);
        printf("\nNew Seat No    : %d", s + 1);
        printf("\nStatus         : CONFIRMED");
        printf("\n====================================\n");
        for (int j = selected; j < waitingCount - 1; j++)
        {
          waitingList[j] = waitingList[j + 1];
        }
        waitingCount--;
        break;  
      }
    }
  }
}

void main() 
{ 
  initBuses();
  loadSeatsFromFile();
  displayBuses();
  if (!searchbus())
  {
    return;
  }
  int busNo;
  printf("\nEnter Bus Number: ");
  scanf("%d", &busNo);
  for (int i = 0; i < buscount; i++)
  {
    if (buses[i].busno == busNo)
    {
      selectedBusIndex = i;
      break;
    }
  }
  if (selectedBusIndex == -1)
  {
    printf("\nInvalid Bus Number selected.\n");
    return;
  }
  printf("\nEnter number of seats required: ");
  scanf("%d", &passengerCount);
  for (int i = 0; i < passengerCount; i++)
  {
    printf("\n--- Passenger %d Details ---\n", i + 1);
    passengers[i] = collectPassengerData();
  }
  if (!seatchoice())
  {
    printf("\nBooking moved to Waiting List.\n");
    return;
  }
  generateTicketAndSummary();         
  while (1)
  {
    int confirmation = confirmTicket();
    if (confirmation == 1)
    {
        bookingCompletionDisplay();
        saveTicketToFile();
        saveSeatsToFile();
        break;   
    }
    else
    {
      int previousTicketId = lastGeneratedTicketId;
      cancelTicket();
      if (lastGeneratedTicketId == previousTicketId)
      {
    
        continue;  
      }
      else
      {
        break;   
      }
    }
  }
}