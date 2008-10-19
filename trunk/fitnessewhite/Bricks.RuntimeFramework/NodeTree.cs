using System;
using System.Collections.Generic;

namespace Bricks.RuntimeFramework
{
    public class NodeTree
    {
        public Node Root { get; private set; }

        public NodeTree(ReflectedObject reflecetedObject)
        {
            Root = (reflecetedObject != null) ? new Node(reflecetedObject.O.GetType().Name, reflecetedObject.O) : new PrimitiveNode("NULL", "NULL");
        }
    }

    public class Nodes : List<Node> {}

    public class Node
    {
        public string Name { get; private set; }
        public string Value { get; set; }
        protected Node() {}

        public Nodes Nodes { get; private set; }

        public Node(string name, object o)
        {
            Name = name;
            Nodes = new Nodes();
            Value = (o != null) ? o.ToString() : "<NULL>";
        }

        public void Add(Node node)
        {
            Nodes.Add(node);
        }
    }

    public class PrimitiveNode : Node
    {
        public PrimitiveNode(string name, object value) : base(name, value) {}

        public new string Name
        {
            get { return Name; }
        }
    }

    public class CircularNode : Node
    {
        public CircularNode(string name, object o) : 
            base(name, String.Format("{0} : <{1}>","Circular Reference Occoured", o)) { }
    }
}