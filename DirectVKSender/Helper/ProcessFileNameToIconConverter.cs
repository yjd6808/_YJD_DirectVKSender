using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Windows.Media.Imaging;
using System.Drawing.Imaging;

namespace DirectVKSender
{
    // Wpf에서 Bitmap을 Image Source에 바인딩 시키는 방법
    // https://stackoverflow.com/questions/7563552/bind-dynamically-created-bitmap-object-to-image-in-wpf
    public class ProcessFileNameToIconConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var fileName = (string)value;

            if (!File.Exists(fileName))
                return new object();

            Icon? icon = Icon.ExtractAssociatedIcon(fileName);

            if (icon == null)
                return new object();

            // Bitmap을 BitmapSource로 변환
            // https://stackoverflow.com/questions/94456/load-a-wpf-bitmapimage-from-a-system-drawing-bitmap
            Bitmap bitmap = icon.ToBitmap();
            using (MemoryStream memory = new MemoryStream())
            {
                bitmap.Save(memory, ImageFormat.Png);
                memory.Position = 0;
                BitmapImage bitmapImage = new BitmapImage();
                bitmapImage.BeginInit();
                bitmapImage.StreamSource = memory;
                bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
                bitmapImage.EndInit();
                return bitmapImage;
            }
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

}
