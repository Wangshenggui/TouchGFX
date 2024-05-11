#ifndef T9_INPUT_HPP
#define T9_INPUT_HPP

#include <gui/containers/KeyBoardContainer.hpp>
#include <gui/containers/T9_InputMb.hpp>




#define MAX_MATCH_PYMB 	10	//最大匹配数

//拼音输入法
typedef struct
{
  unsigned char(*getpymb)(unsigned char *instr);			//字符串到码表获取函数
  py_index *pymb[MAX_MATCH_PYMB];	//码表存放位置
}pyinput;

extern pyinput t9;

unsigned char T9_str_match(unsigned char*str1,unsigned char*str2);
unsigned char T9_get_matched_pymb(unsigned char *strin,const py_index **matchlist);
unsigned char T9_get_pymb(unsigned char* str);
void T9_test_py(unsigned char *inputstr);


#endif // KEYBOARDCONTAINER_HPP
