using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Win32;

namespace BMP_converter
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        BitmapImage sourceImage;
        byte[] pixels = null;
        public MainWindow()
        {
            InitializeComponent();
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openfiledialog = new OpenFileDialog();

            openfiledialog.Title = "Open Image";
            openfiledialog.Filter = "Image File|*.bmp;";

            if (openfiledialog.ShowDialog() == true)
            {
                sourceImage = new BitmapImage(new Uri(openfiledialog.FileName));

                int stride = sourceImage.PixelWidth * 4;
                int size = sourceImage.PixelHeight * stride;
                byte[] pixels = new byte[size];
                sourceImage.CopyPixels(pixels, stride, 0);

                byte[] byteArray = new byte[size / 4];

                int imageWidth = sourceImage.PixelWidth;
                int imageHeight = sourceImage.PixelHeight;
                int nmbOfBytePixels = size / 4;

                for (int i = 0; i < (size / 4); i++)
                {
                    byteArray[i] = pixels[i * 4];
                    // 0 - black
                    // 255 - white
                }

                string c_struct = "const gl_type::image_t img_xxx = {\r\n\t";

                c_struct += ".width = " + imageWidth.ToString() + ",\r\n\t";
                c_struct += ".height = " + imageHeight.ToString() + ",\r\n\t";
                c_struct += ".data = {\r\n\t\t";

                int col_idx = 0;
                for (int i = 0; i < nmbOfBytePixels; i++)
                {
                    c_struct += "0x";
                    c_struct += (byteArray[i]).ToString("X2");
                    if (i != nmbOfBytePixels - 1)
                    {
                        c_struct += ", ";
                    }
                   
                    col_idx++;

                    if (col_idx == 8)
                    {
                        col_idx = 0;
                        c_struct += "\r\n";
                        if (i != nmbOfBytePixels - 1)
                        {
                            c_struct += "\t\t";
                        }
                    }

                    if (i == nmbOfBytePixels - 1)
                    {
                        c_struct += "\r\n\t";
                    }
                }

                c_struct += "}\r\n";
                c_struct += "};";

                GeneratedCodeTB.Text = c_struct;
            }
        }
    }
}
