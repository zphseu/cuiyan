/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-5-30
 * Time: 8:41
 */
using Core;

namespace fitnessewhite
{
	/// <summary>
	/// Description of White.Application.
	/// </summary>
    public sealed class TApplication : Guifixture
	{
        [MethodAttribute("启动指定的应用程序，参数为应用程序的全路径名，如VFC的全路径名为：C:\\Baosight\\CV4PEC\\Client\\VFC2000.exe")]
        static public void Launch(string executable)
        {
			application = Application.Launch(executable);
        }

        [MethodAttribute("附上已经启动的应用程序，参数为应用程序的名称，如VFC的名称为：VFC2000")]
        static public void Attach(string executable)
        {
            application = Application.Attach(executable);
        }
        
        /// <summary>
        /// Kills the applications and waits till it is closed
        /// </summary>
        [MethodAttribute("关闭应用程序")]
        static public void Kill()
        {
			if (application != null)
				application.Kill();
		}

        [MethodAttribute("返回应用程序包含的窗口个数")]
        static public int WindowsCount()
        {
            return application.GetWindows().Count;
        }

        [MethodAttribute("返回应用程序的名称")]
        static public string Name()
        {
            return application.Process.ProcessName;
        }

        /// <summary>
        /// Waits till application is busy.
        /// </summary>
        [MethodAttribute("等待直到应用程序忙")]
        static public void WaitWhileBusy()
        {
        	application.WaitWhileBusy();
        }

        [MethodAttribute("返回是否当前应用已被附上")]
        static public bool IsAttached()
        {
        	return application != null;
        }
	}
}