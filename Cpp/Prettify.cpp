#include "minify.h"

string format_XML(string xml_file)
{
    static string xml_edit = xml_file;
    string xml_edit_2 = xml_file;

    int pre_index;
    int begin_index;
    int true_index;
    int flag = 0;
    int n_tabs = 0;

    stack <string>xml_check_close_outer;
    stack <string>xml_check_close_inner;
    static bool flage = false;

    if (flage == true)
    {
        if (xml_edit == xml_edit_2)
        {
            return xml_file;
        }
        else
        {
            xml_edit = xml_edit_2;
        }
    }
   xml_edit= minify_XML(minify_XML(minify_XML(xml_edit)));
    for (int i = 0; i < xml_edit.length(); i++)
    {
        if (xml_edit[i] == '<')
        {
            i++;

            if (xml_edit[i] != '/')
            {
                begin_index = i;
                while (xml_edit[i] != '>') i++;
                true_index = i;

                i++;
                while (xml_edit[i] == '\t' || xml_edit[i] == '\n' || xml_edit[i] == ' ') i++;

                if (xml_edit[i] == '<');
                else flag = 1;

                i = true_index;
                if (xml_edit[i + 1] != '\n')
                {
                    i++;
                    xml_edit.insert(i, "\n");
                    i++;
                }
                else i += 2;


                if (flag == 1)
                {
                    xml_check_close_inner.push(xml_edit.substr(begin_index, true_index - begin_index));

                    for (int iter = 0; iter < n_tabs; iter++)
                    {
                        xml_edit.insert(i, "   ");
                        i += 3;
                    }
                    xml_edit.insert(i, "    ");

                    while (xml_edit[i] != '<') i++;
                    i--;
                    flag = 0;

                }
                else
                {
                    xml_check_close_outer.push(xml_edit.substr(begin_index, true_index - begin_index));
                    n_tabs++;

                    for (int iter = 0; iter < n_tabs; iter++)
                    {
                        xml_edit.insert(i, "   ");
                        i += 3;
                    }
                    while (xml_edit[i] == '\t' || xml_edit[i] == '\n' || xml_edit[i] == ' ') i++;
                    i--;
                }
            }
            else if (xml_edit[i] == '/')
            {
                i++;
                pre_index = i - 2;

                if (!xml_check_close_inner.empty())
                {

                    i = pre_index - 1;
                    while (xml_edit[i] == ' ' || xml_edit[i] == '\t') i--;
                    if (xml_edit[i] != '\n')
                    {
                        xml_edit.insert(i + 1, "\n");
                        i = pre_index + 1;
                    }
                    else i = pre_index;

                    for (int iter = 0; iter < n_tabs; iter++)
                    {
                        xml_edit.insert(i, "   ");
                        i += 3;
                    }
                    while (xml_edit[i] != '>')i++;
                    if (xml_edit[i + 1] != '\n')
                    {
                        xml_edit.insert(i + 1, "\n");
                    }

                    while (!xml_check_close_inner.empty())
                    {
                        i++;
                        if (xml_edit[i] == '<')
                        {
                            if (xml_edit[i + 1] != '/')
                            {
                                for (int iter = 0; iter < n_tabs; iter++)
                                {
                                    xml_edit.insert(i, "   ");
                                    i += 3;
                                }
                            }
                            xml_check_close_inner.pop();
                            i--;
                        }
                    }
                }
                else
                {
                    xml_check_close_outer.pop();
                    i = pre_index - 1;
                    while (xml_edit[i] == ' ' || xml_edit[i] == '\t') i--;
                    if (xml_edit[i] != '\n')
                    {
                        xml_edit.insert(i + 1, "\n");
                        i = pre_index + 1;
                    }
                    else i = pre_index;

                    n_tabs--;
                    for (int iter = 0; iter < n_tabs; iter++)
                    {
                        xml_edit.insert(i, "   ");
                        i += 3;
                    }

                    while (xml_edit[i] != '>')i++;
                    if (xml_edit[i + 1] != '\n')
                    {
                        xml_edit.insert(i + 1, "\n");
                    }

                    while (xml_edit[i] != '>') i++;
                    if (!xml_check_close_outer.empty())
                    {
                        i++;
                        while (xml_edit[i] == '\t' || xml_edit[i] == '\n' || xml_edit[i] == ' ') i++;

                        if (xml_edit[i] == '<')
                        {
                            if (xml_edit[i + 1] != '/')
                            {
                                for (int iter = 0; iter < n_tabs; iter++)
                                {
                                    xml_edit.insert(i, "   ");
                                    i += 3;
                                }
                                while (xml_edit[i] != '<') i++;
                            }
                        }
                        i--;
                    }
                }
            }
        }
    }
    flage = true;


    return xml_edit;
}
