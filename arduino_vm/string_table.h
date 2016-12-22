const char MSG_COMMAND_NOT_EXIST_FMT[]PROGMEM = "'%s' NOT EXIST, TYPE help FOR SUPPORTED COMMANDS\n";
const char MSG_NOT_FINISHED[]PROGMEM = "NOT FINISHED";
const char MSG_RM_RETURN_CODE_FMT[]PROGMEM = "rm '%s' RETURN CODE %d\n";
const char MSG_VM_STOPPED[]PROGMEM = "VM STOPPD";
const char MSG_VM_START[]PROGMEM = "VM START";
const char MSG_LS_HEADER[]PROGMEM = "    NAME\t\tSIZE";
const char MSG_LS_ITEMS_FMT[]PROGMEM = "%8s\t\t%d\n";
const char MSG_LS_SUMMARY_FMT[]PROGMEM = "\t\t%d FILES\t\t%d BYTES\n";

const char MSG_INPUT_HINT[]PROGMEM = "\nEnter -1 to end input.";
const char MSG_HELP_HEADER_FMT[]PROGMEM = "COMMANDS COUNT (%d)\n";
const char MSG_HELP_ITMES_FMT[]PROGMEM = "%s\t\t\t%s\n";

const char MSG_VM_DUMP_HEADER_FMT[]PROGMEM = "\nSystem started %ld ms ago, runned %ld Instructions\n";
const char MSG_VM_DUMP_HEADER2_FMT[]PROGMEM = "ADDER:%4d, MEMORY:\n%3s";
const char MSG_VM_HELP_HEADER_FMT[]PROGMEM = "THIS MACHINE HAVE %d(int)MEMORY, %d(int)STACK\n";
const char MSG_VM_HELP_CONTENT[]PROGMEM = "INSTRUCTION IS 4 DECIMAL DIGITS, FORMAT: AABB";
const char MSG_VM_WARNING_STACK_OVERFLOW[]PROGMEM = "[warning] STACK OVERFLOW.";
const char MSG_VM_WARNING_STACK_EMPTY[]PROGMEM = "[warning] STACK EMPTY.";

const char MSG_VM_MANAGER_FINISHED_SUMMARY_FMT[]PROGMEM = "\nTotal run %ld instructions. used %ld ms.\n";
const char MSG_VM_MANAGER_DEFAULT_WRITE_BLINK[]PROGMEM = "default write blink code";
const char MSG_VM_MANAGER_LOADED_CODE_FMT[]PROGMEM = "default running code '%s' size:%d\n";
const char MSG_VM_MANAGER_WELCOME_FMT[]PROGMEM = "AISTLAB VM v%s\nBAUD:%ld\n";

