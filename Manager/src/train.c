/*
 * train.c
 *
 *  Created on: Jul 6, 2023
 *      Author: 91701
 */

#include <stdio.h>
#include <stdint.h>



uint32_t train_config_print(void)
	{
		uint32_t menu_no;
		printf("\v1. Add new train\n"
				"2. Delete Existing train\n"
				"3. Update details of train\n"
				"4. Back to Menu\n");
		printf("\nEnter Corresponding no. to perform operation: ");
		scanf("%d",&menu_no);
		return menu_no;

	}

