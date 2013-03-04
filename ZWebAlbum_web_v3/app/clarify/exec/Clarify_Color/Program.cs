using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;

namespace Clarify_Color
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length > 0)
            {
                string path = args[0];
                Bitmap bitmap = new Bitmap(path);
                int[] hueScope = new int[7];
                for (int i = 0; i < 7; ++i)
                {
                    hueScope[i] = 0;
                }
                for (int x = 0; x < bitmap.Width; ++x)
                {
                    for (int y = 0; y < bitmap.Height; ++y)
                    {
                        int hue = (int)bitmap.GetPixel(x, y).GetHue();
                        if (hue >= 290 || hue <= 20)
                        {
                            ++hueScope[0];
                        }
                        else if (hue >= 21 && hue <= 40)
                        {
                            ++hueScope[1];
                        }
                        else if (hue >= 41 && hue <= 75)
                        {
                            ++hueScope[2];
                        }
                        else if (hue >= 76 && hue <= 155)
                        {
                            ++hueScope[3];
                        }
                        else if (hue >= 156 && hue <= 190)
                        {
                            ++hueScope[4];
                        }
                        else if (hue >= 191 && hue <= 270)
                        {
                            ++hueScope[5];
                        }
                        else
                        {
                            ++hueScope[6];
                        }
                    }
                }
                int maxHue = 0;
                for (int i = 1; i < 7; ++i)
                {
                    if (hueScope[i] > hueScope[maxHue])
                    {
                        maxHue = i;
                    }
                }
                Console.Write(maxHue);
            }
            else
            {
                Console.Write(-1);
            }
        }
    }
}
