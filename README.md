# 🚌 BusFlow – Console Based Bus Reservation System (C)

BusFlow is a console-based Bus Ticket Reservation System built using the C programming language.

This is my first complete system-level project in C where I implemented real-world concepts like seat management, ticket generation, waiting list handling, cancellation, and file persistence.

---
---
## 🚀 Project Features

### 🔎 1. Bus Search System

✔ Search bus by:
- Source
- Destination
- Date

✔ Case-insensitive search

---

### 💺 2. Smart Seat Allocation System

Two booking modes:

#### 🔹 Auto Mode

Seats are automatically assigned based on passenger priority:

| Category | Seat Range |
|----------|------------|
| Disabled | 1 – 2 |
| Emergency | 3 – 4 |
| Pregnant | 5 – 6 |
| Senior Citizen (60+) | 7 – 8 |
| Normal | 9+ |

#### 🔹 Manual Mode

- User selects seat manually
- System validates:
  - Seat availability
  - Seat priority eligibility
  - Input correctness

---

### 🎟 3. Unique Ticket ID Generation

- Automatically generates incremental Ticket IDs
- Stored in `ticketid.txt`
- Starts from 1000
- Persists between runs

---

### 💾 4. File Handling (Data Persistence)

The system saves data even after program closes.

Files used:

- `seats.dat` → Stores seat booking status
- `tickets.txt` → Stores confirmed ticket records
- `ticketid.txt` → Stores last generated ticket ID

---

### ⏳ 5. Waiting List System

If seats are full:
- Passengers are moved to waiting list

On cancellation:
- Seats are reallocated based on priority

---

### ❌ 6. Ticket Cancellation

- Cancel using Ticket ID
- Frees allocated seats
- Automatically reassigns seat to waiting list passenger

---
---
## 🛠 Concepts Used

- Structures (`struct Bus`, `struct Passenger`)
- Arrays
- Global variables
- File handling (`fopen`, `fread`, `fwrite`, `fprintf`)
- Binary file storage
- String manipulation
- Case-insensitive search
- Input validation
- Modular programming
- Priority-based logic design
---
---
## 📂 Project Structure

```
BusFlow/
│
├── Module1.c        # Main program file
├── seats.dat        # Seat booking binary file
├── tickets.txt      # Ticket records
├── ticketid.txt     # Stores last ticket ID
└── README.md        # Project documentation
```

---
---
## ▶️ How to Run the Program

### Step 1: Compile
gcc Module1.c -o BusFlow

### Step 2: Run
./BusFlow 

---
---
## 🧠 System Workflow

1. Initialize buses  
2. Load saved seat data  
3. Display available buses  
4. Search bus  
5. Enter passenger details  
6. Choose seat mode (Auto / Manual)  
7. Generate temporary ticket  
8. Confirm booking  
9. Save ticket & seat data  
10. Allow cancellation if needed  
---
---

## 🎯 Learning Outcomes

Through this project, I learned:

- How real-world reservation systems work  
- How to persist data using files  
- How to design priority-based seat logic  
- How to manage waiting lists  
- How to handle user input safely  
- How to modularize large C programs  
---
---

## 📌 Future Improvements

- Multiple ticket lookup  
- Admin dashboard  
- Payment simulation  
- Multiple bus management via file  
- Database integration (MySQL)  
- Better UI formatting  
---
---

## 👨‍💻 Author

Built as part of my C programming learning journey.

