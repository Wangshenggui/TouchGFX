#include <gui/containers/T9_Input.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/Utils.hpp>

#include <string.h>
#include <stdio.h>



//ƴ�����뷨
pyinput t9 =
{
    T9_get_pymb,
    0,
};

//�Ƚ������ַ�����ƥ�����
//����ֵ:0xff,��ʾ��ȫƥ��.
//		 ����,ƥ����ַ���
unsigned char T9_str_match(unsigned char* str1, unsigned char* str2)
{
    unsigned char i = 0;
    while (1)
    {
        if (*str1 != *str2)break;		  //����ƥ��
        if (*str1 == '\0') { i = 0XFF; break; }//��ȫƥ��
        i++;
        str1++;
        str2++;
    }
    return i;//�����ַ������
}

//��ȡƥ���ƴ�����
//*strin,������ַ���,����:"726"
//**matchlist,�����ƥ���.
//����ֵ:[7],0,��ʾ��ȫƥ�䣻1����ʾ����ƥ�䣨����û����ȫƥ���ʱ��Ż���֣�
//		 [6:0],��ȫƥ���ʱ�򣬱�ʾ��ȫƥ���ƴ������
//			   ����ƥ���ʱ�򣬱�ʾ��Чƥ���λ��				    	 
unsigned char T9_get_matched_pymb(unsigned char* strin, const py_index** matchlist)
{
    const py_index* bestmatch = 0; // ָ�����ƥ���ָ��
    unsigned int pyindex_len = 0;
    unsigned int i = 0;
    unsigned char temp, mcnt = 0, bmcnt = 0;

    // ��py_index3���еĵ�һ����Ŀ��ʼ��bestmatch
    bestmatch = &py_index3[0];

    // ��ȡpy_index3��Ĵ�С
    pyindex_len = sizeof(py_index3) / sizeof(py_index3[0]);

    // ����py_index3���е�ÿ����Ŀ
    for (i = 0; i < pyindex_len; i++)
    {
        // ��������ַ����Ƿ񲿷ֻ���ȫƥ�䵱ǰ��Ŀ
        temp = T9_str_match(strin, (unsigned char*)py_index3[i].py_input);

        if (temp)
        {
            // ����ҵ���ȫƥ�䣬������ӵ�matchlist��
            if (temp == 0XFF)
            {
                matchlist[mcnt++] = &py_index3[i];
            }
            else if (temp > bmcnt)
            {
                // �������ƥ��������ǰ�����ƥ�䣬����bestmatch
                bmcnt = temp;
                bestmatch = &py_index3[i];
            }
        }
    }

    // ���û����ȫƥ�䵫�в���ƥ�䣬��matchlist����Ϊ��Ѳ���ƥ��
    if (mcnt == 0 && bmcnt)
    {
        matchlist[0] = bestmatch;
        mcnt = bmcnt | 0X80; // �������λ��ʾ����ƥ��
    }

    return mcnt; // ����ƥ��ĸ���
}



//�õ�ƴ�����.
//str:�����ַ���
//����ֵ:ƥ�����.
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
        printf("\r\n输入数字�?%s\r\n", inputstr);
        printf("部分匹配位数:%d\r\n", t & 0X7F);
        printf("部分匹配结果:%s,%s\r\n", t9.pymb[0]->py, t9.pymb[0]->pymb);
    }
    else if (t)
    {
        printf("\r\n输入数字�?%s\r\n", inputstr);
        printf("完全匹配个数:%d\r\n", t);
        printf("完全匹配的结�?\r\n");
        for (i = 0; i < t; i++)
        {
            printf("%s,%s\r\n", t9.pymb[i]->py, t9.pymb[i]->pymb);
        }
    }
    else printf("没有任何匹配结果！\r\n");
}




