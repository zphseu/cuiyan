// Copyright (c) 2002 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.

using System.Collections;
using System;

namespace fit {
    public abstract class RowFixture : ColumnFixture {
        public object[] results;
        public ArrayList missing = new ArrayList();
        public ArrayList surplus = new ArrayList();

        public override void doRows(Parse rows) {
            try {
                bind(rows.parts);
                results = query();
                match(list(rows.more), list(results), 0);
                Parse last = rows.last();
                last.more = buildRows(surplus.ToArray());
                mark(last.more, "surplus");
                mark(missing, "missing");
            } 
            catch (Exception e) {
                exception (rows.leaf(), e);
            }
        }

        public abstract object[] query();  // get rows to be compared
        public abstract override Type getTargetClass();             // get expected type of row

        // There's a significant "gotcha" here for people porting from the Java
        // version.  Java implements an equals() method on ArrayList that compares
        // the contents of the array.  C# DOES NOT.  The Java implementation of
        // match() depends on this behavior.
        protected internal virtual void match(ArrayList expected, ArrayList computed, int col) {
            if (col >= columnBindings.Length) {
                check (expected, computed);
            } else if (columnBindings[col] == null) {
                match (expected, computed, col+1);
            } else {
                Hashtable eMap = eSort(expected, col);
                Hashtable cMap = cSort(computed, col);
                foreach (object key in union(eMap.Keys, cMap.Keys)) {
                    ArrayList eList = (ArrayList)eMap[key];
                    ArrayList cList = (ArrayList)cMap[key];
                    if (eList == null) {
                        surplus.AddRange(cList);
                    } 
                    else if (cList == null) {
                        missing.AddRange(eList);
                    } 
                    else if (eList.Count==1 && cList.Count==1) {
                        check(eList, cList);
                    } 
                    else {
                        match(eList, cList, col+1);
                    }
                }
            }
        }

        protected virtual ArrayList list(Parse rows) {
            ArrayList result = new ArrayList();
            while (rows != null) {
                result.Add(rows);
                rows = rows.more;
            }
            return result;
        }

        protected virtual ArrayList list(object[] rows) {
            return new ArrayList(rows);
        }

        protected virtual Hashtable eSort(ArrayList list, int col) {
            TypeAdapter a = columnBindings[col];
            Hashtable result = new Hashtable();
            foreach (Parse row in list) {
                Parse cell = row.parts.at(col);
                try {
                    object key = a.parse(cell.text());
                    bin(result, key, row);
                } 
                catch (Exception e) {
                    exception(cell, e);
                    for (Parse rest=cell.more; rest!=null; rest=rest.more) {
                        ignore(rest);
                    }
                }
            }
            return result;
        }

        protected virtual Hashtable cSort(ArrayList list, int col) {
            TypeAdapter a = columnBindings[col];
            Hashtable result = new Hashtable();
            foreach (object row in list) {
                try {
                    a.target = row;
                    object key = a.get();
                    bin(result, key, row);
                } 
                catch (Exception) {
                    // surplus anything with bad keys, including null
                    surplus.Add(row);
                }
            }
            return result;
        }

        protected virtual void bin (Hashtable map, object key, object row) {
            if (key.GetType().IsArray) {
                key = new ComparableArrayList((object[])key);
            }
            if (map.ContainsKey(key)) {
                ((ArrayList)map[key]).Add(row);
            } 
            else {
                ArrayList list = new ArrayList();
                list.Add(row);
                map[key] = list;
            }
        }

        protected virtual ICollection union(ICollection a, ICollection b) {
            Hashtable result = new Hashtable();
            foreach (object o in a) {
                result[o] = true;
            }
            foreach (object o in b) {
                result[o] = true;
            }
            return result.Keys;
        }

        protected virtual void check (ArrayList eList, ArrayList cList) {
            if (eList.Count==0) {
                surplus.AddRange(cList);
                return;
            }
            if (cList.Count==0) {
                missing.AddRange(eList);
                return;
            }
            Parse row = (Parse)eList[0];
            eList.RemoveAt(0);
            Parse cell = row.parts;
            Object obj = cList[0];
            cList.RemoveAt(0);
            for (int i=0; i<columnBindings.Length && cell!=null; i++) {
                TypeAdapter a = columnBindings[i];
                if (a != null) {
                    a.target = obj;
                }
                check(cell, a);
                cell = cell.more;
            }
            check (eList, cList);
        }

        protected virtual void mark(Parse rows, string message) {
            string annotation = label(message);
            while (rows != null) {
                wrong(rows.parts);
                rows.parts.addToBody(annotation);
                rows = rows.more;
            }
        }

        protected virtual void mark(ArrayList rows, string message) {
            string annotation = label(message);
            foreach (Parse row in rows) {
                wrong(row.parts);
                row.parts.addToBody(annotation);
            }
        }

        protected virtual Parse buildRows(object[] rows) {
            Parse root = new Parse(null ,null, null, null);
            Parse next = root;
            for (int i=0; i<rows.Length; i++) {
                next = next.more = new Parse("tr", null, buildCells(rows[i]), null);
            }
            return root.more;
        }

        protected virtual Parse buildCells(object row) {
            if (row == null) {
                Parse nil = new Parse("td", "null", null, null);
                nil.addToTag(" colspan="+columnBindings.Length);
                return nil;
            }
            Parse root = new Parse(null, null, null, null);
            Parse next = root;
            for (int i=0; i<columnBindings.Length; i++) {
                next = next.more = new Parse("td", "&nbsp;", null, null);
                TypeAdapter a = columnBindings[i];
                if (a == null) {
                    ignore (next);
                } 
                else {
                    try {
                        a.target = row;
						info(next, a.get().ToString());
                    } 
                    catch (Exception e) {
                        exception(next, e);
                    }
                }
            }
            return root.more;
        }

        // An ArrayList whose Equals() method compares the contents
        // of the arrays.
        private class ComparableArrayList : ArrayList {
            public ComparableArrayList(object[] sourceArray) : base(sourceArray) {
            }

            public override bool Equals(object comparator) {
                if (!(comparator is ComparableArrayList)) base.Equals(comparator);

                ComparableArrayList that = (ComparableArrayList)comparator;
                if (this.Count != that.Count) return false;
                for (int i = 0; i < this.Count; i++) {
                    if (!(this[i].Equals(that[i]))) return false;
                }
                return true;
            }

            public override int GetHashCode() {
                if (this.Count == 0) return 0;
                return this[0].GetHashCode();
            }
        }
    }
}