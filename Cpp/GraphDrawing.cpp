#include"GraphDrawing.h"

string Get_user_id_name(string input , int found_id)
{
    int begin_index;
    int end_index;
    int i = found_id;

    while (input[i] != '>') i += 1;
    i++;

    while (input[i] == '\t' || input[i] == '\n' || input[i] == ' ') i++;
    begin_index = i;

    while (input[i] != '<')i++;
    i--;
    while (input[i] == '\t' || input[i] == '\n' || input[i] == ' ') i--;
    end_index = i;

    return input.substr(begin_index, (end_index - begin_index + 1));
}



string Graph_present(string xml_file)
{

    string my_graph = "digraph G{subgraph cluster_p {label = Graph;node [shape=record fontname=Arial color = blue];edge [color = red];";
    string id = "<id>" , follower = "<follower>" , name = "<name>" , user = "</student>" , user_id , user_name , user_id_name;
    int found_name , found_id , found_user , found_follower;

    for (int i = 0; i < xml_file.length(); i++)
    {
        found_name = xml_file.find(name, i);
        found_id = xml_file.find(id, i);
        found_user = xml_file.find(user, i);


        if (found_name == string::npos || found_id == string::npos)
            break;

        else
        {
            user_id = Get_user_id_name(xml_file, found_id);
            user_name = Get_user_id_name(xml_file, found_name);
            user_id_name = user_id + "[ style=filled, fillcolor=lightblue ,label=\"{name = " + user_name + "|id = " + user_id + "}\"] ";


            my_graph.append(user_id_name);
            i = found_user;
        }
    }

    for (int i = 0; i < xml_file.length(); i++)
    {

        found_id = xml_file.find(id , i);

        if (found_id == string::npos)
            break;
        else
        {
            user_id = Get_user_id_name(xml_file, found_id);
            my_graph.append(user_id);
            i = found_id;

            found_user = xml_file.find(user, i);
            found_follower = xml_file.find(follower , i);
            if (found_follower > found_user)
                my_graph.append(";");
            else
            {
                found_id = xml_file.find(id, i + 1);
                my_graph.append(" -> ");
                my_graph.append(Get_user_id_name(xml_file, found_id));
                my_graph.append(";");

                i = found_id;
                found_id = xml_file.find(id, i + 1);

                while (found_id < found_user && found_id != string::npos)
                {
                    my_graph.append(user_id);
                    my_graph.append(" -> ");
                    my_graph.append(Get_user_id_name(xml_file, found_id));
                    my_graph.append(";");
                    i = found_id;
                    found_id = xml_file.find(id, i + 1);
                }
            }
        }
    }
    my_graph.append("}}");
    return my_graph;
}
