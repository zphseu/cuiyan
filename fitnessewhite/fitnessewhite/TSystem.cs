/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-5-30
 * Time: 9:23
 */

using System;

namespace fitnessewhite
{
	/// <summary>
	/// Description of White.System.
	/// </summary>
	public sealed class TSystem : Guifixture
	{
        [MethodAttribute("拷贝文件，参数格式：源文件地址;目标文件地址")]	
        static public void CopyFile(string value)
        {
            string[] items = SplitString(value);

            if (items.Length > 1)
                System.IO.File.Copy(items[0], items[1], true);
            else
                throw new ArgumentException("param format: sourceFile;dstFile");
        }

        [MethodAttribute("延时，参数为毫秒")]	
        static public void Sleep(int miSec)
        {
            System.Threading.Thread.Sleep(miSec);
        }
	}
}
