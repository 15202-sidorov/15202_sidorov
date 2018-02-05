/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Utils;


import databaseInterface.DatabaseController;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;
import java.util.UUID;

/**
 *
 * @author Илья
 */
public class ResourceHandler {
    public static String getDocument( String src ) throws IOException {
        File file = new File(src);
        BufferedReader br = new BufferedReader(new FileReader(file));
        StringBuilder sb = new StringBuilder();
        String line = null;
        while ( (line = br.readLine()) != null ) {
            sb.append(line);
        }

        return sb.toString();
    }
    
    public static String getPublicChatList( String src ) throws IOException {
        File file = new File(src);
        BufferedReader br = new BufferedReader(new FileReader(file));
        StringBuilder sb = new StringBuilder();
        String line = null;
        String insertingPoint = "<ul class=\"list-group\">";
        while ( (line = br.readLine()) != null ) {
            sb.append(line);
            if ( line.contains(insertingPoint) ) {
                for ( UUID id : DatabaseController.getPublicChats().keySet() ) {
                    sb.append(" <li class=\"list-group-item\">\n" +
                              " <a class=\"chatname\">" + DatabaseController.getPublicChats().get(id).getName() + 
                            "</a>" +"</li>");
                }
            }
        }
        br.close();
        return sb.toString();   
    }
    
    public static String getPublicChat( String src, String name, String username ) throws IOException {
        File file = new File(src);
        BufferedReader br = new BufferedReader(new FileReader(file));
        StringBuilder sb = new StringBuilder();
        String line = null;
        String insertingPoint = "<div id=\"nearChatName\" class=\"col-md-6\">";
        while ( (line = br.readLine()) != null ) {
            sb.append(line);
            if ( line.contains(insertingPoint) ) {
                sb.append("<div class=\"chatname\"><h1>" +  name + " </h1></div>");
            }
            if ( line.contains("<div id=\"userlist\" class=\"col-md-6\">") ) {
                sb.append("<div id=\"username\"><h1>" + username + "</h1></div>");
            } 
        }
        
        br.close();
        return sb.toString();
    }
}
