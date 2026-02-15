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

struct Bus buses[5];
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
  if (selectedBusIndex == -1 || buses[selectedBusIndex].busno != busNo)
  {
    printf("\n Invalid Bus Number selected.\n");
    return;
  }
  for (int i = 0; i < buscount; i++)
  {
    if (buses[i].busno == busNo)
    {
      selectedBusIndex = i;
      break;
    }
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