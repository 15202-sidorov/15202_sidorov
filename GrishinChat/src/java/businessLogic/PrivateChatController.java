/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package businessLogic;

import businessLogic.Entities.Message;
import businessLogic.Entities.PrivateChat;
import businessLogic.Entities.PublicChat;
import static businessLogic.PublicChatController.checkName;
import databaseInterface.DatabaseController;
import java.util.LinkedList;
import java.util.List;
import java.util.UUID;

/**
 *
 * @author Илья
 */
public class PrivateChatController {
    public static void conntectUserToChat( UUID userID, UUID chatID ) {
        /*
            REFRESH DATABASE
        */
        DatabaseController.getPublicChats().get(chatID).addUser(userID);
    }
    
    public static PrivateChat createChat( String name, UUID ownerID ) {
        if ( !checkName(name) ) {
            PrivateChat newPrivateChat = new PrivateChat(name, ownerID);
            DatabaseController.addPrivateChat(newPrivateChat);
            return newPrivateChat;
        }
        else {
            return null;
        }
    }
    
    public static boolean checkName( String name ) {
        if ( null == DatabaseController.getPrivateChatIDbyName(name) ) {
            return false;
        }
        
        return true;
    }
    
    public static void disconnectChildFromChat( UUID childID ) {
        List<UUID> list = DatabaseController.selectPrivateChatsByUser(childID);
        for ( UUID id : list ) {
            DatabaseController.getPrivateChats().get(id).deleteUser(childID);
        }
    }
    
    public static void deleteChat( UUID chatID ) {
        DatabaseController.deletePrivateChat(chatID);
    }
    
    public static List<PrivateChat> getUserChats( UUID userID ) {
        List<PrivateChat> result = new LinkedList<PrivateChat>();
        List<UUID> ids = DatabaseController.selectPrivateChatsByUser(userID);
        for ( UUID id : ids ) {
            result.add(DatabaseController.getPrivateChats().get(id));
        }
        return result;
    }
    
    public static void newMessage( UUID userID, String data, UUID chatID ) {
        Message message = new Message(data, userID);
        DatabaseController.getPrivateChats().get(chatID).addMessage(message);
    }
    
    public static void removeUserFromChat( UUID userID, UUID chatID ) {
        DatabaseController.getPrivateChats().get(chatID).deleteUser(userID);
    }
    
    public static List<Message> getChatHistory( UUID chatID ) {
        return DatabaseController.getPrivateChats().get(chatID).getMessages();
    }
}
