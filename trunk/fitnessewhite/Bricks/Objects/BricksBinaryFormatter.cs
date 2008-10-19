using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace Bricks.Objects
{
    public class BricksBinaryFormatter
    {
        public static byte[] ToByteArray(object obj)
        {
            using (MemoryStream stream = new MemoryStream())
            {
                BinaryFormatter formatter = new BinaryFormatter();
                formatter.Serialize(stream, obj);
                return stream.ToArray();
            }
        }

        public static object ToObject(byte[] bytes)
        {
            using (MemoryStream stream = new MemoryStream(bytes))
                return new BinaryFormatter().Deserialize(stream);
        }
    }
}