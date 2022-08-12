/*
 * 작성자 : 윤정도
 * 설명 : VK 키코드 확인 및 원하는 윈도우 기반 프로세스에 키코드를 전송할 수 있도록 하자.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Security.Principal;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace DirectVKSender
{

    /*
     * https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-keydown
     * WM_KEYDOWN lParam 구조
     * 0-15	    The repeat count for the current message. The value is the number of times the keystroke is autorepeated as a result of the user holding down the key. If the keystroke is held long enough, multiple messages are sent. However, the repeat count is not cumulative.
     * 16-23    The scan code. The value depends on the OEM.
     * 24	    Indicates whether the key is an extended key, such as the right-hand ALT and CTRL keys that appear on an enhanced 101- or 102-key keyboard. The value is 1 if it is an extended key; otherwise, it is 0.
     * 25-28    Reserved; do not use.
     * 29	    The context code. The value is always 0 for a WM_KEYDOWN message.
     * 30	    The previous key state. The value is 1 if the key is down before the message is sent, or it is zero if the key is up.
     * 31	    The transition state. The value is always 0 for a WM_KEYDOWN message.
     */
    public class WndProcMessage
    {
        public string? Text { get; set; }
        public IntPtr WParam { get; set; }
        public IntPtr LParam { get; set; }

        public int ScanCode { get; set; }
        public int RepeatCount { get; set; }
        public int PreviousKeyState { get; set; }
        public int Extended { get; set; }
    }

    public partial class MainWindow : Window
    {
        private int                 _maxLogCount    = 200;
        private WndProcMessage?     _lastWndMsg;
        private Process?            _selectedWndProcess;


        public MainWindow()
        {
            InitializeComponent();

            bool isElevated = false;

            using (WindowsIdentity identity = WindowsIdentity.GetCurrent())
            {
                WindowsPrincipal principal = new WindowsPrincipal(identity);
                isElevated = principal.IsInRole(WindowsBuiltInRole.Administrator);
            }

            if (isElevated == false)
            {
                MessageBox.Show("관리자 권한으로 실행해주세요");
                Application.Current.Shutdown();
            }
        }


        protected override void OnSourceInitialized(EventArgs e)
        {
            base.OnSourceInitialized(e);
            HwndSource? source = PresentationSource.FromVisual(this) as HwndSource;

            if (source == null)
                throw new Exception("Cannot find HwndSource");

            source.AddHook(WndProc);
        }


        private IntPtr WndProc(IntPtr hwnd, int msgCode, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            switch (msgCode)
            {
                case WindowsMessage.WM_KEYDOWN:
                case WindowsMessage.WM_KEYUP:
                    AddLog(msgCode, wParam, lParam);
                    break;
            }

            return IntPtr.Zero;
        }

        private void AddLog(int msgCode, IntPtr wParam, IntPtr lParam)
        {
            if (_logListBox.Items.Count >= _maxLogCount)
                _logListBox.Items.RemoveAt(0);

            long wLongParam = wParam.ToInt64();
            long lLongParam = lParam.ToInt64();

            _lastWndMsg = new WndProcMessage();
            _lastWndMsg.WParam = wParam;
            _lastWndMsg.LParam = lParam;

            _lastWndMsg.RepeatCount         = (int)(lLongParam & 0x0000ffff);
            _lastWndMsg.ScanCode            = (int)(lLongParam & 0x00ff0000);
            _lastWndMsg.Extended            = (int)(lLongParam & (1 << 24)) >> 24;
            _lastWndMsg.PreviousKeyState    = (int)(lLongParam & (1 << 31)) >> 31;

            _lastWndMsg.Text = string.Format("{0}, {1}, wParam: 0x{2:X8}, lParam: 0x{3:X8}, Ext: {4:D}, Rep: {5}",
                    WindowsMessage.GetName(msgCode), (VirtualKey)wLongParam, wLongParam, lLongParam, _lastWndMsg.Extended, _lastWndMsg.RepeatCount);
            _logListBox.Items.Add(_lastWndMsg);
            _logListBox.ScrollIntoView(_lastWndMsg);
        }

        private void _selectProcessBtn_Click(object sender, RoutedEventArgs e)
        {
            var selectProcessWindow = new ProcessSelectWindow();

            if (selectProcessWindow.ShowDialog().HasValue && selectProcessWindow.SelectedProcess != null)
            {
                _selectedWndProcess = selectProcessWindow.SelectedProcess;
                _selectedProcessImg.Source = new ProcessFileNameToIconConverter().Convert(_selectedWndProcess.MainModule.FileName, null, null, null) as BitmapSource;
                _selectedProcesstb.Text = _selectedWndProcess.ProcessName;
            }
        }

        private void _sendMessageBtn_Click(object sender, RoutedEventArgs e)
        {
            if (_selectedWndProcess == null)
            {
                MsgBox.ShowTopMost("프로세스를 먼저 선택해주세요.");
                return;
            }

            if (!_selectedWndProcess.IsRunning())
            {
                MsgBox.ShowTopMost("프로세스가 실행중이지 않습니다. 다시 선택해주세요.");
                return;
            }

            ProcessHijacker.InjectDLL(_selectedWndProcess.Id);
        }

        private void _postMessageBtn_Click(object sender, RoutedEventArgs e)
        {
            if (_selectedWndProcess == null)
            {
                MsgBox.ShowTopMost("프로세스를 먼저 선택해주세요.");
                return;
            }

            if (!_selectedWndProcess.IsRunning())
            {
                MsgBox.ShowTopMost("프로세스가 실행중이지 않습니다. 다시 선택해주세요.");
                return;
            }

            ProcessHijacker.EjectDLL(_selectedWndProcess.Id);
        }

        private void _saveLogBtn_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
