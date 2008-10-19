using System.Windows;

namespace Core
{
    /// <summary>
    /// This class is for internal use in white
    /// </summary>
    public class C
    {
        public static readonly Point TopLeftPoint = new Point(0, 0);
        public static readonly Point UnlikelyWindowPosition = new Point(-10000, -10000);

        public static System.Drawing.Point BottomRight(Rect rectangle)
        {
            return new System.Drawing.Point((int) rectangle.Right, (int) rectangle.Bottom);
        }

        public static System.Drawing.Point Center(Rect rectangle)
        {
            return
                new System.Drawing.Point((int) (rectangle.Left + (rectangle.Right - rectangle.Left)/2),
                                         (int) (rectangle.Top + (rectangle.Bottom - rectangle.Top)/2));
        }

        public static Point ImmediateExteriorEast(Rect rectangle)
        {
            return new Point((int) (rectangle.Right + 1), Center(rectangle).Y);
        }

        public static Point ImmediateInteriorNorth(Rect rectangle)
        {
            return new Point(Center(rectangle).X, rectangle.Top + 1);
        }

        public static System.Drawing.Point ImmediateInteriorEast(Rect rectangle)
        {
            return new System.Drawing.Point((int) (rectangle.Right - 1), Center(rectangle).Y);
        }

        public static System.Drawing.Point Convert(Point point)
        {
            return new System.Drawing.Point((int) point.X, (int) point.Y);
        }

        public static Point Convert(System.Drawing.Point point)
        {
            return new Point(point.X, point.Y);
        }

        public static System.Drawing.Point ImmediateExteriorWest(Rect rect)
        {
            return new System.Drawing.Point((int) (rect.Left - 1), Center(rect).Y);
        }

        public static Point TopLeft(Rect rectangle)
        {
            return rectangle.TopLeft;
        }

        public static Point ImmediateInteriorSouth(Rect rectangle)
        {
            return new Point(Center(rectangle).X, rectangle.Bottom - 1);
        }
    }
}