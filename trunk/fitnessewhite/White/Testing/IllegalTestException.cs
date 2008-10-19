using System;

namespace Core.Testing
{
    public class IllegalTestException : Exception
    {
        public IllegalTestException(string message) : base(message) {}
    }
}