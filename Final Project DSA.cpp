#include <iostream>
#include <string.h>

using namespace std;

string arr[100];
int sized=0;

struct Day 
{
    int dayOfMonth;
    int month;
    string eventName;
    string eventDesc;
    Day* nextDay;
    bool hasEvent=0;
    
};

Day*head= NULL;

Day* createDay(int day, int month) 
{
    Day* newDay = new Day;
    newDay->dayOfMonth = day;
    newDay->month = month;
    newDay->eventName = "";
    newDay->eventDesc = "";
    newDay->nextDay = NULL;
    return newDay;
}


void addDay(int day, int month) 
{
    Day* newDay = createDay(day, month);
    if (head == NULL) 
	{
        head = newDay;
    } 
	else 
	{
        Day* temp = head;
        while (temp->nextDay != NULL) 
		{
            temp = temp->nextDay;
        }
        temp->nextDay = newDay;
    }
}

void displayCalendar(string monthName, int year, int startingDay) 
{
    string daysOfWeek[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    int dayCounter = 0;

    cout << "------------------------" << endl;
    cout << "|      Calendar        |" << endl;
    cout << "------------------------" << endl;
    cout << "     " << monthName << " " << year << endl;
    cout << " Mon   Tue   Wed   Thu   Fri   Sat  Sun" << endl;
    cout << "------------------------------------------" << endl;

    for (int i = 0; i < startingDay; ++i) 
	{
        cout << "      ";
        dayCounter++;
    }

    Day* temp = head;
    while (temp != NULL) 
	{
        if (dayCounter % 7 == 0) 
		{
            cout << endl;
        }
        cout << "  ";
        if (temp->dayOfMonth < 10) 
		{
            cout << " ";
        }
        cout << temp->dayOfMonth;
        if (temp->eventName!="") 
		{
            cout << " - " << temp->eventName << " ";
        }
        cout << "  ";
        temp = temp->nextDay;
        dayCounter++;
    }
    cout << endl << "---------------------------------------" << endl;
}

void clearCalendar() 
{
    while (head != NULL) 
	{
        Day* temp = head;
        head = head->nextDay;
        delete temp;
    }
}

int getDaysInMonth(int month, int year) 
{
    if (month == 2) 
	{
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
		{
            return 29; 
        } else 
		{
            return 28;
        }
    } 
	else if (month == 4 || month == 6 || month == 9 || month == 11) 
	{
        return 30;
    } 
	else 
	{
        return 31;
    }
}

string getMonthName(int month) 
{
    string monthNames[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    return monthNames[month - 1];
}

int zellersCongruence(int day, int month, int year) 
{
    if (month < 3) 
	{
        month += 12;
        year--;
    }

    int h = (day + ((13 * (month + 1)) / 5) + year + (year / 4) - (year / 100) + (year / 400)) % 7;
    return (h + 5) % 7;
}

void addEvent(int day,int month, string eventName, string eventDesc) 
{
    Day* temp = head;
    while (temp != NULL) 
	{
        if (temp->dayOfMonth == day && temp->month == month ) 
		{  string t=to_string(day)+" "+to_string(month);
		arr[sized]=t;
		sized++;
            temp->eventName = eventName;
            temp->eventDesc = eventDesc;
            
            temp->hasEvent=1;
            cout<<"Event added successfully"<<endl;
            break;
        }
        temp = temp->nextDay;
    }
}

void updateEvent(int day, string eventName, string eventDesc, int month) 
{
	string t=to_string(day)+" "+to_string(month);
	for(int i=0;i<sized;i++)
	{
    	if(t==arr[i])
		{
           Day* temp = head;
    
          while (temp != NULL) 
        	{
               if (temp->dayOfMonth == day) 
	        	{
                 temp->eventName = eventName;
                 temp->eventDesc = eventDesc;
                 temp->month = month;
                 cout<<temp->eventName ; cout << "Event updated successfully on " << day << "/" << getMonthName(temp->month) << "." << endl;
                break;
                }
              temp = temp->nextDay;
            }
          return; 
         }
     }
    
        cout << "No event exists on " << day << "/" << getMonthName(month) << ". Please add the event first." << endl;
   
}

void deleteEvent(int day, int month) 
{
    bool isfound=0;
    string t=to_string(day)+" "+to_string(month);
 for(int i=0;i<sized;i++)
 {
     if(arr[i]==t)
    {
         isfound=1;
     }
 }
 if(isfound==0)
 {
     cout<<"event dont exist"<<endl;
     return;
 }
    
    Day* temp = head;
    Day* prev = NULL;

    while (temp != NULL && (temp->dayOfMonth != day || temp->month != month)) 
	{
        prev = temp;
        temp = temp->nextDay;
    }

    if (prev == NULL) 
	{ 
        head = temp->nextDay;
    } 
	else 
	{
        prev->nextDay = temp->nextDay;
    }

    cout << "Event deleted successfully on " << day << "/" << getMonthName(month) << ".\n";
    delete temp;
}

void displayAllEvents() 
{
    Day* temp = head;
    bool eventsFound = false;

    while (temp != NULL) 
    {
        if (temp->hasEvent) 
        {
            if (!eventsFound) 
            {
                cout << "Events in Calendar:" << endl;
                eventsFound = true;
            }
            cout << "Date: " << temp->dayOfMonth << "/" << temp->month << endl;
            cout << "Event Name: " << temp->eventName << endl;
            cout << "Event Description: " << temp->eventDesc << endl;
            cout << "-----------------------" << endl;
        }
        temp = temp->nextDay;
    }

    if (!eventsFound) 
    {
        cout << "No events found in the Calendar." << endl;
    }
}


int main() 
{
    int year;
    int choice = -1; 

    cout << "Enter the year: ";
    cin >> year;

    Day* calendar = NULL;

    for (int month = 1; month <= 12; ++month) 
	{
        int daysInMonth = getDaysInMonth(month, year);
        int startingDay = zellersCongruence(1, month, year);
        
        for (int day = 1; day <= daysInMonth; ++day) 
		{
            addDay(day, month);
        }

        string monthName = getMonthName(month);
        displayCalendar( monthName, year, startingDay);

        clearCalendar();
    }

    int day, month;
    string eventName, eventDesc;
    

    while (choice != 0) 
	{ 
        cout << "\nChoose an option:\n";
        cout << "1. Add event\n";
        cout << "2. Update event\n";
        cout << "3. Display events\n";
        cout << "4. Delete event\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
		{
            case 1:
                cout << "Enter the day (1-31) and month (1-12) to add event: ";
                cin >> day >> month;
                if (month >= 1 && month <= 12 && day >= 1 && day <= 31) 
				{
                    cout << "Enter the event name: ";
                    cin.ignore();
                    getline(cin, eventName);

                    cout << "Enter the event description: ";
                    getline(cin, eventDesc);

                for (int day = 1; day <= getDaysInMonth(month, year); ++day) 
				{
                            addDay(day, month);
                }
                        addEvent(day, month, eventName, eventDesc);
                        
                        
                }
                break;
            case 2:
                cout << "Enter the day (1-31) and month (1-12) to update event: ";
                cin >> day >> month;
                if (month >= 1 && month <= 12 && day >= 1 && day <= 31) 
				{
                    cout << "Enter the updated event name: ";
                    cin.ignore();
                    getline(cin, eventName);

                    cout << "Enter the updated event description: ";
                    getline(cin, eventDesc);

                    
                        for (int day = 1; day <= getDaysInMonth(month, year); ++day) 
						{
                            addDay(day, month);
                        }
                        updateEvent(day, eventName, eventDesc, month);
                        break;
				}
				case 3:
				displayAllEvents();
				break;
            case 4:
                cout << "Enter the day (1-31) and month (1-12) to delete event: ";
                cin >> day >> month;
                for (int day = 1; day <= getDaysInMonth(month, year); ++day) 
				{
                    addDay(day, month);
                }
                deleteEvent(day, month);
        }
	}
}
