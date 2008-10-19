namespace Bricks.RuntimeFramework
{
    public interface ObjectVisitor
    {
        void Accept(Field field);
    }
}