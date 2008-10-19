using System.IO;
using Bricks.DynamicProxy;
using Core.UIItems;

namespace Core.Configuration
{
    /// <summary>
    /// Represents all the configuration at Core level. These configuration can be set from the configuration file as well as programmatically.
    /// </summary>
    public interface CoreConfiguration
    {
        int BusyTimeout { get; set; }
        bool WaitBasedOnHourGlass { get; set; }
        DynamicProxyInterceptors Interceptors { get; }
        DirectoryInfo WorkSessionLocation { get; set; }
        int UIAutomationZeroWindowBugTimeout { get; set; }
        int PopupTimeout { get; set; }
        int TooltipWaitTime { get; set; }
        int SuggestionListTimeout { get; set; }
        DateFormat DefaultDateFormat { get; set; }
        int DragStepCount { get; }
        bool LogActions { get; set; }
        bool InProc { get; set; }
    }
}