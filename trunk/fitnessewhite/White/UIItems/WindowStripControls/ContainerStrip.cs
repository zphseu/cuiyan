using System.Windows.Automation;
using Core.Factory;
using Core.Sessions;
using Core.UIItems.Actions;
using Core.UIItems.Finders;

namespace Core.UIItems.WindowStripControls
{
    public class ContainerStrip : UIItemContainer
    {
        protected ContainerStrip() {}

        protected ContainerStrip(AutomationElement element, ActionListener listener)
            : base(element, listener, InitializeOption.NoCache, new NullWindowSession()) {}

        internal virtual InitializeOption Cached
        {
            set { ReInitialize(value); }
        }

        public virtual UIItem GetLabel(string text)
        {
            return Get<TextBox>(SearchCriteria.ByText(text));
        }

        public virtual StatusStripSplitButton GetSplitButton(string name)
        {
            TextBox textBox = Get<TextBox>(SearchCriteria.ByText(name));
            if (textBox == null) return null;
            return new StatusStripSplitButton(textBox);
        }

        public virtual StatusStripDropDownButton GetDropDownButton(string name)
        {
            TextBox textBox = Get<TextBox>(SearchCriteria.ByText(name));
            if (textBox == null) return null;
            return new StatusStripDropDownButton(textBox);
        }

        public virtual ProgressBar GetProgressBar()
        {
            return Get<ProgressBar>(SearchCriteria.ByText(string.Empty));
        }

        public virtual ProgressBar GetProgressBar(int index)
        {
            return Get<ProgressBar>(SearchCriteria.ByText(string.Empty).AndIndex(index));
        }

        internal virtual void Associate(WindowSession session)
        {
            windowSession = session;
        }
    }
}