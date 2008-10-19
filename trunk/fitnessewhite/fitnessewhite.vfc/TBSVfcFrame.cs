using System;
using System.IO;
using System.Collections.Generic;
using System.Threading;
using Core;
using Core.Factory;
using Core.UIItems;
using Core.UIItems.Finders;
using Core.UIItems.WindowItems;

namespace fitnessewhite
{
    class TBSVfcFrame : Guifixture
    {
        const int TimeDelay = 500; //miSec
        private string FileName()
        {
            return string.Format("{0}Fit.White.BSVfcFrame-{1}.tmp", 
                System.IO.Path.GetTempPath(), Guifixture.Process.Id);
        }

        [MethodAttribute("启动模块，参数为:模块全路径名;启动后窗口名称")]
        public void Launch(string name)
        {
        	string[] items = SplitString(name);
			
	       	if (items.Length < 2)
                throw new ArgumentException("param format: 模块全路径名;启动后窗口名称...");
	        	
            StreamWriter output = new StreamWriter(FileName(), true);
            output.WriteLine("Launch");
            output.WriteLine(items[0]);
            output.Close();
            Thread.Sleep(TimeDelay);
            uitemcontainer = mainwin.MdiChild(SearchCriteria.ByText(items[1]));
        }

        [MethodAttribute("获取主窗口")]
        public void GetMainWindow()
        {
            List<Window> wins = application.GetWindows();
            if (wins.Count == 1)
            {
                mainwin = wins[0];
                uitemcontainer = mainwin;
                return;
            }
            else if (wins.Count > 1)
            {
                foreach (Window w in wins)
                {
                    if (!w.Name.Trim().StartsWith("iCentroView")) continue;
                    mainwin = w;
                    uitemcontainer = mainwin;
                    return;
                }
            }
            
            throw new UIActionException("未发现主窗口");
        }

        public void DeleteFile()
        {
            File.Delete(FileName());
        }
    }
}
