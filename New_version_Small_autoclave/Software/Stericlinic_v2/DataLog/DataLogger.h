/*
 * DataLogger.h
 *
 *  Created on: Aug 26, 2016
 *      Author: Holguer
 */

#ifndef DATALOGGER_H_
#define DATALOGGER_H_

//json docs https://github.com/nlohmann/json/tree/develop/doc/examples

#include <string>


#include "json.hpp"


using json = nlohmann::json;

//Variables Necesarias para

extern std::string send_string;
extern int send_int;
extern float send_float;


//Seccion donde se hacen MACROS para hacer facil en envio de datos desde JSON hacia Nextion y guardar datos JSON
#define SEND_SINGLE_STR_NEXTION(input,input2) send_string=grabador->init_configs input; \
LCD->nextionF(input2,send_string.c_str())

#define SEND_SINGLE_INT_NEXTION(input,input2) send_int=grabador->init_configs input; \
LCD->nextionF(input2,send_int)

#define SEND_SINGLE_FLOAT_NEXTION(input,input2) send_float=grabador->init_configs input; \
LCD->nextionF(input2,send_float)

#define SET_JSON_STR(input,input2) send_string=input2; \
grabador->init_configs input=send_string

#define SET_JSON_INT(input,input2) send_int=input2; \
grabador->init_configs input=send_int

#define SET_JSON_FLOAT(input,input2) send_float=input2; \
grabador->init_configs input=send_float


class DataLogger {

public:
	std::string current_cycle_file;
	std::string current_cycle_file2print;
	json current_cycle_2_save;
	json init_configs;
	int current_cycle;
	int last_cycle;
	std::string admin_pass;
	std::string user_pass;

	DataLogger();

	//Basic functions
	char CheckDiskStatus();
	char CheckIfSystemWasShutAbruted();
	char append_data_toFile(std::string document, std::string text);
	char create_new_file(char * document);
	char delete_file(char * document);
	char read_byte(char *document);
	void load_file_into_string(char *document,std::string * output_string);
	void save_string2File(char *document, std::string * output_string);
	//Datalogger
	void load_init_configs();
	void load_admin_pass();
	void load_usr_pass();
	void save_init_configs();
	void save_admin_pass();
	void save_usr_pass();
	//cycles utilities
	void create_a_cycle(int number);
	char load_a_cycle(int number);
	void save_cycle();
	void delete_cycle();
	void cycle2Printfile(int sampler);//sampler en segundos



	// Json Test, DO not run
	void testJson();
	void testJson2();
	virtual ~DataLogger();
};

#endif /* DATALOGGER_H_ */
