#include"Prettify.h"
#include"minify.h"
#include"check_errors.h"


string Check_XML_Errors(string xml_file)
{
    static string xml_edit = xml_file;
    string xml_edit_2 = xml_file;

    int pre_index;
    int begin_index;
    int true_index;
    int flag = 0;
    int flag_check = 0;
    int diffrence = 0;

    stack <string>xml_check_close_outer;
    stack <string>xml_check_close_outer_temp;
    stack <string>xml_check_close_inner;
    stack <string>Error_tag_name;

    string xml_check_close;
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
    unsigned int h = (int)xml_edit.find("<", 0), j;
    if (xml_edit.substr(h + 1, 1) == "?")
    {
        j = (int)xml_edit.find(">", h);
        xml_edit.erase(h, j - h + 1);
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
                pre_index = i - 2;
                while (xml_edit[i] != '>') i++;
                true_index = i;
                diffrence = true_index - begin_index;

                if (!xml_check_close_inner.empty())
                {
                    xml_edit.insert(pre_index, "\n--> error here");
                    Error_tag_name.push(xml_check_close_inner.top());
                    xml_check_close_inner.pop();

                    begin_index = pre_index + 17;
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
                pre_index = i - 3;

                while (xml_edit[i] != '>') i++;

                xml_check_close = xml_edit.substr(begin_index, i - begin_index);

                if (!xml_check_close_inner.empty())
                {
                    if (xml_check_close_inner.top() == xml_check_close)
                    {
                        xml_check_close_inner.pop();
                    }

                    else
                    {
                        while (!xml_check_close_outer.empty())
                        {
                            if (xml_check_close_outer.top() != xml_check_close)
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
                            xml_edit.insert(pre_index, "\n--> error here");
                            Error_tag_name.push(xml_check_close_inner.top());
                            xml_check_close_inner.pop();

                            begin_index = pre_index + 18;
                            pre_index = begin_index - 2;
                            i = begin_index - 3;
                        }
                        else
                        {
                            while (!xml_check_close_outer_temp.empty())
                            {
                                xml_check_close_outer.push(xml_check_close_outer_temp.top());
                                xml_check_close_outer_temp.pop();
                            }

                            xml_edit.insert(pre_index + 1, "--> error here");
                            Error_tag_name.push(xml_check_close_inner.top());
                            xml_check_close_inner.pop();

                            begin_index = pre_index + 17;
                            pre_index = begin_index - 2;
                            i = begin_index + (int)xml_check_close.size();
                        }
                    }
                }
                else if (!xml_check_close_outer.empty())
                {
                    if (xml_check_close_outer.top() == xml_check_close)
                    {
                        xml_check_close_outer.pop();
                    }

                    else
                    {
                        while (!xml_check_close_outer.empty())
                        {

                            if (xml_check_close_outer.top() != xml_check_close)
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
                            do
                            {
                                xml_edit.insert(pre_index, "\n--> error here");
                                Error_tag_name.push(xml_check_close_outer.top());
                                xml_check_close_outer.pop();

                                begin_index = pre_index + 18;
                                i = begin_index - 3;
                                pre_index = begin_index - 3;

                            } while (xml_check_close_outer.top() != xml_check_close);


                            flag_check = 0;
                        }
                        else
                        {
                            while (!xml_check_close_outer_temp.empty())
                            {
                                xml_check_close_outer.push(xml_check_close_outer_temp.top());
                                xml_check_close_outer_temp.pop();
                            }

                            xml_edit.insert(pre_index + 1, "--> error here");
                            Error_tag_name.push(xml_check_close_outer.top());
                            xml_check_close_outer.pop();

                            begin_index = pre_index + 17;
                            i = begin_index + (int)xml_check_close.size();
                        }
                    }
                }
            }
        }
    }
    //xml_edit = minify_XML(xml_edit);

    if (!xml_check_close_inner.empty())
    {
        xml_edit.append("--> error here\n");
        Error_tag_name.push(xml_check_close_inner.top());
        xml_check_close_inner.pop();
    }
    while (!xml_check_close_outer.empty())
    {
        xml_edit.append("--> error here\n");
        Error_tag_name.push(xml_check_close_outer.top());
        xml_check_close_outer.pop();
    }

    xml_edit.append("\n\nTags with Errors:\n*****************\n");

    while (!Error_tag_name.empty())
    {
        xml_edit.append(Error_tag_name.top());
        xml_edit.append("\n");
        Error_tag_name.pop();
    }
    flage = true;

    return xml_edit;
}
