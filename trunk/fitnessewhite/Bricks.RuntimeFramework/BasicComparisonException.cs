using System;

namespace Bricks.RuntimeFramework
{
    public class BasicComparisonException : Exception
    {
        public BasicComparisonException(string message): base(message){}
    }

    public class NullComparisonException : Exception
    {
        public NullComparisonException(string message) : base(message) { }
    }

    public class TypeMismatchException : Exception
    {
        public TypeMismatchException(string message) : base(message) { }
    }
}