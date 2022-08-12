using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace DirectVKSender
{
    public static class MsgBox
    {
        public static void ShowTopMost(string msg)
        {
            MessageBox.Show(
                msg,
                "", 
                MessageBoxButton.OK, 
                MessageBoxImage.Exclamation, 
                MessageBoxResult.OK, 
                MessageBoxOptions.DefaultDesktopOnly);
        }
    }
}
