using System.Collections.Generic;
using System.Windows.Automation;
using Core.AutomationElementSearch;
using Core.Factory;
using Core.InputDevices;
using Core.Sessions;
using Core.UIItems;
using Core.UIItems.Actions;
using Core.UIItems.ListBoxItems;
using Core.UIItems.WindowItems;

namespace Core
{
    public class Desktop : UIItemContainer
    {
        public static Desktop Instance = Create();

        private static Desktop Create()
        {
            return new Desktop(AutomationElement.RootElement, new NullActionListener(), InitializeOption.NoCache, new NullWindowSession());
        }

        private readonly AutomationElementFinder finder;

        public Desktop(AutomationElement automationElement, ActionListener actionListener, InitializeOption initializeOption, WindowSession windowSession)
            : base(automationElement, actionListener, initializeOption, windowSession)
        {
            finder = new AutomationElementFinder(automationElement);
        }

        public virtual ListItems Icons
        {
            get { return IconsList.Items; }
        }

        private ListControl IconsList
        {
            get
            {
                AutomationElement element =
                    finder.Child(
                        new AutomationSearchCondition[]
                            {
                                AutomationSearchCondition.ByControlType(ControlType.Pane).OfName("Program Manager"),
                                AutomationSearchCondition.ByControlType(ControlType.List).OfName("Desktop")
                            });
                return new ListControl(element, new ProcessActionListener(element));
            }
        }

        public virtual void Drop(UIItem uiItem)
        {
            Mouse.Instance.DragAndDrop(uiItem, IconsList);
        }

        public virtual List<Window> Windows()
        {
            return WindowFactory.Desktop.DesktopWindows();
        }
    }
}