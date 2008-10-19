using System.Collections;

namespace Bricks.RuntimeFramework
{
    public class ReflectedObjectVisitor : ObjectVisitor {
        public readonly NodeTree nodeTree;
        private readonly LeafRegistry leafRegister;

        public ReflectedObjectVisitor(ReflectedObject reflectedObject, LeafRegistry leafRegister)
        {
            this.leafRegister = leafRegister;
            if(reflectedObject.O != null)
            {
                nodeTree = new NodeTree(reflectedObject);
                leafRegister.AddLeaf(reflectedObject.O.GetType());
                reflectedObject.Visit(this);
                leafRegister.RemoveLeaf(reflectedObject.O.GetType());    
            }else nodeTree = new NodeTree(null);
        } 

        public ReflectedObjectVisitor(ReflectedObject reflectedObject)
            :this(reflectedObject,new LeafRegistry()){}

        public void Accept(Field field)
        {
            if (field.IsPrimitive())
            {
                AcceptPrimitive(field);
            }else
            {
                if(field.Value as ICollection!=null)
                {
                    AcceptCollection(field);
                }else
                {
                    if(!leafRegister.Contains(field.Type))
                    {
                        AcceptNonPrimitive(field);        
                    } else
                    {
                        AcceptCircularReference(field);
                    }
                }
            }
        }

        private void AcceptCollection(Field field)
        {
            Node node = new Node(field.Name, field.Value);
            
            if(!leafRegister.Contains(field.Type))
            {
                ICollection fieldCollection = field.Value as ICollection;
                if (fieldCollection != null) {
                    IEnumerator fieldEnumerator = fieldCollection.GetEnumerator();
                    while (fieldEnumerator.MoveNext())
                    {
                        ReflectedObject nodeObject = new ReflectedObject(fieldEnumerator.Current);
                        ReflectedObjectVisitor nodeVisitor = new ReflectedObjectVisitor(nodeObject, leafRegister);
                        node.Add(nodeVisitor.nodeTree.Root);
                    }
                }
            }
            nodeTree.Root.Add(node);
        }

        public void AcceptNonPrimitive(Field field)
        {
            Node node = new Node(field.Name,field.Value);
            if(!leafRegister.Contains(field.Type))
            {
                ReflectedObject nodeObject = new ReflectedObject(field.Value);
                ReflectedObjectVisitor nodeVisitor = new ReflectedObjectVisitor(nodeObject, leafRegister);
                nodeVisitor.nodeTree.Root.Nodes.ForEach(node.Add);    
            }else
            {
                AcceptCircularReference(field);
            }
            nodeTree.Root.Add(node);
        }

        private void AcceptCircularReference(Field circularField)
        {
            nodeTree.Root.Add(new CircularNode(circularField.Name, circularField.Type));
        }

        public void AcceptPrimitive(Field primitiveField)
        {
            nodeTree.Root.Add(new PrimitiveNode(primitiveField.Name, primitiveField.Value));
        } 
    }

    
}