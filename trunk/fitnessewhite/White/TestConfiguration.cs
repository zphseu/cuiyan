using System;
using System.Diagnostics;
using Core.Factory;

namespace Core
{
    public abstract class TestConfiguration
    {
        public static string WPFTestAppLocation = @"..\WPFTestApp\bin\debug\WindowsPresentationFramework.exe";
        public static string WinFormsTestAppLocation = @"..\WinFormsTestApp\bin\debug\WinFormsTestApp.exe";

        public static string SWTTestAppLocation = @"java";

        private readonly string program;
        protected string commandLineArguments;
        private readonly InitializeOption windowInitializeOption;

        protected TestConfiguration(string program, string commandLineArguments)
        {
            this.program = program;
            this.commandLineArguments = commandLineArguments;
            windowInitializeOption = InitializeOption.NoCache.AndIdentifiedBy("Form1");
        }

        public virtual Application Launch()
        {
            ProcessStartInfo processStartInfo = new ProcessStartInfo();
            processStartInfo.WorkingDirectory = WorkingDir;
            processStartInfo.FileName = program;
            processStartInfo.Arguments = commandLineArguments.Trim();
            processStartInfo.UseShellExecute = false;
            processStartInfo.CreateNoWindow = true;
            return Application.Launch(processStartInfo);
        }

        protected virtual string WorkingDir
        {
            get { return Environment.CurrentDirectory; }
        }

        public virtual InitializeOption WindowInitializeOption
        {
            get { return windowInitializeOption.AndIdentifiedBy("Form1"); }
        }
    }

    public class WPFTestConfiguration : TestConfiguration
    {
        public WPFTestConfiguration(string commandLineArguments) : base(WPFTestAppLocation, commandLineArguments) {}
    }

    public class WinFormTestConfiguration : TestConfiguration
    {
        public WinFormTestConfiguration(string commandLineArguments) : base(WinFormsTestAppLocation, commandLineArguments) {}
    }

    public class SWTTestConfiguration : TestConfiguration
    {
        public SWTTestConfiguration(string commandLineArguments)
            : base(
                SWTTestAppLocation,
                @" -classpath SampleSWTApp\bin;""%classpath%"";SampleSWTApp\org.eclipse.swt.win32.win32.x86_3.2.1.v3235.jar -Djava.library.path=SampleSWTApp Program " +
                commandLineArguments) {}

        protected override string WorkingDir
        {
            get { return @".."; }
        }
    }
}