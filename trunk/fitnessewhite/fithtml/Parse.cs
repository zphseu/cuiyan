// Copyright (c) 2002, 2003 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.

using System.IO;
using System.Text.RegularExpressions;
using System;

namespace fit
{
    public class Parse
    {
        public string leader;
        public string tag;
        public string body;
        public string end;
        public string trailer;

        //cycy for fithtmlwhite to add {{{
        public Parse More
        {
            get { return more; }
        }

        public String Text
        {
            get { return htmlToText(body); }
        }

        //cycy for fithtmlwhite to add }}}

        public Parse more;
        public Parse parts;

        public Parse(string tag, string body, Parse parts, Parse more)
        {
            this.leader = "\n";
            this.tag = "<" + tag + ">";
            this.body = body;
            this.end = "</" + tag + ">";
            this.trailer = "";
            this.parts = parts;
            this.more = more;
        }

        public static string[] tags = { "table", "tr", "td" };

        public Parse(string text)
            : this(text, tags, 0, 0)
        {
        }

        public Parse(string text, string[] tags)
            : this(text, tags, 0, 0)
        {
        }

        private static string Substring(string text, int startIndexInclusive, int endIndexExclusive)
        {
            return text.Substring(startIndexInclusive, endIndexExclusive - startIndexInclusive);
        }

        private static int ProtectedIndexOf(string text, string searchValue, int offset, string tag)
        {
            int result = text.IndexOf(searchValue, offset);
            if (result < 0) throw new ApplicationException("Can't find tag: " + tag);
            else return result;
        }

        public Parse(string text, string[] tags, int level, int offset)
        {
            string lc = text.ToLower();
            string target = tags[level];

            int startTag = ProtectedIndexOf(lc, "<" + target, 0, target);
            int endTag = ProtectedIndexOf(lc, ">", startTag, target) + 1;
            //			int startEnd = ProtectedIndexOf(lc, "</"+target, endTag, target);
            int startEnd = findMatchingEndTag(lc, endTag, tags[level], offset);
            int endEnd = ProtectedIndexOf(lc, ">", startEnd, target) + 1;
            int startMore = lc.IndexOf("<" + target, endEnd);

            leader = Substring(text, 0, startTag);
            tag = Substring(text, startTag, endTag);
            body = Substring(text, endTag, startEnd);
            end = Substring(text, startEnd, endEnd);
            trailer = text.Substring(endEnd);

            if (level + 1 < tags.Length)
            {
                parts = new Parse(body, tags, level + 1, offset + endTag);
                body = null;
            }
            else
            { // Check for nested table
                int index = body.IndexOf("<" + tags[0]);
                if (index >= 0)
                {
                    parts = new Parse(body, tags, 0, offset + endTag);
                    body = "";
                }
            }

            if (startMore >= 0)
            {
                more = new Parse(trailer, tags, level, offset + endEnd);
                trailer = null;
            }
        }

        /* Added by Rick Mugridge, Feb 2005 */
        protected static int findMatchingEndTag(String lc, int matchFromHere, String tag, int offset)
        {
            int fromHere = matchFromHere;
            int count = 1;
            int startEnd = 0;
            while (count > 0)
            {
                int embeddedTag = lc.IndexOf("<" + tag, fromHere);
                int embeddedTagEnd = lc.IndexOf("</" + tag, fromHere);
                // Which one is closer?
                if (embeddedTag < 0 && embeddedTagEnd < 0)
                    throw new ApplicationException("Can't find tag: " + tag);
                if (embeddedTag < 0)
                    embeddedTag = int.MaxValue;
                if (embeddedTagEnd < 0)
                    embeddedTagEnd = int.MaxValue;
                if (embeddedTag < embeddedTagEnd)
                {
                    count++;
                    startEnd = embeddedTag;
                    fromHere = lc.IndexOf(">", embeddedTag) + 1;
                }
                else if (embeddedTagEnd < embeddedTag)
                {
                    count--;
                    startEnd = embeddedTagEnd;
                    fromHere = lc.IndexOf(">", embeddedTagEnd) + 1;
                }
            }
            return startEnd;
        }

