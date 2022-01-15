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
using System.Threading;
using System.Windows.Threading;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for Page1.xaml
    /// </summary>
    public partial class Page0 : Window
    {
        [DllImport("SSCLibrary", SetLastError = true)]
        static extern IntPtr grade_my_pc();

        public struct MyData
        {
            public string info { set; get; }
            public double grade { set; get; }
        }

        public static double[] returnDoubleArray()
        {
            IntPtr intPtr = grade_my_pc();
            double[] ReturnArray = new double[6];
            for (int j = 0; j < 6; j++)
            {
                byte[] ba = new byte[sizeof(double)];


                for (int i = 0; i < ba.Length; i++)
                    ba[i] = Marshal.ReadByte(intPtr, 8 * j + i);

                ReturnArray[j] = BitConverter.ToDouble(ba, 0);
            }

            return ReturnArray;
        }

        public Page0()
        {
            InitializeComponent();

            Thread t1 = new Thread(() => thread1());
            t1.SetApartmentState(ApartmentState.STA);
            t1.Start();

            Dispatcher.BeginInvoke(new ThreadStart(() => thread2(this, t1)));
        }

        public static void thread1()
        {
            Running runningPage = new Running();
            runningPage.Show();
            Dispatcher.Run();
        }

        public static void thread2(Page0 page0, Thread t1)
        {
            double[] res = returnDoubleArray();

            page0.dataGrid.Items.Add(new MyData { info = "Integer processing", grade = res[0] });
            page0.dataGrid.Items.Add(new MyData { info = "Floating-point processing", grade = res[1] });
            page0.dataGrid.Items.Add(new MyData { info = "File access", grade = res[2] });
            page0.dataGrid.Items.Add(new MyData { info = "File read-write operations", grade = res[3] });
            page0.dataGrid.Items.Add(new MyData { info = "Memory access", grade = res[4] });
            page0.dataGrid.Items.Add(new MyData { info = "OVERALL GRADE", grade = res[5] });

            t1.Abort();
        }
    }
}
