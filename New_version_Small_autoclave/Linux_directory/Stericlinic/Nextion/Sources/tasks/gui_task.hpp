/*
 * gui_task.hpp
 *
 *  Created on: Aug 18, 2016
 *      Author: Holguer
 */

#ifndef GUI_TASK_HPP_
#define GUI_TASK_HPP_

void *rx_uart(void *x_void_ptr);
void *print_uart(void *x_void_ptr);

int test(void *shared);
int test2(void *shared);
int teclado(void *shared);
int print(void * shared);

void init_gui();

#endif /* GUI_TASK_HPP_ */
