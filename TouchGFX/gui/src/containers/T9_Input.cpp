#include <gui/containers/T9_Input.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/Utils.hpp>

#include <string.h>
#include <stdio.h>



//拼音输入法
pyinput t9 =
{
    T9_get_pymb,
    0,
};

//比较两个字符串的匹配情况
//返回值:0xff,表示完全匹配.
//		 其他,匹配的字符数
unsigned char T9_str_match(unsigned char* str1, unsigned char* str2)
{
    unsigned char i = 0;
    while (1)
    {
        if (*str1 != *str2)break;		  //部分匹配
        if (*str1 == '\0') { i = 0XFF; break; }//完全匹配
        i++;
        str1++;
        str2++;
    }
    return i;//两个字符串相等
}

//获取匹配的拼音码表
//*strin,输入的字符串,形如:"726"
//**matchlist,输出的匹配表.
//返回值:[7],0,表示完全匹配；1，表示部分匹配（仅在没有完全匹配的时候才会出现）
//		 [6:0],完全匹配的时候，表示完全匹配的拼音个数
//			   部分匹配的时候，表示有效匹配的位数				    	 
unsigned char T9_get_matched_pymb(unsigned char* strin, const py_index** matchlist)
{
    const py_index* bestmatch = 0; // 指向最佳匹配的指针
    unsigned int pyindex_len = 0;
    unsigned int i = 0;
    unsigned char temp, mcnt = 0, bmcnt = 0;

    // 用py_index3表中的第一个条目初始化bestmatch
    bestmatch = &py_index3[0];

    // 获取py_index3表的大小
    pyindex_len = sizeof(py_index3) / sizeof(py_index3[0]);

    // 遍历py_index3表中的每个条目
    for (i = 0; i < pyindex_len; i++)
    {
        // 检查输入字符串是否部分或完全匹配当前条目
        temp = T9_str_match(strin, (unsigned char*)py_index3[i].py_input);

        if (temp)
        {
            // 如果找到完全匹配，将其添加到matchlist中
            if (temp == 0XFF)
            {
                matchlist[mcnt++] = &py_index3[i];
            }
            else if (temp > bmcnt)
            {
                // 如果部分匹配优于先前的最佳匹配，更新bestmatch
                bmcnt = temp;
                bestmatch = &py_index3[i];
            }
        }
    }

    // 如果没有完全匹配但有部分匹配，将matchlist设置为最佳部分匹配
    if (mcnt == 0 && bmcnt)
    {
        matchlist[0] = bestmatch;
        mcnt = bmcnt | 0X80; // 设置最高位表示部分匹配
    }

    return mcnt; // 返回匹配的个数
}



//得到拼音码表.
//str:输入字符串
//返回值:匹配个数.
unsigned char T9_get_pymb(unsigned char* str)
{
    return T9_get_matched_pymb(str, const_cast<const py_index**>(t9.pymb));
}

void T9_test_py(unsigned char* inputstr)
{
    unsigned char t = 0;
    unsigned char i = 0;
    t = t9.getpymb(inputstr);
    if (t & 0X80)
    {
        printf("\r\n杈撳叆鏁板瓧涓?%s\r\n", inputstr);
        printf("閮ㄥ垎鍖归厤浣嶆暟:%d\r\n", t & 0X7F);
        printf("閮ㄥ垎鍖归厤缁撴灉:%s,%s\r\n", t9.pymb[0]->py, t9.pymb[0]->pymb);
    }
    else if (t)
    {
        printf("\r\n杈撳叆鏁板瓧涓?%s\r\n", inputstr);
        printf("瀹屽叏鍖归厤涓暟:%d\r\n", t);
        printf("瀹屽叏鍖归厤鐨勭粨鏋?\r\n");
        for (i = 0; i < t; i++)
        {
            printf("%s,%s\r\n", t9.pymb[i]->py, t9.pymb[i]->pymb);
        }
    }
    else printf("娌℃湁浠讳綍鍖归厤缁撴灉锛乗r\n");
}




