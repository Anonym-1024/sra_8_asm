#ifndef RESOURCES_H
#define RESOURCES_H


enum instruction_argument {
	ARG_REG,
	ARG_REG_IMM,
	ARG_SYS_REG
};

enum instruction_encoding_category {
	IE_CAT_1,
	IE_CAT_2,
	IE_CAT_3,
	IE_CAT_4
};

enum control_signal {
	CSIG

};

struct instruction_definition {
	char mnemonic[10];
	int opcode;
	enum instruction_encoding_category encoding;
	enum instruction_argument arguments[10];
	enum control_signal steps[16][10];
};

extern const int instruction_definitions_count;
extern const struct instruction_definition instruction_definitions[56];

extern const int instruction_names_count;
extern const char instruction_names[56][10];

extern const int condition_code_names_count;
extern const char condition_code_names[19][5];

extern const int register_names_count;
extern const char register_names[16][3];

extern const int system_register_names_count;
extern const char system_register_names[6][10];

extern const int port_names_count;
extern const char port_names[8][3];

extern const int directiove_names_count;
extern const char directive_names[6][10];

extern const int macro_manes_count;
extern const char macro_names[2][10];






#endif
