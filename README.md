# Irrigation Work Summary Software

I made this project for a Database course at VIU. It is designed to run
on a very specific system, and I have not worked out all the kinks in
replicating the same environment so that the project could be built and
ran on other machines.

This project is hosted here to showcase/backup my work. It is by no means
a finished product. In fact,

***THIS PROJECT IS DEPRECIATED***.

## Installation

**Dependencies:**

```bash
apt install g++-4.9 libaio1
```

This project also requires an Oracle server.

## Usage

I had to change the make file to upload to viu learn.
```bash
make

./src/main
```

## Introduction

> The project report can be found at the end of this document.

For this project, I have decided to create a database management system for an irrigation company. I chose this because I have been working in irrigation for three years, and have a large amount of experience dealing with invoicing and customer management, with regards to that industry.

The end-users for this project are irrigation technicians and office administrators. Both of these users would have separate interfaces to the database. Irrigation technicians will be able to clock in and clock out, as well as add parts to an invoice. Office administrators will be able to create invoices and update their status. Finally, irrigation technicians and office administrators will be able to add customers.

**For this project I made several assumptions:**

1. Customers will be paying invoices through Paypal and so no information related to payment is required by this system.
2. Payroll for employees will be handled by a different system.

### Business Operations

The irrigation company handles all things related to an irrigation system. This includes:

- Irrigation system evaluations
- Irrigation system installations
- Irrigation system repairs and improvements
- Starting up and checking over irrigation systems in the spring
- Winterizing irrigation systems in the fall

We make money by billing for labour and parts used in completing a job. This means that we need a comprehensive list of all parts used at each job (recorded by the technicians), and all hours spend on the job for all employees that were present. There is also the case where an employee may need to see a record of all work that has been done at a customers house, to get an idea of what the current state of their irrigation system is (as some modifications and improvements are spread out over a long period of time to allow incremental billing), both the irrigation technicians and the office administrators need access to this information. The final thing that needs to be recorded for each and every job is a description of the work that was done. We need this for three reasons:

1. So that the office knows what works was done
2. So that there is a record of all work that has been done on the customers record
3. So that we can provide our customers with an outline of what they are paying for

### Data Description

To operate an irrigation business there are five main things you need to keep track of:

1. Parts purchased (just what they cost us)
2. Parts billed out
3. Customers billing information
4. Invoices for each job
5. Employees hours on the clock and at each job as well as their hourly rate

Customers can have multiples invoices, where the invoices contain the date the work started, the data that is finished, and the date the invoice was sent to the customer. If any parts were used to complete the work, then a list of which parts, and how many of each part was used. An invoice also outlines clock-in and clock-out data that shows when an employee arrives, when they break for lunch, and when they leave for the day. This data is then used to calculate the number of hours the employee was on the job, which are multiples that by the rate that the employee charges to get the cost of labour.

## Application Design

This section outlines the functionality and design of this project.

### Functionality Description

The main functionalities of this application are:

**Office Administrators will be able to:**

1. Create an invoice, thus scheduling work to be done.

**Irrigation technicians can:**

1. Clock in and out for a job

**Functionalities available to all user groups:**

1. Add parts and notes to an invoice
2. See all invoices for a particular customer
3. See all parts on an invoice
4. See all customers information
5. Add a customer to the system

### Interface Design

This application will have two separate interfaces dependent on whether the employee that logged in is a technician or an office administrator. The interface for this application will be text-based.

I have numbered the different interfaces for ease of explanation, and pressing the key that is in between the `[]` will be used to select that option. For example, you could select option `[C]` in interface 1 below by pressing "c" on the keyboard.

### Interface Documentation Legend

The text that will be shown to the user is indented with four spaces, and my notes on the interface are not indented. The number assigned to the interface is the number that appears not indented and directly above the indented text block. Text that is indented with 6 spaces represents dialogues that will be displayed to the user one at a time, if data does not pass error detection, the user will be shown the following menu:


**Interface Assumptions:**

- At this point, I do not know if it will be better to have the option listings above or below the data listed in this application. For, example, if I am listing all of the invoices in the system, do I want the option to go back to the previous menu to appear above or below the data? for now, I will leave it above.
- In the case of this project, I am using my school login to the database, in a finished version of this application, there would be user records for all employees and based on that employee's position (technician or admin) they would be greeted with their respective menu. For this application, the user will first be asked to enter their database login credentials, then they will be greeted with interface 0 listed below, to serve as a way of testing the application for both user sets.

**Interface 0**

```text
    Select user group:
    
    Press [A] for admin, and [T] for technician.
```

- `[A]` Goes to interface 1.
- `[T]` Goes to interface 4.

### Administrator only interfaces

The following are interfaces that are only available to employees that have the position admin.

**Interface 1:**

```text
    Welcome to the Irrigation Billing 5000 management application

    You are logged in as: Sam Erickson

    Press:
    [C] To see customer options
    [I] To see invoice options
    [E] To see employee options
    [P] To see parts options
    [Q] To quit
```

