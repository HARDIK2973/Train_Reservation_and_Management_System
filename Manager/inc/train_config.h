/*
 * train_config.h
 *
 *  Created on: Jul 5, 2023
 *      Author: 91701
 */

#include <stdio.h>
#include <stdint.h>

#ifndef TRAIN_CONFIG_H_
#define TRAIN_CONFIG_H_

void welcomeUser(void);


uint32_t display_menu_M(void);
uint32_t train_config_print(void);

void add_train(void);
void delete_train(void);
void update_train(void);
void back_to_menu(void);



typedef struct{
	int hours;
	int min;
	int seconds;
	char amopm[3];

}TrainConfigTime_t;

typedef struct{
	char name[15];
	int id;
	char class[8];
	char quota[9];
	int seats;
	char time_s[10];
	TrainConfigTime_t *ptime;
	int fitst_tic_no;
	char save[3];

}TrainConfig_t;

typedef struct{
	char name[15];
	int id;
}TrainDelete_t;

//table Created for Database
void create_table_sqlite(void);

//data inserted to database
void insert_to_database(TrainConfig_t *train);

//delete from database
void delete_from_database(TrainDelete_t train);

#endif /* TRAIN_CONFIG_H_ */
