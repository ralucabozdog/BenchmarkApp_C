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
using System.Runtime.InteropServices;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        [DllImport("SSCLibrary", SetLastError = true)]
        static extern IntPtr processorManufacturerSignature();

        [DllImport("SSCLibrary", SetLastError = true)]
        static extern IntPtr brandString();

        [DllImport("SSCLibrary", SetLastError = true)]
        static extern IntPtr processorFeaturesAndModel();

        [DllImport("SSCLibrary", SetLastError = true)]
        static extern IntPtr frequencyInfo();

        [DllImport("SSCLibrary", SetLastError = true)]
        static extern IntPtr systemInfoProcessor();

        [DllImport("SSCLibrary", SetLastError = true)]
        static extern IntPtr systemInfoMemory();

        [DllImport("SSCLibrary", SetLastError = true)]
        static extern IntPtr cacheFeaturesL2();

        [DllImport("SSCLibrary", SetLastError = true)]
        static extern IntPtr virtualAndPhysicalAddrSize();

        public static string[] returnStringArrayProcessorFeaturesAndModel()
        {
            string[] ReturnArray = new string[10];
            for (int j = 0; j < 6; j++)
                ReturnArray[j] = Marshal.PtrToStringAnsi(Marshal.ReadIntPtr(processorFeaturesAndModel(), 4 * j));
            return ReturnArray;
        }

        public static int[] returnIntArrayfrequencyInfo()
        {
            int[] ReturnArray = new int[3];
            for (int j = 0; j < 3; j++)
                ReturnArray[j] = Marshal.ReadIntPtr(frequencyInfo(), 4 * j).ToInt32();
            return ReturnArray;
        }

        public static int[] returnIntArraySystemInfoProcessor()
        {
            int[] ReturnArray = new int[4];
            for (int j = 0; j < 4; j++)
                ReturnArray[j] = Marshal.ReadIntPtr(systemInfoProcessor(), 4 * j).ToInt32();
            return ReturnArray;
        }

        public static int[] returnIntArraySystemInfoMemory()
        {
            int[] ReturnArray = new int[4];
            for (int j = 0; j < 4; j++)
                ReturnArray[j] = Marshal.ReadIntPtr(systemInfoMemory(), 4 * j).ToInt32();
            return ReturnArray;
        }

        public static string[] returnStringArrayCacheFeaturesL2()
        {
            string[] ReturnArray = new string[3];
            for (int j = 0; j < 3; j++)
                ReturnArray[j] = Marshal.PtrToStringAnsi(Marshal.ReadIntPtr(cacheFeaturesL2(), 4 * j));
            return ReturnArray;
        }

        public static int[] returnIntArrayvirtualAndPhysicalAddrSize()
        {
            int[] ReturnArray = new int[2];
            for (int j = 0; j < 2; j++)
                ReturnArray[j] = Marshal.ReadIntPtr(virtualAndPhysicalAddrSize(), 4 * j).ToInt32();
            return ReturnArray;
        }

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (sender.Equals(button0))
            {
                Page0 page0 = new Page0();
                page0.Show();
            }
            if (sender.Equals(button1))
            {
                Page1 page1 = new Page1(System.Runtime.InteropServices.Marshal.PtrToStringAnsi(processorManufacturerSignature()));
                page1.Show();
            }
            if (sender.Equals(button2))
            {
                Page2 page2 = new Page2(System.Runtime.InteropServices.Marshal.PtrToStringAnsi(brandString()));
                page2.Show();
            }
            if (sender.Equals(button3))
            {
                string[] res = returnStringArrayProcessorFeaturesAndModel();
                
                Page3 page3 = new Page3(res[0], res[1], res[2], res[3], res[4], res[5]);
                page3.Show();
            }
            if (sender.Equals(button4))
            {
                int[] res = returnIntArrayfrequencyInfo();

                Page4 page4 = new Page4(res[0], res[1], res[2]);
                page4.Show();
            }
            if (sender.Equals(button5))
            {
                int[] res = returnIntArraySystemInfoProcessor();

                Page5 page5 = new Page5(res[0], res[1], res[2], res[3]);
                page5.Show();
            }
            if (sender.Equals(button6))
            {
                int[] res = returnIntArraySystemInfoMemory();

                Page6 page6 = new Page6(res[0], res[1], res[2], res[3]);
                page6.Show();
            }
            if (sender.Equals(button7))
            {
                Page7 page7 = new Page7();
                page7.Show();
            }
            if (sender.Equals(button8))
            {
                string[] res = returnStringArrayCacheFeaturesL2();

                Page8 page8 = new Page8(res[0], res[1], res[2]);
                page8.Show();
            }
            if (sender.Equals(button9))
            {
                int[] res = returnIntArrayvirtualAndPhysicalAddrSize();

                Page9 page9 = new Page9(res[0], res[1]);
                page9.Show();
            }
            if (sender.Equals(button10))
            {
                Page10 page10 = new Page10();
                page10.Show();
            }
            if (sender.Equals(button11))
            {
                Page11 page11 = new Page11();
                page11.Show();
            }
            if (sender.Equals(button12))
            {
                Page12 page12 = new Page12();
                page12.Show();
            }
            if (sender.Equals(button13))
            {
                Page13 page13 = new Page13();
                page13.Show();
            }
            if (sender.Equals(button14))
            {
                Page14 page14 = new Page14();
                page14.Show();
            }
        }
    }
}
