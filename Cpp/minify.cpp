#include"minify.h"
string remove_spaces(const string& s)
{
    int last = (int)s.size() - 1;
    while (last >= 0 && s[last] == ' ')
        --last;
    return s.substr(0, last + 1);
}


string minify_XML(string xml_file)
{
    string xml_edit = xml_file;
    int begin_index;
    int new_size = (int)xml_edit.size();
    int flag = 0;
    string temp;

    for (int i = 0; i < xml_edit.size(); i++)
    {
        if (xml_edit[i] == '>' && (i + 1) != xml_edit.size())
        {
            begin_index = i;
            i++;
            while ((xml_edit[i] == '\t' || xml_edit[i] == '\n' || xml_edit[i] == ' ')) i++;
            if (xml_edit[i] == '<')
            {
                xml_edit.erase(begin_index + 1, i - begin_index - 1);
                xml_edit.insert(begin_index + 1, "\n");
            }
            else
            {
                xml_edit.erase(begin_index + 1, i - begin_index - 1);
                xml_edit.insert(begin_index + 1, "\n");
                i = begin_index;

                while (xml_edit[i] != '<')
                {
                    if ((i + 1) == xml_edit.size())
                    {
                        xml_edit.append("\n");
                        flag = 1;
                        break;
                    }
                    i++;
                }

                begin_index = i;
                i--;
                while (xml_edit[i] == '\t' || xml_edit[i] == '\n' || xml_edit[i] == ' ') i--;

                if (flag == 0)
                {
                    xml_edit.erase(i + 1, begin_index - i - 1);
                    xml_edit.insert(i + 1, "\n");
                }
            }
        }
    }
    xml_edit.append("\n");
    temp = remove_spaces(xml_edit);
    new_size = (int)temp.size();
    xml_edit.resize(new_size);

    return xml_edit;
}
