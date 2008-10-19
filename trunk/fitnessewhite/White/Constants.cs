using Core.Configuration;

namespace Core
{
    public class Constants
    {
        public static readonly string WPFFrameworkId = "WPF";
        public static readonly string WinFormFrameworkId = "WinForm";
        public static readonly string Win32FrameworkId = "Win32";
        public static readonly string MissingFrameworkId = "";
        public static readonly string SWT = "SWT";

        public static string BusyMessage
        {
            get { return ", after waiting for " + CoreAppXmlConfiguration.Instance.BusyTimeout + " ms"; }
        }
    }
}