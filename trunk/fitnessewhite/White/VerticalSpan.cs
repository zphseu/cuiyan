using System.Windows;

namespace Core
{
    public class VerticalSpan
    {
        private readonly double start;
        private readonly double end;

        public VerticalSpan(Rect bounds) : this(bounds.Top, bounds.Bottom) {}

        public VerticalSpan(double start, double end)
        {
            this.start = start;
            this.end = end;
        }

        public virtual bool IsOutside(Rect rect)
        {
            if (rect.Equals(Rect.Empty)) return true;
            double center = (rect.Top + rect.Bottom)/2;
            if (center == double.PositiveInfinity || center == double.NegativeInfinity || double.IsNaN(center)) return true;
            return center < start || center > end;
        }

        public virtual VerticalSpan Union(Rect rect)
        {
            double newStart = rect.Top < start ? rect.Top : start;
            double newEnd = rect.Bottom > end ? rect.Bottom : end;
            return new VerticalSpan(newStart, newEnd);
        }

        public virtual VerticalSpan Minus(Rect rect)
        {
            if (rect.Top > start && rect.Top < end)
                return new VerticalSpan(start, rect.Top);
            return this;
        }

        public override string ToString()
        {
            return string.Format("Start: {0}, End: {1}", start, end);
        }
    }
}