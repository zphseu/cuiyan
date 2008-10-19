// Copyright (c) 2002-2005 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.

using System;
using System.Collections;
using System.Reflection;
using System.IO;

namespace fit
{
    public class Fixture
    {
        //cycy for fithtmlwhite to add {{{
        public string Escape(string text)
        {
            return info(text);
        }

        public virtual void Exception(Parse cell, Exception exception)
        {
            error(cell, exception.ToString());
        }

        public virtual void Wrong(Parse cell, string actual)
        {
            wrong(cell, actual);
        }

        public virtual void Right(Parse cell)
        {
            right(cell);
        }

        public virtual void Ignore(Parse cell)
        {
            ignore(cell);
        }
        //cycy for fithtmlwhite to add }}}

        public static string[] assemblyDirs = new string[] {
            @"build",
            @"build\bin",
            @"obj",
            @"bin",
            @"bin\Debug",
            @"bin\Release",
        };

        public Hashtable summary = new Hashtable();
        public Counts counts = new Counts();
        protected String[] args;

        public class RunTime
        {
            DateTime start = DateTime.Now;
            TimeSpan elapsed = new TimeSpan(0);

            public override string ToString()
            {
                elapsed = (DateTime.Now - start);
                if (elapsed.TotalMilliseconds > 600000.0)
                {
                    return d(3600000) + ":" + d(600000) + d(60000) + ":" + d(10000) + d(1000);
                }
                else
                {
                    return d(60000) + ":" + d(10000) + d(1000) + "." + d(100) + d(10);
                }
            }

            protected internal virtual string d(long scale)
            {
                long report = (long)Math.Floor(elapsed.TotalMilliseconds / (double)scale);
                long remaining = (long)Math.Floor(elapsed.TotalMilliseconds - (double)(report * scale));
                elapsed = new TimeSpan(remaining * 10000); // 1ms = 10000ticks
                return report.ToString();
            }
        }

        // Traversal //////////////////////////

        /* Altered by Rick Mugridge to dispatch on the first Fixture */
        public void doTables(Parse tables)
        {
            summary["run date"] = DateTime.Now;
            summary["run elapsed time"] = new RunTime();
            if (tables != null)
            {
                Parse fixtureName = FixtureName(tables);
                if (fixtureName != null)
                {
                    try
                    {
                        Fixture fixture = getLinkedFixtureWithArgs(tables);
                        fixture.interpretTables(tables);
                    }
                    catch (Exception e)
                    {
                        exception(fixtureName, e);
                        interpretFollowingTables(tables);
                    }
                }
            }
        }

        /* Added by Rick Mugridge to allow a dispatch into DoFixture */
        protected void interpretTables(Parse tables)
        {
            try
            { // Don't create the first fixture again, because creation may do something important.
                getArgsForTable(tables); // get them again for the new fixture object
                doTable(tables);
            }
            catch (Exception ex)
            {
                exception(FixtureName(tables), ex);
                return;
            }
            interpretFollowingTables(tables);
        }

        /* Added by Rick Mugridge */
        private void interpretFollowingTables(Parse tables)
        {
            //listener.tableFinished(tables);
            tables = tables.more;
            while (tables != null)
            {
                Parse fixtureName = FixtureName(tables);
                if (fixtureName != null)
                {
                    try
                    {
                        Fixture fixture = getLinkedFixtureWithArgs(tables);
                        fixture.doTable(tables);
                    }
                    catch (Exception e)
                    {
                        exception(fixtureName, e);
                    }
                }
                tables = tables.more;
            }
        }

        /* Added from FitNesse*/
        protected Fixture getLinkedFixtureWithArgs(Parse tables)
        {
            Parse header = tables.at(0, 0, 0);
            Fixture fixture = loadFixture(header.text());
            fixture.counts = counts;
            fixture.summary = summary;
            fixture.getArgsForTable(tables);
            return fixture;
        }

        public Parse FixtureName(Parse tables)
        {
            return tables.at(0, 0, 0);
        }

        public virtual Fixture loadFixture(string className)
        {
            try
            {
                string assemblyList = "";
                string delimiter = "";
                foreach (string assemblyName in assemblies)
                {
                    Assembly assembly = Assembly.LoadFrom(assemblyName);
                    Fixture fixture = (Fixture)assembly.CreateInstance(className);
                    if (fixture != null) return fixture;
                    assemblyList += delimiter + assembly.CodeBase;
                    delimiter = ", ";
                }
                throw new ApplicationException("Fixture '" + className + "' could not be found.  Assemblies searched: " + assemblyList);
            }
            catch (InvalidCastException e)
            {
                throw new ApplicationException("Couldn't cast " + className + " to Fixture.  Did you remember to extend Fixture?", e);
            }
        }

