namespace Bricks.RuntimeFramework
{
    public interface ConflictResolver {
         object Resolve(ReflectedObject original, Field originalField, ReflectedObject other, Field otherField, ReflectedObject mine, Field myField);
    }

    public class UseMine : ConflictResolver
    {
        public object Resolve(ReflectedObject original, Field originalField, ReflectedObject other, Field otherField, ReflectedObject mine, Field myField)
        {
            return myField.Value;
        }
    }

    public class UseOther : ConflictResolver
    {
        public object Resolve(ReflectedObject original, Field originalField, ReflectedObject other, Field otherField, ReflectedObject mine, Field myField)
        {
            return otherField.Value;
        }
    }

    public class UseOriginal : ConflictResolver
    {
        public object Resolve(ReflectedObject original, Field originalField, ReflectedObject other, Field otherField, ReflectedObject mine, Field myField)
        {
            return originalField.Value;
        }
    }
}