- `[C]` Goes to interface 6.
- `[I]` Goes to interface 3.
- `[E]` Goes to interface 2.
- `[P]` Goes to interface 9.
- `[Q]` Will quit the application.

**Interface 2:**

```text
    Employee Options

    Press:
    [U] To update employee record
    [B] To go back to main menu
```

- `[U]` Stays at interface 2 after showing prompt 1.
- `[B]` Goes to interface 2.

**Interface 3:**

```text
    Invoice options

    Press:
    [C] To create a new invoice
    [P] List all parts used in invoice
    [S] To view invoices for a specific customer
    [B] To go back to main menu
```

- `[C]` Shows user prompt 3,stays at interface 3.
- `[P]` Goes to interface 9.
- `[S]` Goes to interface 8 after showing prompt 4.
- `[B]` Goes to interface 2 if admin, interface 4 if technician.

### Interfaces That Are Only Available To technicians

The following are interfaces that are only available to employees that have
the position technician.

**Interface 4:**

```text
    Welcome to the Irrigation Billing 5000 management application

    You are logged in as: Sam Erickson

    Press: 
    [C] To see customer options
    [I] To see invoice options
    [Q] To quit
```

The name Sam Erickson would be replaced with the name of the employee who is
currently logged in (if different from Sam Erickson).

- `[C]` Goes to interface 6.
- `[I]` Goes to interface 5.
- `[Q]` Will quit the application.

**Interface 5:**

```text
    Invoice Options

    Press:
    [P] List all parts used for invoice
    [S] To view invoices for a specific customers
    [B] To go back to main menu
```

- `[P]` Goes to interface 10 after showing prompt 2.
- `[S]` Goes to interface 8 after showing prompt 4.
- `[B]` Goes to interface 2 if admin, 4 if technician.

### Interfaces Available to All Users

All of the interfaces below are available to all users of the system. Making
the assumption that the user has been validated, and has access to the database.

**Interface 6:**

```text
    Customer Options

    Press:
    [A] To add a new customer
    [S] To list all invoices for a customer by id
    [L] To list all customers
    [B] To go back to main menu
```

- `[A]` Shows prompt 5, stays at interface 6.
- `[S]` Goes to interface 8 after showing prompt 2.
- `[L]` Goes to interface 7.
- `[B]` Goes to interface 2 if admin, 4 if technician.

**Interface 7:**

```text
    Customer List

    Press:
    [B] To return to customer Options

    first_name  last_name  address                     email              phone
    ----------  ---------  --------------------------  -----------------  ----------
    Patrick     Star       12 Rockroad, Bikini Bottom  pstar@hotmail.com  1234567890
```

Interface for displaying customer information.

- `[B]` Goes to interface 6.

**Interface 8:**

```text
    Invoice list

    Press:
    [B] To go back to invoice options

    po        client   status    Description               Labour Hours
    --------  ------   --------  ------------------------  ------------
    12345678  Dave     complete  Installed new controller  2
```

This interface is used to show invoices to the user.

- `[B]` Goes to interface 5.


**Interface 9:**

```text
    Parts Options

    Press:
    [A] To add parts to an invoice
    [P] To add a new part
    [B] To go back to main menu
```

- `[A]` Shows prompt 3, stays at interface 9.
- `[P]` Shows prompt 7, stays at interface 9.
- `[B]` Goes to interface 2 if admin, 4 if technician

**Interface 10:**

```text
    List of parts used on po: 1234

    Press:
    [B] To return to parts options

    part_id  description      unit  used  cost   total
    -------  ---------------  ----  ----  -----  --------
    1234     1 PVC S40 TEE    ea    12    15.99  12*15.99
```

- `[B]` Goes to interface 9.

**Interface 11:**

```text
    Edit Employee details

      Name: Sam Erickson
      eid: 1234
      Status: Active
      Rate: 40.00

    Press:
    [S] To edit status
    [R] To edit rate
    [B] To go back to employee options
```

- `[S]` Goes to interface 12.
- `[R]` Goes to interface 11 after showing prompt 8.
- `[B]` Goes to interface 2.

**Interface 12**

```text
    Edit employee status:

    Current employee: Sam Erickson
    Current status: Active

    Press:
    [A] To set active
    [I] To set inactive
    [L] To set on leave
    [T] To set terminated
    [B] To go back to employee options
```

- `[A], [I], [L], [T]` Updates corresponding field and goes to interface 2.
- `[B]` Goes back to interface 2 and does not update record.

### Prompts Shown To The User

**Prompt 0**
In the event that a user enters invalid data, the user will be shown a prompt much like the following (minor differences to give the user information on why what they entered was invalid).

```text
    The value X you have entered is not valid.
    Press [A] to try again, or [B] to go back to the last menu.
```

**Prompt 1**