        public virtual int size()
        {
            return more == null ? 1 : more.size() + 1;
        }

        public virtual Parse last()
        {
            return more == null ? this : more.last();
        }

        public virtual Parse leaf()
        {
            return parts == null ? this : parts.leaf();
        }

        public virtual Parse at(int i)
        {
            return i == 0 || more == null ? this : more.at(i - 1);
        }

        public virtual Parse at(int i, int j)
        {
            return at(i).parts.at(j);
        }

        public virtual Parse at(int i, int j, int k)
        {
            return at(i, j).parts.at(k);
        }

        public String text()
        {
            return htmlToText(body);
        }

        public static String htmlToText(String s)
        {
            s = normalizeLineBreaks(s);
            s = removeNonBreakTags(s);
            s = condenseWhitespace(s);
            s = unescape(s);
            return s;
        }

        private static String removeNonBreakTags(String s)
        {
            int i = 0, j;
            while ((i = s.IndexOf('<', i)) >= 0)
            {
                if ((j = s.IndexOf('>', i + 1)) > 0)
                {
                    if (Substring(s, i, j + 1) != "<br />")
                    {
                        s = Substring(s, 0, i) + s.Substring(j + 1);
                    }
                    else i++;
                }
                else break;
            }
            return s;
        }

        public static String unescape(String s)
        {
            s = s.Replace("<br />", "\n");
            s = unescapeEntities(s);
            s = unescapeSmartQuotes(s);
            return s;
        }

        private static String unescapeSmartQuotes(String s)
        {
            s = s.Replace('\u201c', '"');
            s = s.Replace('\u201d', '"');
            s = s.Replace('\u2018', '\'');
            s = s.Replace('\u2019', '\'');
            return s;
        }

        private static String unescapeEntities(String s)
        {
            s = s.Replace("&lt;", "<");
            s = s.Replace("&gt;", ">");
            s = s.Replace("&nbsp;", " ");
            s = s.Replace("&quot;", "\"");
            s = s.Replace("&amp;", "&");
            return s;
        }

        private static String normalizeLineBreaks(String s)
        {
            s = Regex.Replace(s, "<\\s*br\\s*/?\\s*>", "<br />");
            s = Regex.Replace(s, "<\\s*/\\s*p\\s*>\\s*<\\s*p( .*?)?>", "<br />");
            return s;
        }

        public static String condenseWhitespace(String s)
        {
            char NON_BREAKING_SPACE = (char)160;

            s = Regex.Replace(s, "\\s+", " ", RegexOptions.ECMAScript);
            s = s.Replace(NON_BREAKING_SPACE, ' ');
            s = Regex.Replace(s, "&nbsp;", " ");
            s = s.Trim();
            return s;
        }

        public virtual void addToTag(string text)
        {
            int last = tag.Length - 1;
            tag = Substring(tag, 0, last) + text + ">";
        }

        public virtual void addToBody(string text)
        {
            body = body + text;
        }

        public virtual void print(TextWriter output)
        {
            output.Write(leader);
            output.Write(tag);
            if (parts != null)
            {
                parts.print(output);
            }
            else
            {
                output.Write(body);
            }
            output.Write(end);
            if (more != null)
            {
                more.print(output);
            }
            else
            {
                output.Write(trailer);
            }
        }

        public static int footnoteFiles = 0;
        public virtual string footnote()
        {
            if (footnoteFiles >= 25)
            {
                return "[-]";
            }
            else
            {
                try
                {
                    int thisFootnote = ++footnoteFiles;
                    string html = "footnotes/" + thisFootnote + ".html";
                    FileInfo file = new FileInfo("Reports/" + html);

                    // Create the Reports directory if not exists
                    string directory = file.DirectoryName;
                    if (!Directory.Exists(directory))
                        Directory.CreateDirectory(directory);
                    else if (file.Exists)
                        file.Delete();

                    TextWriter output = file.CreateText();
                    print(output);
                    output.Close();
                    return string.Format("<a href={0}>[{1}]</a>", file.FullName, thisFootnote);
                }
                catch (IOException)
                {
                    return "[!]";
                }
            }
        }
    }
}