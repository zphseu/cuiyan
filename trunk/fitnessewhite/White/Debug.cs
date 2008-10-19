using System;
using System.Text;
using System.Windows.Automation;
using Core.Logging;
using Core.UIItems;

namespace Core
{
    public class Debug
    {
        private const string Tab = "  ";

        public static void ProcessDetails(string processName)
        {
            try
            {
                AutomationElement element =
                    AutomationElement.RootElement.FindFirst(TreeScope.Children, new PropertyCondition(AutomationElement.NameProperty, processName));
                Details(element);
            }
            catch (Exception)
            {
                WhiteLogger.Instance.Warn("Error happened while creating error report");
            }
        }

        public static string Details(AutomationElement automationElement)
        {
            try
            {
                StringBuilder stringBuilder = new StringBuilder();
                Details(stringBuilder, automationElement, string.Empty);
                return stringBuilder.ToString();
            }
            catch (Exception)
            {
                WhiteLogger.Instance.Warn("Error happened while creating error report");
                return string.Empty;
            }
        }

        private static void Details(StringBuilder stringBuilder, AutomationElement automationElement, string displayPadding)
        {
            WriteDetail(stringBuilder, automationElement, displayPadding);
            AutomationElementCollection children = automationElement.FindAll(TreeScope.Children, Condition.TrueCondition);
            foreach (AutomationElement child in children)
                Details(stringBuilder, child, displayPadding + Tab + Tab);
        }

        private static void WriteDetail(StringBuilder stringBuilder, AutomationElement automationElement, string displayPadding)
        {
            WriteDetail(stringBuilder, "AutomationId: " + automationElement.Current.AutomationId, displayPadding);
            WriteDetail(stringBuilder, "ControlType: " + automationElement.Current.ControlType.ProgrammaticName, displayPadding);
            WriteDetail(stringBuilder, "Name: " + automationElement.Current.Name, displayPadding);
            WriteDetail(stringBuilder, "HelpText: " + automationElement.Current.HelpText, displayPadding);
            WriteDetail(stringBuilder, "Bounding rectangle: " + automationElement.Current.BoundingRectangle, displayPadding);
            WriteDetail(stringBuilder, "ClassName: " + automationElement.Current.ClassName, displayPadding);
            WriteDetail(stringBuilder, "IsOffScreen: " + automationElement.Current.IsOffscreen, displayPadding);
            stringBuilder.AppendLine();
        }

        private static void WriteDetail(StringBuilder stringBuilder, string message, string padding)
        {
            stringBuilder.AppendLine(padding + message);
        }

        public static string GetAllWindows()
        {
            try
            {
                StringBuilder stringBuilder = new StringBuilder();
                stringBuilder.AppendLine();
                GetAllWindows(stringBuilder, 0, AutomationElement.RootElement);
                return stringBuilder.ToString();
            }
            catch (Exception)
            {
                WhiteLogger.Instance.Warn("Error happened while creating error report");
            }
            return string.Empty;
        }

        private static void GetAllWindows(StringBuilder stringBuilder, int level, AutomationElement baseElement)
        {
            string padding = level == 0 ? string.Empty : Tab;
            PropertyCondition windowCondition = new PropertyCondition(AutomationElement.ControlTypeProperty, ControlType.Window);
            AutomationElementCollection allWindows = baseElement.FindAll(TreeScope.Children, windowCondition);
            foreach (AutomationElement windowElement in allWindows)
            {
                WindowPattern pattern = (WindowPattern) UIItem.Pattern(windowElement, WindowPattern.Pattern);
                stringBuilder.AppendFormat("{0}Name: {1},  Bounds: {2} ProcessId: {3}, Modal: {4}", padding, windowElement.Current.Name,
                                           windowElement.Current.BoundingRectangle, windowElement.Current.ProcessId, pattern.Current.IsModal);
                stringBuilder.AppendLine();

                if (level == 0) GetAllWindows(stringBuilder, 1, windowElement);
            }
        }

        public static void DisplayPattern(AutomationElement automationElement)
        {
//            automationElement.GetCurrentPattern(RangeValuePattern.Pattern)
            AutomationPattern[] supportedPatterns = automationElement.GetSupportedPatterns();
            foreach (AutomationPattern automationPattern in supportedPatterns)
            {
                object pattern = automationElement.GetCurrentPattern(automationPattern);
            }
        }

        public static void LogProperties(AutomationElement element)
        {
            AutomationProperty[] automationProperties = element.GetSupportedProperties();
            foreach (AutomationProperty automationProperty in automationProperties)
            {
                WhiteLogger.Instance.Info(automationProperty.ProgrammaticName + ":" + element.GetCurrentPropertyValue(automationProperty));
            }
        }
    }
}