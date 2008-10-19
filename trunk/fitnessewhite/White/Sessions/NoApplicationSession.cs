using Core.Factory;

namespace Core.Sessions
{
    public class NoApplicationSession : ApplicationSession
    {
        public override void Dispose() {}

        public override WindowSession WindowSession(InitializeOption initializeOption)
        {
            return new NullWindowSession();
        }

        public override void Save() {}
    }
}