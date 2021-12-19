#include "Consistency.h"
#include "Prettify.h"
#include "minify.h"
using namespace std;

string Check_XML_Consistency(string xml_file)
{
    string xml_edit = xml_file;
    int pre_index;
    int begin_index;
    int true_index;
    int flag = 0;
    int flag_check = 0;
    int diffrence = 0;

    stack <string>xml_check_close_outer;
    stack <string>xml_check_close_outer_temp;
    stack <string>xml_check_close_inner;

    string xml_check_close_string;
    string check_top;
    string correct;
    unsigned int h = (int)xml_edit.find("<", 0), j;
    if (xml_edit.substr(h + 1, 1) == "?")
    {
        j = (int)xml_edit.find(">", h);
        xml_edit.erase(h, j - h + 1);
    }

    for (int i = 0; i < xml_edit.length(); i++)
    {
        if (xml_edit[i] == '<')
        {
            i++;

            if (xml_edit[i] != '/')
            {
                begin_index = i;
                pre_index = i - 1;
                while (xml_edit[i] != '>') i++;
                true_index = i;
                diffrence = true_index - begin_index;

                if (!xml_check_close_inner.empty())
                {
                    xml_edit.insert(pre_index, ">");
                    xml_edit.insert(pre_index, xml_check_close_inner.top());
                    xml_edit.insert(pre_index, "</");
                    correct = xml_check_close_inner.top();
                    xml_check_close_inner.pop();

                    begin_index = pre_index + (int)correct.size() + 4;
                    true_index = begin_index + diffrence;
                    i = true_index;
                }
                i++;
                while (xml_edit[i] == '\t' || xml_edit[i] == '\n' || xml_edit[i] == ' ') i++;

                if (xml_edit[i] == '<');
                else flag = 1;

                i = true_index;
                if (flag == 1)
                {
                    xml_check_close_inner.push(xml_edit.substr(begin_index, i - begin_index));
                    flag = 0;
                }
                else
                {
                    xml_check_close_outer.push(xml_edit.substr(begin_index, i - begin_index));
                }
            }
            else if (xml_edit[i] == '/')
            {
                i++;
                begin_index = i;
                pre_index = i - 2;

                while (xml_edit[i] != '>') i++;

                xml_check_close_string = xml_edit.substr(begin_index, i - begin_index);

                if (!xml_check_close_inner.empty())
                {
                    if (xml_check_close_inner.top() == xml_check_close_string)
                    {
                        xml_check_close_inner.pop();
                    }
                    else if (!xml_check_close_outer.empty())
                    {
                        while (!xml_check_close_outer.empty())
                        {
                            if (xml_check_close_outer.top() != xml_check_close_string)
                            {
                                xml_check_close_outer_temp.push(xml_check_close_outer.top());
                                xml_check_close_outer.pop();
                            }
                            else
                            {
                                while (!xml_check_close_outer_temp.empty())
                                {
                                    xml_check_close_outer.push(xml_check_close_outer_temp.top());
                                    xml_check_close_outer_temp.pop();
                                }
                                flag_check = 1;
                                break;
                            }
                        }
                        if (flag_check == 1)
                        {
                            xml_edit.insert(pre_index, ">");
                            xml_edit.insert(pre_index, xml_check_close_inner.top());
                            xml_edit.insert(pre_index, "</");

                            correct = xml_check_close_inner.top();
                            xml_check_close_inner.pop();

                            begin_index = pre_index + (int)correct.size() + 2;
                            i = begin_index;
                        }
                        else
                        {
                            while (!xml_check_close_outer_temp.empty())
                            {
                                xml_check_close_outer.push(xml_check_close_outer_temp.top());
                                xml_check_close_outer_temp.pop();
                            }
                            xml_edit.insert(pre_index, ">");
                            xml_edit.insert(pre_index, xml_check_close_inner.top());
                            xml_edit.insert(pre_index, "</");

                            correct = xml_check_close_inner.top();
                            xml_check_close_inner.pop();

                            begin_index = pre_index + (int)correct.size() + 2;
                            i = begin_index;
                            xml_edit.erase(begin_index + 1, xml_check_close_string.size() + 3);
                        }
                    }
                }
                else if (!xml_check_close_outer.empty())
                {
                    if (xml_check_close_outer.top() == xml_check_close_string)
                    {
                        xml_check_close_outer.pop();
                    }

                    else
                    {
                        while (!xml_check_close_outer.empty())
                        {
                            if (xml_check_close_outer.top() != xml_check_close_string)
                            {
                                xml_check_close_outer_temp.push(xml_check_close_outer.top());
                                xml_check_close_outer.pop();
                            }
                            else
                            {
                                while (!xml_check_close_outer_temp.empty())
                                {
                                    xml_check_close_outer.push(xml_check_close_outer_temp.top());
                                    xml_check_close_outer_temp.pop();
                                }
                                flag_check = 1;
                                break;
                            }
                        }

                        if (flag_check == 1)
                        {

                            while (xml_check_close_outer.top() != xml_check_close_string)
                            {
                                xml_edit.insert(pre_index, ">");
                                xml_edit.insert(pre_index, xml_check_close_outer.top());
                                xml_edit.insert(pre_index, "</");

                                correct = xml_check_close_outer.top();
                                xml_check_close_outer.pop();

                                begin_index = pre_index + (int)correct.size() + 5;
                                pre_index = begin_index - 2;
                                i = pre_index - 1;
                            }
                            flag_check = 0;
                        }
                        else
                        {
                            while (!xml_check_close_outer_temp.empty())
                            {
                                xml_check_close_outer.push(xml_check_close_outer_temp.top());
                                xml_check_close_outer_temp.pop();
                            }
                            xml_edit.erase(begin_index - 2, i - begin_index + 3);
                            i = begin_index - 3;
                        }
                    }
                }
            }
        }
    }
    if (!xml_check_close_inner.empty())
    {
        xml_edit.append("</"); xml_edit.append(xml_check_close_inner.top()); xml_edit.append(">\n");
        xml_check_close_inner.pop();
    }
    while (!xml_check_close_outer.empty())
    {
        xml_edit.append("</"); xml_edit.append(xml_check_close_outer.top()); xml_edit.append(">\n");
        xml_check_close_outer.pop();
    }
    xml_edit = format_XML(minify_XML(minify_XML(minify_XML(xml_edit))));
    return xml_edit;
}
