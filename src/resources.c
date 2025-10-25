#include "resources.h"




const int instruction_definitions_count = 56;
const struct instruction_definition instruction_definitions[56] = {
	{"mov", 0, IE_CAT_3, {ARG_REG, ARG_REG_IMM}, {
		{},
		{},
		{},
		{}
	}}

};




const int instruction_names_count = 56;
const char instruction_names[56][10] = {
	"mov",
	"movs",
	"mvn",
	"mvns",
	"srw",
	"srr",
	"ldr",
	"ldro",
	"ldri",
	"str",
	"stro",
	"stri",
	"add",
	"adds",
	"addc",
	"addcs",
	"sub",
	"subs",
	"subc",
	"subcs",
	"and",
	"ands",
	"or",
	"ors",
	"eor",
	"eors",
	"lsl",
	"lsls",
	"lsr",
	"lsrs",
	"asr",
	"asrs",
	"cls",
	"csls",
	"csr",
	"csrs",
	"cmn",
	"addcd",
	"cmp",
	"subcd",
	"andd",
	"ord",
	"eord",
	"lsld",
	"lsrd",
	"asrd",
	"csld",
	"csrd",
	"ba",
	"bal",
	"br",
	"brl",
	"ptr",
	"ptw",
	"ptsr",
	"svc"
};

const int condition_code_names_count = 19;
const char condition_code_names[19][5] = {
	"al",
	"eq",
	"zs",
	"mi",
	"vs",
	"su",
	"cc",
	"gu",
	"ss",
	"gs",
	"ne",
	"zc",
	"pl",
	"vc",
	"geu",
	"cs",
	"seu",
	"ges",
	"ses"
};

const int register_names_count = 16;
const char register_names[16][3] = {
	"r0",
	"r1",
	"r2",
	"r3",
	"r4",
	"r5",
	"r6",
	"r7",
	"r8",
	"r9",
	"r10",
	"r11",
	"r12",
	"r13",
	"r14",
	"r15"
};

const int system_register_names_count = 6;
const char system_register_names[6][10] = {
	"pc_b0",
	"pc_b1",
	"pdbr_b0",
	"pdbr_b1",
	"psr",
	"intr"
};

const int port_names_count = 8;
const char port_names[8][3] = {
	"p0",
	"p1",
	"p2",
	"p3",
	"p4",
	"p5",
	"p6",
	"p7"
};

const int directive_names_count = 6;
const char directive_names[6][10] = {
	".def",
	".byte",
	".bytes",
	".arr",
	".label",
	".start"
};

const int macro_names_count = 2;
const char macro_names[2][10] = {
	"!mov",
	"!b"
};





