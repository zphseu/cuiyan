using System;
using System.Collections.Generic;
using System.Text;

namespace fitnessewhite
{
    // Define a custom attribute with one named parameter.
    [AttributeUsage(AttributeTargets.Method, AllowMultiple = false)]
    public class MethodAttribute : Attribute
    {
        private string myName;
        public MethodAttribute(string name)
        {
            myName = name;
        }

        public string Name
        {
            get
            {
                return myName;
            }
        }
    }
}
