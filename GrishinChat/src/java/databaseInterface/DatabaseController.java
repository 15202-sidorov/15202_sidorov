/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package databaseInterface;

import businessLogic.Entities.PrivateChat;
import businessLogic.Entities.PublicChat;
import businessLogic.Entities.User;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.UUID;
import java.util.concurrent.ConcurrentHashMap;

/**
 *
 * @author Илья
 */
public class DatabaseController {
    /*
        SHOULD BE DATABASE
        THIS IS JUST A RAW VERSION
    */
    
    public static UUID getUserIDbyName( String name ) {
        
        return nameMap.get(name);
    }
    
    public static UUID getPublicChatIDbyName( String name ) {
        for ( String name_ : publicChatMap.keySet() ) {
            if ( name.contains(name_) ) {
                return publicChatMap.get(name_);
            }
        }
        
        return null;
    }
    
    public static UUID getPrivateChatIDbyName( String name ) {
        return privateChatMap.get(name);
    }
    
    public static ConcurrentHashMap<UUID, User> getUsers() {
        return allUsers;
    }
    
    public static ConcurrentHashMap<UUID, PublicChat> getPublicChats() {
        return allPublicChats;
    }
    
    public static ConcurrentHashMap<UUID, PrivateChat> getPrivateChats() {
        return allPrivateChats;
    }
    
    public static void addUser(User newUser) {
        allUsers.put(newUser.getID(), newUser);
        nameMap.put(newUser.getName(), newUser.getID());
    }
    
    public static void addPublicChat(PublicChat publicChat) {
        allPublicChats.put(publicChat.getID(), publicChat);
        publicChatMap.put(publicChat.getName(), publicChat.getID());
    }
    
    public static void addPrivateChat( PrivateChat newPrivateChat ) {
        allPrivateChats.put(newPrivateChat.getID(), newPrivateChat);
        privateChatMap.put(newPrivateChat.getName(), newPrivateChat.getID());
    }
    
    public static void deleteUser(UUID userID) {
        for ( String name : nameMap.keySet() ) {
            if ( userID.equals(nameMap.get(name)) ) {
                nameMap.remove(name);
            }
        }
        allUsers.remove(userID);
        
        for ( UUID chatID : allPublicChats.keySet() ) {
            if (allPublicChats.get(chatID).getUsers().contains(userID)) {
                allPublicChats.get(chatID).deleteUser(userID);
            }
        }
        
        for ( UUID chatID : allPrivateChats.keySet() ) {
            if (allPrivateChats.get(chatID).getUsers().contains(userID)) {
                allPrivateChats.get(chatID).deleteUser(userID);
            }
        } 
    }
    
    public static void deletePublicChat(UUID chatID) {
        for ( String name : publicChatMap.keySet() ) {
            if ( chatID.equals(publicChatMap.get(name)) ) {
                publicChatMap.remove(name);
            }
        }
        allPublicChats.remove(chatID);
    }
    
    public static void deletePrivateChat(UUID chatID) {
        for ( String name : privateChatMap.keySet() ) {
            if ( chatID.equals(privateChatMap.get(name)) ) {
                privateChatMap.remove(name);
            }
        }
        allPrivateChats.remove(chatID);
    }
    
    public static List<UUID> selectPublicChatsByUser( UUID userID ) {
        LinkedList<UUID> result = new LinkedList<UUID>();
        for ( UUID chatID : allPublicChats.keySet() ) {
            if ( allPublicChats.get(chatID).getUsers().contains(userID) ) {
                result.add(chatID);
            }
        }
        return result;
    }
    
    public static List<UUID> selectPrivateChatsByUser( UUID userID ) {
        LinkedList<UUID> result = new LinkedList<UUID>();
        for ( UUID chatID : allPrivateChats.keySet() ) {
            if ( allPrivateChats.get(chatID).getUsers().contains(userID) ) {
                result.add(chatID);
            }
        }
        return result;
    }
    
    private static ConcurrentHashMap<UUID, User> allUsers = new ConcurrentHashMap<UUID,User>();
    private static ConcurrentHashMap<UUID, PublicChat> allPublicChats = new ConcurrentHashMap<UUID, PublicChat>();
    private static ConcurrentHashMap<UUID, PrivateChat> allPrivateChats = new ConcurrentHashMap<UUID, PrivateChat>();
    
    private static ConcurrentHashMap<String, UUID> nameMap = new ConcurrentHashMap<String, UUID>();
    private static ConcurrentHashMap<String, UUID> publicChatMap = new ConcurrentHashMap<String, UUID>();
    private static ConcurrentHashMap<String, UUID> privateChatMap = new ConcurrentHashMap<String, UUID>();

}
