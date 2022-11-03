/* Title: dll-accounts.c
 * Abstract:
    extension from lab exercise, using a doubly linked list
    and adding new functions

 * Author: Joao Henares
 * Email: jpireshe@nd.edu
 * Estimate: 5h
 * Date: 09/18/2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// our node struct
typedef struct acc_dll {
    int dollar;
    int cent;
    char name[20];
    struct acc_dll* next_node;
    struct acc_dll* previous_node;
} acc_dll;


typedef struct acc_list {
    struct acc_dll* header;
    struct acc_dll* tail;
} acc_list;

// insert value and create node
void insert(acc_list*, int, int, char[]);

// frees everything
void freeall(acc_dll *);

// displays all nodes
void displayAll(acc_dll*);

// displays nth node
void displayNth(acc_list*, int);

// pushes stuff to front of list
void push_front(acc_list*, int, int, char []);

// put stuff in nth node
void appendNthPosition(acc_list*, int, int, int, char []);

// deletes tail
void delete_tail(acc_list*);

// delete head
void delete_head(acc_list*);

// delete nth record
void deleteNthNode(acc_list*, int);

// find record by name
void find(acc_list*, char [], int, int, int); 

// add money to found account
void addMoney(acc_list*, char personname [], int, int);

// average
void average(acc_list *);

// display amounts bigger
void displayAmountGreaterThan(acc_list*, int, int);

// find the max value
void findMax(acc_list *);

// find the min value
void findMin(acc_list *);

// check duplicates
void hasDuplicates(acc_list *);

// get n of records
void getNumberOfRecords(acc_list *);

// display even records
void displayEven(acc_list *);

int main() {
    // get file
    FILE *fp;
    char filename[20];
    fprintf(stdout, "Please input filename: ");
    fscanf(stdin, "%s", filename);
    fp = fopen(filename, "r");
    if(fp == NULL) {fprintf(stdout, "No such file.\n"); return 1;}

    // read amount of data in file
    int listsize;
    fscanf(fp, "%d", &listsize);

    // allocate list
    acc_list * thelist = (acc_list*)malloc(sizeof(acc_list));
    thelist->header = NULL;
    thelist->tail = NULL;

    // insert nodes in the list size times while reading data from file
    int dol, cent;
    char personname[20];

    for(int i = 0; i < listsize; i++) {
        fscanf(fp, "%s %d %d", personname, &dol, &cent);
        insert(thelist, dol, cent, personname);
    }

    // menu
    int userchoice = -1, usern, ddol;
    char choption, ucontinue = 'P';
    double dmoney, dcent;

    fprintf(stdout, "Options:\n1. Display all nodes\n2. Display nth record\n3. Append a new record - Head or Tail? (H/T)\n4. Append a new record in the Nth position\n5. Delete a record - Head or Tail? (H/T)\n6. Delete Nth record\n7. Find a record\n8. Add money to account\n9. Average all amounts \n10. Display the records of people with more than n.m (n=dollars, m=cents) in their account \n11. Find max amount \n12. Find min amount \n13. Check for duplicates \n14. Get number of records \n15. Display even numbered records \n");

    while(ucontinue != 'N') {
        ucontinue = 'P';
        fprintf(stdout, "Your choice: ");
        fscanf(stdin, "%d", &userchoice);

        // display all nodes
        if(userchoice == 1) {
            displayAll(thelist->header);
        }

        // display nth node
        else if(userchoice == 2) {
            fprintf(stdout, "Enter n: ");
            fscanf(stdin, "%d", &usern);
            // checking only when we actually have the nth node:
            if(usern <= listsize) {displayNth(thelist, usern);}
            else {fprintf(stdout, "That number is bigger than the number of elements I have!\n\n");}
        }

        // append a new record - head or tail
        else if(userchoice == 3) {
            // i do know we were to have a function named append, but c'mon. I did all of this in the lab
            // already. I would rather invest my efforts into creating new stuff.. I even changed the names of the
            // other functions..

            // this was because my fscanf was being jumped. a common c problem.
            getchar();
            // Get head or tail
            fprintf(stdout, "Enter H for head, T for tail: ");
            fscanf(stdin, "%c", &choption);
            // filter for stuff that is not H or T
            if(choption != 'H' && choption != 'T'){fprintf(stdout, "Invalid\n");}
            else {
                // increase list size (we are appending something)
                listsize++;
                
                // ask user for info
                fprintf(stdout, "Enter name: ");
                fscanf(stdin, "%s", personname);
                fprintf(stdout, "Enter amount: ");
                fscanf(stdin, "%lf", &dmoney);
                ddol = (int)dmoney;
                dcent = (dmoney - ddol)*100 + 0.1;
                // either push front or back
                if(choption == 'T') {insert(thelist, (int)dmoney, (int)dcent, personname);}
                else {push_front(thelist, (int)dmoney, (int)dcent, personname);}
                displayAll(thelist->header);
            }
        }

        // append a new record in the nth position
        else if(userchoice == 4) {
            // get position
            fprintf(stdout, "Enter n: ");
            fscanf(stdin, "%d", &usern);
            // if we can have such position
            if(usern <= listsize + 1) {
                // increase list size
                listsize++;
                // get user info
                fprintf(stdout, "Enter name: ");
                fscanf(stdin, "%s", personname);
                fprintf(stdout, "Enter amount: ");
                fscanf(stdin, "%lf", &dmoney);
                // insert stuff into nth node
                ddol = (int)dmoney;
                dcent = (dmoney - ddol)*100 + 0.1;
                appendNthPosition(thelist, usern, (int)dmoney, (int)dcent, personname);
                displayAll(thelist->header);
            }
            else {fprintf(stdout, "That number is bigger than the number of elements I have!\n\n");}
        }
        
        // delete head or tail
        else if(userchoice == 5) {
            getchar();
            fprintf(stdout, "Enter H for head, T for tail: ");
            fscanf(stdin, "%c", &choption);
            if(choption != 'H' && choption != 'T'){fprintf(stdout, "Invalid\n");}
            else {
                listsize--;
                
                if(choption == 'H') {delete_head(thelist);}
                else {delete_tail(thelist);}
                displayAll(thelist->header);
            }
        }

        // delete nth position
        else if(userchoice == 6) {
            fprintf(stdout, "Enter n: ");
            fscanf(stdin, "%d", &usern);
            if(usern <= listsize) {
                deleteNthNode(thelist, usern);
                displayAll(thelist->header);
            }
            else {fprintf(stdout, "That number is bigger than the number of elements I have!\n\n");}
        }

        // find a record
        else if(userchoice == 7) {
            // get user info
            fprintf(stdout, "Enter name: ");
            fscanf(stdin, "%s", personname);

            find(thelist, personname, 0, 0, 0);
        }

        // add money to a record
        else if(userchoice == 8) {
            // get user info
            fprintf(stdout, "Enter name: ");
            fscanf(stdin, "%s", personname);
            fprintf(stdout, "Enter amount: ");
            fscanf(stdin, "%lf", &dmoney);

            // divide money into dol and cent
            ddol = (int)dmoney;
            dcent = (dmoney - ddol)*100 + 0.1;

            addMoney(thelist, personname, (int)dmoney, (int)dcent);
        }
        
        // average
        else if(userchoice == 9) {
            average(thelist);
        }

        // display records of people with more than n.m in their account
        else if(userchoice == 10) {
            // get info
            fprintf(stdout, "Enter amount: ");
            fscanf(stdin, "%lf", &dmoney);

            // divide money into dol and cent
            ddol = (int)dmoney;
            dcent = (dmoney - ddol)*100 + 0.1;

            displayAmountGreaterThan(thelist, ddol, dcent);
        }

        else if(userchoice == 11) {findMax(thelist);}
        else if(userchoice == 12) {findMin(thelist);}
        else if(userchoice == 13) {hasDuplicates(thelist);}
        else if(userchoice == 14) {getNumberOfRecords(thelist);}
        else if(userchoice == 15) {displayEven(thelist);}

        // invalid outputs
        else{fprintf(stdout, "This is not a valid choice!\n");}

        while(ucontinue != 'Y' && ucontinue != 'N') {
            fprintf(stdout, "Continue? (Y/N): ");
            getchar();
            fscanf(stdin, "%c", &ucontinue);
        }
    }

    freeall(thelist->header);
    free(thelist);
    fclose(fp);

    return 0;
}

void getNumberOfRecords(acc_list * thelist) {
    int n = 0;
    acc_dll * curr = thelist->header;
    // iterate and add 1 to n to get num of records
    while(curr != NULL) {
        n += 1;
        curr = curr->next_node;
    }
    // print n 
    fprintf(stdout, "Number of records: %d\n", n);
}

void displayEven(acc_list * thelist) {
    fprintf(stdout, "Displaying even records\n");
    int n = 1;
    acc_dll * curr = thelist->header;
    // iterate and add 1 to n to get num of records
    while(curr != NULL) {
        if(n % 2 == 0) {
            fprintf(stdout, "   %s %d %d\n", curr->name, curr->dollar, curr->cent);
        }
        n += 1;
        curr = curr->next_node;
    }
}


void hasDuplicates(acc_list * thelist) {
    acc_dll* i,* j;
    i = thelist->header;
    fprintf(stdout, "Showing duplicates: \n");
    // iterate list (until last element, not until null)
    while(i->next_node != NULL) {
        j = i->next_node;
        // iterate what is in front of the i element of the list
        while(j != NULL) {
            // check for match, print
            if(strcasecmp(i->name, j->name) ==0) {
                fprintf(stdout, "   %s %d %d\n", i->name, i->dollar, i->cent);
                fprintf(stdout, "   %s %d %d\n", j->name, j->dollar, j->cent);
                fprintf(stdout, "\n");
            }
            j = j->next_node;
        }
        i = i->next_node;
    }
}

void findMax(acc_list * thelist) {
    fprintf(stdout, "Displaying people with max amount: \n");
    acc_dll * curr = thelist->header;
    int dol = curr->dollar, cent = curr->cent;
    // get max using method similar to display amount greater than..
    while(curr != NULL) {
        if(curr->dollar > dol || (curr->dollar == dol && curr->cent > cent)) {
            dol = curr->dollar;
            cent = curr->cent;
        }
        curr = curr->next_node;
    }

    // iterate list and print those with target amount
    curr = thelist->header;
    while(curr != NULL) {
        if(curr->dollar == dol && curr->cent == cent) {
            fprintf(stdout, "   %s %d %d\n", curr->name, curr->dollar, curr->cent);
        }
        curr = curr->next_node;
    }
    fprintf(stdout, "\n");
}

void findMin(acc_list * thelist) {
    fprintf(stdout, "Displaying people with min amount: \n");
    acc_dll * curr = thelist->header;
    int dol = curr->dollar, cent = curr->cent;
    // get max using method similar to display amount greater than..
    while(curr != NULL) {
        if(curr->dollar < dol || (curr->dollar == dol && curr->cent < cent)) {
            dol = curr->dollar;
            cent = curr->cent;
        }
        curr = curr->next_node;
    }

    // iterate list and print those with target amount
    curr = thelist->header;
    while(curr != NULL) {
        if(curr->dollar == dol && curr->cent == cent) {
            fprintf(stdout, "   %s %d %d\n", curr->name, curr->dollar, curr->cent);
        }
        curr = curr->next_node;
    }
    fprintf(stdout, "\n");
}

void displayAmountGreaterThan(acc_list * thelist, int ddol, int dcent) {
    fprintf(stdout, "Displaying accounts with more than %d.%d\n", ddol, dcent);
    // iterate list
    acc_dll* curr = thelist->header;
    while(curr != NULL) {
        // if dollar current > target dollar or dollar is the same and curr cent is bigger than target center, print
        if(curr->dollar > ddol || (curr->dollar == ddol && curr->cent > dcent)) {
            fprintf(stdout, "   %s %d %d\n", curr->name, curr->dollar, curr->cent);
        }
        curr = curr->next_node;
    }
}

void insert(acc_list* thelist, int dol, int cent, char personname[]) { // that can also be push_back
    // we allocate the node we will insert
    acc_dll* insert_node = (acc_dll *) malloc(sizeof(acc_dll));
    // put data inside it
    insert_node->dollar = dol;
    insert_node->cent = cent;
    strcpy(insert_node->name, personname);
    insert_node->previous_node = NULL;
    insert_node->next_node = NULL;

    // check for null list
    if (thelist->header == NULL) {
        thelist->header = insert_node;
        thelist->tail = insert_node;
        return;
    }
    
    // otherwise add to list
    acc_dll* ref = thelist->tail;
    thelist->tail = insert_node;
    
    thelist->tail->previous_node = ref;
    ref->next_node = thelist->tail; 
 
    return;
}

void displayAll(acc_dll* header) {
    fprintf(stdout, "Displaying all records:\n");
    acc_dll* curr = header;
    // here we go to the end (we could do next node != null then final action but that is not necessary)
    while(curr != NULL) {
        fprintf(stdout, "   %s %d %d\n", curr->name, curr->dollar, curr->cent);
        curr = curr->next_node;
    }
    printf("\n");
}

void displayNth(acc_list* thelist, int usern) {
    acc_dll* curr = thelist->header;
    // go to nth node
    for(int i = 0; i < usern - 1; i++) {
        curr = curr->next_node;
    }
    // display it
    fprintf(stdout, "Displaying record %d:\n    %s %d %d\n\n", usern, curr->name, curr->dollar, curr->cent);
}

void push_front(acc_list* thelist, int dol, int cent, char personname[]) {
    // we allocate the node we will insert
    acc_dll* insert_node = (acc_dll *) malloc(sizeof(acc_dll));
    // put data inside it
    insert_node->dollar = dol;
    insert_node->cent = cent;
    insert_node->next_node = NULL;
    insert_node->previous_node = NULL;
    strcpy(insert_node->name, personname);

    // check for null list
    if (thelist->header == NULL) {
        thelist->header = insert_node;
        thelist->tail = insert_node;
        return;
    }
    // else: create pointer to know where you are
    acc_dll* curr_ptr = thelist->header;

    // change header to insert node
    thelist->header = insert_node;
    thelist->header->next_node = curr_ptr;
    
    curr_ptr->previous_node = thelist->header;

    return;
}

void appendNthPosition(acc_list* thelist, int usern, int dol, int cent, char personname[]) {
    // we allocate the node we will insert
    acc_dll* insert_node = (acc_dll *) malloc(sizeof(acc_dll));
    // put data inside it
    insert_node->dollar = dol;
    insert_node->cent = cent;
    strcpy(insert_node->name, personname);
    insert_node->next_node = NULL;
    insert_node->previous_node = NULL;

    // check for null list
    if (thelist->header == NULL) {
        thelist->header = insert_node;
        thelist->tail = insert_node;
        return;
    }

    // go to 1 before nth node
    acc_dll* curr = thelist->header;
    for(int i = 0; i < usern - 2; i++) {
        curr = curr->next_node;
    }
    // to not lose  this nth current node
    // temp: the next node of curr (1 after the one we insert) (do not change temp next)
    // curr: the node before the one we insert ( do not change curr previsous )

    // change curr's next to insert node
    // first store curr's past next node
    acc_dll* temp = curr->next_node;
    insert_node->previous_node = curr; 
    curr->next_node = insert_node; 

    // checking for the last position
    if(temp != NULL) {
        // make insert node next to be temp
        insert_node->next_node = temp;
        // change temp previous
        temp->previous_node = insert_node;
    }
}

void delete_head(acc_list* thelist) {
    acc_dll* curr = thelist->header;
    thelist->header = curr->next_node;
    // take previous node out from new header
    thelist->header->previous_node = NULL;
    // free
    free(curr);
}

void delete_tail(acc_list* thelist) {
    // go to tail (sll method, still works for dll)
    acc_dll* curr = thelist->header;
    acc_dll* temp = curr;
    while(curr->next_node != NULL) {temp = curr; curr = curr->next_node;}
    // make node before tail have no next one
    temp->next_node = NULL;
    // make tail this said node
    thelist->tail = temp;
    // free old tail
    free(curr);
}

void find(acc_list* thelist, char personname[], int addm, int dol, int cent) {
    if (addm == 0) {fprintf(stdout, "Displaying records with name %s:\n", personname);}
    // iterate string:
    acc_dll *curr = thelist->header;
    int found = 0; // to flag if we find something
    while(curr != NULL) {
        if(strcasecmp(curr->name, personname) == 0) { // if we match the names (case insensitive)
            // print info and flag as found
            if(addm == 0) {
            fprintf(stdout, "   %s %d %d\n", curr->name, curr->dollar, curr->cent);
            }
            else { // addmoney mode: i used that in addMoney()
                curr->dollar += dol;
                curr->cent += cent;
                if(curr->cent >= 100) {curr->dollar += 1; curr->cent -= 100;}
            }
            found = 1;
        }
        curr = curr->next_node;
    }

    // in case we did not find anything:
    if(found == 0){fprintf(stdout, "Did not find any records.\n\n");}
    if(addm == 0 && found == 1) {fprintf(stdout, "\n");}
}

void addMoney(acc_list* thelist, char personname [], int dol, int cent) {
    find(thelist, personname, 1, dol, cent);
    displayAll(thelist->header);
}

void deleteNthNode(acc_list* thelist, int usern){
    if(usern != 1) { // if we are not taking out the 1st node
        acc_dll* curr = thelist->header;
        acc_dll* temp = curr;
        // go to nth node
        for(int i = 0; i < usern - 1; i++) {
            temp = curr;
            curr = curr->next_node;
        }
        if(curr->next_node != NULL) {
        // delete it (do not change temp previous or next next)
        temp->next_node = curr->next_node;
        temp->next_node->previous_node = temp;
        free(curr);
        }
        else {delete_tail(thelist);}
    }
    else {delete_head(thelist);}
}

void average(acc_list* thelist) {
    acc_dll* curr = thelist->header;
    double total = 0, n = 0;
    while(curr != NULL) {
        total += (curr->dollar + 0.01 * curr->cent);  

        curr = curr->next_node;
        n += 1;
    }
    fprintf(stdout, "Average of all accounts: %.2lf\n\n", total/n);
}

void freeall(acc_dll * header) {
    acc_dll * temp;
    while(header != NULL) {
        temp = header;
        header = header->next_node;
        free(temp);
    }
}