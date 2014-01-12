using System;
using System.Text.RegularExpressions;

namespace FepManager
{
    internal class HelperRegex
    {
        static public Boolean IsHostName(String input)
        {
            // http://www.luwei.net.cn/view/df2409ebfd8fe1a9614c9a19
            // hostname modify + to * because computer name.
            Regex rex = new Regex(@"^[a-zA-Z0-9][-a-zA-Z0-9]{0,62}(\.[a-zA-Z0-9][-a-zA-Z0-9]{0,62})*\.?$", RegexOptions.Singleline);
            return rex.IsMatch(input);
        }

        static public Boolean IsIpAddress(String input)
        {
            // http://www.luwei.net.cn/view/df2409ebfd8fe1a9614c9a19
            Regex rex = new Regex(@"^((25[0-5])|(2[0-4]\d)|(1\d\d)|([1-9]\d)|\d)(\.((25[0-5])|(2[0-4]\d)|(1\d\d)|([1-9]\d)|\d)){3}$", RegexOptions.Singleline);
            return rex.IsMatch(input);
        }

        static public Boolean IsInt(String input)
        {
            Regex rex = new Regex(@"^\d+$", RegexOptions.Singleline);
            return rex.IsMatch(input);
        }

        static public Boolean IsRange(Int64 v, int min, int max)
        {
            return (v >= min) && (v <= max);
        }

        static public Boolean IsDevName(String input)
        {
            Regex rex = new Regex(@"^[a-zA-Z][_a-zA-Z0-9]{0,62}$", RegexOptions.Singleline);
            return rex.IsMatch(input);
        }

        static public Int32 Str2Int(String input, Int32 def)
        {
            Int32 ret;
            try
            {
                ret = Int32.Parse(input);
            }
            catch
            {
                ret = def;
            }
            return ret;
        }
    }
}