        public virtual ArrayList assemblies
        {
            get
            {
                ArrayList result = new ArrayList();
                foreach (string dir in assemblyDirs)
                {
                    try
                    {
                        result.AddRange(Directory.GetFiles(dir, "*.dll"));
                    }
                    catch (DirectoryNotFoundException)
                    {
                        // ignore missing directories
                    }
                }
                return result;
            }
        }

        /* Added by Rick Mugridge, from FitNesse */
        protected void getArgsForTable(Parse table)
        {
            ArrayList argumentList = new ArrayList();
            Parse parameters = table.parts.parts.more;
            for (; parameters != null; parameters = parameters.more)
                argumentList.Add(parameters.text());
            args = (String[])argumentList.ToArray(typeof(String));
        }

        public virtual void doTable(Parse table)
        {
            doRows(table.parts.more);
        }

        public virtual void doRows(Parse rows)
        {
            while (rows != null)
            {
                Parse more = rows.more;
                doRow(rows);
                rows = more;
            }
        }

        public virtual void doRow(Parse row)
        {
            DoCells(row.parts);
        }

        //cycy for fithtmlwhite to rename from doCells to DoCells
        public virtual void DoCells(Parse cells)
        {
            for (int i = 0; cells != null; i++)
            {
                try
                {
                    doCell(cells, i);
                }
                catch (Exception e)
                {
                    exception(cells, e);
                }
                cells = cells.more;
            }
        }

        public virtual void doCell(Parse cell, int columnNumber)
        {
            ignore(cell);
        }


        // Annotation ///////////////////////////////

        public static String green = "#cfffcf";
        public static String red = "#ffcfcf";
        public static String yellow = "#ffffcf";

        public virtual void right(Parse cell)
        {
            cell.addToTag(" bgcolor=\"" + green + "\"");
            counts.right++;
        }

        public virtual void wrong(Parse cell)
        {
            cell.addToTag(" bgcolor=\"" + red + "\"");
            cell.body = escape(cell.text());
            counts.wrong++;
        }

        public virtual void wrong(Parse cell, string actual)
        {
            wrong(cell);
            cell.addToBody(label("expected") + "<hr>" + escape(actual) + label("actual"));
        }

        public void info(Parse cell, String message)
        {
            cell.addToBody(info(message));
        }

        public String info(String message)
        {
            return " <font color=\"#808080\">" + escape(message) + "</font>";
        }

        public virtual void ignore(Parse cell)
        {
            cell.addToTag(" bgcolor=\"#efefef\"");
            counts.ignores++;
        }

        public void error(Parse cell, String message)
        {
            cell.body = escape(cell.text());
            cell.addToBody("<hr><pre>" + escape(message) + "</pre>");
            cell.addToTag(" bgcolor=\"" + yellow + "\"");
            counts.exceptions++;
        }

        public virtual void exception(Parse cell, Exception exception)
        {
            error(cell, exception.ToString());
        }

        // Utility //////////////////////////////////

        public static string label(string text)
        {
            return " <font size=-1 color=\"#c08080\"><i>" + text + "</i></font>";
        }

        public static String escape(String s)
        {
            s = s.Replace("&", "&amp;");
            s = s.Replace("<", "&lt;");
            s = s.Replace("  ", " &nbsp;");
            s = s.Replace("\r\n", "<br />");
            s = s.Replace("\r", "<br />");
            s = s.Replace("\n", "<br />");
            return s;
        }

        public static string camel(string name)
        {
            string[] tokens = name.Split(' ');
            if (tokens.Length == 1) return name;

            string result = "";
            foreach (string token in tokens)
            {
                result += token.Substring(0, 1).ToUpper();		// replace spaces with camelCase
                result += token.Substring(1);
            }
            return result;
        }

        public virtual void check(Parse cell, TypeAdapter a)
        {
            string text = cell.text();
            if (text == "")
            {
                try
                {
                    info(cell, a.get().ToString());
                }
                catch (Exception)
                {
                    info(cell, "error");
                }
            }
            else if (a == null)
            {
                ignore(cell);
            }
            else if (text == "error")
            {
                try
                {
                    Object result = a.get();
                    wrong(cell, result.ToString());
                }
                catch (MethodAccessException e)
                {
                    exception(cell, e);
                }
                catch (Exception)
                {
                    right(cell);
                }
            }
            else
            {
                try
                {
                    object result = a.get();
                    if (a.equals(a.parse(text), result))
                    {
                        right(cell);
                    }
                    else
                    {
                        wrong(cell, result.ToString());
                    }
                }
                catch (Exception e)
                {
                    exception(cell, e);
                }
            }
        }

        /* Added by Rick, from FitNesse */
        public String[] getArgs()
        {
            return args;
        }
    }
}