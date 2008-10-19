using System;

namespace Core
{
    public class AutomationException : Exception
    {
        public AutomationException(string message) : base(message) {}
    }
}