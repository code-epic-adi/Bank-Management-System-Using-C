#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include<math.h>
#include <time.h>
#include<unistd.h>

//Defining Structure of customer
typedef struct{
    long long int AC_Number;
    char name[100];
    char dob[12];
    long long int mob;
    char email[100];
    char address[1000];
    int safeno;
    char passwd[100];
    long long int debitCardNumber;
}customer;

int Number_of_customers;
customer AC_Details[1000];

//Defining Structure for loan Customers
typedef struct{
    long long int loan_ac;
    char type[100];
    int Open_year;
    int year;
    float amount;
    float interest;
}loan;


//Functions prototype Used in the code
int Indexing(int x);
int isDigit(char ch);
void txtAdder(char ac[]);
int countDigits(int number);
int validPasswd(const char *password);
long long generateRandomNumber(long long min, long long max);
long long generateAccountNumber();
long long generateDebitCardNumber();
int generateCVV();
void customers_details(customer *AC_Details);
void AC_Open();
void resetPassword(long long int ac);
int verifyPassword(const char *name, const char *password, long long int ac);
float Withdrawal(int n) ;
void Deposit();
void Apply_Debit();
void change_pin(char *ac);
void useDebit();
void see_tansaction_history(char *ac);
long long generate_loan_account_number();
void openloanaccount();
double remaining_balance(double principal, double annual_interest_rate, int years);
void makeLoanPayment(long long int loan_ac);

void printUserDetails(){
    Number_of_customers=Indexing(0);
    //for(int i=)
}

