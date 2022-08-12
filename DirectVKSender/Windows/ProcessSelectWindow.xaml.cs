using System;
using System.Collections.Generic;
using System.Diagnostics;
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
using System.Windows.Shapes;

namespace DirectVKSender
{

    public partial class ProcessSelectWindow : Window
    {
        private Process _selectedProcess = null;
        private List<Process> _runningProcessList = new List<Process>();

        public Process SelectedProcess => _selectedProcess;
        public ProcessSelectWindow()
        {
            InitializeComponent();
            UpdateProcessList();
        }

        private void UpdateProcessList()
        {
            _runningProcessList.Clear();

            foreach (var proc in Process.GetProcesses())
            {
                // 윈도우 핸들이 존재하는 것만..
                if (proc.MainWindowHandle != IntPtr.Zero && proc.ProcessName.Contains(_searchtb.Text))
                    _runningProcessList.Add(proc);
            }

            _wndProcessList.ItemsSource = _runningProcessList;
            _wndProcessList.Items.Refresh();
        }

        private void _wndProcessList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (_wndProcessList.SelectedIndex < 0)
                return;

            _selectedProcess = (Process)_wndProcessList.SelectedItem;
        }

        private void _searchbtn_Click(object sender, RoutedEventArgs e)
        {
            UpdateProcessList();
        }

        private void _wndProcessList_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            if (_selectedProcess == null)
                return;

            Close();

        }

        private void _searchtb_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                UpdateProcessList();
            }
        }

        private void _refreshbtn_Click(object sender, RoutedEventArgs e)
        {
            _searchtb.Text = string.Empty;
            UpdateProcessList();
        }
    }
}
