using fitnessewhite;

namespace Sample
{
    public class Calctest : Guifixture
    {
        public object Run()
        {
            doCmd("Button", "ClickByText", "9");
            doCmd("Button", "ClickByText", "*");
            doCmd("Button", "ClickByText", "7");
            doCmd("Button", "ClickByText", "=");
            doCmd("Textbox", "GetById", "403");
            return doCmd("Textbox", "Text", "");
        }
    }
}