//Main Function
int main(){

    //Welocome Message
    char *welcome = "Welcome to Golden Horizon Bank";
    int length = 35; // Length of the welcome message
    int delay_ms = 50; // Delay in milliseconds for printing the text
    int star_delay_ms = 20; // Delay in milliseconds for printing stars
    printf("\t\t");
    // Print top stars
    for (int i = 0; i < 45; i++) {
        printf("*");
        fflush(stdout); // Flush output buffer to ensure immediate printing
        clock_t start_time = clock(); // Get the current time
        while ((clock() - start_time) * 1000.0 / CLOCKS_PER_SEC < star_delay_ms) {}
    }
    // Print leading spaces and "Welcome to Golden Horizon Bank" with delay
    printf("\n\t\t\t");
    for (int i = 0; i < length; i++) {
        printf("%c", welcome[i]);
        fflush(stdout); // Flush output buffer to ensure immediate printing
        clock_t start_time = clock(); // Get the current time
        while ((clock() - start_time) * 1000.0 / CLOCKS_PER_SEC < delay_ms) {}
    }
    printf("\t\t");

    // Print bottom stars with shorter delay
    for (int i = 0; i < 45; i++) {
        printf("*");
        fflush(stdout); // Flush output buffer to ensure immediate printing
        clock_t start_time = clock(); // Get the current time
        while ((clock() - start_time) * 1000.0 / CLOCKS_PER_SEC < star_delay_ms) {}
    }
    printf("\n");
    customers_details(AC_Details);
    Number_of_customers=Indexing(0);
    long long int ac;
    long long int Debit_Card_Number;
    char AcFile[19];
    //Bank will never close (24x7 service provide)

    
    while(1){
        char input[100];
        int key;
      // What our Bank can do
        printf("\n\tWelcome to Our Bank!!\n\n");
        sleep(1);
        printf("Press The Indicated keys to proceed futher:-\n");
        printf("1- For Account Opening\n");
        printf("2- For Money Deposit\n");
        printf("3- For Money Withdrawl\n");
        printf("4- For Reset Password\n");
        printf("5- Apply for Debit Card\n");
        printf("6- Change Debit Card Pin\n");
        printf("7- For using Debit Card\n");
        printf("8- For see Transaction History\n");
        printf("9- For Opening Loan Account\n");
        printf("10- For Pay Loan\n");
        printf("11- For Exit\n\n");
        printf("Enter your choice here: ");

    // To get the value of key
        // Read input as a string using fgets
        fgets(input, sizeof(input), stdin);
        // Convert the string to an integer using sscanf
        if (sscanf(input, "%d", &key) != 1) {
            printf("Invalid input. Please enter a valid integer.\n");
            return 1;
        }
        // Use getchar to consume the newline character
        getchar();

        //Bank serives
        switch(key){
            case 1: AC_Open();
                    break;

            case 2: Deposit();
                    break;

            case 3: if (!Withdrawal(0)){
                    int choice;
                    printf("\nDetails incorrect.\n");
                    printf("1. Retry\n");
                    printf("2. Reset Password\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    switch (choice)
                    {
                    case 1:
                        printf("\nPlease retry with correct details.\n");
                        getchar();
                        Withdrawal(0);
                        break;
                    case 2:
                        resetPassword(ac);
                        break;
                    default:
                        printf("Invalid choice.\n");
                        break;
                    }
                }
                break;

            case 4:
                printf("Enter the Account Number: ");
                scanf("%lld", &ac);
                resetPassword(ac);
                break;
            
            case 5:
                Apply_Debit();
                break;

            case 6: 
                printf("Enter the Account Number: ");
                scanf("%lld",&ac);
                printf("Enter Debit Card Number: ");
                scanf("%lld", &Debit_Card_Number);
                for(int i=0; i<Number_of_customers; i++){
                    if(AC_Details[i].AC_Number==ac && AC_Details[i].debitCardNumber==Debit_Card_Number){
                        printf("User Verified Successfully\n");
                        sprintf(AcFile, "%lld", ac);
                        txtAdder(AcFile);
                        change_pin(AcFile);
                        break;
                    }
                }
                printf("Enter Wrong Details. Try Again.\n");
                break;

            case 7:
                useDebit();
                break;

            case 8: printf("Enter Your Account number: ");
                    scanf("%lld", &ac);
                    int found=0;
                    for(int i=0; i<Number_of_customers; i++){
                        if(AC_Details[i].AC_Number==ac){
                            found=1;
                        }
                    }
                    if(!found){
                        printf("Wrong Account Number.\n");
                        break;
                    }
                    
                    sprintf(AcFile, "%lld", ac);
                    txtAdder(AcFile);
                    see_tansaction_history(AcFile);
                    break;

            case 9: openloanaccount();
                    break;
            
            case 10: printf("Enter Your Loan Account number: ");
                    long long int loan_ac;
                    scanf("%lld", &loan_ac);
                    makeLoanPayment(loan_ac);
                    break;

            case 11:
                printf("\nThanks for using our services.");
                return 0;

        }
        getchar();
    }
}


//Functions Used in the code



int isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

void txtAdder(char ac[]){
    ac[14]='.', ac[15]='t', ac[16]='x', ac[17]='t', ac[18]='\0';
}

int countDigits(int number) {
    int count = 0;
    // Handle negative numbers
    if (number < 0) {
        number = -number;
    }
    // Count digits
    do {
        count++;
        number /= 10;
    } while (number != 0);
    return count;
}

//To Find number of customers till now
int Indexing(int x) {
    int value = -1; // Initialize value to -1 to indicate failure
    FILE *fptr;

    fptr = fopen("Bank Customer Details.txt", "r+");
    if (fptr == NULL) {
        perror("Error opening file");
        return -1; // Return -1 to indicate failure
    }

    char line[500];
    while (fgets(line, sizeof(line), fptr) != NULL) {
        char *token = strtok(line, "=");
        if (token != NULL && strcmp(token, "Number_of_customers") == 0) {
            token = strtok(NULL, "="); // Get the value after '='
            if (token != NULL) {
                value = atoi(token); // Convert string to integer
                if(x==1){
                    value++;
                } // Increment the value by 1

                // Rewind to the beginning of the line and update the value in the file
                fseek(fptr, -(strlen(token)+1), SEEK_CUR);
                fprintf(fptr, "%d", value);
                break; // Exit loop after updating the value
            }
        }
    }
    fclose(fptr);
    return value; // Return the incremented value
}


//Checking For Valid Password
int validPasswd(const char *password) {
    char passwrd[100];
    strcpy(passwrd, password);
    passwrd[strcspn(passwrd, "\n")] = '\0';
    int length = strlen(passwrd);
    int hasSpecialChar = 0;

    // Check password length
    if (length < 8) {
        return 0; // Password length less than 8
    }

    // Check for special characters
    for (int i = 0; i < length; i++) {
        if (!(isalnum(passwrd[i]))) {
            hasSpecialChar = 1;
            break;
        }
    }

    return hasSpecialChar; // Return 1 if there's a special character, 0 otherwise
}


// Function to generate a random number within a specified range
long long generateRandomNumber(long long min, long long max) {
    return min + rand() % (max - min + 1);
}

// Function to generate a unique bank account number
long long generateAccountNumber() {
    long long prefix = 1000; // Example prefix
    long long randomNumber = generateRandomNumber(1000000000, 9999999999); // Generate a 10-digit random number
    return prefix * 10000000000L + randomNumber; // Combine prefix and random number
}

// Function to generate a unique debit card number
long long generateDebitCardNumber() {
    // Assuming a 16-digit debit card number (standard)
    long long prefix = 400000; // Prefix for Visa cards
    long long randomNumber = generateRandomNumber(100000000, 999999999); // Generate a 9-digit random number
    return prefix * 1000000000LL + randomNumber; // Combine prefix and random number
}

// Function to generate a random CVV number (3-digit)
int generateCVV() {
    return generateRandomNumber(100, 999);
}

// Making Array of customers of type structure which use to load data of exisiting customers into the array
void customers_details(customer *AC_Details){
    FILE *ptr;
    char line[1000];
    int Number_of_customers = 0; // Initialize the count of customers

    // Open the file for reading
    ptr = fopen("Bank Customer Details.txt", "r");
    if (ptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Read each line from the file
    while (fgets(line, sizeof(line), ptr)) {
        if (strstr(line, "A/C Number:")) {
            // Found a customer entry
            sscanf(line, "A/C Number: %lld", &AC_Details[Number_of_customers].AC_Number);
            fgets(line, sizeof(line), ptr); // Read the next line (Customer Name)
            sscanf(line, "Customer Name: %[^\n]", AC_Details[Number_of_customers].name);
            fgets(line, sizeof(line), ptr); // Read the next line (Date of Birth)
            sscanf(line, "Date of Birth: %[^\n]", AC_Details[Number_of_customers].dob);
            fgets(line, sizeof(line), ptr); // Read the next line (Mobile Number)
            sscanf(line, "Mobile Number: %lld", &AC_Details[Number_of_customers].mob);
            fgets(line, sizeof(line), ptr); // Read the next line (Email)
            sscanf(line, "Email: %[^\n]", AC_Details[Number_of_customers].email);
            fgets(line, sizeof(line), ptr); // Read the next line (Address)
            sscanf(line, "Address: %[^\n]", AC_Details[Number_of_customers].address);
            fgets(line, sizeof(line), ptr); // Read the next line (Safe Number)
            sscanf(line, "Safe Number: %d", &AC_Details[Number_of_customers].safeno);
            fgets(line, sizeof(line), ptr); // Read the next line (Address)
            sscanf(line, "Password: %[^\n]", AC_Details[Number_of_customers].passwd);
            fgets(line, sizeof(line), ptr); // Read the next line Debit Card Number
            if(strstr(line,"Debit Card Number:")){
                sscanf(line, "Debit Card Number: %lld", &AC_Details[Number_of_customers].debitCardNumber);
            }
            else{
                AC_Details[Number_of_customers].debitCardNumber=0;
            }
            Number_of_customers++; // Increment the customer count
        }
    }

    // Close the file
    fclose(ptr);
}

//Account Opening
void AC_Open(){

    FILE *fptr;
    char successfully_enter;

    customer A;
    printf("Enter your details here\n\n");
    printf("Enter Name: ");
    fgets(A.name, 100, stdin);
    printf("Enter your Date of Birth(dd/mm/yyyy): ");
    fgets(A.dob, 11, stdin);
    getchar();
    printf("Enter Mobile Number: ");
    scanf("%lld", &A.mob);
    getchar();
    printf("Enter Email Address: ");
    fgets(A.email, 100, stdin);
    printf("Enter Residential Address: ");
    fgets(A.address, 1000, stdin);
    printf("Safe Number: ");
    scanf("%d", &A.safeno);
    printf("Password: ");
    scanf("%s", A.passwd);
    while(!validPasswd(A.passwd)){
        printf("\n Enter valid Password.\n ");
        printf("Password must have atleast 8 characters and one special character.\n\n");
        printf("Enter password: ");
        scanf("%s",A.passwd);
    }
    getchar();


    printf("\nIs Successfully enter the details(y/n): ");
    scanf("%c", &successfully_enter);

    if(successfully_enter=='y' || successfully_enter=='Y'){
        customers_details(AC_Details);
        srand(time(NULL)); // Seed the random number generator
        long long accountNumber = generateAccountNumber();

        fptr=fopen("Bank Customer Details.txt", "a");
        Number_of_customers=Indexing(1);
        fprintf(fptr, "\n\n%d. \n", Number_of_customers);
        fprintf(fptr, "A/C Number: %lld\n",accountNumber);
        fprintf(fptr, "Customer Name: %s", A.name);
        fprintf(fptr, "Date of Birth: %s\n", A.dob);
        fprintf(fptr, "Mobile Number: %lld\n", A.mob);
        fprintf(fptr, "Email: %s", A.email);
        fprintf(fptr, "Address: %s", A.address);
        fprintf(fptr, "Safe Number: %d\n",A.safeno);
        fprintf(fptr, "Password: %s",A.passwd);
        fclose(fptr);
        getchar();
        printf("\nYour Account Number is: %lld\n\n",accountNumber);

        //Witre details of new customer into the array of customers
        Number_of_customers--;
        AC_Details[Number_of_customers].AC_Number=accountNumber;
        strcpy(AC_Details[Number_of_customers].name,A.name);
        strcpy(AC_Details[Number_of_customers].dob,A.dob);
        AC_Details[Number_of_customers].mob=A.mob;
        strcpy(AC_Details[Number_of_customers].email,A.email);
        strcpy(AC_Details[Number_of_customers].address,A.address);
        AC_Details[Number_of_customers].safeno=A.safeno;
        strcpy(AC_Details[Number_of_customers].passwd, A.passwd);
        Number_of_customers++;

        // Making the file of the newly added customer Customer
        FILE *fptr;
        char ac[19];
        sprintf(ac, "%lld", accountNumber);
        txtAdder(ac);
        fptr=fptr=fopen(ac, "w");
        fprintf(fptr, "Customer Name: %s", A.name);
        fprintf(fptr, "Date of Birth: %s\n", A.dob);
        fprintf(fptr, "Mobile Number: %lld\n", A.mob);
        fprintf(fptr, "Email: %s", A.email);
        fprintf(fptr, "Address: %s", A.address);
        fprintf(fptr, "Total Balance: 0\n");
        fprintf(fptr, "\nTransaction History:-\n");
        fclose(fptr);
        return;

    }
    else if(successfully_enter=='n' || successfully_enter=='N'){
        AC_Open();
    }

}

//User Verification
void resetPassword(long long int ac) {
    Number_of_customers=Indexing(0);
    int safeno;
    char newPasswd[100];

    // Ask for safeno
    printf("Enter your safe number: ");
    scanf("%d", &safeno);

    // Search for the customer with the given name and safeno
    for (int i = 0; i < Number_of_customers; i++) {
        if (AC_Details[i].safeno == safeno && AC_Details[i].AC_Number==ac) {
            // If found, ask for new password
            printf("User Verified Successfully.\n\n");

            printf("Enter your new password: ");
            scanf("%s", newPasswd);
            while(!validPasswd(newPasswd)){
                printf("\n Enter valid Password.\n ");
                printf("Password must have atleast 8 characters and one special character.\n\n");
                printf("Enter password: ");
                scanf("%s",newPasswd);
            }
            // Update the password
            strcpy(AC_Details[i].passwd, newPasswd);
            FILE *fptr=fopen("Bank Customer Details.txt", "r");
            FILE *fptr_temp=fopen("temp.txt", "w");
            if (fptr == NULL || fptr_temp == NULL) {
                printf("Error opening file.\n");
                return;
            }
            char search_ac[100];
            sprintf(search_ac,"A/C Number: %lld",ac);
            char line[500];
            char oldPasswd[100];
            while (fgets(line, sizeof(line), fptr) != NULL) {
                if (strstr(line, search_ac)) {
                    fputs(line, fptr_temp);
                    while(fgets(line, sizeof(line), fptr) != NULL){
                        if(strstr(line, "Password:")){
                            sscanf(line, "Password: %s", oldPasswd);
                            oldPasswd[strcspn(oldPasswd, "\n")] = '\0';
                            fprintf(fptr_temp, "Password: %s\n", newPasswd);
                        } else {
                            fputs(line, fptr_temp);
                        }
                    }
                } else {
                    fputs(line, fptr_temp);
                }
            }
            fclose(fptr);
            fclose(fptr_temp);
            remove("Bank Customer Details.txt");
            rename("temp.txt", "Bank Customer Details.txt");

            printf("Password reset successfully.\n");
            return;
        }
    }
    // If not found, print a message
    printf("Safe number does not match.\n");
}

int verifyPassword(const char *name, const char *password, long long int ac) {
    Number_of_customers=Indexing(0);
    for (int i = 0; i < Number_of_customers; i++) {
        AC_Details[i].name[strcspn(AC_Details[i].name, "\n")] = '\0';
        if (strcmp(AC_Details[i].name, name)==0 && strcmp(AC_Details[i].passwd, password) == 0 && AC_Details[i].AC_Number==ac) {
            return 1; // Password verified
        }
    }
    return 0; // Password not verified
}

//Withdrawal
float Withdrawal(int n) {
    char name[100];
    char password[100];
    long long int ac;

    printf("    Verify User   \n");
    printf("Enter your Name: ");
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Enter The Account Number: ");
    scanf("%lld",&ac);
    printf("Enter your password: ");
    scanf("%s", password);
                
    // Verify password
    if (verifyPassword(name,password, ac)) {
        printf("User verified.\n\n");

        //Withdrawal Process
        FILE *fptr;
        char AcFile[19];
        sprintf(AcFile, "%lld", ac);
        txtAdder(AcFile);
        fptr=fopen(AcFile, "r+");
        FILE *fptr_temp=fopen("temp1.txt", "w");
        if (fptr == NULL || fptr_temp == NULL) {
            printf("Error opening file.\n");
            return 0;
        }
        printf("Enter the amount to be withdrawal: ");
        float amt;
        scanf("%f",&amt);    
        char line[500];
        float value;
        while (fgets(line, sizeof(line), fptr) != NULL) {
            if (strstr(line, "Total Balance:")) {
                sscanf(line, "Total Balance: %f", &value);
                
                if(amt>value){
                    printf("Insufficient Balance.\n");
                    fclose(fptr_temp);
                    fclose(fptr);
                    remove("temp1.txt");
                    return 1;
                }
                else{
                    value-=amt;
                }
                fprintf(fptr_temp,"Total Balance: %f\n",value);
            }
            else {
                fputs(line, fptr_temp);
            }
        }

        time_t current_time;
        time(&current_time);

        // Convert to local time
        struct tm *local_time = localtime(&current_time);
        // Display current date and time
        char time[100];
        strcpy(time,asctime(local_time));
        time[strcspn(time, "\n")]='\0';

        if(n==0){
            fprintf(fptr_temp, "\n\nOn %s, Amount of Rs. %.2f is Debited by online bank service, Available Balance is: %.2f", time, amt, value);
        }
        else if(n==1){
            fprintf(fptr_temp, "\n\nOn %s Amount of Rs.%.2f is credited by loan, Available Balance is: %.2f", time, amt, value);
        }
        
        fclose(fptr);
        fclose(fptr_temp);
        remove(AcFile);
        rename("temp1.txt", AcFile);
        printf("Amount Withdrawal Successfully.\n");
        printf("Available Balance: %f\n\n",value);
        return amt;
    }
     else {
        getchar();
        return 0;
    }

}

// Deposit 
void Deposit(){
    Number_of_customers=Indexing(0);
    printf("Enter the Account number: ");
    long long int ac;
    scanf("%lld",&ac);
    int found=-1;
    for(int i=0; i<Number_of_customers; i++){
        if(AC_Details[i].AC_Number==ac){
            found=1;
            printf("Enter the amount to be deposited: ");
            long int amt;
            scanf("%ld",&amt);
            FILE *fptr;
            char AcFile[19];
            sprintf(AcFile, "%lld", ac);
            txtAdder(AcFile);
            fptr=fopen(AcFile, "r+");
            FILE *fptr_temp=fopen("temp.txt", "w");
            if (fptr == NULL || fptr_temp == NULL) {
                printf("Error opening file.\n");
                return;
            }
            
            char line[500];
            
            int value=0;
            while (fgets(line, sizeof(line), fptr) != NULL) {
                if (strstr(line, "Total Balance:")) {
                    fputs(line, fptr_temp);
                    sscanf(line, "Total Balance: %ld", &value);
                    value+=amt;
                    fseek(fptr_temp, -(strlen(line)+1), SEEK_CUR);
                    fprintf(fptr_temp,"Total Balance: %ld\n",value);
                }
                else {
                    fputs(line, fptr_temp);
                }
            }
            time_t current_time;
            time(&current_time);

            // Convert to local time
            struct tm *local_time = localtime(&current_time);
            // Display current date and time
            char time[100];
            strcpy(time,asctime(local_time));
            time[strcspn(time, "\n")]='\0';

            fprintf(fptr_temp, "\n\nOn %s, Amount of Rs. %ld is Credited by online bank service, Available Balance is: %ld", time, amt, value);
            fclose(fptr);
            fclose(fptr_temp);
            remove(AcFile);
            rename("temp.txt", AcFile);
            break;
        }
        else{found=0;}
    }

    if(found==1){
        printf("Money Deposited Successfully.");
    }
    else if(found==0){
        printf("Enter the correct account number.");
    }
    printf("\n\n");
    getchar();

}

//Apply for Debit Card
void Apply_Debit(){
    long long int ac;
    printf("Enter your Account Number: ");
    scanf("%lld", &ac);

    char passwd[100];
    int safeNo;
    printf("Enter the Password: ");
    scanf("%s",passwd);
    passwd[strcspn(passwd, "\n")] = '\0';
    printf("Enter the Safe Number: ");
    scanf("%d",&safeNo);
    Number_of_customers=Indexing(0);
    int found=-1;
    for(int i=0; i<Number_of_customers; i++){
        if(AC_Details[i].AC_Number==ac && strcmp(AC_Details[i].passwd, passwd)==0 && AC_Details[i].safeno==safeNo){
            found=1;
            FILE *fptr;
            char AcFile[19];
            sprintf(AcFile, "%lld", ac);
            txtAdder(AcFile);
            fptr=fopen(AcFile, "r+");
            
            char line[1000];
            while (fgets(line, sizeof(line), fptr)) {
                if (strstr(line, "Debit card details")) {
                    printf("\nYou Already have the Debit Card.\n");
                    printf("%s",line);
                    fgets(line, sizeof(line), fptr);
                    printf("%s",line);
                    fgets(line, sizeof(line), fptr);
                    fgets(line, sizeof(line), fptr);
                    printf("%s",line);
                    getchar();
                    return;
                }
            }
            // Seed the random number generator
            srand(time(NULL));

            // Generate a unique debit card number
            long long debitCardNumber = generateDebitCardNumber();

            // Generate a CVV number
            int cvv = generateCVV();

            //Extracting current time
            time_t current_time;
            time(&current_time);
            // Convert to local time
            struct tm *local_time = localtime(&current_time);
            int exp_year = local_time->tm_year + 1900+5;
            int pin;
            printf("Enter the pin of Debit Card: ");
            scanf("%d",&pin);

            fseek(fptr, 0, SEEK_SET);
            FILE *fptr_temp=fopen("temp.txt", "w");
            while (fgets(line, sizeof(line), fptr)!=NULL) {
                if (strstr(line, "Total Balance:")) {
                    fputs(line, fptr_temp);
                    fprintf(fptr_temp, "\n\nDebit card details: \nCard Number- %lld\nCVV- %d\nExpiry Year- %d\nPin- %d\n\n", debitCardNumber, cvv, exp_year,pin);
                    
                }
                else{
                    fputs(line, fptr_temp);
                }
            }
            fclose(fptr);
            fclose(fptr_temp);
            remove(AcFile);
            rename("temp.txt", AcFile);

            fptr=fopen("Bank Customer Details.txt", "r+");
            FILE *temp=fopen("temp1.txt", "w");
            
            char search_ac[100];
            sprintf(search_ac,"A/C Number: %lld",ac);
            search_ac[strcspn(search_ac, "\n")] = '\0';

            char pass_search[200];
            sprintf(pass_search, "Password: %s", passwd);
            pass_search[strcspn(pass_search, "\n")] = '\0';

            while (fgets(line, sizeof(line), fptr)!=NULL) {
                line[strcspn(line, "\n")] = '\0';
                if (strcmp(line,search_ac)==0) {
                    fputs(line,temp);
                    fputs("\n",temp);
                    
                    while (fgets(line, sizeof(line), fptr)!=NULL) {
                        line[strcspn(line, "\n")] = '\0';
                        if (strcmp(line,pass_search)==0) {
                            fputs(line,temp);
                            fprintf(temp, "\nDebit Card Number: %lld\n", debitCardNumber);
                        }
                        else{
                            fputs(line,temp);
                            fputs("\n",temp);
                        }
                    }
                }
                else{
                    fputs(line,temp);
                    fputs("\n",temp);
                }
            }
            fclose(fptr);
            fclose(temp);
            remove("Bank Customer Details.txt");
            rename("temp1.txt", "Bank Customer Details.txt");

            // Print the generated debit card number and CVV
            printf("\nGenerated Debit Card Number: %lld\n", debitCardNumber);
            printf("Generated CVV: %d\n", cvv);
            printf("Expiry Year: %d\n",exp_year);
            AC_Details[i].debitCardNumber=debitCardNumber;
            getchar();
            return;
        }
        else{found=0;}
    }
    if(found==0){
        printf("Enter correct details.");
        return;
    }
}

//Change Debit Card Pin
void change_pin(char *ac){
    FILE *fptr=fopen(ac, "r+");
    int new_pin;
    int old_pin;
    char line[500];
    while(fgets(line, sizeof(line), fptr)!=NULL){
        if(strstr(line, "Pin-")){
            printf("\nEnter New Pin: ");
            scanf("%d",&new_pin);
            sscanf(line, "Pin- %d", &old_pin);
            while(old_pin==new_pin){
                printf("New Pin Number is same as old pin number.\n");
                printf("Enter New Pin: ");
                scanf("%d",&new_pin);
            }
            fseek(fptr, -(strlen(line)+1), SEEK_CUR);
            fprintf(fptr, "Pin- %d\n", new_pin);
            fclose(fptr);
            return;
        }
    }
    
}

//Use Debit Card
void useDebit() {
    static int wrong_attempts = 0;
    if (wrong_attempts > 3) {
        printf("Exceed Number of Attempts. Try Again Later.\n");
        wrong_attempts = 0;
        return;
    }

    long long int debitCardNumber;
    printf("Enter Debit Card Number: ");
    scanf("%lld", &debitCardNumber);

    int found_dcn = -1;
    Number_of_customers = Indexing(0);

    for (int i = 0; i < Number_of_customers; i++) {
        if (AC_Details[i].debitCardNumber == debitCardNumber) {
            found_dcn = 1;

            FILE *fptr;
            char AcFile[19];
            sprintf(AcFile, "%lld", AC_Details[i].AC_Number);
            txtAdder(AcFile);

            fptr = fopen(AcFile, "r+");
            
            char line[500];
            int value = 0;

            time_t current_time;
            time(&current_time);
            struct tm *local_time = localtime(&current_time);
            int year = local_time->tm_year + 1900;

            while (fgets(line, sizeof(line), fptr) != NULL) {
                if (strstr(line, "Expiry Year-")) {
                    int exp_year = -1;
                    sscanf(line, "Expiry Year- %d", &exp_year);
                    if (year > exp_year) {
                        int safe_no;
                        char passwd[100];
                        printf("Your Debit Card is Expired.\n\n");
                        printf("Provide Details to Increase Expiry Date.\n\n");
                        printf("Enter your Safe Number: ");
                        scanf("%d",&safe_no);
                        printf("Enter the Password: ");
                        scanf("%s", passwd);
                        if(AC_Details[i].safeno==safe_no && strcmp(AC_Details[i].passwd, passwd)==0){
                            fseek(fptr, -(strlen(line)+1), SEEK_CUR);
                            fprintf(fptr, "Expiry Year- %d", year+5);
                            change_pin(AcFile);
                        }
                        else{
                            printf("Wrong Details.\n");
                        }
                        fclose(fptr);
                        return;
                    }
                }
            }

            int pin, cvv;
            int found_cvv = -1, found_pin = -1;

            printf("Enter CVV Number: ");
            scanf("%d", &cvv);
            char search_cvv[100], search_pin[100];
            sprintf(search_cvv, "CVV- %d", cvv);
            fseek(fptr, 0, SEEK_SET);

            while (fgets(line, sizeof(line), fptr) != NULL) {
                line[strcspn(line, "\n")] = '\0';
                if (strcmp(line, search_cvv) == 0) {
                    found_cvv = 1;

                    printf("Enter Debit Card Pin: ");
                    scanf("%d", &pin);
                    sprintf(search_pin, "Pin- %d", pin);
                    fseek(fptr, 0, SEEK_SET);

                    while (fgets(line, sizeof(line), fptr) != NULL) {
                        line[strcspn(line, "\n")] = '\0';
                        if (strcmp(line, search_pin) == 0) {
                            found_pin = 1;
                            fseek(fptr, 0, SEEK_SET);
                            long int value = -1;

                            printf("User Details Verified.\n\n");
                            printf("Enter the amount to be withdrawal: ");
                            long int amt;
                            scanf("%ld", &amt);

                            if (amt > 50000) {
                                printf("Exceed Withdrawal Limit.\n");
                                return;
                            }
                            FILE *fptr_temp = fopen("temp.txt", "w");
                            while (fgets(line, sizeof(line), fptr) != NULL) {
                                if (strstr(line, "Total Balance:")) {
                                    sscanf(line, "Total Balance: %ld", &value);
                                    if (amt > value) {
                                        printf("Insufficient Balance.\n");
                                        fclose(fptr_temp);
                                        remove("temp.txt");
                                        fclose(fptr);
                                        return;
                                    } else {
                                        value -= amt;
                                    }
                                    fprintf(fptr_temp, "Total Balance: %d\n", value);
                                    printf("Amount Withdrawal Successfully.\n");
                                    printf("Remaining Balance: %ld\n", value);
                                    
                                } else {
                                    fputs(line, fptr_temp);
                                }
                            }
                            time_t current_time;
                            time(&current_time);

                            // Convert to local time
                            struct tm *local_time = localtime(&current_time);
                            // Display current date and time
                            char time[100];
                            strcpy(time,asctime(local_time));
                            time[strcspn(time, "\n")]='\0';

                            fprintf(fptr_temp, "\n\nOn %s, Amount of Rs. %ld is Debited by Debit Card, Available Balance is: %ld", time, amt, value);
                            fclose(fptr);
                            fclose(fptr_temp);
                            remove(AcFile);
                            rename("temp.txt", AcFile);
                            return;
                        }
                    }
                    if (found_pin == -1) {
                        printf("Wrong Pin Number.\n");
                        wrong_attempts++;
                        useDebit();
                    }
                }
            }

            if (found_cvv == -1) {
                printf("Wrong CVV Number.\n");
                wrong_attempts++;
                useDebit();
            }
        }
    }

    if (found_dcn == -1) {
        printf("Wrong Debit Card Number.\n");
        wrong_attempts++;
        return;
    }
}


void see_tansaction_history(char *ac){
    FILE *fptr=fopen(ac,"r");
    char line[500];
    while(fgets(line, sizeof(line), fptr)!=NULL){
        if(strstr(line, "Transaction History:-")){
            while(fgets(line, sizeof(line), fptr)!=NULL){
                if(strcmp(line, "\n")==0){
                    continue;
                }
                printf("%s",line);
            }
            getchar();
            fclose(fptr);
            return;
        }
    }
}

long long generate_loan_account_number() {
    // Get current time
    time_t current_time;
    time(&current_time);

    // Generate loan account number based on current time
    long long loan_account_number = current_time;

    return loan_account_number;
}

void openloanaccount(){
    printf("Enter your Bank Account Number: ");
    long long int ac;
    scanf("%lld", &ac);
    printf("Enter the Password: ");
    char password[100];
    scanf("%s", password);
    Number_of_customers=Indexing(0);
    getchar();
    for(int i=0; i<Number_of_customers; i++){
        if(AC_Details[i].AC_Number==ac && strcmp(AC_Details[i].passwd, password)==0){
            loan A;
            printf("Enter Customer Name: ");
            char name[100];
            scanf("%[^\n]",name);
            name[strcspn(name, "\n")]='\0';
            AC_Details[i].name[strcspn(AC_Details[i].name, "\n")]='\0';

            if(strcmp(name, AC_Details[i].name)!=0){
                printf("Borrower Name is not match with Bank customer name.\n");
                return;
            }

            printf("\nTypes Of Loan Bank can give: \n");
            printf("1. Home Loan @ 4%% interest per annum for 15 years.\n");
            printf("2. Vehicle Loan @ 6%% interest per annum for 5 years.\n");
            printf("3. Personal Loan @ 10%% interset per annum for 3 years.\n");
            int choice;
            printf("\nEnter Your choice: ");
            scanf("%d", &choice);

            while(choice!=1 && choice!=2 && choice!=3){
                printf("Enter Correct Choice.\n For Exit, press 4.\n\n");
                printf("Enter Your Choice: ");
                scanf("%d", &choice);
                if(choice==4){return;}
            }

            if(choice==1){
                strcpy(A.type, "Home Loan");
                A.interest=4;
                A.year=15;
            }
            else if(choice==2){
                strcpy(A.type, "Vehicle Loan");
                A.interest=6;
                A.year=5;
            }
            else if(choice==3){
                strcpy(A.type, "Personal Loan");
                A.interest=10;
                A.year=3;
            }
            time_t current_time;
            time(&current_time);
            // Convert to local time
            struct tm *local_time = localtime(&current_time);
            A.Open_year = local_time->tm_year + 1900;

            A.loan_ac=generate_loan_account_number();
            FILE *fptr=fopen("LoanCustomer.txt","a");
            fprintf(fptr, "Loan Account number: %lld\n", A.loan_ac);
            fprintf(fptr, "Opening year: %d\n", A.Open_year);
            fprintf(fptr, "Term Year: %d\n", A.year);
            fprintf(fptr, "Loan type: %s\n", A.type);
            fprintf(fptr, "Interest: %.2f\n", A.interest);
            
            printf("\nEnter Amount to be Borrow: ");
            scanf("%f", &A.amount);
            fprintf(fptr, "Amount: %.2f\n", A.amount);
            fprintf(fptr,"\n\n");

            fclose(fptr);

            char AcFile[19];
            sprintf(AcFile, "%lld", ac);
            txtAdder(AcFile);
            fptr=fopen(AcFile, "r+");
            FILE *fptr_temp=fopen("temp.txt", "w");
            if (fptr == NULL || fptr_temp == NULL) {
                printf("Error opening file.\n");
                return;
            }
            
            char line[500];
            
            float value=0;
            while (fgets(line, sizeof(line), fptr) != NULL) {
                if (strstr(line, "Total Balance:")) {
                    fputs(line, fptr_temp);
                    sscanf(line, "Total Balance: %f", &value);
                    value+=A.amount;
                    fseek(fptr_temp, -(strlen(line)+1), SEEK_CUR);
                    fprintf(fptr_temp,"Total Balance: %.2f\n",value);
                }
                else {
                    fputs(line, fptr_temp);
                }
            }
            
            char time[100];
            strcpy(time,asctime(local_time));
            time[strcspn(time, "\n")]='\0';

            fprintf(fptr_temp, "\n\nOn %s, Amount of Rs. %.2f is credited by loan, Available Balance is: %.2f", time, A.amount, value);
            fclose(fptr);
            fclose(fptr_temp);
            remove(AcFile);
            rename("temp.txt", AcFile);

            fprintf(fptr, "Loan Amount: %f\n-----\n", A.amount );
            printf("Your Loan Account Number: %lld\n", A.loan_ac);
            printf("Amount is Disbursed into your bank account.\n");
            getchar();
            return;
        }
    }
}

double remaining_balance(double principal, double annual_interest_rate, int years) {
    // Convert annual interest rate to decimal
    double interest_rate_decimal = annual_interest_rate / 100.0;

    // Calculate total number of compounding periods
    int periods = years;

    // Calculate remaining balance
    double remaining_balance = principal * pow(1 + interest_rate_decimal, periods);
    return remaining_balance;
}

void makeLoanPayment(long long int loan_ac) {
    // Open loan account file for reading and writing
    FILE *fptr = fopen("LoanCustomer.txt", "r+");
    if (fptr == NULL) {
        printf("Error opening loan account file.\n");
        return;
    }

    // Open temporary file for writing updated data
    FILE *temp_fptr = fopen("temp.txt", "w");
    if (temp_fptr == NULL) {
        printf("Error opening temporary file.\n");
        fclose(fptr);
        return;
    }

    loan A;
    // Loop through loan account file to find the account
    int found = 0;
    char line[1000];
    char search_ac[100];
    sprintf(search_ac, "Loan Account number: %lld", loan_ac);

    while (fgets(line, sizeof(line), fptr) != NULL) {
        line[strcspn(line, "\n")]='\0';
        if (strcmp(line, search_ac) == 0) {
            
            // Read and store loan account data
            fgets(line, sizeof(line), fptr);
            sscanf(line, "Opening year: %d", &A.Open_year);
            fgets(line, sizeof(line), fptr);
            sscanf(line, "Term Year: %d", &A.year);
            fgets(line, sizeof(line), fptr);
            sscanf(line, "Loan type: %[^\n]", A.type);
            fgets(line, sizeof(line), fptr);
            sscanf(line, "Interest: %f", &A.interest);
            fgets(line, sizeof(line), fptr);
            sscanf(line, "Amount: %f", &A.amount);
        
            time_t current_time;
            time(&current_time);
            // Convert to local time
            struct tm *local_time = localtime(&current_time);
            int today_year = local_time->tm_year + 1900;
            
            if(A.Open_year+A.year<today_year){
                printf("Duration of repayment of loan is over, Now pay the full amount as soon as possible to avoid penalties over penalties.\n");
                if(strcmp(A.type,"Home Loan")==0){
                    printf("Penality of Rs.3000 is Applied and increase every year.\n");
                    A.amount+=1000*(today_year-A.Open_year-A.year);
                }
                else if(strcmp(A.type,"Vehicle Loan")==0){
                    printf("Penality of Rs.500 is Applied and increase every year.\n");
                    A.amount+=500*(today_year-A.Open_year-A.year);
                }
                else if(strcmp(A.type,"Personal Loan")==0){
                    printf("Penality of Rs.100 is Applied and increase every year.\n");
                    A.amount+=100*(today_year-A.Open_year-A.year);
                }
            }

            if(A.amount<=0){
                printf("Loan Amount is already paid fully.\n");
                fclose(fptr);
                fclose(temp_fptr);
                remove("temp.txt");
                return;
            }
             A.amount= remaining_balance(A.amount, A.interest, (today_year-A.Open_year));

            printf("Amount left to be paid: %.2f\n\n",A.amount);
            getchar();
            A.amount=A.amount-Withdrawal(1);
            
            fprintf(temp_fptr, "Loan Account number: %lld\n", loan_ac);
            fprintf(temp_fptr, "Opening year: %d\n", A.Open_year);
            fprintf(temp_fptr, "Term Year: %d\n", A.year);
            fprintf(temp_fptr, "Loan type: %s\n", A.type);
            fprintf(temp_fptr, "Interest: %.2f\n", A.interest);
            fprintf(temp_fptr, "Amount: %.2f\n", A.amount);

            // Set flag indicating loan account was found
            found = 1;
        }
        // If the account is not the one being searched for, copy it to the temporary file
        else {
            fputs(line, temp_fptr);
            fputc('\n', temp_fptr);
        }
    }

    // Close both files
    fclose(fptr);
    fclose(temp_fptr);

    // Check if the loan account was found
    if (!found) {
        printf("Loan account not found.\n");
        remove("temp.txt"); // Delete temporary file
        return;
    }

    // Remove original loan account file and rename temporary file
    remove("LoanCustomer.txt");
    rename("temp.txt", "LoanCustomer.txt");

    printf("\nLoan Payment successfully made.\n");
    printf("Amount Left to be paid: %.2f\n",A.amount);
}
