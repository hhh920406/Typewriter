using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;

namespace Image_Compress
{
    class Program
    {
        private static ImageCodecInfo GetEncoderInfo(String mimeType)
        {
            int j;
            ImageCodecInfo[] encoders;
            encoders = ImageCodecInfo.GetImageEncoders();
            for (j = 0; j < encoders.Length; ++j)
            {
                if (encoders[j].MimeType == mimeType)
                    return encoders[j];
            }
            return null;
        }

        static void compressImage(string path)
        {
            try
            {
                Bitmap origin = new Bitmap(path);
                int originWidth = origin.Width;
                int originHeight = origin.Height;
                int targetWidth = 720;
                int targetHeight = 540;
                bool flag = false;
                if (originWidth * targetHeight > originHeight * targetWidth)
                {
                    if (originWidth > targetWidth)
                    {
                        targetHeight = originHeight * targetWidth / originWidth;
                        flag = true;
                    }
                }
                else
                {
                    if (originHeight > targetHeight)
                    {
                        targetWidth = originWidth * targetHeight / originHeight;
                        flag = true;
                    }
                }
                if (flag)
                {
                    FileInfo fileInfo = new FileInfo(path);
                    Console.WriteLine("Start compress: " + fileInfo.Name);
                    Console.WriteLine("(" + originWidth + ", " + originHeight + ") => (" + targetWidth + ", " + targetHeight + ")");
                    Console.WriteLine("Origin size:     " + (fileInfo.Length / 1024) + " KB");
                    Bitmap target = new Bitmap(targetWidth, targetHeight);
                    foreach (PropertyItem propitem in origin.PropertyItems)
                    {
                        target.SetPropertyItem(propitem);
                    }
                    for (int x = 0; x < targetWidth; ++x)
                    {
                        for (int y = 0; y < targetHeight; ++y)
                        {
                            int tx = x * originWidth / targetWidth;
                            int ty = y * originHeight / targetHeight;
                            target.SetPixel(x, y, origin.GetPixel(tx, ty));
                        }
                    }
                    origin.Dispose();
                    string extension = fileInfo.Extension.ToLower();
                    if (".jpg" == extension || ".jpeg" == extension)
                    {
                        EncoderParameters ps = new EncoderParameters(1);
                        ps.Param[0] = new EncoderParameter(System.Drawing.Imaging.Encoder.Quality, 90L);
                        target.Save(path, GetEncoderInfo("image/jpeg"), ps);
                    }
                    else
                    {
                        target.Save(path);
                    }
                    target.Dispose();
                    fileInfo = new FileInfo(path);
                    Console.WriteLine("Compressed size: " + (fileInfo.Length / 1024) + " KB");
                    Console.WriteLine();
                }
            }
            catch
            {
                Console.WriteLine("Error: " + path);
            }
            
        }

        static void compress(string path)
        {
            if (File.Exists(path))
            {
                FileInfo file = new FileInfo(path);
                string extension = file.Extension.ToLower();
                if (".jpg" == extension || ".jpeg" == extension || ".png" == extension || ".bmp" == extension)
                {
                    compressImage(path);
                }
            }
            else
            {
                DirectoryInfo dirInfo = new DirectoryInfo(path);
                DirectoryInfo[] dirs = dirInfo.GetDirectories();
                for (int i = 0; i < dirs.Length; ++i)
                {
                    compress(dirs[i].FullName);
                }
                FileInfo[] files = dirInfo.GetFiles();
                for (int i = 0; i < files.Length; ++i)
                {
                    compress(files[i].FullName);
                }
            }
        }

        static void Main(string[] args)
        {
            for (int i = 0; i < args.Length; ++i)
            {
                compress(args[i]);
            }
        }
    }
}
