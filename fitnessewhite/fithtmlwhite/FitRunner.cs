using fit;

namespace fitnessewhite
{
    public class FitRunner : FileRunner
    {
        protected override void exit()
        {
            output.Close();
        }
    }
}