```text
    Enter employee id:
```

**Prompt 2**

```text
    Enter invoice po:
```

**Prompt 3**

```text
    Enter po:

    Enter customer number:

    Enter status:

    Enter description:
```

**prompt 4**

```text
    Enter customer number:
```

**Prompt 5**

```text
    Enter id:

    Enter first name:

    Enter last name:

    Enter email:

    Enter address:

    Enter phone-number:
```

**Prompt 6**

```text
    Enter part id:

    Enter quanitity:
```

**Prompt 7**

```text
    Enter part id:

    Enter part description:

    Enter part unit:

    Enter wholesale cost:

    Enter retail cost:
```

**Prompt 8**

```text
    Enter new rate:
```

## Database Design

This section outlines how the database is designed.

### Entities

The entities of this system are:

1. Parts
2. Customers
3. Invoices
4. Employees
5. ClockInOut (records of when an employee clocks in and out for the day)
6. Parts Used (records which parts were used in an invoice)
7. Jobs (Employees can have one or more jobs within the company)

### Attributes by Entity

1. Parts
    1. ID
    2. Description
    3. Unit (sold by each, linear foot, meter, etc.)
    4. Wholesale (how much it costs the company to buy)
    5. Retail (how much we charge customers for the part)
2. Customers
   1. ID
   2. First Name
   3. Last Name
   4. Email Address
   5. Address
   6. Phone Number
3. Invoices
   1. Purchase Order
   2. Status (scheduled|active|sent|completed)
   3. Date issued
   4. Date Work Started
   5. Date Work Completed
   6. Description (information on what was done)
4. Employees
   1. ID
   2. status (active|inactive|leave|terminated)
   3. First Name
   4. Last Name
   5. Hourly Rate
5. ClockInOut
   1. Clock in date and time
   2. Lunch start data and time
   3. Lunch end data and time
   4. Clock out date and time
6. Parts Used
   1. quantity
7. Jobs
   1. position (tecnician|admin)

### Entity Relationships

- Customers can have multiple invoices
- Invoices can have multiple partsUsed, multiple employees, and multiple
  ClockInOut's.
- Employees can have multiple ClockInOut's.
- PartsUsed is an aggregation between parts and invoices, where a part is in an invoice,
  and that relationship has an attribute quantity which is recorded in partUsed.
- ClockInOut Contains an invoice.
- An Employee can have multiple jobs within the company

### Relational Schema

The primary key is denoted by _primary-key-name_.

- Customers(_cid_, first_name, last_name, email, address, phone_number)
- Parts(_pid_, description, unit, wholesale, retail)
- Employees(_eid_, status, first_name, last_name, rate)
- ClockInOut(_clockIn_, startLunch, endLunch, clockOut, job, eid)
- Invoices(_po_ , status, issued, workStart, workEnd, description)
- PartsUsed(_pid_, _po_, quantity)
- Jobs(_eid_, _position_)

## Project Report

This section of the document was written after the first prototype of this project was created, which is the current state of the codebase.

### Hindsight

This section outlines all of the design choices I wish I made, and all of the things that I wish I had done differently.

#### Database Design

I should have created the database in a way that allows technicians to add notes to an invoice for the cases where additional work is completed once on site, or the customer changed their mind on what needed to be done.

#### Code Implementation

I chose to make a interface class to handle all of the interface related functions. I had very little plans in place for how to link the database queries with this class, and this lead me to simply implement the database queries into the class itself. If I were to do this project again, I would make the interface class make use of a query class that handles all of the query related functions, this would improve the maintainability and readability of the codebase.

I made use of a lot of utility functions that applied to most, but not all, cases for example the check selection function. Whenever this function did not suit the needs of a particular interface, I simple copied the code from the function and tweaked it to suit that functions needs. What I wish I would have done is overloaded the function each time I needed it to perform tasks in a slightly different way.

### Work to be completed

This section outlines all of the work that would be done, if the semester was longer, or if I kept working on the project.

#### Functionality that should be added

In order for this application to be functioning as intended the following functionalities need to be added:

**For All Users:**

1. Search for customers by name
2. Update the wholesale cost of a part
3. Add parts to the system
4. Ability to clock in and out, and take lunch

**For Office Administrators:**

1. Search for an employee by name
2. Check any employees clock in and out history
3. Add an employee to the system
4. Change an employee's status
5. Search for an employee by id

**For Technicians:**
1. Update invoice description
2. See their clock in and out history
3. See a list of all parts
4. Update the wholesale and retail values of a part
5. See all invoices within a date range

#### Software Architecture

- Some interface functions make use of the code that is in the `createInterface` function but slightly modified, these modifications should be implemented by use of overloading the `createInterface` function.
- The columns that display database info to the terminal do not line up well with the variable text length size. The system should check check the length of each string, and a designated column width variable, them add newline characters to make text that is longer than the the designated column width, or spaces if it is shorter.

