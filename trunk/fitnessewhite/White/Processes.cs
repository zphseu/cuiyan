using System.Collections.Generic;
using System.Diagnostics;

namespace Core
{
    public class Processes : List<Process>
    {
        public Processes(Process[] processes)
        {
            foreach (Process process in processes)
                Add(process);
        }
    }
}