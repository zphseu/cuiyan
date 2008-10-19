using System;
using System.IO;
using log4net.Config;

namespace Bricks.Logging
{
    public class BricksLogger
    {
        protected BricksLogger()
        {
            string log4netFilePath = ConfigFile();
            if (File.Exists(log4netFilePath))
            {
                FileInfo configFile = new FileInfo(log4netFilePath);
                XmlConfigurator.ConfigureAndWatch(configFile);
            }
            else
                Console.Error.WriteLine("Log4Net not configured. Looked for file: " + new FileInfo(log4netFilePath).FullName);
        }

        protected virtual string ConfigFile()
        {
            return @"log4net.config";
        }
    }
}