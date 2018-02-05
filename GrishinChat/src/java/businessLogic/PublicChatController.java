/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package businessLogic;

import businessLogic.Entities.Message;
import businessLogic.Entities.PublicChat;
import databaseInterface.DatabaseController;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.UUID;


/**
 *
 * @author Илья
 */
public class PublicChatController {
  
    
    public static void conntectUserToChat( UUID userID, UUID chatID ) {
        /*
            REFRESH DATABASE
        */
        DatabaseController.getPublicChats().get(chatID).addUser(userID);
    }
    
    public static PublicChat createChat( String name ) {
        if ( !checkName(name) ) {
            PublicChat newPublicChat = new PublicChat(name);
            DatabaseController.addPublicChat(newPublicChat);
            return newPublicChat;
        }
        else {
            return null;
        }
    }
    
    public static boolean checkName( String name ) {
        if ( null == DatabaseController.getPublicChatIDbyName(name) ) {
            return false;
        }
        
        return true;
    }
    
    public static void deleteChat( UUID chatID ) {
        DatabaseController.deletePublicChat(chatID);
    }
    
    public static List<PublicChat> getUsersChats( UUID userID ) {
        List<UUID> ids = DatabaseController.selectPublicChatsByUser(userID);
        List<PublicChat> result = new LinkedList<PublicChat>();
        for (UUID id : DatabaseController.getPublicChats().keySet()) {
            if ( ids.contains(id) ) {
                result.add(DatabaseController.getPublicChats().get(id));
            }
        }
        return result;
    }
    
    public static LinkedList<PublicChat> getAllPublicChats() {
        return new LinkedList<PublicChat>(DatabaseController.getPublicChats().values());
    }
    
    public static void newMessage( UUID userID, String data, UUID chatID ) {
        Message message = new Message(data, userID);
        DatabaseController.getPublicChats().get(chatID).addMessage(message);
    }
    
    public static void removeUserFromChat( UUID userID, UUID chatID ) {
        DatabaseController.getPublicChats().get(chatID).deleteUser(userID);
    }
    
    public static List<Message> getChatHistory( UUID chatID ) {
        return DatabaseController.getPublicChats().get(chatID).getMessages();
    }
    
    /*
        SHOULD BE CONNECTION TO ALL INTERFACES OF WEBSOCKETS
    */
}
