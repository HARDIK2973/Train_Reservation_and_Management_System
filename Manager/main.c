/*
 * main.c
 *
 *  Created on: Jul 5, 2023
 *      Author: 91701
 */

#include "train_config.h"
#include "sqlite3.h"
#include <string.h>

void (*fpointer[4])(void) = {&add_train,&delete_train,&update_train,&back_to_menu };
TrainConfig_t train;

sqlite3 *db;

int main() {

	welcomeUser();


	// Create the table if it doesn't exist
	create_table_sqlite();


	uint32_t password = 12345, pass;
	uint8_t try = 3;

	printf("Enter the Password: ");
	scanf("%d", &pass);

	while (try > 0) {
		if (pass == password) {

			do{
				int val;

			val = display_menu_M();
			switch (val) {
				case 1:
					val = train_config_print();
					if(val == 4)
						break;
					system("cls");
					(*fpointer[val - 1])();
					break;
				case 2:

					break;
				case 3:
					break;
				}

				break;

			}while(1);


		} else {
			try--;
			if (try > 0) {
				printf("\nSorry! You have entered Wrong Password.\n");
				printf("You have %d try left to login.\n", try);
				printf("Enter the Password: ");
				scanf("%d", &pass);
			} else {
				printf("\nSorry! Now you can not access this file.");
			}

		}
	}

	while (1);
	return 0;
}

void create_table_sqlite(void){


	char *errMsg = 0;

		int rc = sqlite3_open("train.db", &db);
		if (rc != SQLITE_OK) {
		    // Handle the error
		}

	const char *createTableSQL =
			"CREATE TABLE IF NOT EXISTS MyTable (id INTEGER PRIMARY KEY, name TEXT, class TEXT, quota TEXT, time TEXT, seats INTEGER, first_tic_no INTEGER);";
	rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", errMsg);
		sqlite3_free(errMsg);

	}

}

uint32_t display_menu_M(void) {
	uint32_t menu_no;

	printf("\v1. Train Configuration\n"
			"2. Q & A Section\n"
			"3. Reports\n");
	printf("\nEnter Corresponding no. to perform operation: ");
	scanf("%d", &menu_no);

	return menu_no;
}


void add_train(void) {
	system("cls");
	printf("Enter Train Name: ");
	//	gets(train.name);
	scanf("%s",train.name);
	printf("\nEnter Identification no for your train: ");
	scanf("%d",&train.id);

	printf("\nEnter Class(): ");
	scanf("%s",train.class);

	printf("\n Enter Quota: ");
	scanf("%s",train.quota);

	printf("\nEnter Seats: ");
	scanf("%d",&train.seats);

	printf("\nEnter Time in this (hh:mm:am/pm) format: ");
	scanf("%s",train.time_s);

	printf("\nEnter First ticket no. for your train: ");
	scanf("%d",&train.fitst_tic_no);

	printf("Do You Want to save the details what you have Entered?(y/n)");
	scanf("%s",train.save);


	if(!strcmp(train.save,"y"))//strcmp return 0 if both strings are same
		insert_to_database(&train);
	//printf("save is %s",train.save);



}

void insert_to_database(TrainConfig_t *train){

	// Insert data into the table
	char insertSQL[200];
	char *errMsg = 0;
	int rc;

	snprintf(insertSQL, sizeof(insertSQL),
			"INSERT INTO MyTable (id, name, class, quota, time, seats, first_tic_no) VALUES (%d, '%s', '%s', '%s', '%s', %d, %d);", train->id,
			train->name,train->class, train->quota, train->time_s, train->seats, train->fitst_tic_no);
	rc = sqlite3_exec(db, insertSQL, 0, 0, &errMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", errMsg);
		sqlite3_free(errMsg);
	} else {
		printf("Train %s is added to the Database Successfully.",train->name);
	}
}

void delete_from_database(TrainDelete_t train){

	char *errMsg = 0;
	int rc;

	// Delete data from the table
	char deleteSQL[100];
	snprintf(deleteSQL, sizeof(deleteSQL),
			"DELETE FROM MyTable WHERE id = %d;", train.id);
	rc = sqlite3_exec(db, deleteSQL, 0, 0, &errMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", errMsg);
		sqlite3_free(errMsg);
	} else {
		printf("\nTrain(%s) Data deleted successfully.\n",train.name);
	}
}

void delete_train(void) {
	TrainDelete_t train;
	char yorn[3];
	printf("\nEnter name if the Train you want to delete: ");
	scanf("%s",train.name);

	printf("\nEnter Identification no. of your train: ");
	scanf("%d",&train.id);

	printf("\nYou want to delete %s train Confirm?(y/n)",train.name);
	scanf("%s",yorn);

	if(!strcmp(yorn,"y"))//strcmp return 0 if both strings are same
		delete_from_database(train);


}
void update_train(void) {

}
void back_to_menu(void) {


}

void welcomeUser(void){

	system("color 4F");
	printf("\n\n\n\n\n");
	printf("\t-----------------------------------------------------------------------------------\n");
	printf("\t########################## Train Management System ################################\n");
	printf("\t-----------------------------------------------------------------------------------\n");
	printf("\n\n\n\n\t***************************Welcome***************************************************\n");
	system("pause");
	system("color 3F");
	system("cls");

}
