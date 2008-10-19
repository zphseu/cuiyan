using Bricks.RuntimeFramework;

namespace Bricks.RuntimeFramework
{
    public interface Markable
    {
        bool IsProcessed { get; set; }
        ComparisonStatus ComparisonStatus { get; set; }
    }
}