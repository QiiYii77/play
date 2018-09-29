class Solution {
public:
    int myAtoi(string str) {
        int rt = 0;
        bool pos = true;
        bool number_started = false;
        bool flow = false;
        
        char *c_str = new char[str.length() + 1];
        std:strcpy(c_str, str.c_str());
        char *start = NULL;
        char *end = NULL;
        char *c = c_str;
        while (*c != '\0')
        {
            if (number_started)
            {
                if (*c >= '0' && *c <= '9')
                {
                    if (!start)
                    {
                        start = c;
                    }
                }
                else
                {
                    if (start)
                    {
                        end = c - 1;
                        break;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
            else
            {
                if (*c == ' ')
                {
                    
                }
                else if (*c == '+')
                {
                    pos = true;
                    number_started = true;
                }
                else if (*c == '-')
                {
                    pos = false;
                    number_started = true;
                }
                else if (*c >= '0' && *c <= '9')
                {
                    number_started = true;
                    start = c;
                }
                else
                {
                    return 0;
                }
            }
            c++;
        }
        
        if (!start)
        {
            return 0;
        }
        
        if (!end)
        {
            end = c - 1;
        }
        
        while (*start == '0')
        {
            start += 1;
        }
        
        int len = end - start + 1;
        if (len > 10)
        {
            flow = true;
        }
        else if (len == 10)
        {
            long temp = 0;
            for (int i = 0; i < len; i++)
            {
                temp += (*(start + i) - '0') * pow(10, len - i - 1);
                if (temp > 0x7FFFFFFF)
                {
                    flow = true;
                    break;
                }
            }
            rt = (int) temp;
        }
        else
        {
            for (int i = 0; i < len; i++)
            {
                rt += (*(end - i) - '0') * pow(10, i);
            }
        }
        
        if (flow)
        {
            if (pos)
            {
                return 0x7FFFFFFF;
            }
            else
            {
                return 0x80000000;
            }
        }
        else
        {
            if (pos)
            {
                return rt;
            }
            else
            {
                return 0 - rt;
            }
        }
    }
};
