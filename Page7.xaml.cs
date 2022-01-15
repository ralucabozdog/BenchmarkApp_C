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
    public partial class Page7 : Window
    {
        [DllImport("SSCLibrary", SetLastError = true)]
        static extern IntPtr wrapperDeterministicCacheParameters();

        public struct MyData
        {
            public string cacheInfo { set; get; }
            public string info1 { set; get; }
            public string info2 { set; get; }
            public string info3 { set; get; }
            public string info4 { set; get; }
        }

        public static string[] returnStringArray()
        {
            string[] ReturnArray = new string[52];
            for (int j = 0; j < 52; j++)
                ReturnArray[j] = Marshal.PtrToStringAnsi(Marshal.ReadIntPtr(wrapperDeterministicCacheParameters(), 4 * j));
            return ReturnArray;
        }

        public Page7()
        {
            InitializeComponent();
            string[] res = returnStringArray();
            dataGrid.Items.Add(new MyData { cacheInfo = "Cache type", info1 = res[0], info2 = res[13], info3 = res[26], info4 = res[39] });
            dataGrid.Items.Add(new MyData { cacheInfo = "Cache level", info1 = res[1], info2 = res[14], info3 = res[27], info4 = res[40] });
            dataGrid.Items.Add(new MyData { cacheInfo = "Number of processor cores in this physical processor package", info1 = res[2], info2 = res[15], info3 = res[28], info4 = res[41] });
            dataGrid.Items.Add(new MyData { cacheInfo = "Number of threads sharing this cache", info1 = res[3], info2 = res[16], info3 = res[29], info4 = res[42] });
            dataGrid.Items.Add(new MyData { cacheInfo = "Fully associative cache", info1 = res[4], info2 = res[17], info3 = res[30], info4 = res[43] });
            dataGrid.Items.Add(new MyData { cacheInfo = "Self initializing cache level", info1 = res[5], info2 = res[18], info3 = res[31], info4 = res[44] });

            dataGrid.Items.Add(new MyData { cacheInfo = "Ways of associativity", info1 = res[6], info2 = res[19], info3 = res[32], info4 = res[45] });
            dataGrid.Items.Add(new MyData { cacheInfo = "Physical line partitions", info1 = res[7], info2 = res[20], info3 = res[33], info4 = res[46] });
            dataGrid.Items.Add(new MyData { cacheInfo = "System coherency line size", info1 = res[8], info2 = res[21], info3 = res[34], info4 = res[47] });

            dataGrid.Items.Add(new MyData { cacheInfo = "Number of sets", info1 = res[9], info2 = res[9], info3 = res[35], info4 = res[48] });

            dataGrid.Items.Add(new MyData { cacheInfo = "Complex cache indexing", info1 = res[10], info2 = res[23], info3 = res[36], info4 = res[49] });
            dataGrid.Items.Add(new MyData { cacheInfo = "Cache is inclusive of lower cache levels", info1 = res[11], info2 = res[24], info3 = res[37], info4 = res[50] });

            dataGrid.Items.Add(new MyData { cacheInfo = "Cache size (MB)", info1 = res[12], info2 = res[25], info3 = res[38], info4 = res[51] });
        }

        /*public static void thread1()
        {
            Running runningPage = new Running();
            runningPage.Show();
            Dispatcher.Run();
        }*/

        /*public static void thread2(Page10 page10, Thread t1)
        {
            int nb_tests = Int32.Parse(page10.textBox.Text.ToString());
            double[] res = returnDoubleArray(nb_tests);

            for (int j = 0; j < 2 * nb_tests; j = j + 2)
            {
                page10.dataGrid.Items.Add(new MyData { id = (j / 2 + 1).ToString(), time = res[j], instr_sec = res[j + 1] });
            }
            page10.dataGrid.Items.Add(new MyData { id = "AVERAGE", time = res[2 * nb_tests], instr_sec = res[2 * nb_tests + 1] });

            t1.Abort();
        }*/
    }
}
