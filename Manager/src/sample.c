/*
 * sample.c
 *
 *  Created on: Jul 9, 2023
 *      Author: 91701
 */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

// Callback function for reading data from the database
static int callback(void *data, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main() {
	sqlite3 *db;
	char *errMsg = 0;
	int rc;

	// Open the database connection
	rc = sqlite3_open("example.db", &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		return 1;
	}

	// Create the table if it doesn't exist
	const char *createTableSQL =
			"CREATE TABLE IF NOT EXISTS MyTable (id INTEGER PRIMARY KEY, name TEXT);";
	rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", errMsg);
		sqlite3_free(errMsg);
		return 1;
	}

	int choice;
	int id;
	char name[100];

	while (1) {
		printf("\n1. Add data\n");
		printf("2. Delete data\n");
		printf("3. Read data\n");
		printf("4. Quit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printf("Enter ID: ");
			scanf("%d", &id);
			printf("Enter Name: ");
			scanf("%s", name);

			// Insert data into the table
			char insertSQL[100];
			snprintf(insertSQL, sizeof(insertSQL),
					"INSERT INTO MyTable (id, name) VALUES (%d, '%s');", id,
					name);
			rc = sqlite3_exec(db, insertSQL, 0, 0, &errMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", errMsg);
				sqlite3_free(errMsg);
			} else {
				printf("Data inserted successfully.\n");
			}
			break;

		case 2:
			printf("Enter ID to delete: ");
			scanf("%d", &id);

			// Delete data from the table
			char deleteSQL[100];
			snprintf(deleteSQL, sizeof(deleteSQL),
					"DELETE FROM MyTable WHERE id = %d;", id);
			rc = sqlite3_exec(db, deleteSQL, 0, 0, &errMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", errMsg);
				sqlite3_free(errMsg);
			} else {
				printf("Data deleted successfully.\n");
			}
			break;

		case 3:
			// Read data from the table
			const char *selectSQL = "SELECT * FROM MyTable;";
			rc = sqlite3_exec(db, selectSQL, callback, 0, &errMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", errMsg);
				sqlite3_free(errMsg);
			}
			break;

		case 4:
			// Close the database connection and exit
			sqlite3_close(db);
			return 0;

		default:
			printf("Invalid choice. Please try again.\n");
		}
	}
}

