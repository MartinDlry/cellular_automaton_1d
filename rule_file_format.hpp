#ifndef RULE_FORMAT_HPP
#define RULE_FORMAT_HPP

#define RULE_FILE_COMMENT_SYMBOL "#"

#define RULE_FILE_NUMBER "[0-9]{1,3}"

// defining TAGS

#define RULE_FILE_BEGIN_SIGNATURE_TAG "_ca1d_rule_begin_"

#define RULE_FILE_END_SIGNATURE_TAG "_ca1d_rule_end_"

#define RULE_FILE_NUMBER_OF_STATE_TAG "number_of_states"

#define RULE_FILE_DEFAULT_TAG "default"

#define RULE_FILE_CASE_SEPARATOR_1 "\\|"

#define RULE_FILE_CASE_SEPARATOR_2 "->"

#define RULE_FILE_GENERAL_CASE_STATE_SYMBOL "\\."


//defining line formats/regex

#define RULE_FILE_EMPTY_LINE_REGEX "\\s*(" RULE_FILE_COMMENT_SYMBOL ".*)?"

#define RULE_FILE_STATE_CASE "(" RULE_FILE_NUMBER "|" RULE_FILE_GENERAL_CASE_STATE_SYMBOL ")" 

#define RULE_FILE_FIRST_LINE_REGEX " *"  RULE_FILE_BEGIN_SIGNATURE_TAG  " *"

#define RULE_FILE_NUMBER_OF_STATE_LINE_REGEX " *"  RULE_FILE_NUMBER_OF_STATE_TAG  " *" RULE_FILE_NUMBER " *"

#define RULE_FILE_DEFAULT_LINE_REGEX " *"  RULE_FILE_DEFAULT_TAG  " *" RULE_FILE_NUMBER " *"

#define RULE_FILE_CASE_LINE_REGEX " *" RULE_FILE_STATE_CASE  " *" RULE_FILE_CASE_SEPARATOR_1  " *" RULE_FILE_STATE_CASE " *"  RULE_FILE_CASE_SEPARATOR_1  " *" RULE_FILE_STATE_CASE " *"  RULE_FILE_CASE_SEPARATOR_2 " *" RULE_FILE_NUMBER " *"

#define RULE_FILE_LAST_LINE_REGEX " *"  RULE_FILE_END_SIGNATURE_TAG  " *"


#endif