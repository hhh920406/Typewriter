using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;

namespace Clarify_Time
{
    class Program
    {
        static bool isNumber(char ch)
        {
            return ch >= '0' && ch <= '9';
        }

        static void Main(string[] args)
        {
            if (args.Length > 0)
            {
                try
                {
                    string path = args[0];
                    Bitmap bitmap = new Bitmap(path);
                    string value = Encoding.Default.GetString(bitmap.GetPropertyItem(0x0132).Value);
                    bool flag = true;
                    if (value.Length < 7)
                    {
                        flag = false;
                    }
                    else if (!isNumber(value[0]) || !isNumber(value[1]) || !isNumber(value[2]) || !isNumber(value[3]))
                    {
                        flag = false;
                    }
                    else if (isNumber(value[4]))
                    {
                        flag = false;
                    }
                    else if (!isNumber(value[5]) || !isNumber(value[6]))
                    {
                        flag = false;
                    }
                    if (flag)
                    {
                        value = value.Substring(0, 4) + "-" + value.Substring(5, 2);
                        Console.WriteLine(value);
                    }
                    else
                    {
                        Console.WriteLine(-1);
                    }
                }
                catch
                {
                    Console.WriteLine(-1);
                }
            }
            else
            {
                Console.WriteLine(-1);
            }
        }
    }
}
